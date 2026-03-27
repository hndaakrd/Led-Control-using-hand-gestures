// Finger Count LED Control using Arduino UNO
// Receives finger count (0 to 5) from Python over Serial

const int ledPins[5] = {2, 3, 4, 5, 6};  // LEDs connected to these pins

String inputString = "";
int fingerCount = 0;

void setup() {
  Serial.begin(9600);

  // Set LED pins as OUTPUT
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Arduino Ready");
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');  // Read until newline
    inputString.trim(); // Remove spaces/newline

    if (inputString.length() > 0) {
      fingerCount = inputString.toInt();

      // Safety limit
      if (fingerCount < 0) fingerCount = 0;
      if (fingerCount > 5) fingerCount = 5;

      // Control LEDs based on finger count
      for (int i = 0; i < 5; i++) {
        if (i < fingerCount) {
          digitalWrite(ledPins[i], HIGH);
        } else {
          digitalWrite(ledPins[i], LOW);
        }
      }

      // Debug output
      Serial.print("Received Finger Count: ");
      Serial.println(fingerCount);
    }
  }
}