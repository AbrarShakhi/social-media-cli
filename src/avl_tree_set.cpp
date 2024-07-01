
#include "../include/avl_tree_set.h"
#include "../include/utils.h"

#include <vector>
#include <string>
#include <string.h>

int AVLTreeSet::height(Node* N) {
	if (N == NULL)
		return 0;
	return N->height;
}

int AVLTreeSet::max(int a, int b) { return (a > b) ? a : b; }

AVLTreeSet::Node* AVLTreeSet::newNode(const char key[]) {
	Node* node = new Node();
	cstrcpy(node->data, key);
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	return (node);
}

AVLTreeSet::Node* AVLTreeSet::rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

AVLTreeSet::Node* AVLTreeSet::leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int AVLTreeSet::getBalance(Node* N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

AVLTreeSet::Node* AVLTreeSet::insert(Node* node, const char key[]) {
	if (node == NULL) {
		size++;
		return (newNode(key));
	}

	if (strcmp(key, node->data) < 0) // key < node->data
		node->left = insert(node->left, key);
	else if (strcmp(key, node->data) > 0) // key > node->data
		node->right = insert(node->right, key);
	else
		return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 &&
		strcmp(key, node->left->data) < 0) // key < node->left->data
		return rightRotate(node);

	if (balance < -1 &&
		strcmp(key, node->right->data) > 0) // key > node->right->data
		return leftRotate(node);

	if (balance > 1 &&
		strcmp(key, node->left->data) > 0) // key > node->left->data
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 &&
		strcmp(key, node->right->data) < 0) // key < node->right->data
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

AVLTreeSet::Node* AVLTreeSet::minValueNode(Node* node) {
	Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

AVLTreeSet::Node* AVLTreeSet::remove(const char key[], Node* root) {
	if (root == NULL)
		return root;

	if (strcmp(key, root->data) < 0) // key < root->data
		root->left = remove(key, root->left);
	else if (strcmp(key, root->data) > 0) // key > root->data
		root->right = remove(key, root->right);
	else {
		size--;
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = root->left ? root->left : root->right;

			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			Node* temp = minValueNode(root->right);
			cstrcpy(root->data, temp->data);
			root->right = remove(temp->data, root->right);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void AVLTreeSet::inorder(Node* root, std::vector<std::string>& v) {
	if (!root) {
		return;
	}
	inorder(root->left, v);
	v.push_back(root->data);
	inorder(root->right, v);
}

int AVLTreeSet::length() { return size; }

AVLTreeSet::~AVLTreeSet() {
	Node* current = root;
	while (current) {
		Node* temp = current;
		current = current->left;
		delete temp;
	}
}

AVLTreeSet::AVLTreeSet() {
	root = nullptr;
	size = 0;
}

bool AVLTreeSet::find(const char key[]) {
	Node* current = root;
	while (current) {
		if (strcmp(key, current->data) < 0) {
			current = current->left;
		}
		else if (strcmp(key, current->data) > 0) {
			current = current->right;
		}
		else {
			return true;
		}
	}
	return false;
}
void AVLTreeSet::insert(const std::string& key) { root = insert(root, key.c_str()); }
void AVLTreeSet::remove(const std::string& key) { root = remove(key.c_str(), root); }
std::vector<std::string> AVLTreeSet::get_all() {
	std::vector<std::string> v;
	v.reserve(size);
	inorder(root, v);
	return v;
}