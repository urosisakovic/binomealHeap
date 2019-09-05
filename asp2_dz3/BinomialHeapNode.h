#pragma once
#include <stack>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Koriscena implementacija binomialnog hipa (kraj snimka): https://www.youtube.com/watch?v=7UQd9SYUoNk&t=9s .
class BinomialHeapNode
{
	BinomialHeapNode *sibling,
					 *child,
					 *parent;

	// Stepen binomialnog drveta ciji je ovaj cvor koren.
	int degree;

	// Vrednost u cvoru.
	int value;
public:
	BinomialHeapNode(int val = 0);

	BinomialHeapNode *get_sibling() const;
	int get_value() const;

	// Ispisuje stablo. Ne trazi se u domacem zadatku. Sluzi za testiranje.
	void print_tree() const;
	
	friend class BinomialHeap;

	// Dealocira ovaj cvor i sve cvorove koji su u njegovom podstablu (ciji je on predak).
	friend void delete_binomial_tree(BinomialHeapNode *root);

	// Spaja dva binomialna drveta istog stepena u jedno. Ako nisu istog stepena, vraca gresku.
	friend BinomialHeapNode *merge_trees(BinomialHeapNode *a, BinomialHeapNode *b, string comparison_method);
};

