#ifndef __ArvoreR_HPP__
#define __ArvoreR_HPP__

// incluir dependencias
#include "retangulo.hpp"
#include "entrada.hpp"
#include <vector>

class ArvoreR
{
    public:

        Retangulo* raiz_;

        std::size_t maxNos_;

        ArvoreR(std::size_t maxNos);
        
        ~ArvoreR();

        std::vector<Retangulo> busca(Entrada buscaFronteira);

        void inserir(Entrada pontoDado);

        std::vector<Retangulo> inserirLote(std::vector<Entrada> entLista);

    private:

        std::vector<Retangulo> buscaRecursiva(Retangulo retBusca, Retangulo* no);

        std::vector<Retangulo> camadaRecursivaArvore(std::vector<Retangulo> retLista, int nivel);

        void caminhoArvoreBalanceado(Retangulo folha);

};

#endif // __ArvoreR__