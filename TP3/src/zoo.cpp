#include "zoo.h"

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal (Animal *a1) {
	this->animais.push_back(a1);
}

void Zoo::adicionaVeterinario (Veterinario *v1) {
	this->veterinarios.push_back(v1);
}

string Zoo::getInformacao() const {
	string s;
	for (unsigned i = 0; i < this->animais.size(); i++) {
		s += this->animais[i]->getInformacao();
		s += ";\n";
	}
	return s;
}

bool Zoo::animalJovem(string nomeA) {
	for (unsigned i = 0; i < this->animais.size(); i++) {
		if (this->animais[i]->getNome() == nomeA)
			return this->animais[i]->eJovem();
	}
	return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
	while(!isV.eof()) {
		string nome;
		int cod;
		getline(isV, nome);
		isV >> cod;
		isV.ignore(100, '\n');
		Veterinario *v1 = new Veterinario(nome, cod);
		adicionaVeterinario(v1);
	}
	for (unsigned i_vet = 0, i_an = 0; i_an < this->animais.size(); i_an++, i_vet++) {
		if (i_vet == this->veterinarios.size())
			i_vet = 0;
		this->animais[i_an]->alocarVet(this->veterinarios[i_vet]);
	}
}

bool Zoo::removeVeterinario (string nomeV) {
	for (unsigned i = 0; i < veterinarios.size(); i++) {
		if (veterinarios.at(i)->getNome() == nomeV) {
			for (unsigned j = 0; j < animais.size(); j++) {
				if (animais.at(j)->getVet() == veterinarios.at(i)) {
					if (i+1 != veterinarios.size()) {
						animais.at(j)->alocarVet(veterinarios.at(i+1));
					}
					else if (veterinarios.size() == 1){
						animais.at(j)->alocarVet(0);
					}
					else animais.at(j)->alocarVet(veterinarios.at(0));
				}
			}
		veterinarios.erase(veterinarios.begin() + i);
		return true;
		}
	}
	return false;
}

bool Zoo::operator < (Zoo& zoo2) const {
	int sum1 = 0, sum2 = 0;
	for (unsigned i = 0; i < this->animais.size(); i++) {
		sum1 += this->animais.at(i)->getIdade();
	}
	for (unsigned j = 0; j < zoo2.animais.size(); j++) {
		sum2 += zoo2.animais.at(j)->getIdade();
	}
	return (sum1 < sum2);
}
