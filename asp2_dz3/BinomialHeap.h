#pragma once
#include "BinomialHeapNode.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

// Koriscena implementacija binomialnog hipa (kraj snimka): https://www.youtube.com/watch?v=7UQd9SYUoNk&t=9s .

class BinomialHeap
{
	BinomialHeapNode *first;
	string comparison_method;
public:
	BinomialHeap(string comp);
	~BinomialHeap();

	// Dodaje element u hip.
	void add(int val, int *steps = nullptr);

	// Vraca pokazivac na cvor sa najmanjim (u min hipu), odnosno najvecim (u maks hipu) elementom.
	BinomialHeapNode* get() const;

	// Izbacuje cvor sa najmanjim (u min hipu), odnosno najvecim (u maks hipu) elementom.
	// Broj izvrsenih koraka cuva u steps promenljivoj.
	void remove(int *steps = nullptr); 

	// Alocira novi hip sa istim elementima suprotne vrste.
	BinomialHeap* convert();

	// Ispisuje hip. Ne trazi se u domacem. Sluzi za proveru ispravnosti.
	void print() const;

	// Dodaje jos jedno binomialno drvo u hip.
	// Broj izvrsenih koraka cuva u steps promenljivoj.
	BinomialHeap& merge_tree(BinomialHeapNode* new_tree, int *steps = nullptr);

	// Spaja dva hipa i vraca referencu na novostvoreni hip.
	// Broj izvrsenih koraka cuva u steps promenljivoj.
	friend BinomialHeap& merge(BinomialHeap& a, BinomialHeap& b, int *steps);
	friend class PriorityQueue;
};

