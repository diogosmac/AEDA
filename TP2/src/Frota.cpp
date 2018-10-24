#include "Frota.h"
#include <string>
#include <iostream>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1){
	veiculos.push_back(v1);
}

int Frota::numVeiculos() const{
	return veiculos.size();
}

int Frota::menorAno() const{
	if (veiculos.size() == 0) return 0;

	vector<Veiculo *>::const_iterator it = veiculos.begin();
	int menAno = (*it)->getAno();
	it++;
	while (it != veiculos.end()) {
		int ano = (*it)->getAno();
		if (ano < menAno)
			menAno = ano;
		it++;
	}
	return menAno;
}

ostream & operator<<(ostream & o, const Frota & f) {
	for (vector<Veiculo *>::const_iterator it = f.veiculos.begin(); it != f.veiculos.end(); it++) {
		int inf = (*it)->info();
		o << inf << " ";
	}
	return o;
}

vector<Veiculo *> Frota::operator () (int anoM) const{
	vector<Veiculo *> vec;
	for (vector<Veiculo *>::const_iterator it = this->veiculos.begin(); it != this->veiculos.end(); it++) {
		int ano = (*it)->getAno();
		if (anoM == ano){
			vec.push_back((*it));
		}
	}
	return vec;
}

float Frota::totalImposto() const{
	float total;
	for (vector<Veiculo *>::const_iterator it = veiculos.begin(); it != veiculos.end(); it++) {
		float imp = (*it)->calcImposto();
		total += imp;
	}
	return total;
}
