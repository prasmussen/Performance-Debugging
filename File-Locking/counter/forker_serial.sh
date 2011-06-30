#!/bin/bash


for i in {1..10} ;
do
    filename=serial.count
    echo 0 > $filename
    (./counter $filename &);
done

echo Forks complete
sleep 60
killall ./counter

