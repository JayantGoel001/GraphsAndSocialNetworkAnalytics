#include <bits/stdc++.h>
using namespace std;

vector<int> apPoints;

void APUtil(vector<int> adj[], int u, bool visited[],int disc[], int low[], int& time, int parent,bool isAP[]){
	int children = 0;

	visited[u] = true;

	disc[u] = low[u] = ++time;

	for (auto v : adj[u]) {
		if (!visited[v]) {
			children++;
			APUtil(adj, v, visited, disc, low, time, u, isAP);

			low[u] = min(low[u], low[v]);

			if (parent != -1 && low[v] >= disc[u]){
				isAP[u] = true;
			}
		} else if (v != parent){
			low[u] = min(low[u], disc[v]);
		}
	}

	if (parent == -1 && children > 1){
		isAP[u] = true;
	}
}

void AP(vector<int> adj[], int V){
	
	int disc[V] = { 0 };
	int low[V];
	bool visited[V] = { false };
	bool isAP[V] = { false };
	int time = 0, par = -1;

	for (int u = 0; u < V; u++)
		if (!visited[u]){
			APUtil(adj, u, visited, disc, low,time, par, isAP);
		}

	for (int u = 0; u < V; u++){
		if (isAP[u] == true){
		    apPoints.push_back(u);
		}
    }
}
void addEdge(vector<int> adj[], int u, int v){
	adj[u].push_back(v);
	adj[v].push_back(u);
}

int main(){
    
	cout << "Articulation points in graph \n";
	int V = 6 + 1;
	vector<int> adj[V + 1];
	addEdge(adj,1, 2);
	addEdge(adj,1, 6);
	addEdge(adj,1, 4);
	addEdge(adj,1, 3);
	
	addEdge(adj,2, 3);
	addEdge(adj,2, 4);
	
	addEdge(adj,3, 6);
	AP(adj, V);
	
	if(apPoints.size() == 0){
	    cout<<"No Articulation point in Graph\n";
	}else{
	    for (auto it : apPoints) {
	        cout<<it<<"\n";
	    }
	}
}