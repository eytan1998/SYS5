
.PHONY: clean all

all: st_pipeline

Queue.o: Queue.c Queue.h
	gcc -c -g -fPIC Queue.c

AO.o: AO.c AO.h Queue.h
	gcc -c -g -fPIC AO.c

main.o: main.c AO.h
	gcc -c -g main.c

st_pipeline.so : AO.o Queue.o
	gcc -g -shared -o libst_pipeline.so AO.o Queue.o

st_pipeline: st_pipeline.so main.o
	gcc  -g main.o -o st_pipeline -L. -lst_pipeline -Wl,-rpath,. -pthread

clean:
	rm -f st_pipeline *.o *.so

