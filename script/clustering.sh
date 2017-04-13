#!/bin/bash

R --slave --no-save --no-restore --no-environ --args ./histogrammes/samples.txt 256 ./histogrammes/centers256.txt 100 < ./scriptR/kmeans_clustering.R
