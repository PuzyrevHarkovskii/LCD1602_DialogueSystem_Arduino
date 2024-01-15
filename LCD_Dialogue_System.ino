#define _LCD_TYPE 1
#define BTN_PIN_1 3
#define BTN_PIN_2 4
#include <LCD_1602_RUS_ALL.h>
#include "GyverButton.h"

GButton butt1(BTN_PIN_1);
GButton butt2(BTN_PIN_2);

LCD_1602_RUS lcd(0x27, 16, 2);

bool isDisplayingMessage = false;

void displayMessage(const char* line1, const char* line2, int delayTime = 2000) {
  isDisplayingMessage = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(delayTime);
  isDisplayingMessage = false;
}

void setup() {
  Serial.begin(9600);

  butt1.setDebounce(50);  // Adjust debounce time if needed
  butt2.setDebounce(50);
}

void loop() {
  lcd.init();
  lcd.backlight();

  displayMessage("Реплика 1", "", 2000);
  displayMessage("", "Реплика 2", 1000);

  delay(1000);

  displayMessage("Первый вопрос", "1. Да     2. Нет");

  // Wait for button press
  while (!butt1.isSingle() && !butt2.isSingle()) {
    butt1.tick();
    butt2.tick();
    delay(50);  // Adjust the delay as needed
    Serial.println("Button 1: " + String(butt1.isSingle()) + " Button 2: " + String(butt2.isSingle()));
  }

  if (butt1.isSingle()) {
    displayMessage("Первый вариант", "");
  } else {
    displayMessage("Второй вариант", "");
  }

  // Сброс состояния кнопок перед следующим вопросом
  butt1.resetStates();
  butt2.resetStates();

  displayMessage("Второй вопрос", "1. Да     2. Нет");

  // Wait for button press
  while (!butt1.isSingle() && !butt2.isSingle()) {
    butt1.tick();
    butt2.tick();
    delay(50);  // Adjust the delay as needed
    Serial.println("Button 1: " + String(butt1.isSingle()) + " Button 2: " + String(butt2.isSingle()));
  }

  if (butt1.isSingle()) {
    displayMessage("Первый вариант-2", "");
  } else {
    displayMessage("Второй вариант-2", "");
  }

  // Сброс состояния кнопок перед следующим вопросом
  butt1.resetStates();
  butt2.resetStates();

  displayMessage("Конец диалога", "", 2000);
}
