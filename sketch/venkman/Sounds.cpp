#include <Arduino_FreeRTOS.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "Sounds.h"

SoftwareSerial soundSerial(2, 3);
int endFireSampleIndex = 2;
int firingSampleIndex = 3;
int humSampleIndex = 4;
int idleSampleIndex = 5;
int shutDownSampleIndex = 6;
int armingSampleIndex = 7;

Sounds::Sounds() {
  soundSerial.begin (9600);
  mp3_set_serial (soundSerial);      //set Serial for DFPlayer-mini mp3 module 
  delay(1);                     // delay 1ms to set volume
  mp3_set_volume(20);          // value 0~30
  pinMode(13, OUTPUT);
}

void Sounds::onStateChanged(PackState newState) {
  //mp3_stop();
  
  if (newState == initial || newState == poweredOn) {
    mp3_single_loop(true);
    mp3_play(humSampleIndex);
  } else if (newState == generatorOn || newState == armed) {
    mp3_single_loop(true);
    mp3_play(idleSampleIndex);
  } else if (newState == arming) {
    mp3_single_loop(true);
    mp3_play (armingSampleIndex);
  } else if (newState == firing) {
    mp3_single_loop(false);
    mp3_play(firingSampleIndex);
  } else if (newState == endingFiring) {
    mp3_single_loop(true);
    mp3_play (endFireSampleIndex);
  } else if (newState == shutDown) {
    mp3_single_loop(true);
    mp3_play(shutDownSampleIndex);
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
