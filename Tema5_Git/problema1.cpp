#include "problema1/Arbore_Caut.h"
#include "problema1/Utils.h"

int main() {

	Arbore_Caut copac = Arbore_Caut();

	int cateNoduri;

	std::vector<Nod*> listaNoduri;

	readFromFile(listaNoduri, cateNoduri);

	copac.construct(listaNoduri);

	printTree(copac);

	int x;
	std::cout << "Pe cine stergem: ";
	std::cin >> x;
	//copac.search(x);

	//Nod * leaf = new Nod(x);
	//copac.maxim(leaf);

	//copac.minim(leaf);

	Nod * deSters = copac.search(10);
	copac.delete_element(deSters);

	printTree(copac);

	sout;
	system("pause");
	return 0;
}
