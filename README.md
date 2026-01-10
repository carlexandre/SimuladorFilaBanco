# Trabalho Final da disciplina de Programação
### Apresentação

Este trabalho foi desenvolvido pelos alunos **Carlos Alexandre Batista** e **Caio Emanuel Lima**, e serve integralmente como nota de trabalho final para a disciplina **CK0226 - Programação**, na **Universidade Federal do Ceará, Brasil**, cujo docente é o **Prof. Dr. Miguel Franklin de Castro**.

---

## Objetivo do Projeto
O objetivo do trabalho é desenvolver um projeto em linguagem C representando um sistema de simulação de fila de banco. Todas as especificações foram passadas via PDF na ferramenta Google Sala de Aula, e podem ser conferidas abaixo:

## Especificações do Sistema

O **Banco da Cochinchina do Sul** está precisando de um sistema para organizar as filas de atendimento aos seus caixas. Em cada dia de serviço, `M` caixas estão operacionais, onde `M ≥ 1`.

### Classes de Clientes
Existem 5 classes de clientes que utilizam os serviços desses bancos, cada uma identificada por um número:

1. Cliente Premium
2. Cliente Ouro
3. Cliente Prata
4. Cliente Bronze
5. Cliente Leezu

O banco quer garantir um tratamento diferenciado aos seus clientes mais importantes, que estão listados acima em ordem decrescente de “importância”. Como consequência, há 5 filas distintas, dependendo da classe de cliente.

### Dados do Cliente
Cada cliente que chega ao banco é caracterizado pelo:
* **Número de sua conta** (valor inteiro ÚNICO);
* **Classe da sua conta** (valor inteiro no intervalo [1;5], conforme definido acima);
* **Quantidade** (valor inteiro) de operações financeiras que ele deseja efetuar no caixa.

### Lógica de Atendimento
A disciplina de atendimento em cada fila individual por classe de conta é o **primeiro a chegar é o primeiro a sair**.

Entre as diferentes filas, há um **ESCALONADOR** que segue o seguinte procedimento para cada rodada de atendimento:

* **Passo 1.** Atender `N1` cliente(s) Premium, se houver;
* **Passo 2.** Em seguida, atender `N2` cliente(s) Ouro, se houver;
* **Passo 3.** Em seguida, atender `N3` cliente(s) Prata, se houver;
* **Passo 4.** Em seguida, atender `N4` cliente(s) Bronze, se houver;
* **Passo 5.** Em seguida, atender `N5` cliente(s) Leezu, se houver, e ir para o primeiro passo da próxima rodada.

Ao conjunto `{N1; N2; N3; N4; N5}`, denominamos **“Disciplina de Atendimento”**.

### Funcionamento e Timers
Imagine que há, na frente de todas as filas, um painel que chama o próximo cliente, indicando o número de conta do correntista a ser atendido, logo que um caixa está disponível, seguindo-se a Disciplina de Atendimento escolhida. Caso haja mais de um caixa disponível em um determinado momento, um cliente será atribuído ao caixa de menor número disponível.

Para determinar o status de cada caixa, o programa deve ter um timer para cada caixa, que cada vez que um cliente que vai fazer `K` operações financeiras segue para ser atendido, o timer é definido para chamar outro cliente dentro de `K × ∆T` min., onde `∆T` é o tempo necessário para o caixa processar cada operação financeira. Considere que o valor de `∆T` é fixo e dado como parâmetro.
