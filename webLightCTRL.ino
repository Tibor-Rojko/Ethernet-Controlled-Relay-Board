#include <UIPClient.h>
#include <UIPEthernet.h>
#include <UIPServer.h>

#define LED 9

EthernetServer server = EthernetServer(5000);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 6);
bool gotAMessage = false;
String receiveString;
void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    /*if (!gotAMessage) {
      Serial.println("We have a new client");
      //client.println("Hello, client!");
      gotAMessage = true;
    }*/

    // read the bytes incoming from the client:
    while(client.available()){
      char receiveChars = client.read();
      receiveString += receiveChars;
    }
    Serial.println(receiveString);
    if(receiveString.equals("LEDON")){
      digitalWrite(LED, HIGH);  
    } else if(receiveString.equals("LEDOFF")){
      digitalWrite(LED, LOW);  
    }
    int dimNbr = receiveString.toInt();
    analogWrite(LED, dimNbr);
    receiveString = "";
    //Serial.println(receiveString);
    
  }
}

 
