# Exame-CES11-Algoritmos-e-Estrutura-de-Dados
#Descrição sobre o problema abordado:

A técnica denominada PERT – Program Evaluation and Review Tecnique – Técnica de
Avaliação e Revisão de Projetos – é um tópico da Engenharia de Produção que se utiliza
de grafos para planejar e visualizar a coordenação das tarefas de um projeto.
Cada tarefa é um nó de um grafo orientado. A existência de uma aresta A→B indica que
a tarefa A deve ser finalizada antes de se iniciar a tarefa B. Para cada tarefa associa-se a
sua duração estimada.
Se não houver dependência A→...→B nem dependência B→...→A, então as atividades
A e B podem ser executadas simultaneamente, pois nossa empresa já contratou suficiente
pessoal qualificado. 
Elabore um programa para receber como entrada uma lista das tarefas, com suas durações
e os seus pré-requisitos, e então calcular:
(a) o tempo mínimo para que o projeto seja executado;
(b) quais tarefas não podem sofrer qualquer aumento no tempo de execução para que
esse tempo mínimo não aumente.
A seqüência formada pelas tarefas do item (b) é chamada caminho crítico. Sua
determinação é parte da mundialmente famosa técnica CPM – Critical Path Method.
Esclarecendo: o programa realizará as quatro tarefas seguintes.
- Verificar se o grafo é acíclico.
- Obter ordenação topológica.
- Calcular o tempo mínimo.
- Mostrar o caminho crítico.
  
Entrada:
Número máximo de tarefas: 52.
Descrição das tarefas: até 30 caracteres.
As tarefas são rotuladas com uma única letra, maiúscula ou minúscula.
As letras na entrada podem estar em qualquer ordem.
O ponto indica que a tarefa não tem pré-requisito.
Pode haver zero, uma ou várias tarefas sem pré-requisito.
