INCLUDE = -I/usr/local/include 
LIB = -L/usr/local/lib
TAGS = -lntl -lgmp -lm -O2 

all: test runwitness runtwostrongliars test_tabspsp test_tonysconjecture test_odometer test_exponent test_reliable_witness_lchen

test: test.o formulas.o tab_carmichael.o tab_liars.o first_liar.o sievepractice.o lowestprimesieve.o tab_psp.o DoubleLinkedListArray.o
	g++ $(INCLUDE) $(LIB) formulas.o tab_carmichael.o tab_liars.o tab_psp.o first_liar.o test.o sievepractice.o lowestprimesieve.o DoubleLinkedListArray.o -o test $(TAGS)

runwitness: runreliablewitness.o formulas.o tab_carmichael.o tab_liars.o
	g++ $(INCLUDE) $(LIB) formulas.o tab_carmichael.o tab_liars.o runreliablewitness.o -o runwitness $(TAGS)

runtwostrongliars: runtwostrongliars.o formulas.o
	g++ $(INCLUDE) $(LIB) formulas.o runtwostrongliars.o -o runtwostrongliars $(TAGS)

test_tabspsp: test_tabspsp.o formulas.o tab_psp.o
	g++ $(INCLUDE) $(LIB) formulas.o tab_psp.o test_tabspsp.o -o test_tabspsp $(TAGS)

test_tonysconjecture: test_tonysconjecture.o formulas.o
	g++ $(INCLUDE) $(LIB) formulas.o test_tonysconjecture.o -o test_tonysconjecture $(TAGS)

test_odometer: test_odometer.o Odometer.o
	g++ $(INCLUDE) $(LIB) Odometer.o test_odometer.o -o test_odometer $(TAGS)

test_exponent: test_exponent.o exponent_list.o reliable_witness_lchen.o Odometer.o
	g++ $(INCLUEDE) $(LIB) test_exponent.o exponent_list.o reliable_witness_lchen.o Odometer.o -o test_exponent $(TAGS)

test_reliable_witness_lchen:  test_reliable_witness_lchen.o reliable_witness_lchen.o formulas.o
	g++ $(INCLUEDE) $(LIB) test_reliable_witness_lchen.o reliable_witness_lchen.o formulas.o -o test_reliable_witness_lchen $(TAGS)

test.o: test.cpp
	g++ $(INCLUDE) -c test.cpp

test_tabspsp.o: test_tabspsp.cpp
	g++ $(INCLUDE) -c test_tabspsp.cpp

Odometer.o: Odometer.cpp
	g++ $(INCLUDE) -c Odometer.cpp

test_tonysconjecture.o: test_tonysconjecture.cpp
	g++ $(INCLUDE) -c test_tonysconjecture.cpp

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

exponent_list.o: exponent_list.cpp
	g++ $(INCLUDE) -c exponent_list.cpp

test_exponent.o: test_exponent.cpp
	g++ $(INCLUDE) -c test_exponent.cpp

reliable_witness_lchen.o: reliable_witness_lchen.cpp
	g++ $(INCLUDE) -c reliable_witness_lchen.cpp

test_reliable_witness_lchen.o: test_reliable_witness_lchen.cpp
	g++ $(INCLUDE) -c test_reliable_witness_lchen.cpp

clean: 
	rm *.o