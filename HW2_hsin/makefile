all:
	gcc sdb.c -o sdb -lelf -lcapstone
san:
	gcc sdb.c -o sdb -lelf -lcapstone -fsanitize=address
debug:
	gcc sdb.c -o sdb -lelf -lcapstone -g
64:
	./sdb ./hello64
he:
	./sdb ./hello
gu:
	./sdb ./guess
whi:
	./sdb ./while
clean:
	rm -f sdb