#include<bits/stdc++.h>
#define NIL -1
using namespace std;

class Graph{
	int V; 
	list<int> *adj;
	vector<pair<int,int>> bridges;
    public:
	Graph(int V){
    	this->V = V + 1;
    	this->adj = new list<int>[V + 1];
    }
    
    void addEdge(int v, int w){
    	adj[v].push_back(w);
    	adj[w].push_back(v);
    }
    
    void bridgeUtil(int u, bool visited[], int disc[],int low[], int parent[]){
    	static int time = 0;
    
    	visited[u] = true;
    	low[u] = ++time;
    	disc[u] = low[u];
    
    	for (auto v : adj[u]){
    
    		if (!visited[v]){
    			parent[v] = u;
    			bridgeUtil(v, visited, disc, low, parent);
    
    			low[u] = min(low[u], low[v]);
    
    			if (low[v] > disc[u]){
    			    bridges.push_back({u,v});
    			}
    		} else if (v != parent[u]){
    			low[u] = min(low[u], disc[v]);
    		}
    	}
    }
    
    vector<pair<int,int>> bridge(){
    	
    	bool *visited = new bool[V];
    	int *disc = new int[V];
    	int *low = new int[V];
    	int *parent = new int[V];
    
    	for (int i = 0; i < V; i++){
    		parent[i] = NIL;
    		visited[i] = false;
    	}
    	for (int i = 0; i < V; i++){
    		if (visited[i] == false){
    			bridgeUtil(i, visited, disc, low, parent);
    		}
    	}
    	return bridges;
    }

};



int main(){
	
	cout << "\nBridges in graph \n";
	Graph g(6);
	g.addEdge(1, 2);
	g.addEdge(1, 6);
	g.addEdge(1, 4);
	g.addEdge(1, 3);
	
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	
	g.addEdge(3, 6);
	
	vector<pair<int,int>> bridges = g.bridge();
	if(bridges.size() == 0){
	    cout<<"No bridge in Graph\n";
	}else{
	    for (auto it : bridges) {
	        cout<<it.first<<" "<<it.second<<"\n";
	    }
	}

	return 0;
}
