#include <bits/stdc++.h> //Esto incluye TODO ,despues hay que sacar todos los includes  que usemos

#define cost first
#define value second
#define pb push_back
#define mp make_pair
using namespace std;
void dfs(int s,vector<vector<pair <int,int> > > *graph, vector<int> *conexComp){
	vector<int> visited(200,0);
	stack<int> stack;
	stack.push(s);
	int node;
	cout<<"Let's roll"<<endl;
	while(!stack.empty()){
		node = stack.top();
		stack.pop();
		if(!visited[node]){
			cout<<"Rolling"<<endl;
			(*conexComp).pb(node);
			visited[node]=1;
			for(int i=1; i<(*graph)[node].size();i++){
				if((*graph)[node][i].cost!=-1){
					stack.push(i);
				}
			}
		}
	}

}
int main(){
	vector<vector<pair<int,int> > > graph(200,vector<pair<int,int> >(200,mp(-1,-1)));
	vector<int> conexComp;
	int nodes,edges,cost,value,v1,v2,d;
	cin>>nodes>>edges>>d;
	for(int i=0; i<edges; i++){
		cin>>v1>>v2>>cost>>value;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
	}
	cout<<"Leido"<<endl;
	dfs(d,&graph, &conexComp);
	cout<<"Recorrido"<<endl;
	vector<int> printed(200,0);
	for(int i=0; i<conexComp.size(); i++){
		printed[conexComp[i]]=1;
		for(int j=1; j<graph[conexComp[i]].size(); j++){
			if(graph[conexComp[i]][j].cost!=-1 && printed[j]==0 )
			cout<<conexComp[i]<<' '<<j<<' '<<graph[conexComp[i]][j].cost<<' '<<graph[conexComp[i]][j].value<<endl;
		}
	}

}