const int led1_pin = 2;
const int led2_pin = 3;
const int led3_pin = 4;
const int led4_pin = 5;
const int led5_pin = 6;
const int led6_pin = 7;
const int led7_pin = 8;
const int led8_pin = 9;

const int btn_pin = 13;

int buttonState = 0;

void setup() {
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);
  pinMode(led4_pin, OUTPUT);
  pinMode(led5_pin, OUTPUT);
  pinMode(led6_pin, OUTPUT);
  pinMode(led7_pin, OUTPUT);
  pinMode(led8_pin, OUTPUT);

  pinMode(btn_pin, INPUT);
}

void loop() {
  buttonState = digitalRead(btn_pin);
  if (buttonState == LOW) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(2 + i, HIGH);
        digitalWrite(9 - i, HIGH);
        delay(1000);
      }
      delay(1000);
      for (int i = 0; i < 4; i++) {
        digitalWrite(5 - i, LOW);
        digitalWrite(6 + i, LOW);
        delay(1000);
      }
      delay(1000);
  } else {
    for (int i = 0; i < 8; i++) {
      digitalWrite(led1_pin + i, HIGH);
      delay(200);
    }
    delay(200);
    for (int i = 0; i < 8; i++) {
      digitalWrite(led8_pin - i, LOW);
      delay(200);
    }
    delay(200);
  }
}
