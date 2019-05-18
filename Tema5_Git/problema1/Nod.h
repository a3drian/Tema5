#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#define sout std::cout << "\n"
#define lg(x) std::cout << (x)
#define log(x) std::cout << (x) << " "
#define logn(x) std::cout << (x) << "\n"
#define imp(x) std::cout << "---------------" << (x) << "---------------" << "\n"

struct Nod {

	int info;
	Nod * left;
	Nod * right;
	Nod * parent;

	Nod(int key = 0) {
		this->info = key;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}

	bool isLeaf() {
		if (this->left == nullptr && this->right == nullptr) {
			return true;
		}
		return false;
	}

	//as putea returna aici adresa fiului nenul
	bool hasOneSon(){
		if(this->left == nullptr && this->right != nullptr) {
			return true;
		}
		if (this->left != nullptr && this->right == nullptr) {
			return true;
		}
		return false;
	}

	bool hasTwoSons(){
		if (this->left != nullptr && this->right != nullptr) {
			return true;
		}
		return false;
	}

	~Nod(){
		std::cout << "~Nod()\n";
	}
};

