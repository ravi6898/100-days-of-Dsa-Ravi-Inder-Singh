#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list representation
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX];   // adjacency list
int indegree[MAX]; // in-degree array
int n;             // number of vertices

// Function to add edge u -> v
void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
    indegree[v]++; // increase in-degree of v
}

// Kahn’s Algorithm
void topologicalSort() {
    int queue[MAX], front = 0, rear = 0;
    int count = 0;

    // Enqueue all vertices with in-degree 0
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    printf("Topological Order: ");
    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);
        count++;

        // Reduce in-degree of neighbors
        Node* temp = adj[u];
        while (temp != NULL) {
            indegree[temp->vertex]--;
            if (indegree[temp->vertex] == 0) {
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }

    // If count != n, graph has a cycle
    if (count != n) {
        printf("\nGraph has a cycle! Topological sort not possible.\n");
    }
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency list and indegree
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
        indegree[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    topologicalSort();

    return 0;
}