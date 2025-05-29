#define BLYNK_TEMPLATE_ID "TMPL3mehqGMMa"
#define BLYNK_TEMPLATE_NAME "monitoring"
#define BLYNK_AUTH_TOKEN "9_Gw4FAJbE1CSfXNp6W5OtER7rKMTs1U"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN D0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "chill";
char pass[] = "987654321";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  Blynk.run();

  float temperature;
  temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Hum: ");
  Serial.print(humidity);
  Serial.println(" %");
  Blynk.virtualWrite(V0, temperature); // Temperature to V0
  Blynk.virtualWrite(V1, humidity);    // Humidity to V1
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("DHT11 Readings:");
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");
  display.setCursor(0, 35);
  display.print("Hum : ");
  display.print(humidity);
  display.println(" %");
  display.display();

  delay(2000);
}
