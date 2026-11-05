const byte INPUT_LENGTH = 3;
char inputBuffer[INPUT_LENGTH];
byte inputPosition = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    char incomingByte = Serial.read();

    // 串口监视器可能在输入末尾附加换行符，不把它当作运算内容。
    if (incomingByte == '\r' || incomingByte == '\n')
    {
      continue;
    }

    // 回显收到的字符，让输入内容也显示在串口监视器中。
    Serial.print(incomingByte);
    inputBuffer[inputPosition] = incomingByte;
    inputPosition++;

    if (inputPosition == INPUT_LENGTH)
    {
      char operation = inputBuffer[0];
      char leftDigit = inputBuffer[1];
      char rightDigit = inputBuffer[2];

      Serial.print(" = ");
      if (leftDigit < '0' || leftDigit > '9' ||
          rightDigit < '0' || rightDigit > '9')
      {
        Serial.println("ERR");
      }
      else
      {
        int left = leftDigit - '0';
        int right = rightDigit - '0';

        switch (operation)
        {
          case 'A':
            Serial.println(left + right);
            break;
          case 'S':
            Serial.println(left - right);
            break;
          case 'M':
            Serial.println(left * right);
            break;
          default:
            Serial.println("ERR");
            break;
        }
      }

      // 一条指令处理完后清空接收位置，允许继续发送下一条指令。
      inputPosition = 0;
    }
  }
}
