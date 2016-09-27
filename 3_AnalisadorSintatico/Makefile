# Makefile

CC	= gcc
CFLAGS	= -g -Wall

sic-compiler:	lex.yy.c
		$(CC) $(CFLAGS) lex.yy.c -o sic-compiler -lfl
		
lex.yy.c:	110118995.lex 
		flex 110118995.lex
		
clean:
	rm -f *.o *~ lex.yy.c sic-compiler