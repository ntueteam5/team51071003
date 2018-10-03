//include library
#include <Wire.h>
#include <SPI.h>
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "animation.h"

SSD1306Wire  display(0x3c, 22, 23);
int button_pin = 12;
int old_st = 0, cur_st = 0;
int walking = 0;
unsigned long cur_time = 0, old_time = 0;
int walk_count = 0, idle_count = 0;
int walk_duration = 120, idle_duration = 250;
int cur_posx = 0;

void setup() {
  //設定包率
  Serial.begin(115200);
  display.init();//初始化(init)
  display.setContrast(255); //數值介於0~255，調整對比
  cur_time = millis();
  old_time = cur_time;
  display.clear();//清除螢幕和緩衝區(clear)
  display.drawXbm(0, 0, Logo_width, Logo_height,idle[idle_count]);//印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
  display.display();//顯示畫面(display)
}

void loop() { 

  cur_time = millis();
  cur_st = digitalRead(button_pin);
  delay(30);
  if(old_st == 0 && cur_st == 1){
    walking = 1;
    walk_count = 0;
    old_time = cur_time;
    cur_time += walk_duration;
    }
   if(old_st == 1 && cur_st ==0){
     walking = 0;
     old_time = cur_time;
     cur_time += idle_duration;
     }
     old_st = cur_st;

    if(walking){
      if(cur_time - old_time > walk_duration){
        display.clear(); 
        cur_posx += 40*(cur_time - old_time)/1000;
        if(cur_posx > 128+64){cur_posx = -64;}
        display.drawXbm(cur_posx, 0, Logo_width, Logo_height,walk[walk_count]);//印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
        display.display();
        walk_count++;
        if(walk_count > 7){walk_count = 0;}
        old_time = cur_time;
        }
      }else{
        if(cur_time - old_time > idle_duration){
          display.clear(); 
          display.drawXbm(cur_posx, 0, Logo_width, Logo_height,idle[idle_count]); 
          display.display();
          idle_count++;
          if(idle_count > 1){idle_count = 0;}
          old_time = cur_time;
          }
        }
}


