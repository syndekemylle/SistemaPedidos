#pragma once
#include <iostream>
#include <vector>
#include "Cardapio.h"
#include "Excecoes.h"

using namespace std;
//Possiveis estados do pedido.
enum StatusPedido {
  CRIADO,
  FECHADO,
  PAGO,
  ENVIADO,
  ENTREGUE,
  CANCELADO
};

// A classe Pedido gerencia os itens do carrinho e impede que o fluxo 
// seja burlado. Usamos as exceções personalizadas para garantir que 
// uma transição de estado só aconteça na ordem cronológica correta 
// (ex: não dá pra enviar um pedido que não foi pago).
// Ass. Guilherme Arboés

// Interação e Regras de Estado
class Pedido {
private:
    Usuario* cliente;
    vector<Produto*> itens;
    StatusPedido status;
public:
    Pedido(Usuario* c) { cliente = c; status = CRIADO; }

    void adicionarProduto(Produto* p) {
        // Regra 5: Nao altera pedido fechado (Com excecao adicionada)
        if (status != CRIADO) throw EstadoPedidoException("Erro: Nao altera pedido fechado");
        // Regra 5: Nao adiciona se indisponivel (Com excecao adicionada)
        if (!p->isDisponivel()) throw invalid_argument("Erro: Produto indisponivel");
        itens.push_back(p);
    }

    // Atualizado para receber a escolha do desconto
    void finalizar(bool aplicarDesconto) {
        if (itens.empty() || status != CRIADO) throw EstadoPedidoException("Erro: Nao e possivel finalizar pedido vazio ou ja fechado.");
        status = FECHADO;

        double total = 0;
        for (int i = 0; i < itens.size(); i++) {
            total += itens[i]->calcularTotal();
        }

        double valorDesconto = 0;
        if (aplicarDesconto) {
            valorDesconto = cliente->obterDesconto(total);
        }
        double valorFinal = total - valorDesconto;

        cout << "\n RESUMO DO PEDIDO " << endl;
        cout << "Subtotal: R$ " << total << endl;
        if (aplicarDesconto) {
            cout << "Desconto aplicado: R$ " << valorDesconto << endl;
        } else {
            cout << "Desconto aplicado: R$ 0.00" << endl;
        }
        cout << "Total a Pagar: R$ " << valorFinal << endl;
        cout << "------------------------\n" << endl;
        cout << "Pedido fechado!" << endl;
    }
    // Regras de bloqueio de estados nas funções abaixo
    void pagarPedido() {
        // Verificar e lancar exceção
        if (status != FECHADO) throw EstadoPedidoException("Erro: O pedido so pode ser pago se estiver FECHADO.");
        status = PAGO;
        cout << "Pagamento confirmado!" << endl;
    }

    void enviarPedido() {
        // Verificar e lancar exceção
        if (status != PAGO) throw EstadoPedidoException("Erro: O pedido precisa estar PAGO para ser enviado.");
        status = ENVIADO;
        cout << "Pedido saiu para entrega!" << endl;
    }

    void entregarPedido() {
        //Verificar e lancar exceção
        if (status != ENVIADO) throw EstadoPedidoException("Erro: O pedido precisa estar ENVIADO para ser entregue.");
        status = ENTREGUE;
        cout << "\n=> PEDIDO ENTREGUE! Bom apetite!" << endl;
    }
};
