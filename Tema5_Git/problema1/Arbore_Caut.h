#pragma once

#include "Nod.h"

struct Arbore_Caut {

	Nod * root;
	unsigned short size;

	Arbore_Caut() {
		this->root = nullptr;
		this->size = 0;
	}

	unsigned short getSize();
	bool isEmpty();

	void insert(Nod *);

	Nod * search(int) const;

	Nod * maxim(Nod *) const;
	Nod * minim(Nod *) const;

	Nod * succesor(int) const;
	Nod * predecesor(int) const;

	void transplant(Nod *, Nod *);

	bool delete_element(Nod *);
	bool delete_el(Nod *);

	void print(unsigned short);
	void construct(const std::vector<Nod*> &);
	void empty();
};

unsigned short Arbore_Caut::getSize() {
	return this->size;
}

bool Arbore_Caut::isEmpty() {
	if (this->size == 0) {
		return true;
	}
	return false;
}

void Arbore_Caut::insert(Nod * element) {
	Nod * x = this->root;
	Nod * y = nullptr;

	while (x != nullptr) {
		y = x;
		if (element->info < x->info) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	element->parent = y;

	if (y == nullptr) {
		this->root = element;
	} else {
		if (element->info < y->info) {
			y->left = element;
		} else {
			y->right = element;
		}
	}

	this->size++;
}

Nod * Arbore_Caut::search(int key) const {

	Nod * temp = this->root;

	while (temp != nullptr) {
		if (temp->info == key) {
			std::cout << key << " se afla in arbore si este fiul lui " <<
				((temp->parent) ? temp->parent->info : temp->info) << ".\n";
			return temp;
		}
		if (temp->info < key) {
			temp = temp->right;
		} else {
			temp = temp->left;
		}
	}

	if (temp == nullptr) {
		std::cout << key << " nu se afla in arbore.";
		return nullptr;
	}
}

Nod * Arbore_Caut::maxim(Nod * root) const {
	//consideram nodul primit ca o radacina
	Nod * temp = this->search(root->info);

	if (temp == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}

	if (temp->right == nullptr) {
		std::cout << "Nodul " << root->info << " primit ca parametru este maximul din sub-arbore.\n";
		return root;
	} else {
		while (temp->right != nullptr) {
			temp = temp->right;
		}
		std::cout << "Nodul maxim este " << temp->info << ".\n";
		return temp;
	}

}

Nod * Arbore_Caut::minim(Nod * root) const {
	//consideram nodul primit ca o radacina
	Nod * temp = this->search(root->info);

	if (temp == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}

	if (temp->left == nullptr) {
		std::cout << "Nodul " << root->info << " primit ca parametru este minimul din sub-arbore.\n";
		return root;
	} else {
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		std::cout << "Nodul minim este " << temp->info << ".\n";
		return temp;
	}
}

Nod* Arbore_Caut::succesor(int key) const {

	Nod * x = search(key);
	Nod * y;

	if (x == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}

	//cazul in care avem subarbore drept, succesorul se cauta in valorile mai mari decat key-a noastra
	if (x->right != nullptr) {
		y = minim(x->right);
		if (y != nullptr) {
			std::cout << "Succesorul lui " << x->info << " este " << y->info << ".\n";
		}
		return y;
	}

	y = x->parent;

	while (y != nullptr && x == y->right) {
		x = y;
		y = y->parent;
	}

	if (y != nullptr) {
		std::cout << "Succesorul lui " << key << " este " << y->info << ".\n";
	} else {
		std::cout << key << " nu are succesor.\n";
	}

	return y;
}

Nod* Arbore_Caut::predecesor(int key) const {

	Nod * x = search(key);
	Nod * y;

	if (x == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}

	//cazul in care avem subarbore drept, succesorul se cauta in valorile mai mari decat key-a noastra
	if (x->left != nullptr) {
		y = maxim(x->left);
		if (y != nullptr) {
			std::cout << "Predecesorul lui " << x->info << " este " << y->info << ".\n";
		}
		return y;
	}

	y = x->parent;

	while (y != nullptr && x == y->left) {
		x = y;
		y = y->parent;
	}

	if (y != nullptr) {
		std::cout << "Predecesorul lui " << key << " este " << y->info << ".\n";
	} else {
		std::cout << key << " nu are predecesor.\n";
	}

	return y;
}

void Arbore_Caut::transplant(Nod * vechi, Nod * nou) {

	if (vechi->parent == nullptr) {
		this->root = nou;
	} else {
		if (vechi == vechi->parent->left) {
			vechi->parent->left = nou;
		} else {
			vechi->parent->right = nou;
		}
	}

	if (nou != nullptr) {
		nou->parent = vechi->parent;
	}

	//Nod * parinteVechi = vechi->parent;
	//Nod * fiuStangVechi = vechi->left;

	//fiuStangVechi->parent = nou;
	//if (parinteVechi) { //stergem nodul root
	//	parinteVechi->right = nou;
	//} else {
	//	//nou->left = this->root->left;
	//	this->root = nou;
	//	//this->root->right = nou;
	//}
	//nou->left = fiuStangVechi;

	//vechi->left = vechi->right = vechi->parent = nullptr;
	//delete vechi;
}

bool Arbore_Caut::delete_element(Nod * node) {

	if (node == nullptr) {
		std::cout << "Nodul nu exista in arbore.\n";
		return false;
	}

	//CAZ 1 = z este frunza
	//daca e frunza, putem sterge direct dupa ce aflam pe ce parte a parintelui este
	{
		if (node->isLeaf()) {
			imp("frunza");
			if (node->parent->right == node) {
				node->parent->right = nullptr;
				delete node;
				return true;
			}
			if (node->parent->left == node) {
				node->parent->left = nullptr;
				delete node;
				return true;
			}
		}
	}

	//CAZ 2 = z are un singur fiu nenul
	//daca nu e frunza si are 1 fiu
	{
		if (node->hasOneSon()) {
			imp("1 fiu");
		}
	}

	//CAZ 3 = z are ambii fii nenuli
	//daca nu e frunza si are 2 fii
	{
		if (node->hasTwoSons()) {
			imp("2 fii");
			Nod * temp = this->succesor(node->info);
			transplant(node, temp);
		}
	}

}

bool Arbore_Caut::delete_el(Nod * node) {

	if (node == nullptr) {
		std::cout << "Nodul nu exista in arbore.\n";
		return false;
	}

	if (node->left == nullptr) {
		transplant(node, node->right);
	} else {
		if (node->right == nullptr) {
			transplant(node, node->left);
		} else {
			Nod * y = succesor(node->info);
			if (y != node->right) {
				transplant(y, y->right);
				y->right = node->right;
				node->right->parent = y;
			}
			transplant(node, y);
			y->left = node->left;
			node->left->parent = y;
		}
	}

	this->size--;
}

void Arbore_Caut::construct(const std::vector<Nod*> &noduri) {
	for (int i = 0; i < noduri.size(); i++) {
		this->insert(noduri[i]);
	}
}

void printBT(const std::string & prefix, Nod * nod, bool isLeft) {
	if (nod != nullptr)
	{
		for (int i = 0; i < prefix.length(); i++) {
			std::cout << prefix[i];
		}

		std::cout << (isLeft ? "st__" : "dr__");

		// print the value of the node
		std::cout << nod->info << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), nod->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), nod->right, false);
	}
}
