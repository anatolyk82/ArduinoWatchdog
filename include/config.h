#ifndef PRI_ARDUINO_WATCHDOG
#define PRI_ARDUINO_WATCHDOG

#define RELAY_PIN 4             //Defines which pin has a connected relay to reset power to RPI
#define RELAY_RESET_LEVEL HIGH  //Defines which signal level has to be written to the pin to switch the relay

#define START_PIN 7             //Defines which pin will be used as a start ping to start watching RPi
#define START_LEVEL HIGH        //Defines which level the watchdog expects to start watching RPi

#define CHECK_INTERVAL 300000   //5 min = 5*60*1000 msec = 300000

/*
 * Only certain pins can be useable for interrupts
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 */
#define RESET_PIN 2

#endif //PRI_ARDUINO_WATCHDOG
