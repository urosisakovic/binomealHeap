#include "BinomialHeapNode.h"


BinomialHeapNode::BinomialHeapNode(int val)
{
	value = val;
	degree = 0;
	sibling = parent = child = nullptr;
}


void delete_binomial_tree(BinomialHeapNode *root)
{
	stack <BinomialHeapNode*> nodes;
	nodes.push(root);

	BinomialHeapNode *curr_node;
	while (!nodes.empty())
	{
		curr_node = nodes.top();
		nodes.pop();

		if ( (curr_node->sibling != nullptr) && (curr_node != root) )
			nodes.push(curr_node->sibling);
		if (curr_node->child != nullptr)
			nodes.push(curr_node->child);

		delete curr_node;
	}
}

BinomialHeapNode* BinomialHeapNode::get_sibling() const { return sibling; }

// Vraca true ukoliko a treba da bude iznad b u drvetu. Inace, vraca false.
bool up(int a, int b, string criteria)
{
	if (criteria == "max")
		return a >= b;
	else if (criteria == "min")
		return a <= b;
	else
	{
		cout << "up: criteria must have values 'min' or 'max'." << endl;
		system("pause");
		exit(1);
	}
}

int BinomialHeapNode::get_value() const { return value; }

BinomialHeapNode *merge_trees(BinomialHeapNode *a, BinomialHeapNode *b, string comparison_method)
{
	a->sibling = nullptr; a->parent = nullptr;
	b->sibling = nullptr; b->parent = nullptr;

	if (a->degree != b->degree)
	{
		cout << "merge_trees: Cannot merge two trees of different degrees." << endl;
		system("pause");
		exit(1);
	}

	if (up(b->value, a->value, comparison_method))
		swap(a, b);

	if (a->degree == 0)
	{
		a->child = b;
		b->parent = a;
		a->degree = 1;
		return a;
	}

	a->degree++;
	BinomialHeapNode *ptr = a->child;
	while (ptr->sibling) ptr = ptr->sibling;
	ptr->sibling = b;
	b->parent = a;
	b->sibling = nullptr;

	return a;
}

void BinomialHeapNode::print_tree() const
{
	cout << this->value << " ";
	if (this->child == nullptr)
		return;

	queue<BinomialHeapNode*> q;
	q.push(this->child);

	BinomialHeapNode *ptr = this->child->sibling;
	while (ptr)
	{
		q.push(ptr);
		ptr = ptr->sibling;
	}

	BinomialHeapNode *curr_node;
	while (!q.empty())
	{
		curr_node = q.front();
		q.pop();

		cout << curr_node->value << " ";

		if (curr_node->child != nullptr)
		{
			q.push(curr_node->child);
			BinomialHeapNode *ptr = curr_node->child->sibling;
			while (ptr)
			{
				q.push(ptr);
				ptr = ptr->sibling;
			}
				
		}
	}
	cout << endl;
}
