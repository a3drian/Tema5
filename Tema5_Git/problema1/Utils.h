#pragma once

#include <ctime>

void menuText() {
	logn("1. Cauta");
	logn("2. Sterge");
	logn("3. Element minim");
	logn("4. Element maxim");
	logn("5. Succesor");
	logn("6. Predecesor");
	logn("7. Insereaza");
	logn("8. Printeaza");
	logn("9. Goleste");
	logn("10. Goleste aleator in fisier");
	logn("11. Redraw");

	logn("0. Exit");
	sout;
}

void cauta(const Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Pe cine cautam: ";
		std::cin >> x;
		copac.search(x);
	} else {
		logn("Arborele este gol.");
	}
}

void sterge(Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Pe cine stergem: ";
		std::cin >> x;

		Nod * deSters = copac.search(x);
		copac.delete_element(deSters);
	} else {
		logn("Arborele este gol.");
	}
}

void elemMin(const Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Radacina subarbore: ";
		std::cin >> x;

		Nod * leaf = new Nod(x);
		copac.minim(leaf);
	} else {
		logn("Arborele este gol.");
	}
}

void elemMax(const Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Radacina subarbore: ";
		std::cin >> x;

		Nod * leaf = new Nod(x);
		copac.maxim(leaf);
	} else {
		logn("Arborele este gol.");
	}
}

void succes(const Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Radacina subarbore: ";
		std::cin >> x;

		copac.succesor(x);
	} else {
		logn("Arborele este gol.");
	}
}

void predec(const Arbore_Caut &copac) {
	if (!copac.isEmpty()) {
		int x;
		std::cout << "Radacina subarbore: ";
		std::cin >> x;

		copac.predecesor(x);
	} else {
		logn("Arborele este gol.");
	}
}

void insereaza(Arbore_Caut &copac) {
	int x;
	std::cout << "Valoare nod: ";
	std::cin >> x;

	Nod * leaf = new Nod(x);
	copac.insert(leaf);
}

void drawRandom(std::vector<Nod*> &listaNoduri, const int &cateNoduri) {
	listaNoduri = std::vector<Nod*>(cateNoduri);
	for (int i = 0; i < cateNoduri; i++) {
		int valoare = rand() % 100;
		Nod * leaf = new Nod(valoare);
		listaNoduri[i] = leaf;
	}
}

void startOver(Arbore_Caut &copac, std::vector<Nod*> &listaNoduri, int &cateNoduri) {
	std::cout << "Numarul de noduri pentru arborele generat aleator: ";
	std::cin >> cateNoduri;
	drawRandom(listaNoduri, cateNoduri);

	copac.construct(listaNoduri);

	imp("Arborele generat aleator:");
	copac.dump();
	sout;

	while (true) {
		std::cout << "Redraw? (0/1): ";
		unsigned short y;
		std::cin >> y;
		if (y == 1) {
			drawRandom(listaNoduri, cateNoduri);
			copac.empty();
			copac.construct(listaNoduri);
			copac.dump();
		} else {
			break;
		}
	}
}

void readFromFile(std::vector<Nod*> &listaNoduri, int &cateNoduri) {

	std::ifstream f("problema1/noduri.in");

	f >> cateNoduri;
	listaNoduri = std::vector<Nod*>(cateNoduri);

	for (int i = 0; i < cateNoduri; i++) {
		int valoare;
		f >> valoare;
		Nod * leaf = new Nod(valoare);
		listaNoduri[i] = leaf;
	}

	f.close();
}

void printTree(Arbore_Caut copac) {
	//unsigned short x;
	//std::cout << "Optiune: ";
	//std::cin >> x;
	//copac.print(x);

	if (!copac.isEmpty()) {
		std::string prefix = "";
		printBT(prefix, copac.root, false);
		sout;
	} else {
		logn("Arborele este gol.");
	}
}