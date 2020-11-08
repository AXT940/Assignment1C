#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

#include "bst.h"

Node *root=NULL;

#include "unique_rng.c"
#include "serve_client.c"

int f_verbose = 0;

void clean(){
	/*****************************************************/
	/******   Free resources before program ends  ********/
	/*****************************************************/

	root=freeSubtree(root);
	root= NULL;
	return;
}


void test_tack2(){

	printf("/******** TEST OF PART 2 ********/\n\n");
	unsigned int i;
	char *client_names[5] = {"client1_commands", "client2_commands", "client3_commands",
	                         "client4_commands", "client5_commands"};

	pthread_t threads[6];

	// spawn all threads
	pthread_create(&threads[0], NULL, (void *) ServeClient, client_names[0]);
	pthread_create(&threads[1], NULL, (void *) ServeClient, client_names[1]);
	pthread_create(&threads[2], NULL, (void *) ServeClient, client_names[2]);
	pthread_create(&threads[3], NULL, (void *) ServeClient, client_names[3]);
	pthread_create(&threads[4], NULL, (void *) ServeClient, client_names[4]);


	// join all readers
	for (i = 0; i < 5; i++) {
		pthread_join(threads[i], NULL);
	}
	//pthread_join(threads[0], NULL);
	// The tree should only have one node now
	int count = countNodes(root);
	int sum = sumSubtree(root);

	if (count == 1 && sum == 1){
		printf("Test: Given for Part2 seems OK\n");
	} else{
		printf("Test: Given for Part2 fail\n");
	}

	// Free the tree
	clean();
}

// TODO: You could add more test functions here

void test_1() {
	char* client_name = "client6_commands";
	pthread_t thread;
	
	pthread_create(&thread, NULL, (void*) ServeClient, client_name);
	pthread_join(thread, NULL);
	
	int count = countNodes(root);
	int sum = sumSubtree(root);
	
	if (count == 7 && sum == 42) {
		printf("Test1 for Part2 seems ok.\n");
	} else {
		printf("Test1 for Part2 failed.\n");
	}
	
	clean();
}

void test_2() {
	char* client_name[2] = {"client6_commands", "client7_commands"};
	pthread_t threads[2];
	
	pthread_create(&threads[0], NULL, (void*) ServeClient, client_name[0]);
	pthread_create(&threads[1], NULL, (void*) ServeClient, client_name[1]);
	
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	
	clean();
	
	printf("Test2 for Part2 complete.\n");
}

int main(int argc, char *argv[]){

	if(argc == 2){
	  if(strcmp(argv[1],"-v") == 0)
	    {
	      f_verbose = 1;
	    }
 	}

	test_tack2();

	// TODO: You could call your test functions at here
	test_1();
	test_2();
	return 0;
}
