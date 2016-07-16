/*
 *  Copyright:  DFRobot
 *  name:       DFPlayer_Mini_Mp3 sample code
 *  Author:     lisper <lisper.li@dfrobot.com>
 *  Date:       2014-05-30
 *  Description:    sample code for DFPlayer Mini, this code is test on Uno
 *          note: mp3 file must put into mp3 folder in your tf card
 */
 
 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

const int backPin = 8;
const int nextPin = 9;
const int ledPin = 13;
 
void setup () {
  pinMode(backPin, INPUT);
  pinMode(nextPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
    Serial.begin (9600);
    mp3_set_serial (Serial);      //set Serial for DFPlayer-mini mp3 module 
    delay(1);                     // delay 1ms to set volume
    mp3_set_volume(12);          // value 0~30
    mp3_play(1);
}

bool backPushed = false;
bool nextPushed = false;
 
void loop () {
  const int back = digitalRead(backPin) == HIGH;
    if (back && !backPushed) {
      backPushed = true;
      mp3_prev();
    } else if (!back) {
      backPushed = false;
    }

    const int next= digitalRead(nextPin) == HIGH;
    if (next && !nextPushed) {
      nextPushed = true;
      mp3_next();
    } else if (!next) {
      nextPushed = false;
    }

    digitalWrite(ledPin, nextPushed || backPushed ? HIGH : LOW);
}
 
/*
   mp3_play ();     //start play
   mp3_play (5);    //play "mp3/0005.mp3"
   mp3_next ();     //play next 
   mp3_prev ();     //play previous
   mp3_set_volume (uint16_t volume);    //0~30
   mp3_set_EQ ();   //0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_get_state ();   //send get state command
   void mp3_get_volume (); 
   void mp3_get_u_sum (); 
   void mp3_get_tf_sum (); 
   void mp3_get_flash_sum (); 
   void mp3_get_tf_current (); 
   void mp3_get_u_current (); 
   void mp3_get_flash_current (); 
   void mp3_single_loop (boolean state);    //set single loop 
   void mp3_DAC (boolean state); 
   void mp3_random_play (); 
 */
