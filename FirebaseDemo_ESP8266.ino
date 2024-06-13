#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Define GPIO pins directly
const int speed1 = 14; // D5 on NodeMCU
const int speed2 = 12; // D6 on NodeMCU
const int speed3 = 13; // D7 on NodeMCU

#define FIREBASE_HOST "fan-regulation-c667a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PbWQhm0C1gsXsoEFyV8LdlaBN6DtzxQ63LyECMtO"
#define WIFI_SSID "tracker1"
#define WIFI_PASSWORD "123456789"

void setup() {
  Serial.begin(115200);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
  pinMode(speed3, OUTPUT);
  
  // Ensure all relays are off initially
  digitalWrite(speed1, HIGH);
  digitalWrite(speed2, HIGH);
  digitalWrite(speed3, HIGH);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  int cond = Firebase.getInt("speed");
  if (Firebase.failed()) {
    Serial.println("Failed to get value from Firebase");
    return;
  }
  
  switch (cond) {
    case 1:
      digitalWrite(speed1, LOW);
      digitalWrite(speed2, HIGH);
      digitalWrite(speed3, HIGH);
      Serial.println("Relay 1 on");
      break;
    case 2:
      digitalWrite(speed1, HIGH);
      digitalWrite(speed2, LOW);
      digitalWrite(speed3, HIGH);
      Serial.println("Relay 2 on");
      break;
    case 3:
      digitalWrite(speed1, HIGH);
      digitalWrite(speed2, HIGH);
      digitalWrite(speed3, LOW);
      Serial.println("Relay 3 on");
      break;
    case 0:
      digitalWrite(speed1, HIGH);
      digitalWrite(speed2, HIGH);
      digitalWrite(speed3, HIGH);
      Serial.println("All relays off");
      break;
    default:
      Serial.println("Invalid value received from Firebase");
      break;
  }
}
