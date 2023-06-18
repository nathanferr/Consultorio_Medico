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
 * trabalhopratico2.c
 * Contém a função principal que irá utilizar as funções implementadas  
 * em 'medico.c', 'paciente.c' e 'consulta.c', onde os protótipos se 
 * encontram no arquivo de cabecalho medico.h, paciente.h e consulta.h,
 * para solução do 2º trabalho prático usando makefile.
 */

#include <stdio.h>

/* Inclui os arquivos de cabeçalhos medico.h, paciente.h
 * consulta.h que contém os protótipos das funções e os 
 * tipos de estruturas medico, paciente e consulta. */
#include "medico.h"
#include "paciente.h"
#include "consulta.h"

/* Define as opções do menu apresentadas para o
 * usuário através de um tipo de enumeração 'enum'.
 * indo do 0 até  6 respectivamente. */
enum opcoes_menu { SAIR, 
                   CADASTRAR_MEDICO, 
                   LISTAR_MEDICOS, 
                   CADASTRAR_PACIENTE, 
                   LISTAR_PACIENTES, 
                   CADASTRAR_CONSULTA, 
                   LISTAR_CONSULTAS };

int main()
{

    int op;        // <- Declara uma variável do tipo inteiro que recebe a opção informada pelo usuário.
    do {
        printf("\nCONSULTORIO MEDICO\n");
        printf("<%d> Cadastrar um medico\n", CADASTRAR_MEDICO);
        printf("<%d> Listar todos os medicos\n", LISTAR_MEDICOS);
        printf("<%d> Cadastrar um paciente\n", CADASTRAR_PACIENTE);
        printf("<%d> Listar todos os pacientes\n", LISTAR_PACIENTES);
        printf("<%d> Cadastrar uma consulta\n", CADASTRAR_CONSULTA);
        printf("<%d> Listar as consultas de um medico\n", LISTAR_CONSULTAS);
        printf("<%d> Sair do programa\n", SAIR);
        printf("Opcao: ");
        scanf("%d", &op);

        /* Usa o 'switch' para verificar a opção informada pelo usuário
         * Chamando sua função de acordo com a opção. Caso não for uma
         * opção válida é realizado 'default' que imprime uma mensagem
         * de erro. */
        switch (op) {
            case CADASTRAR_MEDICO:
                cadastrar_medico();
                break;
            case LISTAR_MEDICOS:
                listar_medicos();
                break;
            case CADASTRAR_PACIENTE:
                cadastrar_paciente();
                break;
            case LISTAR_PACIENTES:
                listar_pacientes();
                break;
            case CADASTRAR_CONSULTA:
                cadastrar_consulta();
                break;
            case LISTAR_CONSULTAS:
                listar_consultas();
                break;
            case SAIR:
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (op != SAIR); // <- Enquanto não for informado a opção sair, no caso (0), o laço continua 
                          // sendo realizado.
    return 0;
}