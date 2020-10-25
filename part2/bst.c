#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

// Your source code here
Node* createSubTree(int value, Node* left, Node* right) {
	Node* newNode = (Node *) malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

Node* insertNode(Node* root, int value) {
	if (root == NULL) {
		return createSubTree(value, NULL, NULL);
	}

	if (root->data > value) {
	 	if (root->left == NULL) {
	 		root->left = createSubTree(value, NULL, NULL);
	 		return root;
	 	} else {
			 root->left = insertNode(root->left, value);
	 		return root;
	 	}
	} else if (root->data < value) {
		if (root->right == NULL) {
	 		root->right = createSubTree(value, NULL, NULL);
	 		return root;
	 	} else {
			root->right = insertNode(root->right, value);
			return root;
		}
	} else {
		return root;
	}
}

void printSubtree(Node *N) {
	//in order
	if (N->left != NULL) {
		printSubtree(N->left);
	} 

	printf("%d\n", N->data);

	if (N->right != NULL) {
		printSubtree(N->right);
	}
}

void recursiveCount(Node *N, int *pCounter) {
	++*pCounter;

	if (N->left != NULL) {
		recursiveCount(N->left, pCounter);
	} 

	if (N->right != NULL) {
		recursiveCount(N->right, pCounter);
	}
}

int countNodes(Node *N) {
	int counter = 0;
	int * pCounter = &counter;
	if (N == NULL) {
		return 0;
	}
	recursiveCount(N, pCounter);
	return *pCounter;
}

void recursiveSum(Node *N, int *pSum) {
	*pSum += N->data;

	if (N->left != NULL) {
		recursiveSum(N->left, pSum);
	} 

	if (N->right != NULL) {
		recursiveSum(N->right, pSum);
	}
}

int sumSubtree(Node *N) {
	int sum= 0;
	int *pSum = &sum;
	recursiveSum(N, pSum);
	return *pSum;
}

void freeNode(Node* N) {
	if (N->left != NULL) {
		freeNode(N->left);
	}

	if (N->right != NULL) {
		freeNode(N->right);
	}

	free(N);
}

Node* freeSubtree(Node *N) {
	if (N == NULL) {
		return N;
	}
	
	freeNode(N);
	return NULL;
}

Node* deleteNode(Node* root, int value) {
	if (root == NULL) {
		return root;
	}
	Node* currentNode = root;
	if (root->data > value) { //move down the left subtree
		root->left = deleteNode(root->left, value);
	} else if (root->data < value) { //move down the right subtree
		root->right = deleteNode(root->right, value);
	} else { //the node is found
		
		if (currentNode->left == NULL) { //deals with leaf or right subtree of node
			currentNode = root->right; //moves the right subtree up, even if NULL
			free(root); //frees the memory assigned to root
			root = currentNode; //sets the pointer to the right tree
		} else if (currentNode->right == NULL) { //moves left up
			currentNode = root->left;
			free(root);
			root = currentNode;
		} else { //the node has two children
			currentNode = root->right; //places the cursor at the right subtree
			Node* parent = root; //parent of the left most node

			while (currentNode->left != NULL) { //while currentNode isn't the left most node of the tree
				parent = currentNode;
				currentNode = parent->left;
			}
			
			root->data = currentNode->data; //copy the data of the leftmost right node 
			root->right = deleteNode(root->right, currentNode->data); //remove the leftmost node which has been copied
		}
	}
	//case 1: leaf node, just remove
	//case 2: one subtree, remove node and move sub tree up
	//case 3: two subtrees, remove node, pull up right trees smallest node, pull right of smallest node up
	return root;
}
