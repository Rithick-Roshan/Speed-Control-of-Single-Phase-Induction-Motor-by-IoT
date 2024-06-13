const int relayPins[3] = {2, 3, 4}; // Array of relay pins for 3 relays
const int totalRelays = 3; // Total number of relays

void setup() {
  // Set all relay pins as outputs and turn them off
  for (int i = 0; i < totalRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Ensure all relays are off initially
  }
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  Serial.println("Enter a number between 1 and 3 to control the relays, or 4 to turn off all relays:");
}

void loop() {
  if (Serial.available() > 0) {
    int relayIndex = Serial.parseInt(); // Read the input value
    // Clear the serial buffer
    while (Serial.available() > 0) {
      char _ = Serial.read();
    }
    if (relayIndex >= 1 && relayIndex <= totalRelays) {
      turnOnRelay(relayIndex - 1); // Adjust for zero-based array
    } else if (relayIndex == 4) {
      turnOffAllRelays();
    } else {
      Serial.println("Invalid input. Please enter a number between 1 and 3, or 4 to turn off all relays.");
    }
  }
}

void turnOnRelay(int relayIndex) {
  // Turn off all relays first
  for (int i = 0; i < totalRelays; i++) {
    digitalWrite(relayPins[i], HIGH);
  }
  // Turn on the selected relay
  digitalWrite(relayPins[relayIndex], LOW);
  Serial.print("Relay ");
  Serial.print(relayIndex + 1);
  Serial.println(" is ON.");
}

void turnOffAllRelays() {
  // Turn off all relays
  for (int i = 0; i < totalRelays; i++) {
    digitalWrite(relayPins[i], HIGH);
  }
  Serial.println("All relays turned off.");
}
