#!/bin/bash

program="num_of_diff_char_in_file"

rm "$program.out"
gcc -Wall "$program.c" -o "$program.out"

echo "Lorem ipsum" | "./$program.out"
