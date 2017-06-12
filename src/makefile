INCLUDE = -I/usr/local/include 
LIB = -L/usr/local/lib
TAGS = -lntl -lgmp -lm -O2 

all: test runwitness runtwostrongliars testtonysconjecture

test: test.o formulas.o tab_carmichael.o tab_liars.o first_liar.o sievepractice.o lowestprimesieve.o tab_psp.o DoubleLinkedListArray.o
	g++ $(INCLUDE) $(LIB) formulas.o tab_carmichael.o tab_liars.o tab_psp.o first_liar.o test.o sievepractice.o lowestprimesieve.o DoubleLinkedListArray.o -o test $(TAGS)
	mv test ../bin/

runwitness: runreliablewitness.o formulas.o tab_carmichael.o tab_liars.o
	g++ $(INCLUDE) $(LIB) formulas.o tab_carmichael.o tab_liars.o runreliablewitness.o -o runwitness $(TAGS)
	mv runwitness ../bin/

runtwostrongliars: runtwostrongliars.o formulas.o
	g++ $(INCLUDE) $(LIB) formulas.o runtwostrongliars.o -o runtwostrongliars $(TAGS)
	mv runtwostrongliars ../bin/

testtonysconjecture: testtonysconjecture.o formulas.o
	g++ $(INCLUDE) $(LIB) formulas.o testtonysconjecture.o -o testtonysconjecture $(TAGS)
	mv testtonysconjecture ../bin/

test.o: test.cpp
	g++ $(INCLUDE) -c test.cpp

testtonysconjecture.o: testtonysconjecture.cpp
	g++ $(INCLUDE) -c testtonysconjecture.cpp

runreliablewitness.o: 	runreliablewitness.cpp
	g++ $(INCLUDE) -c runreliablewitness.cpp

formulas.o: formulas.cpp
	g++ $(INCLUDE) -c formulas.cpp

tab_carmichael.o: tab_carmichael.cpp
	g++ $(INCLUDE) -c tab_carmichael.cpp

tab_liars.o: tab_liars.cpp
	g++ $(INCLUDE) -c tab_liars.cpp

first_liar.o:	first_liar.cpp
	g++ $(INCLUDE) -c first_liar.cpp

tab_psp.o:	tab_psp.cpp
	g++ $(INCLUDE) -c tab_psp.cpp

sievepractice.o: sievepractice.cpp
	g++ $(INCLUDE) -c sievepractice.cpp

runtwostrongliars.o:	runtwostrongliars.cpp
	g++ $(INCLUDE) -c runtwostrongliars.cpp

lowestprimesieve.o: lowestprimesieve.cpp
	g++ $(INCLUDE) -c lowestprimesieve.cpp

DoubleLinkedListArray.o:	DoubleLinkedListArray.cpp
	g++ $(INCLUDE) -c DoubleLinkedListArray.cpp

clean:
	rm *.o

clobber: clean
	rm test
