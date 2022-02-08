
/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Marcos Arenas Gómez
  Componente 2: Carlos Peña Pan
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:

	Multiconjunto() {
		num_elems = 0;
	}

	void anyadir(int elem) {

		int pos;	
		if (pertenece(elem, pos)) {	//O(log n)
			elems[pos].multiplicidad++;
		}
		else {
			//Queremos insertar elem en pos que es donde deberia de ir
			//hacer hueco desde pos hasta num_elems

			for (int i = num_elems; i >= pos; i--) {	//O(n) siendo n la distancia entre pos y num_elems
				elems[i + 1] = elems[i];
			}
			elems[pos].valor = elem;	  //O(1)
			elems[pos].multiplicidad = 1; //O(1)
			num_elems++;				  //O(1)
		}
	}

	void eliminar(int elem) {

		int pos;

		if (pertenece(elem, pos)) {

			elems[pos].multiplicidad--;
			if (elems[pos].multiplicidad <= 0) {

				//Eliminamos el elemento
				for (int i = pos; i < num_elems - 1; i++) {
					elems[i] = elems[i + 1];
				}
				num_elems--;
			}
		}
	}


	bool pertenece(int elem, int &pos) {	 

		pos = binarySearch(0, num_elems, elem);	//O(log n)
		if (elems[pos].valor == elem) return true;	//O(1)
		
		return false;

	}
	// Implementa las operaciones necesarias.
	// No olvides el coste!



private:
	struct Elem {
		int valor;
		int multiplicidad;
	};
	Elem elems[MAX_ELEMS];
	int num_elems;

	unsigned int binarySearch(int c, int f, int elem) {

		if (c == f+1) {
			return c - 1;
		}
		else {
			int m = (f - c) / 2;
			if (elems[m].valor == elem) return m;
			else if (elems[m].valor < elem) return binarySearch(m, f, elem);
			else return binarySearch(c, m, elem);
		}

	}
};


// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.

bool tratar_caso() {
	// Implementar

	int M, elemento, pos;
	Multiconjunto secuencia_secreta;
	vector<int> intentos(M);
	cin >> M;
	

	for (int i = 0; i < M; i++) {
		cin >> elemento;
		secuencia_secreta.anyadir(elemento);
	}

	for (int i = 0; i < intentos.size(); i++) {
		cin >> intentos[i];
	}

	for (int i = 0; i < intentos.size(); i++) {
		//si intentos [i] == secuencia_secreta[i] VERDE
		if (secuencia_secreta.pertenece(intentos[i], pos))
			cout << "O";
		
		else if  (!secuencia_secreta.pertenece(intentos[i], pos))
			cout <<".";
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar en Windows si la consola se cierra inmediatamente
	// system("PAUSE");
#endif
	return 0;
}
