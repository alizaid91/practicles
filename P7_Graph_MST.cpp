#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Structure to represent a weighted edge in the graph
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a graph
class Graph
{
private:
    int V;              // Number of vertices
    vector<Edge> edges; // Vector of all edges

public:
    Graph(int V) : V(V) {}

    void addEdge(int src, int dest, int weight)
    {
        edges.push_back({src, dest, weight});
    }

    void displayGraph()
    {
        cout << "Graph (src -> dest, weight):" << endl;
        for (const auto &edge : edges)
        {
            cout << edge.src << " -> " << edge.dest << ", weight: " << edge.weight << endl;
        }
    }

    // Kruskal's algorithm to find Minimum Spanning Tree
    void kruskalMST()
    {
        sort(edges.begin(), edges.end(), [](Edge a, Edge b)
             { return a.weight < b.weight; });

        vector<int> parent(V);
        for (int i = 0; i < V; ++i)
            parent[i] = i;

        function<int(int)> find = [&](int i)
        {
            if (parent[i] != i)
                parent[i] = find(parent[i]);
            return parent[i];
        };

        auto unionSets = [&](int x, int y)
        {
            parent[find(x)] = find(y);
        };

        cout << "Kruskal's MST:" << endl;
        int mstWeight = 0;
        for (const auto &edge : edges)
        {
            int u = find(edge.src);
            int v = find(edge.dest);
            if (u != v)
            {
                cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
                mstWeight += edge.weight;
                unionSets(u, v);
            }
        }
        cout << "Total Weight of MST: " << mstWeight << endl;
    }

    // Prim's algorithm to find Minimum Spanning Tree
    void primMST()
    {
        vector<bool> inMST(V, false);
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        key[0] = 0;

        for (int count = 0; count < V - 1; ++count)
        {
            int u = -1;
            for (int i = 0; i < V; ++i)
                if (!inMST[i] && (u == -1 || key[i] < key[u]))
                    u = i;

            inMST[u] = true;

            for (const auto &edge : edges)
            {
                if (edge.src == u || edge.dest == u)
                {
                    int v = (edge.src == u) ? edge.dest : edge.src;
                    if (!inMST[v] && edge.weight < key[v])
                    {
                        key[v] = edge.weight;
                        parent[v] = u;
                    }
                }
            }
        }

        cout << "Prim's MST:" << endl;
        int mstWeight = 0;
        for (int i = 1; i < V; ++i)
        {
            if (parent[i] != -1)
            {
                cout << parent[i] << " - " << i << " : " << key[i] << endl;
                mstWeight += key[i];
            }
        }
        cout << "Total Weight of MST: " << mstWeight << endl;
    }
};

int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph graph(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; ++i)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    graph.displayGraph();

    cout << "\n1. Kruskal's MST\n2. Prim's MST\nEnter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        graph.kruskalMST();
        break;
    case 2:
        graph.primMST();
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}