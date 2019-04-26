# 
# bison -d LexSyn.y -Wall -Wother
## bison -d LexSyn.y
## flex LexSyn.l
### gcc -O2 -o LexSyn -DYACC LexSyn.tab.c  -lfl
## gcc -O2 -o LexSyn -DYACC LexSyn.tab.c `pkg-config --cflags --libs glib-2.0` -lfl -O2

# ./LexSyn < testFile
# ./LexSyn < ../inputs/input2.c


# bison -d LexSyn.y
# flex LexSyn.l
# gcc -O2 -o LexSyn -DYACC LexSyn.tab.c `pkg-config --cflags --libs glib-2.0` -lfl -O2
# ./LexSyn < testFile
# ./LexSyn < ../inputs/input2.c

bison -d tiny.y
flex tiny.l
gcc -O2 -o tiny -DYACC table.h table.c tiny.tab.c `pkg-config --cflags --libs glib-2.0` -lfl -O2
rm tiny.tab.c tiny.tab.h
# ./tiny < testFile
# ./tiny < ../inputs/input2.c