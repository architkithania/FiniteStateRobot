#include "MAINDEF.h"
#include <Servo.h>
#define BLK 0
#define WHT 1

FSMClass FSM1;                           //The given FSM is named 'FSM1'.
TM1637DisplayClass LEDDisplay(D10, D11); //7-segment LED Display is connected to D10,D11 for debug
ServoClass Servo1(D9);
SensorClass S1(A5);
SensorClass S2(A4);
SensorClass S3(A3);
SensorClass S4(A2);
MotorClass MotorR(D3, D2);
MotorClass MotorL(D5, D4);
UltrasoundSensorClass Sonic(D12, D13);

int counter = 0;
int globalCounter = 0;

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);         //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  FSM1.init(S_999);             //must have this line, you can change the first state of the FSM
  Servo1.init();
  Servo1.setValue(50);
}

void loop()
{
  FSM1.run(); //important, don't modify this line
}
//================= Students add STATES below this line ====================
//----------start of state S_999 -----
void S_999()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(999);
    MotorL.setSpeed(0);
    MotorR.setSpeed(0);
  }
  if (FSM1.getTime() > 1000 && globalCounter <= 6)
    FSM1.transit(S_100);
}
//----------start of state S_100-----
void S_100()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(100);
    while (S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(210);
      MotorR.setSpeed(150);
    }
  }
  if (S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_101);
  if (S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_102);
  if (S1.getHiLow() == BLK && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_202);
  if(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_102);
}
//----------start of state S_101-----
void S_101()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(101);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_100);
}
//----------start of state S_102-----
void S_102()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(102);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK) && !(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK))
    FSM1.transit(S_100);
}
//----------start of state S_202-----
void S_202()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(202);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(Sonic.getDistance()<15)
    FSM1.transit(S_900);
  if(FSM1.getTime()>500 && !(Sonic.getDistance()<15))
    FSM1.transit(S_203);
}
//----------start of state S_200-----
void S_200()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(200);
    MotorL.setSpeed(0);
    MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500 && Sonic.getDistance()<15)
    FSM1.transit(S_900);
  if (FSM1.getTime()>500 && !(Sonic.getDistance()<15))
    FSM1.transit(S_203);
}
//----------start of state S_900-----
void S_900()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(900);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_901);
}
//----------start of state S_919-----
void S_919()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(919);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>150)
    FSM1.transit(S_920);
}
//----------start of state S_920-----
void S_920()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(920);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_901);
}
//----------start of state S_901-----
void S_901()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(901);
    Servo1.setValue(120);
  }
  if(FSM1.getTime()>1500)
    FSM1.transit(S_902);
}
//----------start of state S_902-----
void S_902()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(902);
    Servo1.setValue(50);
  }
  if(FSM1.getTime()>1500)
    FSM1.transit(S_903);
}
//----------start of state S_903-----
void S_903()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(903);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>700)
    FSM1.transit(S_904);
}
//----------start of state S_904-----
void S_904()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(904);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_905);
}
//----------start of state S_905-----
void S_905()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(905);
    MotorL.setSpeed(-150); MotorR.setSpeed(80);
  }
  if(FSM1.getTime() > 1000)
    FSM1.transit(S_915);
}
//----------start of state S_915-----
void S_915()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(915);
    MotorL.setSpeed(0); MotorR.setSpeed(0); 
  }
  if(FSM1.getTime()>300)
    FSM1.transit(S_918);
}
//----------start of state S_918-----
void S_918()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(918);
    MotorL.setSpeed(100); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_916);
}
//----------start of state S_916-----
void S_916()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(916);
    MotorL.setSpeed(-110); MotorR.setSpeed(30);
  }
  if(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT || FSM1.getTime()>800)
    FSM1.transit(S_917);
}
//----------start of state S_917-----
void S_917()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(917);
    MotorL.setSpeed(0); MotorR.setSpeed(0); 
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_906);
}
//----------start of state S_906-----
void S_906()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(906);
    while (S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(210);
      MotorR.setSpeed(150);
    }
  }
  if (S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_907);
  if (S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_908);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_909);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_908);
  if(S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_907);
}
//----------start of state S_209-----
void S_907()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(907);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT) && !(S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT))
    FSM1.transit(S_906);
}
//----------start of state S_908-----
void S_908()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(908);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)&& !(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK))
    FSM1.transit(S_906);
}
//----------start of state S_909-----
void S_909()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(909);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_910);
}
//----------start of state S_910-----
void S_910()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(910);
    MotorL.setSpeed(215); MotorR.setSpeed(-175);
  }
  if(FSM1.getTime()>400)
    FSM1.transit(S_911);
}
//----------start of state S_911-----
void S_911()
{
  if(FSM1.doTask())
  {
    MotorL.setSpeed(0); MotorR.setSpeed(0);
    LEDDisplay.setValue(911);
    Servo1.setValue(0);
  }
  if(FSM1.getTime()>3000)
    FSM1.transit(S_912);
}
//----------start of state S_912-----
void S_912()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(912);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_921);
}
//----------start of state S_921-----new
void S_921()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(921);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_922);
}
//----------start of state S_922-----new
void S_922()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(922);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_913);
}
//----------start of state S_913-----
void S_913()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(913);
    MotorL.setSpeed(-130); MotorR.setSpeed(100);
  }
  if(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_914);
}
//----------start of state S_914-----
void S_914()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(914);
    Servo1.setValue(50);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_100);
}
//----------start of state S_203-----
void S_203()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(203);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_205);
}
//----------start of state S_205-----
void S_205()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(205);
    MotorL.setSpeed(130); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>500 || S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_201);
}
//----------start of state S_204-----
void S_204()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(204);
    MotorL.setSpeed(-100); MotorR.setSpeed(10);
  }
  if(FSM1.getTime()>350)
    FSM1.transit(S_201);
}
//----------start of state S_201-----
void S_201()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(201);
    MotorL.setSpeed(-80);
    MotorR.setSpeed(100);
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT && FSM1.getTime()>300)
    FSM1.transit(S_300);
}
//----------start of state S_300-----
void S_300()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(300);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(175);MotorR.setSpeed(120);
    }
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_301);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_302);
  if (S1.getHiLow() == BLK)
    FSM1.transit(S_303);
}
//----------start of state S_301-----
void S_301()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(301);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_300);
}
//----------start of state S_302-----
void S_302()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(302);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK))
    FSM1.transit(S_300);
}
//----------start of state S_303-----
void S_303()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(303);
    MotorL.setSpeed(0);
    MotorR.setSpeed(0);
  }
  if (FSM1.getTime() > 500)
    FSM1.transit(S_305);
}
//----------start of state S_304----- (NU)
void S_304()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(304);
    MotorL.setSpeed(-150);
    MotorR.setSpeed(-100);
  }
  if (S1.getHiLow() == WHT)
    FSM1.transit(S_305);
}
//----------start of state S_305-----
void S_305()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(305);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_306);
}
//----------start of state S_306-----
void S_306()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(306);
    MotorL.setSpeed(0); MotorR.setSpeed(-120);
  }
  if(FSM1.getTime()>350)
    FSM1.transit(S_307);
}
//----------start of state S_307-----
void S_307()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(307);
    MotorL.setSpeed(0); MotorR.setSpeed(0); 
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_320);
}
//----------start of state S_320-----
void S_320()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(320);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(Sonic.getDistance()<15)
    FSM1.transit(S_328);
  if(FSM1.getTime()>1000 &&!(Sonic.getDistance()<15))
    FSM1.transit(S_321);
}
//----------start of state S_321-----
void S_321()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(321);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_322);
}
//----------start of state S_322-----
void S_322()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(322);
    MotorL.setSpeed(0); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>100 && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_323);
}
//----------start of state S_323-----
void S_323()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(323);
    Servo1.setValue(30);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_324);
}
//----------start of state S_324-----
void S_324()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(324);
    MotorL.setSpeed(215); MotorR.setSpeed(170);
  }
  if(FSM1.getTime()>250 && S1.getHiLow() == WHT)
    FSM1.transit(S_325);
}
//----------start of state S_325-----
void S_325()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(325);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_330);
}
//----------start of state S_335-----
void S_335()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(335);
    MotorL.setSpeed(130); MotorR.setSpeed(80);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_336);
}
//----------start of state S_336-----
void S_336()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(336);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_400);
}
//----------start of state S_330-----(new)
void S_330()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(330);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(215);
      MotorR.setSpeed(150);
    }
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_331);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_332);
  if((S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT) || (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == BLK))
    FSM1.transit(S_333);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_332);
}
//----------start of state S_331-----
void S_331()
{

  if (FSM1.doTask())
  {
    LEDDisplay.setValue(331);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_330);
}
//----------start of state S_332-----
void S_332()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(332);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK) && !(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK) && !(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK))
    FSM1.transit(S_330);
}
//----------start of state S_333-----(FSM Req)
void S_333()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(333);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_339);
}
//----------start of state S_339-----
void S_339()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(339);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>150)
    FSM1.transit(S_334);
}
//----------start of state S_334-----
void S_334()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(334);
    MotorL.setSpeed(130); MotorR.setSpeed(-10);
  }
  if(FSM1.getTime()>300 && !(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT))
    FSM1.transit(S_337);
}
//----------start of state S_337-----
void S_337()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(337);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>150)
    FSM1.transit(S_338);
}
//----------start of state S_338-----
void S_338()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(338);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_400);
}
//----------start of state S_308-----
void S_308()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(308);
    MotorL.setSpeed(-100); MotorR.setSpeed(10);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_319);
}
//----------start of state S_319-----
void S_319()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(319);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_309);
}
//----------start of state S_328-----
void S_328()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(328);
    MotorL.setSpeed(100); MotorR.setSpeed(80);
  }
  if(FSM1.getTime()>150)
    FSM1.transit(S_329);
}
//----------start of state S_329-----
void S_329()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(329);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_309);
}
//----------start of state S_309-----
void S_309()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(309);
    Servo1.setValue(120);
  }
  if(FSM1.getTime()>1500)
    FSM1.transit(S_310);
}
//----------start of state S_310-----
void S_310()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(310);
    Servo1.setValue(50);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_311);
}
//----------start of state S_311-----
void S_311()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(311);
    MotorL.setSpeed(-150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_312);
}
//----------start of state S_312-----
void S_312()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(312);
    MotorL.setSpeed(130); MotorR.setSpeed(-100); 
  }   
  if(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_313);
}
//----------start of state S_313-----
void S_313()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(313);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_314);
}
//----------start of state S_314-----
void S_314()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(314);
    MotorL.setSpeed(150); MotorR.setSpeed(-100);
  }
  if(FSM1.getTime()>300)
    FSM1.transit(S_315);
}
//----------start of state S_315-----
void S_315()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(315);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_316);
}
//----------start of state S_316-----
void S_316()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(316);
    MotorL.setSpeed(120); MotorR.setSpeed(0);
  }
  if(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT || FSM1.getTime()>200)
    FSM1.transit(S_317);
}
//----------start of state S_317-----
void S_317()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(317);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_906);
}
//----------start of state S_318-----
void S_318()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(318);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
}
//----------start of state S_326-----
void S_326()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(326);
    MotorL.setSpeed(175); MotorR.setSpeed(120);
  }
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_327);
}
//----------start of state S_327-----
void S_327()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(327);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
}
//----------start of state S_400-----
void S_400()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(400);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(175);
      MotorR.setSpeed(120);
    }
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_401);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_402);
  if (S1.getHiLow() == BLK)
    FSM1.transit(S_403);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_413);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_402);
}
//----------start of state S_401-----
void S_401()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(401);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_400);
}
//----------start of state S_402-----
void S_402()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(302);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK) && !(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK))
    FSM1.transit(S_400);
}
//----------start of state S_403-----
void S_403()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(403);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_404);
}
//----------start of state S_404-----
void S_404()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(404);
    MotorL.setSpeed(-175); MotorR.setSpeed(-120);
  }
  if(FSM1.getTime()>350)
    FSM1.transit(S_405);
}
//----------start of state S_405-----
void S_405()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(405);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_406);
}
//----------start of state S_406-----
void S_406()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(406);
    MotorL.setSpeed(0); MotorR.setSpeed(-100);
  }
  if(FSM1.getTime()>225)
    FSM1.transit(S_407);
}
//----------start of state S_407-----
void S_407()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(407);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(Sonic.getDistance()<15)
    FSM1.transit(S_412);
  if(FSM1.getTime()>1000 && !(Sonic.getDistance()<15))
    FSM1.transit(S_411);
}
//----------start of state S_412-----
void S_412()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(412);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_417);
}
//----------start of state S_417-----
void S_417()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(417);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_418);
}
//----------start of state S_418-----
void S_418()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(418);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_408);
}
//----------start of state S_408-----
void S_408()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(408);
    Servo1.setValue(120);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_409);
}
//----------start of state S_409-----
void S_409()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(409);
    Servo1.setValue(50);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_410);
}
//----------start of state S_410-----
void S_410()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(410);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_415);
}
//----------start of state S_411-----
void S_411()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(411);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_419);
}
//----------start of state S_419-----
void S_419()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(419);
    MotorL.setSpeed(0); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>100 && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_420);
}
//----------start of state S_420-----
void S_420()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(420);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_421);
}
//----------start of state S_421-----
void S_421()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(421);
    MotorL.setSpeed(130); MotorR.setSpeed(80);
  }
  if(FSM1.getTime()>800 && S1.getHiLow() == WHT)
    FSM1.transit(S_422);
}
//----------start of state S_422-----
void S_422()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(422);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_500);
}
//----------start of state S_413-----
void S_413()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(413);
    MotorL.setSpeed(150); MotorR.setSpeed(-50);
  }
  if(FSM1.getTime()>375 && S1.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_414);
}
//----------start of state S_414-----
void S_414()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(414);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_400);
}
//----------start of state S_415-----
void S_415()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(415);
    MotorL.setSpeed(100); MotorR.setSpeed(-100);
  }
  if(FSM1.getTime()>300 && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_416);
}
//----------start of state S_416-----
void S_416()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(416);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_490);
}
//----------start of state S_490-----
void S_490()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(490);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(130);
      MotorR.setSpeed(80);
    }
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_491);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_492);
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_493);
}
//----------start of state S_491-----
void S_491()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(491);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_490);
}
//----------start of state S_492-----
void S_492()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(492);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK))
    FSM1.transit(S_490);
}
//----------start of state S_493-----
void S_493()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(493);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_494);
}
//----------start of state S_494-----
void S_494()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(494);
    MotorL.setSpeed(100); MotorR.setSpeed(-100);
  }
  if(FSM1.getTime()>300)
    FSM1.transit(S_495);
}
//----------start of state S_495-----
void S_495()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(495);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_496);
}
//----------start of state S_496-----
void S_496()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(496);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_497);
}
//----------start of state S_497-----
void S_497()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(497);
    MotorL.setSpeed(0); MotorR.setSpeed(-150);
  }
  if(FSM1.getTime()>350)
    FSM1.transit(S_498);
}
//----------start of state S_498-----
void S_498()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(498);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_499);
}
//----------start of state S_480-----
void S_480()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(480);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>250)
    FSM1.transit(S_481);
}
//----------start of state S_481-----
void S_481()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(481);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_499);
}
//----------start of state S_499-----
void S_499()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(499);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_483);
}
//----------start of state S_483-----
void S_483()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(483);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>300)
    FSM1.transit(S_484);
}
//----------start of state S_484-----
void S_484()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(484);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>500 || S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_485);
}
//----------start of state S_485-----
void S_485()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(485);
    MotorL.setSpeed(0); MotorR.setSpeed(0); 
  }
  if(FSM1.getTime()>300)
    FSM1.transit(S_906);
}
//----------start of state S_500-----
void S_500()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(500);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(175);MotorR.setSpeed(120);
    }
  }
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_501);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_502);
  if (S1.getHiLow() == BLK)
    FSM1.transit(S_503);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_502);
  if(S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_501);
}
//----------start of state S_501-----
void S_501()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(301);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT) && !(S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT))
    FSM1.transit(S_500);
}
//----------start of state S_502-----
void S_502()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(302);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK) && !(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK))
    FSM1.transit(S_500);
}
//----------start of state S_503-----
void S_503()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(503);
    Servo1.setValue(50);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_504);
}
//----------start of state S_504-----
void S_504()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(504);
    MotorL.setSpeed(-175); MotorR.setSpeed(-120); 
  }
  if(FSM1.getTime()>350)
    FSM1.transit(S_505);
}
//----------start of state S_505-----
void S_505()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(505);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_506);
}
//----------start of state S_506-----
void S_506()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(506);
    MotorL.setSpeed(0); MotorR.setSpeed(-130);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_507);
}
//----------start of state S_407-----
void S_507()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(507);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(Sonic.getDistance()<15)
    FSM1.transit(S_508);
  if(FSM1.getTime()>1000 && !(Sonic.getDistance()<15))
    FSM1.transit(S_599);
}
//----------start of state S_508-----
void S_508()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(508);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>250)
    FSM1.transit(S_509);
}
//----------start of state S_509-----
void S_509()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(509);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_510);
}
//----------start of state S_510-----
void S_510()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(510);
    Servo1.setValue(120);
  }
  if(FSM1.getTime()>1500)
    FSM1.transit(S_511);
}
//----------start of state S_511-----
void S_511()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(511);
    Servo1.setValue(50);
  }
  if(FSM1.getTime()>1000)
    FSM1.transit(S_516);
}
//----------start of state S_516-----
void S_516()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(516);
    MotorL.setSpeed(120); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_512);
}
//----------start of state S_512-----
void S_512()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(512);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>100)
    FSM1.transit(S_514);
}
//----------start of state S_514-----
void S_514()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(514);
    MotorL.setSpeed(0); MotorR.setSpeed(-120);
  }
  if(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT && FSM1.getTime()>200)
    FSM1.transit(S_515);
}
//----------start of state S_515-----
void S_515()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(515);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>400)
    FSM1.transit(S_600);
}
//----------start of state S_600-----
void S_600()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(600);
    while (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    {
      MotorL.setSpeed(175);
      MotorR.setSpeed(120);
    }
  }
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_603);
  if (S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_601);
  if (S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK)
    FSM1.transit(S_602);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK)
    FSM1.transit(S_602);
  if(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT)
    FSM1.transit(S_602);
  if(S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT)
    FSM1.transit(S_601);
}
//----------start of state S_601-----
void S_601()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(601);
    MotorL.setSpeed(0);
    MotorR.setSpeed(100);
  }
  if (!(S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == WHT) && !(S1.getHiLow() == WHT && S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == WHT))
    FSM1.transit(S_600);
}
//----------start of state S_602-----
void S_602()
{
  if (FSM1.doTask())
  {
    LEDDisplay.setValue(602);
    MotorL.setSpeed(150);
    MotorR.setSpeed(0);
  }
  if (!(S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == BLK) && !(S2.getHiLow() == WHT && S3.getHiLow() == WHT && S4.getHiLow() == BLK) && !(S1.getHiLow() == WHT && S2.getHiLow() == WHT && S3.getHiLow() == BLK && S4.getHiLow() == WHT))
    FSM1.transit(S_600);
}
//----------start of state S_603-----
void S_603()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(603);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_606);
}
//----------start of state S_606-----
void S_606()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(606);
    MotorL.setSpeed(150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_608);
}
//----------start of state S_608-----
void S_608()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(608);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_607);
}
// //----------start of state S_607-----
void S_607()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(607);
    MotorL.setSpeed(-10); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200 || (S1.getHiLow() == BLK && S2.getHiLow() == BLK && S3.getHiLow() == BLK && S4.getHiLow() == BLK))
    FSM1.transit(S_609);
}
//----------start of state S_609-----
void S_609()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(608);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500) 
    FSM1.transit(S_610);
}
//----------start of state S_610-----
void S_610()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(610);
    MotorL.setSpeed(-150); MotorR.setSpeed(100);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_611);
}
//----------start of state S_611-----
void S_611()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(611);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>200)
    FSM1.transit(S_612);
}
//----------start of state S_612-----
void S_612()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(612);
    MotorL.setSpeed(-120); MotorR.setSpeed(80);
  }
  if((S2.getHiLow() == BLK && S3.getHiLow() == WHT && S4.getHiLow() == BLK) || FSM1.getTime()>600)
    FSM1.transit(S_613);
}
//----------start of state S_613-----
void S_613()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(613);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
  if(FSM1.getTime()>500)
    FSM1.transit(S_490);
}
//----------start of state S_599-----
void S_599()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(599);
    MotorL.setSpeed(0); MotorR.setSpeed(0);
  }
}