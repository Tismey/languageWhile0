
#Timothée M'BASSIDJE 12104516
#Denis LINDE 12104516


executable:  y.tab.o operator.o lex.yy.o interpreter.o operator.c 
	gcc -g -o executable lex.yy.o y.tab.o operator.o interpreter.o -ll -lm

lex.yy.o: lex.yy.c y.tab.h
	gcc -g -c lex.yy.c
y.tab.o: y.tab.c y.tab.h
	gcc -g -c y.tab.c
operator.o: operator.c operator.h
	gcc -g -c operator.c
interpreter.o: interpreter.c master.h operator.c
	gcc -g -c interpreter.c

lex.yy.c: 
	flex while.l
y.tab.c:
	yacc -t while.y

clean:	
	rm -f lex.yy.c y.tab.c *.o executable