#define COMMAND_LENGTH 30

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

void* ServeClient(char *client){
	FILE *command_file = fopen(client, "r");
	if (command_file == NULL) exit(-1);
	
	char command_line[COMMAND_LENGTH];
	while (fgets(command_line, COMMAND_LENGTH, command_file) != NULL) { 
		char command[COMMAND_LENGTH];
		char number[COMMAND_LENGTH];
		int value = 0;
		
		sscanf(command_line, "%s %s", command, number);
		
		if (strcmp(command, "countNodes") == 0) {
			pthread_rwlock_rdlock(&lock);
			value = countNodes(root);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s = %d\n", client, command, value);
			continue;
		} else if (strcmp(command, "sumSubtree") == 0) {
			pthread_rwlock_rdlock(&lock);
			value = sumSubtree(root);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s = %d\n", client, command, value);
			continue;
		}
		value = strtoul(number, NULL, 10);
		
		if (strcmp(command, "insertNode") == 0) {
			pthread_rwlock_wrlock(&lock);
			root = insertNode(root, value);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s %d\n", client, command, value);
		} else if (strcmp(command, "deleteNode") == 0) {
			pthread_rwlock_wrlock(&lock);
			root = deleteNode(root, value);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s %d\n", client, command, value);
		}
	}
	
	fclose(command_file);
	return NULL;
}
