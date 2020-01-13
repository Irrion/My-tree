#include <iostream>
using namespace std;
struct tree_elem
{
	int key;
	int value;
	tree_elem*left_branch;
	tree_elem*right_branch;
	tree_elem*prev;
	tree_elem(int key, int value, tree_elem*left = nullptr, tree_elem* previos = nullptr, tree_elem*right = nullptr)
	{
		this->key = key;
		this->value = value;
		this->left_branch = left;
		this->right_branch = right;
		this->prev = previos;
	}
};
class tree
{
private:
	tree_elem* head;
	void prin_all(tree_elem*current)
	{
		if (current != nullptr)
		{
			cout << current->value << " - " << current->key << endl;
			prin_all(current->left_branch);
			prin_all(current->right_branch);
		}
	}
public:
	tree()
	{
		head = nullptr;
	}
	~tree()
	{
		remove_all();
	}
	void add(int key, int value)
	{
		tree_elem *new_elem = new tree_elem(key, value);
		if (head == nullptr)
		{
			head = new_elem;
		}
		else
		{
			tree_elem *current = head;
				while (current != nullptr)
				{
					if (current->key == key)
					{
						current->value = new_elem->value;
						break;
					}
					else if (key < current->key)
					{
						if (current->left_branch != nullptr)
						{
							current = current->left_branch;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (current->right_branch != nullptr)
						{
							current = current->right_branch;
						}
						else
						{
							break;
						}
					}
				}
				if (current->key != new_elem->key)
				{
					new_elem->prev = current;
					new_elem->left_branch = nullptr;
					new_elem->right_branch = nullptr;
					if (key < current->key)
					{
						current->left_branch = new_elem;
					}
					else
					{
						current->right_branch = new_elem;
					}
				}
				else
				{
					delete new_elem;
				}
		}
	}
	void remove(int key)
	{
		tree_elem*current = head;
		if (head != nullptr)
		{
			if (key != head->key)
			{
				while (current->key != key)
				{
					if (key > current->key)
					{
						if (current->right_branch != nullptr)
						{
							current = current->right_branch;
						}
						else
						{
							cout << "I not see elements" << endl;
							return;
						}
					}
					else
					{
						if (current->left_branch != nullptr)
						{
							current = current->left_branch;
						}
						else
						{
							cout << "I not found elements" << endl;
							return;
						}
					}
				}
				tree_elem* inher = current;

				if (current->right_branch != nullptr && current->left_branch != nullptr)
				{
					current = current->left_branch;
					if (current->right_branch != nullptr)
					{
						while (current->right_branch != nullptr)
						{
							current = current->right_branch;
						}
						if (current->left_branch != nullptr)
						{
							current->left_branch->prev = current->prev;
							current->prev->right_branch = current->left_branch;
						}
						else
						{
							current->prev->right_branch = nullptr;
						}
						current->right_branch = inher->right_branch;
						current->left_branch = inher->left_branch;
						current->prev = inher->prev;
						current->right_branch->prev = current;
						current->left_branch->prev = current;
						if (current->key > inher->prev->key)
						{
							inher->prev->right_branch = current;
							
						}
						else if (current->key < inher->prev->key)
						{
							inher->prev->left_branch = current;
						}
						delete inher;
						
					}
					else
					{
						current->right_branch = inher->right_branch;
						current->prev = inher->prev;
						current->right_branch->prev = current;
						if (current->key > inher->prev->key)
						{
							inher->prev->right_branch = current;

						}
						else if (current->key < inher->prev->key)
						{
							inher->prev->left_branch = current;
						}
						delete inher;
					}

				}
				else if (current->right_branch == nullptr && current->left_branch == nullptr)
				{
					if (current->prev->key < inher->key)
					{
						current->prev->right_branch = nullptr;
					}
					else
					{
						current->prev->left_branch = nullptr;
					}
					delete inher;
				}
				else if (current->right_branch != nullptr && current->left_branch == nullptr)
				{
					current = current->right_branch;
					current->prev = inher->prev;
					if (current->key > inher->prev->key)
					{
						inher->prev->right_branch = current;

					}
					else if (current->key < inher->prev->key)
					{
						inher->prev->left_branch = current;
					}
					delete inher;
				}
				else if (current->right_branch == nullptr && current->left_branch != nullptr)
				{
					current = current->left_branch;
					current->prev = inher->prev;
					if (current->key > inher->prev->key)
					{
						inher->prev->right_branch = current;

					}
					else if (current->key < inher->prev->key)
					{
						inher->prev->left_branch = current;
					}
					delete  inher;
				}
			}
			else
			{
				if (current->left_branch == nullptr && current->right_branch == nullptr)
				{
					delete current;
				}
				else if (current->left_branch != nullptr && current->right_branch != nullptr)
				{
					head = head->left_branch;
					if (head->right_branch != nullptr)
					{
						while (head->right_branch != nullptr)
						{
							head = head->right_branch;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head->prev;
							head->prev->right_branch = head->left_branch;
						}
						else
						{
							head->prev->right_branch = nullptr;
						}
						head->right_branch = current->right_branch;
						head->left_branch = current->left_branch;
						head->prev = nullptr;
						if (head->right_branch != nullptr)
						{
							head->right_branch->prev = head;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head;
						}
						delete current;
					}
					else
					{
						head->right_branch = current->right_branch;
						head->prev = nullptr;
						if (head->right_branch != nullptr)
						{
							head->right_branch->prev = head;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head;
						}
						delete current;
					}
				}
				else if (current->right_branch != nullptr && current->left_branch == nullptr)
				{
					head = head->right_branch;
					head->prev = nullptr;
					delete current;
				}
				else if (current->right_branch == nullptr && current->left_branch != nullptr)
				{
					head = head->left_branch;
					head->prev = nullptr;
					delete current;
				}
			}
		}
		else
		{
			cout << "I not see elements" << endl;
		}
	}
	void find(int key)
	{
		tree_elem* current = head;
		if (head == nullptr)
		{
			cout << "I not found" << endl;
		}
		else
		{
			while (current != nullptr)
			{
				if (key == current->key)
				{
					cout << current->value << endl;
					break;
				}
				else if (key > current->key)
				{
					if (current->right_branch != nullptr)
					{
						current = current->right_branch;
					}
					else
					{
						cout << "I not found" << endl;
						break;
					}
				}
				else if (key < current->key)
				{
					if (current->left_branch != nullptr)
					{
						current = current->left_branch;
					}
					else
					{
						cout << "I not found" << endl;
						break;
					}
				}
			}
		}
	}
	void remove_all()
	{
		if (head != nullptr)
		{
			while (head != nullptr)
			{
				tree_elem*current = head;
				if (head->left_branch == nullptr && head->right_branch == nullptr)
				{
					delete head;
					head = nullptr;
				}
				else if (current->left_branch != nullptr && current->right_branch != nullptr)
				{
					head = head->left_branch;
					if (head->right_branch != nullptr)
					{
						while (head->right_branch != nullptr)
						{
							head = head->right_branch;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head->prev;
							head->prev->right_branch = head->left_branch;
						}
						else
						{
							head->prev->right_branch = nullptr;
						}
						head->right_branch = current->right_branch;
						head->left_branch = current->left_branch;						
						head->prev = nullptr;
						if (head->right_branch != nullptr)
						{
							head->right_branch->prev = head;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head;
						}
						delete current;
					}
					else
					{
						head->right_branch = current->right_branch;
						head->prev = nullptr;
						if (head->right_branch != nullptr)
						{
							head->right_branch->prev = head;
						}
						if (head->left_branch != nullptr)
						{
							head->left_branch->prev = head;
						}
						delete current;
					}
				}
				else if (current->right_branch != nullptr && current->left_branch == nullptr)
				{
					head = head->right_branch;
					head->prev = nullptr;
					delete current;
				}
				else if (current->right_branch == nullptr && current->left_branch != nullptr)
				{
					head = head->left_branch;
					head->prev = nullptr;
					delete current;
				}
			}
		}
		else
		{
			cout << "Tree is empty" << endl;
		}
	}
	void print_all()
	{
		tree_elem*current = head;
		prin_all(current);	
	}
};


void old() {

	tree n;

	n.add(100, 4);
	n.add(100, 3);
	n.add(163, 5);
	n.add(40, 6);
	n.add(60, 7);
	n.add(111, 1);
	n.add(200, 9);
	n.add(102, 8);
	n.add(150, 11);
	n.add(170, 22);
	n.add(210, 33);
	n.add(101, 23);
	n.add(103, 321);
	n.add(130, 854);
	n.add(151, 64);
	n.add(164, 76);
	n.add(171, 43);
	n.add(209, 56);
	n.add(211, 981);

	n.print_all();
	cout << endl;
	n.find(100);
	n.find(50);
	n.find(163);
	n.find(40);
	n.find(60);
	n.find(111);
	n.find(200);
	n.find(102);
	n.find(150);
	n.find(170);
	n.find(210);
	n.find(101);
	n.find(103);
	n.find(130);
	n.find(151);
	n.find(164);
	n.find(171);
	n.find(209);
	n.find(211);
	cout << "\n";

	n.remove_all();

	cout << "\n";
	n.find(100);
	n.find(50);
	n.find(163);
	n.find(40);
	n.find(60);
	n.find(111);
	n.find(200);
	n.find(102);
	n.find(150);
	n.find(170);
	n.find(210);
	n.find(101);
	n.find(103);
	n.find(130);
	n.find(151);
	n.find(164);
	n.find(171);
	n.find(209);
	n.find(211);
	system("pause");
}


void test_0() {

	/*
							20
			10							30
	5				15			 25				35
  3   7	          13  17	   23  27		  33  37
	
	*/
	tree tr;
	tr.add(20, 0);
	tr.add(10, 1);
	tr.add(5, 2);
	tr.add(3, 3);
	tr.add(7, 4);
	tr.add(15, 5);
	tr.add(13, 6);
	tr.add(17, 7);
	tr.add(30, 8);
	tr.add(25, 9);
	tr.add(23, 10);
	tr.add(27, 11);
	tr.add(35, 12);
	tr.add(33, 13);
	tr.add(37, 14);
	tr.add(26, 35);
	tr.add(16, 76);

	tr.remove(10);
	tr.print_all();
}
void test_0_1() {

	/*
							20
			10							30
	5				15			 25				35

	*/
	tree tr;
	tr.add(20, 0);
	tr.add(10, 1);
	tr.add(5, 2);
	tr.add(15, 5);
	tr.add(30, 8);
	tr.add(25, 9);
	tr.add(35, 12);

	tr.remove(30);
	tr.print_all();
}

int main()
{
	test_0();
	system("pause");
	return 0;
}





