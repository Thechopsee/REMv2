#include <vector>
#include <ESP8266WiFi.h>

#include "config/secret.hh"
#include "objects/GroupBlock.hh"
#include "objects/BasicBlock.hh"
#include "frontend/Renderer.hh"
#include "enums/BlockTypeEnum.hh"
#include "objects/ControllBlocks/OnOffBlock.hh"

WiFiServer server(80);

std::vector<GroupBlock*> Groups;

Renderer *rd;

void setup() {
  Serial.begin(9600);
  delay(10);
  rd=new Renderer();

  Groups.push_back(new GroupBlock(0,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 0, {16,13},"Pozition"));
  Groups.back()->blocks.push_back(new OnOffBlock(0, 1, {14},"Sto"));
  //Groups.back()->blocks.push_back(new OnOffBlock(0, 2, 1,"CABINLED"));
  Groups.push_back(new GroupBlock(1,controll));
  Groups.back()->blocks.push_back(new OnOffBlock(1, 0, {12},"Cabin"));
  //Groups.back()->blocks.push_back(new OnOffBlock(1, 1, 13,"Red"));

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

  server.begin();
  Serial.println("Server started");

  Serial.print("URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) 
  {
      return;
  }
  
  Serial.println("NEW request");
  
  String request = client.readStringUntil('r');
  //ignoring favicon request not pernament solution
  if (request[5]=='f')
  {
      return;  
  }
  Serial.println(request);
  
  client.flush();
  for(int i=0;i<Groups.size();i++)
  {
    for(int j=0;j<Groups[i]->blocks.size();j++)
    {
        Groups[i]->blocks[j]->resolveInput(request);
    }
  }
  rd->drawNew(Groups,client);

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

