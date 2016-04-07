#!/bin/bash

# Script to search a whole bunch of different graphs
# Copyright (C) 2006 Valentin Koch and Michael Henderson

aip2p=~/bin/aip2p

if [ ! -f $aip2p ];
then
    echo "error: could not find " aip2p " binary"
    exit 1
fi

if [ ! -n "$1" ]
then
    echo "Usage: search_graphs N [directory]"
    exit 1
fi 

directory=${2:="."}

for file in $directory/*.dimacs
do
  $aip2p -i $1 -s -1 -g -1 $file
done
