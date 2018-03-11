#!/bin/bash

for i in "$@"
do
case $i in
    -a=*|--a=*)
        a="${i#*=}"
        shift
        ;;
    -b=*|--b=*)
        b="${i#*=}"
        shift
        ;;
    -c=*|--c=*)
        c="${i#*=}"
        shift
        ;;
    -d=*|--d=*)
        d="${i#*=}"
        shift
        ;;
esac
done




largest=$a

if (( b > largest )); then  # first comparison
    largest=$b
fi

if (( c > largest )); then  # second comparison
    largest=$c
fi

if (( d > largest )); then  # third comparison
    largest=$d
fi

echo $largest
