#!/bin/bash

# Script to create a whole bunch of different graphs
# Copyright (C) 2006 Valentin Koch and Michael Henderson

aip2p=~/bin/aip2p

if [ ! -f $aip2p ];
then
    echo "error: could not find " aip2p " binary"
    exit 1
fi

if [ ! -n "$1" ]
then
    echo "Usage: create_graphs N [directory]"
    exit 1
fi 

cycles=$1
directory=${2:="."}
let "total=$cycles*15"

echo "Creating $total graphs in $directory"

for ((i=1; i <= cycles ; i++))
do

  # create random graphs
  for nodes in 100 200 400 500 600 800 1000 2000
  do
    count=1
    for density in .1 .2 .4 .6 .8 1
    do
      $aip2p -t rand -n $nodes -e $density $directory/rand-$nodes-$count-$i.dimacs
      let "count += 1"
    done
  done
  $aip2p -t rand -n 5000 -e .1 $directory/rand-5000-$i.dimacs


  # create geometric graphs
  for nodes in 100 200 400 500 600 800 1000 2000
  do
    for density in 20 40 60 80 90 100
    do
      $aip2p -t geom -n $nodes -e $density $directory/geom-$nodes-$density-$i.dimacs
    done
  done
  $aip2p -t geom -n 5000 -e 20 $directory/geom-5000-$i.dimacs
  


  # create grid graphs
  for rows in 10 20 30 40 50 60 80 100
  do
    for cols in 10 20 30 40 50 60 80 100
    do
      echo $rows " x " $cols
      $aip2p -t grid -r $rows -c $cols $directory/grid-$rows'x'$cols-$i.dimacs
    done
  done
  $aip2p -t grid -r 100 -c 200 $directory/grid-100x200-$i.dimacs
  

done
