#!/bin/bash

nom=$(echo `basename $1` |cut -f1 -d.)
echo $nom
./colorDescriptor --descriptor sift $1 --output $nom.sift
sed -n '4,$p' $nom.sift | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > ./trav.sift
R --slave --no-save --no-restore --no-environ --args centers256.txt 256 ./trav.sift ./$nom.sift < ./scriptR/1nn.R
\rm -f ./trav.sift
