#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
typedef vector<vector<pair <int,int> > > Graph;

/* Funcion que obtiene el beneficio total de una solucion p. 
*/

int visitados(vector<int> p, int (*marked)[110][110],Graph *G){
	int total=0,last=p[0];
	for(int i=1;i<p.size();i++){
		total += (-marked[last][p[i]])*(*G)[last][p[i]].value - (*G)[last][p[i]].cost;
		marked[last][p[i]] = marked[p[i]][last] = 0;
		last = p[i];
	}
	return total;
}

/* Recibe par(nodo,beneficio) y lo ordena de mayor a menor*/
bool comparador (pair <int,int> i,pair <int,int> j) {return (i.second>j.second); }


int busqueda(Graph *graph){
	// VARIABLES
	/* Globales:
	 	beneficioDisponible
		solParcial
		mejorSol
		mayorBen
	*/
	// Locales:
	vector<pair <int,int>> sucesores;						// Vector de sucesores con sus beneficios.
	int marcados[110][110];									// Aristas que ya fueron visitadas.
	int s,benefN,benef,v;											
	memset(marked,-1,sizeof(marked));						// Inicializar marcados

	// ALGORITMO
	v = solParcial.back();									// El vertice mas externo de la solucion parcial
	benef = visitados(solParcial,&marcados,&graph)			// Hallar aristas visitadas o recorridas (MEJORABLE)
	if(v == 1 && benef > mayorBen){							// Reasignar mejor solucion
		mejorSol = solParcial;
		mayorBen = benef;
	}

	for(int i=1;i<graph[v].size();i++){						// Revisar los sucesores
		s = graph[v][i];
		if ( s != -1){
			benefN = benef + marcados[s][i]*graph[s][i].value - graph[s][i].cost
			sucesores.pb(make_pair(i,benefN));
		}
	}
	sort(sucesores.begin(), sucesores.end(), comparador);	// Ordenar sucesores de mayor a menor.
	for(int i=1; i<sucesores.size(); i++){					// Recorrer desde el ultimo.
		e = sucesores[i].first(); 							// Aqui esta el nodo a verificar (Bueno, la arista)
		be = graph[v][e].value;
		ce = graph[v][e].cost;
		if(verificaciones){		 
			solParcial.pb(e);	 							// Agregar a la solucion parcial.
			beneficioDisponible -= max(0,be-ce);
			busqueda();
		}
	}
	beneficioDisponible += max(0,be-ce);
	sucesores.pop_back();

}
int bandb(Graph *G, vector<int> solInicial, int benInicial){
	// PONER ESTO COMO VARIABLES GLOBALES //
	int beneficioDisponible, mayorBen;
	vector<int> solParcial (1,1)
	vector<int> mejorSol (solInicial);
	//-----------------------------------//
	mayorBen = benInicial;
	beneficioDisponible = mayor_ben_grafo(G)		///// ??????
	busqueda(G)										///// ??????
}

