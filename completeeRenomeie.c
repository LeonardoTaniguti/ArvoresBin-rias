#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da árvore
typedef struct no {
    int chave;
    int contador;
    struct no* esq;
    struct no* dir;
} NO, *PONT;

// Protótipos das funções
void inicializar(PONT* raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT encontrarMinimo(PONT raiz);

// Função para inicializar a árvore
void inicializar(PONT* raiz) {
    *raiz = NULL;
}

// Função para criar um novo nó
PONT criarNo(int valor) {
    PONT novo = (PONT) malloc(sizeof(NO));
    if (novo) {
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// Função para buscar um valor na árvore
PONT buscar(PONT raiz, int valor) {
    if (raiz == NULL || raiz->chave == valor)
        return raiz;
    if (valor < raiz->chave)
        return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

// Função para inserir um valor na árvore
PONT inserir(PONT raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);

    if (valor < raiz->chave)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = inserir(raiz->dir, valor);
    else
        raiz->contador++; // Incrementa a contagem se o valor já existir

    return raiz;
}

// Função auxiliar para encontrar o nó com o menor valor
PONT encontrarMinimo(PONT raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

// Função para remover uma única ocorrência de um valor
PONT removerUmaOcorrencia(PONT raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->chave)
        raiz->esq = removerUmaOcorrencia(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = removerUmaOcorrencia(raiz->dir, valor);
    else {
        if (raiz->contador > 1) {
            raiz->contador--; // Apenas reduz a contagem
            return raiz;
        }

        if (raiz->esq == NULL) {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        }

        PONT temp = encontrarMinimo(raiz->dir);
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        temp->contador = 1;
        raiz->dir = removerUmaOcorrencia(raiz->dir, temp->chave);
    }
    return raiz;
}

// Função para remover todas as ocorrências de um valor
PONT removerTodasOcorrencias(PONT raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->chave)
        raiz->esq = removerTodasOcorrencias(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = removerTodasOcorrencias(raiz->dir, valor);
    else {
        if (raiz->esq == NULL) {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        }

        PONT temp = encontrarMinimo(raiz->dir);
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        temp->contador = 1;
        raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
    }
    return raiz;
}

// Função para exibir a árvore em ordem crescente
void exibirInOrder(PONT raiz) {
    if (raiz != NULL) {
        exibirInOrder(raiz->esq);
        printf("%d(%d) ", raiz->chave, raiz->contador);
        exibirInOrder(raiz->dir);
    }
}

int main() {
    PONT raiz;
    inicializar(&raiz);

    // Inserção de elementos
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 70);

    printf("Árvore em ordem: ");
    exibirInOrder(raiz);
    printf("\n");

    // Teste de busca
    int busca = 70;
    PONT encontrado = buscar(raiz, busca);
    if (encontrado)
        printf("Valor %d encontrado na árvore com frequência %d.\n", busca, encontrado->contador);
    else
        printf("Valor %d não encontrado.\n", busca);

    // Removendo uma ocorrência do 70
    raiz = removerUmaOcorrencia(raiz, 70);
    printf("Após remover uma ocorrência de 70: ");
    exibirInOrder(raiz);
    printf("\n");

    // Removendo todas as ocorrências do 70
    raiz = removerTodasOcorrencias(raiz, 70);
    printf("Após remover todas as ocorrências de 70: ");
    exibirInOrder(raiz);
    printf("\n");

    return 0;
}
