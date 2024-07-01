#include "../include/binary_tree_frequency_map.h"
#include "../include/utils.h"
#include "../include/merge_sort.h"

#include <vector>
#include <string.h>



void BinaryTreeFrequencyMap::insert(Node** root, const char key[]) {
	if (!*root) {
		*root = new Node();
		cstrcpy((*root)->key, key);
		(*root)->value = 1;
		size++;
		return;
	}

	if (strcmp(key, (*root)->key) < 0) {
		insert(&(*root)->left, key);
	}
	else if (strcmp(key, (*root)->key) > 0) {
		insert(&(*root)->right, key);
	}
	else {
		(*root)->value++;
	}
}

int BinaryTreeFrequencyMap::get_value(Node* root, const char key[]) {
	if (!root) {
		return 0;
	}
	if (strcmp(key, root->key) < 0) {
		return get_value(root->left, key);
	}
	else if (strcmp(key, root->key) > 0) {
		return get_value(root->right, key);
	}
	else {
		return root->value;
	}
}

void BinaryTreeFrequencyMap::inorder(Node* root, std::vector<std::pair<std::string, int>>& s) {
	if (!root) {
		return;
	}
	inorder(root->left, s);
	s.push_back({ c_2_str(root->key) , root->value });
	inorder(root->right, s);
}

BinaryTreeFrequencyMap::BinaryTreeFrequencyMap() {
	root = nullptr;
	size = 0;
}

BinaryTreeFrequencyMap::~BinaryTreeFrequencyMap() {
	Node* current = root;
	while (current) {
		Node* temp = current;
		current = current->left;
		delete temp;
	}
}

void BinaryTreeFrequencyMap::insert(const std::string& key) { insert(&root, key.c_str()); }
int BinaryTreeFrequencyMap::get_value(const std::string& key) { return get_value(root, key.c_str()); }
int BinaryTreeFrequencyMap::length() { return size; }
std::vector<std::string> BinaryTreeFrequencyMap::get_frequency_sorted() {
	std::vector<std::pair<std::string, int>> freq;
	inorder(root, freq);
	MergeSort::sort(freq);
	std::vector<std::string> s;
	for (auto&& i : freq) {
		s.push_back(i.first);
	}
	return s;
}