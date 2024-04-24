/*!
 * @file fingerprintRegistration.ino
 * @brief Fingerprint Acquisition and Saving 
 * @n This module can be controlled by hardware serial or software serial 
 * @n Experiment Phenomenon：auto retrieve unregistered ID, collect fingerprint 3 times.  
 * @n           In collecting, set LED ring to breathing lighting in blue, and then to quick blink in yellow 3 times when completed 
 * @n           At last, save the fingerprint in an unregistered ID, the green LED lights up for 1s and turns off. 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
*/

#include <DFRobot_ID809.h>

#define COLLECT_NUMBER 3  //Fingerprint sampling times, can be set to 2-3

/*Use software serial when using UNO or NANO */
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
#else
    #define FPSerial Serial1
#endif

DFRobot_ID809 fingerprint;
//String desc;

void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Init FPSerial*/
  FPSerial.begin(115200);
  /*Take FPSerial as communication port of the module*/
  fingerprint.begin(FPSerial);
  /*Wait for Serial to open*/
  while(!Serial);
  /*Test whether the device can communicate properly with mainboard 
    Return true or false
    */
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    /*Get error code information*/
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    delay(1000);
  }

  Serial.println("1. Add Finger Print");
  Serial.println("2. Scan Finger Print");
  Serial.println("3. Delete Finger Print");
}

uint8_t ID,i,ret;

void loop(){

   Serial.println("Which would you like to do?");

  while (Serial.available() == 0) {
  }

  int menuChoice = Serial.parseInt();

  switch (menuChoice) {
    case 1:
        // temp sensor code goes here
        /*Get an unregistered ID for saving fingerprint 
      Return ID when succeeded 
      Return ERR_ID809 if failed 
    */
      if((ID = fingerprint.getEmptyID()) == ERR_ID809){
        while(1){
          /*Get error code information*/
          //desc = fingerprint.getErrorDescription();
          //Serial.println(desc);
          delay(1000);
        }
      }
      Serial.print("unresistered ID,ID=");
      Serial.println(ID);
      i = 0;   //Clear sampling times 
      /*Fingerprint sampling 3 times*/
      while(i < COLLECT_NUMBER){
        /*Set fingerprint LED ring mode, color, and number of blinks 
          Can be set as follows: 
          Parameter 1:<LEDMode>
          eBreathing   eFastBlink   eKeepsOn    eNormalClose
          eFadeIn      eFadeOut     eSlowBlink   
          Parameter 2:<LEDColor>
          eLEDGreen  eLEDRed      eLEDYellow   eLEDBlue
          eLEDCyan   eLEDMagenta  eLEDWhite
          Parameter 3:<Number of blinks> 0 represents blinking all the time 
          This parameter will only be valid in mode eBreathing, eFastBlink, eSlowBlink
        */
        fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
        Serial.print("The fingerprint sampling of the");
        Serial.print(i+1);
        Serial.println("(th) is being taken");
        Serial.println("Please press down your finger");
        /*Capture fingerprint image, 10s idle timeout, if timeout=0,Disable  the collection timeout function
          IF succeeded, return 0, otherwise, return ERR_ID809
        */
        if((fingerprint.collectionFingerprint(/*timeout = */10)) != ERR_ID809){
          /*Set fingerprint LED ring to quick blink in yellow 3 times */
          fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
          Serial.println("Sampling succeeds");
          i++;   //Sampling times +1
        }else{
          Serial.println("Sampling failed");
          /*Get error code information*/
          //desc = fingerprint.getErrorDescription();
          //Serial.println(desc);
        }
        Serial.println("Please release your finger");
        /*Wait for finger to release 
          Return 1 when finger is detected, otherwise return 0 
        */
        while(fingerprint.detectFinger());
      }

      /*Save fingerprint in an unregistered ID */
      if(fingerprint.storeFingerprint(/*Empty ID = */ID) != ERR_ID809){
        Serial.print("Saving succeed，ID=");
        Serial.println(ID);
        Serial.println("-----------------------------");
        /*Set fingerprint LED ring to always ON in green */
        fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
        delay(1000);
        /*Turn off fingerprint LED ring */
        fingerprint.ctrlLED(/*LEDMode = */fingerprint.eNormalClose, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
        delay(1000);
      }else{
        Serial.println("Saving failed");
        /*Get error code information*/
        //desc = fingerprint.getErrorDescription();
        //Serial.println(desc);
      }
      break;
    

    case 2:
          uint8_t ret = 0;
      /*Set fingerprint LED ring mode, color, and number of blinks
        Can be set as follows:
        Parameter 1:<LEDMode>
        eBreathing   eFastBlink   eKeepsOn    eNormalClose
        eFadeIn      eFadeOut     eSlowBlink   
        Parameter 2:<LEDColor>
        eLEDGreen  eLEDRed      eLEDYellow   eLEDBlue
        eLEDCyan   eLEDMagenta  eLEDWhite
        Parameter 3:<number of blinks> 0 represents blinking all the time
        This parameter will only be valid in mode eBreathing, eFastBlink, eSlowBlink
      */
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
      Serial.println("Please press down your finger");
      /*Capture fingerprint image, Disable the collection timeout function 
        If succeed return 0, otherwise return ERR_ID809
      */
      if((fingerprint.collectionFingerprint(/*timeout=*/0)) != ERR_ID809){
        /*Set fingerprint LED ring to quick blink in yellow 3 times*/
        fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
        Serial.println("Capturing succeeds");
          Serial.println("Please release your finger");
        /*Wait for finger to release
          Return 1 when finger is detected, otherwise return 0 
        */
        while(fingerprint.detectFinger());

        /*Compare the captured fingerprint with all the fingerprints in the fingerprint library 
          Return fingerprint ID(1-80) if succeed, return 0 when failed 
        */
        ret = fingerprint.search();
        /*Compare the captured fingerprint with a fingerprint of specific ID 
          Return fingerprint ID(1-80) if succeed, return 0 when failed 
        */
        //ret = fingerprint.verify(/*Fingerprint ID = */1);  
        if(ret != 0){
          /*Set fingerprint LED ring to always ON in green */
          fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
          Serial.print("Matching succeeds,ID=");
          Serial.println(ret);
        }else{
          /*Set fingerprint LED ring to always ON in red*/
          fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
          Serial.println("Matching fails");
        }
      }else{
        Serial.println("Capturing fails");
        /*Get error code information*/
        //desc = fingerprint.getErrorDescription();
        //Serial.println(desc);
      }
      Serial.println("-----------------------------");
      delay(1000); 

      break;

    default:
      Serial.println("Normal State");
  }
  
}  
