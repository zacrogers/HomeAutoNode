/*
ESP8266 pin conversion

ESP pin 3 = pin RX
ESP pin 1 = pinTX
ESP pin 16 = pin D0
ESP pin 5 = pin D1
ESP pin 4 = pin D2
ESP pin 0 = pin D3
ESP pin 2 = pin D4
ESP pin 14 = pin D5
ESP pin 12 = pin D6
ESP pin 13 = pin D7
ESP pin 15 = pin D8
*/

#include"ESP8266PinAssignments.h"
#include <ESP8266WiFi.h>

int Received = 0;
int relay_1_state = 1;
int relay_2_state = 1;
int relay_3_state = 1;
int relay_4_state = 1;

int relay_1 = 5;
int relay_2 = 4;
int relay_3 = 16;
int relay_4 = 14;

int tempSensor = A0;

int temp = 0;

int voltIn;
int milliVolts;

int val = 1; 

const char* ssid = "SSID";
const char* password = "PASSWORD";

//String html ="<!DOCTYPE html> <html> <body> <button type=\"button\" onclick=\"alert('Hello world!')\" value=\"/relay1\">LED ON</button> <button type=\"button\" onclick=\"alert('Hello world!')\" value=\"0\">LED OFF</button> </body> </html>";


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);    
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  

//Uncomment for node 1 static IP
 
  IPAddress ip(192,168,20,100);
  IPAddress gateway(192,168,20,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);  
 

/*
//Uncomment for node 2 static IP
 
  IPAddress ip(192,168,20,101);
  IPAddress gateway(192,168,20,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);
*/

/*
//Uncomment for node 3 static IP
 
  IPAddress ip(192,168,20,102);
  IPAddress gateway(192,168,20,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);
*/

/*
//Uncomment for node 4 static IP
 
  IPAddress ip(192,168,20,103);
  IPAddress gateway(192,168,20,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);
*/




  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop(){

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  temp = (((5.0 * analogRead(tempSensor)) / 1024) * 100.0)-10;
  
  String rel1 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  rel1 += (relay_1_state)?"1_high":"1_low";

  String rel2 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  rel2 += (relay_2_state)?"2_high":"2_low";

  String rel3 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  rel3 += (relay_3_state)?"3_high":"3_low";

  String rel4 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  rel4 += (relay_4_state)?"4_high":"4_low";

  String tempShow = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  tempShow += (temp);  

  String allStates = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  allStates += (relay_states(relay_1_state, relay_2_state, relay_3_state, relay_4_state));  

  int state_refresh = 0;

  if(req.indexOf("/get_states") != -1){
    client.print(allStates);  
  }


  
  if (req.indexOf("/get_temp") != -1){
   Serial.println(temp);  
   client.print(tempShow);

  }
   
  if (relay_1_state == 0 && req.indexOf("/relay1") != -1){
    digitalWrite(relay_1,LOW);
    relay_1_state =1;
    client.print(rel1);
  }

  else if (relay_1_state == 1 && req.indexOf("/relay1") != -1){
    digitalWrite(relay_1,HIGH);
    relay_1_state =0;
    client.print(rel1);
  }

  if (relay_2_state == 0 && req.indexOf("/relay2") != -1){
    digitalWrite(relay_2,LOW);
    relay_2_state =1;
    client.print(rel2);

  }

  else if (relay_2_state == 1 && req.indexOf("/relay2") != -1)
  {
    digitalWrite(relay_2,HIGH);
    relay_2_state =0;
    client.print(rel2);  
  }

  if (relay_3_state == 0 && req.indexOf("/relay3") != -1){
    digitalWrite(relay_3,LOW);
    relay_3_state =1;
    client.print(rel3);

  }

  else if (relay_3_state == 1 && req.indexOf("/relay3") != -1){
    digitalWrite(relay_3,HIGH);
    relay_3_state =0;
    client.print(rel3);
  }

  
  if (relay_4_state == 0 && req.indexOf("/relay4") != -1){
    digitalWrite(relay_4,LOW);
    relay_4_state =1;
    client.print(rel4);    

  }

  else if (relay_4_state == 1 && req.indexOf("/relay4") != -1){
    digitalWrite(relay_4,HIGH);
    relay_4_state=0;
    client.print(rel4);
  }
//    if(req.indexOf("/re1_on")){
//      digitalWrite(relay_1,HIGH);
//      relay_1_state=0;
//      client.print(rel1);
//    }
//    if(req.indexOf("/re1_off")){
//      digitalWrite(relay_1,LOW);
//      relay_1_state=1;
//      client.print(rel1);
//    }
//    if(req.indexOf("/re2_on")){
//      digitalWrite(relay_2,HIGH);
//      relay_2_state=0;
//      client.print(rel2);
//    }
//    if(req.indexOf("/re2_off")){
//      digitalWrite(relay_2,LOW);
//      relay_2_state=0;
//      client.print(rel2);
//    }
//    if(req.indexOf("/re3_on")){
//      digitalWrite(relay_3,HIGH);
//      relay_3_state=0;
//      client.print(rel3);
//    }
//    if(req.indexOf("/re3_off")){
//      digitalWrite(relay_3,LOW);
//      relay_3_state=0;
//      client.print(rel3);
//    }
//    if(req.indexOf("/re4_on")){
//      digitalWrite(relay_4,HIGH);
//      relay_4_state=0;
//      client.print(rel4);
//    }
//    if(req.indexOf("/re4_off")){
//      digitalWrite(relay_4,LOW);
//      relay_4_state=0;
//      client.print(rel4);
//    }
  client.flush();


  // Send the response to the client
  //client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}


int relay_states(int r1, int r2, int r3, int r4){
    int states_code = 0b00000000;

    if(r1 == 0){states_code &= 0b11111110;}
    if(r1 == 1){states_code |= 0b00000001;}
    if(r2 == 0){states_code &= 0b11111101;}
    if(r2 == 1){states_code |= 0b00000010;}
    if(r3 == 0){states_code &= 0b11111011;}
    if(r3 == 1){states_code |= 0b00000100;}
    if(r4 == 0){states_code &= 0b11110111;}
    if(r4 == 1){states_code |= 0b00001000;}
  
    return states_code;
}
//void mirror_control(req, client){
//
//
//}
//  
//void get_status(){}
//    String rel1 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//    rel1 += (relay_1_state)?"1_high":"1_low";
//    
//    String rel2 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//    rel2 += (relay_2_state)?"2_high":"2_low";
//    
//    String rel3 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//    rel3 += (relay_3_state)?"3_high":"3_low";
//    
//    String rel4 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//    rel4 += (relay_4_state)?"4_high":"4_low";
//    
//    String tempShow = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//    tempShow += (temp);  
//}
