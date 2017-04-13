#!/bin/bash

./colorDescriptor --descriptor sift $1 --output `basename $1`.sift
sed -n '4,$p' `basename $1`.sift | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > ./trav.sift
R --slave --no-save --no-restore --no-environ --args centers256.txt 256 ./trav.sift ./`basename $1`.sift < 1nn.R
\rm -f ./trav.sift
