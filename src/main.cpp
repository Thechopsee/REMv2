#include <vector>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config/secret.hh"
#include "objects/GroupBlock.hh"
#include "objects/BasicBlock.hh"
#include "frontend/Renderer.hh"
#include "enums/BlockTypeEnum.hh"
#include "objects/ControllBlocks/OnOffBlock.hh"
#include "objects/SensorBlocks/TextSensorBlock.hh"
#include "sensors/Sensor.hh"

AsyncWebServer server(80);

std::vector<GroupBlock*> Groups;
std::vector<Sensor> Sensors;

Renderer *rd;

void setup() {
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
  Sensor* tempSensor=new Sensor("Temp",[]() {return analogRead(34); },1000);
  Sensors.push_back(*tempSensor);
  Groups.back()->blocks.push_back(new TextSensorBlock(2, 0, {}, "Temp",tempSensor));

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

  server.begin();
  Serial.println("Async server started");
}

void loop() {
  
}

