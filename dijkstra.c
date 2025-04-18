#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 23  // Number of areas in the transport network

// Display the matrix
void display_matrix(int matrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Get the index of the node with minimum distance
int min_distance(int dist[], bool visited[]) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int src, int target, const char* areas[V]) {
    int dist[V];
    bool visited[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(dist, visited);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[target] == INT_MAX) {
        printf("No path exists between %s and %s.\n", areas[src], areas[target]);
        return;
    }

    printf("Shortest path from %s to %s with distance %d:\n", areas[src], areas[target], dist[target]);

    // Print path
    int path[V];
    int path_length = 0;
    for (int v = target; v != -1; v = parent[v]) {
        path[path_length++] = v;
    }
    for (int i = path_length - 1; i > 0; i--) {
        printf("%s -> ", areas[path[i]]);
    }
    printf("%s\n", areas[path[0]]);
}

// Main program
int main() {
    const char* areas[V] = {
        "Bangkok", "Nonthaburi", "Pathum Thani", "Samut Prakan", "Nakhon Pathom", "Chachoengsao",
        "Ayutthaya", "Ang Thong", "Sing Buri", "Lopburi", "Saraburi", "Nakhon Nayok", "Chonburi",
        "Rayong", "Chanthaburi", "Trat", "Prachinburi", "Sa Kaeo", "Ratchaburi", "Samut Sakhon",
        "Samut Songkhram", "Phetchaburi", "Prachuap Khiri Khan"
    };

    // Sample graph: INF = no connection, 1 = direct connection (replace with real distances)
    int graph[V][V];

    // Initialize the graph with no connections
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    // Sample connections (add your real data here)
    graph[0][1] = 10; graph[1][0] = 10; // Bangkok - Nonthaburi
    graph[0][3] = 20; graph[3][0] = 20; // Bangkok - Samut Prakan
    graph[1][2] = 15; graph[2][1] = 15; // Nonthaburi - Pathum Thani
    graph[2][5] = 25; graph[5][2] = 25; // Pathum Thani - Chachoengsao
    graph[5][12] = 30; graph[12][5] = 30; // Chachoengsao - Chonburi

    printf("Extended Bangkok Metropolitan Area Transport Network:\n");
    display_matrix(graph);

    int src_index, dest_index;

    do {
        printf("\nChoose source area:\n");
        for (int i = 0; i < V; i++) printf("%2d: %s\n", i, areas[i]);
        printf("Enter source area number (0-%d): ", V - 1);
        scanf("%d", &src_index);
    } while (src_index < 0 || src_index >= V);

    do {
        printf("\nChoose destination area:\n");
        for (int i = 0; i < V; i++) printf("%2d: %s\n", i, areas[i]);
        printf("Enter destination area number (0-%d): ", V - 1);
        scanf("%d", &dest_index);
    } while (dest_index < 0 || dest_index >= V);

    dijkstra(graph, src_index, dest_index, areas);

    return 0;
}
