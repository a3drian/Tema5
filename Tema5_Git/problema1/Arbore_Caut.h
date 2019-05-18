#pragma once

#include "Nod.h"
#include <sstream>
#include <algorithm>    // std::random_shuffle

using std::vector;
using std::string;
using std::cout;

class Arbore_Caut {
public:
	Nod * root;
	unsigned short size;

	Arbore_Caut() {
		this->root = nullptr;
		this->size = 0;
	}

	unsigned short getSize() const;
	bool isEmpty() const; //daca nu e const, nu merge in cauta() pentru ca nu avem garantia ca isEmpty() nu modifica ceva in obiectul de tip Arbore_Caut

	void insert(Nod *);

	Nod * search(int) const;

	Nod * maxim(Nod *) const;
	Nod * minim(Nod *) const;

	Nod * succesor(int) const;
	Nod * predecesor(int) const;

	void transplant(Nod *, Nod *);
	void transplant_pseudo(Nod *, Nod *);

	bool delete_element(Nod *);

	bool delete_pseudo_transplant(Nod *);
	bool delete_pseudo_transplant_pseudo(Nod *);

	void print(unsigned short) const;
	void construct(const std::vector<Nod*> &);
	void empty();
	void sterge_random(std::vector<Nod*>);

	/*Printare frumi*/
	int get_max_depth() const { return root ? root->max_depth() : 0; }
	struct cell_display {
		string   valstr;
		bool     present;
		cell_display() : present(false) {}
		cell_display(std::string valstr) : valstr(valstr), present(true) {}
	};
	using display_rows = vector< vector< cell_display > >;
	display_rows get_row_display() const {
		{
			// start off by traversing the tree to
			// build a vector of vectors of Node pointers
			vector<Nod*> traversal_stack;
			vector< std::vector<Nod*> > rows;
			if (!root) return display_rows();

			Nod *p = root;
			const int max_depth = root->max_depth();
			rows.resize(max_depth);
			int depth = 0;
			for (;;) {
				// Max-depth Nodes are always a leaf or null
				// This special case blocks deeper traversal
				if (depth == max_depth - 1) {
					rows[depth].push_back(p);
					if (depth == 0) break;
					--depth;
					continue;
				}

				// First visit to node?  Go to left child.
				if (traversal_stack.size() == depth) {
					rows[depth].push_back(p);
					traversal_stack.push_back(p);
					if (p) p = p->left;
					++depth;
					continue;
				}

				// Odd child count? Go to right child.
				if (rows[depth + 1].size() % 2) {
					p = traversal_stack.back();
					if (p) p = p->right;
					++depth;
					continue;
				}

				// Time to leave if we get here

				// Exit loop if this is the root
				if (depth == 0) break;

				traversal_stack.pop_back();
				p = traversal_stack.back();
				--depth;
			}

			// Use rows of Node pointers to populate rows of cell_display structs.
			// All possible slots in the tree get a cell_display struct,
			// so if there is no actual Node at a struct's location,
			// its boolean "present" field is set to false.
			// The struct also contains a string representation of
			// its Node's value, created using a std::stringstream object.
			display_rows rows_disp;
			std::stringstream ss;
			for (const auto& row : rows) {
				rows_disp.emplace_back();
				for (Nod* pn : row) {
					if (pn) {
						ss << pn->info;
						rows_disp.back().push_back(cell_display(ss.str()));
						ss = std::stringstream();
					} else {
						rows_disp.back().push_back(cell_display());
					}
				}
			}
			return rows_disp;
		}
	}
	vector<string> row_formatter(const display_rows& rows_disp) const {
		{
			using s_t = string::size_type;

			// First find the maximum value string length and put it in cell_width
			s_t cell_width = 0;
			for (const auto& row_disp : rows_disp) {
				for (const auto& cd : row_disp) {
					if (cd.present && cd.valstr.length() > cell_width) {
						cell_width = cd.valstr.length();
					}
				}
			}

			// make sure the cell_width is an odd number
			if (cell_width % 2 == 0) ++cell_width;

			// formatted_rows will hold the results
			vector<string> formatted_rows;

			// some of these counting variables are related,
			// so its should be possible to eliminate some of them.
			s_t row_count = rows_disp.size();

			// this row's element count, a power of two
			s_t row_elem_count = 1 << (row_count - 1);

			// left_pad holds the number of space charactes at the beginning of the bottom row
			s_t left_pad = 0;

			// Work from the level of maximum depth, up to the root
			// ("formatted_rows" will need to be reversed when done) 
			for (s_t r = 0; r < row_count; ++r) {
				const auto& cd_row = rows_disp[row_count - r - 1]; // r reverse-indexes the row
				// "space" will be the number of rows of slashes needed to get
				// from this row to the next.  It is also used to determine other
				// text offsets.
				s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
				// "row" holds the line of text currently being assembled
				string row;
				// iterate over each element in this row
				for (s_t c = 0; c < row_elem_count; ++c) {
					// add padding, more when this is not the leftmost element
					row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
					if (cd_row[c].present) {
						// This position corresponds to an existing Node
						const string& valstr = cd_row[c].valstr;
						// Try to pad the left and right sides of the value string
						// with the same number of spaces.  If padding requires an
						// odd number of spaces, right-sided children get the longer
						// padding on the right side, while left-sided children
						// get it on the left side.
						s_t long_padding = cell_width - valstr.length();
						s_t short_padding = long_padding / 2;
						long_padding -= short_padding;
						row += string(c % 2 ? short_padding : long_padding, ' ');
						row += valstr;
						row += string(c % 2 ? long_padding : short_padding, ' ');
					} else {
						// This position is empty, Nodeless...
						row += string(cell_width, ' ');
					}
				}
				// A row of spaced-apart value strings is ready, add it to the result vector
				formatted_rows.push_back(row);

				// The root has been added, so this loop is finsished
				if (row_elem_count == 1) break;

				// Add rows of forward- and back- slash characters, spaced apart
				// to "connect" two rows' Node value strings.
				// The "space" variable counts the number of rows needed here.
				s_t left_space = space + 1;
				s_t right_space = space - 1;
				for (s_t sr = 0; sr < space; ++sr) {
					string row;
					for (s_t c = 0; c < row_elem_count; ++c) {
						if (c % 2 == 0) {
							row += string(c ? left_space * 2 + 1 : left_space, ' ');
							row += cd_row[c].present ? '/' : ' ';
							row += string(right_space + 1, ' ');
						} else {
							row += string(right_space, ' ');
							row += cd_row[c].present ? '\\' : ' ';
						}
					}
					formatted_rows.push_back(row);
					++left_space;
					--right_space;
				}
				left_pad += space + 1;
				row_elem_count /= 2;
			}

			// Reverse the result, placing the root node at the beginning (top)
			std::reverse(formatted_rows.begin(), formatted_rows.end());

			return formatted_rows;
		}
	}
	static void trim_rows_left(vector<string>& rows) {
		{
			if (!rows.size()) return;
			auto min_space = rows.front().length();
			for (const auto& row : rows) {
				auto i = row.find_first_not_of(' ');
				if (i == string::npos) i = row.length();
				if (i == 0) return;
				if (i < min_space) min_space = i;
			}
			for (auto& row : rows) {
				row.erase(0, min_space);
			}
		}
	}
	void dump() const {
		{
			const int d = get_max_depth();

			// If this tree is empty, tell someone
			if (d == 0) {
				cout << " <empty tree>\n";
				return;
			}

			// This tree is not empty, so get a list of node values...
			const auto rows_disp = get_row_display();
			// then format these into a text representation...
			auto formatted_rows = row_formatter(rows_disp);
			// then trim excess space characters from the left sides of the text...
			trim_rows_left(formatted_rows);
			// then dump the text to cout.
			for (const auto& row : formatted_rows) {
				std::cout << ' ' << row << '\n';
			}
		}
	}
	void dumpToFile(std::ofstream &f) const {
		{
			const int d = get_max_depth();

			// If this tree is empty, tell someone
			if (d == 0) {
				f << " <empty tree>\n";
				return;
			}

			// This tree is not empty, so get a list of node values...
			const auto rows_disp = get_row_display();
			// then format these into a text representation...
			auto formatted_rows = row_formatter(rows_disp);
			// then trim excess space characters from the left sides of the text...
			trim_rows_left(formatted_rows);
			// then dump the text to cout.
			for (const auto& row : formatted_rows) {
				f << ' ' << row << '\n';
			}
		}
	}
	/*Printare frumi*/
};

unsigned short Arbore_Caut::getSize() const {
	return this->size;
}

bool Arbore_Caut::isEmpty() const {
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

void Arbore_Caut::transplant_pseudo(Nod * vechi, Nod * nou) {

	//aici nou poate fi null pentru ca va fi inlocuit oricum
	if (vechi->parent == nullptr) {
		this->root = nou;
	} else {
		if (vechi == vechi->parent->left) {
			vechi->parent->left = nou;
		} else {
			vechi->parent->right = nou;
		}
	}

	//pentru cazul in care nou nu este null
	//nu intra cand facem transplant intre vechi si null (cazul 1)
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

bool Arbore_Caut::delete_pseudo_transplant(Nod * node) {

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

bool Arbore_Caut::delete_pseudo_transplant_pseudo(Nod * node) {

	if (node == nullptr) {
		std::cout << "Nodul nu exista in arbore.\n";
		return false;
	}

	if (node->left == nullptr) {
		transplant_pseudo(node, node->right);
	} else {
		if (node->right == nullptr) {
			transplant_pseudo(node, node->left);
		} else {
			//Nod * y = minim(node->right); //echivalent cu aia mai jos, minimul din right-subtree e acelasi lucru cu succesorul nodului pe care il stergem
			Nod * y = succesor(node->info);
			if (y != node->right) { // nu e descendent direct (3a)
				transplant_pseudo(y, y->right);
				y->right = node->right;
				node->right->parent = y;
			}
			transplant_pseudo(node, y);
			y->left = node->left;
			node->left->parent = y;
		}
	}

	this->size--;
}

void Arbore_Caut::transplant(Nod * vechi, Nod * nou) {

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
			if (node->parent) {
				if (node->parent->right == node) { //vine pe partea dreapta a parintelui
					transplant(node->parent->right, node->right);

					this->size--;
					//delete node;
					return true;
				}
				if (node->parent->left == node) {
					transplant(node->parent->left, node->left); //merge cu oricare al node (left/right) [ca inlocuim cu null]

					this->size--;
					//delete node;
					return true;
				}
			} else { //daca stergem nodul radacina cand e frunza
				transplant(this->root, this->root->left); //merge cu oricare al node (left/right)

				this->size--;
				return true;
			}
		}
	}

	//CAZ 2 = z are un singur fiu nenul
	//daca nu e frunza si are 1 fiu
	{
		if (node->hasOneSon()) {
			imp("1 fiu");
			if (node->left == nullptr) {
				transplant(node, node->right);

				this->size--;
				return true;
			}
			if (node->right == nullptr) {
				transplant(node, node->left);

				this->size--;
				return true;
			}
		}
	}

	//CAZ 3 = z are ambii fii nenuli
	//daca nu e frunza si are 2 fii, cautam succesorul, facem transplant si refacem legaturile
	{
		if (node->hasTwoSons()) {
			imp("2 fii");

			Nod * temp = this->succesor(node->info);
			transplant(node, temp);

			//Nod * y = succesor(node->info);
			//if (y != node->right) {
			//	transplant(y, y->right);
			//	y->right = node->right;
			//	node->right->parent = y;
			//}
			//transplant(node, y);
			//y->left = node->left;
			//node->left->parent = y;

			this->size--;
			return true;
		}
	}
}

void Arbore_Caut::construct(const std::vector<Nod*> &noduri) {
	for (int i = 0; i < noduri.size(); i++) {
		this->insert(noduri[i]);
	}
}

void printBTToFile(const std::string & prefix, Nod * nod, bool isLeft, std::ofstream &g) {
	if (nod != nullptr)
	{
		for (int i = 0; i < prefix.length(); i++) {
			g << prefix[i];
		}

		g << (isLeft ? "st__" : "dr__");

		// print the value of the node
		g << nod->info <<
			" [" <<
			((nod->parent) ? nod->parent->info : 0)
			<< "]\n";

		// enter the next tree level - left and right branch
		printBTToFile(prefix + (isLeft ? "|   " : "    "), nod->left, true, g);
		printBTToFile(prefix + (isLeft ? "|   " : "    "), nod->right, false, g);
	}
}

void Arbore_Caut::empty() {
	while (!this->isEmpty()) {
		log("Stergem pe");
		logn(this->root->info);
		this->dump();
		//this->delete_pseudo_transplant_pseudo(this->root);
		this->delete_pseudo_transplant(this->root);
	}
}

void Arbore_Caut::sterge_random(std::vector<Nod*>listaNoduri) {
	std::ofstream g("problema1/output.in");

	std::random_shuffle(listaNoduri.begin(), listaNoduri.end());
	for (int i = 0; i < listaNoduri.size(); i++) {
		if (listaNoduri[i]->isLeaf() || listaNoduri[i]->hasOneSon()) {
			g << "Stergem pe ";
			g << listaNoduri[i]->info;
			g << "\n";
			this->dumpToFile(g);

			//std::string prefix = "";
			//printBTToFile(prefix, this->root, false, g);
			//g << "\n";

			g << "\n";
			//this->delete_pseudo_transplant_pseudo(listaNoduri[i]);
			//this->delete_pseudo_transplant(listaNoduri[i]);

			//sterg doar daca e cazul 1 sau cazul 2

			this->delete_element(listaNoduri[i]);

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

void printBT(const std::string & prefix, Nod * nod, bool isLeft) {
	if (nod != nullptr)
	{
		for (int i = 0; i < prefix.length(); i++) {
			std::cout << prefix[i];
		}

		std::cout << (isLeft ? "st__" : "dr__");

		// print the value of the node
		std::cout << nod->info <<
			" [" <<
			((nod->parent) ? nod->parent->info : 0)
			<< "]\n";

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), nod->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), nod->right, false);
	}
}

void Arbore_Caut::print(unsigned short option) const {
	switch (option) {
		case 1:
			{
				std::string prefix = "";
				printBT(prefix, this->root, false);
				std::cout << "\n";
				break;
			}
		case 2:
			{
				this->dump();
				std::cout << "\n";
				break;
			}
	}
}