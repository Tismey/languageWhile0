

executable:  y.tab.o operator.o lex.yy.o interpreter.o
	gcc -g -o executable lex.yy.o y.tab.o operator.o interpreter.o -ll 

lex.yy.o: lex.yy.c y.tab.h
	gcc -g -c lex.yy.c
y.tab.o: y.tab.c y.tab.h
	gcc -g -c y.tab.c
operator.o: operator.c operator.h
	gcc -g -c operator.c
interpreter.o: interpreter.c master.h
	gcc -g -c interpreter.c

lex.yy.c: 
	flex while.l
y.tab.c:
	yacc while.y

clean:	
	rm -f lex.yy.c y.tab.c *.o executable