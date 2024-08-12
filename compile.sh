#!/bin/bash

output="colores"

sources = "main.c"

gcc -o $output $sources -lncurses

if [ $? -eq 0 ]; then
	echo "Compilation Successful."
else
	echo "Compilation Error."
fi	
