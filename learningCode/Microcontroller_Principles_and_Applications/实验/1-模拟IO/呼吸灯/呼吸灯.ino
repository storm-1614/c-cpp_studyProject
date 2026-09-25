const int LED = 9;
const int DELAY_TIME = 30;  // 延时时间

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    analogWrite(LED, fadeValue);
    delay(DELAY_TIME);
  }

  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(LED, fadeValue);
    delay(DELAY_TIME);
  }
}
