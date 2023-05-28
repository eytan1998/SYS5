
.PHONY: clean all

all: st_pipelie

Queue.o: Queue.c Queue.h
	gcc -c -g -fPIC Queue.c

AO.o: AO.c AO.h Queue.h
	gcc -c -g -fPIC AO.c

main.o: main.c AO.h
	gcc -c -g main.c

st_pipelie.so : AO.o Queue.o
	gcc -g -shared -o libst_pipelie.so AO.o Queue.o

st_pipelie: st_pipelie.so main.o
	gcc  -g main.o -o st_pipelie -L. -lst_pipelie -Wl,-rpath,. -pthread

clean:
	rm -f st_pipelie *.o *.so

