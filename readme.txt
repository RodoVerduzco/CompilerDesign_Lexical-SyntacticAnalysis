/*
*   Compiling and Running
*
*  To compile and run:
*
*      1) Use Makefile:
*          make
*          ./tiny < file
*
*					./tiny < ../inputs/input2.c
*
*      2) Manually:
*          bison -v tiny.y -o tiny.tab.c
*          flex tiny.l
*          gcc -DGRAMMAR `pkg-config gtk+-2.0 --cflags --libs` -O2 -o tiny table.c tiny.tab.c -lfl
*				
*					OR
*
*		   gcc -DGRAMMAR table.c tiny.tab.c `pkg-config gtk+-2.0 --cflags --libs` -O2 -o tiny -lfl
*          ./tiny < file
*
*/

/*
*   Compiling and Running Ubuntu Version
*
* 	Use the Makefile.sh
* 	Execute with:
* 		./Makefile.sh
* 	or manually:
* 		bison -d tiny.y -Wall -Wother	
*			flex tiny.l	
*			gcc -O2 -o tiny -DYACC table.h table.c interpreter.h interpreter.c tiny.tab.c `pkg-config --cflags --libs glib-2.0` -lfl -O2	
*			rm tiny.tab.c tiny.tab.h
*/