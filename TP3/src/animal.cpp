#include "animal.h"

// ------------------------------------

Animal::Animal(string n, int i) {
	nome = n;
	idade = i;
	vet = new Veterinario("n/a", 0);
	if (i < maisJovem || maisJovem == 0) {
		maisJovem = i;
	}
}

int Animal::maisJovem = 0;

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const {
	return idade;
}

int Animal::getMaisJovem() {
	return maisJovem;
}

bool Animal::eJovem() const {
	return false;
}

string Animal::getInformacao() const {
	ostringstream oss;
	oss << nome << ", " << idade;
	return oss.str();
}

void Animal::alocarVet(Veterinario *v1) {
	vet = v1;
}

Veterinario* Animal::getVet() {
	return vet;
}

// ------------------------------------

Voador::Voador(int v_max, int a_max) {
	this->velocidade_max = v_max;
	this->altura_max = a_max;
}

int Voador::getVelocidadeMax() const {
	return this->velocidade_max;
}

int Voador::getAlturaMax() const {
	return this->altura_max;
}

// ------------------------------------

Cao::Cao(string n, int i, string rac) :
		Animal(n, i) {
	this->raca = rac;
}

bool Cao::eJovem() const {
	if (idade < 5) return true;
	else return false;
}

string Cao::getInformacao() const {
	ostringstream oss;
	oss << nome << ", " << idade << ", ";
	if (this->vet->getNome() != "n/a") {
		oss << this->vet->getInformacao() << ", ";
	}
	oss << raca;
	return oss.str();
}

// ------------------------------------

Morcego::Morcego(string n, int i, int v_max, int a_max) :
		Animal(n, i), Voador(v_max, a_max) {
}

bool Morcego::eJovem() const {
	if (idade < 4) return true;
	else return false;
}

string Morcego::getInformacao() const {
	ostringstream oss;
	oss << nome << ", " << idade << ", ";
	if (this->vet->getNome() != "n/a") {
		oss << this->vet->getInformacao() << ", ";
	}
	oss << getVelocidadeMax() << ", " << getAlturaMax();
	return oss.str();
}

