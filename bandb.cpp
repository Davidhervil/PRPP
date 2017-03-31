#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
typedef vector<vector<pair <int,int> > > Graph;

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

bool ciclo_negativo(vector<int> solpar, int e, Graph *G){
	int marked[110][110];
	int n=solpar.size(),revenue=0,ant;
	memset(marked,-1,sizeof(marked));
	ant = solpar[n-1];
	revenue += (*G)[e][solpar[n-1]].value-(*G)[e][solpar[n-1]].cost;
	for(int i=n-2;i>=0;i--){
		revenue+= (-marked[ant][solpar[i]])*(*G)[ant][solpar[i]].value-(*G)[ant][solpar[i]].cost;
		marked[ant][solpar[i]] = 0;
		marked[solpar[i]][ant] = 0;
		if (solpar[i]==e){
			if(revenue<0)return true;
		}
		ant = solpar[i];
	}
	return false;
}

bool cumple_acota(Graph *graph, int v, int e,int be, int ce, int benef){
	int beneficioE, beneficioSolP, beneficioMax;
	beneficioE    = be-ce;
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
		e  = sucesores[i].first; 							// Aqui esta el nodo a verificar (Bueno, la arista)
		be = sucesores[i].second;
		ce = (*graph)[v][e].cost;
		if(!cumple_acota(graph,v,e,be,ce,benef) &&
			!esta_lado_en_sol_parcial(make_pair(v,e),be)) {		 
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
	cout<<mayorBen<<endl;
	for(int i=0;i<solParcial.size();i++)cout<<solParcial[i]<<' ';
		cout<<endl;
}


