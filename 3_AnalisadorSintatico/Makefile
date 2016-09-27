# Makefile

OBJS	= 110118995.tab.o lex.yy.o

CC	= gcc
CFLAGS	= -g -Wall

sic-compiler:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o sic-compiler -lfl

lex.yy.o:	lex.yy.c
		$(CC) $(CFLAGS) -c lex.yy.c -o lex.yy.o
		
lex.yy.c:	110118995.lex 
		flex 110118995.lex
		
110118995.tab.o:	110118995.tab.c
			$(CC) $(CFLAGS) -c 110118995.tab.c -o 110118995.tab.o

110118995.tab.c:	110118995.y
			bison -d -v -Wall 110118995.y
		
lex.yy.o:	110118995.tab.h

clean:
	rm -f *.o *~ lex.yy.c 110118995.tab.c 110118995.tab.h 110118995.output sic-compiler