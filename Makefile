####################################################################
#
# File name:    Makefile
#
# Description:  Flex Makefile
#
# History:
#   Fri Jan 28 2005 Abelardo Lopez   File created.
#   Tue Aug 29 2006 Abelardo Lopez   Changed byacc for bison
#   Wed Feb 01 2017 Abelardo Lopez   New formating
#   Tue Oct 02 2018 Rodolfo Verduzco Changed files used
#
####################################################################
#
# Define the compiler optimization flags
#
COPT    = -O2
COPT2   = -Wall -Wother -O2
CDBG    = -g -DDEBUG
GLIB    = `pkg-config gtk+-2.0 --cflags --libs`
CC      = gcc
LEX     = flex
YACC    = bison
#
# Define the target names
#
TARGET_LEX    = tiny.l
TARGET_BISON  = tiny.y
TARGET_GRAM   = tiny.y
TARGET_NAME   = tiny
TARGET_HELPER = table.c
#
# Rule definitions for target builds
#
all:
	$(YACC) -v $(TARGET_GRAM) -o $(TARGET_NAME).tab.c
	$(LEX) $(TARGET_LEX)
	$(CC) -DGRAMMAR $(COPT) $(GLIB) -o $(TARGET_NAME) $(TARGET_HELPER) $(TARGET_NAME).tab.c -lfl

clean:
	rm -f *~ core lex.yy.c $(TARGET_NAME).tab.* $(TARGET_NAME).output

clobber: clean
	rm -f $(TARGET_NAME)
