#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <TFT_eSPI.h>

#define SERVER_IP "192.168.23.251"
#define SERVER_PORT 7000

TFT_eSPI tft = TFT_eSPI(); // Create an object of the TFT library
TFT_eSprite spr = TFT_eSprite(&tft); // Create a sprite object

char ssid[] = "S10+"; // type your wifi name
char pass[] = "Aaaaaaaa"; // type your wifi password

#define DHTPIN BCM3 //Pin to connect to Wio terminal
#define DHTTYPE DHT22 // DHT type
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  tft.begin(); // Initialize the TFT library
  tft.setRotation(3); // Set the rotation of the display (if needed)
  tft.fillScreen(TFT_BLACK); // Fill the screen with a background color
  
  tft.fillRect(0,0,320,50,TFT_DARKGREEN); //Rectangle fill with dark green 
  tft.setTextColor(TFT_WHITE); //Setting text color
  tft.setTextSize(3); //Setting text size 
  tft.drawString("Smart Container",35,15); //Drawing a text string 

  Serial.begin(115200);
  
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Connect to the server
  if (client.connect(SERVER_IP, SERVER_PORT)) {
    // Send data to the server
    client.println("Temperature: " + String(t) + "C, Humidity: " + String(h) + "%");
    client.stop();
  }

  delay(1000);
}
