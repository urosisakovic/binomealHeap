#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(string comparison_method) { bh = new BinomialHeap(comparison_method); }

PriorityQueue::~PriorityQueue() { delete bh; }

bool PriorityQueue::empty() const { return bh->first == nullptr; }

int PriorityQueue::front() const { return bh->get()->get_value(); }

int PriorityQueue::pop(int *steps)
{
	int ret_value = front();
	bh->remove(steps);
	return ret_value;
}

void PriorityQueue::push(int value, int *steps) { bh->add(value, steps); }


// Permutuje niz arr[] od n elemenata na pseudo-slucajan nacin.
void shuffle(int arr[], int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		int idx = rand() % (n - i) + i;
		swap(arr[i], arr[idx]);
	}
}

// Skalira datu vrednost i daje joj pomeraj. Nije neophodno. Uvedeno radi lepse rasporednjenosti brojeve.
// Moglo je i da se ne uvede.
int transform(int x, int offset, int scale) { return x * scale + offset; }

// Generise se size pseudo-slucajnih brojeva i dodaju se u p. r.
void PriorityQueue::fill_random(int size, int *steps)
{
	int *help_arr = new int[size];
	for (int i = 0; i < size; i++) help_arr[i] = i;

	shuffle(help_arr, size);

	for (int i = 0; i < size; i++) help_arr[i] = transform(help_arr[i], 100, 10 * size);

	for (int i = 0; i < size; i++) push(help_arr[i], steps);

	delete[] help_arr;
}

// Citaju se brojevi iz fajla i ubacuju u red.
void PriorityQueue::fill_from_file(string file_path, int *steps)
{
	ifstream file;
	file.open(file_path);
	if (!file.is_open()) 
	{
		cout << "fill_from_file: Cannot open file." << endl;
		system("pause");
		exit(1);
	}

	int buffer;
	while (!file.eof())
	{
		file >> buffer;
		this->push(buffer, steps);
	}
}

// Bira se da li ucitavamo brojeve iz fajla ili ih i generisemo i zatim se mere performanse.
// Obratiti paznju da se nakon merenja performanse brojevi ne izbacuju iz reda.
// Funkcija se moze pozivati vise puta za redom i pokazivati promenu performansi iste
// operacije kada je red pun nasuprot tome kad je red prazan.
void PriorityQueue::print_performance_measures(int size, string file_path)
{
	int steps = 0;
	auto t0 = chrono::steady_clock::now();

	if (size < 0)
		fill_from_file(file_path, &steps);
	else
		fill_random(size, &steps);

	auto t1 = chrono::steady_clock::now();
	cout << "Insertion time in microseconds: "
		<< chrono::duration_cast<chrono::microseconds>(t1 - t0).count() << endl;
	cout << "Insertion steps count: " << steps << endl;

	steps = 0;
	t0 = chrono::steady_clock::now();
	pop(&steps);
	t1 = chrono::steady_clock::now();
	cout << "Extraction time in microseconds: "
		<< chrono::duration_cast<chrono::microseconds>(t1 - t0).count() << endl;
	cout << "Extraction steps count: " << steps << endl;
}