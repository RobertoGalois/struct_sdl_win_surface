#!/bin/bash

files_c=''              #all .c files
files_o=''              #all .o files String
prog_name='prog'        #exec file name, 'prog' by default

#listing all .o files in a String like 'file1.o file2.o file3.o etc'
for file in `ls *.c`
do
    file=${file/%.c/.o}
    files_o="$files_o $file"
done

#get the name of the exec file name
if [ ! -z $1  ]
then
    prog_name=$1
fi

#makefile header:
echo '.PHONY: clean' > ./makefile
echo '.SUFFIXES:' >> ./makefile
echo '' >> ./makefile

#compilation of prog_name: *.o
echo "$prog_name:$files_o" >> ./makefile
echo "  gcc$files_o -o $prog_name"' `sdl-config --cflags --libs`' >> ./makefile

#generating *.o files
for file in `ls *.c`
do
    echo `gcc -MM $file` >> ./makefile
    echo "  gcc -c $file" >> ./makefile
done

#makefile footer
echo "clean:" >> ./makefile
echo "  rm -f *.o $prog_name" >> ./makefile
