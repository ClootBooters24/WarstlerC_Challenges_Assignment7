#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int numCitiesMax = 1e5+5;
const int LOG = 20;
int depth[numCitiesMax], parent[numCitiesMax][LOG], 
    maximumDistance[numCitiesMax][LOG], 
    minimumDistance[numCitiesMax][LOG], root;
vector<pair<int, int>> graph[numCitiesMax];

void depthFirstSearch(int node, int parentNode) {
    depth[node] = depth[parentNode] + 1;
    parent[node][0] = parentNode;

    //Loop through neighbors of current node
    for(auto neighbor : graph[node]) {

        //Get neighbor and weight
        int neighborNode = neighbor.first;
        int edgeWeight = neighbor.second;

        //If neighbor is parent, skip
        if(neighborNode == parentNode) 
            continue;

        maximumDistance[neighborNode][0] = minimumDistance[neighborNode][0] = edgeWeight;
        depthFirstSearch(neighborNode, node);
    }
}

//Get parent and distance
void preprocess(int numCities) {
    for(int i = 1; i < LOG; i++) {
        for(int j = 1; j <= numCities; j++) {
            //Get parent of parent
            if(parent[j][i-1]) {
                parent[j][i] = parent[parent[j][i-1]][i-1];
            }
        }
    }
}

int lastCommonAncestor(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);

    int difference = depth[u] - depth[v];

    for(int i = LOG - 1; i >= 0; i--) {
        if((1 << i) & difference)
            u = parent[u][i];
    }

    if(u == v)
        return u;

    for(int i = LOG - 1; i >= 0; i--) {
        if(parent[u][i] && parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

//Get LCA and distance
pair<int,int> get(int u, int v) {
    int lca = lastCommonAncestor(u, v);
    return {lca, depth[u] + depth[v] - 2 * depth[lca]};
}

int main() {
    int numCities;
    cin >> numCities;

    for(int i = 1; i < numCities; i++) {
        int u, v;
        cin >> u >> v;

        //Add edge to graph
        graph[u].push_back({v, 1});
        graph[v].push_back({u, 1});
    }

    root = 1;

    depthFirstSearch(root, 0);
    preprocess(numCities);

    int numQueries;
    cin >> numQueries;

    for(int i = 0; i < numQueries; i++) {
        int u, v;
        cin >> u >> v;
        pair<int,int> result = get(u, v);
        cout << result.first << " " << result.second << endl;
    }
    return 0;
}