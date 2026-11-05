/* Arduino 串口输出
 * 
 * Date: 2026-10-22
 * Author: storm1614.top
 */
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println("Hello World!");
    delay(1000);
}
