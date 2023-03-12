
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <sd.h>
#include <bmp.h>
#include <chinese.h>
#include <ESP8266WiFi.h>
#include <Chrono.h> 
#include <WiFiUdp.h>
#include <NTPClient.h>



const char * ssid = "LNO_CIAS";      // wifi的网络名称
const char * password = "36112458";       // wifi的密码
#define AP_NAME "SarmtHome" //dev
const int SD_CS = 16;

TFT_eSPI tft = TFT_eSPI();
WiFiUDP ntpUDP;
Chrono nTpChrono; 
String strIP;

#define main    1     //主界面
#define setMenu   2     //设置界面
uint8_t display_count = 1;
NTPClient timeClient(ntpUDP, "cn.pool.ntp.org", 60*60*8, 60000);
 
void timeDate(){
  if (display_count == main) {
    tft.setCursor(10, 40);
    tft.setTextColor(TFT_WHITE,0x6D7E); 
    tft.drawString(timeClient.getFormattedTime(),12,30,2); 
    tft.setTextColor(TFT_WHITE,0x6DBF); 
    tft.drawString(timeClient.getFormattedDate(),12,10,2);
    tft.setTextColor(TFT_WHITE,0x6D3E); 
    tft.drawString(timeClient.getwDay(),12,50,2); 
    
    
  } else if (display_count == setMenu) {
    
  }   
};

void mainview(){
  tft.fillScreen(0x29AA);
  tft.pushImage(10,8,222,90,b01);
  tft.pushImage(10,100,110,70,b02);
  tft.pushImage(122,100,110,70,b03);
  tft.pushImage(10,173,110,70,b04);
  tft.pushImage(122,173,110,70,b05);
  tft.pushImage(10,246,110,70,b06);
  tft.pushImage(122,246,110,70,b07);

  //tft.setTextColor(TFT_WHITE); 
  //tft.drawString(strIP,12,80,2);  
}

void setdMenu(){
  tft.setCursor(10, 5);
  tft.setTextColor(TFT_WHITE);  
  tft.setTextSize(1);
  tft.print("localIP: ");
}

void displays(){
  if (display_count == main) {
    mainview();
  } else if (display_count == setMenu) {
    setdMenu();
  }
  //timeDate();
}

void setup(void) {

  uint16_t calibrationData[5]={485,3122,353,3169,2};

  Serial.begin(115200);
  WiFi.begin(ssid, password);


  tft.init();
  tft.begin(); 
  tft.fillScreen(TFT_WHITE);
  // tft.setRotation(0); 
  // calibrationData :: 485,3122,353,3169,2
  tft.setTouch(calibrationData);
  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 0, 4);

  tft.setSwapBytes(true);
  tft.pushImage(50,130,140,60,logob);
  
  delay(3000);

  // Set the font colour to be white with a black background
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.setCursor(100, 190);
    tft.setTextColor(TFT_BLACK,TFT_WHITE); 
    tft.print(".");
    
  }
  timeClient.begin();
  strIP=WiFi.localIP().toString();
  //Serial.println(strIP);
  displays();

}

void loop() {

  if (nTpChrono.hasPassed(100) ) {
	  nTpChrono.restart();
	  timeClient.update();
    timeDate();
    //Serial.println(timeClient.getFormattedTime());
  }
  
  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {

  }
}