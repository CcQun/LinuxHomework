main: comp1.o comp2.o comp3.o comp4.o func1.o func2.o func3.o main.o
	gcc $^ -o main
comp1.o: comp1.c comp1.h func1.h func2.h usedtype.h
	gcc -c comp1.c
comp2.o: comp2.c func2.h comp1.h
	gcc -c comp2.c
comp3.o: comp3.c func3.h comp3.h usedtype.h
	gcc -c comp3.c
comp4.o: comp4.c func1.h func3.h func2.h comp4.h
	gcc -c comp4.c
func1.o: func1.c func1.h usedtype.h
	gcc -c func1.c
func2.o: func2.c func2.h usedtype.h
	gcc -c func2.c
func3.o: func3.c func3.h usedtype.h
	gcc -c func3.c
main.o: main.c main.h comp1.h comp2.h comp3.h comp4.h
	gcc -c main.c
clean:
	-rm main *.o
	@echo Finished
