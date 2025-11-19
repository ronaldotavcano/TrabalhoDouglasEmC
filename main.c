#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
/*
    Funções:

    Inserção no início da lista.
    Inserção no final da lista.
    Remoção do início da lista.
    Remoção do final da lista.
    Exibição de todos os elementos.
    Atualização do valor armazenado em um determinado nó.
    Destruir lista.

    Quantidade de ponteiros de controle: 2 ponteiros, fica mais verboso e na nossa opinião menos
    complexo, pois facilita as operações inserir e remover. E com 2 ponteiros removemos a necessidade 
    de pensar no melhor local para o início.

    Tipo de encadeamento: Duplamente encadeada, pois facilitou a manipulação dos elementos da lista nas
    funções de inserir e remover (lá ele).

    Grupo:
    - Matheus Silva Carneiro, Ra: 2038093                
    - Ronaldo Tavares Cano, Ra: 2051371                 
    - Victor Freire do Carmo, Ra: 2051790

*/
typedef struct no{
    int info;
    struct no *prox;
    struct no *ant;
}no;

typedef struct{
    no *inicio;
    no *fim;
} ldc;

ldc* cria_lista(){
    ldc *l;
    l = malloc(sizeof(ldc));
    l->inicio = NULL;
    l->fim = NULL;

    return l;
}

void insere_inicio(ldc *l, int valor) {
    
    no *novo;
    novo = malloc(sizeof(no));
    novo->info = valor;

    if (l->inicio == NULL) { 
        
        l->inicio = novo;
        l->fim = novo;
        
        novo->prox = novo;
        novo->ant = novo;
        
    } else {  
        //1
        novo->prox = l->inicio; 
        //2
        l->inicio->ant = novo; 
        //3
        novo->ant = l->fim;  
        //4   
        l->fim->prox = novo;
        //5
        l->inicio = novo;
    }
}

void insere_fim(ldc *l, int valor) {
    
    no *novo;
    novo = malloc(sizeof(no));
    novo->info = valor;

    if (l->inicio == NULL) { 
        
        l->inicio = novo;
        l->fim = novo;
        
        novo->prox = novo;
        novo->ant = novo;
        
    } else {  
        
        novo->ant = l->fim; 
        l->fim->prox = novo; 
        novo->prox = l->inicio;
        l->inicio->ant = novo;
        l->fim = novo;
    }
}

void remove_inicio(ldc *l){
    
    if (l->inicio == NULL){
        printf("\n A lista esta vazia \n" );
        return;
    }

    no *aux = l->inicio;
    
    if( l->inicio == l->fim){
        l->inicio = NULL;
        l->fim = NULL;
    } else{
        //1
        l->inicio = aux->prox;
        //2
        l->fim->prox = l->inicio;
        //3
        l->inicio->ant = l->fim;
    }
    free(aux);
}

void remove_fim(ldc *l){  
    if (l->inicio == NULL){
        printf("\n A lista esta vazia\n");
        return;
    }

    no *aux = l->fim;
    
    if( l->inicio == l->fim){
        l->inicio = NULL;
        l->fim = NULL;
    } else{
        l->fim = aux->ant;
        l->inicio->ant = l->fim;
        l->fim->prox = l->inicio;
    }
    free(aux);
}

void exibe_lista(ldc *l) {

    if (l->inicio == NULL) {
        printf("\n A lista esta vazia.\n");
        return;
    }
    no *aux = l->inicio;
    
    printf("\nLista: \n");
    printf("<---> ");
    
    do {
        printf("%d <---> ", aux->info);
        aux = aux->prox;
    } while (aux != l->inicio); 
    
}

void alterar_valor(ldc *l, int valor, int valor_novo) {
    
    if (l->inicio == NULL) {
        printf("\nA lista esta vazia\n");
        return;
    }

    no *aux = l->inicio;

    bool encontrado = false; 

    do {
        if (aux->info == valor) {
            aux->info = valor_novo;
            encontrado = true;
            break;
        }       
        aux = aux->prox; 
        
    } while (aux != l->inicio); 

    if (encontrado) {
        printf("\nValor %d alterado com sucesso para %d.\n", valor, valor_novo);
    } else {
        printf("\nValor %d nao encontrado na lista.\n", valor);
    }
}

void destroi_lista(ldc *l) {
    if (l->inicio == NULL) {
        free(l);
        return;
    }

    no *atual;
    atual = l->inicio->prox;
    no *aux;

    while (atual != l->inicio) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    
    free(l->inicio);
    free(l);
}

void main(){
    setlocale(LC_ALL, "Portuguese");
    int valor, opcao, valor_novo;
    ldc *lista = cria_lista();

    do{
        printf("\n");
		system("pause");
		system("cls");

        printf("******** Menu ********\n");
		printf("******** Lista Duplamente Encadeada Circular ********\n");
		printf("[1] Inserir no início \n");
		printf("[2] Inserir no fim \n");
		printf("[3] Remover no início \n");
		printf("[4] Remover no fim \n");
		printf("[5] Exibir Lista \n");
		printf("[6] Atualizar Valor\n");
		printf("[0] Sair \n");
		printf("Escolha uma opção: ");
		scanf("%d", &opcao);

       switch (opcao){
		    case 1: 
                printf("\nDigite o valor a ser implementado no inicio: ");
                scanf("%d", &valor);
                insere_inicio(lista, valor);
                break;


            case 2: 
                printf("\nDigite o valor a ser implementado no fim: ");
                scanf("%d", &valor);
                insere_fim(lista, valor);
                break;


            case 3: 
                remove_inicio(lista);
                break;


            case 4: 
                remove_fim(lista);
                break;


            case 5: 
                exibe_lista(lista);
                break;


            case 6: 
                printf("\nDigite o valor que deseja alterar: ");
                scanf("%d", &valor);
                printf("Digite o novo valor: ");
                scanf("%d", &valor_novo);
                alterar_valor(lista, valor, valor_novo);
                break;


            case 0: 
                destroi_lista(lista);
                printf("\nPrograma finalizado \n"); 
                break;

            default: 
                printf("\nA opção escolhida não existe. Escolha uma opção válida \n");
                break;
       }   
    } while (opcao != 0);   
}