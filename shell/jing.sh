#! /bin/bash

gcc  source/function.c -o source/function.o -c -I./include
gcc  source/show.c -o source/show.o -c -I./include
gcc  source/get_bankcard.c -o source/get_bankcard.o -c -I./include

ar rcs library/libmy_stati.a source/*.o

rm ./source/*.o

echo "系统静态库制作完成"
tree
