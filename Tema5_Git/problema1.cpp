#include "problema1/Arbore_Caut.h"
#include "problema1/Utils.h"


int main() {
	srand(time(NULL));
	std::ofstream file("problema1/output.in");

	Arbore_Caut copac = Arbore_Caut();

	int cateNoduri;
	std::vector<Nod*> listaNoduri;

	//FROM FILE
	//readFromFile(listaNoduri, cateNoduri);
	//copac.construct(listaNoduri);
	////copac.sterge_random(listaNoduri);
	//imp("Arbore:");
	////printTree(copac);
	//copac.dump();

	//RANDOM
	startOver(copac, listaNoduri, cateNoduri);

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
					copac.dump();
					sout;
					break;
				}
			case 9:
				{
					logn("9. Inaltimea");

					copac.empty();
					sout;
					break;
				}
			case 10:
				{
					logn("10. Goleste aleator in fisier");

					if (copac.getSize() == cateNoduri) {
						copac.emptyToFileRandom(file, listaNoduri);
					} else {
						logn("Nu se poate sterge aleator din fisier.");
					}

					sout;
					break;
				}
			case 11:
				{
					logn("11. Redraw");

					startOver(copac, listaNoduri, cateNoduri);

					sout;
					break;
				}
		}
	}

	file.close();

	sout;
	system("pause");
	return 0;
}
