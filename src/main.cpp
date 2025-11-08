#include <vector>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <U8g2lib.h>

#include "config/secret.hh"
#include "objects/GroupBlock.hh"
#include "objects/BasicBlock.hh"
#include "frontend/Renderer.hh"
#include "enums/BlockTypeEnum.hh"
#include "objects/ControllBlocks/OnOffBlock.hh"
#include "objects/SensorBlocks/TextSensorBlock.hh"
#include "sensors/Sensor.hh"
#include "sensors/MPU6050Sensor.hh"

AsyncWebServer server(80);

std::vector<GroupBlock*> Groups;
std::vector<Sensor*> Sensors;

U8G2_SSD1306_96X40_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

Renderer *rd;

void setup() {
  u8g2.begin();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  delay(10);
  rd=new Renderer();

  Groups.push_back(new GroupBlock(0,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, {16,13},"Pozition"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 1, {14},"Sto"));
  //Groups.back()->blocks.push_back(new OnOffBlock(0, 2, 1,"CABINLED"));
  Groups.push_back(new GroupBlock(1,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(1, 0, {12},"Cabin"));
  //Groups.back()->blocks.push_back(new OnOffBlock(1, 1, 13,"Red"));
  Groups.push_back(new GroupBlock(2,status));
  Sensor* movementSensor=new MPU6050Sensor("Movement",1000,33,32);
  Sensors.push_back(movementSensor);
  Groups.back()->blocks.push_back(new TextSensorBlock(2, 0, {}, "Movement",movementSensor));

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request) 
  {
    if (request->hasParam("name") && request->hasParam("state")) {
      String name  = request->getParam("name")->value();
      String state = request->getParam("state")->value();

      for (auto group : Groups) {
        for (auto block : group->blocks) {
          OnOffBlock* onoff = static_cast<OnOffBlock*>(block);
          if (onoff && name.equalsIgnoreCase(onoff->name)) {
            if (state.equalsIgnoreCase("ON")) {
              onoff->setPin(true);
            } else if (state.equalsIgnoreCase("OFF")) {
              onoff->setPin(false);
            }
          }
        }
      }
      request->redirect("/");
    } else {
      request->send(400, "text/plain", "Missing parameters: name & state");
    }
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    rd->drawNew(Groups, *response);   
    request->send(response);
  });

  for (auto sensor: Sensors) {
    sensor->Begin();
  }
  
  server.begin();
  Serial.println("Async server started");

  u8g2.sendF("c", 0xD3); // Display offset
  u8g2.sendF("c", 0x00); // Zkus 0x00–0x20 pro doladění

   u8g2.sendF("c", 0x00 + (32 & 0x0F));   // lower nibble
  u8g2.sendF("c", 0x10 + ((32>> 4) & 0x0F));

  // Text a rám pro kontrolu
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(30, 2, "Hello 0.42 OLED!");
  u8g2.drawFrame(30, 0, 72, 40);

  int centerX = 66; // 72 / 2
  int centerY = 20; // 40 / 2
  int radius = 10;  // velikost kolečka

  u8g2.drawCircle(centerX, centerY, radius, U8G2_DRAW_ALL);

  u8g2.sendBuffer();
}

void loop() 
{
  for (auto sensor: Sensors) 
  {
    sensor->ReadValue();
  }
  delay(10);
}

