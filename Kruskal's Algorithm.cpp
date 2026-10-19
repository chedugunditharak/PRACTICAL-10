#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
    
    // Comparator operator to sort edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) / Union-Find Data Structure
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, every node is its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the ultimate representative/parent of a node (with path compression)
    int findParent(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node]); // Path compression
    }

    // Connect two nodes together (with Union by Rank)
    bool unionSets(int u, int v) {
        int rootU = findParent(u);
        int rootV = findParent(v);

        // If they have the same ultimate parent, they are already in the same set (a cycle forms)
        if (rootU == rootV) 
            return false;

        // Union by rank optimization
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

void kruskalsMST(int V, vector<Edge>& edges) {
    // Step 1: Sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end());

    DisjointSet dsu(V);
    vector<Edge> mst;
    int mstWeight = 0;

    // Step 2: Iterate through the sorted edges
    for (const auto& edge : edges) {
        // If the nodes belong to different components, pick the edge
        if (dsu.unionSets(edge.src, edge.dest)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
        }

        // Optimization: An MST always contains exactly V - 1 edges
        if (mst.size() == V - 1) 
            break;
    }

    // Print the resulting MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << "\n";
    }
    cout << "Total Weight of Minimum Spanning Tree: " << mstWeight << endl;
    cout << "Enrollment No:92460118181";
}

int main() {
    int V = 6; // Total number of vertices (0 to 5)
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3},
        {2, 5, 2}, {2, 4, 4}, {3, 4, 3}, {5, 4, 3}
    };

    kruskalsMST(V, edges);

    return 0;
}
