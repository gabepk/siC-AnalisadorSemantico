# Makefile

OBJS	= Parser.y.o Parser.lex.o

CC	= gcc
CFLAGS	= -g -Wall

Parser:		$(OBJS)
		$(CC) $(CFLAGS) -o Parser $(OBJS) -lfl

Parser.lex.o:	Parser.lex.c
		$(CC) $(CFLAGS) -c Parser.lex.c -o Parser.lex.o

Parser.lex.c:	Parser.lex 
		flex Parser.lex
		mv lex.yy.c Parser.lex.c

Parser.y.o:	Parser.y.c
		$(CC) $(CFLAGS) -c Parser.y.c -o Parser.y.o

Parser.y.c:	Parser.y
		bison -d -v Parser.y
		mv Parser.tab.h Parser.h
		mv Parser.tab.c Parser.y.c

Parser.lex.o:	Parser.h

clean:
	rm -f *.o *~ Parser.lex.c lex.yy.c Parser.y.c Parser.h Parser.tab.c Parser.tab.h Parser.output Parser