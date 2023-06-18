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
 * paciente.c
 * Contém as implementações das funções que se encontram no arquivo de 
 * cabeçalho paciente.h para solução do 2º trabalho prático. 
 */

/* Inclui o arquivo de cabeçalho paciente.h que contém os
 * protótipos das funções e o tipo de estrutura paciente. */
#include "paciente.h"

#include <ctype.h>
#include <stdio.h>

/* Função para cadastrar um paciente */
void cadastrar_paciente()
{   
    /* Declara uma variável local do tipo paciente (Estrutura para armazenar dados) 
     * e um ponteiro do tipo FILE (Para apontar para um arquivo) */
    paciente p;                                                             
    FILE *arq;

    /* Abre o arquivo binário ARQ_PACIENTES para anexo e verifica se há algum erro de 
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq = fopen(ARQ_PACIENTES, "ab")) == NULL){ 
        fprintf(stderr, "Erro de abertura do arquivo %s!", ARQ_PACIENTES);
        return;
    }

    fseek(arq, 0, SEEK_END);                            // <- Desloca o indicador de posição para o final do arquivo.
     
    printf("\nNovo paciente\n");      
    p.cod_paciente = (ftell(arq) / sizeof(p)) + 1;  // <- O codigo do paciente é gerado automaticamente                                
    printf("Codigo: %d\n", p.cod_paciente);         // somando um ao numero de pacientes cadastrados e 
    printf("Nome: ");                               // atribuindo o valor ao 'cod_paciente' da variável 'p'.
    scanf(" %40[^\n]", &p.nome);
    printf("Sexo (M|F): ");
    scanf(" %c", &p.sexo);
    p.sexo = toupper(p.sexo);                      // <- Transforma o caractere em maiúsculo.

    while (p.sexo != 'M' && p.sexo != 'F') {       // <- Enquanto não for informado o caractere M ou F
        printf("Erro: sexo invalido!\n");          // <- será impresso uma mensagem de erro e uma
        printf("Sexo (M|F): ");                    // <- mensagem para ser informado novamente o caractere.
        scanf(" %c", &p.sexo);
        p.sexo = toupper(p.sexo);                  // <- Transforma o caractere informado em maiúsculo.
    }
    
    printf("Idade: ");
    scanf("%d", &p.idade);
    fwrite(&p, sizeof(p), 1, arq);                 // <- Escreve o conteúdo da variável 'p' no arquivo 
                                                    // binário apontado por arq.
    fclose(arq);                                   // <- 'fclose' fecha o arquivo e salva as alterações.
    printf("\nPaciente castrado com sucesso!\n");  // <- Imprime uma mensagem de confirmação de cadastro.

}

/* Função para listar todos os pacientes */
void listar_pacientes(int n_pacientes, const paciente pacientes[])
{
    /* Declara uma variável local do tipo paciente (Estrutura para armazenar dados) 
     * e um ponteiro do tipo FILE (Para apontar para um arquivo) */
    paciente p;
    FILE *arq;

    /* Abre o arquivo binário ARQ_PACIENTES como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq = fopen(ARQ_PACIENTES, "rb")) == NULL){ 
        fprintf(stderr, "\nNao ha' nenhum paciente cadastrado.\n");
        return;
    }

    printf("\n\tPacientes cadastrados\n");
    printf("----------------------------------------\n");
    printf("Cod. Nome                     Sexo Idade\n");
    printf("----------------------------------------\n");
    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq' e
     * armazena seu conteúdo na variavel 'p' enquanto não chegar ao 
     * final do arquivo (que retorna -1 quando chegar, saindo do laço). */
    while(fread(&p, sizeof(p), 1, arq) > 0){
        printf("%04d %-25.25s  %c  %3d\n",  p.cod_paciente, p.nome,          // <- Utiliza variavel 'p' que foi lida no
                                            p.sexo, p.idade);                // arquivo e imprimi os membros dela.
    }
    printf("----------------------------------------\n");   
    fclose(arq);                                       // <- 'fclose' fecha o arquivo.
}
