const int TrigPin = 2; 
const int EchoPin = 3; 
const int GreenPin = 4;
const int YellowPin = 5;
const int RedPin = 6; 
float cm;

void setup()
{ Serial.begin(9600); 
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
}

void loop()
{ digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm
  cm = (int(cm * 100)) / 100; //保留两位小数
  if (cm < 10)
    {digitalWrite(RedPin, HIGH);
     delay(100);
     digitalWrite(RedPin, LOW);
      }
  else if (cm > 10 && cm < 50)
    {digitalWrite(YellowPin, HIGH);
     delay(100);
     digitalWrite(YellowPin, LOW);
      }
  else if (cm > 50)
    {digitalWrite(GreenPin, HIGH);
     delay(100);
     digitalWrite(GreenPin, LOW);
      }
  Serial.print(cm);
  Serial.print("cm");//串口输出
  Serial.println();
}
