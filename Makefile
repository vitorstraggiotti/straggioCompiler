# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Makefile for compiling the straggio compiler                   #
#                                                                #
# Author: Vitor Henrique Andrade Helfensteller Straggiotti Silva #
# Created on: 25/01/2021 (DD/MM/YYYY)                            #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Compiler used
CC = gcc

# Main program source
main = straggio_assembler_main.c

# Dependencies source
C_01 = str_process.c
H_01 = str_process.h

# Compiled objects
objects = str_process.o \
          straggio_assembler_main.o

straggio: $(objects)
	$(CC) $(objects) -o straggio

str_process.o: $(C_01) $(H_01)
	$(CC) -c $(C_01)

straggio_assembler_main.o: $(main) $(H_01)
	$(CC) -c $(main)


.PHONY: clean cleanall

cleanall: clean
	rm straggio

clean:
	rm $(objects)

#################################################
# Compiling debug version                       #
#################################################

.PHONY: debug_version

debug_version:
	$(CC) -g $(main) $(C_01) -o straggio.out




