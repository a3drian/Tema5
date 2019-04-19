#include <iostream>
#include <vector>

#define sout std::cout<<"\n"
#define getch system("pause")
#define type int

//template <class T>
struct Nod {

	int key;
	Nod * left;
	Nod * right;
	Nod * parent;

	Nod(int key) {
		this->key = key;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}

	bool isLeaf() {
		if (this->left == NULL && this->right == NULL) {
			return true;
		}
		return false;
	}
};

struct Arbore_Caut {

	Nod * root;

	Arbore_Caut() {
		this->root = NULL;
	}

	void insert(Nod *);
	void print(Nod *);
	void construct(std::vector<Nod*>);
};

void Arbore_Caut::insert(Nod * element) {
	Nod * x = this->root;
	Nod * y = NULL;

	while (x != NULL) {
		y = x;
		if (element->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	element->parent = y;

	if (y == NULL) {
		this->root = element;
	} else {
		if (element->key < y->key) {
			y->left = element;
		} else {
			y->right = element;
		}
	}

}

void printBT(const std::string & prefix, Nod * nod, bool isLeft) {
	if (nod != nullptr)
	{
		for (int i = 0; i < prefix.size(); i++) {
			std::cout << prefix[i];
		}

		std::cout << (isLeft ? "s" : "d");

		// print the value of the node
		std::cout << nod->key << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), nod->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), nod->right, false);
	}
}

void Arbore_Caut::construct(std::vector<Nod*> noduri) {
	for (int i = 0; i < noduri.size(); i++) {
		this->insert(noduri[i]);
	}
}

int main() {

	Arbore_Caut copac = Arbore_Caut();
	//Nod * leaf = new Nod(14);

	int dim;
	std::cin >> dim;

	std::vector<Nod*> listaNoduri(dim);

	for (int i = 0; i < dim; i++) {
		int valoare;
		std::cout << "val: ";
		std::cin >> valoare;
		Nod * leaf = new Nod(valoare);
		listaNoduri[i] = leaf;
	}

	copac.construct(listaNoduri);

	//copac.print(copac.root);

	std::string prefix = "";
	printBT(prefix, copac.root, false);

	sout;
	getch;
	return 0;
}