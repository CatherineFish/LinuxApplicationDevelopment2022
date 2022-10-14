#!/bin/bash


y=0
sleep_timer="0.05" 
for i in "$@" 
do
	sleep_timer="$i"
done
tput clear

tr [:blank:] "\001" |

while read -r line; 
do
	line=$(echo -n $line | od -v -A n -t x1)	
	size=$((${#line} - 1))
	x=0
	for elem in $line
	do
		if [ "$elem" != "01" ]
		then
			echo -e "$y-$x-$elem"
		fi
		x=$((x + 1))
	done
	y=$((y + 1))
done |

shuf |

while IFS=- read -r y x ch;
do
	tput cup $y $x
	echo -ne "\x$ch"
	sleep $sleep_timer
done 
tput cup $(tput lines) 0