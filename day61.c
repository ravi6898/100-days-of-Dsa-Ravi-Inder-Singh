#include <stdio.h>

int main() {
    int n, m, directed;
    scanf("%d", &n);          // number of vertices
    scanf("%d", &m);          // number of edges
    scanf("%d", &directed);   // 0 = undirected, 1 = directed

    int adj[n][n];

    // Initialize matrix with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // assuming vertices are numbered from 1 to n
        adj[u-1][v-1] = 1;

        if (!directed) {
            adj[v-1][u-1] = 1; // add reverse edge for undirected graph
        }
    }

    // Print adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}