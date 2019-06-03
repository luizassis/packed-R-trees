#include <iostream>
#include <limits>
#include <math.h>
#include <algorithm>
#include <vector>

#include "arvorer.hpp"
#include "retangulo.hpp"
#include "curvahilbert.hpp"


using namespace std;

const double MAX = numeric_limits<double>::max();

ArvoreR::ArvoreR(size_t maxNos) { 

	maxNos_ = maxNos;
	raiz_ = new Retangulo(); 
}

ArvoreR::~ArvoreR() {

}

vector<Retangulo> ArvoreR::buscaRecursiva(Retangulo retBusca, Retangulo* no) {

	vector<Retangulo> resultado;

	if (retBusca.contem(*no) || no->noFolha()) {
		vector<Retangulo> aux = no->obterSubArvore();
		resultado.insert(resultado.end(), aux.begin(), aux.end());
		return resultado;
	} else {		
		vector<Retangulo> aux;
		for (int unsigned i = 0; i <= no->filhos_.size(); i++) {
			if (retBusca.sobrepoe(no->filhos_[0])) {
				aux = buscaRecursiva(retBusca, &(no->filhos_[i]));
				resultado.insert(resultado.end(), aux.begin(), aux.end());
			}
		}
		return resultado;
	}

}

vector<Retangulo> ArvoreR::busca(Entrada buscaFronteira) {
	
	Retangulo buscaRet = Retangulo(buscaFronteira.obterX(), buscaFronteira.obterY(), buscaFronteira.obterLargura(), buscaFronteira.obterAltura(), 0);
	
	return buscaRecursiva(buscaRet, raiz_);

}

void ArvoreR::inserir(Entrada dadoEntrada) {
	
	Retangulo ret = Retangulo(dadoEntrada.obterX(), dadoEntrada.obterY(), dadoEntrada.obterLargura(), dadoEntrada.obterAltura(), dadoEntrada.obterDado());

	Retangulo* no = raiz_;

	cout << "no folha: " << no->temNoFolha() << endl; 

	while(!no->temNoFolha()) {
		no->aumentaRetangulo(ret);
		int min = MAX;
		for (int unsigned i = 0; i < no->filhos_.size(); i++) {
			int area = ret.acrescimoArea(no->filhos_[i]);
			if (area < min) {
				no = &(no->filhos_[i]);
			}
		}
	}
				
	no->inserirFilho(ret);
	cout << "no folha - inserir: " << no->temNoFolha() << endl;
	caminhoArvoreBalanceado(ret);

}

vector<Retangulo> ArvoreR::camadaRecursivaArvore(vector<Retangulo> retLista, int nivel) {
	
	int numeroPais =  ceil((retLista.size() / maxNos_));
	vector<Retangulo> nivelNo;
	int contFilho = 0;

	for (int i = 0; i < numeroPais; i++) {
		Retangulo pai = Retangulo();
		contFilho = min(maxNos_, retLista.size());			
		for (int j = 0; j < contFilho; j++) {
			Retangulo aux = retLista.back();
			retLista.pop_back();
			pai.inserirFilho(aux);
		}
		nivelNo.push_back(pai);
	}
		
	if (numeroPais > 1) {
		return camadaRecursivaArvore(nivelNo, nivel + 1);
	} else {
		return nivelNo;
	}

}

vector<Retangulo> ArvoreR::inserirLote(vector<Entrada> entLista) {
		
	vector<Retangulo> retLista; 
	
	for (int unsigned i = 0; i <= entLista.size(); i++)
		retLista.push_back(Retangulo(entLista[i].obterX(), entLista[i].obterY(), entLista[i].obterLargura(), entLista[i].obterAltura(), entLista[i].obterDado()));	

	int coordenadaMax = -MAX;
	int coordenadaMin = MAX;
	int x, y;

	for (int unsigned j = 0; j <= retLista.size(); j++) {
		x = ceil(static_cast<double>(retLista[j].obterX() + retLista[j].obterLargura()*0.5));
		y = ceil(static_cast<double>(retLista[j].obterY() + retLista[j].obterAltura()*0.5));
		coordenadaMax = max(coordenadaMax, max(x, y));
		coordenadaMin = min(coordenadaMin, min(x, y));
	}

	vector<Retangulo> ordenado; 
	Curvahilbert ch;
	for (int unsigned k = 0; k <= retLista.size(); k++) {
		/*double idx =*/ ch.coordenadasHilbert(coordenadaMax-coordenadaMin, ceil(retLista[k].obterX() + retLista[k].obterLargura()*0.5) - coordenadaMin, ceil(retLista[k].obterY() + retLista[k].obterAltura()*0.5) - coordenadaMin);
	}
	
	vector<Retangulo> aux = camadaRecursivaArvore(ordenado, 1);

	raiz_ = &aux[0];

	return aux;

}

void ArvoreR::caminhoArvoreBalanceado(Retangulo folha) {
	
	Retangulo no = folha;
	Retangulo* ptr = no.pai_;
	
	while ((!ptr) && (ptr->numeroFilhos() > maxNos_)) {
		
		no = *ptr;

		if (no != *raiz_){
			ptr->removerFilho(no);
			vector<Retangulo> aux = no.dividirIrmaos();
			for (int unsigned i = 0; i < aux.size(); i++) {
				ptr->inserirFilho(aux[i]);
			}
		} else 
			if (no == *raiz_) {
				vector<Retangulo> aux = no.dividirIrmaos();
				for (int unsigned i = 0; i < aux.size(); i++) {
					ptr->inserirFilho(aux[i]);
				}
			}
	}
}