int cyclotronLedPin[] = {3,5,6,9};
int cyclotronLedBrightness[] = {0, 0, 0, 0};
int cyclotronLedState[]= {1,0,0,0}; // 0 = off, 1 = turning on, 2 = on, 3 = turning off
int cyclotronLedOnTime = 1000;  // ms
int delayTime = 30; // ms

void setup() {
  for (int i = 0; i < 4; i ++) {
    pinMode(cyclotronLedPin[i], OUTPUT);
  }
  //Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i ++) {
    updateCyclotronLedState(i);
    updateCyclotronLedBrightness(i);
  }

  delay(delayTime);
}

int getFadeDeltaForCyclotronLed(int index) {
  int state = cyclotronLedState[index];
  int currentBrightness = cyclotronLedBrightness[index];
  
  if (state == 0 && currentBrightness == 0) return 0;
  if (state == 1 && currentBrightness < 255) return 76;
  if (state == 1 && currentBrightness >= 255) return 0;
  if (state == 0 && currentBrightness > 0) return -38;
  
  return 0; // should never be reached ;-)
}

void updateCyclotronLedBrightness(int index) {
  cyclotronLedBrightness[index] = constrain(cyclotronLedBrightness[index] + getFadeDeltaForCyclotronLed(index), 0, 255);

  analogWrite(cyclotronLedPin[index], cyclotronLedBrightness[index]);
}

void updateCyclotronLedState(int index) {
  int ledThatShouldBeOn = (millis() / cyclotronLedOnTime) % 4;
  bool shouldThisLedBeOn = ledThatShouldBeOn == index;
  
  if (cyclotronLedState[index] == 0 && shouldThisLedBeOn) cyclotronLedState[index] = 1;
  if (cyclotronLedState[index] == 1 && !shouldThisLedBeOn) cyclotronLedState[index] = 0;
}

