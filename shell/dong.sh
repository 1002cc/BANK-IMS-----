#! /bin/bash

gcc  source/function.c -o source/function.o -c -I./include -fPIC
gcc  source/show.c -o source/show.o -c -I./include -fPIC
gcc  source/get_bankcard.c -o source/get_bankcard.o -c -I./include -fPIC

gcc -fPIC -shared -o ./library/libmy_auto.so ./source/*.o

sudo cp ./library/libmy_auto.so /lib/

rm ./source/*.o

echo ”该系统动态库制作完成“
tree
