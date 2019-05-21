#include "problema1/Arbore_Caut.h"
#include "problema1/Utils.h"
#include <ctime>

void drawRandom(std::vector<Nod*> &listaNoduri, int cateNoduri) {
	listaNoduri = std::vector<Nod*>(cateNoduri);
	for (int i = 0; i < cateNoduri; i++) {
		int valoare = rand() % 100;
		Nod * leaf = new Nod(valoare);
		listaNoduri[i] = leaf;
	}
}

int main() {
	srand(time(NULL));

	Arbore_Caut copac = Arbore_Caut();

	int cateNoduri;
	std::vector<Nod*> listaNoduri;

	readFromFile(listaNoduri, cateNoduri);
	copac.construct(listaNoduri);
	//copac.sterge_random(listaNoduri);
	imp("Arbore:");
	//printTree(copac);
	copac.dump();

	//std::cin >> cateNoduri;
	//drawRandom(listaNoduri, cateNoduri);

	//copac.construct(listaNoduri);
	////copac.sterge_random(listaNoduri);

	//imp("Arbore:");
	////printTree(copac);
	//copac.dump();

	//while (true) {
	//	std::cout << "Redraw?: ";
	//	bool y;
	//	std::cin >> y;
	//	if (y == true) {
	//		drawRandom(listaNoduri, cateNoduri);
	//		copac.dump();
	//	} else {
	//		break;
	//	}
	//}


	while (true) {
		menuText();

		unsigned short comanda;
		log(">");
		std::cin >> comanda;

		if (comanda == 0) {
			break;
		}

		switch (comanda) {
			case 1:
				{
					logn("1. Cauta");
					cauta(copac);
					sout;
					break;
				}
			case 2:
				{
					logn("2. Sterge");
					sterge(copac);
					printTree(copac);
					//copac.sterge_random(listaNoduri);
					//copac.dump();
					sout;
					break;
				}
			case 3:
				{
					logn("3. Element minim");
					elemMin(copac);
					sout;
					break;
				}
			case 4:
				{
					logn("4. Element maxim");
					elemMax(copac);
					sout;
					break;
				}
			case 5:
				{
					logn("5. Succesor");
					succes(copac);
					sout;
					break;
				}
			case 6:
				{
					logn("6. Predecesor");
					predec(copac);
					sout;
					break;
				}
			case 7:
				{
					logn("7. Insereaza");
					insereaza(copac);
					sout;
					break;
				}
			case 8:
				{
					logn("8. Printeaza");
					//printTree(copac);
					copac.dump();
					sout;
					break;
				}
			case 9:
				{
					logn("9. Inaltimea");
					imp(copac.get_max_depth());
					copac.dump();
					sout;
					break;
				}
			case 10:
				{
					logn("10. Goleste");
					//copac.empty();
					copac.sterge_random(listaNoduri);
					sout;
					break;
				}
		}
	}

	//printTree(copac);
	copac.dump();

	sout;
	system("pause");
	return 0;
}
