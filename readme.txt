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
*          bison -v tiny_grammar.y -o tiny.tab.c
*          flex tiny.l
*          gcc -DGRAMMAR `pkg-config gtk+-2.0 --cflags --libs` -O2 -o tiny table.c tiny.tab.c -lfl
*          ./tiny < file
*
*/

/*
*   Compiling and Running Ubuntu Version
*
* 	Use the Makefile.sh
* 	Execute with:
* 		./Makefile.sh
*/