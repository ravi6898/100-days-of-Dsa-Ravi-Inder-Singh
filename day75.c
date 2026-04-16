#include <stdio.h>
#include <stdlib.h>

// HashMap node structure
struct HashNode {
    int sum;
    int index;
    struct HashNode* next;
};

// HashMap size
#define SIZE 1000

// Hash function
int hash(int key) {
    if (key < 0) key = -key;
    return key % SIZE;
}

// Insert into hashmap
void insert(struct HashNode* hashTable[], int sum, int index) {
    int h = hash(sum);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->sum = sum;
    newNode->index = index;
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}

// Search in hashmap
int search(struct HashNode* hashTable[], int sum) {
    int h = hash(sum);
    struct HashNode* temp = hashTable[h];
    while (temp) {
        if (temp->sum == sum) return temp->index;
        temp = temp->next;
    }
    return -1;
}

// Function to find longest zero-sum subarray length
int longestZeroSumSubarray(int arr[], int n) {
    struct HashNode* hashTable[SIZE] = {NULL};
    int prefix_sum = 0, max_len = 0;

    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];

        if (prefix_sum == 0) {
            max_len = i + 1;
        }

        int prevIndex = search(hashTable, prefix_sum);
        if (prevIndex != -1) {
            int len = i - prevIndex;
            if (len > max_len) max_len = len;
        } else {
            insert(hashTable, prefix_sum, i);
        }
    }
    return max_len;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Length of longest zero-sum subarray: %d\n", longestZeroSumSubarray(arr, n));
    return 0;
}