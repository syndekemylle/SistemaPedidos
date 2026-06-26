#pragma once
#include <iostream>
#include <string>

using namespace std;

//Aqui implementei a estrutura do sistema: o polimorfismo cuida das diferenças entre usuários e produtos, as regras
//de negócio garantem as validações de pedido e limites de itens,
//e a classe de pedido faz a integração de tudo isso calculando
//o valor final com base nessas regras. Ass. Noronha :P

// Polimorfismo 1: Usuario e tipos de usuario
class Usuario {
protected:
    string nome;
public:
    Usuario(string n) { nome = n; }
    virtual ~Usuario() {}
    virtual double obterDesconto(double valor) = 0;
    string getNome() { return nome; }
};

class Cliente : public Usuario {
public:
    Cliente(string n) : Usuario(n) {}
    double obterDesconto(double valor) override {
        // Regra 1: Desconto só acima de 50
        if (valor > 50.0) return valor * 0.05;
        return 0.0;
    }
};

class Funcionario : public Usuario {
public:
    Funcionario(string n) : Usuario(n) {}
    double obterDesconto(double valor) override {
        // Regra 2: Desconto fixo de 20%
        return valor * 0.20;
    }
};

// Polimorfismo 2: Produto e tipos de produto
class Produto {
protected:
    string nome;
    double preco;
    bool disponivel;
public:
    Produto(string n, double p) { nome = n; preco = p; disponivel = true; }
    virtual ~Produto() {}
    virtual double calcularTotal() = 0;
    string getNome() { return nome; }
    bool isDisponivel() { return disponivel; }

    // Sobrecarga do operador << 
    friend ostream& operator<<(ostream& os, Produto& p) {
        os << p.getNome() << " - R$ " << p.calcularTotal();
        return os;
    }
};

class Lanche : public Produto {
private:
    int adicionais;
public:
    Lanche(string n, double p) : Produto(n, p) { adicionais = 0; }
    void addIngrediente() {
        // Regra 3: Maximo de 3 extras
        if (adicionais < 3) adicionais++;
    }
    double calcularTotal() override { return preco + (adicionais * 2.0); }
};

class Bebida : public Produto {
private:
    bool comGelo;
public:
    Bebida(string n, double p, bool gelo) : Produto(n, p) { comGelo = gelo; }
    
    void setGelo(bool gelo) { comGelo = gelo; }

    double calcularTotal() override {
        // Regra 4: Gelo custa extra
        if (comGelo) return preco + 1.0;
        return preco;
    }
};
