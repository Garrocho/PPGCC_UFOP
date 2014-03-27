ps aux | grep chrome | sed '2,$ d' | awk '{print $3,";",$4}'
