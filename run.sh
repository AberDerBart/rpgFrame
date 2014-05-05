#!/bin/bash
cd rpgFrame
make clean
make 
cd ..
make clean
make

if [ "$1" = "-d" ]
then
	LD_LIBRARY_PATH=/usr/local/lib/ gdb ./pokethulhu
else
	if [ "$1" = "-v" ]
	then
		LD_LIBRARY_PATH=/usr/local/lib/ valgrind -v ./pokethulhu
	else
		LD_LIBRARY_PATH=/usr/local/lib/ ./pokethulhu $@
	fi
fi
