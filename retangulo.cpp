#include <iostream>
#include "retangulo.hpp"
#include "curvahilbert.hpp"

#include <limits>
#include <math.h>
#include <algorithm>  
#include <tuple>
#include <vector>

using namespace std;

const int MAX = numeric_limits<int>::max();

Retangulo::Retangulo() {

    x_ = MAX;
    y_ = MAX;
    largura_ = 0;
    altura_ = 0;
    dado_ = 0;

}

Retangulo::Retangulo(int x, int y, int largura, int altura, int dado) {

    x_ = x;
    y_ = y;
    largura_ = largura;
    altura_ = altura;
    dado_ = dado;

}

Retangulo::~Retangulo() {
    
    cout << "Retangulo destruida!" << endl;

}

double Retangulo::obterX() {
    return x_;
}

double Retangulo::obterY() {
    return y_;
}

double Retangulo::obterLargura() {
    return largura_;
}

double Retangulo::obterAltura() {
    return altura_;
}

int Retangulo::obterDado() {
    return dado_;
}

bool Retangulo::operator==(const Retangulo& ret) const
{
    return std::forward_as_tuple(x_, y_, largura_, altura_, dado_) == std::forward_as_tuple(ret.x_, ret.y_, ret.largura_, ret.altura_, ret.dado_);
}

bool Retangulo::operator!=(const Retangulo& ret) const 
{
    return !(*this == ret);
}

bool Retangulo::sobrepoe(Retangulo ret) { 
    
    return ((x_ < ret.x_ + ret.largura_ && x_ + largura_ > ret.x_)  && (y_ + altura_ > ret.y_ && ret.y_ + ret.altura_ > y_));

}

bool Retangulo::contem(Retangulo ret) {
    
    return ((x_ <= ret.x_ && x_ + largura_ >= ret.x_ + ret.largura_) && (y_ <= ret.y_ && y_ + altura_ >= ret.y_ + ret.altura_));

}

void Retangulo::aumentaRetangulo(Retangulo ret) {
    	
    if (x_ == MAX){
    	altura_ = ret.altura_;
	    largura_ = ret.largura_;
	    x_ = ret.x_;
	    y_ = ret.y_;
    } else {
        altura_ = max(y_ + altura_, ret.y_ + ret.altura_) - min(y_, ret.y_);
	    largura_ = max(x_ + largura_, ret.x_ + ret.largura_) - min(x_, ret.x_);
	    x_ = min(x_, ret.x_);
	    y_ = min(y_, ret.y_);
    }

}

double Retangulo::acrescimoArea(Retangulo ret) {

    if (x_ == MAX ){
        return ret.altura_ * ret.largura_;
    }
    else {
    	return (max(y_ + altura_, ret.y_ + ret.altura_) - min(y_, ret.y_)) * (max(x_ + largura_, ret.x_ + ret.largura_) - min(x_, ret.x_)) - obterArea();
    }
    
}

double Retangulo::obterArea() {

    return altura_ * largura_;

}

vector<Retangulo> Retangulo::dividirIrmaos() {
    
    int unsigned pivo = floor(filhos_.size()/2);
    Retangulo primeiroIrmao;
    Retangulo segundoIrmao;

    int coordenadaMax = -MAX;
	int coordenadaMin = MAX;
	int x, y;

    for (int unsigned i = 0; i < filhos_.size(); ++i) {
		x = ceil(filhos_[i].x_ + filhos_[i].largura_*0.5);
		y = ceil(filhos_[i].y_ + filhos_[i].altura_*0.5);
		coordenadaMax = max(coordenadaMax, max(x, y));
		coordenadaMin = min(coordenadaMin, min(x, y));
    };

	vector <Retangulo> ordenado;
    Curvahilbert ch;
    for (int unsigned j = 0; j < ordenado.size(); ++j)
	    ch.coordenadasHilbert(coordenadaMax - coordenadaMin, int(ceil(ordenado[j].x_ + ordenado[j].largura_*0.5)) - coordenadaMin, int(ceil(ordenado[j].y_ + ordenado[j].altura_*0.5)) - coordenadaMin);

    for (int unsigned k = 0; k < ordenado.size(); ++k) {
		if (k <= pivo){
    	    primeiroIrmao.inserirFilho(ordenado[k]);
        } else {
    		segundoIrmao.inserirFilho(ordenado[k]);	
    	}
    }

    vector <Retangulo> resultado;
    resultado[0] = primeiroIrmao;
    resultado[1] = segundoIrmao;

    return resultado;

}

size_t Retangulo::numeroFilhos() {

    return filhos_.size();

}

bool Retangulo::noFolha() {

	return filhos_.size() == 0;

}

bool Retangulo::temNoFolha() {
		
    return noFolha() || filhos_[0].noFolha(); //fix
	
}

Retangulo* Retangulo::inserirFilho(Retangulo ret) {
	
    filhos_.push_back(ret);
	//filhos_[filhos_.size()-1].pai_ = this;//new Retangulo(this->obterX(), this->obterY(), this->obterLargura(), this->obterAltura(), this->obterDado());
    //cout << "pai: " << filhos_[filhos_.size()-1].pai_ << endl; 
	aumentaRetangulo(ret);
    return this;

}

void Retangulo::removerFilho(Retangulo ret) {
    
    std::vector<Retangulo>::iterator itr = std::find(filhos_.begin(), filhos_.end(), ret);

	if (itr != filhos_.cend())
	    filhos_.erase(filhos_.begin() + std::distance(filhos_.begin(), itr));
	
}

vector<Retangulo> Retangulo::obterSubArvore() {
    
    vector<Retangulo> resultado;

    if (filhos_.size() == 0) {
        resultado[0] = Retangulo(x_, y_, largura_, altura_, dado_); 
	    return resultado;
	} else {
        vector<Retangulo> aux;
        for (int unsigned i = 0; i < filhos_.size(); i++) {
           aux = filhos_[i].obterSubArvore();
           resultado.insert(resultado.end(), aux.begin(), aux.end());
        }
        return resultado;
    }

}