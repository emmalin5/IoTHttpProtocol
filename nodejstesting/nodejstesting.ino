#include <WiFi.h>

// WiFi credentials
const char* ssid = "Yoon Lae Htike";
const char* password = "30101997";

// Create a WiFiServer instance
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP Address: "); 
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Check for incoming clients
  if (client) {
    Serial.println("New client connected");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Respond to the client
    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Content-Type: text/plain\r\n\r\n");
    client.print("Hello, World!");
    client.stop();
    Serial.println("Client disconnected");
  }
}
