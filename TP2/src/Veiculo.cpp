#include "Veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a){
	this->marca = mc;
	this->mes = m;
	this->ano = a;
}

int Veiculo::getAno() const{
	return ano;
}

int Veiculo::getMes() const{
	return mes;
}

string Veiculo::getMarca() const{
	return marca;
}

int Veiculo::info() const{
	return 3;
}

bool Veiculo::operator <(const Veiculo & v) const{
	if (this->getAno() < v.getAno()) return true;
	else if (this->getAno() > v.getAno()) return false;
	else if (this->getMes() < v.getMes()) return true;
	else return false;
}

float Veiculo::calcImposto() const{
	return 0;
}

// --------------------------------------


Motorizado::Motorizado(string mc, int m, int a, string c, int cil) :
		Veiculo(mc, m, a){
	this->combustivel = c;
	this->cilindrada = cil;
}

string Motorizado::getCombustivel() const{
	return combustivel;
}

int Motorizado::info() const{
	return 5;
}

float Motorizado::calcImposto() const{
	if (combustivel == "gasolina"){
		if (getAno() > 1995) {
			if (cilindrada <= 1000) return 14.56;
			else if (cilindrada <= 1300) return 29.06;
			else if (cilindrada <= 1750) return 45.15;
			else if (cilindrada <= 2600) return 113.98;
			else if (cilindrada <= 3500) return 181.17;
			else return 320.89;
		}
		else {
			if (cilindrada <= 1000) return 8.10;
			else if (cilindrada <= 1300) return 14.56;
			else if (cilindrada <= 1750) return 22.65;
			else if (cilindrada <= 2600) return 54.89;
			else if (cilindrada <= 3500) return 87.13;
			else return 148.37;
		}
	}
	else {
		if (getAno() > 1995) {
			if (cilindrada <= 1500) return 14.56;
			else if (cilindrada <= 2000) return 29.06;
			else if (cilindrada <= 3000) return 45.15;
			else return 113.98;
		}
		else {
			if (cilindrada <= 1500) return 8.10;
			else if (cilindrada <= 2000) return 14.56;
			else if (cilindrada <= 3000) return 22.65;
			else return 54.89;
		}
	}
}

// --------------------------------------

Automovel::Automovel(string mc, int m, int a, string c, int cil) :
		Motorizado(mc, m, a, c, cil){}

int Automovel::info() const{
	return 5;
}

// --------------------------------------

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm) :
		Motorizado(mc, m, a, c, cil){
	carga_maxima = cm;
}

int Camiao::info() const{
	return 6;
}

// --------------------------------------

Bicicleta::Bicicleta(string mc, int m, int a, string t) :
		Veiculo(mc, m, a){
	tipo = t;
}

int Bicicleta::info() const{
	return 4;
}

float Bicicleta::calcImposto() const{
	return 0;
}
