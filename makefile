PATHS = -I/usr/local/include -L/usr/local/lib
TAGS = -lntl -lgmp -lm -O2 -static 

all: test runwitness runtwostrongliars 

test: test.o formulas.o tab_carmichael.o tab_liars.o first_liar.o sievepractice.o lowestprimesieve.o tab_psp.o
	g++ $(PATHS) formulas.o tab_carmichael.o tab_liars.o tab_psp.o first_liar.o test.o sievepractice.o lowestprimesieve.o -o test $(TAGS)

runwitness:	runreliablewitness.o formulas.o tab_carmichael.o tab_liars.o
	g++ $(PATHS) formulas.o tab_carmichael.o tab_liars.o runreliablewitness.o -o runwitness $(TAGS)

runtwostrongliars:	runtwostrongliars.o formulas.o
	g++ $(PATHS) formulas.o runtwostrongliars.o -o runtwostrongliars $(TAGS)

test.o: test.cpp
	g++ $(PATHS) -c test.cpp	

runreliablewitness.o: 	runreliablewitness.cpp
	g++ $(PATHS) -c runreliablewitness.cpp

formulas.o: formulas.cpp
	g++ $(PATHS) -c formulas.cpp

tab_carmichael.o: tab_carmichael.cpp
	g++ $(PATHS) -c tab_carmichael.cpp

tab_liars.o: tab_liars.cpp
	g++ $(PATHS) -c tab_liars.cpp

first_liar.o:	first_liar.cpp
	g++ $(PATHS) -c first_liar.cpp

tab_psp.o:	tab_psp.cpp
	g++ $(PATHS) -c tab_psp.cpp

sievepractice.o: sievepractice.cpp
	g++ $(PATHS) -c sievepractice.cpp

runtwostrongliars.o:	runtwostrongliars.cpp
	g++ $(PATHS) -c runtwostrongliars.cpp

lowestprimesieve.o: lowestprimesieve.cpp
	g++ $(PATHS) -c lowestprimesieve.cpp

clean:
	rm *.o

clobber: clean
	rm test
