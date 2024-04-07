# Script for Programming system generation
all: komppl.exe kompassr.exe absloadm.exe
#komppl.o: komppl.c
#	gcc -o komppl.o komppl.c
komppl.exe: komppl.c
	@echo "__komppl.exe generation__"	

	gcc -o komppl.exe komppl.c
	
	@echo "________________"
kompassr.exe: kompassr.c
	@echo "__kompassr.exe generation__"

	gcc -o kompassr.exe kompassr.c

	@echo "________________"
absloadm.exe: absloadm.c
	@echo "__absloadm.exe generation__"
	
	gcc -o absloadm.exe absloadm.c -lncurses

	@echo "________________"

