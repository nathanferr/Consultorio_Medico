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
 * medico.c
 * Contém as implementações das funções que se encontram no arquivo de 
 * cabeçalho medico.h para solução do 2º trabalho prático. 
 */

/* Inclui o arquivo de cabeçalho medico.h que contém os
 * protótipos das funções e o tipo de estrutura medico. */
#include "medico.h"

#include <stdio.h>

/* Função para cadastrar um medico */
void cadastrar_medico()
{
    /* Declara uma variável local do tipo medico (Estrutura para armazenar dados) 
     * e um ponteiro do tipo FILE (Para apontar para um arquivo) */
    medico m;
    FILE *arq;

    /* Abre o arquivo binário ARQ_MEDICOS para anexo e verifica se há algum erro de 
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq = fopen(ARQ_MEDICOS, "ab")) == NULL){ 
        fprintf(stderr, "Erro de abertura do arquivo %s!", ARQ_MEDICOS);
        return;
    }
    fseek(arq, 0, SEEK_END);                            // <- Desloca o indicador de posição para o final do arquivo.
    printf("\nNovo medico\n");
    m.cod_medico = (ftell(arq) / sizeof(m)) + 1;    // <- O codigo do médico é gerado automaticamente somando
    printf("Codigo: %d\n", m.cod_medico);           // um ao número de médicos cadastrados e atribuindo o valor
    printf("Nome: ");                               // ao 'cod_medico' da variável 'm'.
    scanf(" %40[^\n]", m.nome);
    printf("Especialidade: ");
    scanf(" %30[^\n]", m.especialidade);
    fwrite(&m, sizeof(m), 1, arq);                  // <- Escreve o conteúdo da variável 'm' no arquivo binário 
                                                    // apontado por arq.
    fclose(arq);                                    // <- 'fclose' fecha o arquivo e salva as alterações.
    printf("\nMedico castrado com sucesso!\n");     // <- mensagem de confirmação de cadastro.
}

 /* Função para listar todos os medicos */
void listar_medicos()
{
    /* Declara uma variável local do tipo medico (Estrutura para armazenar dados) 
     * e um ponteiro do tipo FILE (Para apontar para um arquivo). */
    medico m;
    FILE *arq;

    /* Abre o arquivo binário ARQ_MEDICOS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq = fopen(ARQ_MEDICOS, "rb")) == NULL){ 
        fprintf(stderr, "\nNao ha' nenhum medico cadastrado.\n");
        return;
    }
    
    printf("\n\tMedicos cadastrados\n");
    printf("---------------------------------------------\n");
    printf("Cod. Nome                      Especialidade\n");
    printf("---------------------------------------------\n");

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq' e
     * armazena seu conteúdo na variavel 'm' enquanto não chegar ao 
     * final do arquivo (que retorna -1 quando chegar, saindo do laço). */
    while (fread(&m, sizeof(m), 1, arq) > 0) {
        printf("%04d %-25.25s %-15.15s\n", m.cod_medico, m.nome,            // <- Utiliza variavel 'm' que foi lida no
                                           m.especialidade);                // arquivo e imprimi os membros dela.
                                           
    }
    printf("---------------------------------------------\n");
    fclose(arq);                                        // <- 'fclose' fecha o arquivo.
}
