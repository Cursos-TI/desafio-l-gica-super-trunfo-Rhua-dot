#include <stdio.h> // Para funções de entrada/saída como printf
#include <string.h> // Para manipulação de strings (embora não seja tão usado neste exemplo direto)

// --- Definição da Estrutura para uma Carta do Super Trunfo ---
// Atributos de cada carta.
typedef struct {
    char estado[3]; // Ex: "SP", "RJ" -
    char codigoCarta[5]; // Ex: "C001"
    char nomeCidade[50];
    int populacao;
    float area; // em km²
    float pib; // em bilhões de Reais
    int pontosTuristicos;
    float densidadePopulacional; // Atributo calculado: População / Área
    float pibPerCapita; // Atributo calculado: PIB / População
} Carta;

// --- Função para Calcular Atributos Derivados (Densidade Populacional e PIB per Capita) ---
// Recebe um ponteiro para uma Carta para modificar seus valores calculados diretamente.
void calcularAtributosCalculados(Carta *carta) {
    // Sem divisao por zero ao calcular a densidade populacional
    if (carta->area > 0) {
        carta->densidadePopulacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidadePopulacional = 0; // Se a área for 0, a densidade é 0
    }

    // Garante que não haja divisao por zero ao calcular o PIB per capita
    if (carta->populacao > 0) {
        // Multiplica o PIB por 1 bilhao (1.000.000.000) para converter de bilhoes de Reais para Reais antes de dividir pela populaçao
        carta->pibPerCapita = (carta->pib * 1000000000.0) / carta->populacao;
    } else {
        carta->pibPerCapita = 0; // Se a populaçao for 0, o PIB per capita e 0
    }
}

// --- Funçao para Exibir os Detalhes Completos de uma Carta ---
// Recebe um ponteiro constante para uma Carta, pois não a modificará, apenas exibira.
void exibirDetalhesCarta(const Carta *carta) {
    printf("--- Detalhes da Carta ---\n");
    printf("Estado: %s\n", carta->estado);
    printf("Codigo da Carta: %s\n", carta->codigoCarta);
    printf("Nome da Cidade: %s\n", carta->nomeCidade);
    printf("Populacao: %d habitantes\n", carta->populacao);
    printf("Area: %.2f km2\n", carta->area);
    printf("PIB: R$ %.2f bilhoes\n", carta->pib);
    printf("Pontos Turisticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km2\n", carta->densidadePopulacional);
    printf("PIB per Capita: R$ %.2f\n", carta->pibPerCapita);
    printf("-------------------------\n\n");
}

// --- Função Principal do Programa ---
int main() {
    // 1. Receber os dados de duas cartas:
    // As cartas são pré-definidas diretamente no código, conforme simplificação do desafio.
    Carta carta1 = {
        "SP",        // Estado
        "C001",      // Codigo da carta
        "Sao Paulo", // Nome da cidade
        12300000,    // Populacao
        1521.11,     // Area (em km²)
        747.6,       // PIB (em bilhoes de Reais)
        100          // Numero de pontos turisticos
    };

    Carta carta2 = {
        "RJ",          // Estado
        "C002",        // Codigo da carta
        "Rio de Janeiro", // Nome da cidade
        6775000,       // Populaçao
        1200.27,       // Area (em km²)
        370.0,         // PIB (em bilhoes de Reais)
        80             // Numero de pontos turisticos
    };

    // 2. Calcular Densidade Populacional e PIB per Capita para ambas as cartas
    calcularAtributosCalculados(&carta1);
    calcularAtributosCalculados(&carta2);

    // --- Escolha do Atributo para Comparacao (diretamente no codigo) ---
    // Você pode alterar o valor de 'atributoComparacao' (1 a 5) para testar diferentes comparacoes.
    // 1: População
    // 2: Área
    // 3: PIB
    // 4: Densidade Populacional (menor valor vence!)
    // 5: PIB per Capita
    int atributoComparacao = 1; // Exemplo: Comparar por Populaçao

    printf("--- Super Trunfo: Comparacao de Cartas ---\n\n");

    // Opcional: Exibir detalhes completos das cartas para visualização
    printf("Carta 1:\n");
    exibirDetalhesCarta(&carta1);
    printf("Carta 2:\n");
    exibirDetalhesCarta(&carta2);

    // --- Logica de Comparação Principal ---
    printf("Comparacao de cartas (Atributo: ");

    float valorCarta1, valorCarta2;
    //'const char *' para atribuir literais de string com segurança.
    const char *nomeAtributo; // Variável para armazenar o nome do atributo sendo comparado
    int cartaVencedora = 0;   // 0 = empate, 1 = carta1 vence, 2 = carta2 vence

    // determinar qual atributo comparar e aplicar a regra de vitória.
    switch (atributoComparacao) {
        case 1: // Comparacao por Populacao
            nomeAtributo = "Populacao";
            valorCarta1 = (float)carta1.populacao;
            valorCarta2 = (float)carta2.populacao;
            // Para Populacao, o maior valor vence
            if (valorCarta1 > valorCarta2) {
                cartaVencedora = 1;
            } else if (valorCarta2 > valorCarta1) {
                cartaVencedora = 2;
            }
            break;
        case 2: // Comparacao por Area
            nomeAtributo = "Area";
            valorCarta1 = carta1.area;
            valorCarta2 = carta2.area;
            // Para Area, o maior valor vence
            if (valorCarta1 > valorCarta2) {
                cartaVencedora = 1;
            } else if (valorCarta2 > valorCarta1) {
                cartaVencedora = 2;
            }
            break;
        case 3: // Comparação por PIB
            nomeAtributo = "PIB";
            valorCarta1 = carta1.pib;
            valorCarta2 = carta2.pib;
            // Para PIB, o maior valor vence
            if (valorCarta1 > valorCarta2) {
                cartaVencedora = 1;
            } else if (valorCarta2 > valorCarta1) {
                cartaVencedora = 2;
            }
            break;
        case 4: // Comparação por Densidade Populacional
            nomeAtributo = "Densidade Populacional";
            valorCarta1 = carta1.densidadePopulacional;
            valorCarta2 = carta2.densidadePopulacional;
            // **EXCEÇÃO:** Para Densidade Populacional, o MENOR valor vence!
            if (valorCarta1 < valorCarta2) {
                cartaVencedora = 1;
            } else if (valorCarta2 < valorCarta1) {
                cartaVencedora = 2;
            }
            break;
        case 5: // Comparação por PIB per Capita
            nomeAtributo = "PIB per Capita";
            valorCarta1 = carta1.pibPerCapita;
            valorCarta2 = carta2.pibPerCapita;
            // Para PIB per Capita, o maior valor vence
            if (valorCarta1 > valorCarta2) {
                cartaVencedora = 1;
            } else if (valorCarta2 > valorCarta1) {
                cartaVencedora = 2;
            }
            break;
        default:
            // Caso um número de atributo inválido seja escolhido
            printf("Atributo de comparacao invalido.\n");
            return 1; // Retorna 1 para indicar um erro
    }

    // --- Exibir o Resultado da Comparação ---
    printf("%s):\n", nomeAtributo);

    printf("Carta 1 - %s (%s): ", carta1.nomeCidade, carta1.estado);
    // Formatação específica para cada atributo para melhor legibilidade
    if (atributoComparacao == 1) printf("%d\n", (int)valorCarta1); // População como inteiro
    else if (atributoComparacao == 5) printf("R$ %.2f\n", valorCarta1); // PIB per capita como moeda
    else if (atributoComparacao == 4) printf("%.2f hab/km2\n", valorCarta1); // Densidade com unidade
    else printf("%.2f\n", valorCarta1); // Outros floats

    printf("Carta 2 - %s (%s): ", carta2.nomeCidade, carta2.estado);
    if (atributoComparacao == 1) printf("%d\n", (int)valorCarta2);
    else if (atributoComparacao == 5) printf("R$ %.2f\n", valorCarta2);
    else if (atributoComparacao == 4) printf("%.2f hab/km2\n", valorCarta2);
    else printf("%.2f\n", valorCarta2);

    printf("Resultado: ");
    if (cartaVencedora == 1) {
        printf("Carta 1 (%s) venceu!\n", carta1.nomeCidade);
    } else if (cartaVencedora == 2) {
        printf("Carta 2 (%s) venceu!\n", carta2.nomeCidade);
    } else {
        printf("Empate!\n");
    }

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
