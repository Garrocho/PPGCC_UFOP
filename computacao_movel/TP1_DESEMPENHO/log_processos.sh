#!/bin/bash

if [ "$1" = "" ]; then
    echo "./log_processos.sh <nome_processo>"
fi

if [ "$1" != "" ]; then
   ps aux | grep chrome | sed '2,$ d' | awk '{print $3,";",$4}'
fi
#ps aux | grep chrome | sed '2,$ d' | awk '{print $3,";",$4}'
