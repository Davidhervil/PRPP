#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
typedef vector<vector<pair <int,int> > > Graph;

bool esta_lado_en_sol_parcial(vector<int> sparcial, pair<int,int> e, int be){
	int marked[110][110];
	int ant;
	ant = sparcial[0];
	memset(marked,-1,sizeof(marked));

	for(int i=1;i<sparcial.size();i++){
		marked[ant][sparcial[i]] += 1;
		marked[sparcial[i]][ant] += 1;
		ant=sparcial[i];
	}
	if(marked[e.first][e.second]==-1){
		return false
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

bool cumple_acota(Graph *graph, int v, int e, int benef){
	be = (*graph)[v][e].value;
	e  = (*graph)[v][e].cost;
	beneficioE    = (*graph);
	beneficioSolP = benef + beneficioE;
	beneficioMax  = beneficioDisponible - max(0,be-ce) + beneficioSolP;
	return beneficioMax > mayorBen;
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
	int s,b1,b2,be,ce,benef,v,e;											

	// ALGORITMO
	v = solParcial.back();									// El vertice mas externo de la solucion parcial
	benef = profit(solParcial,&graph)						// Hallar beneficio actual (MEJORABLE)
	if(v == 1 && benef > mayorBen){							// Reasignar mejor solucion
		mejorSol = solParcial;
		mayorBen = benef;									
	}

	for(int i=1;i<(*graph)[v].size();i++){						// Crear lista de sucesores
		s = (*graph)[v][i].value;
		if ( s != -1){
			b1 = benef + (*graph)[v][i].value - (*graph)[v][i].cost;	// calcular beneficio nuevo
			b2 = benef - (*graph)[v][i].cost;						// Calcular beneficio nuevo
			sucesores.pb(make_pair(i,b1));						// Agregar vecinos.
			sucesores.pb(make_pair(i,b2));
		}
	}
	sort(sucesores.begin(), sucesores.end(), comparador);		// Ordenar sucesores de mayor a menor.

	for(int i=0; i<sucesores.size(); i++){					// Recorrer desde el ultimo.
		e  = sucesores[i].first(); 							// Aqui esta el nodo a verificar (Bueno, la arista)
		be = (*graph)[v][e].value;
		ce = (*graph)[v][e].cost;
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
	vector<int> solParcial (1,1);
	vector<int> mejorSol (solInicial);
	//-----------------------------------//
	mayorBen = benInicial;
	beneficioDisponible = mayor_ben_grafo(G);		///// ??????
	busqueda(G);										///// ??????
}

