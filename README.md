# ArduinoWatchdog

 The main idea of this project is to create an arduino based watchdog to monitor RPi. It requires an additional relay to trigger power on Raspberry Pi. The monitored Raspberry Pi must change a level at a certain pin on Arduino which works as the watchdog. This event must happend periodically during a certain period. If RPi cannot do it, the watchdog switches the relay and interrupts power for a short period to RPi which causes to restart RPi.
