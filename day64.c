#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue implementation
int queue[MAX], front = -1, rear = -1;

void enqueue(int x) {
    if (rear == MAX - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = x;
}

int dequeue() {
    if (front == -1 || front > rear) {
        return -1;
    }
    return queue[front++];
}

int isEmpty() {
    return (front == -1 || front > rear);
}

int main() {
    int n, s;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // adjacency list
    int adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;   // directed graph
        // adj[v][u] = 1; // uncomment for undirected graph
    }

    printf("Enter source vertex: ");
    scanf("%d", &s);

    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // BFS
    enqueue(s);
    visited[s] = 1;

    printf("BFS Traversal: ");
    while (!isEmpty()) {
        int node = dequeue();
        printf("%d ", node);

        for (int v = 0; v < n; v++) {
            if (adj[node][v] == 1 && !visited[v]) {
                enqueue(v);
                visited[v] = 1;
            }
        }
    }
    printf("\n");

    return 0;
}