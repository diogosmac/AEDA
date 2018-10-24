
#ifndef SRC_VETERINARIO_H_
#define SRC_VETERINARIO_H_

#include <string>
#include <sstream>
using namespace std;

class Veterinario {
	string nome;
	long codOrdem;
public:
	Veterinario(string nome, int cod);
	string getNome() const;
	string getInformacao() const;
	//completar
};



#endif /* SRC_VETERINARIO_H_ */