#!/usr/bin/python
# -*- coding: utf-8 -*-

import random


def findlargest(lst, N):
    largest = lst[0]            # largest = list[1]
    for i in range(1, N):       # for i = 2 to N do
        if lst[i] > largest:        # if (list[i] > largest) then
            largest = lst[i]            # largest = list[i]
                                    # end if
                                # end for
    return largest


def main():
    lst = [i for i in range(10)]
    random.shuffle(lst)
    print(findlargest(lst, len(lst)))

if __name__ == '__main__':
    main()

