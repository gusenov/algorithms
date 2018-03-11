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




if [ "$a" -gt "$b" ]; then  # first comparison

    if [ "$a" -gt "$c" ]; then  # second comparison

        if [ "$a" -gt "$d" ]; then  # third comparison
            echo $a
        else
            echo $d
        fi

    else

        if [ "$c" -gt "$d" ]; then  # third comparison
            echo $c
        else
            echo $d
        fi

    fi

else

    if [ "$b" -gt "$c" ]; then  # second comparison

        if [ "$b" -gt "$d" ]; then  # third comparison
            echo $b
        else
            echo $d
        fi

    else

        if [ "$c" -gt "$d" ]; then  # third comparison
            echo $c
        else
            echo $d
        fi

    fi

fi
