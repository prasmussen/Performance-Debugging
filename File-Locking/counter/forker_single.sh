#!/bin/bash

(./counter serial.count&);
echo Forks complete
sleep 60
killall ./counter

