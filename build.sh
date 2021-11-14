#!/bin/sh
gcc ./scroll.c
mv ./a.out scroll
cp ./scroll /usr/local/bin

# If saved dir is changed then you must change the two times it's referenced in scroll.c
touch /home/seth/tmp/saved