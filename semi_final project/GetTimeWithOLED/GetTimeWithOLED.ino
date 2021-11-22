#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ssd1306syp.h>
#define SDA_PIN 2
#define SCL_PIN 0
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
boolean connectioWasAlive = true;

const char* ssid     = "";
const char* password ="";

const String url = "http://quan.suning.com/getSysTime.do";//主机IP：端口/路径 或 网址
int httpCode;
String payload;
String inputString = "";  //接收到的数据
bool GetDate=false;
int Year;
int Month;
int Day;
int Hour;
int Minute;
int Second;
 
void setup() 
{
  Serial.begin(9600);
  display.initialize();
  
  WiFi.begin(ssid, password);   //WiFi connection
  
  Serial.println("");           
  Serial.print("Waiting for connecting to ");
  Serial.println(ssid);
  
  display.setTextSize(1);//字体大小
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Waiting for connecting to ");
  display.println(ssid);
  
  
  while (WiFi.status() != WL_CONNECTED)   //Wait for the WiFI connection completion
  {
    delay(500);
    Serial.print(".");
    display.print(".");
  }
  Serial.println("");
  Serial.println("Wifi connected!"); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  display.println("");
  display.println("Wifi connected!"); 
  display.println("IP address: ");
  display.println(WiFi.localIP());
  display.update();
  delay(2000);
  display.clear();
}
 
void loop() 
{
   GetTime(); 
   DateHandle();
  display.setTextSize(1);//大概8个像素点的高度
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Data");
  display.setTextSize(2);//字体大小
  display.setTextColor(WHITE);
  display.setCursor(10,12);//x  y  12=8+4
  display.print(Year);
  display.print(":");
  display.print(Month);
  display.print(":");
  display.println(Day);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("Time");
  display.update();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,44);//32+8+4
  display.print(Hour);
  display.print(":");
  display.print(Minute);
  display.print(":");
  display.println(Second);/**/
  display.update();
  
  display.clear();
}

void GetTime()
{
     if(WiFi.status()== WL_CONNECTED)   //确保WiFi连接
     {
       HTTPClient http;    //定义一个客户端类
     
       http.begin(url);      //主机IP：端口/路径 或 网址，此处用的是api
       http.addHeader("Content-Type", "text/plain");  //设置消息类型
     
       httpCode = http.POST("Message from ESP8266");   //发送请求
       payload = http.getString();                  //获取返回payload
       /*测试用
       //Serial.println(httpCode);   //
       //Serial.println(payload);    //
       //inputString += http.getString();
       */
       http.end();  //关闭TCP 释放资源
     }
     else
     {
        Serial.println("WiFi Unconnected!!!!");  
     }
     delay(1000); //获取时间间隔
     GetDate=true;
}
void DateHandle()
{
    int jsonBeginAt = payload.indexOf("{");   //判断json数据完整性
    int jsonEndAt = payload.lastIndexOf("}");
    if (jsonBeginAt != -1 && jsonEndAt != -1) 
    {
        if(GetDate==true)
        {
                //净化json数据
            payload = payload.substring(jsonBeginAt, jsonEndAt + 1);//取得一个完整的JSON字符串
            
            const size_t capacity = JSON_OBJECT_SIZE(2) + 60;
            DynamicJsonDocument doc(capacity);
            //const char* json = "{\"sysTime2\":\"2020-03-07 19:13:28\",\"sysTime1\":\"20200307191328\"}";
            deserializeJson(doc, payload);//解析payload
            
            const char* sysTime2 = doc["sysTime2"]; // "2020-03-07 19:13:28"
            const char* sysTime1 = doc["sysTime1"]; // "20200307191328"
        
            String Date=sysTime1;
            //int nian = sysTime2.lastIndexOf("-");//定位到某处
            Year=(Date.substring(0,4)).toInt();//截取（下标从0开始）[0,4)的数据
            Month=(Date.substring(4,6)).toInt();
            Day=(Date.substring(6,8)).toInt();
            Hour=(Date.substring(8,10)).toInt();
            Minute=(Date.substring(10,12)).toInt();
            Second=(Date.substring(12,14)).toInt();
            /*测试用
            //Serial.println(Date);
            //Serial.println(Year);
            //Serial.println(Second);
            */
            GetDate=false;
        }
    }
}
