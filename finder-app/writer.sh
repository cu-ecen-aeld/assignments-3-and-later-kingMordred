#!/bin/sh

writefile=$1
writestr=$2

if [ $# -lt 2 ]
then
    echo one or more parameters were not specified
    exit 1
elif [ ! -d $writefile ]
then
    mkdir -p "$(dirname "$writefile")" && touch "$writefile"
    #echo $writestr > $writefile
else
    echo file could not be created
    exit 1
fi

echo $writestr > $writefile
exit 0
