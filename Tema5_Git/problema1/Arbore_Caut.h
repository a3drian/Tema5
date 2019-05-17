#pragma once

#include "Nod.h"

struct Arbore_Caut {

	Nod * root;

	Arbore_Caut() {
		this->root = nullptr;
	}

	void insert(Nod *);

	Nod * search(int) const;

	Nod * maxim(Nod *) const;
	Nod * minim(Nod *) const;

	Nod * predecesor(Nod *) const;
	Nod * succesor(Nod *) const;
	Nod * succesor(int) const;

	bool delete_element(Nod *);
	void print(Nod *);
	void construct(const std::vector<Nod*> &);
};

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

Nod* Arbore_Caut::succesor(Nod * root) const {

	Nod * temp = this->search(root->info);

	if (temp == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}

	//cazul in care avem subarbore drept, succesorul se cauta in valorile mai mari decat key-a noastra
	if (root->right != nullptr) {
		minim(root->right);
	}

	Nod * y = root->parent;
	while (y != nullptr && y == root->right) {
		root = y;
		y = root->parent;
	}

	if (y != nullptr) {
		std::cout << y->info << " se afla in arbore si este fiul lui " <<
			((y->parent) ? y->parent->info : y->info) << ".\n";
	}

	return y;
}

Nod* Arbore_Caut::predecesor(Nod * root) const {

	Nod * temp = this->search(root->info);

	if (temp == nullptr) {
		std::cout << root->info << " nu se afla in arbore.\n";
		return nullptr;
	}
}

bool Arbore_Caut::delete_element(Nod * node) {

	if (node == nullptr) {
		std::cout << "Nodul nu exista in arbore.\n";
		return false;
	}

	//daca e frunza, putem sterge direct dupa ce aflam pe ce parte a parintelui este
	{
		if (node->isLeaf()) {
			std::cout << "FRUNZA\n";
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

	//daca nu e frunza
	{
		std::cout << "NU E FRUNZA\n";
		if (node->parent->left == node) {
			node->parent->left = node->left;
			node->left->parent = node->parent;
			delete node;
			return true;
		}
	}

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

		std::cout << (isLeft ? "st--" : "dr--");

		// print the value of the node
		std::cout << nod->info << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), nod->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), nod->right, false);
	}
}
