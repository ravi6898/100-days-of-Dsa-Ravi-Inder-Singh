#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

typedef struct Queue {
    Node* arr[100];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear == 99) return; // overflow, assuming N <= 100
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->arr[q->rear] = node;
}

Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    Node* node = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return node;
}

void mirror(Node* node) {
    if (node == NULL) return;
    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
    mirror(node->left);
    mirror(node->right);
}

void inorder(Node* node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int N;
    scanf("%d", &N);
    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    if (N == 0) {
        printf("\n");
        return 0;
    }
    Queue q;
    initQueue(&q);
    Node* root = newNode(arr[0]);
    enqueue(&q, root);
    int index = 1;
    while (!isEmpty(&q) && index < N) {
        Node* curr = dequeue(&q);
        // left child
        if (arr[index] != -1) {
            curr->left = newNode(arr[index]);
            enqueue(&q, curr->left);
        }
        index++;
        if (index >= N) break;
        // right child
        if (arr[index] != -1) {
            curr->right = newNode(arr[index]);
            enqueue(&q, curr->right);
        }
        index++;
    }
    mirror(root);
    inorder(root);
    printf("\n");
    // Don't forget to free memory, but for simplicity, omit in contest code
    free(arr);
    return 0;
}
