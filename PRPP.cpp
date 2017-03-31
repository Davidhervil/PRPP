#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
#include <algorithm>

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
int beneficioDisponible, mayorBen,countBusq;
vector<int> solParcial (1,1);
vector<int> mejorSol;

/* 	Este dfs modifica conexComp quedando con las listas de los nodos que componen
	cada componente conexa del grafo graph. Inicialmente era considerada 
	para formar parte de la heuristica
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
	//cout<<"Rolled"<<endl;
}
/* Esta funcion retorna 1 si el camino *prev es un ciclo
*/
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

/* 	Procedimiento inspirado en el algoritmo de Bellman-Ford, que retorna
	una lista con los beneficios hacia todos los nodos desde el deposito.
	en prev, se guarda indirectamente los caminos hacia estos nodos
*/
vector<int> bellman(int nodes,int s, Graph *graph, vector<int> *prev){
	int valid[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[s] = 0;
	//cout<<"Empezando Bell"<<endl;
	memset(valid,-1,sizeof(valid));
	for (int node = 1; node <= nodes-1; node++)
	{
		for(int i=s; i<=nodes;i++){
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
		for(int i=1; i<s;i++){
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
/* 	Procedimiento inspirado en el algoritmo de Bellman-Ford, que retorna
	una lista con los beneficios hacia todos los nodos desde el deposito.
	en prev, se guarda indirectamente los caminos hacia estos nodos.
	Esta es una sobrecarga del procedimeinto anterior. Se utiliza en el algoritmos
	que intenta mejorar la solucion
*/
vector<int> bellman(int nodes,int s, Graph *graph, vector<int> *prev, int (*inpaths)[110][110]){
	int valid[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[s] = 0;
	//cout<<"Empezando Bell"<<endl;
	memset(valid,-1,sizeof(valid));
	for (int node = 1; node <= nodes-1; node++)
	{
		for(int i=s; i<=nodes;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost;
						valid[i][j] = valid[j][i] = 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}
			} 
		}
		for(int i=1; i<s;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost;
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
/* 	Dado un camino parcial indirecto guardado en *p, marca las aristas en la 
	tabla *inroad que se encuentren en este.
*/
void mark(int from, vector<int> *p,int (*inroad)[110][110] ){
	int i = from,cycle=0;
	while((*p)[i]!=-1){
		//cout<<i<<' ';
		if((*p)[i]!=-1)
		(*inroad)[i][(*p)[i]] = (*inroad)[(*p)[i]][i] = 0; 
		i = (*p)[i];
	}
}
/* 	Modificacion del procedimiento 'bellman' antes mencionado. Dado un camino parcial de ida
	retorna una lista con los beneficios resultantes de regresar al deposito para cada nodo.
	En *prev se guarda indirectamente ese camino de regreso.
*/
vector<int> regreso(int nodes,int from, Graph *graph, vector<int> *ida,vector<int> *prev){
	int valid[110][110],inroad[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[from] = 0;
	//cout<<"Empezando Regreso"<<endl;
	memset(inroad,-1,sizeof(inroad));
	mark(from,ida,&inroad);
	memset(valid,-1,sizeof(valid));
	for (int node = 1; node <= nodes-1; node++)
	{
		 for(int i=from; i<=nodes;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-1)*inroad[i][j]*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-1)*inroad[i][j]*(*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = inroad[i][j] = inroad[j][i]= 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			}
		}
		for(int i=1; i<from;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-1)*inroad[i][j]*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-1)*inroad[i][j]*(*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = inroad[i][j] = inroad[j][i]= 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			}
		}
	}
	//for(int i=1;i<=nodes;i++)cout<<distances[i]<<' ';
	//	cout<<endl;
	return distances;
}
/* 	Modificacion del procedimiento 'bellman' antes mencionado. Dado un camino parcial de ida
	retorna una lista con los beneficios resultantes de regresar al deposito para cada nodo.
	En *prev se guarda indirectamente ese camino de regreso.
	Esta es una sobre carga del procedimiento anterior que se usa en la mejora de soluciones.
*/
vector<int> regreso(int nodes,int from, Graph *graph, vector<int> *ida,vector<int> *prev, int (*inpaths)[110][110]){
	int valid[110][110],inroad[110][110],hold;
	vector<int> distances(nodes+1,-INF);
	distances[from] = 0;
	//cout<<"Empezando Regreso"<<endl;
	memset(inroad,-1,sizeof(inroad));
	mark(from,ida,&inroad);
	memset(valid,-1,sizeof(valid));
	for (int node = 1; node <= nodes-1; node++)
	{
		 for(int i=from; i<=nodes;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-1)*inroad[i][j]*(-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-1)*inroad[i][j]*(-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = inroad[i][j] = inroad[j][i]= 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			}
		}
		for(int i=1; i<from;i++){
			for (int j = 1; j <=nodes; j++)
			{	
			 	if((*graph)[i][j].cost!=-1 && valid[i][j]!=0 &&
			 		distances[j] < distances[i] + (-1)*inroad[i][j]*(-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost){	
					hold = (*prev)[j];
					(*prev)[j] = i;
					if(!infinite(prev,i)){
						distances[j] = distances[i] + (-1)*inroad[i][j]*(-(*inpaths)[i][j])*(*graph)[i][j].value-(*graph)[i][j].cost;
						//cout<<"i "<<i<<' '<<distances[i]<<endl;
						//cout<<"j "<<j<<' '<<distances[j]<<endl;
						valid[i][j] = valid[j][i] = inroad[i][j] = inroad[j][i]= 0;
						(*prev)[j] = i;
					}else{
						(*prev)[j] = hold;
					}
				}

			}
		}
	}
	//for(int i=1;i<=nodes;i++)cout<<distances[i]<<' ';
	//	cout<<endl;
	return distances;
}

/* 	Este procedimiento reconstruye en una lista de nodos 
	el ciclo resultante de los dos caminos parciales de ida y vuelta desde node
*/
vector<int> constructPath(vector<int> venida,vector<int> ida,int node){
	vector<int> path;
	int i = node;
	//cout<<"Armando ciclo"<<endl;
	path.pb(i);
	i=venida[i];
	while(i!=-1){
		path.pb(i);
		i = venida[i];
	}
	i=path.back();
	i=ida[i];
	while(i!=-1){
		path.pb(i);
		i = ida[i];
	}
	return path;
}
/* 	Procedimiento de mejora de soluciones. El objetivo es usar cada nodo de la
	solucion propuesta como un deposito virtual y reaplicar el algoritmo general 
	de busqueda de solucion a manera de	buscar posibles caminos obviados en la
	primera corrida.
*/
vector<vector<int> > mejorar(int nodes,Graph *graph, vector<int> *ida,vector<int> *venida,int bst){	
	int inpaths[110][110], improved[110],node, best,max;
	vector<vector<int> > additions(110);
	vector<int> prevs(110,-1),backprevs(110,-1),bellResult,backResult;
	vector<int> bestbackpath;
	memset(improved,0,sizeof(improved));
	memset(inpaths,-1,sizeof(improved));
	mark(bst,ida,&inpaths);
	mark(depo,venida,&inpaths);
	node = bst;
	while((*ida)[node]!=-1){
		if(!improved[node])
			fill(backprevs.begin(),backprevs.end(),-1);
			fill(prevs.begin(),prevs.end(),-1);
			bellResult = vector<int> (); 
			backResult = vector<int> ();
			bellResult = bellman(nodes,node,graph, &prevs,&inpaths);
			backResult = regreso(nodes,node,graph,&prevs,&backprevs,&inpaths);
			max = bellResult[node] + backResult[node];
			best = node;
			bestbackpath = backprevs;
			for (int i = 1; i <= nodes; ++i){	
				if(i!=node){
					fill(backprevs.begin(),backprevs.end(),-1);
					backResult = regreso(nodes,i,graph,&prevs,&backprevs,&inpaths);
					if(max<bellResult[i]+backResult[1]){
						max=bellResult[i]+backResult[1];
						best = i;
						bestbackpath = backprevs;
					}
				}
			}
			if(max>0){
				additions[node] = constructPath(bestbackpath,prevs,node);
				improved[node] = 1;
				mark(best,&prevs,&inpaths);
				mark(node,&backprevs,&inpaths);
			}
		node = (*ida)[node];
	}
	node = depo;
	while((*venida)[node]!=-1){
		if(!improved[node])
			fill(backprevs.begin(),backprevs.end(),-1);
			fill(prevs.begin(),prevs.end(),-1);
			bellResult=bellman(nodes,node,graph, &prevs,&inpaths);
			backResult = regreso(nodes,node,graph,&prevs,&backprevs,&inpaths);
			max = bellResult[node] + backResult[node];
			best = node;
			bestbackpath = backprevs;
			for (int i = 1; i <= nodes; ++i){	
				if(i!=node){
					fill(backprevs.begin(),backprevs.end(),-1);
					backResult = regreso(nodes,i,graph,&prevs,&backprevs,&inpaths);
					if(max<bellResult[i]+backResult[1]){
						max=bellResult[i]+backResult[1];
						best = i;
						bestbackpath = backprevs;
					}
				}
			}
			if(max>0){
				additions[node] = constructPath(bestbackpath,prevs,node);
				improved[node] = 1;
				mark(best,&prevs,&inpaths);
				mark(node,&backprevs,&inpaths);
			}
		node = (*venida)[node];
	}
	return additions;
}
/* Procedimiento auxiliar para debugging
*/
void leprint (int nodes,int (*cR)[110][110]){
	for(int i = 1;i<=nodes;i++){
		for(int j=1; j<=nodes;j++){
			cout<<(*cR)[i][j]<<' ';
		}
		cout<<endl;
	}
}
/* Procedimiento que imprime en pantalla un camino parcial.
*/
void printpath(vector<int> prv, int max){
	int i = max;
	while(prv[i]!=-1){
		cout<<i<<' ';
		i = prv[i];
	}
	cout<<i<<endl;
}
/* 	Procedimiento que anhade las posibles mejoras  encontradas
	a la solucion proveida
*/
vector<int> add(vector<int> *path,vector<vector<int> > *mejoras){
	vector<int> final;
	for(int i=0;i<(*path).size();i++){
		final.pb((*path)[i]);
		if((*mejoras)[(*path)[i]].size()!=0){
			for(int j = 1; j<(*mejoras)[(*path)[i]].size();j++)
				if(final.back()!=(*mejoras)[(*path)[i]][j])		
				final.pb((*mejoras)[(*path)[i]][j]);
		}
	}
	return final;
}

vector<int> elim_ciclos_neg(vector<int> path,Graph *G){//INCOMPLETO
	int marked[110][110],total=0,last=p[0],n=path.size();
	int node,cyclecost=0,ant;
	for(int i=0;i<n;i++){
		node = path[i];
		ant=node;
		cyclecost=0;
		
		for(int j=i+1;j<n;j++){
			
		}
	}
	return path;
}

/* Funcion que obtiene el beneficio total de una solucion p. 
*/
int profit(vector<int> p,Graph *G){
	int marked[110][110],total=0,last=p[0];
	memset(marked,-1,sizeof(marked));
	for(int i=1;i<p.size();i++){
		total += (-marked[last][p[i]])*(*G)[last][p[i]].value - (*G)[last][p[i]].cost;
		marked[last][p[i]] = marked[p[i]][last] = 0;
		last = p[i];
	}
	return total;
}

/* Procedimiento principal
*/


bool esta_lado_en_sol_parcial(pair<int,int> e, int be){
	int marked[110][110];
	int ant;
	ant = solParcial[0];
	memset(marked,-1,sizeof(marked));
	for(int i=1;i<solParcial.size();i++){
		marked[ant][solParcial[i]] += 1;
		marked[solParcial[i]][ant] += 1;
		ant=solParcial[i];
	}
	if(marked[e.first][e.second]==-1){
		return false;
	}
	else if(marked[e.first][e.second]==0){
		if(be == 0){
			return false;
		}else{
			return true;
		}
	}
	return true;
}

bool no_repite_ciclo(int e, Graph *G){
	int n=solpar.size(),ant;
	memset(marked,-1,sizeof(marked));
	ant = solpar[n-1];
	for(int i=n-2;i>=0;i--){
		if(solpar[i]){	
			if ((*G)[e][solpar[n-1]].value-(*G)[e][solpar[n-1]].cost < (*G)[ant][solpar[i]].value-(*G)[ant][solpar[i]].cost){
				return false
			}else{
				return true;
			}
		}
		ant = solpar[i];
	}
	return false;
}

bool cumple_acota(Graph *graph, int v, int e,int be, int ce, int benef){
	int beneficioE, beneficioSolP, beneficioMax;
	bool b;
	beneficioE    = be-ce;					// Ganancia de recorrer la arista
	beneficioSolP = benef + beneficioE;		// 
	beneficioMax  = beneficioDisponible - max(0,beneficioE) + beneficioSolP;
	b = beneficioMax> mayorBen;
	return b;
}

bool ciclo_negativo(int e, Graph *G){
	int marked[110][110];
	int n=solParcial.size(),revenue=0,ant;
	memset(marked,-1,sizeof(marked));
	ant = solParcial[n-1];
	revenue += (*G)[e][solParcial[n-1]].value-(*G)[e][solParcial[n-1]].cost;
	for(int i=n-2;i>=0;i--){
		revenue+= (-marked[ant][solParcial[i]])*(*G)[ant][solParcial[i]].value-(*G)[ant][solParcial[i]].cost;
		marked[ant][solParcial[i]] = 0;
		marked[solParcial[i]][ant] = 0;
		if (solParcial[i]==e){
			if(revenue<0)return true;
		}
		ant = solParcial[i];
	}
	return false;
}

/* Recibe par(nodo,beneficio) y lo ordena de mayor a menor*/
bool comparador (pair <int,int> i,pair <int,int> j) {return (i.value>j.value); }

int busqueda(Graph *graph){
	// VARIABLES
	/* Globales:
	 	beneficioDisponible
		solParcial
		mejorSol
		mayorBen
	*/
	// Locales:
	vector<pair <int,int> > sucesores;						// Vector de sucesores con sus beneficios.
	int s,b1,b2,be,ce,benef,v,e, ultimo, penultimo;							

	for(int i=0;i<solParcial.size();i++)cout<<solParcial[i]<<' ';
	cout<<endl<<"mayor: "<<mayorBen<<"   "<<endl;
	cout<<endl<<"Disponible: "<<beneficioDisponible<<"   "<<endl;
	// ALGORITMO
	v = solParcial.back();					// El vertice mas externo de la solucion parcial
	if(v == 1 && benef > mayorBen){			// Si llegamos al deposito.			
		benef = profit(solParcial,graph);	// Hallar beneficio actual (MEJORABLE)
		if (benef > mayorBen){				// Reasignar mejor solucion
			mejorSol = solParcial;			// Guardar mejor camino.
			mayorBen = benef;				// Hallar beneficio actual (MEJORABLE)
		}							
	}
	for(int i=1;i<(*graph)[v].size();i++){	// Crear lista de sucesores
		s = (*graph)[v][i].value; 			// 
		if ( s != -1){
			b1 = (*graph)[v][i].value - (*graph)[v][i].cost;	// calcular beneficio nuevo
			b2 = (*graph)[v][i].cost;							// Calcular beneficio nuevo
			sucesores.pb(make_pair(i,b1));								// Agregar vecinos.
			sucesores.pb(make_pair(i,b2));
		}
	}

	sort(sucesores.begin(), sucesores.end(), comparador);	// Ordenar sucesores de mayor a menor.
	for(int i=0; i<sucesores.size(); i++){					// Recorrer desde el ultimo.
		e  = sucesores[i].first; 							// Aqui esta el nodo a verificar (Bueno, la arista)
		be = sucesores[i].second;
		ce = (*graph)[v][e].cost;
		if(cumple_acota(graph,v,e,be,ce,benef) &&
			!esta_lado_en_sol_parcial(make_pair(v,e),be)&&!ciclo_negativo(e,graph)) {		 
			solParcial.pb(e);	 							// Agregar a la solucion parcial.
			beneficioDisponible -= max(0,be-ce);
			busqueda(graph);	
			beneficioDisponible += max(0,be-ce);								// ?????????????????
		}
	}
	if (solParcial.size()!=0){
		countBusq -= 1;
		ultimo = solParcial.back();
		solParcial.pop_back();
	}
}

int mayor_ben_grafo(Graph *graph){
	int r=0;
	for(int i=0;i<(*graph)[0].size();i++){
		for(int j=0;j<(*graph)[0].size();j++){
			r += (max(0,(*graph)[i][j].value - (*graph)[i][j].cost ))/2;
		}
	}
	return r;
}
int bandb(Graph *G, vector<int> *solInicial, int benInicial){
	mejorSol = (*solInicial);
	mayorBen = benInicial;
	beneficioDisponible = mayor_ben_grafo(G);		///// ??????
	busqueda(G);										///// ??????
		cout<<"chao busqueda"<<endl;
	cout<<mayorBen<<endl;
	for(int i=0;i<mejorSol.size();i++)cout<<mejorSol[i]<<' ';
		cout<<endl;
}


int main(){
	int graphFloyd[110][110][2],bene4Floyd[110][110],costPaths[110][110];
	int costResult[110][110],beneResult[110][110],benePaths[110][110];
	Graph graph(110,connections(110,mp(-1,-1)));
	Graph Gr(110,connections(110,mp(-1,-1)));
	vector<vector<int> > CkR,improvements;
	vector<int> BCk,prevs(110,-1),bellResult,backResult,backprevs(110,-1);
	vector<int> bestbackpath,path,final;
	int nodes,edgesR,nedgesR,cost,value,v1,v2,dinR=0;
	int bestCompDijk,bestCompB,max,best,ganancia;
	for(int i=0;i<110;i++){
		memset(costPaths[i],-1,sizeof(costPaths[i]));
		memset(benePaths[i],-1,sizeof(benePaths[i]));
	}
	scanf("number of vertices :  %d \n",&nodes);
	scanf("number of required edges  %d \n",&edgesR);
	for(int i=0; i<edgesR; i++){
		scanf("%d %d %d %d \n",&v1,&v2,&cost,&value);
		if(v1 == 1 || v2== 1)dinR=1;
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
		Gr[v1][v2] = mp(cost,value);
		Gr[v2][v1] = mp(cost,value);
	}

	scanf("number of non required edges  %d \n",&nedgesR);
	for(int i=0; i<nedgesR; i++){
		scanf("%d %d %d %d \n",&v1,&v2,&cost,&value);
		graph[v1][v2] = mp(cost,value);
		graph[v2][v1] = mp(cost,value);
	}
	bellResult 	 = bellman(nodes,depo,&graph, &prevs);
	backResult 	 = regreso(nodes,depo,&graph,&prevs,&backprevs);
	bestbackpath = backprevs;
	max  = bellResult[depo] + backResult[depo];
	best = depo;

	for (int i = 2; i <= nodes; i++)
	{	
		fill(backprevs.begin(),backprevs.end(),-1);
		backResult = regreso(nodes,i,&graph,&prevs,&backprevs);
		if(max<bellResult[i]+backResult[1]){
			max=bellResult[i]+backResult[1];
			best = i;
			bestbackpath = backprevs;
		}
	}

	path = constructPath(bestbackpath,prevs,depo);
	improvements = mejorar(nodes,&graph,&prevs,&backprevs,best);
	final = add(&path,&improvements);

	// dar resultados
	ganancia = profit(final,&graph);
	//for(int i=0;i<path.size();i++)cout<<path[i]<<' ';
	if(ganancia>max){
		//return ganancia;
		cout<<ganancia<<endl;
		for(int i=0;i<final.size();i++)cout<<final[i]<<' ';
			cout<<endl;

		bandb(&graph,&final,ganancia);
	}else{
		//return max;
		cout<<max<<endl;
		for(int i=0;i<path.size();i++)cout<<path[i]<<' ';
		cout<<endl;
		bandb(&graph,&path,max);
	}
	//for(int i=0;i<graph[0].size();i++)cout<<graph[10][i].second<<' ';
}
