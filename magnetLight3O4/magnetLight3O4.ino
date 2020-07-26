//--------------------------------------------------------------------------------
// 磁石によるON/OFFができる模型用車両室内灯スケッチ
// [magnetLight3O4.ino]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------
#include <arduino.h>

//各種設定、宣言

#define O1 0            // Atiny85 PB0(5pin)
#define O2 1            // Atiny85 PB1(6pin) analogwrite
#define O3 3            // Atint85 PB3(2pin)
#define O4 4            // Atiny85 PB4(3pin) analogwrite

unsigned char gBright = 10;
//unsigned char gBright = 255;

unsigned long gPreviosTimeA  = 0;  // PreviosTime 前時間

void setup()
{
  pinMode(O1, INPUT_PULLUP); // リードスイッチ入力 
  pinMode(O2, OUTPUT);
  pinMode(O3, OUTPUT);
  pinMode(O4, OUTPUT);  // 室内灯

  gPreviosTimeA = millis();
}
void loop() {
  static int state = 0;
  static char MagSw = LOW;
  char io;
  
  if ( (millis() - gPreviosTimeA ) >= 100) {// 100:100msec  10:10msec  Function decoder は 10msecにしてみる。
    switch(state){
      case 0:
             if( digitalRead(O1) == LOW){
                if(MagSw == LOW){
                  analogWrite(O4,gBright / 4);
                  delay(100);
                  analogWrite(O4,0);
                  delay(100);
                  analogWrite(O4,gBright);
                  delay(10);
                  analogWrite(O4,0);
                  delay(30);
                  analogWrite(O4,gBright/4);
                  delay(10);
                  analogWrite(O4,0);
                  delay(50);
                  analogWrite(O4,gBright/4);
                  delay(100);
                  analogWrite(O4,gBright);
                  MagSw = HIGH;
                } else {
                  analogWrite(O4,0);
                  MagSw = LOW;
                }
                state = 1;
              }
              break;
      case 1:
              if(digitalRead(O1) == HIGH){
                state = 0;
              }
              break;                            
      default:
              break;
    }
    gPreviosTimeA = millis();
  }
}
