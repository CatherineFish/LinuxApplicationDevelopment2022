#!/bin/bash


y=0
flag="0"
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
		if [[ "$flag" == "1" && "$elem" == "08" ]]
		then 
			flag=0
		else
			if [[ "$flag" == "1" && "$elem" != "08" ]]
			then	
				flag=0
				echo -e "$y-$x-5f"
				x=$((x + 1))
				echo -e "$y-$x-$elem"
				x=$((x + 1))
			else
				if [[ "$flag" == "0" && "$elem" == "01" ]]
				then
					x=$((x + 1))
				else
					if [[ "$elem" != "01" && "$flag" == "0" ]]
					then
						if [  "$elem" == "5f" ]
						then
							flag="1" 
						else
							echo -e "$y-$x-$elem"
							x=$((x + 1))
						fi	
					fi
				fi	
			fi
		fi
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