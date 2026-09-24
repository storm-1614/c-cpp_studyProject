int led_pin[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

const int btn1_pin = 10;
const int btn2_pin = 11;

int button1State = 0;
int button2State = 0;

int i, j;

void setup() {
  for (i = 0; i < 8; i++) {
    pinMode(led_pin[i], OUTPUT);
  }

  pinMode(btn1_pin, INPUT);
  pinMode(btn2_pin, INPUT);
}

void loop() {
  button1State = digitalRead(btn1_pin);
  button2State = digitalRead(btn2_pin);
  if (button1State == HIGH) {
    for (i = 0; i < 8; i++) {
      digitalWrite(led_pin[i], HIGH);
      delay(1000);
      digitalWrite(led_pin[i], LOW);
    }
  } else {
    for (i = 0; i < 8; i++) {
      digitalWrite(led_pin[i], LOW);
    }
  }

  if (button2State == HIGH) {
    for (i = 0; i < 4; i++) {
      digitalWrite(led_pin[i], HIGH);
      digitalWrite(led_pin[7 - i], HIGH);
      delay(1000);
    }

    for (i = 0; i < 4; i++) {
      digitalWrite(led_pin[3 - i], LOW);
      digitalWrite(led_pin[4 + i], LOW);
      delay(1000);
    }
  } else {
    for (i = 0; i < 8; i++) {
      digitalWrite(led_pin[i], LOW);
    }
  }
}
