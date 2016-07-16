const int cyclotronPin1 = 7;

bool lightMask[4];

void lightsTask(void *pvParameters) {
  for (int i = 0; i < 4; i ++) {
    pinMode(cyclotronPin1 - i, OUTPUT);
  }

  for (;;) lightsTaskLoop();
}

void lightsTaskLoop() {
  // TODO replace with shift register
  for (int i = 0; i < 4; i ++) {
    digitalWrite(cyclotronPin1 - i, lightMask[i]);
  }

  vTaskDelay(1 / portTICK_PERIOD_MS);
}

void setCyclotronMask(bool tl, bool tr, bool br, bool bl) {
  lightMask[0] = tl;
  lightMask[1] = tr;
  lightMask[2] = br;
  lightMask[3] = bl;
}

