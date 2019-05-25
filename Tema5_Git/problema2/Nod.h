#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#define sout std::cout << "\n"
#define lg(x) std::cout << (x)
#define log(x) std::cout << (x) << " "
#define logn(x) std::cout << (x) << "\n"
#define imp(x) std::cout << "---------------" << (x) << "---------------" << "\n"

class Nod {

public:

	int info;
	Nod * left;
	Nod * right;
	Nod * parent;

	bool visited;
	int height;
	int depth;

	int factor;

	Nod(int key = 0) {
		this->info = key;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;

		this->height = 0;
		this->depth = 0;
		this->factor = 0;

		visited = false;
	}

	void setHeight(int height){
		this->height = height;
	}

	void setDepth(int depth) {
		this->depth = depth;
	}

	void setFactor(int factor) {
		this->factor = factor;
	}

	int getHeight() const{
		return this->height;
	}

	int getDepth() const {
		return this->depth;
	}

	int getFactor() const {
		return this->factor;
	}

	bool isLeaf() {
		if (this->left == nullptr && this->right == nullptr) {
			return true;
		}
		return false;
	}

	//as putea returna aici adresa fiului nenul
	bool hasOneSon() {
		if (this->left == nullptr && this->right != nullptr) {
			return true;
		}
		if (this->left != nullptr && this->right == nullptr) {
			return true;
		}
		return false;
	}

	bool hasTwoSons() {
		if (this->left != nullptr && this->right != nullptr) {
			return true;
		}
		return false;
	}

	int max_depth() const {
		const int left_depth = left ? left->max_depth() : 0;
		const int right_depth = right ? right->max_depth() : 0;
		return (left_depth > right_depth ? left_depth : right_depth) + 1;
	}

	int max_dep() const {
		const int left_depth = left ? left->max_depth() : 0;
		const int right_depth = right ? right->max_depth() : 0;
		return (left_depth > right_depth ? left_depth : right_depth);
	}

	bool wasVisited(){
		return this->visited;
	}

	void setVisited(){
		this->visited = true;
	}

	~Nod() {
		std::cout << "~Nod()\n";
	}
};

