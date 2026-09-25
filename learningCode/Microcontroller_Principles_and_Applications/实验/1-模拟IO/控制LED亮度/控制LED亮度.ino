// 定义 PWN 输出引为数字引脚 3
const int pwn = 3;

void setup() {
  // 设置 PWN 引脚为输出模式
  pinMode(pwn, OUTPUT);
}

void loop() {
  int pwnscale = 25;
  while (pwnscale < 256) {
    analogWrite(pwn, pwnscale);
    delay(100);
    pwnscale = (pwnscale + 15);
  }
  while (pwnscale > 0) {
    analogWrite(pwn, pwnscale);
    delay(100);
    pwnscale = (pwnscale - 15);
  }
}
