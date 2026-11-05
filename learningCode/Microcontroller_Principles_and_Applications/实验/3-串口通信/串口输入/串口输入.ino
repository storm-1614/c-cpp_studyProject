int ledPin = 13;

void setup() {
  Serial.begin(9600);  // 启动串口通讯，传输波特率 9600
  Serial.println("Please input serial data:");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {  // 检查串口缓存是否有数据等待传输
    int serialData = Serial.read();
    Serial.println(serialData);
    delay(100);

    if (serialData == 'H') {  // 如果是字母 'H'，打开 LED 灯
      digitalWrite(ledPin, HIGH);
      delay(500);
    }

    if (serialData == 'L') {  // 如果是字母 'L'，关闭 LED 灯
      digitalWrite(ledPin, LOW);
      delay(500);
    }
  }
}
