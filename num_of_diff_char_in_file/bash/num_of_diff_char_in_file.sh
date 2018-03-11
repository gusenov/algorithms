#!/bin/bash

for i in "$@"
do
case $i in
    -f=*|--file=*)
        file="${i#*=}"
        shift
        ;;
esac
done




for ((i=0;i<256;i++)); do  # for all 256 characters do
    counter[$i]=0  # assign zero to the counter
done  # end for

while read -n1 character; do  # while there are more characters in the file do
                              #     get the next character

    ((counter[$(LC_CTYPE=C printf '%d' "'$character")]++))  # increment the counter for this character by one

# end while
done < $file




echo ${counter[@]}

for ((i=0;i<256;i++)); do
    character=$(printf "\\$(printf '%03o' "$i")")
    echo "$character - ${counter[${i}]}"
done
