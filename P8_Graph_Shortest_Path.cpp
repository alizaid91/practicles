#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph
{
private:
    int V;                         // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix to store distances

public:
    Graph(int V) : V(V)
    {
        adjMatrix.resize(V, vector<int>(V, INT_MAX));
        for (int i = 0; i < V; ++i)
            adjMatrix[i][i] = 0; // Distance to itself is 0
    }

    void addEdge(int src, int dest, int weight)
    {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight; // Assuming undirected graph
    }

    void displayGraph()
    {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (adjMatrix[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void dijkstra(int src)
    {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        dist[src] = 0;

        for (int count = 0; count < V - 1; ++count)
        {
            int u = -1;
            for (int i = 0; i < V; ++i)
                if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                    u = i;

            visited[u] = true;

            for (int v = 0; v < V; ++v)
            {
                if (!visited[v] && adjMatrix[u][v] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        cout << "Shortest distances from source " << src << ":" << endl;
        for (int i = 0; i < V; ++i)
        {
            if (dist[i] == INT_MAX)
                cout << "INF ";
            else
                cout << "Vertex " << i << " : " << dist[i] << endl;
        }
    }
};

int main()
{
    int V, E;
    cout << "Enter the number of vertices (landmarks): ";
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

    int src;
    cout << "\nEnter the source vertex for Dijkstra's algorithm: ";
    cin >> src;
    graph.dijkstra(src);

    return 0;
}