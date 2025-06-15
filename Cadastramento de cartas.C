#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CIDADES 100

// Definição da estrutura Cidade, que agrupa os dados de cada cidade
typedef struct {
    char nome[100];             // Nome da cidade
    int populacao;              // População total
    float area;                 // Área em km²
    float pib;                  // PIB total em bilhões
    int pontosTuristicos;       // Número de pontos turísticos
    float densidadePopulacional; // Propriedade calculada: população / área
    float pibPerCapita;         // Propriedade calculada: PIB / população
} Cidade;

// Função que calcula as propriedades derivadas da cidade
void calcularPropriedades(Cidade *c) {
    // Calcula densidade populacional (habitantes por km²)
    if (c->area != 0)
        c->densidadePopulacional = c->populacao / c->area;
    else
        c->densidadePopulacional = 0; // Evita divisão por zero

    // Calcula PIB per capita (PIB dividido pela população)
    if (c->populacao != 0)
        c->pibPerCapita = c->pib / c->populacao;
    else
        c->pibPerCapita = 0; // Evita divisão por zero
}

// Função para cadastrar uma nova cidade, com entrada e validação dos dados
void cadastrarCidade(Cidade cidades[], int *quantidade) {
    Cidade nova;
    char buffer[256];

    printf("\n--- Cadastro de Cidade ---\n");

    // Entrada do nome da cidade (string com espaços)
    printf("Nome da cidade: ");
    fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = 0;  // Remove o caractere '\n' do final

    // Entrada e validação da população (inteiro positivo)
    while (1) {
        printf("População: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nova.populacao) == 1 && nova.populacao > 0)
            break;
        printf("Entrada inválida. Digite um número inteiro positivo.\n");
    }

    // Entrada e validação da área (float positivo)
    while (1) {
        printf("Área (km²): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &nova.area) == 1 && nova.area > 0)
            break;
        printf("Entrada inválida. Digite um número decimal positivo.\n");
    }

    // Entrada e validação do PIB (float, pode ser zero)
    while (1) {
        printf("PIB (em bilhões): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &nova.pib) == 1 && nova.pib >= 0)
            break;
        printf("Entrada inválida. Digite um número decimal válido.\n");
    }

    // Entrada e validação do número de pontos turísticos (inteiro >= 0)
    while (1) {
        printf("Número de pontos turísticos: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nova.pontosTuristicos) == 1 && nova.pontosTuristicos >= 0)
            break;
        printf("Entrada inválida. Digite um número inteiro válido.\n");
    }

    // Calcula as propriedades derivadas automaticamente
    calcularPropriedades(&nova);

    // Armazena a nova cidade no vetor e incrementa a quantidade cadastrada
    cidades[*quantidade] = nova;
    (*quantidade)++;

    printf("Cidade cadastrada com sucesso!\n");
}

// Função para exibir todas as cidades cadastradas com seus dados completos
void exibirCidades(Cidade cidades[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhuma cidade cadastrada.\n");
        return;
    }

    printf("\n--- Cidades Cadastradas ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nCidade: %s\n", cidades[i].nome);
        printf("População: %d\n", cidades[i].populacao);
        printf("Área: %.2f km²\n", cidades[i].area);
        printf("PIB: R$ %.2f bilhões\n", cidades[i].pib);
        printf("Pontos turísticos: %d\n", cidades[i].pontosTuristicos);
        printf("Densidade Populacional: %.2f hab/km²\n", cidades[i].densidadePopulacional);
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
        printf("Escolha uma opção: ");

        // Leitura segura da opção do menu
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
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
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}