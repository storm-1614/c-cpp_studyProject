const int pwn = 3;  // 定义 PWN 输出引脚为数字引脚 3
const int adc = 0;  // 定义模拟输入引脚为 A0

void setup() {
  pinMode(pwn, OUTPUT);
}

void loop() {
    int adc = analogRead(0);

    adc = map(adc, 0, 1023, 0, 255);

    analogWrite(pwn, adc);
}
