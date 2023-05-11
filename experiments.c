#include <stdio.h>
#include <stdlib.h>

#define d 256
#define q 13

int iteracoes = 0, instrucoes = 0;

typedef struct {
    char* valor;
    int tam;
} string;

string inicializa_string() {
    string str;
    str.tam = 0;
    str.valor = malloc(str.tam * sizeof(char));
    return str;
} 

string le_entrada(string* str) {
    char ch;

    while((ch = getchar()) != '\n' && ch != EOF) {
        str->valor = realloc(str->valor, ++(str->tam) * sizeof(char));
        *(str->valor + str->tam - 1) = ch;
    }
}

int verifica_primeira_ocorrencia(string entrada, string comparacao) {
    int pos_atual_entrada = 0, pos_atual_comparacao = 0;
    instrucoes += 2;
    
    while (pos_atual_entrada < entrada.tam) {
        iteracoes++;
        instrucoes++;
        if (*(entrada.valor + pos_atual_entrada++) == *(comparacao.valor + pos_atual_comparacao)) {
            instrucoes++;
            if (++pos_atual_comparacao == comparacao.tam) {
                instrucoes++;
                return pos_atual_entrada - pos_atual_comparacao;
            }
        } else pos_atual_comparacao = 0;
        instrucoes++;
    }

    instrucoes++;
    return -1;
}

int rabin_karp(string entrada, string comparacao) {
    int m = comparacao.tam;
    int n = entrada.tam;
    int i, j, p = 0, t = 0, h = 1;
    instrucoes += 6;

    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
        instrucoes++;
        iteracoes++;
    }

    // Calculando hash para string de entrada e comparacao
    for (i = 0; i < m; i++) {
        p = (d * p + *(comparacao.valor + i)) % q;
        t = (d * t + *(entrada.valor + i)) % q;
        instrucoes += 2;
        iteracoes++;
    }

    // Encontrando ocorrencia
    for (i = 0; i <= n - m; i++) {
        instrucoes++;
        iteracoes++;
        if (p == t) {
            instrucoes++;
            for (j = 0; j < m; j++) {
                instrucoes += 2;
                iteracoes++;
                if (*(entrada.valor + i + j) != *(comparacao.valor + j))
                    break;
            }

            instrucoes++;
            if (j == m) {
                instrucoes++;
                return i;
            }
        }

        if (i < n - m) {
            instrucoes += 2;
            t = (d * (t - *(entrada.valor + i) * h) + *(entrada.valor + i + m)) % q;

            if (t < 0) {
                instrucoes++;
                t = (t + q);
            }
        }
    }
}

int knuth_morris_pratt(string entrada, string comparacao) {
    int M = comparacao.tam;
    int N = entrada.tam;
    int length = 0, i = 1;

    int pps[M];
    pps[0] = 0;
    instrucoes += 6;
    while (i < M) {
        instrucoes++;
        iteracoes++;
        if (*(comparacao.valor + i) == *(comparacao.valor + comparacao.tam)) {
            length++;
            pps[i] = length;
            i++;
            instrucoes += 4;
        } else {
            if (length != 0) {
                length = pps[length - 1];
                instrucoes++;
            }
            else {
                pps[i] = 0;
                i++;
                instrucoes += 2;
            }
            instrucoes++;
        }
    }

    i = 0;
    int j = 0;
    instrucoes += 2;
    while (i < N) {
        iteracoes++;
        if (*(comparacao.valor + j) == *(entrada.valor + i)) {
            j++;
            i++;
            instrucoes += 2;
        }
        if (j == M) {
            instrucoes++;
            return i - j;
            // j = pps[j - 1];
        }
        else if (i < N && *(comparacao.valor + j) != *(entrada.valor + i)) {
            if (j != 0) j = pps[j - 1];
            else i = i + 1;
            instrucoes += 3;
        }
        instrucoes += 2;
    }
}

int main() {
    int primeira_ocorrencia;

    string entrada = inicializa_string();
    printf("\nInforme string de entrada: ");
    le_entrada(&entrada);

    string comparacao = inicializa_string();
    printf("\nInforme string de comparacao: ");
    le_entrada(&comparacao);

    // iteracoes = 0;
    // instrucoes = 0;
    // primeira_ocorrencia = verifica_primeira_ocorrencia(entrada, comparacao);

    // if (primeira_ocorrencia != -1) printf("\nPrimeira ocorrencia = %d\n", primeira_ocorrencia);
    // else printf("\nNao ha ocorrencias\n");

    // printf("\nIteracoes: %d : Instrucoes: %d\n\n", iteracoes, instrucoes);
    
    iteracoes = 0;
    instrucoes = 0;
    primeira_ocorrencia = rabin_karp(entrada, comparacao);

    if (primeira_ocorrencia != -1) printf("\nPrimeira ocorrencia = %d\n", primeira_ocorrencia);
    else printf("\nNao ha ocorrencias\n");

    printf("\nIteracoes: %d : Instrucoes: %d\n\n", iteracoes, instrucoes);
    
    iteracoes = 0;
    instrucoes = 0;
    primeira_ocorrencia = knuth_morris_pratt(entrada, comparacao);

    if (primeira_ocorrencia != -1) printf("\nPrimeira ocorrencia = %d\n", primeira_ocorrencia);
    else printf("\nNao ha ocorrencias\n");

    printf("\nIteracoes: %d : Instrucoes: %d\n\n", iteracoes, instrucoes);

    return 0;
}