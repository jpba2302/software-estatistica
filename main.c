#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Programa com vetor dinâmico que vai aumentando o tamanho conforme o usuário vai registrando as amostras
calcula média, mediana, moda e desvio padrão */

/* Mostra o menu e retorna a opção selecionada pelo usuário (int) */

int mostraMenu() {
    int opcao;
    printf("1- Registrar amostra\n");
    printf("2- Calcular média\n");
    printf("3- Calcular mediana\n");
    printf("4- Calcular moda\n");
    printf("5- Calcular desvio padrão\n");
    printf("6- Encerrar programa\n\n");
    printf("Digite uma opção: ");
    scanf("%d",&opcao);
    printf("\n");
    return opcao;
}

/*Recebe um vetor e um tamanho, aumenta o tamanho do vetor e retorna ele, também aumenta o valor do tamanho*/

float *registraAmostra (float *vetor, int *pTamanho) {

    int tamanho = *pTamanho;
    if (*pTamanho == 0) {
        tamanho = tamanho + 1;
        vetor = (float*)realloc(vetor, sizeof(float)*tamanho);
    } else {
        tamanho = tamanho + 1;
        vetor = (float*)realloc(vetor,sizeof(float)*tamanho);
    }
    printf("Digite o valor da amostra: ");
    scanf("%f",&vetor[tamanho - 1]);
    printf("\n");
    *pTamanho = tamanho;
    return vetor;
}

void mostraVetor(float *vetor, int tamanho) {
    printf("\n");
    for (int i = 0;i < tamanho;i++) {
        printf("%.2f ",*(vetor + i));
    }
    printf("\n\n");
}

// Recebeo o vetor e o tamanho e retorna ele ordenado

float *bubblesort(float *vetor, int tamanho) {
    for (int i = 0;i < tamanho - 1;i++) {
        for (int j = 0;j < tamanho - 1;j++) {
            if (vetor[j] > vetor[j+1]) {
                float aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
    printf("\nVetor ordenado com sucesso\n\n");
    return vetor;
}

// recebe um vetor e um tamanho, calcula a média e retorna ela
float calculaMedia (float *vetor, int tamanho) {
    float soma = 0;
    for (int i = 0;i < tamanho;i++) {
        soma = soma + vetor[i];
    }
    soma = soma / tamanho;
    return soma;
}

// recebe um vetor e um tamanho e mostra a moda
void calculaModa (float *vetor, int tamanho) {
    float moda = 0;
    int maiorReps = 0;
    int repAtual = 0;
    float numAtual = 0;
    int modas = 0;
    for (int i = 0;i < tamanho;i++) {
        if (i == 0) {
            moda = vetor[i];
            numAtual = vetor[i];
        }
        if (vetor[i] != numAtual) {
            numAtual = vetor[i];
            repAtual = 1;
        } else {
            repAtual = repAtual + 1;
        }
        if (repAtual > maiorReps) {
            modas = 1;
            moda = numAtual;
            maiorReps = repAtual;
        } else if (repAtual == maiorReps) {
            modas = modas + 1;
        }
    }
    if (modas > 1 && maiorReps != 1) {
        printf("O vetor possui mais de uma moda\n");
    }
    if (maiorReps == 1) {
        printf("O vetor não tem moda\n");
    } else {
        printf("A moda é %.2f\n\n", moda);
    }
}

// recebe um vetor e um tamanho e mostra a mediana
void calculaMediana (float *vetor, int tamanho) {
    if (tamanho % 2 == 0) {
        printf("A mediana é: %.2f\n\n",(vetor[tamanho/2] + vetor[tamanho/2-1])/2);
    } else {
        printf("A mediana é: %.2f\n\n",vetor[tamanho / 2]);
    }
}

// recebe um vetor e um tamanho e calcula a variancia
float calculaVariancia (float *vetor, int tamanho) {
    float soma = 0;
    for (int i = 0;i < tamanho;i++) {
        soma = pow(vetor[i] - calculaMedia(vetor, tamanho), 2) + soma;
    }
    return soma;
}

// recebe um vetor e um tamanho e calcula o desvio padrão
float calculaDp (float *vetor, int tamanho) {
    float soma = calculaVariancia(vetor, tamanho);
    soma = soma / tamanho;
    return sqrt(soma);
}

int main()
{
    int opcao = 0;
    int tamanho = 0;
    int *pTamanho;
    pTamanho = &tamanho;
    float *vetor = NULL;
    vetor = (float*)malloc(sizeof(float)*1);

    while (opcao != 6) {
        opcao = mostraMenu();
        switch(opcao) {

            case 1:
                vetor = registraAmostra(vetor, pTamanho);
                mostraVetor(vetor, tamanho);
                printf("%d amostras registradas\n\n",tamanho);
                break;

            case 2:
                printf("A média do vetor é: %.2f\n\n",calculaMedia(vetor, tamanho));
                break;

            case 3:
                vetor = bubblesort(vetor, tamanho);
                calculaMediana(vetor, tamanho);
                mostraVetor(vetor, tamanho);
                break;

            case 4:
                vetor = bubblesort(vetor, tamanho);
                calculaModa(vetor, tamanho);
                mostraVetor(vetor, tamanho);
                break;

            case 5:
                printf("O desvio padrão é %.2f\n\n", calculaDp(vetor, tamanho));
                break;

            case 6:
                printf("Encerrando o programa\n");
                break;

            default:
                printf("Opção inválida\n");
        }
    }
    return 0;
}
