all: p5

p5: p5.c
	gcc -o p5.out -I p5.h p5.c

clean:
	rm -rf p5.out