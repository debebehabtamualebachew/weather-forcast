#include <Ethernet.h>

#include <ESP8266WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* host = "your_host_address";

const int fanPin = 3;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Send a request to the host to get the fan state
  if (client.connect(host, 80)) {
    client.print("GET /fan HTTP/1.1\n");
    client.print("Host: " + String(host) + "\n");
    client.print("\n");

    String response = "";
    while (client.available()) {
      response += (char)client.read();
    }
    client.stop();

    // Extract the fan state from the response
    int fanState = response.toInt();

    // Set the fan pin based on the fan state
    digitalWrite(fanPin, fanState);
  } else {
    Serial.println("Connection to host failed");
  }

  delay(1000);
}