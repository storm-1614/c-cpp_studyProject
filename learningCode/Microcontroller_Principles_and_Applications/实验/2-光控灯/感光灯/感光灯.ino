
const int photocellPin = A2;
const int ledPin = 9;

const int sensorMin = 0;
const int sensorMax = 1023;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int val = analogRead(photocellPin);

    int brightness = map(val, sensorMin, sensorMax, 255, 0);
    brightness = constrain(brightness, 0, 255);

    analogWrite(ledPin, brightness);

    Serial.print("Light: ");
    Serial.print(val);
    Serial.print("  PWM: ");
    Serial.println(brightness);

    delay(100);
}
