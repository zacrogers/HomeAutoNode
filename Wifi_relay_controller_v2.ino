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

#include <ESP8266WiFi.h>
#define NUM_RELAYS 4


typedef struct 
{
    char* high;
    char* low;
}StateString;  

int Received      = 0;

uint8_t states[NUM_RELAYS] = {1, 1, 1, 1};

const uint8_t RELAYS[NUM_RELAYS]  = {5, 4, 16, 14};
const *char RELAY_STR[NUM_RELAYS] = {"/relay1", "/relay2", "/relay3", "/relay4"};

const StateString STATE_STR[NUM_RELAYS] = {{.high = "1_high", .low = "1_low"}, 
                                           {.high = "2_high", .low = "2_low"}, 
                                           {.high = "3_high", .low = "3_low"}, 
                                           {.high = "4_high", .low = "4_low"}};

int tempSensor    = A0;

int temp          = 0;

int voltIn;
int milliVolts;

int val = 1; 

const char* ssid     = "SSID";
const char* password = "PASSWORD";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);

    // prepare GPIO
    for(uint8_t relay = 0; relay < NUM_RELAYS; ++relay)
    {
        pinMode(RELAYS[relay], OUTPUT);
        digitalWrite(RELAYS[relay], HIGH);
    }

  
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
 
    while (WiFi.status() != WL_CONNECTED)
    {
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
    if (!client)
    {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available())
    {
        delay(1);
    }
  
  // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    update_temp();
    
    for(uint8_t relay = 0; relay < NUM_RELAYS; ++relay)
    {
        update_state(relay);
    }

  // Send the response to the client
  //client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void update_temp(void)
{
    temp = (((5.0 * analogRead(tempSensor)) / 1024) * 100.0) - 10;
    String tempShow = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    tempShow += (temp); 

    if (req.indexOf("/get_temp") != -1)
    {
        Serial.println(temp);  
        client.print(tempShow);
    }
}

void update_state(uint8_t relay)
{
    String relay_state = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    relay_state += (states[relay]) ? STATE_STR[relay].high : STATE_STR[relay].low;
    
    if(states[relay] == 0 && req.indexOf(RELAY_STR[relay]) != -1)
    {
        digtalWrite(RELAYS[relay], LOW);
        states[relay] = 1;
        client.print(relay_state);
    }
 
    if(states[relay] == 1 && req.indexOf(RELAY_STR[relay]) != -1)
    {
        digtalWrite(RELAYS[relay], HIGH);
        states[relay] = 0;
        client.print(relay_state);
    }  
}

