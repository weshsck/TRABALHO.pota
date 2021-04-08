#include <stdio.h>
#include <stdlib.h>

// constante repesenta o tamanho da tabela
#define M 19

// estrutura Pessoa com nome e uma matrícula
typedef struct{
    int matricula;
    char nome[50];
}Pessoa;

// nossa tabela hash do tipo Pessoa
Pessoa tabelaHash[M];

// inicializa nossa tabela com o valor de codigo -1
void inicializarTabela(){
    int i;
    for(i = 0; i < M; i++)
        tabelaHash[i].matricula = -1;
}

// função de espalhamento (resto da divisão da chave por M)
int gerarCodigoHash(int chave){
    return chave % M;
}

// função para ler e retornar uma pessoa
Pessoa lerPessoa(){
    Pessoa p;
    printf("Digite a matricula: ");
    scanf("%d", &p.matricula);
    scanf("%*c");
    printf("Digite o nome: ");
    fgets(p.nome, 50, stdin);
    return p;
}

// inserir uma pessoa na tabela
void inserir(){
    Pessoa pes = lerPessoa();
    int indice = gerarCodigoHash(pes.matricula);
    while(tabelaHash[indice].matricula != -1)
        indice = gerarCodigoHash(indice + 1);
    tabelaHash[indice] = pes;
}

Pessoa* buscar(int chave){
    int indice = gerarCodigoHash(chave);
    while(tabelaHash[indice].matricula != -1){
        if(tabelaHash[indice].matricula == chave)
            return &tabelaHash[indice];
        else
            indice = gerarCodigoHash(indice + 1);
    }
    return NULL;
}

void imprimir(){
    int i;
    printf("\n------------------------TABELA---------------------------\n");
    for(i = 0; i < M; i++){
        if(tabelaHash[i].matricula != -1)
            printf("%2d = %3d \t %s", i, tabelaHash[i].matricula, tabelaHash[i].nome);
        else
            printf("%2d =\n", i);
    }
    printf("\n----------------------------------------------------------\n");
}

int main() {
    int op, chave;
    Pessoa *p;

    inicializarTabela();

    do{
        printf("1 - Inserir\n2 - Buscar\n3 - Imprimir\n0 - Sair\n");
        scanf("%d", &op);

        switch(op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            inserir();
            break;
        case 2:
            printf("Digite a matricula a ser buscada: ");
            scanf("%d", &chave);
            p = buscar(chave);

            if(p)
                printf("\n\tMatricula: %d \tNome: %s\n", p->matricula, p->nome);
            else
                printf("\nMatricula nao encontrada!\n");
            break;
        case 3:
            imprimir();
            break;
        default:
            printf("Opcao invalida!\n");
        }

    }while(op != 0);

    return 0;
}
