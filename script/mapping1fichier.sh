#!/bin/sh
echo "Traitrement de $f"
sed -n '4,$p' $1 | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > ./trav.sift
R --slave --no-save --no-restore --no-environ --args ../histogrammes/centers256.txt 256 ./trav.sift ./res.sift < 1nn.R

\rm -f ./trav.sift


