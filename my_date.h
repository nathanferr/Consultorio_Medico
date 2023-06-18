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
 
 * my_date.h
 * Contém a biblioteca de função, do M.e Ciro C. Trindade, 
 * para tratamento de data e horário que serão utilizadas
 * na solução do 2º trabalho prático.
 */

/* Verifica se a biblioteca foi incluida utilizando a constante.
 * E define a constante, caso ela não esteja incluida.    */
#ifndef _MY_DATE_H
#define _MY_DATE_H

/* Define uma estrutura e nomeia o tipo como 'data'.
 * Essa estrutura contém três membros, sendo eles:
 * dia - que armazena um valor inteiro.
 * mes - que armazena um valor inteiro.
 * ano - que armazena um valor inteiro.                   */
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

/* Define uma estrutura e nomeia o tipo como 'horario'.
 * Essa estrutura contém dois membros, sendo eles:
 * horas - que armazena um valor inteiro.
 * minutos - que armazena um valor inteiro.               */
typedef struct {
    int horas;
    int minutos;
} horario;

/* Funções para impressão de data e horário */
void imprime_data(data);
void imprime_horario(horario);
void imprime_data_horario(data, horario);

/* Funções para a entrada de data e horário */
void le_data(const char *, data *);
void le_horario(const char *, horario *);
void le_data_horario(const char *, data *, horario *);

/* Funções de comparação de data e horário */
int compara_data(data, data);
int compara_horario(horario, horario);
int compara_data_horario(data, horario, data, horario);

/* Macros auxiliares */
/* Transforma a data em um número no formato aaaammdd 
 * 27/05/2021 = 2021 * 10000 + 5 * 100 + 27 = 20210000 + 500 + 27 = 20210527 */
#define data_to_aaaammdd(dt) (dt.ano * 1000000 + dt.mes * 100 + dt.dia)
/* Transforma o horario em minutos
 * 9:30 = 9 * 60 + 30 = 540 + 30 = 570 */
#define horario_to_minutos(h) (h.horas * 100 + h.minutos)

#endif // Finaliza o ifndef.