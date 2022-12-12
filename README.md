# ESP8266_W5500_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_W5500_manager.svg?)](https://www.ardu-badge.com/ESP8266_W5500_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP8266_W5500_manager.svg)](https://github.com/khoih-prog/ESP8266_W5500_Manager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP8266_W5500_Manager/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP8266_W5500_manager.svg)](http://github.com/khoih-prog/ESP8266_W5500_Manager/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Why do we need this ESP8266_W5500_Manager library](#why-do-we-need-this-ESP8266_W5500_Manager-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [How It Works](#how-it-works)
* [HOWTO Basic configurations](#howto-basic-configurations)
  * [1. Using default for every configurable parameter](#1-using-default-for-every-configurable-parameter)
  * [2. Using many configurable parameters](#2-using-many-configurable-parameters)
  * [3. Using STA-mode DHCP, but don't like to change to static IP or display in Config Portal](#3-using-sta-mode-dhcp-but-dont-like-to-change-to-static-ip-or-display-in-config-portal) 
  * [4. Using STA-mode DHCP, but permit to change to static IP and display in Config Portal](#4-using-sta-mode-dhcp-but-permit-to-change-to-static-ip-and-display-in-config-portal)
  * [5. Using STA-mode StaticIP, and be able to change to DHCP IP and display in Config Portal](#5-using-sta-mode-staticip-and-be-able-to-change-to-dhcp-ip-and-display-in-config-portal)
  * [6. Using STA-mode StaticIP and configurable DNS, and be able to change to DHCP IP and display in Config Portal](#6-using-sta-mode-staticip-and-configurable-dns-and-be-able-to-change-to-dhcp-ip-and-display-in-config-portal) 
  * [7. Using STA-mode StaticIP and auto DNS, and be able to change to DHCP IP and display in Config Portal](#7-using-sta-mode-staticip-and-auto-dns-and-be-able-to-change-to-dhcp-ip-and-display-in-config-portal)
  * [8. Not using NTP to avoid issue with some WebBrowsers, especially in CellPhone or Tablets.](#8-not-using-ntp-to-avoid-issue-with-some-webbrowsers-especially-in-cellphone-or-tablets)
  * [9. Using NTP feature with CloudFlare. System can hang until you have Internet access for CloudFlare.](#9-using-ntp-feature-with-cloudflare-system-can-hang-until-you-have-internet-access-for-cloudflare) 
  * [10. Using NTP feature without CloudFlare to avoid system hang if no Internet access for CloudFlare.](#10-using-ntp-feature-without-cloudflare-to-avoid-system-hang-if-no-internet-access-for-cloudflare)
  * [11. Setting STA-mode static IP](#11-setting-sta-mode-static-ip)
  * [12. Using CORS (Cross-Origin Resource Sharing) feature](#12-using-cors-cross-origin-resource-sharing-feature) 
  * [13. How to auto getting _timezoneName](#13-how-to-auto-getting-_timezonename)
  * [14. How to get TZ variable to configure Timezone](#14-how-to-get-tz-variable-to-configure-timezone) 
  * [15. How to use the TZ variable to configure Timezone](#15-how-to-use-the-tz-variable-to-configure-timezone)
* [HOWTO Open Config Portal](#howto-open-config-portal)
* [HOWTO Add Dynamic Parameters](#howto-add-dynamic-parameters) 
  * [1. Determine the variables to be configured via Config Portal (CP)](#1-determine-the-variables-to-be-configured-via-config-portal-cp)
  * [2. Initialize the variables to prepare for Config Portal (CP)](#2-initialize-the-variables-to-prepare-for-config-portal-cp)
    * [2.1 Use the following simple constructor for simple variables such as `thingspeakApiKey`, `pinSda` and `pinScl`](#21-use-the-following-simple-constructor-for-simple-variables-such-as-thingspeakapikey-pinsda-and-pinscl-) 
    * [2.2 For example, to create a new `ESP8266_EMParameter` object `p_thingspeakApiKey` for `thingspeakApiKey`](#22-for-example-to-create-a-new-ESP8266_EMParameter-object-p_thingspeakapikey-for-thingspeakapikey)
    * [2.3 Use the more complex following constructor for variables such as `sensorDht22`](#23-use-the-more-complex-following-constructor-for-variables-such-as-sensordht22)
    * [2.4 For example, to create a new `ESP8266_EMParameter` object `p_sensorDht22` for `sensorDht22`](#24-for-example-to-create-a-new-ESP8266_EMParameter-object-p_sensordht22-for-sensordht22)
  * [3. Add the variables to Config Portal (CP)](#3-add-the-variables-to-config-portal-cp) 
    * [3.1 addParameter() function Prototype:](#31-addparameter-function-prototype)
    * [3.2 Code to add variables to CP](#32-code-to-add-variables-to-cp)
  * [4. Save the variables configured in Config Portal (CP)](#4-save-the-variables-configured-in-config-portal-cp) 
    * [4.1 Getting variables' data from CP](#41-getting-variables-data-from-cp)
  * [5. Write to FS (SPIFFS, LittleFS, etc.) using JSON format](#5-write-to-fs-spiffs-littlefs-etc-using-json-format)
    * [5.1 Create a DynamicJsonDocument Object](#51-create-a-dynamicjsondocument-object) 
    * [5.2 Fill the DynamicJsonDocument Object with data got from Config Portal](#52-fill-the-dynamicjsondocument-object-with-data-got-from-config-portal)
    * [5.3 Open file to write the Jsonified data](#53-open-file-to-write-the-jsonified-data)
    * [5.4 Write the Jsonified data to CONFIG_FILE](#54-write-the-jsonified-data-to-config_file) 
    * [5.5 Close CONFIG_FILE to flush and save the data](#55-close-config_file-to-flush-and-save-the-data)
  * [6. Read from FS using JSON format](#6-read-from-fs-using-json-format) 
    * [6.1 Open CONFIG_FILE to read](#61-open-config_file-to-read) 
    * [6.2 Open CONFIG_FILE to read](62-open-config_file-to-read)
    * [6.3 Populate the just-read Jsonified data into the DynamicJsonDocument json object](#63-populate-the-just-read-jsonified-data-into-the-dynamicjsondocument-json-object)
    * [6.4 Parse the Jsonified data from the DynamicJsonDocument json object to store into corresponding parameters](#64-parse-the-jsonified-data-from-the-dynamicjsondocument-json-object-to-store-into-corresponding-parameters) 
    * [6.5 Then what to do now](#65-then-what-to-do-now)
* [So, how it works?](#so-how-it-works)
* [Documentation](#documentation)
  * [Password protect the configuration Access Point](#password-protect-the-configuration-access-point)
  * [Callbacks](#callbacks)
    * [Save settings](#save-settings) 
  * [ConfigPortal Timeout](#configportal-timeout)
  * [On Demand ConfigPortal](#on-demand-configportal)
  * [Custom Parameters](#custom-parameters)
  * [Custom IP Configuration](#custom-ip-configuration) 
    * [Custom Station (client) Static IP Configuration](#custom-station-client-static-ip-configuration)
  * [Custom HTML, CSS, Javascript](#custom-html-css-javascript) 
* [How to connect W5x00 to ESP8266](#How-to-connect-W5x00-to-ESP8266)
* [Examples](#examples)
  * [ConfigOnSwitch](examples/ConfigOnSwitch)
  * [ConfigOnSwitchFS](examples/ConfigOnSwitchFS)
  * [ConfigOnDoubleReset_TZ](examples/ConfigOnDoubleReset_TZ)         (now support ArduinoJson 6.0.0+ as well as 5.13.5-)
  * [ConfigOnDoubleReset](examples/ConfigOnDoubleReset)               (now support ArduinoJson 6.0.0+ as well as 5.13.5-)
  * [ConfigPortalParamsOnSwitch](examples/ConfigPortalParamsOnSwitch) (now support ArduinoJson 6.0.0+ as well as 5.13.5-)
  * [ESP8266_FSWebServer](examples/ESP8266_FSWebServer)
  * [ESP8266_FSWebServer_DRD](examples/ESP8266_FSWebServer_DRD)
* [Example ConfigOnSwitch](#example-ConfigOnSwitch)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ConfigOnDoubleReset_TZ using LittleFS on ESP8266_DEV with ESP8266_W5500](#1-ConfigOnDoubleReset_TZ-using-LittleFS-on-ESP8266_DEV-with-ESP8266_W5500)
  * [2. ConfigOnSwichFS using LittleFS on ESP8266_DEV with ESP8266_W5500](#2-ConfigOnSwichFS-using-LittleFS-on-ESP8266_DEV-with-ESP8266_W5500)
  * [3. ESP8266_FSWebServer_DRD using LittleFS on ESP8266_DEV with ESP8266_W5500](#3-ESP8266_FSWebServer_DRD-using-LittleFS-on-ESP8266_DEV-with-ESP8266_W5500)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---


### Why do we need this [ESP8266_W5500_Manager library](https://github.com/khoih-prog/ESP8266_W5500_Manager)

#### Features

This is an `ESP8266 + LwIP W5500` Credentials and Connection Manager with fallback Web ConfigPortal. This Library is used for configuring ESP8266 Ethernet Static / DHCP and Credentials at runtime. You can specify static DNS servers, personalized HostName and CORS feature.

This library is based on, modified and improved from:

1. [`Khoi Hoang's ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)


#### Currently supported Boards

This [**ESP8266_W5500_Manager** library](https://github.com/khoih-prog/ESP8266_W5500_Manager) currently supports these following boards:

 1. **ESP8266 boards** using `LwIP W5500 Ethernet`


<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/W5500.png">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/W5500_small.png">
</p>
 
---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
 3. [`ESP_DoubleResetDetector v1.3.2+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) if using DRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector). Use v1.1.0+ if using `LittleFS` for ESP8266 v1.0.6+.
 
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `ESP8266_W5500_Manager`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_W5500_manager.svg?)](https://www.ardu-badge.com/ESP8266_W5500_Manager) for more detailed instructions.

### Manual Install

1. Navigate to [ESP8266_W5500_Manager](https://github.com/khoih-prog/ESP8266_W5500_Manager) page.
2. Download the latest release `ESP8266_W5500_Manager-main.zip`.
3. Extract the zip file to `ESP8266_W5500_Manager-main` directory 
4. Copy the whole `ESP8266_W5500_Manager-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP8266_W5500_Manager** library](https://registry.platformio.org/libraries/khoih-prog/ESP8266_W5500_Manager) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ESP8266_W5500_Manager/installation). Search for **ESP8266_W5500_Manager** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---


### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can use

```cpp
#include <ESP8266_W5500_Manager.hpp>               //https://github.com/khoih-prog/ESP8266_W5500_Manager
```

in many files. But be sure to use the following `#include <ESP8266_W5500_Manager.h>` **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <ESP8266_W5500_Manager.h>          //https://github.com/khoih-prog/ESP8266_W5500_Manager
```

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESP8266_W5500_Manager/discussions/80)

---
---

## How It Works

- The [ConfigOnSwitch](examples/ConfigOnSwitch) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [ConfigOnSwitch](examples/ConfigOnSwitch) is that a new `ESP8266` will start a ConfigPortal when powered up and save the configuration data in non volatile memory. Thereafter, the ConfigPortal will only be started again if a button is pushed on the `ESP8266` module.
- Using any network-enabled device with a browser (computer, phone, tablet) connect to the newly created Access Point (AP) (Dynamic or Static IP specified in sketch)

then connect `WebBrowser` to configurable ConfigPortal IP address, e.g. `192.168.186`

---
---

### HOWTO Basic configurations

#### 1. Using default for every configurable parameter

- Include in your sketch

```cpp
#include <FS.h>

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>

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

// You only need to format the filesystem once
//#define FORMAT_FILESYSTEM       true
#define FORMAT_FILESYSTEM         false

////////////////////////////////////////////////////

#include <ESP8266_W5500_Manager.h>               //https://github.com/khoih-prog/ESP8266_W5500_Manager

#define HTTP_PORT     80

```
---

#### 2. Using many configurable parameters

- Include in your sketch

```cpp
#include <FS.h>

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>

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

//////////////////////////////////////////////////////////////

// You only need to format the filesystem once
//#define FORMAT_FILESYSTEM       true
#define FORMAT_FILESYSTEM         false

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

#define  CONFIG_FILENAME              F("/eth_cred.dat")

//////////////////////////////////////////////////////////////

// Indicates whether ESP has credentials saved from previous session, or double reset detected
bool initialConfig = false;

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP8266_W5500_Manager.h>
#define USE_AVAILABLE_PAGES     true

// From v1.0.10 to permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     true

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

// New in v1.0.11
#define USING_CORS_FEATURE          true

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

#define USE_CONFIGURABLE_DNS      true

IPAddress dns1IP      = gatewayIP;
IPAddress dns2IP      = IPAddress(8, 8, 8, 8);

#include <ESP8266_W5500_Manager.h>               //https://github.com/khoih-prog/ESP8266_W5500_Manager

#define HTTP_PORT     80

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
```

---

#### 3. Using STA-mode DHCP, but don't like to change to static IP or display in Config Portal

```cpp
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
#define USE_STATIC_IP_CONFIG_IN_CP          false
```

---

#### 4. Using STA-mode DHCP, but permit to change to static IP and display in Config Portal

```cpp
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
  // Force DHCP to be true
  #if defined(USE_DHCP_IP)
    #undef USE_DHCP_IP
  #endif
  #define USE_DHCP_IP     true
#else
  // You can select DHCP or Static IP here
  #define USE_DHCP_IP     true
#endif
```

---

#### 5. Using STA-mode StaticIP, and be able to change to DHCP IP and display in Config Portal

```cpp
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
// Force DHCP to be true
  #if defined(USE_DHCP_IP)
    #undef USE_DHCP_IP
  #endif
  #define USE_DHCP_IP     true
#else
  // You can select DHCP or Static IP here
  #define USE_DHCP_IP     false
#endif
```

---

#### 6. Using STA-mode StaticIP and configurable DNS, and be able to change to DHCP IP and display in Config Portal

```cpp
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
  // Force DHCP to be true
  #if defined(USE_DHCP_IP)
    #undef USE_DHCP_IP
  #endif
  #define USE_DHCP_IP     true
#else
  // You can select DHCP or Static IP here
  #define USE_DHCP_IP     false
#endif

#define USE_CONFIGURABLE_DNS      true

IPAddress dns1IP      = gatewayIP;
IPAddress dns2IP      = IPAddress(8, 8, 8, 8);
```

---

#### 7. Using STA-mode StaticIP and auto DNS, and be able to change to DHCP IP and display in Config Portal

```cpp
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
  // Force DHCP to be true
  #if defined(USE_DHCP_IP)
    #undef USE_DHCP_IP
  #endif
  #define USE_DHCP_IP     true
#else
  // You can select DHCP or Static IP here
  #define USE_DHCP_IP     false
#endif

#define USE_CONFIGURABLE_DNS      false
```

---

#### 8. Not using NTP to avoid issue with some WebBrowsers, especially in CellPhone or Tablets.


```cpp
// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     false
```

---

#### 9. Using NTP feature with CloudFlare. System can hang until you have Internet access for CloudFlare.


```cpp
// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     true

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP          true
```

---

#### 10. Using NTP feature without CloudFlare to avoid system hang if no Internet access for CloudFlare.


```cpp
// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     true

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP          false
```

---

#### 11. Setting STA-mode static IP


```cpp
//ESP8266_W5500_manager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
ESP8266_W5500_manager.setSTAStaticIPConfig(WM_STA_IPconfig);
```

---

#### 12. Using CORS (Cross-Origin Resource Sharing) feature

1. To use CORS feature with **default** CORS Header "*". Some WebBrowsers won't accept this allowing-all "*" CORS Header.

```cpp
// Default false for using only whenever necessary to avoid security issue
#define USING_CORS_FEATURE     true
```

2. To use CORS feature with specific CORS Header "Your Access-Control-Allow-Origin". **To be modified** according to your specific Allowed-Origin.

```cpp
// Default false for using only whenever necessary to avoid security issue
#define USING_CORS_FEATURE     true

...

#if USING_CORS_FEATURE
  ESP_wifiManager.setCORSHeader("Your Access-Control-Allow-Origin");
#endif
```

3. Not use CORS feature (default)

```cpp
// Default false for using only whenever necessary to avoid security issue
#define USING_CORS_FEATURE     false
```

---

#### 13. How to auto getting _timezoneName


1. Turn on auto `NTP` configuration by

```cpp
// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_ETH_MANAGER_NTP     true
```

2. The `_timezoneName`, in the format similar to **America/New_York, America/Toronto, Europe/London, etc.**, can be retrieved by using


```cpp
String tempTZ = ESP8266_W5500_manager.getTimezoneName();
```

---

#### 14. How to get TZ variable to configure Timezone


1. ESP8266 `TZ` can be configured, using the  similar to `EST5EDT,M3.2.0,M11.1.0` (for America/New_York) , as follows:

```cpp
// EST5EDT,M3.2.0,M11.1.0 (for America/New_York)
// EST5EDT is the name of the time zone
// EST is the abbreviation used when DST is off
// 6 hours is the time difference from GMT
// EDT is the abbreviation used when DST is on
// ,M3 is the third month
// .2 is the second occurrence of the day in the month
// .0 is Sunday
// ,M11 is the eleventh month
// .1 is the first occurrence of the day in the month
// .0 is Sunday

configTime(Ethconfig.TZ, "pool.ntp.org");
```

2. To convert from `_timezoneName` to `TZ`, use the function `getTZ()` as follows:

```cpp
const char * TZ_Result = ESP8266_W5500_manager.getTZ(_timezoneName);
```

The conversion depends on the stored TZs, which is using some memory, and can cause issue for ESP8266 in certain cases. Therefore, enable just the region you're interested.

For example, your application is used in America continent, you need just

```cpp
#define USING_AMERICA       true
```

Hereafter is the regions' list


```cpp
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
```

---


#### 15. How to use the TZ variable to configure Timezone


```cpp
configTime(Ethconfig.TZ, "pool.ntp.org");
```

then to print local time


```cpp
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
```

---
---

### HOWTO Open Config Portal

- When you want to open a config portal, with default `DHCP` hostname `ESP8266-XXXXXX`, just add

```cpp
#include <ESP8266_W5500_Manager.h>              //https://github.com/khoih-prog/ESP8266_W5500_Manager

#define HTTP_PORT           80

WebServer webServer(HTTP_PORT);

ESP8266_W5500_Manager ESP8266_W5500_manager();
```

If you'd like to have a personalized hostname 
`(RFC952-conformed,- 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char)`

add

```cpp
ESP8266_W5500_Manager ESP8266_W5500_manager("Personalized-HostName");
```

then later call

```cpp
ESP8266_W5500_manager.startConfigPortal()
```

While in Config Portal, connect to it using its AP IP, e.g. `192.168.2.186`, configure Credentials, then save. The settings will be saved in non volatile memory. It will then reboot and autoconnect.

---
---

### HOWTO Add Dynamic Parameters


These illustrating steps is based on the example [ConfigOnSwitchFS](https://github.com/khoih-prog/ESP8266_W5500_Manager/tree/main/examples/ConfigOnSwitchFS)

###  1. Determine the variables to be configured via Config Portal (CP)

The application will:

- use DHT sensor (either DHT11 or DHT22) and 
- need to connect to ThingSpeak with unique user's API Key. 

The DHT sensor is connected to the ESP boards using SDA/SCL pins which also need to be configurable.

So this is the list of variables to be dynamically configured using CP

```
1. `thingspeakApiKey`,  type `char array`, max length 17 chars, and just arbitrarily selected default value to be "" or "ThingSpeak-APIKey"
2. `sensorDht22`,       type `bool`, default to be `true` (DHT22)
3. `pinSda`,            type `int`,  default to be `PIN_D2`
4. `pinScl`,            type `int`,  default to be `PIN_D1`
```

The Label can be any arbitrary string that help you identify the variable, but must be unique in your application

The initial code will be

```cpp
#define API_KEY_LEN                 17

// Default configuration values
char thingspeakApiKey[API_KEY_LEN]  = "";
bool sensorDht22                    = true;
int pinSda                          = PIN_D2;     // Pin D2 mapped to pin GPIO4 of ESP8266
int pinScl                          = PIN_D1;     // Pin D1 mapped to pin GPIO5 of ESP8266

// Any unique string helping you identify the vars
#define ThingSpeakAPI_Label         "thingspeakApiKey"
#define SensorDht22_Label           "SensorDHT22"
#define PinSDA_Label                "PinSda"
#define PinSCL_Label                "PinScl"
```

---

###  2. Initialize the variables to prepare for Config Portal (CP)

The example [ConfigOnSwitchFS](https://github.com/khoih-prog/ESP8266_W5500_Manager/tree/main/examples/ConfigOnSwitchFS) will open the CP whenever a SW press is detected in `loop()`. So the code to add `dynamic variables` will be there, just after the CP `ESP8266_W5500_Manager` class initialization to create `ESP8266_W5500_Manager` object.

```cpp
void loop()
{
// is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || (digitalRead(TRIGGER_PIN2) == LOW))
  {
    Serial.println("\nConfiguration portal requested.");
    digitalWrite(LED_BUILTIN, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.

    //Local initialization. Once its business is done, there is no need to keep it around
    ESP8266_W5500_Manager ESP8266_W5500_manager("ConfigOnSwitchFS");

    //Check if there is stored WiFi router/password credentials.
    //If not found, device will remain in configuration mode until switched off via webserver.
    Serial.print("Opening configuration portal. ");
    
    ...
    
    // The addition of dynamic vars will be somewhere here
    
}    
```

The `ESP8266_EMParameter` class constructor will be used to initialize each newly-added parameter object.

#### 2.1 Use the following simple constructor for simple variables such as `thingspeakApiKey`, `pinSda` and `pinScl` :

```cpp
ESP8266_EMParameter(const char *id, const char *placeholder, const char *defaultValue, int length);
```

#### 2.2 For example, to create a new `ESP8266_EMParameter` object `p_thingspeakApiKey` for `thingspeakApiKey`, 

The command to use will be 


```cpp
ESP8266_EMParameter p_thingspeakApiKey(ThingSpeakAPI_Label, "Thingspeak API Key", thingspeakApiKey, API_KEY_LEN);
```

where

```
- p_thingspeakApiKey                  : ESP8266_EMParameter class object reference that stores the new Custom Parameter
- id => ThingSpeakAPI_Label           : var ref to Json associative name and HTML element ID for the new Custom Paramerter you just defined in step 1
- placeholder => "Thingspeak API Key" : HTML input placeholder and/or label element text the user sees in the configuration interface for this Custom Parameter
- defaultValue => thingspeakApiKey    : variable for storing the value of your Custom Parameter in the file system or default value when no data is entered
- length  => API_KEY_LEN              : max allowed length you want for this Custom Parameter to have
```

For `pinSda` and `pinScl`, the command will be similar

```cpp
// I2C SCL and SDA parameters are integers so we need to convert them to char array but
// no other special considerations
char convertedValue[3];
sprintf(convertedValue, "%d", pinSda);
ESP8266_EMParameter p_pinSda(PinSDA_Label, "I2C SDA pin", convertedValue, 3);

sprintf(convertedValue, "%d", pinScl);
ESP8266_EMParameter p_pinScl(PinSCL_Label, "I2C SCL pin", convertedValue, 3);
```

where

```
- p_pinSda / p_pinScl                         : ESP8266_EMParameter class object reference that stores the new Custom Parameter
- id => PinSDA_Label/PinSCL_Label             : var ref to Json associative name and HTML element ID for the new Custom Paramerter you just defined in step 1
- placeholder => "I2C SDA pin"/"I2C SCL pin"  : HTML input placeholder and/or label element text the user sees in the configuration interface for this Custom Parameter
- defaultValue => convertedValue              : variable for storing the value of your Custom Parameter in the file system or default value when no data is entered
- length  => 3                                : max allowed length you want for this Custom Parameter to have
```

---

#### 2.3 Use the more complex following constructor for variables such as `sensorDht22`:

```cpp
ESP8266_EMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement);
```

#### 2.4 For example, to create a new `ESP8266_EMParameter` object `p_sensorDht22` for `sensorDht22`, 

The command to use will be 


```cpp
ESP8266_EMParameter p_sensorDht22(SensorDht22_Label, "DHT-22 Sensor", "T", 2, customhtml, WFM_LABEL_AFTER);
```

where

```
- p_sensorDht22                       : ESP8266_EMParameter class object reference that stores the new Custom Parameter
- id => SensorDht22_Label             : var ref to Json associative name and HTML element ID for the new Custom Paramerter you just defined in step 1
- placeholder => "DHT-22 Sensor"      : HTML input placeholder and/or label element text the user sees in the configuration interface for this Custom Parameter
- defaultValue => "T"                 : variable for storing the value of your Custom Parameter in the file system or default value when no data is entered ("T" means `true`)
- length  => 2                        : max allowed length you want for this Custom Parameter to have
- custom => customhtml                : custom HTML code to add element type, e.g. `checkbox`, and `checked` when `sensorDht22 == true`
- labelPlacement => WFM_LABEL_AFTER   : to place label after
```

and customhtml Code is:

```cpp
char customhtml[24] = "type=\"checkbox\"";

if (sensorDht22)
{
  strcat(customhtml, " checked");
}
```

---

###  3. Add the variables to Config Portal (CP)

Adding those `ESP8266_EMParameter` objects created in Step 2 using the function `addParameter()` of object `ESP8266_W5500_Manager`

#### 3.1 addParameter() function Prototype:

```cpp
//adds a custom parameter
bool addParameter(ESP8266_EMParameter *p);
```

#### 3.2 Code to add variables to CP


Add parameter objects, previously created in Step 2, such as : `p_thingspeakApiKey`, `p_sensorDht22`, `p_pinSda` and `p_pinScl`

```cpp
//add all parameters here

ESP8266_W5500_manager.addParameter(&p_thingspeakApiKey);
ESP8266_W5500_manager.addParameter(&p_sensorDht22);
ESP8266_W5500_manager.addParameter(&p_pinSda);
ESP8266_W5500_manager.addParameter(&p_pinScl);
```

---

###  4. Save the variables configured in Config Portal (CP)

When the CP exits, we have to store the parameters' values that users input via CP to use later.

For ESP8266, that can be `EEPROM` or `SPIFFS`.

We can write directly to a **well-defined structure of our choice**, but the current example is using `JSON` to be portable but **much more complicated and not advised for new users**.


#### 4.1 Getting variables' data from CP

After users select `Save`, the CP `ESP8266_W5500_Manager` object will save the user input data into related `ESP8266_EMParameter` objects.

We can now retrieve the data, using `getValue()` function, for each `ESP8266_EMParameter` object. Then we can utilize the data for our purpose, such as `thingspeakApiKey` to log in, `sensorDht22` type to know how to handle the sensor, `pinSda` and `pinSda` to know which pins to use to communicate with the DHT sensor.


The code is as follows:

```cpp
// Getting posted form values and overriding local variables parameters
// Config file is written regardless the connection state
strcpy(thingspeakApiKey, p_thingspeakApiKey.getValue());
sensorDht22 = (strncmp(p_sensorDht22.getValue(), "T", 1) == 0);
pinSda = atoi(p_pinSda.getValue());
pinScl = atoi(p_pinScl.getValue());
```

We can also save to FS file to use later in next boot.

```cpp
// Writing JSON config file to flash for next boot
writeConfigFile();
```

---

### 5. Write to FS (SPIFFS, LittleFS, etc.) using JSON format

First, you have to familiarize yourself with `ArduinoJson` library, its functions, the `disruptive` differences between `ArduinoJson version 5.x.x-` and `v6.0.0+`. The best documentation can be found at [The best JSON library for embedded C++](https://arduinojson.org/).

This documentation will discuss only `ArduinoJson v6.x.x+` (`ARDUINOJSON_VERSION_MAJOR >= 6`)


Then have a look at the code snippet of `writeConfigFile()` function and the following step-by-step explanations.


```cpp
bool writeConfigFile()
{
  Serial.println("Saving config file");

#if (ARDUINOJSON_VERSION_MAJOR >= 6)
  DynamicJsonDocument json(1024);
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
#endif

  // JSONify local configuration parameters
  json[ThingSpeakAPI_Label] = thingspeakApiKey;
  json[SensorDht22_Label] = sensorDht22;
  json[PinSDA_Label] = pinSda;
  json[PinSCL_Label] = pinScl;

  // Open file for writing
  File f = FileFS.open(CONFIG_FILE, "w");

  if (!f)
  {
    Serial.println("Failed to open config file for writing");
    return false;
  }

#if (ARDUINOJSON_VERSION_MAJOR >= 6)
  serializeJsonPretty(json, Serial);
  // Write data to file and close it
  serializeJson(json, f);
#else
  json.prettyPrintTo(Serial);
  // Write data to file and close it
  json.printTo(f);
#endif

  f.close();

  Serial.println("\nConfig file was successfully saved");
  return true;
}
```

#### 5.1 Create a DynamicJsonDocument Object

We'll create an object with size 1024 bytes, enough to hold our data:

```cpp
DynamicJsonDocument json(1024);
```

#### 5.2 Fill the DynamicJsonDocument Object with data got from Config Portal

Then `JSONify` all local parameters we've just received from CP and wish to store into FS by using the function prototype:

```cpp
json[Unique_Label] = Value_For_Unique_Label;
```

as follows:

```cpp
// JSONify local configuration parameters
json[ThingSpeakAPI_Label] = thingspeakApiKey;
json[SensorDht22_Label]   = sensorDht22;
json[PinSDA_Label]        = pinSda;
json[PinSCL_Label]        = pinScl;
```


#### 5.3 Open file to write the Jsonified data


This is the `CONFIG_FILE` file name we already declared at the beginning of the sketch (for ESP8266):

```cpp
#include <SPIFFS.h>
FS* filesystem =      &SPIFFS;
#define FileFS        SPIFFS
    
const char* CONFIG_FILE = "/ConfigSW.json";
```

Now just open the file for writing, and abort if open-for-writing error:


```cpp
// Open file for writing
File f = FileFS.open(CONFIG_FILE, "w");

if (!f)
{
  Serial.println("Failed to open config file for writing");
  return false;
}
```


#### 5.4 Write the Jsonified data to CONFIG_FILE

As simple as this single command to write the whole `json` object we declared then filled with data in steps 5.1 and 5.2

```cpp
// Write data to file and close it
serializeJson(json, f);
```

#### 5.5 Close CONFIG_FILE to flush and save the data

Soooo simple !!! Now everybody can do it.

```cpp
f.close();
```


But **HOWTO use the saved data in the next startup** ???? That's in next step 6.


### 6. Read from FS using JSON format


Now, you have familiarized yourself with ArduinoJson library, its functions. We'll discuss HOWTO read data from the `CONFIG_FILE` in Jsonified format, then HOWTO parse the to use.

The documentation will discuss only `ArduinoJson v6.x.x+` (`ARDUINOJSON_VERSION_MAJOR >= 6`)


First, have a look at the code snippet of `readConfigFile()` function.


```cpp
bool readConfigFile()
{
  // this opens the config file in read-mode
  File f = FileFS.open(CONFIG_FILE, "r");

  if (!f)
  {
    Serial.println("Configuration file not found");
    return false;
  }
  else
  {
    // we could open the file
    size_t size = f.size();
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size + 1]);

    // Read and store file contents in buf
    f.readBytes(buf.get(), size);
    // Closing file
    f.close();
    // Using dynamic JSON buffer which is not the recommended memory model, but anyway
    // See https://github.com/bblanchon/ArduinoJson/wiki/Memory%20model

#if (ARDUINOJSON_VERSION_MAJOR >= 6)
    DynamicJsonDocument json(1024);
    auto deserializeError = deserializeJson(json, buf.get());
    if ( deserializeError )
    {
      Serial.println("JSON parseObject() failed");
      return false;
    }
    serializeJson(json, Serial);
#else
    DynamicJsonBuffer jsonBuffer;
    // Parse JSON string
    JsonObject& json = jsonBuffer.parseObject(buf.get());
    // Test if parsing succeeds.
    if (!json.success())
    {
      Serial.println("JSON parseObject() failed");
      return false;
    }
    json.printTo(Serial);
#endif

    // Parse all config file parameters, override
    // local config variables with parsed values
    if (json.containsKey(ThingSpeakAPI_Label))
    {
      strcpy(thingspeakApiKey, json[ThingSpeakAPI_Label]);
    }

    if (json.containsKey(SensorDht22_Label))
    {
      sensorDht22 = json[SensorDht22_Label];
    }

    if (json.containsKey(PinSDA_Label))
    {
      pinSda = json[PinSDA_Label];
    }

    if (json.containsKey(PinSCL_Label))
    {
      pinScl = json[PinSCL_Label];
    }
  }
  Serial.println("\nConfig file was successfully parsed");
  return true;
}

```

and the following step-by-step explanations. 
 
### 6.1 Open CONFIG_FILE to read

As simple as this

```cpp
// this opens the config file in read-mode
File f = FileFS.open(CONFIG_FILE, "r");
```

We'll inform and abort if the `CONFIG_FILE` can't be opened (file not found, can't be opened, etc.)

```cpp
if (!f)
{
  Serial.println("Configuration file not found");
  return false;
}
```

### 6.2 Open CONFIG_FILE to read

Now we have to determine the file size to create a buffer large enough to store the to-be-read data

```cpp
// we could open the file
size_t size = f.size();
// Allocate a buffer to store contents of the file.
std::unique_ptr<char[]> buf(new char[size + 1]);
```

**Remember always add 1 to the buffer length to store the terminating `0`.**


Then just read the file into the buffer, and close the file to be safe

```cpp
// Read and store file contents in buf
f.readBytes(buf.get(), size);
// Closing file
f.close();
```

### 6.3 Populate the just-read Jsonified data into the DynamicJsonDocument json object

We again use the same `DynamicJsonDocument json` object to store the data we've just read from `CONFIG_FILE`.

Why the same complicated `DynamicJsonDocument json` object ?? Because in steps 5, we did store `Jsonified data` using the same `DynamicJsonDocument json` object. It's much easier we now use it again to facilitate the parsing of `Jsonified data` back to the data we can use easily.


We first create the object with enough size

```cpp
DynamicJsonDocument json(1024);
```

then populate it with data from buffer we read from `CONFIG_FILE` in step 6.2, pre-parse and check for error. All is done just by one command `deserializeJson()`

```cpp
auto deserializeError = deserializeJson(json, buf.get());
```

Abort if there is any data error in the process of writing, storing, reading back. If OK, just nicely print out to the Debug Terminal

```cpp
if ( deserializeError )
{
  Serial.println("JSON parseObject() failed");
  return false;
}

serializeJson(json, Serial);
```

### 6.4 Parse the Jsonified data from the DynamicJsonDocument json object to store into corresponding parameters


This is as simple as in the step 5.2, but in reverse direction.

To be sure there is good corresponding data, not garbage, for each variable, we have to perform **sanity checks** by 
verifying the `DynamicJsonDocument json object` still contains the correct keys we passed to it when we wrote into `CONFIG_FILE`. 

For example:

```cpp
if (json.containsKey(ThingSpeakAPI_Label))
```

Then proceed to get every parameter we know we stored there from last CP `Save`.


```cpp
// Parse all config file parameters, override
// local config variables with parsed values
if (json.containsKey(ThingSpeakAPI_Label))
{
  strcpy(thingspeakApiKey, json[ThingSpeakAPI_Label]);
}

if (json.containsKey(SensorDht22_Label))
{
  sensorDht22 = json[SensorDht22_Label];
}

if (json.containsKey(PinSDA_Label))
{
  pinSda = json[PinSDA_Label];
}

if (json.containsKey(PinSCL_Label))
{
  pinScl = json[PinSCL_Label];
}
```


### 6.5 Then what to do now

**Just use those parameters for whatever purpose you designed them for in step 1:**


```cpp
The application will use DHT sensor (either DHT11 or DHT22) and need to connect to ThingSpeak with unique user's API Key. The DHT sensor is connected to the ESP boards using SDA/SCL pins which also need to be configurable.
```

---
---

## So, how it works?

In `ConfigPortal Mode`, it starts an access point @ the current Static or DHCP IP.

 Connect to it by going to, e.g. `http://192.168.2.186`, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Main.png">
</p>

Select `Information` to enter the Info page where the board info will be shown (long page)

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Info.png">
</p>


Select `Configuration` to enter this page where you can modify its Credentials

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Configuration_Standard.png">
</p>

Enter your credentials, then click **Save**. The Credentials will be saved and the board continues, or reboots if necessary, to connect to the selected Static IP or DHCP.

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Saved.png">
</p>


If you're already satisfied with the current settings and don't want to change anything, just select **Exit Portal** from the `Main` page to continue or reboot the board and connect using the previously-stored Credentials.

---
---

## Documentation

#### Password protect the configuration Access Point

You can password protect the ConfigPortal AP. Check [ESP8266_FSWebServer](examples/ESP8266_FSWebServer) example

---

#### Callbacks

##### Save settings

This gets called when custom parameters have been set **AND** a connection has been established. Use it to set a flag, so when all the configuration finishes, you can save the extra parameters somewhere.

See [ConfigOnSwitchFS Example](examples/ConfigOnSwitchFS).

```cpp
ESP8266_W5500_manager.setSaveConfigCallback(saveConfigCallback);
```
saveConfigCallback declaration and example

```cpp
//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () 
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
```

---

#### ConfigPortal Timeout

If you need to set a timeout so the `ESP8266` doesn't hang waiting to be configured for ever. 

```cpp
ESP8266_W5500_manager.setConfigPortalTimeout(120);
```

which will wait 2 minutes (120 seconds). When the time passes, the `startConfigPortal()` function will return and continue the sketch, 
unless you're accessing the `Config Portal`. In this case, the `startConfigPortal()` function will stay until you save config data or exit 
the `Config Portal`.

---

#### On Demand ConfigPortal

Example usage

```cpp
void loop()
{
  // is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || (digitalRead(TRIGGER_PIN2) == LOW))
  {
    Serial.println(F("\nConfiguration portal requested."));
    digitalWrite(LED_BUILTIN, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.

    //Local intialization. Once its business is done, there is no need to keep it around
    // Use this to default DHCP hostname to ESP8266-XXXXXX
    //ESP8266_W5500_Manager ESP8266_W5500_manager;
    // Use this to personalize DHCP hostname (RFC952 conformed)
    ESP8266_W5500_Manager ESP8266_W5500_manager("ConfigOnSwitch");

#if !USE_DHCP_IP
#if USE_CONFIGURABLE_DNS
    // Set static IP, Gateway, Subnetmask, DNS1 and DNS2
    ESP8266_W5500_manager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
#else
    // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
    ESP8266_W5500_manager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
#endif
#endif

#if USING_CORS_FEATURE
    ESP8266_W5500_manager.setCORSHeader("Your Access-Control-Allow-Origin");
#endif

    //Check if there is stored credentials.
    //If not found, device will remain in configuration mode until switched off via webserver.
    Serial.println(F("Opening configuration portal. "));

    if (loadConfigData())
    {
      //If no access point name has been previously entered disable timeout.
      ESP8266_W5500_manager.setConfigPortalTimeout(120);

      Serial.println(F("Got stored Credentials. Timeout 120s for Config Portal"));
    }
    else
    {
      // Enter CP only if no stored SSID on flash and file
      ESP8266_W5500_manager.setConfigPortalTimeout(0);
      Serial.println(F("Open Config Portal without Timeout: No stored Credentials."));
      initialConfig = true;
    }

    //Starts an access point
    //and goes into a blocking loop awaiting configuration
    if (!ESP8266_W5500_manager.startConfigPortal())
      Serial.println(F("Not connected to ETH network but continuing anyway."));
    else
    {
      Serial.println(F("ETH network connected...yeey :)"));
      Serial.print(F("Local IP: "));
      Serial.println(eth.localIP());
    }

#if USE_ESP_ETH_MANAGER_NTP
    String tempTZ = ESP8266_W5500_manager.getTimezoneName();

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

    digitalWrite(LED_BUILTIN, LED_OFF); // Turn led off as we are not in configuration mode.
  }

  // put your main code here, to run repeatedly
  check_status();
}
```

See  [ConfigOnSwitch](examples/ConfigOnSwitch) example for a more complex version.

---
---

#### Custom Parameters

Many applications need configuration parameters like `MQTT host and port`, [Blynk](http://www.blynk.cc) or [emoncms](http://emoncms.org) tokens, etc. While it is possible to use [`ESP8266_W5500_Manager`](https://github.com/khoih-prog/ESP8266_W5500_Manager) to collect additional parameters, it is better to read these parameters from a web service once [`ESP8266_W5500_Manager`](https://github.com/khoih-prog/ESP8266_W5500_Manager) has been used to connect to the Internet.

To capture other parameters with [`ESP8266_W5500_Manager`](https://github.com/khoih-prog/ESP8266_W5500_Manager) is a little bit more complicated than all the other features. This requires adding custom HTML to your form. 

If you want to do it with [`ESP8266_W5500_Manager`](https://github.com/khoih-prog/ESP8266_W5500_Manager) see the example [ConfigOnSwitchFS](examples/ConfigOnSwitchFS)

---

#### Custom IP Configuration

You can set a custom IP for STA (station mode, client mode, normal project state)


##### Custom Station (client) Static IP Configuration

This will use the specified IP configuration instead of using DHCP in station mode.

```cpp
ESP8266_W5500_manager.setSTAStaticIPConfig(IPAddress(192,168,2,186), IPAddress(192,168,2,1), IPAddress(255,255,255,0));
```

---

#### Custom HTML, CSS, Javascript

There are various ways in which you can inject custom HTML, CSS or Javascript into the ConfigPortal.

The options are:

- **inject custom head element**

You can use this to any html bit to the head of the ConfigPortal. If you add a `<style>` element, keep in mind it overwrites the included `css`, not replaces.

```cpp
ESP8266_W5500_manager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>");
```

- **inject a custom bit of html in the configuration form**

```cpp
ESP8266_EMParameter custom_text("<p>This is just a text paragraph</p>");
ESP8266_W5500_manager.addParameter(&custom_text);
```

- **inject a custom bit of html in a configuration form element**

Just add the bit you want added as the last parameter to the custom parameter constructor.

```cpp
ESP8266_EMParameter custom_mqtt_server("server", "mqtt server", "iot.eclipse", 40, " readonly");
```

---
---

#### How to connect W5x00 to ESP8266

You can change the `CS/SS` pin to another one. Default is `GPIO16`

Connecting `CS/SS` to `TX0/GPIO15` interferes with uploading firmware to ESP8266. If absolutely necessary to use `TX0/GPIO15`, remove the wire to `TX0/GPIO15` before uploading firmware. Then reconnect after done uploading.

```cpp
// Using GPIO4, GPIO16, or GPIO5
#define CSPIN             16
```

---


<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/W5500.png">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/W5500_small.png">
</p>


|W5x00|<--->|ESP8266|
|:-:|:-:|:-:|
|MOSI|<--->|GPIO13|
|MISO|<--->|GPIO12|
|SCK|<--->|GPIO14|
|SS|<--->|GPIO16|
|GND|<--->|GND|
|3.3V|<--->|3.3V|

---
---

### Examples

 1. [ConfigOnSwitch](examples/ConfigOnSwitch)
 2. [ConfigOnSwitchFS](examples/ConfigOnSwitchFS)
 3. [ConfigOnDoubleReset_TZ](examples/ConfigOnDoubleReset_TZ)           (now support ArduinoJson 6.0.0+ as well as 5.13.5-) 
 4. [ConfigOnDoubleReset](examples/ConfigOnDoubleReset)                 (now support ArduinoJson 6.0.0+ as well as 5.13.5-)
 5. [ConfigPortalParamsOnSwitch](examples/ConfigPortalParamsOnSwitch)   (now support ArduinoJson 6.0.0+ as well as 5.13.5-)
 6. [ESP8266_FSWebServer](examples/ESP8266_FSWebServer)
 7. [ESP8266_FSWebServer_DRD](examples/ESP8266_FSWebServer_DRD)

---
---

### Example [ConfigOnSwitch](examples/ConfigOnSwitch)


https://github.com/khoih-prog/ESP8266_W5500_Manager/blob/42a01dfa832cd7bc406b3bb3d571e0b04cc98bbf/examples/ConfigOnSwitch/ConfigOnSwitch.ino#L27-L786

---
---

### Debug Terminal Output Samples

#### 1. ConfigOnDoubleReset_TZ using LittleFS on ESP8266_DEV with ESP8266_W5500

##### 1.1 DRD => Config Portal

This is terminal debug output when running [ConfigOnDoubleReset](examples/ConfigOnDoubleReset) on  **ESP8266_W5500**. `Config Portal` was requested by DRD to input and save Credentials, such as Static IP address.

```
Starting ConfigOnDoubleReset_TZ using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
ESP_DoubleResetDetector v1.3.2
[EM] RFC925 Hostname = ConfigOnDoubleReset_TZ
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
Got stored Credentials. Timeout 120s for Config Portal
[EM] Current TZ_Name = America/New_York , TZ =  EST5EDT,M3.2.0,M11.1.0
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.186
LittleFS Flag read = 0xD0D01234
doubleResetDetected
Saving config file...
Saving config file OK
Open Config Portal without Timeout: Double Reset Detected
Starting configuration portal @ 192.168.2.186
_domainName = *
_resolvedIP = 192.168.2.186
_port = 53
[EM] _configPortalStart millis() = 354
[EM] Config Portal IP address = 192.168.2.186
[EM] HTTP server started
[EM] startConfigPortal : Enter loop
[EM] handleRoot
[EM] captivePortal: hostHeader =  192.168.2.186
[EM] Handle ETH
[EM] Static IP = 192.168.2.186
[EM] Sent config page
[EM] ETH save
[EM] TZ name = America/New_York
[EM] New Static IP = 192.168.2.188
[EM] New Static Gateway = 192.168.2.1
[EM] New Static Netmask = 255.255.255.0
[EM] New Static DNS1 = 192.168.2.1
[EM] New Static DNS2 = 8.8.8.8
[EM] Sent eth save page
[EM] stopConfigPortal
ETH network connected...yeey :)
[EM] Saving current TZ_Name = America/New_York , TZ =  EST5EDT,M3.2.0,M11.1.0
[EM] getSTAStaticIPConfig
[EM] SaveCfgFile 
[EM] stationIP = 192.168.2.188 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
[EM] OK
Current IP = 192.168.2.186. Reset to take new IP = 192.168.2.188
ets Jan  8 2013,rst cause:2, boot mode:(3,6)
```

##### 1.2. Get new Static IP after reset

```
Starting ConfigOnDoubleReset_TZ using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
ESP_DoubleResetDetector v1.3.2
[EM] RFC925 Hostname = ConfigOnDoubleReset_TZ
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.188 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
Got stored Credentials. Timeout 120s for Config Portal
[EM] Current TZ_Name = America/New_York , TZ =  EST5EDT,M3.2.0,M11.1.0
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.188
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
After waiting 0.00 secs more in setup(), connection result is connected. Local IP: 192.168.2.188
[EM] freeing allocated params!
Stop doubleResetDetecting
Saving config file...
Saving config file OK
Local Date/Time: Sun Dec 11 18:23:34 2022
Local Date/Time: Sun Dec 11 18:24:34 2022
Local Date/Time: Sun Dec 11 18:25:34 2022
Local Date/Time: Sun Dec 11 18:26:34 2022
Local Date/Time: Sun Dec 11 18:27:34 2022
Local Date/Time: Sun Dec 11 18:28:34 2022
```

---

#### 2. ConfigOnSwichFS using LittleFS on ESP8266_DEV with ESP8266_W5500

This is terminal debug output when running [ConfigOnSwichFS](examples/ConfigOnSwichFS) on  **ESP8266_W5500**. `Config Portal` was requested to input and save Credentials.


```
Starting ConfigOnSwichFS using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
{"thingspeakApiKey":"","SensorDHT22":true,"PinSda":4,"PinScl":5}
Config file was successfully parsed
[EM] RFC925 Hostname = ConfigOnSwitchFS
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
Got stored Credentials. Timeout 120s for Config Portal
Current Timezone is not set. Enter Config Portal to set.
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.186
After waiting 0.00 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
[EM] freeing allocated params!

Configuration portal requested.
[EM] RFC925 Hostname = ConfigOnSwitchFS
Opening configuration portal. 
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
Got stored Credentials. Timeout 120s for Config Portal
[EM] Adding parameter thingspeakApiKey
[EM] Adding parameter SensorDHT22
[EM] Adding parameter PinSda
[EM] Adding parameter PinScl
[EM] setSTAStaticIPConfig for USE_CONFIGURABLE_DNS
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] _configPortalStart millis() = 26788
[EM] Config Portal IP address = 192.168.2.186
[EM] HTTP server started
[EM] startConfigPortal : Enter loop
[EM] handleRoot
[EM] request host IP = 192.168.2.186
[EM] Info
[EM] Info page sent
[EM] handleRoot
[EM] request host IP = 192.168.2.186
[EM] Handle ETH
[EM] Static IP = 192.168.2.186
[EM] Sent config page
[EM] ETH save
[EM] TZ = America/Toronto
[EM] Parameter and value : thingspeakApiKey 
[EM] Parameter and value : SensorDHT22 T
[EM] Parameter and value : PinSda 4
[EM] Parameter and value : PinScl 5
[EM] New Static IP = 192.168.2.186
[EM] New Static Gateway = 192.168.2.1
[EM] New Static Netmask = 255.255.255.0
[EM] New Static DNS1 = 192.168.2.1
[EM] New Static DNS2 = 8.8.8.8
[EM] Sent eth save page
[EM] stopConfigPortal
ETH network connected...yeey :)
Local IP: 192.168.2.186
[EM] Saving current TZ_Name = America/Toronto , TZ =  EST5EDT,M3.2.0,M11.1.0
[EM] getSTAStaticIPConfig
[EM] SaveCfgFile 
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
[EM] OK
Saving config file
{
  "thingspeakApiKey": "",
  "SensorDHT22": true,
  "PinSda": 4,
  "PinScl": 5
}
Config file was successfully saved
Current IP = 192.168.2.186. Reset to take new IP = 192.168.2.186
ets Jan  8 2013,rst cause:2, boot mode:(3,6)

...

Starting ConfigOnSwichFS using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
{"thingspeakApiKey":"","SensorDHT22":true,"PinSda":4,"PinScl":5}
Config file was successfully parsed
[EM] RFC925 Hostname = ConfigOnSwitchFS
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
Got stored Credentials. Timeout 120s for Config Portal
[EM] Current TZ_Name = America/Toronto , TZ =  EST5EDT,M3.2.0,M11.1.0
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.186
After waiting 0.00 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
[EM] freeing allocated params!
Local Date/Time: Fri Dec  9 23:05:29 2022
Local Date/Time: Fri Dec  9 23:06:29 2022
```

---

#### 3. ESP8266_FSWebServer_DRD using LittleFS on ESP8266_DEV with ESP8266_W5500

This is terminal debug output when running [ESP8266_FSWebServer_DRD](examples/ESP8266_FSWebServer_DRD) on **ESP8266_W5500**.

The terminal debug output demonstrate the upload the contents of the data folder to ESP8266 LittleFS using the following command

```
for file in `\ls -A1`; do curl -F "file=@$PWD/$file" 192.168.2.186/edit; done
```


```cpp
Starting ESP_FSWebServer_DRD using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
ESP_DoubleResetDetector v1.3.2
Opening / directory
FS File: PM2_5_Log.csv, size: 40B
FS File: drd.dat, size: 4B
FS File: eth_cred.dat, size: 142B
FS File: timezone.dat, size: 32B

[EM] RFC925 Hostname = ESP-FSWebServerDRD
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.186
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
After waiting 0.00 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
HTTP server started @ 192.168.2.186
===============================================================
Open http://192.168.2.186/edit.htm to see the file browser
Using username = admin and password = admin
===============================================================
[EM] freeing allocated params!
Stop doubleResetDetecting
Saving config file...
Saving config file OK
handleFileRead: /
handleFileRead: /edit.htm
handleFileRead: /edit.htm
handleFileRead: /
handleFileUpload Name: /CanadaFlag_1.png
handleFileUpload Size: 41214
handleFileUpload Name: /CanadaFlag_2.png
handleFileUpload Size: 8311
handleFileUpload Name: /CanadaFlag_3.jpg
handleFileUpload Size: 11156
handleFileUpload Name: /edit.htm.gz
handleFileUpload Size: 4116
handleFileUpload Name: /favicon.ico
handleFileUpload Size: 1150
handleFileUpload Name: /graphs.js.gz
handleFileUpload Size: 1971
handleFileUpload Name: /index.htm
handleFileUpload Size: 3721
handleFileRead: /
handleFileRead: /graphs.js
handleFileRead: /edit.htm
handleFileRead: /index.htm
handleFileList: /
handleFileRead: /CanadaFlag_1.png
```

---

Then after restart, the uploaded files are shown in `/` directory


```
Starting ESP_FSWebServer_DRD using LittleFS on ESP8266_NODEMCU_ESP12E with ESP8266_W5500 Ethernet
ESP8266_W5500_Manager v1.0.0
ESP_DoubleResetDetector v1.3.2
Opening / directory
FS File: CanadaFlag_1.png, size: 40.25KB
FS File: CanadaFlag_2.png, size: 8.12KB
FS File: CanadaFlag_3.jpg, size: 10.89KB
FS File: PM2_5_Log.csv, size: 40B
FS File: drd.dat, size: 4B
FS File: edit.htm.gz, size: 4.02KB
FS File: eth_cred.dat, size: 142B
FS File: favicon.ico, size: 1.12KB
FS File: graphs.js.gz, size: 1.92KB
FS File: index.htm, size: 3.63KB
FS File: timezone.dat, size: 32B

[EM] RFC925 Hostname = ESP-FSWebServerDRD
[EM] setSTAStaticIPConfig
[EM] Set CORS Header to :  Your Access-Control-Allow-Origin
[EM] LoadCfgFile 
[EM] OK
[EM] stationIP = 192.168.2.186 , gatewayIP = 192.168.2.1
[EM] netMask = 255.255.255.0
[EM] dns1IP = 192.168.2.1 , dns2IP = 8.8.8.8
[EM] Default SPI pinout:
[EM] MOSI: 13
[EM] MISO: 12
[EM] SCK: 14
[EM] CS: 16
[EM] =========================
Connecting to network : 
Ethernet Static IP address: 192.168.2.186
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
After waiting 0.00 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
HTTP server started @ 192.168.2.186
===============================================================
Open http://192.168.2.186/edit.htm to see the file browser
Using username = admin and password = admin
===============================================================
[EM] freeing allocated params!
```

---
---

### Debug

Debug is enabled by default on Serial. To disable, add before `startConfigPortal()`

```cpp
ESP8266_W5500_manager.setDebugOutput(false);
```

You can also change the debugging level from 0 to 4

```cpp
// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ESP8266_ETH_MGR_LOGLEVEL_    3
```
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP8266` core for Arduino.

Sometimes, the library will only work if you update the `ESP8266` core to the latest version because I am using some newly added function.

If you connect to the created configuration Access Point but the ConfigPortal does not show up, just open a browser and type in the IP of the web portal, by default `192.168.2.186`.

---

### Issues ###

Submit issues to: [ESP8266_W5500_Manager issues](https://github.com/khoih-prog/ESP8266_W5500_Manager/issues)

---
---


### Contributions and Thanks

 1. Based on and modified from [Tzapu](https://github.com/tzapu/WiFiManager), [KenTaylor's version]( https://github.com/kentaylor/WiFiManager), and [`Khoi Hoang's ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager).


<table>
  <tr>
    <td align="center"><a href="https://github.com/Tzapu"><img src="https://github.com/Tzapu.png" width="100px;" alt="Tzapu"/><br /><sub><b>⭐️ Tzapu</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kentaylor"><img src="https://github.com/kentaylor.png" width="100px;" alt="kentaylor"/><br /><sub><b>⭐️ Ken Taylor</b></sub></a><br /></td>
  </tr>
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP8266_W5500_Manager/blob/main/LICENSE)

---

## Copyright

Copyright 2022- Khoi Hoang


