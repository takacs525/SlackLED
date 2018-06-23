/*
  SlackLED - Turns the LEDs on and off based on your Slack presence.

  FB: https://www.facebook.com/flyingiot/

  Slack: https://slack.com
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "./Config.h"
 
void setup () {
  delay(1000);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
 
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");
  
  initWifi();
}

void initWifi() {
    if (WiFi.status() != WL_CONNECTED) 
    {
        WiFi.stopSmartConfig();
        WiFi.enableAP(false);

        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        WiFi.begin(ssid, password);
    
        Serial.print("Waiting for Wifi connection.");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
        
        Serial.println();
        Serial.println("Connected to wifi.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } 
}

 
void loop() {
  initWifi();

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/api/users.getPresence?token=" + token;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: SlackLED_ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");

  String payload;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    //Serial.println(line);
    if (line.startsWith("{\"ok\":")) {
      payload = line;
      break;
    }    
  }
  
  Serial.print("reply was:");
  Serial.println(payload);
  Serial.println("closing connection");
  Serial.println();  


  if(payload.indexOf("\"presence\":\"active\",") > 0)
  {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }

  if(payload.indexOf("\"presence\":\"away\",") > 0)
  {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);    
  }  
 
  delay(delay_sec * 1000);    //Send a request every X seconds
}

