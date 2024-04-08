#include <Arduino.h>

#define Breath_Led_Pin D10  //定义呼吸灯的引脚为D10

int brightness = 0;  //定义PWM初值
int fadeAmount = 5;  //定义PWM每次增加的值


void setup(void)
{
  Serial.begin(115200);
  Serial2.begin(115200);
	//这里不需要定义引脚的模式，即不需要使用pinMode();
}

void loop(void)
{
  int i = analogRead(A0);
  int j = analogRead(A1);
  int x = analogRead(A2);
  int y = analogRead(A3);
  analogWrite(D3, brightness);
  analogWrite(D6, brightness);
  analogWrite(D9, brightness);
  analogWrite(D10, brightness);
    analogWrite(D11, brightness);    //对引脚号为10的LED灯进行模拟量输出，大小为brighness
    brightness = brightness + fadeAmount;    //改变brighness的大小
    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;   //循环增加brightness的大小，保证其数值在0-255之间
    }

    delay(550);  //延迟30ms
    
    Serial.print("I:");
    Serial.println(i);
    
    Serial.print("J:");
    Serial.println(j);
    
    Serial2.print("X:");
    Serial2.println(x);
  
    Serial2.print("Y:");
    Serial2.println(y);


}
