all: ./code/fibo.o ./code/main.o
	gcc code/fibo.o code/main.o -o main

./code/fibo.o:
	gcc -c ./code/fibo.c -o ./code/fibo.o -I include

./code/main.o:
	gcc -c ./code/main.c -o ./code/main.o -I include

clean:
	rm ./code/*.o