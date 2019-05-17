#include "problema1/Arbore_Caut.h"
#include "problema1/Utils.h"

int main() {

	Arbore_Caut copac = Arbore_Caut();

	int cateNoduri;

	std::vector<Nod*> listaNoduri;

	readFromFile(listaNoduri, cateNoduri);

	copac.construct(listaNoduri);

	printTree(copac);

	while (true) {
		menuText();

		unsigned int comanda;
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
		}
	}

	printTree(copac);

	sout;
	system("pause");
	return 0;
}
