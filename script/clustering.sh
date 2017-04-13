#!/bin/bash

R --slave --no-save --no-restore --no-environ --args ./samples.txt 256 ./centers256.txt 100 < kmeans_clustering.R
