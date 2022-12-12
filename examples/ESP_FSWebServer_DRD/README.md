# ESP_FSWebServer_DRD Example

Compare this efficient ESP_FSWebServer_DRD example with the so complicated twin [ESP_FSWebServer_DRD](https://github.com/khoih-prog/ESP_WiFiManager/tree/master/examples/ESP_FSWebServer_DRD) to appreciate the powerful AsynWebServer this [ESP8266_W5500_Manager Library](https://github.com/khoih-prog/ESP8266_W5500_Manager) is relying on.

## First, how Config Portal works?

Connect to Config Portal @ the localIP address, e.g. `192.168.2.186`


You'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Main.png">
</p>

Select `Information` to enter the Info page where the board info will be shown (long page)

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Info.png">
</p>


Select `Configuration` to enter this page where you can select an AP and specify its WiFi Credentials

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/Images/Configuration_Standard.png">
</p>

Enter your credentials, then click `Save`.

---

## How to use this ESP_FSWebServer_DRD example?

This shows you how to use this example in Ubuntu (but you can use similar commands in other OSes)

### Download Data files

1. For example, you already downloaded data files from [ESP_FSWebServer_DRD data](https://github.com/khoih-prog/ESP8266_W5500_Manager/tree/main/examples/ESP_FSWebServer_DRD/data) to a local folder, for example:

```
~/Arduino/libraries/ESP8266_W5500_Manager-main/examples/ESP_FSWebServer_DRD/data
```

### HOWTO Upload files to ESP8266 (LittleFS or SPIFFS)

Use one of these methods (preferable first)

1. Go to http://esp8266fs.local/edit.htm, then "Choose file" -> "Upload"
2. or Upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
3. or upload the contents of a folder by running the following commands: 

```
Ubuntu$ cd ~/Arduino/libraries/ESP8266_W5500_Manager-main/examples/ESP_FSWebServer_DRD/data
Ubuntu$ for file in \`\ls -A1\`; do curl -F "file=@$PWD/$file" http://esp8266fs.local/edit; done
```

---

### Demonstrating pictures

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/examples/ESP_FSWebServer_DRD/pics/esp8266fs.local.png">
</p>

4. Edit / Delete / Download any file in the the folder by going to http://esp8266fs.local/edit.htm

<p align="center">
    <img src="https://github.com/khoih-prog/ESP8266_W5500_Manager/raw/main/examples/ESP_FSWebServer_DRD/pics/esp8266fs.local_edit.png">
</p>


