#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	Node *root=NULL;
	
	printSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root));
	printf("%d\n", sumSubtree(root));
	root = deleteNode(root, 4);
	printf("\n");
	
	root=insertNode(root, 14);
	root=insertNode(root, 12);
	root=insertNode(root, 6);
	root=insertNode(root, 17);
	root=insertNode(root, 8);
	root=deleteNode(root, 4);
	printSubtree(root);
	printf("\n");
	printf("%d\n", sumSubtree(root));
	root=deleteNode(root,14);
	root=deleteNode(root,8);
	printSubtree(root);
	root=freeSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root));
	printf("\n");
	
	root = insertNode(root, 19);
	root = insertNode(root, 1);
	root = insertNode(root, 21);
	root = insertNode(root, 0);
	root = insertNode(root, 10);
	root = insertNode(root, 20);
	root = insertNode(root, 22);

	printSubtree(root);
	printf("\n");
	printf("%d\n", sumSubtree(root)); //93
	printf("Number of nodes=%d\n", countNodes(root)); //7

	root=deleteNode(root, 0);
	printSubtree(root);
	printf("\n");

	root = deleteNode(root, 1);
	printSubtree(root);
	printf("\n");

	root=deleteNode(root, 21);
	printSubtree(root);
	printf("%d\n", sumSubtree(root)); //71
	//printf("\n");
	//printSubtree(root);
	root=freeSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root));
	printf("\n");
	
	root = insertNode(root, 8);
	root = insertNode(root, 3);
	root = insertNode(root, 11);
	root = insertNode(root, 1);
	root = insertNode(root, 6);
	root = insertNode(root, 7);
	root = insertNode(root, 9);
	root = insertNode(root, 10);
	root = insertNode(root, 14);
	root = insertNode(root, 12);
	root = insertNode(root, 15);

	deleteNode(root, 11);
	printSubtree(root);
	printf("\n");
	printf("%d\n", sumSubtree(root)); //96
	printf("Number of nodes=%d\n", countNodes(root)); //10
	printf("\n");
	root = freeSubtree(root);
	
	root = insertNode(root, 3);
	root = deleteNode(root, 3);
	printf("%d\n", sumSubtree(root));
	printf("Number of nodes=%d\n", countNodes(root)); //10
	root = insertNode(root, 7);
	root = insertNode(root, 4);
	root = insertNode(root, 20);
	root = insertNode(root, 10);
	root = insertNode(root, 8);
	root = insertNode(root, 9);
	root = insertNode(root, 11);
	root = insertNode(root, 12);
	root = insertNode(root, 30);
	root = insertNode(root, 25);
	root = insertNode(root, 31);
	printSubtree(root);
	root = deleteNode(root, 10);
	printSubtree(root);
	root = insertNode(root, 26);
	root = insertNode(root, 28);
	root = insertNode(root, 27);
	root = (insertNode(root, 29));
	root = deleteNode(root, 30);
	printSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root)); //10
	printf("%d\n", sumSubtree(root));
	root = deleteNode(root, 28);
	printSubtree(root);
	root = deleteNode(root, 26);
	printSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root)); //10
	return 0;
}
