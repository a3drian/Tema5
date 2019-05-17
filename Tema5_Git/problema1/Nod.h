#pragma once

#include <iostream>
#include <fstream>
#include <vector>

struct Nod {

	int info;
	Nod * left;
	Nod * right;
	Nod * parent;

	Nod(int key) {
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
};

