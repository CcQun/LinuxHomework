CC=afl-clang-fast

main:main.o func1.o func2.o func3.o comp1.o comp2.o comp3.o comp4.o
	$(CC) $^ -o main

main.o:main.h
main.o:main.c
	$(CC) -c main.c

u = usedtype.h

func1.o:func1.h $(u)
func1.o:func1.c
	$(CC) -c func1.c

func2.o:func2.h $(u)
func2.o:func2.c
	$(CC) -c func2.c

func3.o:func3.h $(u)
func3.o:func3.c
	$(CC) -c func3.c

comp1.o:comp1.h func1.h func2.h $(u)
comp1.o:comp1.c
	$(CC) -c comp1.c

comp2.o:comp2.h func2.h
comp2.o:comp2.c
	$(CC) -c comp2.c

comp3.o:comp3.h func3.h $(u)
comp3.o:comp3.c
	$(CC) -c comp3.c

comp4.o:comp4.h func1.h func2.h func3.h
comp4.o:comp4.c
	$(CC) -c comp4.c

clean:
	-rm main *.o
	@echo "Finished"	
