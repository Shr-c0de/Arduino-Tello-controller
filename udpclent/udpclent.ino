#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Airtel_9663926095";
const char* password = "air76259";



WiFiUDP Udp;

const char* serveradd = "192.168.1.9";
unsigned int serverport = 8080; 


char incomingPacket[255];          // buffer for incoming packets

void setup() {
  pinMode(4, OUTPUT);

  int status = WL_IDLE_STATUS;
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("connecting.");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    analogWrite(4, 100);
    delay(250);
    analogWrite(4,  0);
  }
  Serial.println("\nConnected to wifi");

  Serial.printf("IP address = %s\n", WiFi.localIP());

  ////////////////////////////////////////////////wifi connectivity over

  Udp.begin(serverport);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte;
    String s = "";

    // Read incoming bytes and build the string
    while (Serial.available() > 0) {
      incomingByte = Serial.read();
      s += incomingByte;
      delay(2);  // Small delay to ensure all bytes are read
    }

    // Print the string to the serial monitor
    Serial.println(s);

    // Send the string via UDP
    Udp.beginPacket(serveradd, serverport);
    Udp.write((const unsigned char*)s.c_str(), s.length());
    Udp.endPacket();
  }
}
