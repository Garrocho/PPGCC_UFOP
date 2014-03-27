#!/bin/bash

if [ "$1" = "" ]; then
    echo "./log_processos.sh <nome_processo>"
fi

if [ "$1" != "" ]; then
   echo "CPU e MEM do Processo $1"
   ps aux | grep chrome | awk '{print $3,";",$4}'
fi
