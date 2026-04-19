#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000000

// Function to find the minimum key vertex not yet included in MST
int minKey(int key[], bool mstSet[], int n) {
    int min = INF, min_index;
    for (int v = 1; v <= n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int primMST(int n, int graph[n+1][n+1]) {
    int parent[n+1];   // store MST
    int key[n+1];      // key values to pick minimum weight edge
    bool mstSet[n+1];  // track vertices included in MST

    for (int i = 1; i <= n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[1] = 0;     // start from vertex 1
    parent[1] = -1; // first node has no parent

    int totalWeight = 0;

    for (int count = 1; count <= n; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;
        totalWeight += key[u];

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    return totalWeight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize adjacency matrix
    int graph[n+1][n+1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // undirected
    }

    int result = primMST(n, graph);
    printf("%d\n", result);

    return 0;
}
