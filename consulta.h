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

 * consulta.h
 * Contém a definição do tipo consulta e os protótipos de suas funções 
 * que serão utilizadas na solução do 2º trabalho prático.
 */

/* Verifica se a biblioteca foi incluida utilizando a constante.
 * E define a constante, caso ela não esteja incluida. */
#ifndef _CONSULTA_H
#define _CONSULTA_H

/* Inclui os arquivos de cabeçalho my_date.h, paciente.h, medico.h que
 * contém os protótipos das funções e os tipos de estruturas de cada um. */
#include "my_date.h"
#include "paciente.h"
#include "medico.h"

#include <stdbool.h>

/* Define uma constante com o identificador ARQ_CONSULTAS de texto 
 * "Consultas.dat" (que será usado para nomear o arquivo). */
#define ARQ_CONSULTAS "Consultas.dat"

/* Define uma estrutura e nomeia o tipo como 'consulta'.
 * Essa estrutura contém cinco membros, sendo eles:
 * num_prontuario - que armazena um valor inteiro.
 * data_consulta - que armazena uma estrutura do tipo 'data'.
 * hora_consulta - que armazena uma estrutura do tipo 'horario'. 
 * cod_medico - que armazena um valor inteiro.
 * cod_paciente - que armazena um valor inteiro. */
typedef struct {
    int num_prontuario;
    data data_consulta;
    horario hora_consulta;
    int cod_medico;
    int cod_paciente;
} consulta;

/* Função para cadastrar uma consulta. */
void cadastrar_consulta();

/* Função para mostrar as consultas de um medico numa data/horario. */
void listar_consultas();

/* Função que valida a data e o horário de uma consulta. */
static bool valida_data_horario(consulta);

/* Função que gera um arquivo com as consultas de um medico 
 * listado na função listar_consultas. */
void gerar_listagem(data, int);

#endif // Finaliza o ifndef.