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
 * consulta.c
 * Contém as implementações das funções que se encontram 
 * no arquivo de cabeçalho consulta.h para solução do 2º 
 * trabalho prático.
 */

/* Inclui o arquivo de cabeçalho consulta.h que contém os
 * protótipos das funções e os tipo de estrutura consulta. */
#include "consulta.h"

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Função que valida a data e o horário de uma consulta. A
 * função é definida como static pois so é usada dentro
 * deste módulo e recebe como parâmetro uma variável
 * constante do tipo consulta. */
static bool valida_data_horario(const consulta c)
{
    /* Declara uma variável local do tipo consulta (Estrutura para armazenar dados) 
     * e um ponteiro do tipo FILE (Para apontar para um arquivo) */
    FILE *arq_consultas;
    consulta consultas;

    /* Abre o arquivo binário ARQ_CONSULTAS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. 
     * Se não houver erro, entra no bloco else.*/
    if((arq_consultas = fopen(ARQ_CONSULTAS, "rb")) == NULL) { 
        fprintf(stderr, "Erro de abertura do arquivo %s!", ARQ_CONSULTAS);
    } else {

        /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_consultas'
         * e armazena seu conteúdo na variavel 'consultas' enquanto não chegar ao 
         * final do arquivo (que retorna -1 quando chegar, saindo do laço). */
        while (fread(&consultas, sizeof(consultas), 1, arq_consultas) > 0) {

            /* Compara o cod_medico do arquivo com o cod_medico informado pelo usuário, 
             * é feito o mesmo processo com o cod_paciente. Após isso, compara a data e  
             * o horário do arquivo com o informado pelo usuário. Se as duas condições 
             * forem satisfeitas retorna 'false' (significa que já existe uma consulta 
             * para o paciente ou para o médico nesta data e horário). */
            if ((consultas.cod_medico == c.cod_medico || consultas.cod_paciente == c.cod_paciente) 
                && compara_data_horario(consultas.data_consulta, consultas.hora_consulta,
                                        c.data_consulta, c.hora_consulta) == 0) {
                return false;
            }
        }
        fclose(arq_consultas);                          // <- 'fclose' fecha o arquivo.
        return true;                                    // <- Retorna verdadeiro se não existir uma consulta 
    }                                                   // para o paciente ou para o médico nesta data e horário.
}

/* Função para cadastrar uma consulta. */ 
void cadastrar_consulta()
{
    /* Declara três variáveis locais, são elas, 'c' do tipo 'consulta', 
     * 'm' do tipo 'medico' e 'p' do tipo 'paciente' (Estruturas para 
     * armazenar dados) e ponteiros do tipo FILE (que aponta para cada  
     * arquivo que será aberto). */
    FILE *arq_medicos, *arq_pacientes, *arq_consultas;
    consulta c;
    medico m;
    paciente p;
    
    /* Abre o arquivo binário ARQ_MEDICOS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if ((arq_medicos = fopen(ARQ_MEDICOS, "rb")) == NULL) {
        fprintf(stderr, "\nErro: Nao ha' nenhum medico cadastrado!\n");           // <- mensagem de erro.
        return;
    }

    /* Abre o arquivo binário ARQ_PACIENTES como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if ((arq_pacientes = fopen(ARQ_PACIENTES, "rb")) == NULL) {
        fprintf(stderr, "\nErro: Nao ha' nenhum paciente cadastrado!\n");        // <- mensagem de erro.
        fclose(arq_medicos);                                                     // <- 'fclose' fecha o arquivo.
        return;
    }

    /* Abre o arquivo binário ARQ_CONSULTAS para anexo e verifica se há algum erro de 
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_consultas = fopen(ARQ_CONSULTAS, "ab")) == NULL) { 
        fprintf(stderr, "Erro de abertura do arquivo %s!", ARQ_CONSULTAS);      // <- mensagem de erro.
        fclose(arq_pacientes);                                                  // <- 'fclose' fecha o arquivo.
        fclose(arq_medicos);                                                    // <- 'fclose' fecha o arquivo.  
        return;
    } 
    fseek(arq_consultas, 0, SEEK_END);                  // <- Modifica o indicador de posição para o final do arquivo.
    fseek(arq_medicos, 0, SEEK_END);                // <- Modifica o indicador de posição para o final do arquivo.
    fseek(arq_pacientes, 0, SEEK_END);              // <-                            ''

    /* Declara cinco variáveis locais do tipo inteiro, sendo que 'n_medico' e 'n_pacientes' recebe 
        * como valor o retorno da função 'ftell' dividido pelo tamanho de sua estrutura (retorno de
        * sizeof), ou seja, recebe o número de médicos ou pacientes listados no arquivo. E as outras
        * variáveis tem como propósito guardar o código do médico e do paciente informado pelo usuário, 
        * já o sair é uma variável auxiliar. */
    int n_medicos = (ftell(arq_medicos) / sizeof(m));
    int n_pacientes = (ftell(arq_pacientes) / sizeof(p));
    int cod_medico, cod_paciente, sair;
    printf("\nNova consulta\n");
    c.num_prontuario = (ftell(arq_consultas) / sizeof(c)) + 1;  // <- O codigo do prontuário é gerado automaticamente somando
    printf("Numero do prontuario: %d\n", c.num_prontuario);     // um ao numero de consultas cadastrados e atribuindo o valor
    printf("Codigo do medico (1 a %d): ", n_medicos);           // ao 'num_prontuario' da variável 'c'.
    scanf("%d", &cod_medico);
    
    /* Enquanto não for informado um código de médico válido será impresso
        * uma mensagem de erro solicitando para que seja informado novamente o
        * código ou que seja informado -1 para encerrar a função. */
    while (cod_medico < 1 || cod_medico > n_medicos) {          
        printf("Erro: codigo invalido!\n");
        printf("Codigo do medico (1 a %d ou -1 p/ cancelar): ", n_medicos);
        scanf("%d", &cod_medico);
        if (cod_medico == -1) {                                 // <- Caso seja informado -1
            return;                                             // o cadastrado é cancelado.
        }
    }

    /* Desloca o indicador de posição do começo do arquivo para a posição
        * do médico informada pelo usuário. */
    fseek(arq_medicos, (cod_medico - 1) * sizeof(m), SEEK_SET); 

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_medicos' 
        * e armazena seu conteúdo na variavel 'm'. */ 
    fread(&m, sizeof(m), 1, arq_medicos);

    /* Atribui o código informado pelo usuário ao código da variável 'c'. */
    c.cod_medico = cod_medico;                                
    printf("Nome do medico: %s\n", m.nome);
    printf("Codigo do paciente (1 a %d): ", n_pacientes);
    scanf("%d", &cod_paciente);

    /* Enquanto não for informado um código de paciente válido será impresso
        * uma mensagem de erro solicitando para que seja informado novamente o
        * código ou que seja informado -1 para encerrar a função. */
    while (cod_paciente < 1 || cod_paciente > n_pacientes) {
        printf("Erro: codigo invalido!\n");
        printf("Codigo do paciente (1 a %d ou -1 p/ cancelar): ", n_pacientes);
        scanf("%d", &cod_paciente);
        if (cod_paciente == -1) {                               // <- Caso seja informado -1
            return;                                             // o cadastrado é cancelado.
        }
    }

    /* Desloca o indicador de posição do começo do arquivo para a posição
        * do paciente informada pelo usuário. */
    fseek(arq_pacientes, (cod_paciente - 1) * sizeof(p), SEEK_SET);

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_pacientes' 
        * e armazena seu conteúdo na variavel 'p'. */ 
    fread(&p, sizeof(p), 1, arq_pacientes);

    /* Atribui o código informado pelo usuário ao código da variável 'c'. */
    c.cod_paciente = cod_paciente;
    printf("Nome do paciente: %s\n", p.nome);

    /* Chama a função le_data_horario, passando por parâmetro uma mensagem inforamtiva
        * e o endereço de 'data_consulta' e 'hora_consulta' "(Para alteracoes)". */
    le_data_horario("Informe a data e horario da consulta", &c.data_consulta, &c.hora_consulta); 

    /* Enquanto o retorno da função booleana não for verdadeira (significa que a data e horário
        * informada pelo usuário são iguais), será impresso uma mensagem de erro e uma mensagem
        * perguntando ao usuário se desejar continuar o cadastro da consulta, caso o usuário
        * informe -1, a funcao se encerra. Caso informe qualquer outro numero é chamada 
        * novamente a função le_data_horario. */
    while (!valida_data_horario(c)) {
        printf("\nErro: Ja' existe uma consulta para este medico ou paciente neste horario!\n");
        printf("Digite um numero qualquer p/ continuar ou (-1) p/ encerrar: ");
        scanf("%d", &sair);
        if (sair == -1) {
            return;
        }                    
        le_data_horario("Informe a data e horario da consulta", &c.data_consulta, &c.hora_consulta);
    }

    fwrite(&c, sizeof(c), 1, arq_consultas);                    // <- Escreve o conteúdo da variável 'c' no arquivo 
                                                                // binário apontado por arq_consultas.
    printf("\nConsulta cadastrada com sucesso!\n");             // <-  mensagem de confirmação de cadastro.
    fclose(arq_consultas);                                      // <- 'fclose' fecha o arquivo e salva as alterações.
    fclose(arq_medicos);                                        // <- 'fclose' fecha o arquivo.
    fclose(arq_pacientes);                                      // <- 'fclose' fecha o arquivo.
}

/* Função para mostrar as consultas de um medico numa data/horario. */
void listar_consultas()
{
    /* Declara três variáveis locais do tipo FILE (que aponta para cada  
     * arquivo que será aberto). */
    FILE *arq_consultas, *arq_medicos, *arq_pacientes;
        
    /* Abre o arquivo binário ARQ_CONSULTAS para anexo e verifica se há algum erro de 
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_consultas = fopen(ARQ_CONSULTAS, "rb")) == NULL){ 
        fprintf(stderr, "\nNao ha' nenhuma consulta cadastrada!\n");
        return; 
    }

    /* Abre o arquivo binário ARQ_MEDICOS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_medicos = fopen(ARQ_MEDICOS, "rb")) == NULL){ 
        fprintf(stderr, "\nErro de abertura do arquivo %s!\n", ARQ_MEDICOS);
        fclose(arq_consultas);                         // <- 'fclose' fecha o arquivo.
        return;
    }
    
    /* Abre o arquivo binário ARQ_PACIENTES como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_pacientes = fopen(ARQ_PACIENTES, "rb")) == NULL){ 
        fprintf(stderr, "\nErro de abertura do arquivo %s!\n", ARQ_PACIENTES);
        fclose(arq_consultas);                          // <- 'fclose' fecha o arquivo.
        fclose(arq_medicos);                            // <- 'fclose' fecha o arquivo.
        return;
    }
    
    /* Declara quatro variáveis locais, são elas, 'c' do tipo 'consulta', 
     * 'm' do tipo 'medico', 'p' do tipo 'paciente' e 'dt' do tipo 'data'
     * (Estruturas para armazenar dados). */
    consulta c;
    medico m;
    paciente p;
    data dt;

    /* Declara duas variáveis, uma do tipo inteiro, que tem como propósito 
     * guardar o código do médico informado pelo usuário, e uma do tipo char
     * que tem como propósito guardar a resposta do usuário para ser verificada. */
    int cod_medico;
    char ch;

    fseek(arq_medicos, 0, SEEK_END);                    // <- Modifica o indicador de posição para o final do arquivo.

    /* 'n_medicos' recebe  como valor o retorno da função 'ftell' dividido
     * pelo tamanho de sua estrutura (retorno de sizeof), ou seja, recebe
     * o número de médicos listados no arquivo (apontado por arq_medicos). */
    int n_medicos = ftell(arq_medicos) / sizeof(m);
    
    printf("\nConsultas de um medico\n");
    printf("Codigo do medico (1 a %d): ", n_medicos);
    scanf("%d", &cod_medico);

    /* Enquanto não for informado um código de médico válido será impresso
     * uma mensagem de erro solicitando para que seja informado novamente o
     * código ou que seja informado -1 para encerrar a função. */
    while (cod_medico < 1 || cod_medico > n_medicos) {
        printf("Erro: codigo invalido!\n");
        printf("Codigo do medico (1 a %d ou -1 p/ cancelar): ", n_medicos);
        scanf("%d", &cod_medico);
        if (cod_medico == -1) {                         // <- Caso seja informado -1
            return;                                     // o cadastrado é cancelado.
        }
    }

    /* Desloca o indicador de posição do começo do arquivo para a posição
     * do médico informada pelo usuário. */
    fseek(arq_medicos, (cod_medico - 1) * sizeof(m), SEEK_SET);

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_medicos' 
     * e armazena seu conteúdo na variavel 'm'. */ 
    fread(&m, sizeof(m), 1, arq_medicos);
    printf("Nome do medico: %s\n", m.nome);

    /* Chama a função le_data, passando por parâmetro uma mensagem inforamtiva
     * e o endereço de 'dt' (Para alterações). */
    le_data("Data das consultas", &dt);
    printf("\nConsultas de %s no dia ", m.nome);
    imprime_data(dt);
    printf("\n-----------------------------------\n");
    printf("#Pront. Paciente            Horario\n");
    printf("-----------------------------------\n");

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_consultas' e
     * armazena seu conteúdo na variavel 'c' enquanto não chegar ao final do
     * arquivo (que retorna -1 quando chegar, saindo do laço). */
    while (fread(&c, sizeof(c), 1, arq_consultas) > 0) { 

        /* Compara o cod_medico do arquivo com o cod_medico informado pelo usuário. 
         * Após isso, compara a data informada pelo usuário. Se as duas condições 
         * forem satisfeitas, entra no bloco if. */
        if (c.cod_medico == cod_medico && compara_data(c.data_consulta, dt) == 0) {

            /* Desloca o indicador de posição do começo, do arquivo, para a posição
             * do paciente cadastrado, na consulta da data informada. */
            fseek(arq_pacientes, (c.cod_paciente - 1) * sizeof(p), SEEK_SET);

            /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_pacientes' 
             * e armazena seu conteúdo na variavel 'p'. */ 
            fread(&p, sizeof(p), 1, arq_pacientes); 
            printf("%06d  %-20.20s ", c.num_prontuario, p.nome);
            imprime_horario(c.hora_consulta);
            printf("\n");
        } 
    }
    printf("\nDeseja armazenar essa listagem em arquivo de texto? (S|N): ");

    do {     
        scanf(" %c", &ch);
        ch = toupper(ch);                     // <- Transforma o caractere informado em maiúsculo.
        if(ch != 'S' && ch != 'N'){                               // <- Se não for infarmado nenhuma das opções
            printf("\nErro: Opcao invalida.\nInforme (S|N): ");   // <- será impresso uma mensagem de erro e uma
        }                                                         // mensagem para ser informado novamente o caractere.
    } while(ch != 'S' && ch != 'N');          // <- Enquanto não for informado o caractere S ou N o laço 'do' se repete.
                                                    
    if(ch == 'S') {                           // <- Se for informado 'S', é chamada a funcao gerar arquivo
        gerar_listagem(dt, cod_medico);       // e passa como parâmetro 'dt' e o 'cod_medico'.
    }
    fclose(arq_consultas);                    // <- 'fclose' fecha o arquivo.
    fclose(arq_medicos);                      // <- 'fclose' fecha o arquivo.
    fclose(arq_pacientes);                    // <- 'fclose' fecha o arquivo.
    printf("\n-------------------------------------\n");
        
}     

/* Função que gera um arquivo com as consultas de um medico 
 * listado na função listar_consultas. Recebe como parâmetro
 * uma variável do tipo data e um inteiro. */
void gerar_listagem(data dt, int cod_medico)
{
    /* Declara quatro variáveis locais do tipo FILE (que aponta para cada  
     * arquivo que será aberto). */
    FILE *arq_consultas, *arq_medicos, *arq_pacientes, *arq_listagem;

    /* Declara três variáveis locais, são elas, 'c' do tipo 'consulta', 
     * 'm' do tipo 'medico' e 'p' do tipo 'paciente'(Estruturas para 
     * armazenar dados). */
    consulta c;
    medico m;
    paciente p;

    /* Declara um vetor de caracteres de tamanho 41 para 
     * guardar o nome do arquivo informado pelo usuário. */
    char nome_arq[41];

    /* Abre o arquivo binário ARQ_CONSULTAS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_consultas = fopen(ARQ_CONSULTAS, "rb")) == NULL){ 
        fprintf(stderr, "\nNao ha' nenhuma consulta cadastrada.\n");
        return;
    }

    /* Abre o arquivo binário ARQ_MEDICOS como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_medicos = fopen(ARQ_MEDICOS, "rb")) == NULL){ 
        fprintf(stderr, "\nErro na abertura do arquivo!\n");
        fclose(arq_consultas);                          // <- 'fclose' fecha o arquivo.
        return;
    }

    /* Abre o arquivo binário ARQ_PACIENTES como leitura e verifica se há algum erro de
     * abertura. Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_pacientes = fopen(ARQ_PACIENTES, "rb")) == NULL){ 
        fprintf(stderr, "\nErro na abertura do arquivo!\n");
        fclose(arq_consultas);                          // <- 'fclose' fecha o arquivo.
        fclose(arq_medicos);                            // <- 'fclose' fecha o arquivo.
        return;
    }

    printf("\nInforme o nome do arquivo que ira guardar a listagem (.txt): ");
    scanf(" %40[^\n]", nome_arq);

    /* Cria uma constante do tipo char, e atribui a ele
     * a string ".txt" para comparação do nome do
     * arquivo. */
    const char *ch = ".txt";

    /* Cria um laço for com duas variaveis: 'i' que inicializa com a ultima posição
     * do caractere do 'nome_arq' e 'j' inicializa com a ultima posição de 'ch' e
     * compara os caracteres das posições de cada um ate chegar na primeira posição
     * de 'ch'. Se forem diferentes concatena 'ch' no 'nome_arq', ou seja, se não for
     * informado a extensão (.txt) do arquivo ele a completa. */
    for(int i = strlen(nome_arq) - 1, j = 3; i > (strlen(nome_arq) - 1) - 4, j >= 0; i--, j--){
        if(nome_arq[i] != ch[j]){
            strcat(nome_arq, ch);
            break;       
        }
    }

    /* Cria e abre um arquivo de texto como escrita e verifica se há algum erro de abertura.
     * Se houver erro, apresenta uma mensagem de erro e a função se encerra. */
    if((arq_listagem = fopen(nome_arq, "w")) == NULL){
        fprintf(stderr, "\nErro na abertura do arquivo\n");
        return;
    }
    
    
    /* Desloca o indicador de posição do começo do arquivo para a posição
     * do médico informada pelo usuário que foi passado pelo parâmetro. */ 
    fseek(arq_medicos, (cod_medico - 1) * sizeof(m), SEEK_SET);

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_medicos' 
     * e armazena seu conteúdo na variavel 'm'. */ 
    fread(&m, sizeof(m), 1, arq_medicos);

    /* 'fprintf' imprime em 'arq_listagem' (Arquivo de texto). */
    fprintf(arq_listagem,"Consultas de %s no dia ", m.nome);
    fprintf(arq_listagem,"%02d/%02d/%4d", dt.dia, dt.mes, dt.ano);
    fprintf(arq_listagem,"\n-----------------------------------\n");
    fprintf(arq_listagem,"#Pront. Paciente            Horario\n");
    fprintf(arq_listagem,"-----------------------------------\n");

    /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_consultas' e
     * armazena seu conteúdo na variavel 'c' enquanto não chegar ao final do
     * arquivo (que retorna -1 quando chegar, saindo do laço). */
    while (fread(&c, sizeof(c), 1, arq_consultas) > 0) { 

        /* Compara o cod_medico do arquivo com o cod_medico informado pelo usuário. 
         * Após isso, compara a data informada pelo usuário. Se as duas condições 
         * forem satisfeitas, entra no bloco if. */
        if (c.cod_medico == cod_medico && compara_data(c.data_consulta, dt) == 0) {

            /* Desloca o indicador de posição do começo, do arquivo, para a posição
             * do paciente cadastrado, na consulta da data informada. */
            fseek(arq_pacientes, (c.cod_paciente - 1) * sizeof(p), SEEK_SET);

            /* 'fread' lê a estrutura do arquivo apontado pelo ponteiro 'arq_pacientes' 
             * e armazena seu conteúdo na variavel 'p'. */ 
            fread(&p, sizeof(p), 1, arq_pacientes);

            /* 'fprintf' imprime em 'arq_listagem' (Arquivo de texto). */
            fprintf(arq_listagem,"%06d  %-20.20s ", c.num_prontuario, p.nome);
            fprintf(arq_listagem,"%02d:%02d\n", c.hora_consulta.horas, c.hora_consulta.minutos);
        } 
    }
    fclose(arq_listagem);                               // <- 'fclose' fecha o arquivo e salva as alterações.
    fclose(arq_consultas);                              // <- 'fclose' fecha o arquivo.
    fclose(arq_medicos);                                // <- 'fclose' fecha o arquivo.
    fclose(arq_pacientes);                              // <- 'fclose' fecha o arquivo.
    printf("\nArquivo \"%s\" gerado com sucesso!\n", nome_arq);          // <- Imprime uma mensagem de confirmação da criação do arquivo.
}
