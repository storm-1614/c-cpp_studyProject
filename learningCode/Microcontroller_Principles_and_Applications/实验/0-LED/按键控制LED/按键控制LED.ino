/*
 * 按钮控制 LED
 *
 * Date: 2026.09.15
 * Author: storm1614.top
 */

const int buttonPin = 7;   // 按键接 D7
const int ledPin = 11;     // LED 接 D11

int buttonState = 0;

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // 读取按键状态
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
        // 按下按键
        digitalWrite(ledPin, HIGH);
    } else {
        // 松开按键
        digitalWrite(ledPin, LOW);
    }
}
