#pragma once
#include "../include/limits.h"

#include <vector>
#include <string>

class AVLTreeSet {
	struct Node {
		Node* left = nullptr;
		Node* right = nullptr;
		int height = 1;
		char data[MAX_USERNAME_LEN] = "";
	};

	int size;
	Node* root;

	int height(Node* N);
	int max(int a, int b);
	Node* newNode(const char key[]);
	Node* rightRotate(Node* y);
	Node* leftRotate(Node* x);
	int getBalance(Node* N);
	Node* insert(Node* node, const char key[]);
	Node* minValueNode(Node* node);
	Node* remove(const char key[], Node* root);
	void inorder(Node* root, std::vector<std::string>& v);

public:
	int length();

	~AVLTreeSet();
	AVLTreeSet();

	bool find(const char key[]);
	void insert(const std::string& key);
	void remove(const std::string& key);
	std::vector<std::string> get_all();
};