#include <iostream>
#include <fstream>
#include <vector>

#define sout std::cout<<"\n"
#define getch system("pause")
#define type int

//template <class T>
struct Nod {

	int info;
	Nod * left;
	Nod * right;
	Nod * parent;

	Nod(int key) {
		this->info = key;
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
	Nod * search(int key);
	void print(Nod *);
	void construct(std::vector<Nod*>);
};

void Arbore_Caut::insert(Nod * element) {
	Nod * x = this->root;
	Nod * y = NULL;

	while (x != NULL) {
		y = x;
		if (element->info < x->info) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	element->parent = y;

	if (y == NULL) {
		this->root = element;
	} else {
		if (element->info < y->info) {
			y->left = element;
		} else {
			y->right = element;
		}
	}

}

Nod * Arbore_Caut::search(int key) {
	Nod * leaf = new Nod(key);

	Nod * temp = this->root;

	while (temp != NULL) {
		if (temp->info < leaf->info) {

		}
	}

	return leaf;
}

void printBT(const std::string & prefix, Nod * nod, bool isLeft) {
	if (nod != NULL)
	{
		for (int i = 0; i < prefix.length(); i++) {
			std::cout << prefix[i];
		}

		std::cout << (isLeft ? "st--" : "dr--");

		// print the value of the node
		std::cout << nod->info << std::endl;

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
	//std::cout << "Noduri: ";
	//std::cin >> dim;

	std::ifstream f("problema1/noduri.in");

	f >> dim;
	std::vector<Nod*> listaNoduri(dim);

	for (int i = 0; i < dim; i++) {
		int valoare;
		f >> valoare;
		Nod * leaf = new Nod(valoare);
		listaNoduri[i] = leaf;
	}

	f.close();

	//for (int i = 0; i < dim; i++) {
	//	int valoare;
	//	std::cout << "val: ";
	//	std::cin >> valoare;
	//	Nod * leaf = new Nod(valoare);
	//	listaNoduri[i] = leaf;
	//}

	copac.construct(listaNoduri);

	//copac.print(copac.root);

	std::string prefix = "";
	printBT(prefix, copac.root, false);

	sout;
	getch;
	return 0;
}