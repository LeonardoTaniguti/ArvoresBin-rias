#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct No {
    int chave;
    int contador;           // Contador de ocorrências da chave
    struct No* esq;
    struct No* dir;
} No, *PonteiroNo;

// Protótipos das funções
void inicializar(PonteiroNo* raiz);
PonteiroNo criarNo(int valor);
PonteiroNo inserir(PonteiroNo raiz, int valor);
PonteiroNo removerUmaOcorrencia(PonteiroNo raiz, int valor);
PonteiroNo removerTodasOcorrencias(PonteiroNo raiz, int valor);
PonteiroNo buscar(PonteiroNo raiz, int valor);
void exibirInOrder(PonteiroNo raiz);
int contarNos(PonteiroNo raiz);
int contarTotalElementos(PonteiroNo raiz);
int kEsimoMenor(PonteiroNo raiz, int k);
void imprimirIntervalo(PonteiroNo raiz, int min, int max);
PonteiroNo ancestralComumMinimo(PonteiroNo raiz, int val1, int val2);

//------------------------------------------------------------------------------
// 1) Inicializar
void inicializar(PonteiroNo* raiz) {
    *raiz = NULL;
}

//------------------------------------------------------------------------------
// 2) Criar nó
PonteiroNo criarNo(int valor) {
    PonteiroNo novo = (PonteiroNo) malloc(sizeof(No));
    if (novo) {
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//------------------------------------------------------------------------------
// 3) Buscar
PonteiroNo buscar(PonteiroNo raiz, int valor) {
    if (!raiz || raiz->chave == valor)
        return raiz;
    if (valor < raiz->chave)
        return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

//------------------------------------------------------------------------------
// 4) Inserir
PonteiroNo inserir(PonteiroNo raiz, int valor) {
    if (!raiz) return criarNo(valor);
    if (valor < raiz->chave)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = inserir(raiz->dir, valor);
    else
        raiz->contador++;
    return raiz;
}

//------------------------------------------------------------------------------
// 5) Remover UMA ocorrência
PonteiroNo removerUmaOcorrencia(PonteiroNo raiz, int valor) {
    if (!raiz) return NULL;
    if (valor < raiz->chave)
        raiz->esq = removerUmaOcorrencia(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = removerUmaOcorrencia(raiz->dir, valor);
    else {
        if (raiz->contador > 1) {
            raiz->contador--;
            return raiz;
        }
        if (!raiz->esq) {
            PonteiroNo temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (!raiz->dir) {
            PonteiroNo temp = raiz->esq;
            free(raiz);
            return temp;
        }
        PonteiroNo temp = raiz->dir;
        while (temp->esq)
            temp = temp->esq;
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        raiz->dir = removerUmaOcorrencia(raiz->dir, temp->chave);
    }
    return raiz;
}

//------------------------------------------------------------------------------
// 6) Remover TODAS ocorrências
PonteiroNo removerTodasOcorrencias(PonteiroNo raiz, int valor) {
    PonteiroNo noEncontrado = buscar(raiz, valor);
    while (noEncontrado)
        raiz = removerUmaOcorrencia(raiz, valor);
    return raiz;
}

//------------------------------------------------------------------------------
// 7) Exibir InOrder
void exibirInOrder(PonteiroNo raiz) {
    if (raiz) {
        exibirInOrder(raiz->esq);
        for (int i = 0; i < raiz->contador; i++)
            printf("%d ", raiz->chave);
        exibirInOrder(raiz->dir);
    }
}

//------------------------------------------------------------------------------
// 8) Contar nós distintos
int contarNos(PonteiroNo raiz) {
    if (!raiz) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//------------------------------------------------------------------------------
// 9) Contar total de elementos
int contarTotalElementos(PonteiroNo raiz) {
    if (!raiz) return 0;
    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir);
}

//------------------------------------------------------------------------------
// 10) k-ésimo menor
int kEsimoMenor(PonteiroNo raiz, int k) {
    if (!raiz) return -1;
    int esquerda = contarTotalElementos(raiz->esq);
    if (k <= esquerda)
        return kEsimoMenor(raiz->esq, k);
    if (k <= esquerda + raiz->contador)
        return raiz->chave;
    return kEsimoMenor(raiz->dir, k - esquerda - raiz->contador);
}

//------------------------------------------------------------------------------
// 11) Imprimir Intervalo
void imprimirIntervalo(PonteiroNo raiz, int min, int max) {
    if (!raiz) return;
    if (min < raiz->chave)
        imprimirIntervalo(raiz->esq, min, max);
    if (min <= raiz->chave && raiz->chave <= max)
        for (int i = 0; i < raiz->contador; i++)
            printf("%d ", raiz->chave);
    if (max > raiz->chave)
        imprimirIntervalo(raiz->dir, min, max);
}

//------------------------------------------------------------------------------
// 12) Ancestral Comum Mínimo
PonteiroNo ancestralComumMinimo(PonteiroNo raiz, int val1, int val2) {
    while (raiz) {
        if (val1 < raiz->chave && val2 < raiz->chave)
            raiz = raiz->esq;
        else if (val1 > raiz->chave && val2 > raiz->chave)
            raiz = raiz->dir;
        else
            return raiz;
    }
    return NULL;
}
