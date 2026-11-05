#include <Keypad.h>

// 设置键盘的尺寸
const byte ROWS = 4;  // 行数
const byte COLS = 4;  // 列数

// 定义键盘上的按键字符布局
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

// 指定 Arduino 引脚连接的行和列
byte rowPins[ROWS] = {6, 7, 8, 9};  // 连接行（R1-R4）的引脚
byte colPins[COLS] = {5, 4, 3, 2};  // 连接列（C1-C4）的引脚

// 创建 Keypad 对象
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // 设置串口调试波特率
  Serial.println("4x4键盘测试");
  Serial.println("-按下按键查看结果-");
}

void loop() {
  // 尝试获取一个按键；无按键时 getKey() 返回 NO_KEY
  char key = keypad.getKey();

  if (key) {  // 如果有按键被按下
    Serial.print("按键：");
    Serial.println(key);  // 在串口监视器中打印按下的键
  }
}
