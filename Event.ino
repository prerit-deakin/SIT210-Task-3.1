#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include <Wire.h>
#include <BH1750.h>
#include <IFTTTMaker.h>

char ssid[] = "Prerit's Pixel 7 Pro";       
char password[] = "Prerit123";  
#define KEY "gJ_G5ib4jvxmQDljur-X_Jrhq0UYNEYkJ9SkPpo_j3s"  
#define EVENT_NAME "sunlight_on" 




WiFiSSLClient client;
IFTTTMaker ifttt(KEY, client);

void setup() {

  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
  if(ifttt.triggerEvent(EVENT_NAME, ssid)){
    Serial.println("Successfully sent");
  } else
  {
    Serial.println("Failed!");
  }

}

void loop() {
}
