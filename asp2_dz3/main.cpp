#include <iostream>
#include "PriorityQueue.h"
using namespace std;


void print_commands(bool start = false)
{
	if (!start) cout << endl << endl;
	cout << "OPERATIONS: " << endl;
	cout << "To initialize priority queue enter 1." << endl;
	cout << "To check if queue is empty enter 2." << endl;
	cout << "To get front element enter 3." << endl;
	cout << "To pop front element enter 4." << endl;
	cout << "To push element into the priority queue enter 5." << endl;
	cout << "To fill priority queue with random elements enter 6." << endl;
	cout << "To fill priority queue with elements from file enter 7." << endl;
	cout << "To measure performances enter 8." << endl;
	cout << "To end program enter 9." << endl;
	cout << endl;
}

int main()
{
	PriorityQueue *pq = nullptr;
	int op;

	print_commands(true);
	
	cin >> op;
	while (true)
	{
		switch (op)
		{
			case 1:
			{
				if (pq != nullptr)
				{
					delete pq;
					pq = nullptr;
				}

				cout << "To initialize max priority queue enter 'max' and to initialize min priority queue enter 'min'." << endl;
				string pq_kind;
				cin >> pq_kind;
				pq = new PriorityQueue(pq_kind);
				break;
			}
			case 2:
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				if (pq->empty())
					cout << "Priority queue is EMPTY." << endl;
				else
					cout << "Priority queue is NOT EMPTY." << endl;
				break;
			}
			case 3: 
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				if (pq->empty())
				{
					cout << "Priority queue is empty." << endl;
					break;
				}
					
				cout << "The value of the front element is: " << pq->front() << endl;
				break;
			}
			case 4:
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				if (pq->empty())
				{
					cout << "Priority queue is empty." << endl;
					break;
				}

				pq->pop();
				cout << "Front element popped." << endl;
				break;
			}
			case 5: 
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				cout << "Enter the value of the element to be pushed into the priority queue: " << endl;
				int val;
				cin >> val;
				pq->push(val);
				break;
			}
			case 6:
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				cout << "Enter number of random elements to be pushed into the priority queue." << endl;
				int size;
				cin >> size;
				pq->fill_random(size);
				break;
			}
			case 7:
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				cout << "Enter file path to the file containg elements to be added to priority queue (one value per line)." << endl;
				string file_path;
				cin >> file_path;
				pq->fill_from_file(file_path);
				break;
			}
			case 8:
			{
				if (pq == nullptr)
				{
					cout << "Priority queue must be initialize first." << endl;
					break;
				}

				cout << "For random generated numbers enter 1. For numbers from file enter 2." << endl;
				int op1; cin >> op1;
				if (op1 == 1)
				{
					cout << "Enter number of elements to be added." << endl;
					int size;
					cin >> size;
					pq->print_performance_measures(size);
				}
				else if (op1 == 2)
				{
					cout << "Enter full file path to a file containg a number per line." << endl;
					string file_path;
					cin >> file_path;
					pq->print_performance_measures(-1, file_path);
				}
				else
				{
					cout << "Non existing command." << endl;
				}

				
				break;
			}
			case 9:
			{
				delete pq;
				cout << "End of program." << endl;
				system("pause");
				return 0;
			}
			default:
			{
				cout << "Operation code must have value between 1 and 9." << endl;
			}
		}

		print_commands();
		cin >> op;
	}
}