int photocellPin = A2;
int ledPin = 9;
int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(photocellPin);

  if (val <= 300) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  Serial.print("Light: ");
  Serial.println(val);
  delay(100);
}
