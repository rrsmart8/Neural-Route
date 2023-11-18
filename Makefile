CC = gcc
CFLAGS = -Wall -g

build: tema3

tema3: graf-L.c test-graf.c
	$(CC) $(CFLAGS) $^ -o $@

run:
	./tema3

.PHONY: clean
clean:
	rm -f *.o *~ tema3
