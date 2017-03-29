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
	int s,b1,b2,benef,v;											
	memset(marked,-1,sizeof(marked));						// Inicializar marcados

	// ALGORITMO
	v = solParcial.back();									// El vertice mas externo de la solucion parcial
	benef = profit(solParcial,&graph)						// Hallar beneficio actual (MEJORABLE)
	if(v == 1 && benef > mayorBen){							// Reasignar mejor solucion
		mejorSol = solParcial;
		mayorBen = benef;									
	}

	for(int i=1;i<graph[v].size();i++){						// Crear lista de sucesores
		s = graph[v][i];
		if ( s != -1){
			b1 = benef + graph[s][i].value - graph[s][i].cost;	// calcular beneficio nuevo
			b2 = benef - graph[s][i].cost						// Calcular beneficio nuevo
			sucesores.pb(make_pair(i,b1));						// Agregar vecinos.
			sucesores.pb(make_pair(i,b2));
		}
	}
	sort(sucesores.begin(), sucesores.end(), comparador);		// Ordenar sucesores de mayor a menor.

	for(int i=1; i<sucesores.size(); i++){					// Recorrer desde el ultimo.
		e = sucesores[i].first(); 							// Aqui esta el nodo a verificar (Bueno, la arista)
		be = graph[v][e].value;
		ce = graph[v][e].cost;
		if(verificaciones){		 
			solParcial.pb(e);	 							// Agregar a la solucion parcial.
			beneficioDisponible -= max(0,be-ce);
			busqueda(G);									// ?????????????????
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

