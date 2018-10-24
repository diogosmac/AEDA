#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento (unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli){
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
	int index = -1;
	for (unsigned i = 0; i < clientes.size(); i++){
		if (clientes[i].nome == nome){
			index = i;
			break;
		}
	}
	return index;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
	if ((posicaoCliente(nome) == -1) && (clientes.size() < numMaximoClientes)){
		InfoCartao novoCliente;
		novoCliente.nome = nome;
		novoCliente.presente = false;
		clientes.push_back(novoCliente);
		return true;
	}

	return false;
}

bool ParqueEstacionamento::entrar(const string & nome) {
	int index = posicaoCliente(nome);
	if ((index == -1) || (clientes[index].presente == true) || (vagas == 0))
		return false;
	clientes[index].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
	int index = posicaoCliente(nome);
	if ((index == -1) || (clientes[index].presente == true))
		return false;
	clientes.erase(clientes.begin() + index);
	return true;
}

bool ParqueEstacionamento::sair(const string & nome) {
	int index = posicaoCliente(nome);
	if (index == -1)
		return false;
	else if (clientes[index].presente == false)
			return false;
	clientes[index].presente = false;
	vagas++;
	return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}
