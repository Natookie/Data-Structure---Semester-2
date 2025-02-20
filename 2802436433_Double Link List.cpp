#include <stdio.h>
#include <stdlib.h>

/*
	2802436433 || Natanael Kevin Kurniawan
	Tugas: Double linked list, push & pop
*/

struct Node{
	int x;
	
	struct Node* next;
	struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;

struct Node* createNewNode(int x){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	
	newNode->x = x;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

//===PUSH
void PushHead(int x){
	struct Node* newNode = createNewNode(x);
	
	if(head == NULL) head = tail = newNode;
	else{
		newNode->next = head;
		head->prev = newNode;
		
		head = newNode;
		head->prev = NULL;
	}
}

void PushTail(int x){
	struct Node* newNode = createNewNode(x);
	
	if(head == NULL) head = tail = newNode;
	else{
		newNode->prev = tail;
		tail->next = newNode;
		
		tail = newNode;
		tail->next = NULL;
	}
}

void PushMid(int x){
	struct Node* newNode = createNewNode(x);
	
	if(head == NULL) head = tail = newNode;
	else{
		struct Node* curr = head;
		//Beda dari source code, ini dia sorting asc
		if(head->x > x){
			PushHead(x);
			return;
		}else if(tail->x < x){
			PushTail(x);
			return;
		}
		
		while(curr->next != NULL && curr->next->x < x){
			curr = curr->next;
		}
		newNode->next = curr->next;
		newNode->prev = curr;
		
		curr->next = newNode;
		newNode->next->prev = newNode;
	}
}

//===POP
void PopHead(){
	struct Node* curr = head;
	
	if(head == NULL) return;
	if(head == tail){
		head = tail = NULL;
		free(curr);
	}else{
		curr = head;
		head = head->next;
		head->prev = NULL;
		free(curr);
	}
}

void PopTail(){
	struct Node* curr = head;
	
	if(head == NULL) return;
	if(head == tail){
		head = tail = NULL;
		free(curr);
	}else{
		curr = tail;
		tail = tail->prev;
		tail->next = NULL;
		free(curr);
	}
}

void PopMid(int x){
	struct Node* curr = head;
	
	if(head == NULL) return;
	if(head->x == x){
		PopHead();
		return;
	}
	else if(tail->x == x){
		PopTail();
		return;
	}
	
	while(curr->x != x && curr->next != NULL){
		curr = curr->next;
	}
	
	if(curr->next == NULL) return;
	
	struct Node* toDelete = curr->next;
	curr->next = toDelete->next;
	toDelete->next->prev = curr;
	toDelete->next = NULL;
	toDelete->prev = NULL;
				
	free(toDelete);
}

//===SEARCH
int index = 0;
void PrintSearchNode(int x){
	struct Node* curr = head;
	
	index = 0;
	while(curr != NULL && curr->x != x){
		curr = curr->next;
		index++;
	}
	
	if(curr == NULL){
		printf("X : %d \t (Index: %d) \n", x, -1);
		return;
	}
	
	printf("X : %d \t (Index: %d) \n", curr->x, index);
}

//===VIEW
void PrintAllNodes(){
	struct Node* curr = head;
	
	if(curr == NULL){
		printf("Data not found");
		return;
	}
	
	index = 0;
	while(curr != NULL){ 
		index++;
		printf("X : %d \t (Index: %d) \n", curr->x, index - 1);
		
		curr = curr->next;
	}
}

void FreeAllNodes(){
    struct Node* curr = head;
    while (curr != NULL){
        struct Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = tail = NULL;
}


int main(){
	PushHead(1);
	PushHead(2);
	PushHead(3);
	PushHead(4);
	PushTail(0);
	
	PushMid(10);
	PushMid(12);
	PushMid(11);
	PushMid(13);
	
	PopHead();
	PopTail();
	PopMid(12);
	
	/*Timeline
	4 -> Deleted, pop head
	3
	2
	1
	0 -> Push tail
	10 -> Bigger than tail
	12 -> Deleted, pop mid
	11
	13 -> Deleted. pop tail
	*/
	
	puts("");
	puts("=================PRINT ALL");
	PrintAllNodes();
	
	puts("");
	puts("=================PRINT SPECIFIC");
	PrintSearchNode(0);
	PrintSearchNode(13);
	PrintSearchNode(3);
	
	FreeAllNodes();
	return 0;
}
