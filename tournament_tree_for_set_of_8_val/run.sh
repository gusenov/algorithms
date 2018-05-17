#!/bin/bash

file_name="tournament-tree-for-a-set-of-eight-values"
dot -Tpng "$file_name.gv" -o "$file_name.png"
