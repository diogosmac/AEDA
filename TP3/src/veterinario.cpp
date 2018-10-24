
#include "veterinario.h"

Veterinario::Veterinario(string nome, int cod) {
	this->nome = nome;
	codOrdem = cod;
}

string Veterinario::getNome() const {
	return nome;
}

string Veterinario::getInformacao() const {
	ostringstream oss;
	oss << nome << ", " << codOrdem;
	return oss.str();
}
