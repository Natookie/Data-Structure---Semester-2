#include <stdio.h>

int minHeap[100];
int dataCount = 1;

int getParentIndex(int index){
    return index / 2;
}
int getLeftChildIndex(int index){
    return index * 2;
}
int getRightChildIndex(int index){
    return index * 2 + 1;
}

void swapValue(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void viewHeap(){
    if(dataCount == 1){
        printf("Heap is empty.\n");
        return;
    }

    printf("Heap: ");
    for(int i = 1; i < dataCount; i++){
        printf("%d ", minHeap[i]);
    }
    printf("\n");
}

void heapUp(int index){
    if(index == 1) return;
    
    int parentIndex = getParentIndex(index);
    if(minHeap[parentIndex] <= minHeap[index]) return;

    swapValue(&minHeap[parentIndex], &minHeap[index]);
    heapUp(parentIndex);
}
void heapDown(int index){
    int leftChildIndex = getLeftChildIndex(index);
    int rightChildIndex = getRightChildIndex(index);
    int smallestIndex = index;

    if(leftChildIndex < dataCount && minHeap[leftChildIndex] < minHeap[smallestIndex]){
        smallestIndex = leftChildIndex;
    }
    if(rightChildIndex < dataCount && minHeap[rightChildIndex] < minHeap[smallestIndex]){
        smallestIndex = rightChildIndex;
    }
    if(smallestIndex != index){
        swapValue(&minHeap[index], &minHeap[smallestIndex]);
        heapDown(smallestIndex);
    }
}

/*
void insertHeap(int index){
    if(index <= 1) return;
    
    if(dataCount >= 100){
        printf("Heap is full.\n");
        return;
    }

    int parentIndex = getParentIndex(index);
    if(minHeap[parentIndex] <= minHeap[index]) return;

    swapValue(&minHeap[parentIndex], &minHeap[index]);
    heapUp(parentIndex);
}
*/

void pushHeap(int value){
	if(dataCount >= 100){
        printf("Heap is full.\n");
        return;
    }
    
    minHeap[dataCount] = value;
    heapUp(dataCount);
    dataCount++;
}
int popHeap(){
    if(dataCount <= 1){
        printf("Heap is empty.\n");
        return -1;
    }

    int minValue = minHeap[1];
    minHeap[1] = minHeap[dataCount - 1];
    dataCount--;
    heapDown(1);
    
    return minValue;
}

void createMenu(){
	puts("MIN HEAP");
    puts("1. Insert");
    puts("2. Pop");
    puts("3. View Heap");
    puts("4. Exit");
}

int main(){
    int choice, value;

    while(1){
    	puts("");
        createMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                pushHeap(value);
                break;
            case 2:
                value = popHeap();
                if(value != -1){
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                viewHeap();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
