CC		= gcc
CFLAGS	= -Wall -g -D_GNU_SOURCE -fPIC
LDFLAGS = -lunwind -lunwind-$(shell uname -m)
PROGS	= chals libpoem.so libsolver.so chalss

all: $(PROGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

chals: chals.o libpoem.so
	$(CC) -o $@ $^ $(LDFLAGS)

chalss: chalss.o libpoem.so
	$(CC) -o $@ $^ $(LDFLAGS)

libpoem.so: libpoem.o
	$(CC) -o $@ -shared $^ $(LDFLAGS)
	
libsolver.so: libsolver.o
	$(CC) -o $@ -shared $^ $(LDFLAGS)


test:
	LD_LIBRARY_PATH=`pwd` LD_PRELOAD=./libsolver.so ./chals
# test:
# 	LD_LIBRARY_PATH=`pwd` ./chalss
run:
	LD_LIBRARY_PATH=`pwd` ./chals

# libsolver2.so: libsolver2.o
# 	$(CC) -shared -o $@ $^ 
# test:
# 	LD_LIBRARY_PATH=`pwd` LD_PRELOAD=./libsolver2.so ./chals
cleanup:
	rm -f *.o

clean:
	rm -f $(PROGS) *.o
	rm -rf __pycache__

pwn:
	. ~/pwntools/bin/activate
x86:
	x86_64-linux-gnu-gcc -o libsolver.so -shared -fPIC libsolver.c
submit:
	python3 submit.py libsolver.so
