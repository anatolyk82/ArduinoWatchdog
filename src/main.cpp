#include <Arduino.h>
#include "config.h"

unsigned long previous_time = 0;
unsigned long uptime = 0;

void interruptHandler() {
  Serial.println("Reset signal received. Start counting time again.");
  previous_time = millis();
}

void setup() {
  Serial.begin(115200);
  /* Setup the relay pin as output */
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, !RELAY_RESET_LEVEL);

  /* Wait for a command to start */
  pinMode(START_PIN, INPUT);
  Serial.print("Watchdog is ready. Wait for the start signal at the pin ");
  Serial.println(START_PIN);
  while (digitalRead(START_PIN) != START_LEVEL) { }
  previous_time = millis();

  Serial.println("Watchdog starts");

  /*
   * RPi must switch level ever time in an interval smaller than CHECK_INTERVAL
   * To be safe in this, RPi must only switch the input level.
   * For example if the level was HIGH, the next time PRi must set LOW and the next
   * time after that it must switch it to HIGH again.
   */
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), interruptHandler, CHANGE);
}

void loop() {
  uint64_t up = millis();
  if (up < uptime) { //the value has overflowed
    previous_time = up;
  }
  uptime = up;
  unsigned long delta = uptime - previous_time;
  if (delta > CHECK_INTERVAL) {
    Serial.println("Reset the monitored device");
    digitalWrite(RELAY_PIN, RELAY_RESET_LEVEL);
    delay(1000);
    digitalWrite(RELAY_PIN, !RELAY_RESET_LEVEL);

    /* Wait for the next start */
    Serial.println("Watchdog is ready. Wait for the start signal");
    while (digitalRead(START_PIN) != START_LEVEL) { }
    previous_time = millis();
    Serial.println("Watchdog starts");
  }
}
