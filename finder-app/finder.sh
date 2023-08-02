#!/bin/bash

filesdir=$1
searchstr=$2

if [ $# -lt 2 ]
then
    echo one or more parameters were not specified
    exit 1
elif [ ! -d $filesdir ]
then
    echo directory does not exist
    exit 1
fi

#X=ls | wc -l
X=$(find $filesdir -type f | wc -l)
#FILES=$(find $filesdir -type f)
Y=$(grep -r -c $searchstr $filesdir | awk -F ':' '{ sum += $2 } END { print sum }')
#echo $X/$filesdir
echo The number of files are $X and the number of matching lines are $Y
exit 0
#echo $filesdir $searchstr