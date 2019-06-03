#ifndef __Retangulo_HPP__
#define __Retangulo_HPP__

#include <vector>

const unsigned int N = 100000;

class Retangulo
{
    public:

        Retangulo();
        
        Retangulo(int x, int y, int largura, int altura, int dado);
        
        ~Retangulo();

        std::vector<Retangulo> filhos_;

        Retangulo* pai_;

        bool operator==(const Retangulo &ret) const;

        bool operator!=(const Retangulo& ret) const;

        bool sobrepoe(Retangulo ret);

        bool contem(Retangulo ret);

        void aumentaRetangulo(Retangulo ret);

        double acrescimoArea(Retangulo ret);

        double obterArea();

        double obterX();

        double obterY();

        double obterLargura();

        double obterAltura();

        int obterDado();

        std::vector<Retangulo> dividirIrmaos();
        
        std::size_t numeroFilhos();

        bool noFolha();

        bool temNoFolha();

        Retangulo* inserirFilho(Retangulo ret);

        void removerFilho(Retangulo ret);

        std::vector<Retangulo> obterSubArvore();

    private:

        int x_;

        int y_;

        int largura_;

        int altura_;

        int dado_;

};

#endif // __Retangulo_HPP__