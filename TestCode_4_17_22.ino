//--------------------------------------------------------------------------------------------------

#include <SPI.h>
#include "epd2in9_V2.h"
#include "epdpaint.h"
#include "EasterEggLogo.h"
#include "EasterEgg.h"
#include "Neal.h"

// pin definitions-----------------------------------------------------------------------------------

#define COLORED        0
#define UNCOLORED      1
const int HomePin       = 4;
const int Profile1Pin   = 14;
const int Tracking1Pin  = 15;
const int Focus1Pin     = 16;
const int Profile2Pin   = 17;
const int VoiceNotePin  = 18;
const int RecordPin     = 19;

//--------------------------------------------------------------------------------------------------

unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8 
Epd epd;
unsigned long time_start_ms;
//unsigned long time_now_s;

//--------------------------------------------------------------------------------------------------

void setup() {
  
  Serial.begin(115200);
  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

  pinMode(HomePin, INPUT_PULLDOWN);
  pinMode(Profile1Pin, INPUT_PULLDOWN);
  pinMode(Tracking1Pin, INPUT_PULLDOWN);  
  pinMode(Focus1Pin, INPUT_PULLDOWN);
  pinMode(Profile2Pin, INPUT_PULLDOWN);
  pinMode(VoiceNotePin, INPUT_PULLDOWN);
  pinMode(RecordPin, INPUT_PULLDOWN);

  attachInterrupt(digitalPinToInterrupt(HomePin), Home, RISING);
  attachInterrupt(digitalPinToInterrupt(Profile1Pin), Profile1, RISING);
  attachInterrupt(digitalPinToInterrupt(Tracking1Pin), Tracking1, RISING);
  attachInterrupt(digitalPinToInterrupt(Focus1Pin), Focus1, RISING);
  attachInterrupt(digitalPinToInterrupt(Profile2Pin), Profile2, RISING);
  attachInterrupt(digitalPinToInterrupt(VoiceNotePin), VoiceNote, RISING);
  attachInterrupt(digitalPinToInterrupt(RecordPin), Record, RISING);

  
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(32);
  paint.SetHeight(200);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Little Time", &Font24, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 64, 56, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Buddy", &Font24, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 96, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(1000);

  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed ");
      return; 
  }

}

//--------------------------------------------------------------------------------------------------

void loop() {
  
}
//--------------------------------------------------------------------------------------------------
//States//
// NOTE: All values for sizing and locations are set in increments of 8-bits. 
void Home(){
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  paint.SetWidth(24);
  paint.SetHeight(200);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Home Screen", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 48, 48, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(180000);
}

void Profile1(){
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(200);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Profile 1", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 64, 48, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Screen", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 96, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(180000);
}

void Tracking1(){
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();  
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(32);
  paint.SetHeight(200);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(10, 4, "Tracking 1", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 64, 48, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(10, 4, "Screen", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 96, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(180000);
}

void Focus1(){
  epd.SetFrameMemory_Base(Easter_Egg_Logo);
  epd.DisplayFrame();
  
  delay(4000);
  
  epd.SetFrameMemory_Base(Easter_Egg);
  epd.DisplayFrame();

  time_start_ms = millis();
  
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(160);
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "AhAhAh", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 96, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "You didn't say", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 80, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "The magic word", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 64, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "FOUCS TIMER", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 32, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "IN DEVELOPMENT", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 16, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  delay(180000);
}

void Profile2(){
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(200);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Profile 2", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 64, 48, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Screen", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 96, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(180000);
}

void VoiceNote(){
  epd.SetFrameMemory_Base(Neal_Data);
    epd.DisplayFrame();

    time_start_ms = millis();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(200);
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Leave a voice note", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 96, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(144);
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "You can do it", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  
  paint.SetRotate(ROTATE_90);
  paint.SetWidth(24);
  paint.SetHeight(160);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "either or both", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 24, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "ways -Neal", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 8, 8, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  delay(180000);
}

void Record(){
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  paint.SetWidth(24);
  paint.SetHeight(224);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Record Screen", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 48, 48, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(180000);
}
