#!/bin/bash

#ls ./sift/sift/*.sift > liste_test_sift

i=0

>samples.txt

while read file
do
	while read line
	do
	
	get=$((i % 150))
	
	if [ "$get" -eq 0 ] && [ "$i" -ge 3 ]
	then
		echo $line|sed 's/<.*>; /''/g'| tr -d ";" >> samples.txt
	fi
	i=$((i+1))
	done < $file
	

done < liste_test_sift


