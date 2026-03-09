#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100005

// Min-Heap (smaller value has higher priority)
int heap[MAX_SIZE];
int size = 0;

// Helper functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Move newly inserted element up to correct position
void heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] <= heap[idx]) {
            break;
        }
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

// Move element at idx down to correct position
void heapify_down(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&heap[idx], &heap[smallest]);
        heapify_down(smallest);
    }
}

void insert(int x) {
    if (size >= MAX_SIZE) {
        // In real problems usually not needed, but good practice
        return;
    }
    heap[size] = x;
    heapify_up(size);
    size++;
}

int delete_min() {
    if (size == 0) {
        return -1;
    }
    
    int min_val = heap[0];
    heap[0] = heap[size - 1];
    size--;
    if (size > 0) {
        heapify_down(0);
    }
    return min_val;
}

int peek() {
    if (size == 0) {
        return -1;
    }
    return heap[0];
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // consume newline after reading N

    for (int i = 0; i < N; i++) {
        char op[10];
        int val;

        // Read the entire line
        fgets(op, sizeof(op), stdin);
        
        // Remove trailing newline