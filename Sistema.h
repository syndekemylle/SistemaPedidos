#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cardapio.h"
#include "Pedido.h"
#include "Excecoes.h"

using namespace std;

// Classe 8: Estoque
class Estoque {
private:
    vector<Produto*> listaDeProdutos;
public:
    ~Estoque() {
        for(int i = 0; i < listaDeProdutos.size(); i++) {
            delete listaDeProdutos[i];
        }
    }

    void cadastrarProduto(Produto* p) {
        listaDeProdutos.push_back(p);
    }

    void exibirCardapio() {
        cout << "\nCardápio" << endl;
        if(listaDeProdutos.empty()) {
            cout << "Sem produtos no momento..." << endl;
            return;
        }
        // Cataloga apenas os lanches.
        cout << "\n[ LANCHES ]" << endl;
        for (int i = 0; i < listaDeProdutos.size(); i++) {
            if (dynamic_cast<Lanche*>(listaDeProdutos[i]) != NULL) {
                cout << i << " -> " << *listaDeProdutos[i] << endl; 
            }
        }

        // Cataloga apenas os Petiscos
        cout << "\n[ PETISCOS ]" << endl;
        for (int i = 0; i < listaDeProdutos.size(); i++) {
            if (dynamic_cast<Petisco*>(listaDeProdutos[i]) != NULL) {
                cout << i << " -> " << *listaDeProdutos[i] << endl; 
            }
        }

        // Cataloga apenas as Bebidas
        cout << "\n[ BEBIDAS ]" << endl;
        for (int i = 0; i < listaDeProdutos.size(); i++) {
            if (dynamic_cast<Bebida*>(listaDeProdutos[i]) != NULL) {
                cout << i << " -> " << *listaDeProdutos[i] << endl; 
            }
        }
        cout << "\n------------------------------\n" << endl;
    }

    Produto* selecionarProduto(int indice) {
        if (indice >= 0 && indice < listaDeProdutos.size()) {
            return listaDeProdutos[indice];
        }
        throw invalid_argument("Erro: Produto nao encontrado no estoque!");
    }
};

// Classe 9: Sistema
class Sistema {
private:
    Estoque meuEstoque;
    Pedido* meuPedido;
    Usuario* userLogado;
    // Implementaçãos dos produtos disponiveis para compra.
    void inicializarDados() {
        meuEstoque.cadastrarProduto(new Lanche("Hamburguer Simples", 15.00));
        meuEstoque.cadastrarProduto(new Lanche("X-Tudo", 25.00));
        meuEstoque.cadastrarProduto(new Lanche("Lanche Kids", 10.00));
        meuEstoque.cadastrarProduto(new Lanche("Hamburger Vegano", 27.50));
        meuEstoque.cadastrarProduto(new Petisco("Batata Frita", 12.00));
        meuEstoque.cadastrarProduto(new Petisco("Macaxeira Frita", 10.00));
        meuEstoque.cadastrarProduto(new Petisco("Cubos de Frango", 18.00));
        meuEstoque.cadastrarProduto(new Bebida("Coca-Cola - Lata 350ml", 5.00, true));
        meuEstoque.cadastrarProduto(new Bebida("Guarana - Lata 350ml", 5.00, true));
        meuEstoque.cadastrarProduto(new Bebida("Agua (sem gas)", 1.50, true));
        meuEstoque.cadastrarProduto(new Bebida("Agua (com gas)", 3.00, true));
        meuEstoque.cadastrarProduto(new Bebida("Cerveja", 6.50, true));
        meuEstoque.cadastrarProduto(new Bebida("Cerveja (sem alcool)", 7.00, true));

    }

public:
    Sistema() {
        meuPedido = NULL; 
        userLogado = NULL;
        inicializarDados();
    }
    // Destrutor
    ~Sistema() {
        if(meuPedido != NULL) delete meuPedido;
        if(userLogado != NULL) delete userLogado;
    }

    void iniciarTerminal() {
        string nomeDoCliente;
        // Registrar o cliente.
        cout << "Qual seu nome pra gente anotar o pedido? ";
        getline(cin, nomeDoCliente);
        // Verificar se o usuário é um funcionário.
        char tipoUser;
        cout << "E funcionario do restaurante? (s/n): ";
        cin >> tipoUser;

        if (tipoUser == 's' || tipoUser == 'S') {
            userLogado = new Funcionario(nomeDoCliente);
            cout << "\nOla " << userLogado->getNome() << ", bom turno! (Desconto de 20% ativado)" << endl;
        } else {
            userLogado = new Cliente(nomeDoCliente);
            cout << "\nOla " << userLogado->getNome() << ", bem-vindo!" << endl;
        }

        int esc = 0;
        while (esc != 5) {
            cout << "\n [Hamburgueria++] \n [MENU PRINCIPAL] " << endl;
            cout << "1 Olhar o cardapio" << endl;
            cout << "2 Abrir comanda" << endl;
            cout << "3 Pedir" << endl;
            cout << "4 Ver Total, Pagar e Finalizar" << endl;
            cout << "5 Sair" << endl;
            cout << "=> ";
            
            cin >> esc;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Erro: Digite uma opcao valida (numero)." << endl;
                continue;
            }

            try {
                if (esc == 1) {
                    meuEstoque.exibirCardapio();
                } 
                else if (esc == 2) {
                    if (meuPedido != NULL) {
                        cout << "Erro: Voce ja tem um pedido aberto! Finalize ele primeiro." << endl;
                    } else {
                        meuPedido = new Pedido(userLogado);
                        cout << "Pedido criado com sucesso!" << endl;
                    }
                } 
                else if (esc == 3) {
                    if (meuPedido == NULL) {
                        cout << "Aviso: Abra um pedido primeiro (opcao 2)." << endl;
                    } else {
                        meuEstoque.exibirCardapio();
                        int idLanche;
                        cout << "Digite o numero do pedido: ";
                        cin >> idLanche;
                        
                        Produto* selecionado = meuEstoque.selecionarProduto(idLanche);
                        
                        Lanche* lancheCast = dynamic_cast<Lanche*>(selecionado);
                        Bebida* bebidaCast = dynamic_cast<Bebida*>(selecionado);
                        // Adicional de carne, apenas em lanches.
                        if (lancheCast != NULL) {
                            char querAdicional;
                            cout << "Deseja colocar o adicional de carne?  R$ 2.00 (s/n): ";
                            cin >> querAdicional;
                            
                            while (querAdicional == 's' || querAdicional == 'S') {
                                lancheCast->addIngrediente();
                                cout << "Adicional colocado! Quer mais um? (s/n): ";
                                cin >> querAdicional;
                            }
                        }else if (bebidaCast != NULL) {
                            // Adicional de gelo, apenas bebidas.
                            char querGelo;
                            cout << "Vai querer gelo por R$ 1.00 a mais? (s/n): ";
                            cin >> querGelo;
                            
                            if (querGelo == 's' || querGelo == 'S') {
                                bebidaCast->setGelo(true);
                            } else {
                                bebidaCast->setGelo(false);
                            }
                        }
                        
                        meuPedido->adicionarProduto(selecionado);
                        cout << "Item inserido no pedido com sucesso!" << endl;
                    }
                } 
                else if (esc == 4) {
                    if (meuPedido == NULL) {
                        cout << "Nenhum pedido pra finalizar." << endl;
                    } else {
                        // ETAPA 1: Desconto e exibição do total
                        char querDesc;
                        cout << "Deseja ver se tem direito a desconto e aplicar no pedido? (s/n): ";
                        cin >> querDesc;
                        bool aplicar = (querDesc == 's' || querDesc == 'S');
                        
                        // Isso muda o estado para FECHADO e imprime o recibo
                        meuPedido->finalizar(aplicar); 

                        // ETAPA 2: Confirmar o pagamento na mesma tela
                        char querPagar;
                        cout << "Deseja confirmar o pagamento e mandar entregar? (s/n): ";
                        cin >> querPagar;

                        if (querPagar == 's' || querPagar == 'S') {
                            meuPedido->pagarPedido();  // Muda para PAGO
                            meuPedido->enviarPedido(); // Muda para ENVIADO
                            
                            cout << "\nO entregador esta na sua rua" << endl;
                            cout << "Digite 1 e de Enter assim que o motoboy realizar a entrega: ";
                            int chegou;
                            cin >> chegou;

                            meuPedido->entregarPedido();

                            delete meuPedido;
                            meuPedido = NULL;
                            cout << "Obrigado pela preferencia! Encerrando o sistema..." << endl;
                            
                            // Força a saida do programa sem precisar voltar pro menu
                            esc = 5;
                        } else {
                            // Se nao efetuar o pagamento todo o pedido é reniciado
                            cout << "\nPagamento abortado. O pedido foi cancelado." << endl;
                            delete meuPedido;
                            meuPedido = NULL;
                        }
                    }
                } 
                else if (esc == 5) {
                    cout << "Encerrando..." << endl;
                } 
                else {
                    cout << "Opcao invalida." << endl;
                }
            } 
            catch (const EstadoPedidoException& e) {
                cout << "\n[ERRO DE NEGOCIO] " << e.what() << endl;
            } 
            catch (const invalid_argument& e) {
                cout << "\n[ERRO DE DADOS] " << e.what() << endl;
            }
        }
    }
};
