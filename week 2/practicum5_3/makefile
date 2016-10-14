#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := compressed.asm decompress.asm

# header files in this project
HEADERS :=  

# other places to look for files for this project
SEARCH  := 
# set BMPTK to the next higher directory and defer to the Makefile.due
BMPTK := $(BMPTK)../
include $(BMPTK)Makefile.due

main.exe : compressed.asm main.cpp decompress.asm
	gcc compressed.asm main.cpp decompress.asm -o main.exe

compressed.asm : make_compressed.exe

make_compressed.exe : make_compressed.cpp wilhelmus.txt
	gcc make_compressed.cpp -o make_compressed.exe