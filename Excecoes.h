#pragma once
#include <stdexcept>
#include <string>

using namespace std;

// A classe EstadoPedidoException herda da biblioteca padrão runtime_error (herança na pratica!)
// e serve pra gente disparar nossas proprias exceções customizadas sempre que alguem 
// tentar pular as regras de negocio e os estados do pedido (tipo tentar pagar sem fechar).
// Ass. Guilherme Arboés

class EstadoPedidoException : public runtime_error {
public:
    EstadoPedidoException(const string& msg) : runtime_error(msg) {}
};
