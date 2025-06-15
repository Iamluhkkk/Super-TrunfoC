#include <stdio.h>
#include <locale.h>  // para setlocale

// Definição da estrutura para armazenar os dados das cartas
struct Carta {
    char estado[3];
    char cidade[50];
    char codigo_carta[10];
    float populacao;
    float area_km2;
    float PIB;
    int pontos_turisticos;
};

int main() {
    setlocale(LC_ALL,"Portuguese_Brazil");

    // Criando um array de cartas
    struct Carta cartas[5] = {
        {"SP","São Paulo","A01", 12300000 ,1521.11, 799.0e9, 30},
        {"SP", "Sorocaba","A02", 757459, 449.87, 44.5e6,15},
        {"SP", "Itapevi", "A03", 232297, 82.659, 12e7, 9},
        {"SP", "Diadema", "A04", 393237, 30.732, 4.3e4, 10},
        {"SP", "Guarulhos", "A05", 1291771, 319.2, 55.0e8, 10},
    };

    // Exibindo os dados das cartas
    for (int i = 0; i < 5; i++) {
        printf("\n----- Carta %d -----\n", i + 1);
        printf("Estado: %s\n", cartas[i].estado);
        printf("Cidade: %s\n", cartas[i].cidade);
        printf("Código da Carta: %s\n", cartas[i].codigo_carta);
        printf("População: %.0f\n", cartas[i].populacao);
        printf("Área (km²): %.2f\n", cartas[i].area_km2);
        printf("PIB: %.2f milhões\n", cartas[i].PIB / 1e6);
        printf("Pontos turísticos: %d\n", cartas[i].pontos_turisticos);
    }

    return 0;
}