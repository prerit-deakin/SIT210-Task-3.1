#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include <Wire.h>
#include <BH1750.h>
#include <IFTTTMaker.h>

char ssid[] = "Prerit's Pixel 7 Pro";
char password[] = "Prerit14";
#define KEY "gJ_G5ib4jvxmQDljur-X_Jrhq0UYNEYkJ9SkPpo_j3s"
#define EVENT_NAME "sunlight_on"

WiFiSSLClient client;
IFTTTMaker ifttt(KEY, client);
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to WiFi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin();
  lightMeter.begin();
  Serial.println("BH1750 sensor initialized.");
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light level: ");
  Serial.print(lux);
  Serial.println(" lx");

  if (lux > 50) {
    if (ifttt.triggerEvent(EVENT_NAME)) {
      Serial.println("IFTTT trigger sent!");
    } else {
      Serial.println("IFTTT trigger failed.");
    }
    delay(600000); // wait 10 minutes before triggering again
  }

  delay(5000); // check light every 5 seconds
}
