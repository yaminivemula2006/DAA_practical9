#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Pair structure: {weight, vertex}
typedef pair<int, int> iPair;

class Graph {
    int V; // Number of vertices
    vector<vector<iPair>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an undirected weighted edge to the graph
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({weight, v});
        adj[v].push_back({weight, u});
    }

    // Function to find and print the Minimum Spanning Tree (MST)
    void primMST() {
        // Priority queue to store vertices that are being processed by the MST.
        // It stores pairs in the format: {weight, vertex_index}
        priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

        int src = 0; // Starting with vertex 0

        // Vector to store keys (minimum edge weight to include vertex in MST)
        vector<int> key(V, INT_MAX);

        // Vector to store parent nodes to construct/print the MST
        vector<int> parent(V, -1);

        // Vector to keep track of vertices included in MST
        vector<bool> inMST(V, false);

        // Insert source vertex into priority queue and initialize its key as 0
        pq.push({0, src});
        key[src] = 0;

        int totalWeight = 0;

        while (!pq.empty()) {
            // Extract the vertex with the minimum key value
            int u = pq.top().second;
            pq.pop();

            // If the vertex is already part of the MST, skip it
            if (inMST[u]) continue;

            // Include vertex in MST
            inMST[u] = true;
            
            // Add the weight of the selected edge to the total MST weight
            if (parent[u] != -1) {
                // Find the exact edge weight that linked parent[u] to u
                for (auto& edge : adj[parent[u]]) {
                    if (edge.second == u) {
                        totalWeight += edge.first;
                        break;
                    }
                }
            }

            // Traverse all adjacent vertices of u
            for (auto& neighbor : adj[u]) {
                int weight = neighbor.first;
                int v = neighbor.second;

                // If v is not yet in MST and the edge weight u-v is smaller than current key of v
                if (!inMST[v] && key[v] > weight) {
                    // Update key of v
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        // Print the constructed MST
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << " \t";
            // Find edge weight for printing
            for (auto& edge : adj[parent[i]]) {
                if (edge.second == i) {
                    cout << edge.first << "\n";
                    break;
                }
            }
        }
        cout << "\nTotal Weight of Minimum Spanning Tree: " << totalWeight << endl;
    }
};

int main() {
    // Create a graph with 5 vertices (0 to 4)
    int V = 5;
    Graph g(V);

    // Adding weighted undirected edges
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    // Run Prim's algorithm
    g.primMST();

    return 0;
}
