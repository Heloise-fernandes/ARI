#!/bin/bash

#ls ../sift/*.sift > ./histogrammes/liste_test_sift

i=0



>./histogrammes/samples.txt

while read file
do
	i=0
	while read line
	do
	
	get=$((i % 150))
	
	if [ "$get" -eq 0 ] && [ "$i" -ge 3 ]
	then
		echo $line|sed 's/<.*>; /''/g'| tr -d ";" >> ./histogrammes/samples.txt
	fi
	i=$((i+1))
	done < $file
	

done < ./histogrammes/liste_test_sift


