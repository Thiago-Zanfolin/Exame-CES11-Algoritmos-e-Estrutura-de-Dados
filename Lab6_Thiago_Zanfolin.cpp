// Thiago Jos� Belini Zanfolin
// Turma 4
// Laborat�rio 6: Caminho Cr�tico
// Programa compilado com Code Blocks 20.03

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 53
int Matriz_De_Adjacencias[MAX][MAX];
//declarando como global n�o preciso ficar passando ela como argumento de fun��o, mas uso do 1 ao n
typedef struct noh_grafo
{
    char Tarefa;
    char descricao[31];
    int duracao_semanas;
    char Tarefas_Precedentes[104];//seu tamanho � 2*52-1+1=104, pois h� no m�ximo 52 tarefas alteradas com virgula mais o barra 0
    int descoberto;//se esse inteiro foi 1, implica que est� descoberto
    int finalizado;
    int tmt;
    char marcador;
} noh_grafo;
typedef struct pilha
{
    int topo; //ja serve como quantidade tamb�m
    noh_grafo *vet;//guardar as tarefas, come�a do 1
} pilha;
typedef struct Grafo
{
    noh_grafo vetor_noh_grafo[MAX];
    int quant_nohs_grafo;
    int tem_ciclo;
    pilha *p;
} Grafo;

void Inicializar(Grafo *G)
{
    G->p->vet=(noh_grafo*)malloc((MAX)*sizeof(noh_grafo));
    G->p->topo=0;//inicialmente pilha vazia
    G->quant_nohs_grafo=0;
    G->tem_ciclo=0;//inicialmente, n�o h� a principio ciclo no grafo
}
void Inserir_Na_Pilha(Grafo *G,int i)
{
    if(G->p->topo<MAX)//empilha somente se tiver espa�o
    {
        //como � pilha,basta acrescenta-lo no topo
        G->p->topo++;
        G->p->vet[G->p->topo]=G->vetor_noh_grafo[i];
    }
}
void Printar_Ciclo(Grafo *G,FILE *saida)
{
    int i,j;
    int flag=0;
    int k=1;
    fprintf(saida,"%c ", G->p->vet[G->p->topo]);
    for(i=1; i<=G->p->topo && flag!=1; i++)
    {
        for(j=1; j<=G->quant_nohs_grafo && flag!=1; j++)
        {
            if(G->vetor_noh_grafo[j].Tarefa==G->p->vet[i].Tarefa)
            {
                if(Matriz_De_Adjacencias[G->p->topo][j]!=1)//essa l�gica deve ser feita pois os �ndices s�o salvados com respeito ao vetor, n�o a pilha
                    k++;//uma forma de remover
                if(Matriz_De_Adjacencias[G->p->topo][j]==1)//achou o primeiro que aponta, isto �, o come�o do ciclo
                    flag=1;
            }
        }
    }
    for(k;k<=G->p->topo;k++)
      fprintf(saida,"%c ",G->p->vet[k]);//printando o ciclo na ordem correta
    G->p->topo=0;//esvazeia todos os elementos da pilha de uma vez s�
}
void Desempilhar_Da_Pilha(Grafo *G)
{
    if(G->p->topo==0)
        return;
    G->p->topo--;//n�o tem que fazer shift nem nada, pois eu retiro do topo
}

void PrintarCabecalho(FILE *saida) //fazer o cabe�alho
{
    fprintf(saida,"Exemplo de arquivo de saida \n");
    fprintf(saida,"PERT/CPM \n");
    fprintf(saida,"Grafos \n");
    fprintf(saida,"Meu querido programa: \n");
    fprintf(saida,"por favor funcione :) \n");
    fprintf(saida,"-------------------------------------------------- \n");
}

void PularLinhas(FILE *entrada)
{
    char lixo[70];
    int i;
    for(i=0; i<=6; i++)
        fgets(lixo,sizeof(lixo),entrada);
}
void DFS(Grafo *G, int i,FILE *saida)//indicar que h� ciclo
{
    int j;
    G->vetor_noh_grafo[i].descoberto=1;//marcado como descoberto
    Inserir_Na_Pilha(G,i);
    for(j=1; j<=G->quant_nohs_grafo; j++)
    {
        //tem que ter essa l�gica do tem ciclo, pra parar o DFS ja quando achar o ciclo
        if(Matriz_De_Adjacencias[i][j]==1 && G->vetor_noh_grafo[j].descoberto==0 &&G->tem_ciclo!=1)//visitar o n�o descoberto
            DFS(G,j,saida);
        if(Matriz_De_Adjacencias[i][j]==1 && G->vetor_noh_grafo[j].descoberto==1 && G->vetor_noh_grafo[j].finalizado==0 &&G->tem_ciclo!=1)
        {
            fprintf(saida,"\nTem ciclo \n");//agora devo informar o ciclo
            fprintf(saida,"Exemplo de caminho com cilo:\n");
            G->tem_ciclo=1;//identificador de que h� ciclo, n�o tem como algu�m do in�cio ser ciclo
        }
    }//ap�s explorar todos os vizinhos
    G->vetor_noh_grafo[i].finalizado=1;
    if(G->tem_ciclo==1 && G->p->topo!=0)
    {
        Printar_Ciclo(G,saida);//imprimindo o ciclo
    }
    else
        Desempilhar_Da_Pilha(G);
}
void DFS_Topologico(Grafo *G, int i)//quando o grafo n�o for conexo, a travessia funciona
{
    int j;
    G->vetor_noh_grafo[i].descoberto=1;//marcado como descoberto
    for(j=1; j<=G->quant_nohs_grafo; j++)
    {
        if(Matriz_De_Adjacencias[i][j]==1 && G->vetor_noh_grafo[j].descoberto!=1)
            DFS_Topologico(G,j);
    }//ap�s explorar todos os vizinhos, remover da fila
    Inserir_Na_Pilha(G,i);
}
void Travessia_DFS(Grafo *G,FILE *saida)
{
    int i;
    for (i=1; i<=G->quant_nohs_grafo && G->tem_ciclo!=1; i++)
    {
        if (G->vetor_noh_grafo[i].descoberto==0)
            DFS(G,i,saida);
    }
}
void Travessia_DFS_Topologico(Grafo *G)
{
    int i;
    for (i=1; i<=G->quant_nohs_grafo; i++)
    {
        if (G->vetor_noh_grafo[i].descoberto==0)
            DFS_Topologico(G,i);
    }
}
void Tempo_Minimo_Travessia(Grafo *G) //l�gica v�lida para grafos n�o conexos e conexos
{
    int i,j;
    // Percorrer os n�s do grafo
    for (j=1; j<=G->quant_nohs_grafo; j++)
    {
        int maxx=0;
        // Verificar predecessores do n� j
        for (i=1; i<=G->quant_nohs_grafo; i++)
        {
            if (Matriz_De_Adjacencias[i][j]==1)
            {
                // Atualizar o tempo m�ximo do predecessor
                if (G->vetor_noh_grafo[i].tmt>maxx)
                {
                    maxx=G->vetor_noh_grafo[i].tmt;
                }
            }
        }
        // Atualizar o tempo m�nimo de travessia do n� j
        G->vetor_noh_grafo[j].tmt=maxx+G->vetor_noh_grafo[j].duracao_semanas;
        //O do A vai ser justamente o a, no vetor de predecessores
    }
}
void Caminho_Critico(Grafo *G,int n,int indice) //l�gica v�lida pra grafos n�o conexos
{
    int j;
    int indice_caminho_critico;
    int duracao=0;

    // Percorrer todos os n�s conectados ao n� atual
    for (j=1; j<=n; j++)
    {
        if (Matriz_De_Adjacencias[j][indice]==1)   // Se existe uma conex�o, olho de baixo pra cima
        {
            // Procurar o sucessor com maior tmt
            if (G->vetor_noh_grafo[j].tmt>duracao)
            {
                duracao=G->vetor_noh_grafo[j].tmt;
                indice_caminho_critico=j;
            }
        }
    }

    // Imprimir informa��es do n� atual
    G->vetor_noh_grafo[indice].marcador='-';

    // Continuar a partir do pr�ximo n� no caminho cr�tico, se houver
    if (duracao>0)
    {
        Caminho_Critico(G,n,indice_caminho_critico);
    }
}
int main()
{
    FILE *saida;
    FILE *entrada;
    entrada=fopen("entrada6.txt","r");
    saida=fopen("Lab6_Thiago_Zanfolin.txt","w");
    PrintarCabecalho(saida);//printando o cabe�alho
    PularLinhas(entrada);//pulando linhas da entrada
    char Pula_Linha[72];
    Grafo G;
    Inicializar(&G);//inicializando o grafo junto a pilha incrementada a ele
    int i=1;
    while(G.vetor_noh_grafo[i].Tarefa!='-' || G.quant_nohs_grafo==52) //verificar se leu todas as linhas ou se excedeu o n�mero de tarefas
    {
        fscanf(entrada,"  %c   ",&G.vetor_noh_grafo[i].Tarefa);
        if(G.vetor_noh_grafo[i].Tarefa!='-')
        {
            fgets(G.vetor_noh_grafo[i].descricao,31,entrada);
            fscanf(entrada,"  %d",&G.vetor_noh_grafo[i].duracao_semanas);
            fscanf(entrada,"     %s",G.vetor_noh_grafo[i].Tarefas_Precedentes);
            G.quant_nohs_grafo++;
            i++;
        }
    }//lendo o arquivo de entrada
    //j� leu os dados, hora de fazer a matriz
    int n;//quantidade de n�s no grafo
    n=G.quant_nohs_grafo;
    int j,x;//linha
    int k,y;//coluna
    for(j=1; j<=n; j++)
    {
        for(i=0; i<strlen(G.vetor_noh_grafo[j].Tarefas_Precedentes); i++)
        {
            for(k=1; k<=n; k++)
            {
                if(G.vetor_noh_grafo[j].Tarefas_Precedentes[i]==G.vetor_noh_grafo[k].Tarefa)
                    Matriz_De_Adjacencias[k][j]=1;
            }
        }
    }//esse loop triplo tem como fun��o preencher a matriz de adjac�ncias, ap�s a leitura do arquivo de entrada
    for(i=1; i<=n; i++)
    {
        G.vetor_noh_grafo[i].descoberto=0;//inicializando todos os n�s como n�o descobertos
        G.vetor_noh_grafo[i].finalizado=0;
    }//marcando inicialmente todos os n�s do grafo como n�o descobertos e n�o finalizados
    Travessia_DFS(&G,saida);//tal travessia tem como fun��o indetificar, se houver, um ciclo
    if (G.tem_ciclo==1)
    {
        fprintf(saida,"\nHa um ciclo no grafo, representado acima");
        fprintf(saida,"\nLogo eh impossivel buscar o caminho critico\n");
        fprintf(saida,"\n--------------------------------------------------");
        fclose(entrada);
        fclose(saida);
        return 0;//caso tenha algum ciclo no grafo o programa ja se encerra, alertando a sua exist�ncia
    }
    for(i=1; i<=n; i++)
    {
        G.vetor_noh_grafo[i].descoberto=0;//inicializando todos os n�s como n�o descobertos
        G.vetor_noh_grafo[i].finalizado=0;
    }//tem que resetar tudo novamente para fazer o DFS da ordem topol�gica
    //j� analisado se h� ciclo, posso usar a mesma pilha esvaziada para o topol�gico
    Travessia_DFS_Topologico(&G);
    for(i=n; i>=1; i--)
        G.vetor_noh_grafo[n+1-i]=G.p->vet[i];//muda todas as informa��es, para deixar o vetor original de forma topol�gica
    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
            Matriz_De_Adjacencias[i][j]=0;//resetando a matriz de adjac�ncias inicial de acordo com o novo vetor, em ordem topol�gica
    }
    //fazendo agora a nova matriz de adjac�ncias, com o vetor ordenado topologicamente:
    for(j=1; j<=n; j++)
    {
        for(i=0; i<strlen(G.vetor_noh_grafo[j].Tarefas_Precedentes); i++)
        {
            for(k=1; k<=n; k++)
            {
                if(G.vetor_noh_grafo[j].Tarefas_Precedentes[i]==G.vetor_noh_grafo[k].Tarefa)
                    Matriz_De_Adjacencias[k][j]=1;
            }
        }
    }//tal passo � essencial pois ap�s repreencher o vetor de n�s do grafo, a informa��o dos vizinhos foi perdida
    fprintf(saida,"\n");
    fprintf(saida,"UMA ORDENACAO TOPOLOGICA:\n");
    fprintf(saida,"\n");
    for(i=n; i>=1; i--)
        fprintf(saida,"%c ",G.p->vet[i].Tarefa);//indicando a ordem topol�gica
    fprintf(saida,"\n");
    fprintf(saida,"\n-------------------------------------------------- \n");
    //para calcular o tempo minimo
    Tempo_Minimo_Travessia(&G);//atualizando o tempo minimo de travessia de cada v�rtice
    G.vetor_noh_grafo[0].tmt=G.vetor_noh_grafo[1].tmt;//armazeno um tmt para fazer compara��es, aqui otimizo espa�o preenchendo o zero do vetor
    //essas compara��es v�o ser feitas afim de identificar qual o cara do vetor com maior tmt, e consequentemente a dura��o m�xima
    for(i=1; i<=n; i++)
    {
        if(G.vetor_noh_grafo[0].tmt<G.vetor_noh_grafo[i].tmt)
        {
            G.vetor_noh_grafo[0]=G.vetor_noh_grafo[i];//acha o elemento com o maior tmt e salva a posi��o dele
        }
    }
    fprintf(saida,"\nTEMPO MINIMO PARA O PROJETO:  %d semanas\n",G.vetor_noh_grafo[0].tmt);
    fprintf(saida,"\n-------------------------------------------------- \n");//printando o tempo m�nimo de execu��o do projeto
    fprintf(saida,"\nCAMINHO CRITICO:\n");
    fprintf(saida,"\nTAREFA        DESCRICAO           DURACAO\n");
    fprintf(saida,"\n");
    for(i=1; i<=n; i++)
    {
        if(G.vetor_noh_grafo[0].tmt==G.vetor_noh_grafo[i].tmt)
            Caminho_Critico(&G,n,i);//faz o do maior tmt, n�o tem erro percorrendo de traz pra frente,isto �, mandando quem tem o maior tmt
    }
    for(i=1; i<=n; i++)//marcados as tarefas que pertencem ao tmt m�ximo
    {
        if(G.vetor_noh_grafo[i].marcador=='-')
        {
            fprintf(saida," %c    ", G.vetor_noh_grafo[i].Tarefa);
            fprintf(saida,"%s", G.vetor_noh_grafo[i].descricao);
            fprintf(saida," %2d\n", G.vetor_noh_grafo[i].duracao_semanas);
        }
    }//imprimo elas
    fprintf(saida,"\n--------------------------------------------------");
    fclose(entrada);
    fclose(saida);
    return 0;
}
