/*
 * 交通信号灯
 *
 * Date: 2026-09-15
 * Author: storm1614.top
*/


int redled = 10;
int yellowled = 7;
int greenled = 3;

void setup()
{
    pinMode(redled, OUTPUT);
    pinMode(yellowled, OUTPUT);
    pinMode(greenled, OUTPUT);
}

void loop()
{
    digitalWrite(redled, HIGH);
    delay(1000);
    digitalWrite(redled, LOW);
    digitalWrite(yellowled, HIGH);
    delay(200);
    digitalWrite(yellowled, LOW);
    digitalWrite(greenled, HIGH);
    delay(1000);
    digitalWrite(greenled, LOW);
}
