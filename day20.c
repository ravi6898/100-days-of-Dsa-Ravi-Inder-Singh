#include <stdio.h>
#include <stdlib.h>

// Hash map node
typedef struct Node {
    long long key;   // prefix sum
    int value;       // frequency
    struct Node* next;
} Node;

// Hash map size (prime number for better distribution)
#define SIZE 100003

Node* hashTable[SIZE];

// Hash function
unsigned long long hash(long long x) {
    return (x % SIZE + SIZE) % SIZE;
}

// Insert or update frequency
void insert(long long key) {
    unsigned long long idx = hash(key);
    Node* curr = hashTable[idx];
    while (curr) {
        if (curr->key == key) {
            curr->value++;
            return;
        }
        curr = curr->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = 1;
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// Get frequency of a key
int get(long long key) {
    unsigned long long idx = hash(key);
    Node* curr = hashTable[idx];
    while (curr) {
        if (curr->key == key) return curr->value;
        curr = curr->next;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    long long prefix_sum = 0;
    long long count = 0;

    // Initialize with prefix sum 0 occurring once
    insert(0);

    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];
        int freq = get(prefix_sum);
        count += freq;       // add all previous occurrences
        insert(prefix_sum);  // update frequency
    }

    printf("%lld\n", count);
    return 0;
}