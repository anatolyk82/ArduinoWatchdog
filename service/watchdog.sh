#!/usr/bin/env bash

LOGFILE="/mnt/ssd/watchdog.log"
RESET_INTERVAL=30 #seconds
RESET_GPIO=21 #pin40
GPIO_VALUE=0

START_GPIO=20 #pin38
START_LEVEL=1

who_am_i = `whoami`

if [ $who_am_i != 'root' ]
then
  echo "The script must be run as root" > $LOGFILE
  exit 1
fi

echo "Export reset pin $RESET_GPIO to userspace" > $LOGFILE
echo $RESET_GPIO > /sys/class/gpio/export
sleep 1

echo "Set the reset pin $RESET_GPIO as an output" > $LOGFILE
echo "out" > /sys/class/gpio/gpio$RESET_GPIO/direction
sleep 1
echo $GPIO_VALUE > /sys/class/gpio/gpio$RESET_GPIO/value

echo "Export the start pin $START_GPIO to userspace" > $LOGFILE
echo $START_GPIO > /sys/class/gpio/export
sleep 1

echo "Set the start pin $START_GPIO as an output" > $LOGFILE
echo "out" > /sys/class/gpio/gpio$START_GPIO/direction
sleep 1
echo 0 > /sys/class/gpio/gpio$START_GPIO/value

echo "Pause 2 minutes before starting the watchdog" > $LOGFILE
sleep 120

echo "Send the start signal" > $LOGFILE
echo 1 > /sys/class/gpio/gpio$START_GPIO/value

while true
do
  GPIO_VALUE=$((1-GPIO_VALUE))
  echo $GPIO_VALUE > /sys/class/gpio/gpio$RESET_GPIO/value
  sleep $RESET_INTERVAL
done
