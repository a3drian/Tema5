#pragma once

#include "Nod.h"

#include <sstream>
#include <algorithm>    // std::random_shuffle
#include <queue>

#include <stdio.h>
#include <windows.h>
#include <wincon.h>

class Arbore_AVL {
public:
	Nod * root;
	unsigned short size;

	Arbore_AVL() {
		this->root = nullptr;
		this->size = 0;
	}

	unsigned short getSize() const;
	bool isEmpty() const; //daca nu e const, nu merge in cauta() pentru ca nu avem garantia ca isEmpty() nu modifica ceva in obiectul de tip Arbore_AVL

	Nod * search(int) const;

	Nod * maxim(Nod *) const;
	Nod * minim(Nod *) const;

	Nod * succesor(int) const;
	Nod * predecesor(int) const;

	void transplant(Nod *, Nod *);

	void construct(const std::vector<Nod*> &);
	void empty();
	void emptyToFile(std::ofstream &);
	void emptyToFileRandom(std::ofstream &, std::vector<Nod*>);

	void emptyRandom(std::vector<Nod*>);

	void balansare_insert(Nod* parinteNodSters);
	void insert_repair(Nod *);

	void balansare_delete(Nod* parinteNodSters);
	bool delete_repair(Nod *);

	//Print
	void preordine(Nod*) const;
	void inordine(Nod*) const;
	void postordine(Nod*) const;
	void printLevelByLevel(Nod*) const;

	void print(unsigned short) const;

	void rotate_right(int);
	void rotate_left(int);

	void merge(Arbore_AVL);

	int inaltime_maxima(Nod*);

	void inaltime(Nod*);
	void factor(Nod*);
	void adancime(Nod*);

	/*Printare frumi*/
	struct LevelNode
	{
		int leftSpacing, rightSpacing;
		Nod* node;
		bool hasLeftchild, hasRightChild;
	};

	int GetDepth(Nod* current) const
	{
		if (current == NULL)
			return 0;
		else
		{
			int leftDepth = GetDepth(current->left);
			int rightDepth = GetDepth(current->right);

			if (leftDepth > rightDepth)
				return(leftDepth + 1);
			else return(rightDepth + 1);
		}
	}
	int GetLeftSpacing(int level, int maxLevel) const
	{
		int sum = 0, aux;
		for (int index = 0; index < maxLevel - level; index++)
		{
			aux = 2;
			for (int index2 = 1; index2 <= index; index2++)
				aux *= 2;
			sum += aux;
		}
		return sum;
	}
	void ShowChar(const char *ch, int rep) const
	{
		for (int index = 0; index < rep; index++)
			std::cout << ch;
	}
	void ShowCharToFile(const char *ch, int rep, std::ofstream &f) const
	{
		for (int index = 0; index < rep; index++)
			f << ch;
	}

	void PrintLevelOrder(Nod *root) const
	{
		if (root == NULL)
			return;

		int depth = this->GetDepth(root) - 1;
		int currentLevel = 0, nodeCount;		//Variabile care ne ajuta la parcurgerea pe nivel
		int leftSpacing, nextLevelSpacing;		//Folositoare la formatarea textului
		int previousLevelDim;
		int numberSizeCorrector = 0, aux;

		std::queue<LevelNode> myQueue;
		LevelNode currentLevelNode, leftChild, rightChild;				//Variabile folosite la gasirea urmatoarelor noduri
		LevelNode *previousLevelNodes = new LevelNode[pow(2, depth)];	//Vector care retine nodurile de pe nivelul anterior. Avem nevoie sa stim ce copii au.

		leftSpacing = GetLeftSpacing(currentLevel, depth);

		//Implementam primul nod
		currentLevelNode.node = root;
		currentLevelNode.leftSpacing = leftSpacing;
		currentLevelNode.rightSpacing = currentLevelNode.leftSpacing + 3;
		currentLevelNode.hasLeftchild = true;
		currentLevelNode.hasRightChild = true;

		myQueue.push(currentLevelNode);

		while (myQueue.empty() == false)
		{
			nodeCount = myQueue.size();		//Retinem cate noduri avem pe nivel
			previousLevelDim = 0;

			nextLevelSpacing = GetLeftSpacing(currentLevel + 1, depth);

			while (nodeCount > 0)
			{
				currentLevelNode = myQueue.front();
				myQueue.pop();
				previousLevelNodes[previousLevelDim] = currentLevelNode;	//Retinem nodul curent ca sa putem afisa muchiile dupa ce trecem la urmatorul nivel

				numberSizeCorrector = 0;	//In caz ca numarul are prea multe zecimale trebuie sa corectam spatierea, iar datorita afisarii factorului trebuie mai multa corectura

				ShowChar(" ", currentLevelNode.leftSpacing);
				if (currentLevelNode.node == nullptr)
					std::cout << " ";
				else {
					std::cout << currentLevelNode.node->info;
					aux = currentLevelNode.node->info;
					while (aux / 10 != 0)
					{
						numberSizeCorrector++;
						aux /= 10;
					}
				}
				if (nodeCount != 1)
					ShowChar(" ", currentLevelNode.rightSpacing - numberSizeCorrector);

				if (currentLevel <= depth)
				{
					//Left child
					//Vrem sa aflam daca copilul stang exista sau nu. Deoarece e posibil ca nici tatal sa nu existe trebuie facute 2 comparari
					if (currentLevelNode.node == nullptr)
						leftChild.node = nullptr;
					else
						leftChild.node = currentLevelNode.node->left;

					if (leftChild.node == nullptr)
						previousLevelNodes[previousLevelDim].hasLeftchild = false;
					else
						previousLevelNodes[previousLevelDim].hasLeftchild = true;

					leftChild.leftSpacing = nextLevelSpacing;
					leftChild.rightSpacing = leftChild.leftSpacing + 3;

					//Right child
					//Vrem sa aflam daca copilul drept exista sau nu. Deoarece e posibil ca nici tatal sa nu existe trebuie facute 2 comparari
					if (currentLevelNode.node == nullptr)
						rightChild.node = nullptr;
					else
						rightChild.node = currentLevelNode.node->right;
					if (rightChild.node == nullptr)
						previousLevelNodes[previousLevelDim].hasRightChild = false;
					else
						previousLevelNodes[previousLevelDim].hasRightChild = true;

					rightChild.leftSpacing = nextLevelSpacing;
					rightChild.rightSpacing = rightChild.leftSpacing + 3;

					//Adaugam toate nodurile in coada pana cand ajungem la ultimul nivel.
					//Adaugam si noduri nule ca sa putem pastra afisarea uniforma, in cazul lor afisam spatierea si inca un spatiu in loc de valoare.
					if (currentLevel != depth)
					{
						myQueue.push(leftChild);
						myQueue.push(rightChild);
					}

					previousLevelDim++;
				}

				nodeCount--;
			}
			//Afisaza factorul de balansare
			std::cout << "\n";
			for (int index = 0; index < previousLevelDim; index++)
			{
				numberSizeCorrector = 0;
				ShowChar(" ", previousLevelNodes[index].leftSpacing);
				if (previousLevelNodes[index].node == nullptr)
					std::cout << " ";
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					std::cout << previousLevelNodes[index].node->getFactor();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					if (previousLevelNodes[index].node->getFactor() < 0)
						numberSizeCorrector++;
				}
				if (index != previousLevelDim - 1);
				ShowChar(" ", previousLevelNodes[index].rightSpacing - numberSizeCorrector);
			}

			//Afisaza inaltimea
			std::cout << "\n";
			for (int index = 0; index < previousLevelDim; index++)
			{
				numberSizeCorrector = 0;
				ShowChar(" ", previousLevelNodes[index].leftSpacing);
				if (previousLevelNodes[index].node == nullptr)
					std::cout << " ";
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					std::cout << previousLevelNodes[index].node->getHeight();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					if (previousLevelNodes[index].node->getHeight() < 0)
						numberSizeCorrector++;
				}
				if (index != previousLevelDim - 1);
				ShowChar(" ", previousLevelNodes[index].rightSpacing - numberSizeCorrector);
			}

			//Afiseaza adancimea
			//std::cout << "\n";
			//for (int index = 0; index < previousLevelDim; index++)
			//{
			//	numberSizeCorrector = 0;
			//	ShowChar(" ", previousLevelNodes[index].leftSpacing);
			//	if (previousLevelNodes[index].node == nullptr)
			//		std::cout << " ";
			//	else {
			//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			//		std::cout << previousLevelNodes[index].node->getDepth();
			//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			//		if (previousLevelNodes[index].node->getDepth() < 0)
			//			numberSizeCorrector++;
			//	}
			//	if (index != previousLevelDim - 1);
			//	ShowChar(" ", previousLevelNodes[index].rightSpacing - numberSizeCorrector);
			//}

			std::cout << "\n";
			currentLevel++;
			//Calculam cate linii ne trebuie sa afisam muchiile
			for (int slashesIndex = 1; slashesIndex <= leftSpacing - nextLevelSpacing - 1; slashesIndex++)
			{
				//Pentru fiecare nod afisem muchiile cu spatiere si verificam daca are sau nu copil
				for (int index = 0; index < previousLevelDim; index++)
				{
					ShowChar(" ", leftSpacing - slashesIndex);

					if (previousLevelNodes[index].hasLeftchild == true)
						std::cout << "/";
					else
						std::cout << " ";
					ShowChar(" ", 2 * slashesIndex - 1);

					if (previousLevelNodes[index].hasRightChild == true)
						std::cout << "\\";
					else
						std::cout << " ";
					if (index != previousLevelDim - 1)
						ShowChar(" ", leftSpacing + 3 - slashesIndex);
				}

				std::cout << "\n";
			}
			leftSpacing = nextLevelSpacing;
		}
		delete[] previousLevelNodes;
	}
	void PrintLevelOrderToFile(Nod *root, std::ofstream &f) const
	{
		if (root == NULL)
			return;

		int depth = this->GetDepth(root) - 1;
		int currentLevel = 0, nodeCount;		//Variabile care ne ajuta la parcurgerea pe nivel
		int leftSpacing, nextLevelSpacing;		//Folositoare la formatarea textului
		int previousLevelDim;
		int numberSizeCorrector = 0, aux;

		std::queue<LevelNode> myQueue;
		LevelNode currentLevelNode, leftChild, rightChild;				//Variabile folosite la gasirea urmatoarelor noduri
		LevelNode *previousLevelNodes = new LevelNode[pow(2, depth)];	//Vector care retine nodurile de pe nivelul anterior. Avem nevoie sa stim ce copii au.

		leftSpacing = GetLeftSpacing(currentLevel, depth);

		//Implementam primul nod
		currentLevelNode.node = root;
		currentLevelNode.leftSpacing = leftSpacing;
		currentLevelNode.rightSpacing = currentLevelNode.leftSpacing + 3;
		currentLevelNode.hasLeftchild = true;
		currentLevelNode.hasRightChild = true;

		myQueue.push(currentLevelNode);

		while (myQueue.empty() == false)
		{
			nodeCount = myQueue.size();		//Retinem cate noduri avem pe nivel
			previousLevelDim = 0;

			nextLevelSpacing = GetLeftSpacing(currentLevel + 1, depth);

			while (nodeCount > 0)
			{
				currentLevelNode = myQueue.front();
				myQueue.pop();
				previousLevelNodes[previousLevelDim] = currentLevelNode;	//Retinem nodul curent ca sa putem afisa muchiile dupa ce trecem la urmatorul nivel

				numberSizeCorrector = 0;	//In caz ca numarul are prea multe zecimale trebuie sa corectam spatierea, iar datorita afisarii factorului trebuie mai multa corectura

				ShowCharToFile(" ", currentLevelNode.leftSpacing, f);
				if (currentLevelNode.node == nullptr)
					f << " ";
				else {
					f << currentLevelNode.node->info;
					aux = currentLevelNode.node->info;
					while (aux / 10 != 0)
					{
						numberSizeCorrector++;
						aux /= 10;
					}
				}
				if (nodeCount != 1)
					ShowCharToFile(" ", currentLevelNode.rightSpacing - numberSizeCorrector, f);

				if (currentLevel <= depth)
				{
					//Left child
					//Vrem sa aflam daca copilul stang exista sau nu. Deoarece e posibil ca nici tatal sa nu existe trebuie facute 2 comparari
					if (currentLevelNode.node == nullptr)
						leftChild.node = nullptr;
					else
						leftChild.node = currentLevelNode.node->left;

					if (leftChild.node == nullptr)
						previousLevelNodes[previousLevelDim].hasLeftchild = false;
					else
						previousLevelNodes[previousLevelDim].hasLeftchild = true;

					leftChild.leftSpacing = nextLevelSpacing;
					leftChild.rightSpacing = leftChild.leftSpacing + 3;

					//Right child
					//Vrem sa aflam daca copilul drept exista sau nu. Deoarece e posibil ca nici tatal sa nu existe trebuie facute 2 comparari
					if (currentLevelNode.node == nullptr)
						rightChild.node = nullptr;
					else
						rightChild.node = currentLevelNode.node->right;
					if (rightChild.node == nullptr)
						previousLevelNodes[previousLevelDim].hasRightChild = false;
					else
						previousLevelNodes[previousLevelDim].hasRightChild = true;

					rightChild.leftSpacing = nextLevelSpacing;
					rightChild.rightSpacing = rightChild.leftSpacing + 3;

					//Adaugam toate nodurile in coada pana cand ajungem la ultimul nivel.
					//Adaugam si noduri nule ca sa putem pastra afisarea uniforma, in cazul lor afisam spatierea si inca un spatiu in loc de valoare.
					if (currentLevel != depth)
					{
						myQueue.push(leftChild);
						myQueue.push(rightChild);
					}

					previousLevelDim++;
				}

				nodeCount--;
			}
			//Afisaza factorul de balansare
			f << "\n";
			for (int index = 0; index < previousLevelDim; index++)
			{
				numberSizeCorrector = 0;
				ShowCharToFile(" ", previousLevelNodes[index].leftSpacing, f);
				if (previousLevelNodes[index].node == nullptr)
					f << " ";
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					f << previousLevelNodes[index].node->getFactor();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					if (previousLevelNodes[index].node->getFactor() < 0)
						numberSizeCorrector++;
				}
				if (index != previousLevelDim - 1);
				ShowCharToFile(" ", previousLevelNodes[index].rightSpacing - numberSizeCorrector, f);
			}

			//Afisaza inaltimea
			f << "\n";
			for (int index = 0; index < previousLevelDim; index++)
			{
				numberSizeCorrector = 0;
				ShowCharToFile(" ", previousLevelNodes[index].leftSpacing, f);
				if (previousLevelNodes[index].node == nullptr)
					f << " ";
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					f << previousLevelNodes[index].node->getHeight();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					if (previousLevelNodes[index].node->getHeight() < 0)
						numberSizeCorrector++;
				}
				if (index != previousLevelDim - 1);
				ShowCharToFile(" ", previousLevelNodes[index].rightSpacing - numberSizeCorrector, f);
			}

			f << "\n";
			currentLevel++;
			//Calculam cate linii ne trebuie sa afisam muchiile
			for (int slashesIndex = 1; slashesIndex <= leftSpacing - nextLevelSpacing - 1; slashesIndex++)
			{
				//Pentru fiecare nod afisem muchiile cu spatiere si verificam daca are sau nu copil
				for (int index = 0; index < previousLevelDim; index++)
				{
					ShowCharToFile(" ", leftSpacing - slashesIndex, f);

					if (previousLevelNodes[index].hasLeftchild == true)
						f << "/";
					else
						f << " ";
					ShowCharToFile(" ", 2 * slashesIndex - 1, f);

					if (previousLevelNodes[index].hasRightChild == true)
						f << "\\";
					else
						f << " ";
					if (index != previousLevelDim - 1)
						ShowCharToFile(" ", leftSpacing + 3 - slashesIndex, f);
				}

				f << "\n";
			}
			leftSpacing = nextLevelSpacing;
		}
		delete[] previousLevelNodes;
	}
	/*Printare frumi*/
};

void Arbore_AVL::rotate_left(int key) {

	Nod * x = this->search(key);

	if (x == nullptr) {

	} else {
		Nod * y = x->right;
		x->right = y->left;

		if (y->left != nullptr) {
			y->left->parent = x;
		}

		y->parent = x->parent;

		if (x->parent == nullptr) {
			this->root = y;
		} else {
			if (x == x->parent->left) { //vedem pe care parte a parintelui lui x il legam pe y
				x->parent->left = y;
			}
			if (x == x->parent->right) {
				x->parent->right = y;
			}
		}

		// legam x de y ca fiu de tata
		x->parent = y;
		y->left = x;
	}
}

void Arbore_AVL::merge(Arbore_AVL copac){
	Nod * maxim = copac.maxim(copac.root);
}

void Arbore_AVL::rotate_right(int key) {

	Nod * x = this->search(key);

	if (x == nullptr) {

	} else {

		Nod * y = x->left;
		x->left = y->right;

		if (y->right) {
			y->right->parent = x;
		}

		y->parent = x->parent;

		if (x->parent == nullptr) {
			this->root = y;
		} else {
			if (x == x->parent->right) { //vedem pe care parte a parintelui lui x il legam pe y
				x->parent->right = y;
			}
			if (x == x->parent->left) {
				x->parent->left = y;
			}
		}

		// legam x de y ca fiu de tata
		x->parent = y;
		y->right = x;
	}
}

int Arbore_AVL::inaltime_maxima(Nod * root) {
	std::queue<Nod*> queue;
	queue.push(root);

	int height = -1;

	while (!queue.empty())
	{
		int size = queue.size();

		while (size--)
		{
			Nod * front = queue.front();
			queue.pop();

			if (front->left)
				queue.push(front->left);

			if (front->right)
				queue.push(front->right);
		}

		height++;
	}

	std::cout << "Inaltimea arborelui este: " << height << ".\n";
	return height;
}

void Arbore_AVL::inaltime(Nod * root) {
	std::queue<Nod*> q_nodes;

	int height = this->inaltime_maxima(root);
	Nod * start = root;
	start->setHeight(height--);

	q_nodes.push(start);

	while (!q_nodes.empty()) {
		int size = q_nodes.size();

		while (size--) {
			Nod * temp = q_nodes.front();
			q_nodes.pop();
			if (temp->left) {
				temp->left->setHeight(temp->getHeight() - 1);
				q_nodes.push(temp->left);
			}
			if (temp->right) {
				temp->right->setHeight(temp->getHeight() - 1);
				q_nodes.push(temp->right);
			}
			height--;
		}
	}

}

void Arbore_AVL::adancime(Nod * root) {

	std::queue<Nod*> q_nodes;

	int depth = 0;
	Nod * start = root;
	start->setDepth(depth);

	q_nodes.push(start);

	while (!q_nodes.empty()) {
		int size = q_nodes.size();

		while (size--) {
			Nod * temp = q_nodes.front();
			q_nodes.pop();
			if (temp->left) {
				temp->left->setDepth(temp->getDepth() + 1);
				q_nodes.push(temp->left);
			}
			if (temp->right) {
				temp->right->setDepth(temp->getDepth() + 1);
				q_nodes.push(temp->right);
			}
			depth++;
		}
	}

}

int balans_factor(Nod * temp) {

	//std::cout << "Factor de balansare pt. nodul " << temp->info << " ";

	int factor = 0;

	if (temp->right == nullptr) {

		//std::cout << "[0] - " << temp->getHeight() << ".\n";
		factor = 0 - temp->getHeight();

	} else if (temp->left == nullptr) {

		//std::cout << temp->getHeight() << " - [0]" << ".\n";
		factor = temp->getHeight() - 0;

	} else {

		//std::cout << temp->right->getHeight() << " - " << temp->left->getHeight() << ".\n";
		factor = temp->right->getHeight() - temp->left->getHeight();

	}

	return factor;

}

int f_getHeight(Nod * root) {

	std::queue<Nod *> q;
	int height = 0;

	// add root to the queue
	q.push(root);

	// add null as marker
	q.push(nullptr);

	while (!q.empty()) {
		Nod * n = q.front();
		q.pop();
		// check if n is null, if yes, we have reached to the end of the
		// current level, increment the height by 1, and add the another
		// null as marker for next level
		if (n == nullptr) {
			// before adding null, check if queue is empty, which means we
			// have traveled all the levels
			if (!q.empty()) {
				q.push(nullptr);
			}
			height++;
		} else {
			// else add the children of extracted node.
			if (n->left != nullptr) {
				q.push(n->left);
			}
			if (n->right != nullptr) {
				q.push(n->right);
			}
		}
	}
	return (height - 1);
}

void Arbore_AVL::factor(Nod * root) {
	std::queue<Nod*> q_nodes;

	Nod * start = this->root;

	q_nodes.push(start);

	while (!q_nodes.empty()) {
		int size = q_nodes.size();

		while (size--) {

			Nod * temp = q_nodes.front();
			q_nodes.pop();

			std::cout << temp->info << " ";

			if (temp->left) {

				if (temp->right == nullptr) {
					std::cout << "0 - " << temp->left->getHeight() << ".\n";
					temp->left->setFactor(0 - temp->left->getHeight());
				} else if (temp->left == nullptr) {
					std::cout << temp->right->getHeight() << " - 0" << ".\n";
					temp->left->setFactor(temp->right->getHeight() - 0);
				} else {
					std::cout << temp->right->getHeight() << " - " << temp->left->getHeight() << ".\n";
					temp->left->setFactor(temp->right->getHeight() - temp->left->getHeight());
				}

				q_nodes.push(temp->left);
			}

			if (temp->right) {

				if (temp->right == nullptr) {
					std::cout << "0 - " << temp->left->getHeight() << ".\n";
					temp->right->setFactor(0 - temp->left->getHeight());
				} else if (temp->left == nullptr) {
					std::cout << temp->right->getHeight() << " - 0" << ".\n";
					temp->right->setFactor(temp->right->getHeight() - 0);
				} else {
					std::cout << temp->right->getHeight() << " - " << temp->left->getHeight() << ".\n";
					temp->right->setFactor(temp->right->getHeight() - temp->left->getHeight());
				}

				q_nodes.push(temp->right);
			}
		}
	}
}

unsigned short Arbore_AVL::getSize() const {
	return this->size;
}

bool Arbore_AVL::isEmpty() const {
	if (this->size == 0) {
		return true;
	}
	return false;
}

Nod * Arbore_AVL::search(int key) const {

	Nod * temp = this->root;

	while (temp != nullptr) {
		if (temp->info == key) {
			if (temp->parent) {
				std::cout << key << " se afla in arbore si este fiul lui " <<
					temp->parent->info << ".\n";
			} else {
				std::cout << key << " se afla in arbore si este radacina.\n";
			}
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

Nod * Arbore_AVL::maxim(Nod * root) const {
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

Nod * Arbore_AVL::minim(Nod * root) const {
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

Nod* Arbore_AVL::succesor(int key) const {

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

Nod* Arbore_AVL::predecesor(int key) const {

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

void Arbore_AVL::transplant(Nod * vechi, Nod * nou) {

	// parintele lui vechi devine parintele lui nou
	if (vechi->parent) {
		if (vechi->parent->right == vechi) { //copilul parintelui vechi devine nou
			vechi->parent->right = nou;
		}
		if (vechi->parent->left == vechi) {
			vechi->parent->left = nou;
		}
	} else { //se face transplant cu nodul root
		this->root = nou;
	}

	// copii lui vechi devin copii lui nou
	if (vechi->left) {
		if (vechi->left != nou) {
			nou->left = vechi->left;
			vechi->left->parent = nou;
		}
	}
	if (vechi->right) {
		if (vechi->right != nou) {
			nou->right = vechi->right;
			vechi->right->parent = nou;
		}
	}

	if (nou != nullptr) {
		imp("nou != nullptr");

		if (nou) {
			std::cout << "Schimb intre " << vechi->info << " si " << nou->info << " de parinti.\n";
			if (vechi->parent) {
				std::cout << "Lui " << nou->info << " i se pune parinte " << vechi->parent->info << ".\n";
			}
		}

		if (vechi) {
			log(vechi->info);
		}

		if (vechi->parent) {
			lg("(");
			lg(vechi->parent->info);
			logn(")");
		}

		if (nou) {
			log(nou->info);
		}

		if (nou->parent) {
			lg("(");
			lg(nou->parent->info);
			logn(")");
		}

		imp("nou != nullptr");
		nou->parent = vechi->parent;
	}
}

void Arbore_AVL::construct(const std::vector<Nod*> &noduri) {
	for (int i = 0; i < noduri.size(); i++) {
		//this->insert(noduri[i]);
		this->insert_repair(noduri[i]);
	}
}

void Arbore_AVL::empty() {
	while (!this->isEmpty()) {
		log("Stergem pe");
		logn(this->root->info);
		this->print(6);
		this->delete_repair(this->root);
	}
}

void Arbore_AVL::emptyToFile(std::ofstream &file) {
	file << "----------Redrawn----------" << "\n";

	while (!this->isEmpty()) {
		file << "Stergem pe ";
		file << this->root->info;
		file << "\n";
		this->PrintLevelOrderToFile(this->root, file);
		this->delete_repair(this->root);
		file << "\n";
	}
}

void Arbore_AVL::emptyToFileRandom(std::ofstream &file, std::vector<Nod*> listaNoduri) {
	file << "----------Redrawn----------" << "\n";

	std::random_shuffle(listaNoduri.begin(), listaNoduri.end());

	for (int i = 0; i < listaNoduri.size(); i++) {
		file << "Stergem pe ";
		file << listaNoduri[i]->info;
		file << "\n";
		this->PrintLevelOrderToFile(this->root, file);
		this->delete_repair(listaNoduri[i]);
		file << "\n";
	}

	for (int i = 0; i < listaNoduri.size(); i++) {
		std::cout << listaNoduri[i]->info << " ";
	}
}

void Arbore_AVL::emptyRandom(std::vector<Nod*> listaNoduri) {
	std::ofstream g("problema2/output.in");

	std::random_shuffle(listaNoduri.begin(), listaNoduri.end());

	for (int i = 0; i < listaNoduri.size(); i++) {
		if (listaNoduri[i]->hasTwoSons()) {
			g << "Stergem pe ";
			g << listaNoduri[i]->info;
			g << "\n";
			this->PrintLevelOrderToFile(this->root, g);

			g << "\n";

			this->delete_repair(listaNoduri[i]);

			g << "L-am sters pe ";
			g << listaNoduri[i]->info;
			g << ":\n";
		}
	}

	for (int i = 0; i < listaNoduri.size(); i++) {
		std::cout << listaNoduri[i]->info << " ";
	}

	g.close();
}

void Arbore_AVL::balansare_insert(Nod * parinteNodSters) {

}

void Arbore_AVL::insert_repair(Nod * element) {

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

	Nod * parinteNodInserat = nullptr;
	Nod * nodulInserat = nullptr;

	if (y == nullptr) {
		this->root = element;
		std::cout << "Nodul inserat este noua radacina.\n";
		std::cout << this->root->info << "\n";

		nodulInserat = this->root;
		parinteNodInserat = this->root;

	} else {
		if (element->info < y->info) {

			y->left = element; //sau de aici imi pot da seama pe ce parte a fost inserat

			nodulInserat = y->left;
			parinteNodInserat = y->left->parent;
		} else {

			y->right = element;

			nodulInserat = y->right;
			parinteNodInserat = y->right->parent;
		}
	}

	int h_before, h_after;
	h_before = parinteNodInserat->getHeight();
	//std::cout << "Inaltimea before pentru: " << parinteNodInserat->info << ", " << h_before << " ";
	parinteNodInserat->setHeight(f_getHeight(parinteNodInserat));
	h_after = parinteNodInserat->getHeight();
	//std::cout << "Inaltimea after pentru: " << parinteNodInserat->info << ", " << h_after;

	std::cout << "\n";

	int f_before, f_after;
	f_before = parinteNodInserat->getFactor();
	//std::cout << "Factor before pentru: " << parinteNodInserat->info << ", " << f_before << " ";
	parinteNodInserat->setFactor(balans_factor(parinteNodInserat));
	f_after = parinteNodInserat->getFactor();
	//std::cout << "Factor after pentru: " << parinteNodInserat->info << ", " << f_after;

	std::cout << "\n";

	Nod * sus = parinteNodInserat;

	bool junc = false;

	while (sus->parent) {

		std::cout << "Suntem la " << sus->info << " urcam la " << sus->parent->info << ".\n";
		sus = sus->parent;

		//std::cout << "Inaltimea before pentru: " << sus->info << ", " << sus->getHeight() << " ";
		sus->setHeight(f_getHeight(sus));
		h_after = sus->getHeight();
		//std::cout << "Inaltimea after pentru: " << sus->info << ", " << h_after;

		std::cout << "\n";

		//std::cout << "Factor before pentru: " << sus->info << ", " << sus->getFactor() << " ";
		sus->setFactor(balans_factor(sus));
		f_after = sus->getFactor();
		//std::cout << "Factor after pentru: " << sus->info << ", " << f_after << ".\n";

		if (f_after == -1)
		{
			std::cout << "Mai tb. urcat in arbore!\n";
		}
		if (f_after == 1)
		{
			std::cout << "Mai tb. urcat in arbore!\n";
		}

		if (f_after == -2)
		{
			std::cout << "Rotatie spre dreapta in jurul parintelui " << sus->info << ".\n";
			if (sus->left->getFactor() == 1) { //sa vad daca trebuie sa repar cotul

				rotate_left(sus->left->info);
				rotate_right(sus->info);
				junc = true;

				break;
			}
			if (sus->left->getFactor() == -1) { //inseamna ca toate cele 3 noduri sunt in linie
				//inseamna ca trebuie o rotatie la dreapta in jurul, se face doar o rotatie spre dreapta
				rotate_right(sus->info);
				break;
			}

		}

		if (f_after == 2)
		{
			std::cout << "Rotatie spre stanga in jurul parintelui " << sus->info << ".\n";
			if (sus->right->getFactor() == -1) { //sa vad daca trebuie sa repar cotul

				rotate_right(sus->right->info);
				rotate_left(sus->info);
				junc = true;

				break;
			}
			if (sus->right->getFactor() == 1) { //inseamna ca toate cele 3 noduri sunt in linie
				rotate_left(sus->info);
				break;
			}

		}

		if (f_after == 0) {
			std::cout << "Arborele s-a echilibrat.\n";
			break;
		}
	}

	if (junc) {

		//std::cout << "FINAL cu cot:\n"; //nodul inserat devine parintele celorlalte doua noduri

		//std::cout << "Factor sus:\t";
		sus->setHeight(f_getHeight(sus));
		sus->setFactor(balans_factor(sus));

		//std::cout << "Factor parinte:\t";
		parinteNodInserat->setHeight(f_getHeight(parinteNodInserat));
		parinteNodInserat->setFactor(balans_factor(parinteNodInserat));

		//std::cout << "Factor nod:\t";
		nodulInserat->setHeight(f_getHeight(nodulInserat));
		nodulInserat->setFactor(balans_factor(nodulInserat));

	} else {
		//std::cout << "FINAL fara cot:\n"; //nodul inserat ramane copil

		//std::cout << "Factor sus:\t";
		sus->setHeight(f_getHeight(sus));
		sus->setFactor(balans_factor(sus));

		//std::cout << "Factor nod:\t";
		nodulInserat->setHeight(f_getHeight(nodulInserat));
		nodulInserat->setFactor(balans_factor(nodulInserat));

		//std::cout << "Factor parinte:\t";
		parinteNodInserat->setHeight(f_getHeight(parinteNodInserat));
		parinteNodInserat->setFactor(balans_factor(parinteNodInserat));
	}

	this->size++;
}

void Arbore_AVL::balansare_delete(Nod * parinteNodSters) {

	if (parinteNodSters == nullptr) {
		return;
	}

	this->print(6);

	parinteNodSters->setHeight(f_getHeight(parinteNodSters));
	parinteNodSters->setFactor(balans_factor(parinteNodSters));

	std::cout << "Incepem rebalansarea de la " << parinteNodSters->info << ".\n";
	Nod * sus = parinteNodSters; //nu e ->parent pentru ca parinteNodSters->parent ar fi null daca daca parintele nodului sters ar fi radacaina

	while (sus) {
		std::cout << "Am urcat mai sus la " << sus->info << ".\n";
		sus->setHeight(f_getHeight(sus));
		sus->setFactor(balans_factor(sus));

		if (sus->getFactor() == 1 || sus->getFactor() == -1) { //arbore dezechilibrat pe o parte
			std::cout << "Ne-am oprit la " << sus->info << " cu factorul " << sus->getFactor() << ".\n";
			break;
		}

		if (sus->factor == -2)
		{
			std::cout << "Rotatie spre dreapta in jurul parintelui " << sus->info << ".\n";
			if (sus->left->getFactor() == 1) { //sa vad daca trebuie sa repar cotul

				rotate_left(sus->left->info);
				rotate_right(sus->info);

				break;
			}
			if (sus->left->getFactor() == -1) { //inseamna ca toate cele 3 noduri sunt in linie
				//inseamna ca trebuie o rotatie la dreapta in jurul, se face doar o rotatie spre dreapta
				rotate_right(sus->info);
				break;
			}
			if (sus->left->getFactor() == 0) {
				rotate_right(sus->info);
				break;
			}

		}

		if (sus->factor == 2)
		{
			std::cout << "Rotatie spre stanga in jurul parintelui " << sus->info << ".\n";
			if (sus->right->getFactor() == -1) { //sa vad daca trebuie sa repar cotul

				rotate_right(sus->right->info);
				rotate_left(sus->info);

				break;
			}
			if (sus->right->getFactor() == 1) { //inseamna ca toate cele 3 noduri sunt in linie
				rotate_left(sus->info);
				break;
			}
			if (sus->right->getFactor() == 0) {
				rotate_left(sus->info);
				break;
			}
		}

		sus = sus->parent;
	}

	parinteNodSters->setHeight(f_getHeight(parinteNodSters));
	parinteNodSters->setFactor(balans_factor(parinteNodSters));
}

bool Arbore_AVL::delete_repair(Nod* node) {

	if (node == nullptr) {
		std::cout << "Nodul nu exista in arbore.\n";
		return false;
	}

	std::cout << "++++++++++++++++++";
	std::cout << "il stergem pe " << node->info << "++++++++++++++++++\n";

	//CAZ 1 = z este frunza
	//daca e frunza, putem sterge direct dupa ce aflam pe ce parte a parintelui este
	{
		if (node->isLeaf()) {
			imp("frunza");

			bool frunzaLeft = false;
			bool frunzaRight = false;
			bool radacina = false;

			Nod * parinteNodSters = nullptr;

			if (node->parent) {
				if (node->parent->right == node) { //vine pe partea dreapta a parintelui

					parinteNodSters = node->parent;
					frunzaRight = true;

					transplant(node->parent->right, node->right);

					this->size--;

				}
				if (node->parent->left == node) {

					parinteNodSters = node->parent;
					frunzaLeft = true;

					transplant(node->parent->left, node->left); //merge cu oricare al node (left/right) [ca inlocuim cu null]

					this->size--;

				}
			} else { //daca stergem nodul radacina cand e frunza
				transplant(this->root, this->root->left); //merge cu oricare node (left/right)
				radacina = true;

				this->size--;

			}

			if (radacina) {
				std::cout << "Nodul sters era o radacina frunza (singurul nod din arbore).\n";
				return true;
			}

			if (frunzaLeft) {
				std::cout << "Nodul a fost sters de pe partea stanga a parintelui.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

			if (frunzaRight) {
				std::cout << "Nodul a fost sters de pe partea dreapta a parintelui.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

		}
	}

	//CAZ 2 = z are un singur fiu nenul
	//daca nu e frunza si are 1 fiu
	{
		if (node->hasOneSon()) {

			imp("1 fiu");

			bool fromTheLeft = false; //daca nodul pe care il stergem vine de pe partea stanga
			bool fromTheRight = false; //daca nodul pe care il stergem vine de pe partea dreapta
			bool radacina = false;

			Nod * parinteNodSters = nullptr;

			if (node == this->root) {
				parinteNodSters = node;
				radacina = true;
			}

			if (node->left == nullptr) {

				parinteNodSters = node->parent;
				fromTheLeft = true;

				transplant(node, node->right);

				this->size--;

			}
			if (node->right == nullptr) {

				parinteNodSters = node->parent;
				fromTheRight = true;

				transplant(node, node->left);

				this->size--;

			}

			if (radacina) {
				std::cout << "Nodul devine radacina.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

			if (fromTheLeft) {
				std::cout << "Nodul a fost sters de pe partea stanga a parintelui.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

			if (fromTheRight) {
				std::cout << "Nodul a fost sters de pe partea dreapta a parintelui.\n";
				balansare_delete(parinteNodSters);
				return true;
			}
		}
	}

	//CAZ 3 = z are ambii fii nenuli
	//daca nu e frunza si are 2 fii, cautam succesorul, facem transplant si refacem legaturile
	{
		if (node->hasTwoSons()) {
			imp("2 fii");

			bool descendentDirect = false;

			Nod * parinteNodSters = nullptr;

			Nod * y = this->succesor(node->info);
			if (y == node->right) { //succesorul este descendentul direct

				descendentDirect = true;
				parinteNodSters = y;

				transplant(node, y);
				this->size--;

			}

			if (y != node->right) { //succesorul nu este descendentul direct
				imp("succesorul nu e descendent direct");

				descendentDirect = false;
				parinteNodSters = y;

				transplant(y, y->right);

				transplant(node, y);

				this->size--;

			}

			if (descendentDirect) {
				std::cout << "Nodul sters are descendent direct ca succesor.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

			if (!descendentDirect) {
				std::cout << "Nodul sters NU are descendent direct ca succesor.\n";
				balansare_delete(parinteNodSters);
				return true;
			}

		}
	}
}

void Arbore_AVL::preordine(Nod * root) const
{
	if (root == nullptr) {
		return;
	}

	std::cout << root->info << " ";
	preordine(root->left);
	preordine(root->right);
}

void Arbore_AVL::inordine(Nod * root) const
{
	if (root == nullptr) {
		return;
	}

	inordine(root->left);
	std::cout << root->info << " ";
	inordine(root->right);
}

void Arbore_AVL::postordine(Nod * root) const
{
	if (root == nullptr) {
		return;
	}
	postordine(root->left);
	postordine(root->right);
	std::cout << root->info << " ";
}

void Arbore_AVL::printLevelByLevel(Nod * root) const {
	std::queue<Nod *> q;

	// add root to the queue
	q.push(root);

	// add null as marker
	q.push(nullptr);

	while (!q.empty()) {

		Nod * n = q.front();

		q.pop();
		// check if n is null, if yes, we have reached to the end of the
		// current level, increment the height by 1, and add the another
		// null as marker for next level
		if (n == nullptr) {
			// before adding null, check if queue is empty, which means we
			// have traveled all the levels
			if (!q.empty()) {
				q.push(nullptr);
			}
		} else {
			std::cout << n->info << " ";
			// else add the children of extracted node.
			if (n->left != nullptr) {
				q.push(n->left);
			}
			if (n->right != nullptr) {
				q.push(n->right);
			}
		}
	}
}

void Arbore_AVL::print(unsigned short option) const {
	switch (option) {
		case 1: //preordine
			{
				std::cout << "Preordine: ";
				preordine(this->root);
				std::cout << "\n";
				break;
			}
		case 2: //inordine
			{
				std::cout << "Inordine: ";
				inordine(this->root);
				std::cout << "\n";
				break;
			}
		case 3: //postordine
			{
				std::cout << "Postordine: ";
				postordine(this->root);
				std::cout << "\n";
				break;
			}
		case 4: //printare pe nivel
			{
				printLevelByLevel(this->root);
				std::cout << "\n";
				break;
			}
		case 6: //printare H + F
			{
				PrintLevelOrder(this->root);
				std::cout << "\n";
				break;
			}
	}
}