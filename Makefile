.PHONY: all
all: shell.out test.out 

shell.out: shell.c parser.c qualifyPath.c piping.c
	gcc -g -o $@ $^

test.out: test.c parser.c qualifyPath.c piping.c
	gcc -g -o $@ $^ 

.PHONY: clean
clean: 
	rm -f *.out

.PHONY: test
test: test.out
	./test.out