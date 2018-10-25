#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia += 1;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

// ---------------------------------------------------------------------

bool InfoCartao::operator == (const InfoCartao &ic1) const {
	return (this->nome == ic1.nome);
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao info;
	info.nome = nome;
	return sequentialSearch(clientes, info);
}

// ---------------------------------------------------------------------

string InfoCartao::getNome() const {
	return nome;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const {
	int client_index = posicaoCliente(nome);
	if (client_index == -1) {
		throw ClienteNaoExistente(nome);
	}
	return clientes[client_index].frequencia;
}

// ---------------------------------------------------------------------

bool InfoCartao::operator < (const InfoCartao &ic1) const {
	if (this->frequencia < ic1.frequencia)
		return false;
	else if (this->frequencia == ic1.frequencia)
		return (this->nome < ic1.nome);
	else return true;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

// ---------------------------------------------------------------------

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	vector<InfoCartao> clientes_intervalo;
	for (size_t i = 0; i < clientes.size(); i++) {
		if ((clientes.at(i).frequencia >= n1) && (clientes.at(i).frequencia <= n2))
			clientes_intervalo.push_back(clientes.at(i));
	}
	insertionSort(clientes_intervalo);
	vector<string> nomes_clientes;
	for (size_t i = 0; i < clientes_intervalo.size(); i++) {
		nomes_clientes.push_back(clientes_intervalo.at(i).getNome());
	}
	return nomes_clientes;
}

// ---------------------------------------------------------------------

void ParqueEstacionamento::ordenaClientesPorNome() {
	for (size_t i = 1; i < clientes.size(); i++) {
		InfoCartao tmp = clientes.at(i);
		size_t j;
		for (j = i; j > 0 && tmp.getNome() < clientes.at(j-1).getNome(); j--) {
			clientes.at(j) = clientes.at(j-1);
		}
		clientes.at(j) = tmp;
	}
}

// ---------------------------------------------------------------------

std::ostream & operator << (ostream &os, const ParqueEstacionamento &pe) {
	os << '\n';
	for (size_t i = 0; i < pe.clientes.size(); i++) {
		InfoCartao ic = pe.clientes.at(i);
		os << ic.nome << " - ";
		if (ic.presente) os << "Presente";
		else os << "Ausente";
		os << " - Usou o parque " << ic.frequencia << " vez";
		if (ic.frequencia != 1) os << "es";
		os << ".\n";
	}
	os << '\n';
	return os;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const {
	size_t max = clientes.size();
	if (p >= max) {
		throw PosicaoNaoExistente(p);
	}

	return clientes.at(p);
}
