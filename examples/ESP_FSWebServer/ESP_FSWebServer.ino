/****************************************************************************************************************************
  ESP_FSWebServer - Example WebServer with SPIFFS backend for esp8266
  For Ethernet shields using ESP8266_W5500 (ESP8266 + LwIP W5500)

  WebServer_ESP8266_W5500 is a library for the ESP8266 with Ethernet W5500 to run WebServer

  Modified from
  1. Tzapu               (https://github.com/tzapu/WiFiManager)
  2. Ken Taylor          (https://github.com/kentaylor)
  3. Khoi Hoang          (https://github.com/khoih-prog/ESP_WiFiManager)

  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_W5500_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/
/*****************************************************************************************************************************
   How To Upload Files:
   1) Go to http://esp8266fs.local/edit, then "Choose file" -> "Upload"
   2) or Upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
   3) or you can upload the contents of a folder if you CD in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" esp8266fs.local/edit; done

   How To Use:
   1) access the sample web page at http://esp8266fs.local
   2) edit the page by going to http://esp8266fs.local/edit
   3) Use configurable user/password to login. Default is admin/admin
*****************************************************************************************************************************/

#if !( defined(ESP8266) )
  #error This code is intended to run on the (ESP8266 + W5500) platform! Please check your Tools->Board setting.
#endif

//////////////////////////////////////////////////////////////

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ESP8266_ETH_MGR_LOGLEVEL_    4

// To not display stored Credentials on Config Portal, select false. Default is true
// Even the stored Credentials are not display, just leave them all blank to reconnect and reuse the stored Credentials
//#define DISPLAY_STORED_CREDENTIALS_IN_CP        false

//////////////////////////////////////////////////////////////
// Using GPIO4, GPIO16, or GPIO5
#define CSPIN             16

//////////////////////////////////////////////////////////

#include <FS.h>

// Now support ArduinoJson 6.0.0+ ( tested with v6.19.4 )
#include <ArduinoJson.h>      // get it from https://arduinojson.org/ or install via Arduino library manager

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>

#define USE_LITTLEFS      true

#if USE_LITTLEFS
  #include <LittleFS.h>
  FS* filesystem =      &LittleFS;
  #define FileFS        LittleFS
  #define FS_Name       "LittleFS"
#else
  FS* filesystem =      &SPIFFS;
  #define FileFS        SPIFFS
  #define FS_Name       "SPIFFS"
#endif

//////////////////////////////////////////////////////////

#define ESP_getChipId()   (ESP.getChipId())

#define LED_ON      LOW
#define LED_OFF     HIGH

//////////////////////////////////////////////////////////

// Assuming max 49 chars
#define TZNAME_MAX_LEN            50
#define TIMEZONE_MAX_LEN          50

typedef struct
{
  char TZ_Name[TZNAME_MAX_LEN];     // "America/Toronto"
  char TZ[TIMEZONE_MAX_LEN];        // "EST5EDT,M3.2.0,M11.1.0"
  uint16_t checksum;
} EthConfig;

EthConfig         Ethconfig;

#define  CONFIG_FILENAME              F("/eth_cred.dat")

//////////////////////////////////////////////////////////

// Indicates whether ESP has credentials saved from previous session, or double reset detected
bool initialConfig = false;

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP8266_W5500_Manager.h>
#define USE_AVAILABLE_PAGES     true  //false

// To permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     true    //false

// Just use enough to save memory. On ESP8266, can cause blank ConfigPortal screen
// if using too much memory
#define USING_AFRICA        false
#define USING_AMERICA       true
#define USING_ANTARCTICA    false
#define USING_ASIA          false
#define USING_ATLANTIC      false
#define USING_AUSTRALIA     false
#define USING_EUROPE        false
#define USING_INDIAN        false
#define USING_PACIFIC       false
#define USING_ETC_GMT       false

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP          false

#define USING_CORS_FEATURE          true

////////////////////////////////////////////

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
  // Force DHCP to be true
  #if defined(USE_DHCP_IP)
    #undef USE_DHCP_IP
  #endif
  #define USE_DHCP_IP     true
#else
  // You can select DHCP or Static IP here
  //#define USE_DHCP_IP     true
  #define USE_DHCP_IP     false
#endif

#if ( USE_DHCP_IP )
  // Use DHCP

  #if (_ESP8266_ETH_MGR_LOGLEVEL_ > 3)
    #warning Using DHCP IP
  #endif

  IPAddress stationIP   = IPAddress(0, 0, 0, 0);
  IPAddress gatewayIP   = IPAddress(192, 168, 2, 1);
  IPAddress netMask     = IPAddress(255, 255, 255, 0);

#else
  // Use static IP

  #if (_ESP8266_ETH_MGR_LOGLEVEL_ > 3)
    #warning Using static IP
  #endif

  IPAddress stationIP   = IPAddress(192, 168, 2, 186);
  IPAddress gatewayIP   = IPAddress(192, 168, 2, 1);
  IPAddress netMask     = IPAddress(255, 255, 255, 0);
#endif

////////////////////////////////////////////

#define USE_CONFIGURABLE_DNS      true

IPAddress dns1IP      = gatewayIP;
IPAddress dns2IP      = IPAddress(8, 8, 8, 8);

//////////////////////////////////////////////////////////////

#include <ESP8266_W5500_Manager.h>               //https://github.com/khoih-prog/ESP8266_W5500_Manager

String host = "esp8266fs";

#define HTTP_PORT     80

ESP8266WebServer server(HTTP_PORT);

//holds the current upload
File fsUploadFile;

String http_username = "admin";
String http_password = "admin";

String separatorLine = "===============================================================";

//////////////////////////////////////////////////////////////

/******************************************
   // Defined in ESP8266_W5500_Manager.hpp
  typedef struct
  {
    IPAddress _sta_static_ip;
    IPAddress _sta_static_gw;
    IPAddress _sta_static_sn;
    #if USE_CONFIGURABLE_DNS
    IPAddress _sta_static_dns1;
    IPAddress _sta_static_dns2;
    #endif
  }  ETH_STA_IPConfig;
******************************************/

ETH_STA_IPConfig EthSTA_IPconfig;

//////////////////////////////////////////////////////////////

void initSTAIPConfigStruct(ETH_STA_IPConfig &in_EthSTA_IPconfig)
{
  in_EthSTA_IPconfig._sta_static_ip   = stationIP;
  in_EthSTA_IPconfig._sta_static_gw   = gatewayIP;
  in_EthSTA_IPconfig._sta_static_sn   = netMask;
#if USE_CONFIGURABLE_DNS
  in_EthSTA_IPconfig._sta_static_dns1 = dns1IP;
  in_EthSTA_IPconfig._sta_static_dns2 = dns2IP;
#endif
}

//////////////////////////////////////////////////////////////

void displayIPConfigStruct(ETH_STA_IPConfig in_EthSTA_IPconfig)
{
  LOGERROR3(F("stationIP ="), in_EthSTA_IPconfig._sta_static_ip, ", gatewayIP =", in_EthSTA_IPconfig._sta_static_gw);
  LOGERROR1(F("netMask ="), in_EthSTA_IPconfig._sta_static_sn);
#if USE_CONFIGURABLE_DNS
  LOGERROR3(F("dns1IP ="), in_EthSTA_IPconfig._sta_static_dns1, ", dns2IP =", in_EthSTA_IPconfig._sta_static_dns2);
#endif
}

//////////////////////////////////////////////////////////////

//format bytes
String formatBytes(size_t bytes)
{
  if (bytes < 1024)
  {
    return String(bytes) + "B";
  }
  else if (bytes < (1024 * 1024))
  {
    return String(bytes / 1024.0) + "KB";
  }
  else if (bytes < (1024 * 1024 * 1024))
  {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
  else
  {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

//////////////////////////////////////////////////////////////

String getContentType(String filename)
{
  if (server.hasArg("download"))
  {
    return "application/octet-stream";
  }
  else if (filename.endsWith(".htm"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".html"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".css"))
  {
    return "text/css";
  }
  else if (filename.endsWith(".js"))
  {
    return "application/javascript";
  }
  else if (filename.endsWith(".png"))
  {
    return "image/png";
  }
  else if (filename.endsWith(".gif"))
  {
    return "image/gif";
  }
  else if (filename.endsWith(".jpg"))
  {
    return "image/jpeg";
  }
  else if (filename.endsWith(".ico"))
  {
    return "image/x-icon";
  }
  else if (filename.endsWith(".xml"))
  {
    return "text/xml";
  }
  else if (filename.endsWith(".pdf"))
  {
    return "application/x-pdf";
  }
  else if (filename.endsWith(".zip"))
  {
    return "application/x-zip";
  }
  else if (filename.endsWith(".gz"))
  {
    return "application/x-gzip";
  }

  return "text/plain";
}

//////////////////////////////////////////////////////////////

bool handleFileRead(String path)
{
  Serial.println("handleFileRead: " + path);

  if (path.endsWith("/"))
  {
    path += "index.htm";
  }

  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";

  if (filesystem->exists(pathWithGz) || filesystem->exists(path))
  {
    if (filesystem->exists(pathWithGz))
    {
      path += ".gz";
    }

    File file = filesystem->open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////

void handleFileUpload()
{
  if (server.uri() != "/edit")
  {
    return;
  }

  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;

    if (!filename.startsWith("/"))
    {
      filename = "/" + filename;
    }

    Serial.print(F("handleFileUpload Name: "));
    Serial.println(filename);
    fsUploadFile = filesystem->open(filename, "w");
    filename.clear();
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    //Serial.print(F("handleFileUpload Data: ")); Serial.println(upload.currentSize);

    if (fsUploadFile)
    {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (fsUploadFile)
    {
      fsUploadFile.close();
    }

    Serial.print(F("handleFileUpload Size: "));
    Serial.println(upload.totalSize);
  }
}

//////////////////////////////////////////////////////////////

void handleFileDelete()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileDelete: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (!filesystem->exists(path))
  {
    return server.send(404, "text/plain", "FileNotFound");
  }

  filesystem->remove(path);
  server.send(200, "text/plain", "");
  path.clear();
}

//////////////////////////////////////////////////////////////

void handleFileCreate()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileCreate: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (filesystem->exists(path))
  {
    return server.send(500, "text/plain", "FILE EXISTS");
  }

  File file = filesystem->open(path, "w");

  if (file)
  {
    file.close();
  }
  else
  {
    return server.send(500, "text/plain", "CREATE FAILED");
  }

  server.send(200, "text/plain", "");
  path.clear();
}

//////////////////////////////////////////////////////////////

void handleFileList()
{
  if (!server.hasArg("dir"))
  {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server.arg("dir");
  Serial.println("handleFileList: " + path);
  Dir dir = filesystem->openDir(path);
  path.clear();

  String output = "[";

  while (dir.next())
  {
    File entry = dir.openFile("r");

    if (output != "[")
    {
      output += ',';
    }

    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";

    if (entry.name()[0] == '/')
    {
      output += &(entry.name()[1]);
    }
    else
    {
      output += entry.name();
    }

    output += "\"}";
    entry.close();
  }

  output += "]";
  server.send(200, "text/json", output);
}

//////////////////////////////////////////////////////////////

void toggleLED()
{
  //toggle state
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

//////////////////////////////////////////////////////////////

#if USE_ESP_ETH_MANAGER_NTP
void printLocalTime()
{
  static time_t now;

  now = time(nullptr);

  if ( now > 1451602800 )
  {
    Serial.print("Local Date/Time: ");
    Serial.print(ctime(&now));
  }
}
#endif

//////////////////////////////////////////////////////////

void heartBeatPrint()
{
#if USE_ESP_ETH_MANAGER_NTP
  printLocalTime();
#else
  static int num = 1;

  if (eth.connected())
    Serial.print(F("H"));        // H means connected to Ethernet
  else
    Serial.print(F("F"));        // F means not connected to Ethernet

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }

#endif
}

//////////////////////////////////////////////////////////////

void check_status()
{
  static ulong checkstatus_timeout  = 0;

  static ulong current_millis;

#if USE_ESP_ETH_MANAGER_NTP
#define HEARTBEAT_INTERVAL    60000L
#else
#define HEARTBEAT_INTERVAL    10000L
#endif

  current_millis = millis();

  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((current_millis > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = current_millis + HEARTBEAT_INTERVAL;
  }
}

//////////////////////////////////////////////////////////////

int calcChecksum(uint8_t* address, uint16_t sizeToCalc)
{
  uint16_t checkSum = 0;

  for (uint16_t index = 0; index < sizeToCalc; index++)
  {
    checkSum += * ( ( (byte*) address ) + index);
  }

  return checkSum;
}

//////////////////////////////////////////////////////////////

bool loadConfigData()
{
  File file = FileFS.open(CONFIG_FILENAME, "r");
  LOGERROR(F("LoadCfgFile "));

  memset((void *) &Ethconfig,       0, sizeof(Ethconfig));
  memset((void *) &EthSTA_IPconfig, 0, sizeof(EthSTA_IPconfig));

  if (file)
  {
    file.readBytes((char *) &Ethconfig,   sizeof(Ethconfig));
    file.readBytes((char *) &EthSTA_IPconfig, sizeof(EthSTA_IPconfig));
    file.close();

    LOGERROR(F("OK"));

    if ( Ethconfig.checksum != calcChecksum( (uint8_t*) &Ethconfig, sizeof(Ethconfig) - sizeof(Ethconfig.checksum) ) )
    {
      LOGERROR(F("Ethconfig checksum wrong"));

      return false;
    }

    displayIPConfigStruct(EthSTA_IPconfig);

    return true;
  }
  else
  {
    LOGERROR(F("failed"));

    return false;
  }
}

//////////////////////////////////////////////////////////////

void saveConfigData()
{
  File file = FileFS.open(CONFIG_FILENAME, "w");
  LOGERROR(F("SaveCfgFile "));

  if (file)
  {
    Ethconfig.checksum = calcChecksum( (uint8_t*) &Ethconfig, sizeof(Ethconfig) - sizeof(Ethconfig.checksum) );

    file.write((uint8_t*) &Ethconfig, sizeof(Ethconfig));

    displayIPConfigStruct(EthSTA_IPconfig);

    file.write((uint8_t*) &EthSTA_IPconfig, sizeof(EthSTA_IPconfig));
    file.close();

    LOGERROR(F("OK"));
  }
  else
  {
    LOGERROR(F("failed"));
  }
}

//////////////////////////////////////////////////////////////

void initEthernet()
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  LOGWARN(F("Default SPI pinout:"));
  LOGWARN1(F("MOSI:"), MOSI);
  LOGWARN1(F("MISO:"), MISO);
  LOGWARN1(F("SCK:"),  SCK);
  LOGWARN1(F("CS:"),   CSPIN);
  LOGWARN(F("========================="));

#if !USING_DHCP
  //eth.config(localIP, gateway, netMask, gateway);
  eth.config(EthSTA_IPconfig._sta_static_ip, EthSTA_IPconfig._sta_static_gw, EthSTA_IPconfig._sta_static_sn,
             EthSTA_IPconfig._sta_static_dns1);
#endif

  eth.setDefault();

  if (!eth.begin())
  {
    Serial.println("No Ethernet hardware ... Stop here");

    while (true)
    {
      delay(1000);
    }
  }
  else
  {
    Serial.print("Connecting to network : ");

    while (!eth.connected())
    {
      Serial.print(".");
      delay(1000);
    }
  }

  Serial.println();

#if USING_DHCP
  Serial.print("Ethernet DHCP IP address: ");
#else
  Serial.print("Ethernet Static IP address: ");
#endif

  Serial.println(eth.localIP());
}

//////////////////////////////////////////////////////////////

void setup()
{
  //set led pin as output
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  while (!Serial);

  delay(200);

  Serial.print(F("\nStarting ESP_FSWebServer using "));
  Serial.print(FS_Name);
  Serial.print(F(" on "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);
  Serial.println(ESP8266_W5500_MANAGER_VERSION);

  Serial.setDebugOutput(false);

  // Uncomment to force FS format. Remember to uncomment after done
#if FORMAT_FILESYSTEM
  Serial.println(F("Forced Formatting."));
  FileFS.format();
#endif

  // Format FileFS if not yet
  if (!FileFS.begin())
  {
    FileFS.format();

    Serial.println(F("SPIFFS/LittleFS failed! Already tried formatting."));

    if (!FileFS.begin())
    {
      // prevents debug info from the library to hide err message.
      delay(100);

#if USE_LITTLEFS
      Serial.println(F("LittleFS failed!. Please use SPIFFS or EEPROM. Stay forever"));
#else
      Serial.println(F("SPIFFS failed!. Please use LittleFS or EEPROM. Stay forever"));
#endif

      while (true)
      {
        delay(1);
      }
    }
  }

  Dir dir = FileFS.openDir("/");
  Serial.println(F("Opening / directory"));

  while (dir.next())
  {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();

    Serial.println("FS File: " + fileName + ", size: " + formatBytes(fileSize));
  }

  Serial.println();

  unsigned long startedAt = millis();

  initSTAIPConfigStruct(EthSTA_IPconfig);

  digitalWrite(LED_BUILTIN, LED_ON);

  //Local initialization. Once its business is done, there is no need to keep it around
  // Use this to default DHCP hostname to ESP8266-XXXXXX
  //ESP8266_W5500_Manager ESP8266_W5500_manager(&webServer, &dnsServer);
  // Use this to personalize DHCP hostname (RFC952 conformed)
  ESP8266_W5500_Manager ESP8266_W5500_manager("ESP-FSWebServer");

#if !USE_DHCP_IP
  // Set (static IP, Gateway, Subnetmask, DNS1 and DNS2) or (IP, Gateway, Subnetmask). New in v1.0.5
  ESP8266_W5500_manager.setSTAStaticIPConfig(EthSTA_IPconfig);
#endif

#if USING_CORS_FEATURE
  ESP8266_W5500_manager.setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  bool configDataLoaded = loadConfigData();

  if (configDataLoaded)
  {
#if USE_ESP_WIFIMANAGER_NTP

    if ( strlen(Ethconfig.TZ_Name) > 0 )
    {
      LOGERROR3(F("Saving current TZ_Name ="), Ethconfig.TZ_Name, F(", TZ = "), Ethconfig.TZ);

      configTime(Ethconfig.TZ, "pool.ntp.org");
    }
    else
    {
      Serial.println(F("Current Timezone is not set. Enter Config Portal to set."));
    }

#endif
  }
  else
  {
    // Enter CP only if no stored Credentials on flash and file
    Serial.println(F("Open Config Portal without Timeout: No stored Credentials."));
    initialConfig = true;
  }

  //////////////////////////////////

  // Connect ETH now if using STA
  initEthernet();

  //////////////////////////////////

  if (initialConfig)
  {
    Serial.print(F("Starting configuration portal @ "));
    Serial.println(eth.localIP());

    digitalWrite(LED_BUILTIN, LED_ON); // Turn led on as we are in configuration mode.

    //sets timeout in seconds until configuration portal gets turned off.
    //If not specified device will remain in configuration mode until
    //switched off via webserver or device is restarted.
    //ESP8266_W5500_manager.setConfigPortalTimeout(600);

    // Starts an access point
    if (!ESP8266_W5500_manager.startConfigPortal())
      Serial.println(F("Not connected to ETH network but continuing anyway."));
    else
    {
      Serial.println(F("ETH network connected...yeey :)"));
    }

#if USE_ESP_ETH_MANAGER_NTP
    String tempTZ   = ESP8266_W5500_manager.getTimezoneName();

    if (strlen(tempTZ.c_str()) < sizeof(Ethconfig.TZ_Name) - 1)
      strcpy(Ethconfig.TZ_Name, tempTZ.c_str());
    else
      strncpy(Ethconfig.TZ_Name, tempTZ.c_str(), sizeof(Ethconfig.TZ_Name) - 1);

    const char * TZ_Result = ESP8266_W5500_manager.getTZ(Ethconfig.TZ_Name);

    if (strlen(TZ_Result) < sizeof(Ethconfig.TZ) - 1)
      strcpy(Ethconfig.TZ, TZ_Result);
    else
      strncpy(Ethconfig.TZ, TZ_Result, sizeof(Ethconfig.TZ_Name) - 1);

    if ( strlen(Ethconfig.TZ_Name) > 0 )
    {
      LOGERROR3(F("Saving current TZ_Name ="), Ethconfig.TZ_Name, F(", TZ = "), Ethconfig.TZ);

      configTime(Ethconfig.TZ, "pool.ntp.org");
    }
    else
    {
      LOGERROR(F("Current Timezone Name is not set. Enter Config Portal to set."));
    }

#endif

    ESP8266_W5500_manager.getSTAStaticIPConfig(EthSTA_IPconfig);

    saveConfigData();

#if !USE_DHCP_IP

    // Reset to use new Static IP, if different from current eth.localIP()
    if (eth.localIP() != EthSTA_IPconfig._sta_static_ip)
    {
      Serial.print(F("Current IP = "));
      Serial.print(eth.localIP());
      Serial.print(F(". Reset to take new IP = "));
      Serial.println(EthSTA_IPconfig._sta_static_ip);

      ESP.reset();
      delay(2000);
    }

#endif
  }

  digitalWrite(LED_BUILTIN, LED_OFF); // Turn led off as we are not in configuration mode.

  startedAt = millis();

  Serial.print(F("After waiting "));
  Serial.print((float) (millis() - startedAt) / 1000);
  Serial.print(F(" secs more in setup(), connection result is "));

  if (eth.connected())
  {
    Serial.print(F("connected. Local IP: "));
    Serial.println(eth.localIP());
  }

  MDNS.begin(host);

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", HTTP_PORT);

  //SERVER INIT
  //list directory
  server.on("/list", HTTP_GET, handleFileList);

  //load editor
  server.on("/edit", HTTP_GET, []()
  {
    if (!handleFileRead("/edit.htm"))
    {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);

  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);

  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []()
  {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([]()
  {
    if (!handleFileRead(server.uri()))
    {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, []()
  {
    String json = "{";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ", \"analog\":" + String(analogRead(A0));
    json += ", \"gpio\":" + String((uint32_t)(0));
    json += "}";
    server.send(200, "text/json", json);
    json = String();
  });

  server.begin();

  MDNS.begin(host);
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", HTTP_PORT);

  //////////////////////////////////////////////////////////////

  Serial.print(F("HTTP server started @ "));
  Serial.println(eth.localIP());

  Serial.println(separatorLine);
  Serial.print("Open http://");
  Serial.print(eth.localIP());
  Serial.println("/edit.htm to see the file browser");
  Serial.println("Using username = " + http_username + " and password = " + http_password);
  Serial.println(separatorLine);

  digitalWrite(LED_BUILTIN, LED_OFF);
}

//////////////////////////////////////////////////////////////

void loop()
{
  MDNS.update();

  server.handleClient();

  check_status();
}
