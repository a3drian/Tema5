#pragma once

#define sout std::cout << "\n"
#define lg(x) std::cout << (x)
#define log(x) std::cout << (x) << " "
#define logn(x) std::cout << (x) << "\n"
#define imp(x) std::cout << "---------------" << (x) << "---------------" << "\n"

void readFromFile(std::vector<Nod*> &listaNoduri, int &cateNoduri){

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

void printTree(Arbore_Caut copac){
	std::string prefix = "";
	printBT(prefix, copac.root, false);
	sout;
}