#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#define HASH_SIZE 5
#define COLL_SIZE 3
#define OPT_SIZE 3
#define QUIT_SIZE 2

#define TABLE_SIZE 10

void setColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void displayMenu(const char* title, char* menuItems[], int size, int selectedIndex){
	system("cls");

	puts(title);
	puts("   ===================================================");
	for(int i = 0; i < size; i++){
		if(i == selectedIndex){
			setColor(10);
			printf(">> %s\n", menuItems[i]);
			setColor(7);
		}else{
			printf("   %s\n", menuItems[i]);
		}
	}
}

int navigateMenu(const char* title, char* menuItems[], int size){
	int selectedIndex = 0;
	char key;

	displayMenu(title, menuItems, size, selectedIndex);
	
	while(1){
		if(_kbhit()){
			key = _getch();
			
			if(key == 'W' || key =='w') selectedIndex = (selectedIndex - 1 + size) % size;
			else if(key == 'S' || key =='s') selectedIndex = (selectedIndex + 1) % size;
			else if(key == 13) return selectedIndex;
			
			displayMenu(title, menuItems, size, selectedIndex);
		}
	}
}

int hashIndex = -1, collIndex = -1;
int globalCount = 0;

struct Node{
	char data[101];
	struct Node* next;
};

char* hashTable[TABLE_SIZE] = {NULL};
struct Node* chainTable[TABLE_SIZE] = {NULL};

//HASHING=============================================================================================
char* hashItem[HASH_SIZE] = {"Mid-Square", "Division", "Folding", "Digit Extraction", "Rotation"};
void hashMenu(){
	int selectedHash = navigateMenu("   Welcome to Hashink, choose the hashing method", hashItem, HASH_SIZE);	
	hashIndex = selectedHash;
}

//COLLISION===========================================================================================
char* collItem[COLL_SIZE] = {"Linear Probing", "Chaining", "Rehashing"};
void collisionMenu(){
	int selectedCollision = navigateMenu("   Choose the collision handling method", collItem, COLL_SIZE);
	collIndex = selectedCollision;
}

//QUIT=================================================================================================
void resetTable(){
	int fakeDur = 1;
	
	for(int i = 0; i < TABLE_SIZE; i++){
		if(hashTable[i] != NULL){
			free(hashTable[i]);
			hashTable[i] = NULL;
			fakeDur++;
		}
		
		struct Node* curr = chainTable[i];
		while(curr != NULL){
			struct Node* toDel = curr;
			curr = curr->next;
			free(toDel);
		}
		chainTable[i] = NULL;
	}
	
	
	globalCount = 0;
	hashIndex = 0;
	collIndex = 0;
	
	system("cls");
	puts("    All data cleared, restarting...");
	
	char fakeLoad[] = "    ##########################";
	int fakeLen = strlen(fakeLoad);
	for(int i = 0; i < fakeLen; i++){
		printf("%c", fakeLoad[i]);
		_sleep(15 * fakeDur);
	}
	
	hashMenu();
	collisionMenu();
}

char* quitItem[QUIT_SIZE] = {"Close App", "Go back to start"};
void quitMenu(){
	int quitChoice = navigateMenu("   Are you sure you want to quit?", quitItem, QUIT_SIZE);
	if(quitChoice == 0){
		printf("\n   Exiting application...\n");
		exit(0);
	}else{
		resetTable();
	}
}

//HASH TABLE LOGIC===================================================================================
int hashFunction(char* word){
	/* LIST HASH METHOD
	0 = "Mid-Square", 
	1 = "Division", 
	2 = "Folding", 
	3 = "Digit Extraction", 
	4 = "Rotation"
	*/
	int wordLen = strlen(word);
	int hashKey = -1;
	
	switch(hashIndex){
		case 0:{
			int square = 0;
			for(int i = 0; i < wordLen; i++){
				square += word[i];
			}
			square = pow(square, 2);
			hashKey = (square / 100) % TABLE_SIZE;
			
			break;
		}
		case 1:{
			int sum = 0;
			for(int i = 0; i < wordLen; i++){
				sum += word[i];
			}
			hashKey = sum % TABLE_SIZE;
			
			break;
		}
		case 2:{
			int sum = 0;
			int chunkSize = 2;
			for(int i = 0; i < wordLen; i++){
				int chunk = 0;
				for(int j = 0; j < chunkSize; j++){
					chunk = chunk * 10 + word[i + j];
				}
				sum += chunk;
			}
			hashKey = sum % TABLE_SIZE;
			
			break;
		}
		case 3:{
			if(wordLen >= 3) hashKey = (word[0] + word[wordLen / 2] + word[wordLen - 1]) % TABLE_SIZE;
			else hashKey = 0 % TABLE_SIZE;
			
			break;
		}
		case 4:{
			int sum = 0;
			for(int i = 0; i < wordLen; i++){
				sum = (sum << 4) ^ (sum >> 28) ^ word[i];
			}
			hashKey = sum % TABLE_SIZE;
			
			break;
		}
	}
	
	return hashKey;
}

void insertData(){
	char word[101];
	system("cls");
	
	if(globalCount >= TABLE_SIZE){
		setColor(12);
		puts("TABLE SIZE IS FULL");
		setColor(7);
		
		puts("");
		system("pause");
		return;
	}
	
	printf("   Enter a STRING to insert: \n"); 
	printf("   => "); setColor(6);
	scanf("%100s", word); setColor(7);
	
	int index = hashFunction(word);
	
	/* LIST COLLISSION METHOD
	0 = "Linear Probing", 
	1 = "Chaining", 
	2 = "Rehashing"
	*/
	switch(collIndex){
		case 0:{
			while(hashTable[index] != NULL){
				index = (index + 1) % TABLE_SIZE;
			}	
			hashTable[index] = strdup(word);
			
			break;
		}
		case 1:{
			struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
			strcpy(newNode->data, word);
			newNode->next = NULL;
			
			if(chainTable[index] == NULL){
				chainTable[index] = newNode;
			}else{
				struct Node* curr = chainTable[index];
				while(curr->next != NULL){
					curr = curr->next;
				}
				curr->next = newNode;
			}
			
			break;
		}
		case 2:{
			int i = 1;
		    int rehashIndex = index;
		
		    while(hashTable[rehashIndex] != NULL){
		        rehashIndex = (index + i * i) % TABLE_SIZE;
		        i++;
		        if(i >= TABLE_SIZE){
		            printf("   Hash table is full, cannot insert \"%s\"\n", word);
		            return;
		        }
		    }
		
		    hashTable[rehashIndex] = strdup(word);
		    index = rehashIndex;
			break;
		}
	}

	puts("");
	printf("   +-------------------------------------+\n");
	printf("     Inserted \"%s\" at index %d  \n", word, index);
	printf("   +-------------------------------------+\n");

	globalCount++;
	puts("");
	system("pause");
}

// VIEW FUNCTION======================================================================================
void viewData(){
	system("cls");
	printf("   Hash Table:\n");
	printf("   =====================================\n");

	for(int i = 0; i < TABLE_SIZE; i++){
		printf("   Index %d: ", i);
		if(collIndex == 1 && chainTable[i] != NULL){
			struct Node* curr = chainTable[i];
			setColor(6);
			while(curr != NULL){
				printf("%s", curr->data);
				if(curr->next != NULL) printf(" -> ");
				else puts("");
				curr = curr->next;
			}
			setColor(7);
		}else if(hashTable[i] != NULL){
			setColor(6);
			printf("%s\n", hashTable[i]);
			setColor(7);
		}else{
			setColor(12);
			printf("(NULL)\n");
			setColor(7);
		}
	}
	
	puts("");
	system("pause");
}

//OPTION==============================================================================================
char* optionItem[OPT_SIZE] = {"Insert", "View", "Exit"};
void optionMenu(){
	while(1){
		char optionTitle[100];
		sprintf(optionTitle, "   Choose an option [%s | %s]", hashItem[hashIndex], collItem[collIndex]);
		
		int selectedOption = navigateMenu(optionTitle, optionItem, OPT_SIZE);

		if(selectedOption == 0) insertData();
		else if(selectedOption == 1) viewData();
		else quitMenu();
	}
}

int main(){
	hashMenu();
	collisionMenu();
	optionMenu();
	
	return 0;
}

/*
	Color:
	Black				0
	Blue				1
	Green				2
	Cyan				3
	Red					4
	Purple				5
	Yellow (Gold)		6
	White (Gray)		7
	Gray (Dark Gray)	8
	
	Light Blue			9
	Light Green			10
	Light Aqua			11
	Light Red			12
	Light Purple		13
	Light Yellow		14
	Bright White		15
*/

