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
 * paciente.h
 * Contém a definição do tipo paciente e os protótipos de suas funções 
 * que serão utilizadas na solução do 2º trabalho prático.
 */


/* Verifica se a biblioteca foi incluida utilizando a constante.
 * E define a constante, caso ela não esteja incluida.    */
#ifndef _PACIENTE_H
#define _PACIENTE_H

/* Define uma constante com o identificador ARQ_PACIENTES de texto "Pacientes.dat"
 * (que será usado para nomear o arquivo).                */
#define ARQ_PACIENTES "Pacientes.dat"

/* Define uma estrutura e nomeia o tipo como 'paciente'.
 * Essa estrutura contém quatro membros, sendo eles:
 * cod_paciente - que armazena um valor inteiro.
 * nome - que armazena até 41 caracteres.
 * sexo - que armazena um caractere. 
 * idade - que armazena um valor inteiro.                 */
typedef struct {
    int cod_paciente;
    char nome[41];
    char sexo;
    int idade;
} paciente;

/* Função para cadastrar um paciente */
void cadastrar_paciente();

/* Função para listar todos os pacientes */
void listar_pacientes();

#endif // Finaliza o ifndef.