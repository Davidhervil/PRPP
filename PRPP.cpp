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
{  Graph *G;
public:
  mycomparison(Graph *g)
    {G = g; }
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
	//cout<<"Let's roll"<<endl;

	(*conexComp).pb(vector<int> ());
	memset(done,0,sizeof(done));
	stack.push(s);
	while(remain){
		memset(visited,0,sizeof(visited));
		while(!stack.empty()){
			node = stack.top();
			stack.pop();
			if(!visited[node]){
				//cout<<"Rolling"<<endl;
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
		//cout<<"Verifying"<<endl;
		if(verify<=nodes){
			stack.push(verify);
			//cout<<verify<<endl;
			(*conexComp).pb(vector<int> ());
			comp++;
		}
	}
	cout<<"Rolled"<<endl;
}
int infinite( vector<int> *prev,int from){
	int i = from,cycle=0;
	while((*prev)[i]!=-1){
		//cout<<i<<' ';
		i = (*prev)[i];
		if(i==from){
			cycle=1;
			break;
		}
	}
	return cycle;
	//cout<<i<<endl;
}
vector<int> bellman(int nodes,int s, Graph *graph, vector<int> *prev){
	int valid[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[s] = 0;
	cout<<"Empezando Bell"<<endl;
	memset(valid,-1,sizeof(valid));
	for (int node = 1; node <= nodes-1; node++)
	{
		 for(int i=1; i<=nodes;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			 } 
		}
	}
	return distances;
}

void regreso(int nodes,int from, Graph *graph, vector<int> *prevs){
	int valid[110][110],inroad[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[from] = 0;
	cout<<"Empezando Bell"<<endl;
	memset(valid,-1,sizeof(valid));
	memset(inroad,0,sizeof(inroad));
	for (int node = 1; node <= nodes-1; node++)
	{
		 for(int i=1; i<=nodes;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			 } 
		}
	}
}
void fldWrshllC(int nodes,int (*gf)[110][110][2], int (*cR)[110][110], int (*cP)[110][110], Graph *g){
	cout<<"Empezando"<<endl;
	for(int i = 1;i<=nodes;i++){
		for(int j= 1; j<=nodes;j++){
			(*cP)[i][j] = -1;
			if(j==i){
				(*cR)[j][j] = 0;
			}
			else{
				if((*g)[i][j].cost!=-1){
					(*cR)[i][j] = (*cR)[j][i] = (*g)[i][j].cost;
					(*cP)[i][j] = j;
				}else{
					(*cR)[i][j] = INF;
				}
			}
		}
	}
	cout<<"Floydeando"<<endl;
	for (int k = 1; k <= nodes; k++)
	{	
		for (int i = 1; i <= nodes; i++)
		{
			for (int j = 1; j <= nodes; j++)
			{
				if((*cR)[i][j]>(*cR)[i][k]+(*cR)[k][j]){
					(*cR)[i][j] = (*cR)[i][k]+(*cR)[k][j];
					(*cP)[i][j] = (*cP)[i][k];
				}
			}
		}
	}
}
void leprint (int nodes,int (*cR)[110][110]){
	for(int i = 1;i<=nodes;i++){
		for(int j=1; j<=nodes;j++){
			cout<<(*cR)[i][j]<<' ';
		}
		cout<<endl;
	}
}
int findmax(vector<int> v){
	int max=v[0],holis;
	for(int i=0;i<v.size();i++){
		if(v[i]>=max){
			max=v[i];
			holis=i;
			}
	}
	return holis;
}
void printpath(vector<int> prv, int max){
	int i = max;
	while(prv[i]!=-1){
		cout<<i<<' ';
		i = prv[i];
	}
	cout<<i<<endl;
}
int main(){
	Graph graph(110,connections(110,mp(-1,-1)));
	Graph Gr(110,connections(110,mp(-1,-1)));
	int graphFloyd[110][110][2],bene4Floyd[110][110],costPaths[110][110];
	int costResult[110][110],beneResult[110][110],benePaths[110][110];
	vector<vector<int> > CkR;
	vector<int> BCk,prevs(110,-1),bellResult;
	int nodes,edgesR,nedgesR,cost,value,v1,v2,dinR=0;
	int bestCompDijk,bestCompB,max;
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
	fldWrshllC(nodes,&graphFloyd,&costResult,&costPaths,&graph);
	cout<<"fldWrshllC Listo"<<endl;
	leprint(nodes,&costResult);
	cout<<"Vamos con Bell"<<endl;
	bellResult=bellman(nodes,depo,&graph, &prevs);
	for(int i=1;i<=nodes;i++)cout<<bellResult[i]<<' ';
		cout<<endl;
	max = findmax(bellResult);
	printpath(prevs,max);
	if(dinR)//CkR[0] esta en solucion
	dfs(depo,&Gr, &CkR,nodes); //Notar que en CkR[0] estara V0 (Componente con el deposito)
	else{
		bestCompCost(depo, &graph, &CkR, &prevs);
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