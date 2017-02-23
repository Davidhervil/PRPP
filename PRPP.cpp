#include <bits/stdc++.h> //Esto incluye TODO ,despues hay que sacar todos los includes  que usemos

#define cost first
#define value second
#define pb push_back
#define mp make_pair
#define depo 1
#define COST [0]
#define VALUE [1]
#define INF 10000000
using namespace std;
typedef vector<pair<int,int> > connections;
typedef vector<vector<pair <int,int> > > Graph;
typedef struct edgy
{
	int v1,v2,cost,value;
}Edge;

class mycomparison
{
public:
  mycomparison()
    {}
  bool operator() (const pair<int,int>&v1, pair<int,int>&v2) const
  { //par(vertice,distancia)
    return (v1.second < v2.second);
  }
};

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

void dijkstra(int s, Graph *graph, vector<vector<int> > *CkR, vector<int> *camino){
	priority_queue<pair<int,int>,vector<pair<int,int> >,mycomparison> q;
}

void bestCompCost(int d, Graph *graph, vector<vector<int> > *CkR, vector<int> *camino){

}
void floydWarshall(int nodes,int (*gf)[110][110][2], int (*cR)[110][110], int (*cP)[110][110], Graph *g){
	for(int i = 1;i<nodes;i++){
		for(int j=1; j<nodes;i++){
			if(j==i){
				(*cR)[j][j] = 0;
			}
			else{
				if((*g)[i][j].cost!=-1){
					(*cR)[i][j] = (*cR)[j][i] = (*g)[i][j].cost;
				}
			}
		}
	}
}
int main(){
	Graph graph(110,connections(110,mp(-1,-1)));
	Graph Gr(110,connections(110,mp(-1,-1)));
	int graphFloyd[110][110][2],bene4Floyd[110][110],costPaths[110][110];
	int costResult[110][110],beneResult[110][110],benePaths[110][110];
	vector<vector<int> > CkR;
	vector<int> BCk,camino;
	int nodes,edgesR,nedgesR,cost,value,v1,v2,dinR=0;
	int bestCompDijk,bestCompB;
	for(int i=0;i<110;i++){

		memset(graphFloyd[i],0,sizeof(graphFloyd[i]));
		memset(costPaths[i],-1,sizeof(costPaths[i]));
		memset(benePaths[i],-1,sizeof(benePaths[i]));
	}
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
		graphFloyd[v1][v2]COST = cost; graphFloyd[v1][v2]VALUE = value;
		graphFloyd[v2][v1]COST = cost; graphFloyd[v2][v1]VALUE = value;
		bene4Floyd[v1][v2] = bene4Floyd[v2][v1] = cost - value;
	}
	scanf("number of non required edges  %d \n",&nedgesR);
	for(int i=0; i<nedgesR; i++){
		scanf("%d %d %d %d \n",&v1,&v2,&cost,&value);
		cout<<v1<<' '<<v2<<' '<<cost<<' '<<value<<endl;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
		graphFloyd[v1][v2]COST = cost; graphFloyd[v1][v2]VALUE = value;
		graphFloyd[v2][v1]COST = cost; graphFloyd[v2][v1]VALUE = value;
		bene4Floyd[v1][v2] = bene4Floyd[v2][v1] = cost - value;
	}
	cout<<"Leido"<<endl;
	floydWarshall(nodes,&graphFloyd,&costResult,&costPaths, &graph);
	if(dinR)//CkR[0] esta en solucion
	dfs(depo,&Gr, &CkR,nodes); //Notar que en CkR[0] estara V0 (Componente con el deposito)
	else{
		bestCompCost(depo, &graph, &CkR, &camino);
	}
	BCk.resize(CkR.size(),0);
	cout<<"Recorrido"<<endl;
	vector<int> printed(110,0);
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