#!/bin/bash

teste=`ps axu | grep cliente.py | wc -l`;
#echo "$teste" >> /home/charles/Net-Opp/log.txt
if [ "$teste" != "1" ]; then
   echo "tem"
else
  echo "nao tem"
   /usr/bin/python /home/charles/workspace/MCC/DTN/cliente.py &
fi
