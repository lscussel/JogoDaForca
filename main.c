/*
    Aluno: Leonardo Scussel
    Data.:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

#define tam 50

// retorna: 1, se acertou; 0, se nao
int verificarSeAcertou(char palavraSecreta[], char resposta[])
{
    if (strcmp(palavraSecreta, resposta) == 0)
        return 1;

    return 0;
}

// retorna: 1, se encontrou letra na palavra; 0, se nao encontrou
int assinalarLetrasNaResposta(char palavraSecreta[], char letra, char resposta[])
{
    int i, achou;

    achou = 0;
    i = 0;
    while (palavraSecreta[i] != '\0') {
        if (palavraSecreta[i] == letra) {
            achou = 1;
            resposta[i] = letra;
        }
        i++;
    }

    return achou;
}

// retorna: 1, se acertou letra; 0, se errou
int jogar(char palavraSecreta[], char resposta[], char letra, int letrasUtilizadas[])
{
    int letraEmDecimal, jaSaiu, acertouLetra;

    letraEmDecimal = letra - 65; // 65 e o valor do A em decimal
    jaSaiu = letrasUtilizadas[letraEmDecimal]; // POSICAO: [0] = A; [1] = B; ... e [26] = Z. Valor da posicao guarda se jogador ja escolheu determinada letra na rodada

    if (jaSaiu == 0) {
        letrasUtilizadas[letraEmDecimal] = 1;
        acertouLetra = assinalarLetrasNaResposta(palavraSecreta, letra, resposta);
        return acertouLetra; //retorna: 1, se acertou letra; 0, se errou
    }

    return 1; //retornou 1, pois ja tinha escolhido a mesma letra anteriormente
}

char receberUmaLetra()
{
    char letra;

    do {
        printf("\nDIGITE UMA LETRA (A a Z): ");
        letra = getch();
        letra = toupper(letra);

        if (letra < 65 && letra > 90)
            printf("ENTRADA INVALIDA!! ");
    } while (letra < 65 && letra > 90);

    return letra;
}

void converterPalavraEmMaiusculas(char palavra[])
{
    int i;

    i = 0;
    while (palavra[i] != '\0') {
        palavra[i] = toupper(palavra[i]);
        i++;
    }
}

void inicializarLetrasUtilizadas(int letrasUtilizadas[])
{
    int i;

    for (i = 0; i <= 26; i++) {
        letrasUtilizadas[i] = 0;
    }
}

void zerarResposta(char resposta[], char palavraSecreta[])
{
    int i;
    char temp[tam];

    strcpy(temp, palavraSecreta);
    i = 0;
    while (temp[i] != '\0') {
        if (temp[i] != ' ') {
            temp[i] = '_';
        }
        i++;
    }

    strcpy(resposta, temp);
}

void receberPalavraMaisDicaSecreta(char palavra[], char dica[])
{
    char entrada[tam];

    do {
        printf("\nDIGITE A PALAVRA SECRETA? ");
        fflush(stdin);
        gets(entrada);
        if (strlen(entrada) < 3) {
            printf("ENTRADA INVALIDA!! PALAVRA SECRETA DEVE TER MAIS DE 3 LETRAS\n");
        }
    } while (strlen(entrada) < 3);
    converterPalavraEmMaiusculas(entrada);
    strcpy(palavra, entrada);

    do {
        printf("\nDIGITE A DICA DA PALAVRA SECRETA? ");
        fflush(stdin);
        gets(entrada);
        if (strlen(entrada) < 3) {
            printf("ENTRADA INVALIDA!! DICA DA PALAVRA SECRETA DEVE TER MAIS DE 3 LETRAS\n");
        }
    } while (strlen(entrada) < 3);
    converterPalavraEmMaiusculas(entrada);
    strcpy(dica, entrada);
}

void montarCorpo(int vidas, char corpo[])
{
    char membros[7];
    int i;

    membros[6] = 'o';
    membros[5] = '|';
    membros[4] = '/';
    membros[3] = '\\';
    membros[2] = '/';
    membros[1] = '\\';
    membros[0] = ' ';

    i = 6;
    while (vidas <= i) {
        corpo[i] = membros[i];
        i--;
    }

    while (i >= 0) {
        corpo[i] = ' ';
        i--;
    }
}

void imprimirTelaJogo(int vidas, char resposta[], char dicaPalavra[], char palavraSecreta[])
{
    char corpo[7];

    montarCorpo(vidas, corpo);

    printf(" %c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 187);
    printf(" %c    %c\n", 186, corpo[6]);
    printf(" %c   %c%c%c      %s\n", 186, corpo[4], corpo[5], corpo[3], resposta);
    printf(" %c   %c %c      \n", 186, corpo[2], corpo[1]);
    printf(" %c            %s\n", 186, dicaPalavra);
    printf(" %c\n", 186);
    printf("%c%c%c ", 205, 202, 205);
    if (vidas == 0)
        printf("ENFORCADO!!    ** A RESPOSTA ERA => %s **", palavraSecreta);
    printf("\n");
    printf("    NUMEROS DE JOGADAS RESTANTES: %d\n\n", vidas);
}

int jogarNovamente()
{
    char continuar;

    do {
        printf("\n\nDESEJA JOGAR NOVAMENTE? (S) ou (N): ");
        fflush(stdin);
        continuar = getch();
            if (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
                printf("ENTRADA INVALIDA!! ");
            }
    } while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n');
}

int main()
{
    char continuar, letra;
    int vidas, acertou, letrasUtilizadas[26], venceu;
    char palavraSecreta[tam], dica[tam], resposta[tam];

    venceu = 0;
    vidas = 0;
    strcpy(resposta, "JOGO DA FORCA");
    strcpy(dica, "BY LSCUSSEL");
    strcpy(palavraSecreta, "FACA TEU MELHOR, NA CONDICAO QUE VOCE TEM!");
    imprimirTelaJogo(vidas, resposta, dica, palavraSecreta);
    Sleep(5000);
    do {
        vidas = 7;
        receberPalavraMaisDicaSecreta(palavraSecreta, dica);
        zerarResposta(resposta, palavraSecreta);
        do {
            system("cls");
            inicializarLetrasUtilizadas(letrasUtilizadas);
            imprimirTelaJogo(vidas, resposta, dica, palavraSecreta);
            letra = receberUmaLetra();
            acertou = jogar(palavraSecreta, resposta, letra, letrasUtilizadas);
            if (acertou == 0)
                vidas--;
            venceu = verificarSeAcertou(palavraSecreta, resposta);
        } while (vidas > 0 && venceu == 0);

        system("cls");
        imprimirTelaJogo(vidas, resposta, dica, palavraSecreta);

        if (venceu == 1)
            printf("PARABENS. VOCE VENCEU \\o/\n");
        continuar = jogarNovamente();
    } while (continuar == 'S' || continuar == 's');

    printf("\n\nBy LScussel\n");
    printf("Digite qualquer tecla para sair\n");
    getch();
    return 0;
}
