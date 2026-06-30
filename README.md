# Sistema de Pedidos - "Hamburgueria++"

Um sistema interativo de terminal em C++ que simula o uso completo de um aplicativo de delivery de comida. 

Este projeto foi desenvolvido colaborativamente como avaliação da Unidade 03 para a disciplina de Linguagem de Programação I (LP-I)  do curso de Tecnologia da Informação (UFRN). O objetivo principal é demonstrar a aplicação prática de conceitos de POO, modelagem de classes e implementação de regras de negócio estritas.

## O que esperar do projeto (Funcionalidades)

O sistema roda em uma interface de texto e suporta interação direta com o usuário, permitindo o gerenciamento de um fluxo de compras. As principais características:

* Polimorfismo na Prática: O sistema diferencia o usuário logado entre `Cliente` ou `Funcionario`. Dependendo de quem está comprando, o cálculo de desconto é aplicado de forma completamente diferente por debaixo dos panos. O mesmo vale para os produtos (`Lanche`, `Bebida`, `Petisco`).
* Regras de Negócio e Estados Dinâmicos: A classe `Pedido` possui diferentes estados (`CRIADO` -> `FECHADO` -> `PAGO` -> `ENVIADO` -> `ENTREGUE`). O sistema impede ações inválidas, como tentar pagar um pedido que ainda está aberto ou entregar algo que não foi pago.
* Tratamento de Exceções: Uso de classes de exceção personalizadas (como `EstadoPedidoException`) para capturar violações das regras de negócio e evitar que o programa feche abruptamente se o usuário digitar informações inválidas.
* Interatividade Dinâmica: Sobrecarga de operadores para exibir o cardápio de forma limpa e uso de `dynamic_cast` para oferecer opções específicas baseadas no tipo de produto (ex: perguntar sobre ingredientes adicionais apenas para lanches e gelo apenas para bebidas).

## Pré-requisitos

Para conseguir rodar o projeto na sua máquina, você vai precisar ter instalado:
* Um compilador C++ (recomendado o `g++`).
* O utilitário `make` para interpretar as rotinas de compilação.
* Um ambiente de terminal (Linux, macOS ou WSL no Windows).

## Como compilar e executar

O projeto conta com um arquivo `Makefile` configurado para automatizar todo o processo.

1. Abra o seu terminal.
2. Navegue até o diretório raiz onde os arquivos `.cpp` e `.h` foram extraídos.
3. Para compilar o código fonte e gerar o executável, digite o comando:
   make
4. Se a compilação for bem-sucedida será criado um executavel, inicie a aplicação digitando:
    ./sistema_pedidos
5. Para limpar os arquivos binários gerados pela compilação anterior, utilize o comando:
    make clean
