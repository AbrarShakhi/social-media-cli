#pragma once
#include "../include/limits.h"

#include <vector>
#include <string>

class BinaryTreeFrequencyMap {
	struct Node {
		Node* left = nullptr;
		Node* right = nullptr;
		char key[MAX_USERNAME_LEN] = "";
		int value = 0;
	};

	Node* root;
	int size;

	void insert(Node** root, const char key[]);

	int get_value(Node* root, const char key[]);

	void inorder(Node* root, std::vector<std::pair<std::string, int>>& s);

public:
	BinaryTreeFrequencyMap();
	~BinaryTreeFrequencyMap();

	void insert(const std::string& key);
	int get_value(const std::string& key);
	int length();
	std::vector<std::string> get_frequency_sorted();
};