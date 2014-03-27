#!/bin/bash

if [ "$1" = "" ]; then
    echo "./log_processos.sh <nome_processo>"
fi

if [ "$1" != "" ]; then
   echo "CPU e MEM do Processo $1"
   ps aux | grep $1 | awk '{print $3,";",$4}'
   echo "BATERIA Utilizada pelo Processo $1"
   cat bateria.csv | grep /opt/google/chrome/chrome | grep /s
fi
