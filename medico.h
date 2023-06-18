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
 
 * medico.h
 * Contém a definição do tipo medico e os protótipos de suas funções 
 * que serão utilizadas na solução do 2º trabalho prático.
 */

/* Verifica se a biblioteca foi incluida utilizando a constante.
 * E define a constante, caso ela não esteja incluida.    */
#ifndef _MEDICO_H
#define _MEDICO_H

/* Define uma constante com o identificador ARQ_MEDICOS de texto "Medicos.dat"
 * (que será usado para nomear o arquivo).                */
#define ARQ_MEDICOS "Medicos.dat"

/* Define uma estrutura e nomeia o tipo como 'medico'.
 * Essa estrutura contém três membros, sendo eles:
 * cod_medico - que armazena um valor inteiro.
 * nome - que armazena até 41 caracteres.
 * especialidade - que armazena até 31 caracteres.       */
typedef struct {
    int  cod_medico;
    char nome[41];
    char especialidade[31];
} medico;

/* Função para cadastrar um novo medico */
void cadastrar_medico();

/* Função para listar todos os médicos */
void listar_medicos();

#endif // Finaliza o ifndef.