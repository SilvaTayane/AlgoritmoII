#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_PESSOAS 50
typedef struct {
    char nome[30];
    char telefone[4];
    char email[30];
    char data[10];
    char cpf[12];
    int id;
} Agenda;

void menu();
void cadastrar();
void editar();
void excluir();
void consultar();

int main()
{
    menu();
    return 0;
}

void salvarEmArquivo(Agenda *cadastros, int quantidade) {
    Agenda pessoa[MAX_PESSOAS];
    FILE *arquivo = fopen("cadastros.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "ID: %d\n", pessoa[i].id);
        fprintf(arquivo, "Nome: %s\n", pessoa[i].nome);
        fprintf(arquivo, "Data de nascimento: %s\n", pessoa[i].data);
        fprintf(arquivo, "CPF: %s\n", pessoa[i].cpf);
        fprintf(arquivo, "Email: %s\n", pessoa[i].email);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void menu() {
    int opcao;
    do {
        // Menu
        printf("=========Agenda Telefônica=========\n");
        printf("|1| Cadastrar\n");
        printf("|2| Editar\n");
        printf("|3| Excluir\n");
        printf("|4| Consultar\n");
        printf("|5| Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                editar();
                break;
            case 3:
                excluir();
                break;
            case 4:
                consultar();
                break;
            case 5:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

int validarCPF(const char *cpf) {
    int i;
    int digito1 = 0, digito2 = 0;

    for (i = 0; i < 9; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
        digito1 += (10 - i) * (cpf[i] - '0');
        digito2 += (11 - i) * (cpf[i] - '0');
    }

    digito1 = (digito1 % 11) < 2 ? 0 : 11 - (digito1 % 11);
    digito2 += digito1 * 2;
    digito2 = (digito2 % 11) < 2 ? 0 : 11 - (digito2 % 11);

    return (cpf[9] - '0' == digito1) && (cpf[10] - '0' == digito2);
}
int validarEmail(const char *email) {
    int i;
    int temArroba = 0;
    int temPonto = 0;

    for (i = 0; i < strlen(email); i++) {
        if (email[i] == '@')
            temArroba = 1;
        if (email[i] == '.')
            temPonto = 1;
    }

    return temArroba && temPonto;
}
int validarData(const char *data) {
    int i;
    int dia, mes, ano;
    char copiaData[11];
    strcpy(copiaData, data);

    if (strlen(copiaData) != 10)
        return 0;

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (copiaData[i] != '/')
                return 0;
        } else {
            if (!isdigit(copiaData[i]))
                return 0;
        }
    }

    dia = atoi(strtok(copiaData, "/"));
    mes = atoi(strtok(NULL, "/"));
    ano = atoi(strtok(NULL, "/"));

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2023)
        return 0;

    return 1;
}

void cadastrar(){
    Agenda pessoa[MAX_PESSOAS];
    int op_2, op_3;
    char cpf[12], email[100], data[11];
    int quantidade=0;
    
    do{
        printf("---- Cadastrar ----\n|1| Pessoa\n|2| Telefone\n|3| Retornar\nEscolha uma opção: ");
        scanf("%d", &op_2);
        if (op_2 == 1){
            printf("Nome: ");
            scanf("%s", pessoa[quantidade].nome);

            do{
                printf("Data de nascimento (dd/mm/YYYY): ");
                scanf("%s", data);
                    if(validarData(data))
                        strcpy(pessoa[quantidade].data,data);
                    else
                        printf("Data de nascimento invalida! Tente novamente.");
            }while(!validarData(data));
            
            do{
                printf("CPF: ");
                scanf("%s", cpf);
                    if(validarCPF)
                        strcpy(pessoa[quantidade].cpf,cpf);
                    else
                        printf("CPF invalido! Tente novamente.\n");
            }while(!validarCPF);
            
            do{
                printf("Email: ");
                scanf("%s", email);
                if (validarEmail(email))
                    strcpy(pessoa[quantidade].email, email);
                else
                    printf("Email invalido! Tente novamente.\n");
            }while(!validarEmail(email));
            // Atribui um ID em ordem crescente
           pessoa[quantidade].id = quantidade + 1;

        // Incrementa a quantidade de pessoas
            quantidade++;
            printf("\nCadastro realizado com sucesso!!\n");
            salvarEmArquivo(pessoa, quantidade);
            
        }else if(op_2 == 2){
            int i=0;
            printf("---- Telefone ----\nComo deseja realizar a pesquisa:\n");
            printf("|1| Nome\n|2| IDPessoa");
            scanf("%d", &op_3);
            if(op_2==1){
                
            }
            salvarEmArquivo(pessoa, quantidade);
        }else if(op_2 == 3){
            menu();
        }
    }while (op_2 < 1 || op_2 > 3);
}
void editar(){
    int op_4;
    
    printf("Como deseja realizar a pesquisa:\n");
    printf("|1| Nome\n|2| IDPessoa");
    scanf("%d", &op_4);
    
    if(op_4==1){
        
    }else if(op_4==2){
        
    }
    
    
    
}
void excluir(){
    
}
void consultar(){
    
}

