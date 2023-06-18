/*
 -2º Trabalho Prático de Linguagem de Programação - Consultório Médico
 -Fatec Carapicuíba | ADS | Matutino
------------------------------------------------------
 -Autores:    
 *Gustavo Liros Silva dos Santos     RA: 1430482021029
 *José Victor de Oliveira Cazzolli   RA: 1430482021034
 *Matheus Delfino Costa Silva        RA: 1430482021001
 *Nathan Rosa Ferreira               RA: 1430482021018
 *Ryan Silva Aquino                  RA: 1430482021015
------------------------------------------------------
 * my_date.c
 * Contém as implementações das funções, do M.e Ciro C. Trindade,
 * que se encontram no arquivo de cabeçalho my_date.h para solução
 * do 2º trabalho prático.
 */ 
 
/* Inclui o arquivo de cabeçalho my_date.h que contém os
 * protótipos das funções e os tipos de estrutura data e
 * horario, do M.e Ciro C. Trindade. */
#include "my_date.h"

#include <stdio.h>

/* Função para impressão de data. */
void imprime_data(data d)                               // <- Recebe como Parâmetro uma estrutura do tipo 'data'.
{
    printf("%02d/%02d/%4d", d.dia, d.mes, d.ano);       // <- Imprime os membros 'dias', 'mes' e 'ano'.
}
/* Função para impressão de horário. */
void imprime_horario(horario h)                         // <- Recebe como Parâmetro uma estrutura do tipo 'horario'.
{
    printf("%02d:%02d", h.horas, h.minutos);            // <- Imprime os membros 'horas' e 'minutos'.
}

/* Função para impressão de data e horário. */
void imprime_data_horario(data d, horario h)            // <- Recebe como Parâmetro uma estrutura do tipo 'data' e 'horario'.
{
    imprime_data(d);                                    // <- Chama a função imprime_data passando a variável 'd'.
    printf(" - ");                              
    imprime_horario(h);                                 // <- Chama a função imprime_horario passando a variável 'h'.
}

/* Função para a entrada de data. */
void le_data(const char * msg, data * d)                // <- Recebe uma constante do tipo char e uma variável 
{                                                       // do tipo 'data' por referência.
    printf("%s (dd/mm/aaaa): ", msg);                   
    scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);       // <- Lê as variáveis e atribui por ponteiro.
}

/* Função para a entrada de horário. */
void le_horario(const char * msg, horario * h)          // <- Recebe uma constante do tipo char e uma variável 
{                                                       // do tipo 'horario' por referência.
    printf("%s (hh:mm): ", msg);
    scanf("%d:%d", &h->horas, &h->minutos);             // <- Lê as variáveis e atribui por ponteiro.
}

/* Função para a entrada de data e horário. */
void le_data_horario(const char * msg, data * d, horario * h) // <- Recebe uma constante do tipo char, uma variável do tipo
{                                                             // 'data' e uma variável do tipo 'horario', ambas por referência.
    printf("%s (dd/mm/aaaa hh:mm): ", msg);
    scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);       // <- Lê as variáveis e atribui por ponteiro.
    scanf("%d:%d", &h->horas, &h->minutos);             // <-                 '' 
}

/* Função de comparação de data. Retorna 0 caso forem
 * iguais. Se for diferente, vai ser retornado um valor
 * diferente de 0. */
int compara_data(data d1, data d2)                      // <- Recebe duas variáveis do tipo 'data'.
{
    return data_to_aaaammdd(d1) - data_to_aaaammdd(d2); // <- Utiliza as macros auxiliares que recebem as
}                                                       // variáveis 'd1' e 'd2' e retorna a diferença.

/* Função de comparação de horário. Retorna 0 caso forem
 * iguais. Se for diferente, vai ser retornado um valor
 * diferente de 0. */
int compara_horario(horario h1, horario h2)             // <- Recebe duas variáveis do tipo 'horario'.
{
    return horario_to_minutos(h1) - horario_to_minutos(h2); // <- Utiliza as macros auxiliares que recebem as
}                                                           // variáveis 'h1' e 'h2' e retorna a diferença.

/* Função de comparação de horário e data. Retorna a dt se 
 * as datas forem diferentes. Caso forem iguais, retorna a 
 * diferença dos horários. */
int compara_data_horario(data d1, horario h1, data d2, horario h2) // <- Recebe duas variáveis do tipo 'horario'
{                                                                  // e duas variáveis do tipo 'data'.
    /* Armazena em 'dt' (Uma variável do tipo inteiro) o retorno 
     * da função 'compara_data' que recebe 'd1' e 'd2' por parâmetro */
    int dt = compara_data(d1, d2);                      
    if (dt != 0) {                                      // <- Verifica se 'dt' é diferente de 0, isto
        return dt;                                      // é, se as datas forem diferentes retorna dt.
    }
    return compara_horario(h1, h2);                     // <- Caso as datas forem iguais, retorna 
}                                                       // o resultado da função 'compara_horario'.
