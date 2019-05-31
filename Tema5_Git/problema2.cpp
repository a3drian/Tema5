#include "problema2/Arbore_AVL.h"
#include "problema2/Utils.h"

int main() {
	srand(time(NULL));
	std::ofstream file("problema2/output.in");

	Arbore_AVL copac = Arbore_AVL();

	int cateNoduri;
	std::vector<Nod*> listaNoduri;
	int contor;

	//FROM FILE
	readFromFile(listaNoduri, cateNoduri);
	contor = cateNoduri - 1;
	copac.construct(listaNoduri);
	//copac.emptyRandom(listaNoduri);
	imp("Arbore:");
	//printTree(copac);
	//copac.dump();
	copac.print(6);
	sout;

	//RANDOM
	//startOver(copac, listaNoduri, cateNoduri);
	//contor = cateNoduri - 1;

	//ONE BY ONE
	////std::cout << "Numar maxim noduri: ";
	////std::cin >> cateNoduri;
	//contor = 0;
	//cateNoduri = 100;
	//listaNoduri = std::vector<Nod*>(cateNoduri);

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
					copac.print(6);
					sout;
					break;
				}
			case 3:
				{
					logn("3. Roteste stanga");
					rot_st(copac);
					//elemMin(copac);
					sout;
					break;
				}
			case 4:
				{
					logn("4. Roteste dreapta");
					rot_dr(copac);
					//elemMax(copac);
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
					insereaza(copac, listaNoduri, contor);
					sout;
					break;
				}
			case 8:
				{
					logn("8. Printeaza");

					copac.print(6);
					//copac.dump();

					sout;
					break;
				}
			case 9:
				{
					//logn("9. Inaltimea");
					logn("9. SETEAZA INALTIME SI FACTOR");

					cateNoduri = copac.getSize();

					for (int i = 0; i < cateNoduri; i++) {
						//listaNoduri[i]->setHeight(listaNoduri[i]->max_dep());
						listaNoduri[i]->setHeight(f_getHeight(listaNoduri[i]));
					}
					for (int i = 0; i < cateNoduri; i++) {
						listaNoduri[i]->setFactor(balans_factor(listaNoduri[i]));
					}

					//copac.inaltime(copac.root);

					sout;
					sout;
					break;
				}
			case 10:
				{
					logn("10. Goleste aleator in fisier");

					if (copac.getSize() == cateNoduri) {
						copac.emptyToFileRandom(file, listaNoduri);
					} else {
						logn("Nu se poate sterge aleator in fisier.");
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
			case 12:
				{
					logn("12. Print SRD");

					copac.print(3);

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
