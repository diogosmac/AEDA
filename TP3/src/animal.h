#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
#include <sstream>
using namespace std;

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	string getNome() const;
	int getIdade() const;
	static int getMaisJovem();
	virtual bool eJovem() const;
	virtual string getInformacao() const;
	void alocarVet(Veterinario *v1);
	Veterinario* getVet();
	//completar
};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem() const;
	string getInformacao() const;
	//completar
};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	int getVelocidadeMax() const;
	int getAlturaMax() const;
	virtual ~Voador(){};
	//completar
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem() const;
	string getInformacao() const;
	//completar
};


#endif /* SRC_ANIMAL_H_ */
