#!/bin/bash

rm -f para*.count

for i in {1..10} ;
do
    filename=para$i.count
    echo 0 > $filename
    (./counter $filename&);
done

echo Forks complete
sleep 60
killall ./counter

