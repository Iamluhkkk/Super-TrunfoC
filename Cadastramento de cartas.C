#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CIDADES 100

// Defini��o da estrutura Cidade, que agrupa os dados de cada cidade
typedef struct {
    char nome[100];             // Nome da cidade
    int populacao;              // Popula��o total
    float area;                 // �rea em km�
    float pib;                  // PIB total em bilh�es
    int pontosTuristicos;       // N�mero de pontos tur�sticos
    float densidadePopulacional; // Propriedade calculada: popula��o / �rea
    float pibPerCapita;         // Propriedade calculada: PIB / popula��o
} Cidade;

// Fun��o que calcula as propriedades derivadas da cidade
void calcularPropriedades(Cidade *c) {
    // Calcula densidade populacional (habitantes por km�)
    if (c->area != 0)
        c->densidadePopulacional = c->populacao / c->area;
    else
        c->densidadePopulacional = 0; // Evita divis�o por zero

    // Calcula PIB per capita (PIB dividido pela popula��o)
    if (c->populacao != 0)
        c->pibPerCapita = c->pib / c->populacao;
    else
        c->pibPerCapita = 0; // Evita divis�o por zero
}

// Fun��o para cadastrar uma nova cidade, com entrada e valida��o dos dados
void cadastrarCidade(Cidade cidades[], int *quantidade) {
    Cidade nova;
    char buffer[256];

    printf("\n--- Cadastro de Cidade ---\n");

    // Entrada do nome da cidade (string com espa�os)
    printf("Nome da cidade: ");
    fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = 0;  // Remove o caractere '\n' do final

    // Entrada e valida��o da popula��o (inteiro positivo)
    while (1) {
        printf("Popula��o: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nova.populacao) == 1 && nova.populacao > 0)
            break;
        printf("Entrada inv�lida. Digite um n�mero inteiro positivo.\n");
    }

    // Entrada e valida��o da �rea (float positivo)
    while (1) {
        printf("�rea (km�): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &nova.area) == 1 && nova.area > 0)
            break;
        printf("Entrada inv�lida. Digite um n�mero decimal positivo.\n");
    }

    // Entrada e valida��o do PIB (float, pode ser zero)
    while (1) {
        printf("PIB (em bilh�es): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &nova.pib) == 1 && nova.pib >= 0)
            break;
        printf("Entrada inv�lida. Digite um n�mero decimal v�lido.\n");
    }

    // Entrada e valida��o do n�mero de pontos tur�sticos (inteiro >= 0)
    while (1) {
        printf("N�mero de pontos tur�sticos: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nova.pontosTuristicos) == 1 && nova.pontosTuristicos >= 0)
            break;
        printf("Entrada inv�lida. Digite um n�mero inteiro v�lido.\n");
    }

    // Calcula as propriedades derivadas automaticamente
    calcularPropriedades(&nova);

    // Armazena a nova cidade no vetor e incrementa a quantidade cadastrada
    cidades[*quantidade] = nova;
    (*quantidade)++;

    printf("Cidade cadastrada com sucesso!\n");
}

// Fun��o para exibir todas as cidades cadastradas com seus dados completos
void exibirCidades(Cidade cidades[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhuma cidade cadastrada.\n");
        return;
    }

    printf("\n--- Cidades Cadastradas ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nCidade: %s\n", cidades[i].nome);
        printf("Popula��o: %d\n", cidades[i].populacao);
        printf("�rea: %.2f km�\n", cidades[i].area);
        printf("PIB: R$ %.2f bilh�es\n", cidades[i].pib);
        printf("Pontos tur�sticos: %d\n", cidades[i].pontosTuristicos);
        printf("Densidade Populacional: %.2f hab/km�\n", cidades[i].densidadePopulacional);
        printf("PIB per Capita: R$ %.2f\n", cidades[i].pibPerCapita);
    }
}

int main() {
    setlocale(LC_ALL, "");

    Cidade cidades[MAX_CIDADES];
    int quantidade = 0;
    int opcao;
    char buffer[256];

    do {
        printf("\n--- Menu Super Trunfo ---\n");
        printf("1. Cadastrar cidade\n");
        printf("2. Exibir cidades cadastradas\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");

        // Leitura segura da op��o do menu
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &opcao) != 1) {
            printf("Entrada inv�lida! Digite um n�mero.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                if (quantidade >= MAX_CIDADES) {
                    printf("Limite de cidades cadastradas atingido.\n");
                } else {
                    cadastrarCidade(cidades, &quantidade);
                }
                break;
            case 2:
                exibirCidades(cidades, quantidade);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}