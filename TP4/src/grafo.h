#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }



// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

// ----------------------------------------------------

template <class N, class A>
Grafo<N, A>::Grafo() {}

template <class N, class A>
Grafo<N, A>::~Grafo() {
	for (size_t i = 0; i < nos.size(); i++) {
		delete nos.at(i);
	}
}

template <class N, class A>
int Grafo<N, A>::numNos() const {
	return nos.size();
}

template <class N, class A>
int Grafo<N, A>::numArestas() const {
	int numA = 0;
	for(size_t i = 0; i < nos.size(); i++) {
		numA += nos.at(i)->arestas.size();
	}
	return numA;
}

// ----------------------------------------------------

template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &dados) {
	bool N_exist = true;
	for (size_t i = 0; i < nos.size(); i++) {
		if (dados == nos.at(i)->info)
			N_exist = false;
	}
	if (N_exist) {
		No<N, A>* NovoNo = new No<N, A>(dados);
		nos.push_back(NovoNo);
	}
	else throw NoRepetido<N>(dados);

	return *this;
}

// ----------------------------------------------------

template <class N>
class ArestaRepetida {
public:
	N info_1;
	N info_2;
	ArestaRepetida(N inf_1, N inf_2) {
		info_1 = inf_1;
		info_2 = inf_2;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar) {
	out << "Aresta repetida: " << ar.info_1 << " , " << ar.info_2;
	return out;
}


template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
	int i_inicio = -1;
	int i_fim = -1;
	for (size_t i = 0; i < nos.size(); i++) {
		if (inicio == nos.at(i)->info)
			i_inicio = i;
		if (fim == nos.at(i)->info)
			i_fim = i;
	}
	if (i_inicio == -1)
		throw NoInexistente<N>(inicio);
	if (i_fim == -1)
		throw NoInexistente<N>(fim);

	for (size_t i = 0; i < nos.at(i_inicio)->arestas.size(); i++) {
		if (nos.at(i_inicio)->arestas.at(i).destino->info == fim)
			throw ArestaRepetida<N>(inicio, fim);
	}

	Aresta<N, A> novaAresta(nos.at(i_fim), val);
	nos.at(i_inicio)->arestas.push_back(novaAresta);

	return *this;
}

// ----------------------------------------------------

template <class N>
class ArestaInexistente{
public:
	N info_1;
	N info_2;
	ArestaInexistente(N inf_1, N inf_2) {
		info_1 = inf_1;
		info_2 = inf_2;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai) {
	out << "Aresta inexistente: " << ai.info_1 << " , " << ai.info_2;
	return out;
}

template <class N, class A>
A & Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {
	int i_inicio = -1;
	int i_fim = -1;
	for (size_t i = 0; i < nos.size(); i++) {
		if (inicio == nos.at(i)->info)
			i_inicio = i;
		if (fim == nos.at(i)->info)
			i_fim = i;
	}
	if (i_inicio == -1)
		throw NoInexistente<N>(inicio);
	if (i_fim == -1)
		throw NoInexistente<N>(fim);

	for (size_t i = 0; i < nos.at(i_inicio)->arestas.size(); i++) {
		if (nos.at(i_inicio)->arestas.at(i).destino->info == fim)
			return nos.at(i_inicio)->arestas.at(i).valor;
	}

	throw ArestaInexistente<N>(inicio, fim);

}

// ----------------------------------------------------

template <class N, class A>
Grafo<N, A> & Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim) {
	int i_inicio = -1;
	int i_fim = -1;
	for (size_t i = 0; i < nos.size(); i++) {
		if (inicio == nos.at(i)->info)
			i_inicio = i;
		if (fim == nos.at(i)->info)
			i_fim = i;
	}
	if (i_inicio == -1)
		throw NoInexistente<N>(inicio);
	if (i_fim == -1)
		throw NoInexistente<N>(fim);

	for (size_t i = 0; i < nos.at(i_inicio)->arestas.size(); i++) {
		if (nos.at(i_inicio)->arestas.at(i).destino->info == fim) {
			nos.at(i_inicio)->arestas.erase(nos.at(i_inicio)->arestas.begin() + i);
			return *this;
		}
	}

	throw ArestaInexistente<N>(inicio, fim);

}

template <class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const {
	for (size_t i = 0; i < nos.size(); i++) {
		os << "( " << nos.at(i)->info;
		for (size_t j = 0; j < nos.at(i)->arestas.size(); j++) {
			os << "[ " << nos.at(i)->arestas.at(j).destino->info;
			os << " " << nos.at(i)->arestas.at(j).valor << "] ";
		}
		os << ") ";
	}
}

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g) {
	g.imprimir(out);
	return out;
}
