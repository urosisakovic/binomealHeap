#include "BinomialHeap.h"


BinomialHeap::BinomialHeap(string comparison_method)
{
	this->first = nullptr;
	if ((comparison_method != "min") && (comparison_method != "max"))
	{
		cout << "BinomialHeap: comparison_method must be 'min' or 'max'" << endl;
		system("pause");
		exit(1);
	}
	this->comparison_method = comparison_method;
}

// Destruktor. Prvo gurne pokazivace na sva binomialna drva
// u stek i onda ih skida jedan po jedan i dealocira sve te cvorove.
BinomialHeap::~BinomialHeap()
{
	stack <BinomialHeapNode*> binomial_trees;
	BinomialHeapNode *ptr;

	ptr = this->first;
	while (ptr)
	{
		binomial_trees.push(ptr);
		ptr = ptr->sibling;
	}

	BinomialHeapNode *binomial_tree;
	while (!binomial_trees.empty())
	{
		binomial_tree = binomial_trees.top();
		binomial_trees.pop();

		delete_binomial_tree(binomial_tree);
	}
}

// Napravi novi hip, koji ima samo jedno binomialno drvo reda 0,
// a zatim ga spoji sa postojecim hipom.
void BinomialHeap::add(int val, int *steps)
{
	BinomialHeapNode *new_node = new BinomialHeapNode(val);

	BinomialHeap *new_heap = new BinomialHeap(this->comparison_method);
	new_heap->first = new_node;
	(*steps)++;

	*this = merge(*this, *new_heap, steps);
}


// Prolazi kroz cvorove svih binomialnih drveca iz hipa i uzima najmanji (za min hip),
// odnosno najveci (za max hip) i vraca pokazivac na njega.
BinomialHeapNode* BinomialHeap::get() const
{
	BinomialHeapNode *ptr = this->first;

	int ret;
	BinomialHeapNode *ret_node = nullptr;
	if (comparison_method == "max")
		ret = -1;
	else if (comparison_method == "min")
		ret = INT_MAX;

	while (ptr)
	{
		if (comparison_method == "max")
		{
			if (ret < ptr->value)
			{
				ret = ptr->value;
				ret_node = ptr;
			}
		}
		else if (comparison_method == "min")
		{
			if (ret > ptr->value)
			{
				ret = ptr->value;
				ret_node = ptr;
			}
		}
		ptr = ptr->sibling;
	}

	return ret_node;
}

// Brisanje najmanjeg, odnosno najveceg elementa. 
// Prvo ga lociramo koristeci metodu get(). Dealociramo ga,
// a svu njegovi decu (koja su isto binomialna drveca) merge-ujemo sa hipom.
void BinomialHeap::remove(int *steps)
{
	if (this->first == nullptr)
		return;

	BinomialHeapNode *top_node = this->get();

	if (top_node == this->first)
	{
		this->first = this->first->sibling;
		top_node->sibling = nullptr;
	}
	else
	{
		BinomialHeapNode *prev = this->first;
		while (prev->sibling != top_node)
			prev = prev->sibling;
		prev->sibling = top_node->sibling;
		top_node->sibling = nullptr;
	}

	BinomialHeapNode *children = top_node->child;
	BinomialHeapNode *temp;
	while (children)
	{
		temp = children->sibling;
		children->sibling = nullptr;
		children->parent = nullptr;
		merge_tree(children, steps);
		children = temp;
	}

	delete top_node;
}


// Obilazimo sve cvorove iz hipa i dodajemo ih jedan po jedan u novi
// hip koji smo alocirali i zadali mu da bude suprotnog tipa.
BinomialHeap* BinomialHeap::convert()
{
	string new_comparison_method;
	if (this->comparison_method == "max")
		new_comparison_method = "min";
	else if (this->comparison_method == "min")
		new_comparison_method = "max";

	BinomialHeap *new_heap = new BinomialHeap(new_comparison_method);

	stack<BinomialHeapNode*> s;
	s.push(this->first);

	BinomialHeapNode *curr_node;
	while (!s.empty())
	{
		curr_node = s.top();
		s.pop();

		new_heap->add(curr_node->value, nullptr);

		if (curr_node->sibling)
			s.push(curr_node->sibling);
		if (curr_node->child)
			s.push(curr_node->child);
	}

	return new_heap;
}


// Dodajemo binomialno drvo u nas hip.
BinomialHeap& BinomialHeap::merge_tree(BinomialHeapNode *new_tree, int *steps)
{
	new_tree->sibling = nullptr;
	new_tree->parent = nullptr;

	if (this->first == nullptr)
	{
		(*steps)++;
		this->first = new_tree;
		return *this;
	}

	BinomialHeapNode *ptr = this->first;
	BinomialHeapNode *prev = nullptr;
	while (ptr)
	{
		(*steps)++;
		if (ptr->degree < new_tree->degree)
		{
			prev = ptr;
			ptr = ptr->sibling;
		}

		else if (ptr->degree == new_tree->degree)
		{
			BinomialHeapNode *nxt = ptr->sibling;
			new_tree = merge_trees(ptr, new_tree, this->comparison_method);
			(*steps)++;

			if (prev != nullptr)
			{
				prev->sibling = nxt;
				ptr = nxt;
			}
			else
			{
				if (nxt != nullptr)
				{
					this->first = nxt;
					prev = nullptr;
					ptr = nxt;
				}
				else
				{
					this->first = new_tree;
					return *this;
				}
				
			}
				
		}
		else if (ptr->degree > new_tree->degree)
		{
			if (prev == nullptr)
			{
				new_tree->sibling = ptr;
				this->first = new_tree;
			}
			else
			{
				prev->sibling = new_tree;
				new_tree->sibling = ptr;
			}
			return *this;
		}
	}

	if (!ptr)
	{
		prev->sibling = new_tree;
		return *this;
	}
	else
	{
		cout << "merge_tree: Impossible case." << endl;
		system("pause");
		exit(1);
	}
}

// Spajamo dva hipa tako sto svako binomialno drvo iz jednog dodamo u drugo.
BinomialHeap& merge(BinomialHeap& a, BinomialHeap& b, int *steps = nullptr)
{
	if (a.first == nullptr)
		return b;

	BinomialHeapNode *ptr = a.first->get_sibling(),
					 *merge_node = a.first;

	while (ptr)
	{
		b.merge_tree(merge_node, steps);
		merge_node = ptr;
		ptr = ptr->get_sibling();
	}

	b.merge_tree(merge_node, steps);
	return b;
}

void BinomialHeap::print() const
{
	BinomialHeapNode *ptr = this->first;

	while (ptr)
	{
		cout << "binomial tree with degree " << ptr->degree << ":   ";
		ptr->print_tree();
		cout << endl;
		ptr = ptr->sibling;
	}
	cout << endl << endl;
}