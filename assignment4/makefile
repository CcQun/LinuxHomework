main:main.o func1.o func2.o func3.o comp1.o comp2.o comp3.o comp4.o
	gcc $^ -o main

main.o:main.h
main.o:main.c
	gcc -c main.c

u = usedtype.h

func1.o:func1.h $(u)
func1.o:func1.c
	gcc -c func1.c

func2.o:func2.h $(u)
func2.o:func2.c
	gcc -c func2.c

func3.o:func3.h $(u)
func3.o:func3.c
	gcc -c func3.c

comp1.o:comp1.h func1.h func2.h $(u)
comp1.o:comp1.c
	gcc -c comp1.c

comp2.o:comp2.h func2.h
comp2.o:comp2.c
	gcc -c comp2.c

comp3.o:comp3.h func3.h $(u)
comp3.o:comp3.c
	gcc -c comp3.c

comp4.o:comp4.h func1.h func2.h func3.h
comp4.o:comp4.c
	gcc -c comp4.c

clean:
	-rm main *.o
	@echo "Finished"	
