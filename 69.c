#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    Edge **adj;
    int n;
} Graph;

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

Graph *create_graph(int n) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->adj = calloc(n, sizeof(Edge *));
    return g;
}

void add_edge(Graph *g, int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = g->adj[u];
    g->adj[u] = e;
}

MinHeap *create_heap(int capacity) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->data = malloc(sizeof(HeapNode) * (capacity + 1));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap_heap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify_up(MinHeap *h, int idx) {
    while (idx > 1) {
        int parent = idx / 2;
        if (h->data[parent].dist <= h->data[idx].dist)
            break;
        swap_heap_nodes(&h->data[parent], &h->data[idx]);
        idx = parent;
    }
}

void heapify_down(MinHeap *h, int idx) {
    while (2 * idx <= h->size) {
        int left = 2 * idx;
        int right = left + 1;
        int smallest = left;
        if (right <= h->size && h->data[right].dist < h->data[left].dist)
            smallest = right;
        if (h->data[smallest].dist >= h->data[idx].dist)
            break;
        swap_heap_nodes(&h->data[smallest], &h->data[idx]);
        idx = smallest;
    }
}

void push_heap(MinHeap *h, int node, int dist) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, sizeof(HeapNode) * (h->capacity + 1));
    }
    h->size++;
    h->data[h->size].node = node;
    h->data[h->size].dist = dist;
    heapify_up(h, h->size);
}

int heap_empty(MinHeap *h) {
    return h->size == 0;
}

HeapNode pop_heap(MinHeap *h) {
    HeapNode top = h->data[1];
    h->data[1] = h->data[h->size];
    h->size--;
    if (h->size > 0)
        heapify_down(h, 1);
    return top;
}

void dijkstra(Graph *g, int src, int *dist) {
    for (int i = 0; i < g->n; i++)
        dist[i] = INF;

    MinHeap *pq = create_heap(g->n + 1);
    dist[src] = 0;
    push_heap(pq, src, 0);

    while (!heap_empty(pq)) {
        HeapNode cur = pop_heap(pq);
        int u = cur.node;
        int d = cur.dist;
        if (d > dist[u])
            continue;

        for (Edge *e = g->adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            int nd = d + e->weight;
            if (nd < dist[v]) {
                dist[v] = nd;
                push_heap(pq, v, nd);
            }
        }
    }

    free(pq->data);
    free(pq);
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2)
        return 0;

    Graph *g = create_graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        // Input is 0-based; if edges are 1-based, subtract 1 from u and v.
        add_edge(g, u, v, w);
        add_edge(g, v, u, w); // remove this line for directed graphs
    }

    int src;
    scanf("%d", &src);

    int *dist = malloc(sizeof(int) * n);
    dijkstra(g, src, dist);

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }

    for (int i = 0; i < n; i++) {
        Edge *e = g->adj[i];
        while (e) {
            Edge *tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
    free(dist);
    return 0;
}
