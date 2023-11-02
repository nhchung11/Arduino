void setup() {
  Serial.begin(9600); // Initialize the Serial communication
  pinMode(2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    char receivedChar = Serial.read(); // Read the character
    Serial.print("You typed: "); // Print a message
    Serial.println(receivedChar); // Print the character
  }
  if (Serial.available())
  {
    char data = Serial.read();
    if (data == '1')
    {
      digitalWrite(2, HIGH);
    }
    else if (data == '0')
    {
      digitalWrite(2, LOW);
    }
  }
}
