#!/bin/bash

make 1>/dev/null
make bonus 1>/dev/null
echo -n "cheker_Mac -->" $(./push_swap $(cat list.txt) | ./checker_Mac $(cat list.txt))
echo -n "   cheker -->" $(./push_swap $(cat list.txt) | ./checker $(cat list.txt))
./push_swap $(cat list.txt) | wc -l
