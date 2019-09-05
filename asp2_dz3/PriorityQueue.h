#pragma once
#include "BinomialHeap.h"
#include <string>
#include <time.h>
#include <fstream>
#include <chrono>
using namespace std;

// Prvo pogledati BinomialHeap. 
// Ista struktura sa malo promenjenim interfejsom zato sto 
// zadatak tako nalaze.
// Sastoji se od samo jednog binomialnog hipa i metode
// ove strukture uglavnom pozivaju analogne metode strukture binomialnog hipa.
// Cudna postavka zadatka?
class PriorityQueue
{
	BinomialHeap *bh;
public:
	PriorityQueue(string comparison_method);
	~PriorityQueue();

	// Proverava da li je prioritetni red prazan.
	bool empty() const;

	// Vraca pokazivac na prvi element prioritetnog reda.
	int front() const;

	// Izbacuje prvi element iz reda.
	// U steps cuva broj koraka.
	int pop(int *steps = nullptr);

	// Ubacuje novi element u red.
	// U steps cuva broj koraka.
	void push(int value, int *steps = nullptr);

	// Dodaje size proizvoljnih, pseudo-slucajno generisanih brojeva u hip.
	// U steps cuva broj koraka.
	void fill_random(int size, int *steps = nullptr);

	// Cita celobrojne brojeve iz fajla cija je putanja zadata
	// stringom file_path. Pretpostavka je da svaka linija sadzri po jedan broj.
	// U steps cuva broj koraka.
	void fill_from_file(string file_path, int *steps = nullptr);

	// Izvrsava zadatu operaciju i ispisuje metrike trazene u postavci domaceg zadatka.
	// Ukoliko je size>0, file_path se zanemaruje. U p. r. se dodaje size pseudo-slucajnih brojeve
	// i mere se performance.
	// Ukoliko je size <= 0, ucitavaju se brojevi iz fajla sa putanjom file_path i mere
	// se performanse.
	void print_performance_measures(int size, string file_path="");
};

