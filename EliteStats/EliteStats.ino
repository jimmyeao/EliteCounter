#include <ESP8266WiFi.h>        // Include the Wi-Fi library

#include <WiFiClientSecure.h>

#include <ArduinoJson.h>

const char * host = "www.edsm.net";
//---------------------------------------------------------------------------------------------------------------------
//you need to change these!!
const char * EDSMAPI = "YOUR_EDSM_API_KEY";
const char * CMDR = "YOUR_CMDR_NAME";

const char * ssid = "YOUR_SSID"; // The SSID (name) of the Wi-Fi network you want to connect to
const char * password = "YOUR_SSID_PASSWORD"; // The password of the Wi-Fi network
// comment out any stats you dont want!
#define ShowExplorer true
#define ShowCombat true
#define ShowTrade true
#define ShowSoldier true
#define ShowExobiologist true
#define ShowCQC true
#define ShowFederation true
#define ShowEmpire true
#define ShowProgress true //shows progress towards next rank
//---------------------------------------------------------------------------------------------------------------------
//Dont change anything below this line unless you know what you are doing ;)
//LED Maxtrix settings

#define scrollspeed 50 //the higher the number the slower the scroll speed
#define DELAY 000 //the delay between changing stats
#define LOOPS 15 //the number of times to loop before refreshing the data
#define NUM_MAX 4
#define ROTATE 90

#define DIN_PIN 15 // D8
#define CS_PIN 13 // D7
#define CLK_PIN 12 // D6
#include "fonts.h"

#include "max7219.h"


void loop() {
  // put your main code here, to run repeatedly:
  WiFiClientSecure client;
  client.setInsecure();

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 443)) {
    Serial.println("connected]");

    Serial.println("[Sending a request]");

    String cmd = String("GET /api-commander-v1/get-ranks?apikey=") + EDSMAPI + "&commanderName=" + CMDR + " HTTP/1.1\r\n" + "Host: " + host + "\r\nUser-Agent: ESP8266/1.1\r\nConnection: close\r\n\r\n";
    client.print(cmd);

    //change delay if you want a pause after everyscroll
    int repeatCounter = 10;
    while (!client.available() && repeatCounter--) {
      delay(50);
    }
    String line, buf = "";
    int startJson = 0;

    while (client.connected() && client.available()) {
      line = client.readStringUntil('\n');
      if (line[0] == '{') startJson = 1;
      if (startJson) {
        for (int i = 0; i < line.length(); i++)
          if (line[i] == '[' || line[i] == ']') line[i] = ' ';
        buf += line + "\n";
      }
    }

    client.stop();

    DynamicJsonBuffer jsonBuf;
    JsonObject & root = jsonBuf.parseObject(buf);
    if (!root.success()) {
      Serial.println("parseObject() failed");
      delay(10);
    }
    Serial.println(buf);
    for (int i = 0; i < LOOPS; i++) {

      if (ShowCombat) {
        String combbat = root["ranksVerbose"]["Combat"];
        if (ShowProgress) {
          int combprog = root["progress"]["Combat"];

          String V = "        Combat        " + combbat + " " + String(combprog) + "%";
          Serial.println(V);
          printStringWithShift(V.c_str(), scrollspeed);
        } else {
          String V = "        Combat        " + combbat;
          Serial.println(V);
          printStringWithShift(V.c_str(), scrollspeed);
        }

        delay(DELAY);
      }

      if (ShowTrade) {
        String Trade = root["ranksVerbose"]["Trade"];
        if (ShowProgress) {
          int tradeprog = root["progress"]["Trade"];

          String Vids = "        Trade        " + Trade + " " + String(tradeprog) + "%";
          Serial.println(Vids);
          printStringWithShift(Vids.c_str(), scrollspeed);
        } else {
          String Vids = "        Trade        " + Trade;
          Serial.println(Vids);
          printStringWithShift(Vids.c_str(), scrollspeed);
        }

        delay(DELAY);
      }

      if (ShowExplorer) {
        String Explore = root["ranksVerbose"]["Explore"];
        if (ShowProgress) {
          int expprog = root["progress"]["Explore"];

          String ranksVerbose = "        Explorer        " + Explore + " " + String(expprog) + "%";
          Serial.println(ranksVerbose);
          printStringWithShift(ranksVerbose.c_str(), scrollspeed);
        } else {
          String ranksVerbose = "        Explorer        " + Explore;
          Serial.println(ranksVerbose);
          printStringWithShift(ranksVerbose.c_str(), scrollspeed);
        }
        delay(DELAY);
      }
      if (ShowSoldier) {
        String ShowSoldier1 = root["ranksVerbose"]["Soldier"];
        if (ShowProgress) {
          int solprog = root["progress"]["Soldier"];

          String Soldier = "        Soldier        " + ShowSoldier1 + " " + String(solprog) + "%";
          Serial.println(Soldier);
          printStringWithShift(Soldier.c_str(), scrollspeed);
        } else {
          String Soldier = "        Soldier        " + ShowSoldier1;
          Serial.println(Soldier);
          printStringWithShift(Soldier.c_str(), scrollspeed);
        }

        delay(DELAY);
      }
      if (ShowExobiologist) {
        String ShowExobiologist1 = root["ranksVerbose"]["Exobiologist"];
        if (ShowProgress) {
          int exoprog = root["progress"]["Exobiologist"];

          String Exobiologist = "        Exobiologist        " + ShowExobiologist1 + " " + String(exoprog) + "%";
          Serial.println(Exobiologist);
          printStringWithShift(Exobiologist.c_str(), scrollspeed);
        } else {
          String Exobiologist = "        Exobiologist        " + ShowExobiologist1;
          Serial.println(Exobiologist);
          printStringWithShift(Exobiologist.c_str(), scrollspeed);
        }
        delay(DELAY);
      }
      if (ShowCQC) {
        String ShowCQC1 = root["ranksVerbose"]["CQC"];
        if (ShowProgress) {
          int cqcrog = root["progress"]["CQC"];

          String CQC = "        CQC        " + ShowCQC1 + " " + String(cqcrog) + "%";
          Serial.println(CQC);
          printStringWithShift(CQC.c_str(), scrollspeed);
        } else {
          String CQC = "        CQC        " + ShowCQC1;
          Serial.println(CQC);
          printStringWithShift(CQC.c_str(), scrollspeed);
        }
        delay(DELAY);
      }
      if (ShowFederation) {
        String ShowFederation1 = root["ranksVerbose"]["Federation"];
        if (ShowProgress) {
          int fedprog = root["progress"]["Federation"];

          String Federation = "        Federation        " + ShowFederation1 + " " + String(fedprog) + "%";
          Serial.println(Federation);
          printStringWithShift(Federation.c_str(), scrollspeed);
        } else {
          String Federation = "        Federation        " + ShowFederation1;
          Serial.println(Federation);
          printStringWithShift(Federation.c_str(), scrollspeed);
        }
        delay(DELAY);
      }
      if (ShowEmpire) {
        String ShowEmpire1 = root["ranksVerbose"]["Empire"];
        if (ShowProgress) {
          int empprog = root["progress"]["Empire"];

          String empire = "        Empire        " + ShowEmpire1 + " " + String(empprog) + "%";
          Serial.println(empire);
          printStringWithShift(empire.c_str(), scrollspeed);
        } else {
          String empire = "        Empire        " + ShowEmpire1;
          Serial.println(ShowEmpire1);
          printStringWithShift(empire.c_str(), scrollspeed);
        }

        delay(DELAY);
      }
    }

    Serial.println("\n[Disconnected]");
  } else {
    Serial.println("connection failed!]");
    client.stop();
  }

}

int showChar(char ch,
  const uint8_t * data) {
  int len = pgm_read_byte(data);
  int i, w = pgm_read_byte(data + 1 + ch * len);
  for (i = 0; i < w; i++)
    scr[NUM_MAX * 8 + i] = pgm_read_byte(data + 1 + ch * len + 1 + i);
  scr[NUM_MAX * 8 + i] = 0;
  return w;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN, 1);
  sendCmdAll(CMD_INTENSITY, 2);
  printStringWithShift("  Elite  ", 50);
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password); // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

}
// =======================================================================

void printStringWithShift(const char * s, int shiftDelay) {
  while ( * s) {
    printCharWithShift( * s++, shiftDelay);
  }
}

// =======================================================================
// =======================================================================

void printCharWithShift(unsigned char c, int shiftDelay) {
  c = convertPolish(c);
  if (c < ' ' || c > MAX_CHAR) return;
  c -= 32;
  int w = showChar(c, font);
  for (int i = 0; i < w + 1; i++) {
    delay(shiftDelay);
    scrollLeft();
    refreshAll();
  }
}

// =======================================================================
int dualChar = 0;
unsigned char convertPolish(unsigned char _c) {
  unsigned char c = _c;
  if (c == 196 || c == 197 || c == 195) {
    dualChar = c;
    return 0;
  }
  if (dualChar) {
    switch (_c) {
    case 133:
      c = 1 + '~';
      break; // '??'
    case 135:
      c = 2 + '~';
      break; // '??'
    case 153:
      c = 3 + '~';
      break; // '??'
    case 130:
      c = 4 + '~';
      break; // '??'
    case 132:
      c = dualChar == 197 ? 5 + '~' : 10 + '~';
      break; // '??' and '??'
    case 179:
      c = 6 + '~';
      break; // '??'
    case 155:
      c = 7 + '~';
      break; // '??'
    case 186:
      c = 8 + '~';
      break; // '??'
    case 188:
      c = 9 + '~';
      break; // '??'
      //case 132: c = 10+'~'; break; // '??'
    case 134:
      c = 11 + '~';
      break; // '??'
    case 152:
      c = 12 + '~';
      break; // '??'
    case 129:
      c = 13 + '~';
      break; // '??'
    case 131:
      c = 14 + '~';
      break; // '??'
    case 147:
      c = 15 + '~';
      break; // '??'
    case 154:
      c = 16 + '~';
      break; // '??'
    case 185:
      c = 17 + '~';
      break; // '??'
    case 187:
      c = 18 + '~';
      break; // '??'
    default:
      break;
    }
    dualChar = 0;
    return c;
  }
  switch (_c) {
  case 185:
    c = 1 + '~';
    break;
  case 230:
    c = 2 + '~';
    break;
  case 234:
    c = 3 + '~';
    break;
  case 179:
    c = 4 + '~';
    break;
  case 241:
    c = 5 + '~';
    break;
  case 243:
    c = 6 + '~';
    break;
  case 156:
    c = 7 + '~';
    break;
  case 159:
    c = 8 + '~';
    break;
  case 191:
    c = 9 + '~';
    break;
  case 165:
    c = 10 + '~';
    break;
  case 198:
    c = 11 + '~';
    break;
  case 202:
    c = 12 + '~';
    break;
  case 163:
    c = 13 + '~';
    break;
  case 209:
    c = 14 + '~';
    break;
  case 211:
    c = 15 + '~';
    break;
  case 140:
    c = 16 + '~';
    break;
  case 143:
    c = 17 + '~';
    break;
  case 175:
    c = 18 + '~';
    break;
  default:
    break;
  }
  return c;
}
// =======================================================================

