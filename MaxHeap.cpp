#include <stdio.h>

int maxHeap[100];
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
        printf("%d ", maxHeap[i]);
    }
    printf("\n");
}

void heapUp(int index){
    if(index == 1) return;

    int parentIndex = getParentIndex(index);
    if(maxHeap[parentIndex] >= maxHeap[index]) return;

    swapValue(&maxHeap[parentIndex], &maxHeap[index]);
    heapUp(parentIndex);
}

void heapDown(int index){
    int leftChildIndex = getLeftChildIndex(index);
    int rightChildIndex = getRightChildIndex(index);
    int largestIndex = index;

    if(leftChildIndex < dataCount && maxHeap[leftChildIndex] > maxHeap[largestIndex]){
        largestIndex = leftChildIndex;
    }
    if(rightChildIndex < dataCount && maxHeap[rightChildIndex] > maxHeap[largestIndex]){
        largestIndex = rightChildIndex;
    }
    if(largestIndex != index){
        swapValue(&maxHeap[index], &maxHeap[largestIndex]);
        heapDown(largestIndex);
    }
}

void pushHeap(int value){
    if(dataCount >= 100){
        printf("Heap is full.\n");
        return;
    }

    maxHeap[dataCount] = value;
    heapUp(dataCount);
    dataCount++;
}

int popHeap(){
    if(dataCount <= 1){
        printf("Heap is empty.\n");
        return -1;
    }

    int maxValue = maxHeap[1];
    maxHeap[1] = maxHeap[dataCount - 1];
    dataCount--;
    heapDown(1);

    return maxValue;
}

void createMenu(){
    puts("MAX HEAP");
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
