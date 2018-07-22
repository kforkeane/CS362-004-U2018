CFLAGS = -Wall -fpic -coverage -std=c99 #remove -lm because math library not used

testme.o: testme.c
	gcc -c testme.c -g  $(CFLAGS)

testme: testme.o
	gcc -o testme -g testme.o $(CFLAGS)
	./testme 

	# specs say to make the rule execute the test as well

clean:
	rm -f *.o *.exe *.gcda *.gcno