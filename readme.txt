/*
*   Compiling and Running
*
*  To compile and run:
*
*      1) Use Makefile:
*          make
*          ./tiny < tiny
*
*      2) Manually:
*          bison -v tiny_grammar.y -o tiny.tab.c
*          flex tiny.l
*          gcc -DGRAMMAR -O2 -o tiny tiny.tab.c -lfl
*          ./tiny < tiny
*
*/
