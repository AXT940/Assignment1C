#define COMMAND_LENGTH 50
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


unsigned int convertValue(char* string) {
	char number[COMMAND_LENGTH];
	int index = 0;
	//printf("%s",string);
	while(string[index] != '\n' && string[index] != '\0') {
		number[index] = string[index];
		index++;
	}
	return strtoul(number, NULL, 10);
} 

void* ServeClient(char *client){
	FILE *command_file = fopen(client, "r"); //opens the file 
	if (command_file == NULL) exit(-1); //failed to open the file
	
	char command_line[COMMAND_LENGTH];
	char delimiter[] = " ";
	
	while (fgets(command_line, COMMAND_LENGTH, command_file) != NULL) { 
		char* command = strtok(command_line, delimiter);
		unsigned int data = 0;
		
		if (strcmp(command, "insertNode") == 0) { //write
			char* value = strtok(NULL, delimiter);
			if (value == NULL) {
				printf("[%s]%s %s\n", client, command, value);
				return NULL;
			} else {
				data = convertValue(value);
			}
			
			pthread_rwlock_wrlock(&lock);
			root = insertNode(root, data);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s %d\n", client, command, data);
		} else if (strcmp(command, "deleteNode") == 0) { //write
			char* value = strtok(NULL, delimiter);
			if (value == NULL) {
				printf("[%s]%s %s\n", client, command, value);
				return NULL;
			} else {
				data = convertValue(value);
			}
			pthread_rwlock_wrlock(&lock);
			root = deleteNode(root, data);
			pthread_rwlock_unlock(&lock);
			
			printf("[%s]%s %d\n", client, command, data);
		} else if (strcmp(command, "countNodes\n") == 0) { //read
			pthread_rwlock_rdlock(&lock);
			data = countNodes(root);
			pthread_rwlock_unlock(&lock);			
					
			printf("[%s]countNodes = %d\n", client, data);
		} else if (strcmp(command, "sumSubtree\n") == 0) { //read
			pthread_rwlock_rdlock(&lock);
			data = sumSubtree(root);
			pthread_rwlock_unlock(&lock);

			printf("[%s]sumSubtree = %d\n", client, data);
		} else {
			printf("[%s]Command error: %s.\n", client, command);
		}
	}
	fclose(command_file);
	return NULL;
}

