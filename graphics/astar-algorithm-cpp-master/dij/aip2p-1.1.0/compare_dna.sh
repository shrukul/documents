#!/bin/bash
#
# Script to compare first 50 characters of DNA sequences
# in plain format
#
# Copyright (C) 2006 Valentin Koch and Michael Henderson

aip2p=`which aip2p`

if [ ! -f $aip2p ]
then
    echo "error: could not find " aip2p " binary"
    exit 1
fi

if [ ! -n "$1" ]
then
    echo "Usage: compare_dna [file]"
    exit 1
fi 

file=$1
gawk 'BEGIN{ FS = "\n"; RS = ">HLA" }
           { str1=substr($2,1,50); getline; system("aip2p -d -s " str1 " -g " substr($2,1,100) ) }' < "$file"
