#include <bits/stdc++.h> //Esto incluye TODO ,despues hay que sacar todos los includes  que usemos

#define cost first
#define value second
#define pb push_back
#define mp make_pair
#define depo 1
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
	Graph Gr(200,connections(200,mp(-1,-1)));
	vector<vector<int> > CkR;
	vector<int> BCk;
	int nodes,edgesR,nedgesR,cost,value,v1,v2,dinR=0;
	scanf("number of vertices :  %d \n",&nodes);
	scanf("number of required edges  %d \n",&edgesR);
	for(int i=0; i<edgesR; i++){
		scanf("%d %d %d %d \n",&v1,&v2,&cost,&value);
		cout<<v1<<' '<<v2<<' '<<cost<<' '<<value<<endl;
		if(v1 == 1 || v2== 1)dinR=1;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
		Gr[v1][v2] = mp(cost,value);
		Gr[v2][v1] = mp(cost,value);
	}
	scanf("number of non required edges  %d \n",&nedgesR);
	for(int i=0; i<nedgesR; i++){
		scanf("%d %d %d %d \n",&v1,&v2,&cost,&value);
		cout<<v1<<' '<<v2<<' '<<cost<<' '<<value<<endl;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
	}
	cout<<"Leido"<<endl;
	if(dinR)//CkR[0] esta en solucion
	dfs(depo,&Gr, &CkR,nodes); //Notar que en CkR[0] estara V0
	BCk.resize(CkR.size(),0);
	cout<<"Recorrido"<<endl;
	vector<int> printed(200,0);
	int c = 0;
	for(vector<vector<int> >::iterator comp = CkR.begin();
		comp!=CkR.end(); ++comp,c++)
	{	
		cout<<"Componente "<< c << endl;
		for(int i=0;i<comp->size();i++){
			printed[(*comp)[i]]=1;
			for(int j=1; j<Gr[(*comp)[i]].size(); j++){
				if(Gr[(*comp)[i]][j].cost!=-1 && printed[j]==0 ){
					BCk[c] += Gr[(*comp)[i]][j].value - Gr[(*comp)[i]][j].cost;
					cout<<(*comp)[i]<<' '<<j<<' '<<Gr[(*comp)[i]][j].cost<<' '<<Gr[(*comp)[i]][j].value<<endl;
				}
			}
		}
		cout<<"Beneficio: "<<BCk[c]<<endl;
	}

}