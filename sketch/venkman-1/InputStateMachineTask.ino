const int backPin = 8;
const int nextPin = 9;
const int stopPin = 10;
const int ledPin = 12;
bool backPushed = false;
bool nextPushed = false;
bool stopPushed = false;

void inputStateMachineTask(void *pvParameters) {
  inputStateMachineTaskSetup();
  inputStateMachineTaskLoop();
}

void inputStateMachineTaskSetup() {
  pinMode(backPin, INPUT);
  pinMode(nextPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin (9600);
  mp3_set_serial (Serial);      //set Serial for DFPlayer-mini mp3 module 
  delay(1);                     // delay 1ms to set volume
  mp3_set_volume(18);          // value 0~30
  mp3_play(0);
}

void inputStateMachineTaskLoop() {
  for (;;) {
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
  
    const int stop = digitalRead(stopPin) == HIGH;
    if (stop && !stopPushed) {
      stopPushed = true;
      mp3_stop();
    } else if (!stop) {
      stopPushed = false;
    }
  
    digitalWrite(ledPin, next || back || stop ? HIGH : LOW);
  }
}
