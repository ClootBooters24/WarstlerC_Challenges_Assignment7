#include <iostream>
#include <vector>
using namespace std;

vector<int> adjList[100005];
bool visited[100005];

void depthFirstSearch(int node) {
    visited[node] = true;

    for(int i = 0; i < adjList[node].size(); i++) {
        int nextNode = adjList[node][i];

        if(!visited[nextNode]) {
            depthFirstSearch(nextNode);
        }
    }
}

int main() {
    int numTests;
    cin >> numTests;

    for(int i = 0; i < numTests; i++) {
        int numVertices, numEdges;
        cin >> numVertices >> numEdges;

        // Clear the adjacency list and visited array
        for(int j = 0; j <= numVertices; j++) {
            adjList[j].clear();
            visited[j] = false;
        }

        for(int j = 0; j < numEdges; j++) {
            int vertex1, vertex2;
            cin >> vertex1 >> vertex2;

            adjList[vertex1].push_back(vertex2);
            adjList[vertex2].push_back(vertex1);
        }

        depthFirstSearch(1);

        bool isConnected = true;

        for(int j = 1; j <= numVertices; j++) {
            if(!visited[j]) {
                isConnected = false;
                break;
            }
        }

        if(isConnected) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}