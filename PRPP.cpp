#include <bits/stdc++.h> //Esto incluye TODO ,despues hay que sacar todos los includes  que usemos

#define cost first
#define value second
#define pb push_back
#define mp make_pair
using namespace std;
typedef vector<pair<int,int> > connections;
typedef vector<vector<pair <int,int> > > Graph;
typedef struct edgy
{
	int v1,v2,cost,value;
}Edge;

/* 	Este dfs modifica conexComp quedando con las listas de los nodos que componen
	cada componente conexa del grafo graph.
*/
void dfs(int s,Graph *graph,vector<vector<int> > *conexComp, int nodes){
	int visited[nodes+1],done[nodes+1];
	int remain = nodes, verify = 1, comp = 0, node;
	stack<int> stack;
	cout<<"Let's roll"<<endl;

	(*conexComp).pb(vector<int> ());
	memset(done,0,sizeof(done));
	stack.push(s);
	while(remain){
		memset(visited,0,sizeof(visited));
		while(!stack.empty()){
			node = stack.top();
			stack.pop();
			if(!visited[node]){
				cout<<"Rolling"<<endl;
				(*conexComp)[comp].pb(node);
				visited[node] = 1;
				done[node] = 1;
				remain--;
				for(int i=1; i<(*graph)[node].size();i++){
					if((*graph)[node][i].cost!=-1){
						stack.push(i);
					}
				}
			}
		}
		while(verify<=nodes && done[verify]==1){
			verify++;
		}
		cout<<"Verifying"<<endl;
		if(verify<=nodes){
			stack.push(verify);
			//cout<<verify<<endl;
			(*conexComp).pb(vector<int> ());
			comp++;
		}
	}
	cout<<"Rolled"<<endl;
}
int main(){
	Graph graph(200,connections(200,mp(-1,-1)));
	vector<vector<int> > conexComp;
	int nodes,edges,cost,value,v1,v2,d;
	cin>>nodes>>edges>>d;
	for(int i=0; i<edges; i++){
		cin>>v1>>v2>>cost>>value;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
	}
	cout<<"Leido"<<endl;
	dfs(d,&graph, &conexComp,nodes); //Notar que en conexComp[0] estara V0
	cout<<"Recorrido"<<endl;
	vector<int> printed(200,0);
	int c = 0;
	for(vector<vector<int> >::iterator comp = conexComp.begin();
		comp!=conexComp.end(); ++comp,c++)
	{	
		cout<<"Componente "<< c << endl;
		for(int i=0;i<comp->size();i++){
			printed[(*comp)[i]]=1;
			for(int j=1; j<graph[(*comp)[i]].size(); j++){
				if(graph[(*comp)[i]][j].cost!=-1 && printed[j]==0 )
				cout<<(*comp)[i]<<' '<<j<<' '<<graph[(*comp)[i]][j].cost<<' '<<graph[(*comp)[i]][j].value<<endl;
			}
		}
	}

}