const int cyclotronDelay = 250;
int cyclotronStep = -1;

void cyclotronTask(void *pvParameters) {
  for (;;) cyclotronLoop();
}

void cyclotronLoop() {
  cyclotronStep ++;
  if (cyclotronStep == 4) {
    cyclotronStep = 0;
  }

  setCyclotronMask(
    cyclotronStep == 0,
    cyclotronStep == 1,
    cyclotronStep == 2,
    cyclotronStep == 3
  );
  
  vTaskDelay(cyclotronDelay / portTICK_PERIOD_MS);
}
