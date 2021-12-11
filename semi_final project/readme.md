从代码到实物课程记录————互联网时钟（半期项目）

物料

ESP8266开发板   
oleds1306显示屏

使用ESP8266连接wifi，籍由API（http://quan.suning.com/getSysTime.do）
获得时间并显示在屏幕上，未完成所有内容（无外壳）  
制作过程：
1.下载arduino IDE并安装  
![image](https://user-images.githubusercontent.com/89186177/145661777-5cde2f61-f761-4a7b-bc52-18ce8f645947.png)  
2.打开IDE，文件-首选项，在“附加开发板管理器地址”中输入 http://arduino.esp8266.com/stable/package_esp8266com_index.json  
![image](https://user-images.githubusercontent.com/89186177/145661820-344d650f-e5bb-498a-965e-fb6a90128f01.png)  
3.选择项目-加载库-管理库，搜索esp8266并安装对应库  
4.将esp8266开发板连接，编译并下载程序。  
5.连接开发板与oled屏幕，d1连接SCL端，d2连接SDA端。  
6.接通电源，打开手机搜索wifi“flyAkrai”并连接  
![Screenshot_20211211_112357_com android settings](https://user-images.githubusercontent.com/89186177/145662299-2d5b73d0-b85f-4e3d-8e02-e0732fb2c686.jpg)  
7.在浏览器中输入192.168.4.1，连接wifi  
![Screenshot_20211211_112459_com huawei browser](https://user-images.githubusercontent.com/89186177/145662300-aeb3de00-7582-46a3-a288-cd30c209b0ba.jpg)  
8.大功告成  
![IMG_20211211_112512](https://user-images.githubusercontent.com/89186177/145662257-41d422f0-2b6f-463a-9e5c-47d202e6fd5b.jpg)
