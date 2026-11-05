#include <Arduino.h>
#line 1 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
#include <Keypad.h>
#include <string.h>

// 4×4 矩阵键盘布局
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

// 沿用“键盘按键检测”实验的接线：行接 6、7、8、9，列接 5、4、3、2
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char password[] = "1234";
char inputPassword[sizeof(password)] = {0};
byte inputLength = 0;

#line 23 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
void clearInput();
#line 28 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
void checkPassword();
#line 43 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
void setup();
#line 51 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
void loop();
#line 23 "/data/project/c-cpp_studyProject/learningCode/Microcontroller_Principles_and_Applications/实验/4-矩阵键盘/密码锁/密码锁.ino"
void clearInput() {
  inputLength = 0;
  inputPassword[0] = '\0';
}

void checkPassword() {
  Serial.println();

  if (inputLength == sizeof(password) - 1 &&
      strcmp(inputPassword, password) == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("pass");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("error");
  }

  clearInput();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("请输入四位密码，按 # 确认，按 * 清除：");
}

void loop() {
  char key = keypad.getKey();
  if (key == NO_KEY) {
    return;
  }

  if (key >= '0' && key <= '9') {
    // 最多接收四位，避免写入缓冲区之外
    if (inputLength < sizeof(password) - 1) {
      inputPassword[inputLength++] = key;
      inputPassword[inputLength] = '\0';
      Serial.print(key);
    }
  } else if (key == '*') {
    clearInput();
    Serial.println();
    Serial.println("已清除，请重新输入：");
  } else if (key == '#') {
    checkPassword();
  }
}

