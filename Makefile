
app.out : main.o def_m.o
	gcc -o app.out main.o def_m.o

main.o :
	gcc -c main.c

def_m.o :
	gcc -c def_m.c
