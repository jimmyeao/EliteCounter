# EliteCounter
Elite stats counter, stats from EDSM displayed on a max7219 display
Utilises an ESP8266 (I use a Wemos D1 Mini)
Connect as follows:
  D1      max7219
  
  3.3v  -> VCC
  
  G     -> Gnd
  
  D6    -> CLK
  
  D7    -> CS
  
  D8    -> DIN
  
  
  Edit the ino file to enter your WIFI and EDSM details
  
  Requires the following libraries
  
    ESP8266WiFi
    
    WiFiClientSecure
    
    ArduinoJson (Version 5.x)
    
  If you would lie a pause after each stat, change line the **#define DELAY 000 //the delay between changing stats** to **#define DELAY 500 //the delay between changing stats**
  To Come - 3d Printed case..
