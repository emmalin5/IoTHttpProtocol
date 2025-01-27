#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Yoon Lae Htike";
const char* password = "30101997";

// REST API endpoint
const char* serverName = "http://192.168.1.7:3000/api/data";  // Replace <your_server_ip> with your API server's IP

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL
    http.begin(serverName);

    // Set the request content type to JSON
    http.addHeader("Content-Type", "application/json");

    // Prepare the JSON payload
    // Fade Data Pay load
    String jsonData = "{\"temperature\": 25.5, \"humidity\": 60}";

    // Send POST request
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.setTimeout(10000);  // 5000 milliseconds = 5 seconds

    // Free resources
    http.end();
  }

  delay(10000);  // Send data every 10 seconds
}
