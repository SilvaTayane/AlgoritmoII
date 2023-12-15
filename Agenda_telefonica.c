#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define INFINITY (1<<20)

//Struct para armazenar as informações do arquivo
typedef struct p{
    int IDPessoa;
    char nome[31];
    char cpf[12];
    char data[11];
    char telefone[12];
    char email[31];
} PESSOA;

//Declarando funções
void menu();
void carregaArquivo();
void imprimeArquivo();
void editaArquivo();
void excluiArquivo();
void cadastraArquivo();
void escreverArquivo();
int ultimoID();
int validarCPF(const char *cpf);
int validarEmail(const char *email);
int validarData(const char *data);
int verificaTelefone(const char *telefone);


PESSOA lista[100];
int cont;
FILE *arquivo;

//Main
int main(){
    menu();
    return 0;
}

//Menu principal
void menu() {
    int opcao;
    carregaArquivo();
    do {
        // Menu
        printf("\n=========Agenda Telefônica=========\n");
        printf("|1| Cadastrar\n");
        printf("|2| Editar\n");
        printf("|3| Excluir\n");
        printf("|4| Consultar\n");
        printf("|5| Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastraArquivo();
                break;
            case 2:
                editaArquivo();
                break;
            case 3:
                excluiArquivo();
                break;
            case 4:
                imprimeArquivo();
                break;
            case 5:
                printf("\nSaindo do programa. Obrigado!\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

//Carregar de arquivo para memoria
void carregaArquivo(){
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");
    //Percorre o arquivo até que encontre o fim do arquivo (EOF)
    //Utiliza a função fscanf para realizar a leitura formatada
    //Guarda os dados lidos no vetor de structs criado anteriormente
    while (fscanf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n",
                  &lista[cont].IDPessoa, lista[cont].nome , lista[cont].cpf,
                  lista[cont].data , lista[cont].email , lista[cont].telefone) != EOF) {
        cont++;
    }
    fclose(arquivo);
} 

//Carregar de memoria para arquivo 
void escreverArquivo() {
arquivo = fopen("pessoa.txt", "w+");
    
    for(int k = 0; k < cont; k++) {
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[k].IDPessoa, lista[k].nome, lista[k].cpf, lista[k].data, lista[k].email, lista[k].telefone);
    }
    fclose(arquivo);
}

//Funcoes de CRUD

void cadastraArquivo(){
    PESSOA novaPessoa;

    printf("\n----   Cadastrar   ----\n");
    
    do{
        printf("Nome: ");
        scanf("%s", novaPessoa.nome);
    }while(strlen(novaPessoa.nome) < 2);
    
    do {
        printf("CPF: ");
        scanf("%s", novaPessoa.cpf);
        if (validarCPF(novaPessoa.cpf) ==0 ) {
            printf("CPF inválido! Tente novamente.\n");
        }
    } while (validarCPF(novaPessoa.cpf) == 0);
    
    do {
        printf("Data de nascimento (dd/mm/YYYY): ");
        scanf("%s", novaPessoa.data);
        if (validarData(novaPessoa.data) == 0) {
            printf("Data de nascimento inválida! Tente novamente.\n");
        }
    } while (validarData(novaPessoa.data) == 0);

    do {
        printf("Email: ");
        scanf("%s", novaPessoa.email);
        if(validarEmail(novaPessoa.email)==0){
            printf("Email inválido!");
        }
    } while (validarEmail(novaPessoa.email) == 0);
    

    do {
        printf("Digite o Telefone com (DDD): ");
        scanf("%s", novaPessoa.telefone);
        if(verificaTelefone(novaPessoa.telefone) == 0)
            printf("Telefone inválido!");
    }while(verificaTelefone(novaPessoa.telefone) == 0);

    printf("\nCadastro realizado com sucesso!!\n");
    
    arquivo = fopen("pessoa.txt", "a+");
    fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", ultimoID()+1,novaPessoa.nome,novaPessoa.cpf,novaPessoa.data,novaPessoa.email,novaPessoa.telefone);
    fclose(arquivo);
    
    carregaArquivo();
}


void editaArquivo(){
    int i;
    int IDPessoaAlteracao, op_editar, op_alteracao;
    char NomePessoaAlteracao[31];


    do{
        imprimeArquivo();
        printf("\n-----EDIÇÃO-----\n");
        printf("\n|1| Editar usando o Nome\n|2| Editar usando o ID\n|3| Retornar\n");
        scanf("%d", &op_editar);
        if (op_editar == 1)
        {
            printf("Digite o nome: ");
            scanf("%s", NomePessoaAlteracao);

            for (int i = 0; i < cont; i++)
            {
                if (strcmp(NomePessoaAlteracao, lista[i].nome) == 0)
                {
                    printf("O que deseja alterar:\n |1| Nome\n|2| Data de nascimento\n|3| CPF\n|4| Email\n|5| Retornar\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao)
                    {
                        case 1:
                            printf("Digite o novo nome: ");
                            scanf("%s", lista[i].nome);
                            escreverArquivo();
                            break;
                        case 2:
                            printf("Digite a data de nascimento: ");
                            scanf("%s", lista[i].data);
                            escreverArquivo();
                            break;
                        case 3:
                            printf("Digite o CPF: ");
                            scanf("%s", lista[i].cpf);
                            escreverArquivo();
                            break;
                        case 4:
                            printf("Digite o Email: ");
                            scanf("%s", lista[i].email);
                            escreverArquivo();
                            break;
                        case 5:
                            break;
                    }
                }
            }
        }else if(op_editar==2){
            printf("Digite o ID: ");
            scanf("%d", &IDPessoaAlteracao);

            for (int i = 0; i < cont; i++)
            {
                if (IDPessoaAlteracao == lista[i].IDPessoa)
                {
                    printf("O que deseja alterar:\n|1| Nome\n|2| Data de nascimento\n|3| CPF\n|4| Email\n|5| Retornar\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao)
                    {
                        case 1:
                            printf("Digite o novo nome: ");
                            scanf("%s", lista[i].nome);
                            escreverArquivo();
                            break;
                        case 2:
                            printf("Digite a data de nascimento: ");
                            scanf("%s", lista[i].data);
                            escreverArquivo();
                            break;
                        case 3:
                            printf("Digite o CPF: ");
                            scanf("%s", lista[i].cpf);
                            escreverArquivo();
                            break;
                        case 4:
                            printf("Digite o Email: ");
                            scanf("%s", lista[i].email);
                            escreverArquivo();
                            break;
                        case 5:
                            break;
                        default:
                        printf("Opção inválida");
                    }
                }
            }
        }else if((op_editar !=3) && (op_editar !=2) && (op_editar !=1)){
            printf("Opção inválida!\n");
        }
    }while(op_editar != 3);

}

void excluiArquivo(){
    arquivo = fopen("pessoa.txt", "w+");
    int ID_exclusao, encontrou=0;
    printf("Digite o ID para exclusao: \n");
    scanf("%d", &ID_exclusao);
    int i;
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa != ID_exclusao)
        {
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].data,lista[i].email ,lista[i].telefone);
        }else{
            encontrou=1;
        }
    }
        if(encontrou != 1) {
            printf("ID não encontrado!");
    }
    fclose(arquivo);
    carregaArquivo();
}
//impressão do arquivo no terminal
void imprimeArquivo(){
    int i;
    for(i = 0; i < cont; i++)
    {
        printf("%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].data, lista[i].email, lista[i].telefone);
    }
}

//---------------------------------------------------

//Validações
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
    
    if(temPonto == 1 && temArroba==1){
        return 1;
    }else{
        return 0;
    }
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
int verificaTelefone(const char *telefone) {
    // Verifica se o comprimento do número de telefone é válido
    if (strlen(telefone) != 11) {
        return 0;  // O número de telefone deve ter 11 dígitos
    }

    // Verifica se cada caractere do número de telefone é um dígito numérico
    for (int i = 0; i < 11; i++) {
        if (!isdigit(telefone[i])) {
            return 0;  // Se algum caractere não for um dígito, o número é inválido
        }
    }

    // Se todas as verificações passarem, o número de telefone é considerado válido
    return 1;
}


int ultimoID(){
    int maiorID = -INFINITY;
    int i;
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa > maiorID)
        {
            maiorID = lista[i].IDPessoa;
        }
    }
}
