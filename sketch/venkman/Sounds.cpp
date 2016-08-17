#include <Arduino_FreeRTOS.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "Sounds.h"

Sounds::Sounds() {
  idleSampleIndex = 5;
  humSampleIndex = 4;
  armingSampleIndex = 0;

//  Serial.begin (9600);
//  mp3_set_serial (Serial);      //set Serial for DFPlayer-mini mp3 module 
//  delay(1);                     // delay 1ms to set volume
//  mp3_set_volume(18);          // value 0~30
}

void Sounds::onStateChanged(PackState newState) {
  return;
  
  if (newState == invalidState) {
    mp3_stop();
  } else if (newState == poweredOn) {
    mp3_play(idleSampleIndex);
    mp3_single_loop(false);
  } else if (newState == generatorOn) {
    digitalWrite(12, HIGH);
    mp3_play(humSampleIndex);
    mp3_single_loop(false);
  } else if (newState == arming) {
    digitalWrite(12, LOW);
    mp3_play(armingSampleIndex);
    mp3_single_loop(true);
    //todo transition to armed
  } else if (newState == armed) {
    mp3_play(humSampleIndex);
    mp3_single_loop(false);
  } else {
    // unimplemented state
    mp3_stop();
  }
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
