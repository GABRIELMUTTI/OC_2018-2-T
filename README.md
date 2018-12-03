# Trabalho de Otimização Combinatória 2018/2
## Metaheurística: GRASP
## Problema: Coloração Mais Balanceada
- Instância: Um grafo representado por uma lista de vértices e arestas, uma
lista de pesos correspondentes a cada vértice e um inteiro positivo k.
- Solução: Uma k-coloração do grafo.
- Objetivo: Minimizar o peso máximo da cor com a maior soma dos pesos das arestas.
- Informações adicionais: [Instâncias para baixar.](http://www.inf.ufrgs.br/~mrpritt/oc/cmb.zip)
- Melhores valores conhecidos:

| Instância	 |       BKV |
| -------------- | --------- |
| cmb01          |    101405 |
| cmb02          | 250083.96 |
| cmb03          | 140129.42 |
| cmb04          |  78146.84 |
| cmb05          | 786315.23 |
| cmb06          | 330082.16 |
| cmb07          |  156773.4 |
| cmb08          | 636637.88 |
| cmb09          | 221418.46 |
| cmb10          | 123671.76 |

# Como executar:
  - Compile o código com o comando "make all";
  - Execute com, por exemplo, "make run ARGS=""1000 0.85 /home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb02 /home/gabriel/Documents/ufrgs/courses/oc/trab/my_solutions/"" onde:
   - o primeiro número é o número de iterações;
   - o segundo é o valor do alpha;
   - o terceiro é o filepath da instância.
   - o quarto é onde os resultados serão salvos.