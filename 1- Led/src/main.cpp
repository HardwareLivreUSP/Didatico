#include <Arduino.h>

int tempo = 1000;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH); // Escreve 5V
  delay(tempo);
  digitalWrite(LED_BUILTIN, LOW); // Escreve 0V
  delay(tempo);
}