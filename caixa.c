#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Definir os nomes de usuario e senhas para o admin e usuario padrao
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"
#define USER_USERNAME "caixa"
#define USER_PASSWORD "caixa"

// Estrutura para representar um cliente
typedef struct
{
    char nome[50];
    char email[50];
    char telefone[15];
    double saldo;
} Cliente;

#define MAX_CLIENTES 100

Cliente clientes[MAX_CLIENTES];
int numClientes = 0;
int isAdmin = 0; // Variavel para verificar se o usuario logou como admin

// Estrutura para representar as respostas do questionario
typedef struct
{
    char nome[50];
    int respostas[10];
} Questionario;

#define MAX_QUESTIONARIOS 100

Questionario questionarios[MAX_QUESTIONARIOS];
int numQuestionarios = 0;

// Prototipos das funcoes
void login();
void cadastrarCliente();
void registrarTransacao();
void listarClientes();
void salvarClientes();
void carregarClientes();
void corrigirCadastro();
void calcularSomaSaldos();
void excluirCliente();
void preencherQuestionario(int clienteIndex);
void salvarRespostasQuestionario();
void exibirPerguntas();
void adicionarQuestionario(const char *nome);
void carregarQuestionarios();
void listarQuestionarios();
void exibirDescricaoPrograma();

// Perguntas para os questionarios
const char *perguntas[] = {
    "Voce achou as informacoes sobre a Semana de Arte Moderna interessantes?\n"
    "(1 - Sim / 2 - Nao)\n",

    "As explicacoes ajudaram voce a entender melhor o contexto da Semana de Arte Moderna?\n"
    "(1 - Sim / 2 - Nao)\n",

    "Voce se sente mais informado sobre a historia da arte brasileira apos visitar esta sala?\n"
    "(1 - Sim / 2 - Nao)\n",

    "As obras expostas e as informacoes correspondentes foram relevantes para voce?\n"
    "(1 - Sim / 2 - Nao)\n",

    "As informacoes despertaram seu interesse pela arte moderna brasileira?\n"
    " 1 - Sim / 2 - Nao)\n",

    "Voce acredita que esta sala adiciona valor à sua visita ao museu?\n"
    "(1 - Sim / 2 - Nao)",
    "As informacoes sao apresentadas de forma envolvente e atraente?\n"
    "(1 - Sim / 2 - Nao)\n",

    "Voce gostaria de ver mais exposicoes relacionadas à arte moderna brasileira em museus?\n"
    "(1 - Sim / 2 - Nao)\n",

    "A sala forneceu uma experiencia educativa sobre o tema?\n"
    "(1 - Sim / 2 - Nao)\n",

    "Voce recomendaria esta sala a outras pessoas que visitam o museu?\n"
    "(1 - Sim / 2 - Nao)\n"};

// funcao para verificar as credenciais do usuario
void login()
{
    char username[50];
    char password[50];
    int loginSucesso = 0;

    while (!loginSucesso)
    {
        printf("=============================================\n");
        printf("           TELA DE LOGIN                     \n");
        printf("=============================================\n");
        printf("Nome de usuario: ");
        scanf(" %[^\n]", username);
        printf("Senha: ");
        scanf(" %[^\n]", password);
        system("cls");

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0)
        {
            isAdmin = 1; // O usuario logou como admin
            printf("=============================================\n");
            printf("   Login como administrador bem-sucedido!  \n");
            printf("=============================================\n");
            loginSucesso = 1; // Definir loginSucesso como verdadeiro para sair do loop
        }
        else if (strcmp(username, USER_USERNAME) == 0 && strcmp(password, USER_PASSWORD) == 0)
        {
            isAdmin = 0;      // O usuario logou como usuario padrao
            loginSucesso = 1; // Definir loginSucesso como verdadeiro para sair do loop
        }
        else
        {
            printf("=============================================\n");
            printf("     Nome de usuario ou senha incorretos.     \n");
            printf("     Tente novamente.\n");
            printf("=============================================\n");
        }
    }
}

// funcao para salvar os clientes em um arquivo
void salvarClientes()
{
    FILE *arquivo = fopen("clientes.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

        // Obter a data e hora atuais
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char dataHora[50];
    strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Escrever a data e hora no arquivo
    fprintf(arquivo, "Data e Hora de Registro: %s\n", dataHora);

    for (int i = 0; i < numClientes; i++)
    {
        fprintf(arquivo, "%s; ", clientes[i].nome);
        fprintf(arquivo, "%s; ", clientes[i].email);
        fprintf(arquivo, "%s; ", clientes[i].telefone);
        fprintf(arquivo, "%.2lf;\n", clientes[i].saldo);
    }

    fclose(arquivo);
}

// funcao para carregar os clientes de um arquivo
void carregarClientes()
{
    FILE *arquivo = fopen("clientes.csv", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de clientes nao encontrado.\n");
        return;
    }

    while (fscanf(arquivo, " %[^;];", clientes[numClientes].nome) == 1)
    {
        fgetc(arquivo); // Consumir o ponto e virgula
        fscanf(arquivo, " %[^;];", clientes[numClientes].email);
        fgetc(arquivo); // Consumir o ponto e virgula
        fscanf(arquivo, " %[^;];", clientes[numClientes].telefone);
        fgetc(arquivo); // Consumir o ponto e virgula
        fscanf(arquivo, "%lf;", &clientes[numClientes].saldo);
        fgetc(arquivo); // Consumir a quebra de linha
        numClientes++;
    }
    fclose(arquivo);
}

// funcao para cadastrar um novo cliente
void cadastrarCliente()
{
    if (numClientes < MAX_CLIENTES)
    {
        Cliente novoCliente;
        printf("=============================================\n");
        printf("            CADASTRO DE NOVO CLIENTE         \n");
        printf("=============================================\n");
        printf("Informe o nome do cliente: ");
        scanf(" %[^\n]", novoCliente.nome);
        printf("Informe o e-mail do cliente: ");
        scanf(" %[^\n]", novoCliente.email);
        printf("Informe o numero de telefone do cliente: ");
        scanf(" %[^\n]", novoCliente.telefone);
        printf("Informe o saldo inicial do cliente: "); // Adicao do saldo inicial
        scanf("%lf", &novoCliente.saldo);               // Captura do saldo
        clientes[numClientes] = novoCliente;
        numClientes++;
        system("cls");
        printf("=============================================\n");
        printf("    Cliente cadastrado com sucesso!          \n");
        printf("=============================================\n");
        salvarClientes();
    }
    else
    {
        printf("=============================================\n");
        printf(" Limite maximo de clientes atingido.        \n");
        printf("=============================================\n");
    }
}

// funcao para registrar uma transacao no fluxo de caixa
void registrarTransacao()
{
    if (numClientes == 0)
    {
        system("cls");
        printf("=============================================\n");
        printf("     Nenhum cliente cadastrado.             \n");
        printf("=============================================\n");
        return;
    }

    char nomeCliente[50];
    printf("Informe o nome do cliente: ");
    scanf(" %[^\n]", nomeCliente);

    for (int i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].nome, nomeCliente) == 0)
        {
            double valor;
            printf("Informe o valor da transacao: ");
            scanf("%lf", &valor);
            clientes[i].saldo += valor;
            system("cls");
            printf("=============================================\n");
            printf("   Transacao registrada com sucesso!         \n");
            printf("=============================================\n");
            salvarClientes();
            return;
        }
    }

    printf("=============================================\n");
    printf("      Cliente nao encontrado.                \n");
    printf("=============================================\n");
}

// funcao para listar os clientes e seus saldos
void listarClientes()
{
    if (numClientes == 0)
    {
        system("cls");
        printf("=============================================\n");
        printf("     Nenhum cliente cadastrado.             \n");
        printf("=============================================\n");
        return;
    }
    system("cls");
    printf("=============================================\n");
    printf("          Lista de clientes:                 \n");
    printf("=============================================\n");
    for (int i = 0; i < numClientes; i++)
    {
        printf("Nome: %s\n", clientes[i].nome);
        printf("E-mail: %s\n", clientes[i].email);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Saldo: R$%.2lf\n", clientes[i].saldo);
        printf("=============================================\n");
    }
}

// funcao para corrigir o cadastro de um cliente
void corrigirCadastro()
{
    if (numClientes == 0)
    {
        system("cls");
        printf("=============================================\n");
        printf("     Nenhum cliente cadastrado.             \n");
        printf("=============================================\n");
        return;
    }

    char nomeCliente[50];
    printf("Informe o nome do cliente que deseja corrigir: ");
    scanf(" %[^\n]", nomeCliente);

    for (int i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].nome, nomeCliente) == 0)
        {
            system("cls");
            printf("=============================================\n");
            printf("            CORRECAO DE CADASTRO             \n");
            printf("=============================================\n");
            printf("Nome atual: %s\n", clientes[i].nome);
            printf("Novo nome: ");
            scanf(" %[^\n]", clientes[i].nome);
            printf("E-mail atual: %s\n", clientes[i].email);
            printf("Novo e-mail: ");
            scanf(" %[^\n]", clientes[i].email);
            printf("Telefone atual: %s\n", clientes[i].telefone);
            printf("Novo telefone: ");
            scanf(" %[^\n]", clientes[i].telefone);
            printf("Saldo atual: R$%.2lf\n", clientes[i].saldo);
            printf("Novo saldo: ");
            scanf("%lf", &clientes[i].saldo);
            system("cls");
            printf("=============================================\n");
            printf("     Cadastro corrigido com sucesso!        \n");
            printf("=============================================\n");
            salvarClientes();
            return;
        }
    }
    system("cls");
    printf("=============================================\n");
    printf("      Cliente nao encontrado.                \n");
    printf("=============================================\n");
}

// funcao para calcular a soma dos saldos de todos os clientes
void calcularSomaSaldos()
{
    double soma = 0;
    for (int i = 0; i < numClientes; i++)
    {
        soma += clientes[i].saldo;
    }
    system("cls");
    printf("=============================================\n");
    printf("  Soma dos saldos de todos os clientes: R$%.2lf\n", soma);
    printf("=============================================\n");
}

// funcao para excluir um cliente
void excluirCliente()
{
    if (numClientes == 0)
    {
        system("cls");
        printf("=============================================\n");
        printf("     Nenhum cliente cadastrado.             \n");
        printf("=============================================\n");
        return;
    }

    char nomeCliente[50];
    printf("Informe o nome do cliente a ser excluIdo: ");
    scanf(" %[^\n]", nomeCliente);

    for (int i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].nome, nomeCliente) == 0)
        {
            // Remover o cliente da lista movendo os elementos restantes para cima
            for (int j = i; j < numClientes - 1; j++)
            {
                clientes[j] = clientes[j + 1];
            }
            numClientes--;

            system("cls");
            printf("=============================================\n");
            printf("   Cliente excluIdo com sucesso!         \n");
            printf("=============================================\n");
            salvarClientes(); // Salvar a lista de clientes atualizada
            return;
        }
    }
    system("cls");
    printf("=============================================\n");
    printf("      Cliente nao encontrado.                \n");
    printf("=============================================\n");
}

// funcao para preencher um questionario
void preencherQuestionario(int clienteIndex)
{
    if (clienteIndex >= 0 && clienteIndex < numClientes)
    {
        adicionarQuestionario(clientes[clienteIndex].nome);

        printf("=============================================\n");
        printf("          PREENCHER QUESTIONARIO             \n");
        printf("=============================================\n");

        for (int i = 0; i < 10; i++)
        {
            int resposta;
            do
            {
                printf("%s ", perguntas[i]);
                scanf("%d", &resposta);
            } while (resposta != 1 && resposta != 2);
            questionarios[numQuestionarios - 1].respostas[i] = resposta;
        }

        printf("=============================================\n");
        printf("  Questionario preenchido com sucesso!       \n");
        printf("=============================================\n");
        salvarRespostasQuestionario();
    }
    else
    {
        printf("=============================================\n");
        printf("  Cliente nao encontrado. Impossivel preencher o questionario.\n");
        printf("=============================================\n");
    }
}

void salvarRespostasQuestionario()
{
    FILE *arquivo = fopen("respostas_questionario.csv", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de respostas do questionario.\n");
        return;
    }

    fprintf(arquivo, "%s;", questionarios[numQuestionarios - 1].nome);

    for (int i = 0; i < 10; i++)
    {
        fprintf(arquivo, "%d;", questionarios[numQuestionarios - 1].respostas[i]);
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);

    printf("=============================================\n");
    printf("  Respostas do questionario salvas com sucesso!\n");
    printf("=============================================\n");
}


// funcao para exibir as perguntas do questionario
void exibirPerguntas()
{
    system("cls");
    printf("=============================================\n");
    printf("            PERGUNTAS DO QUESTIONARIO         \n");
    printf("=============================================\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s\n", i + 1, perguntas[i]);
    }
}

// funcao para adicionar um novo questionario à lista de questionarios
void adicionarQuestionario(const char *nome)
{
    if (numQuestionarios < MAX_QUESTIONARIOS)
    {
        strcpy(questionarios[numQuestionarios].nome, nome);
        for (int i = 0; i < 10; i++)
        {
            questionarios[numQuestionarios].respostas[i] = 0; // Inicializa todas as respostas com zero
        }
        numQuestionarios++;
    }
    else
    {
        printf("=============================================\n");
        printf(" Limite maximo de questionarios atingido.     \n");
        printf("=============================================\n");
    }
}

void carregarQuestionarios()
{
    FILE *arquivo = fopen("respostas_questionario.csv", "r");
    if (arquivo != NULL)
    {
        char linha[512]; // Tamanho máximo de uma linha no arquivo, ajuste conforme necessário
        int linhaAtual = 0;

        while (fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            if (linhaAtual >= MAX_QUESTIONARIOS)
            {
                break; // Evitar estouro do vetor
            }

            char *token = strtok(linha, ";");

            if (token != NULL)
            {
                strncpy(questionarios[linhaAtual].nome, token, sizeof(questionarios[linhaAtual].nome));
            }

            for (int i = 0; i < 10; i++)
            {
                token = strtok(NULL, ";");

                if (token != NULL)
                {
                    questionarios[linhaAtual].respostas[i] = atoi(token);
                }
            }

            linhaAtual++;
        }

        numQuestionarios = linhaAtual;
        fclose(arquivo);
    }
    else
    {
        printf("Arquivo de respostas do questionário não encontrado.\n");
    }
}

// Função para listar os questionários preenchidos
void listarQuestionarios()
{
    system("cls");
    printf("=============================================\n");
    printf("    LISTA DE QUESTIONARIOS PREENCHIDOS       \n");
    printf("=============================================\n");

    for (int i = 0; i < numQuestionarios; i++)
    {
        printf("Questionario para: %s\n", questionarios[i].nome);
        printf("Respostas:\n");

        for (int j = 0; j < 10; j++)
        {
            printf("%d. %s: %d\n", j + 1, perguntas[j], questionarios[i].respostas[j]);
        }

        printf("=============================================\n");
    }
}


// Função para exibir a descrição do programa
void exibirDescricaoPrograma()
{
    printf("=============================================\n");
    printf("           Descricao do Programa             \n");
    printf("=============================================\n\n");
    
    printf("=============================================\n");
    printf("Cadastro de Cliente:\n");
    printf("=============================================\n");    
    printf("A funcao cadastrarCliente permite adicionar \n");
    printf("novos clientes. a lista solicita informacoes \n");
    printf("como nome, e-mail, telefone e saldo inicial \n");
    printf("do cliente. detalhes do cliente sao \n");
    printf("armazenados em uma estrutura de dados.\n\n\n");

    
    printf("=============================================\n");
    printf("Registro de Transacao:\n");
    printf("=============================================\n");
    printf("A funcao registrarTransacao permite registrar \n");
    printf("transacoes para clientes existentes.Ela \n");
    printf("solicita o nome do cliente e o valor da\n");
    printf("transacao, atualizando o saldo do cliente.\n\n\n");


    printf("=============================================\n");
    printf("Correcao de Cadastro:\n");
    printf("=============================================\n");
    printf("A funcao corrigirCadastro permite ao\n");
    printf(" administrador corrigir as informacoes de um \n");
    printf("cliente. Isso inclui a capacidade de editar \n");
    printf("o nome, e-mail, telefone e saldo do cliente.\n\n\n");


    printf("=============================================\n");
    printf("Lista de Clientes:\n");
    printf("=============================================\n");
    printf("A funcao listarClientes exibe uma lista de \n");
    printf("todos os clientes cadastrados, incluindo seus\n");
    printf("nomes, e-mails, telefones e saldos.\n\n\n");


    printf("=============================================\n");
    printf("Calculo da Soma dos Saldos:\n");
    printf("=============================================\n");
    printf("A funcao calcularSomaSaldos calcula a soma\n");
    printf("dos saldos de todos os clientes e a exibe \n");
    printf("na tela.\n\n\n");


    printf("=============================================\n");
    printf("Exclusao de Cliente:\n");
    printf("=============================================\n");
    printf("A funcao excluirCliente permite ao\n");
    printf("administrador excluir um cliente da lista.\n\n\n");


    printf("=============================================\n");
    printf("Preenchimento de Questionario:\n");
    printf("=============================================\n");
    printf("A funcao preencherQuestionario permite que um\n");
    printf("cliente responda a um questionario com 10\n");
    printf("perguntas.respostas sao armazenadas em uma\n");
    printf("estrutura de dados separada.\n\n\n");


    printf("=============================================\n");
    printf("Exibicao de Perguntas do Questionario:\n");
    printf("=============================================\n");
    printf("A funcao exibirPerguntas exibe as 10\n");
    printf("do questionario.\n\n\n");


    printf("=============================================\n");
    printf("Listar Questionarios:\n");
    printf("=============================================\n");
    printf("A funcao listarQuestionarios exibe uma lista\n");
    printf("de questionarios preenchidos, incluindo o\n");
    printf("nome do cliente e suas respostas.\n\n\n");


    printf("=============================================\n");
    printf("Pressione qualquer tecla para voltar ao menu.\n");
    printf("=============================================\n");

    getch(); // Aguarde uma tecla ser pressionada para continuar
    system("cls");
}

int main()
{
    login(); // Chame a funcao de login no inicio do programa

    if (!isAdmin)
    {
        system("cls");
        printf("=============================================\n");
        printf("     Bem-vindo ao modo de usuario caixa!     \n");
        printf("=============================================\n");
    }

    carregarClientes(); // Carregar os clientes do arquivo ao iniciar o programa
    carregarQuestionarios();

    int opcao;

    while (1)
    {
        printf("\n=============================================\n");
        printf("            MENU DE OPCOES                   \n");
        printf("=============================================\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Registrar transacao\n");
        if (isAdmin)
        {
            // Apenas o admin pode acessar essas opcoes
            printf("3. Corrigir cadastro\n");
            printf("4. Excluir cliente\n");
            printf("5. Preencher questionario\n");
            printf("6. Exibir perguntas do questionario\n");
            printf("7. Listar questionarios\n");
        }
        printf("8. Listar clientes\n");
        printf("9. Calcular soma dos saldos\n");
        printf("10. Sair\n");
        printf("11. Exibir descricao do programa \n"); // Opção para exibir a descrição do programa

        // Leitura segura de opcao
        int scanfResult;
        do
        {
            printf("Escolha uma opcao: ");
            scanfResult = scanf("%d", &opcao);
            if (scanfResult != 1)
            {
                // Limpar o buffer de entrada em caso de entrada invalida
                while (getchar() != '\n')
                    ;
            }
        } while (scanfResult != 1);

        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            registrarTransacao();
            break;
        case 3:
            if (isAdmin)
                corrigirCadastro();
            else
                printf("Voce nao tem permissao para esta opcao.\n");
            break;
        case 4:
            if (isAdmin)
                excluirCliente();
            else
                printf("Voce nao tem permissao para esta opcao.\n");
            break;
        case 5:
            if (isAdmin)
            {
                system("cls");
                printf("=============================================\n");
                printf("            PREENCHER QUESTIONARIO             \n");
                printf("=============================================\n");
                if (numClientes == 0)
                {
                    printf("Nenhum cliente cadastrado. Impossivel preencher o questionario.\n");
                }
                else
                {
                    system("cls");
                    listarClientes();
                    char nomeCliente[50];
                    printf("Informe o nome do cliente para o qual deseja preencher o questionario: ");
                    scanf(" %[^\n]", nomeCliente);

                    int clienteIndex = -1; // Inicialize com um valor que indica que o cliente nao foi encontrado

                    for (int i = 0; i < numClientes; i++)
                    {
                        if (strcmp(clientes[i].nome, nomeCliente) == 0)
                        {
                            clienteIndex = i;
                            break; // Cliente encontrado, saia do loop
                        }
                    }

                    if (clienteIndex != -1)
                    {
                        preencherQuestionario(clienteIndex); // Passe o indice do cliente
                    }
                    else
                    {
                        printf("Cliente nao encontrado. Impossivel preencher o questionario.\n");
                    }
                }
            }
            else
            {
                printf("Voce nao tem permissao para esta opcao.\n");
            }
            break;
        case 6:
            if (isAdmin)
                exibirPerguntas();
            else
                printf("Voce nao tem permissao para esta opcao.\n");
            break;
        case 7:
            if (isAdmin)
                listarQuestionarios();
            else
                printf("Voce nao tem permissao para esta opcao.\n");
            break;
        case 8:
            listarClientes();
            break;
        case 9:
            calcularSomaSaldos();
            break;
        case 10:
            salvarClientes();
            return 0;
        case 11:
            system("cls");
            exibirDescricaoPrograma(); // Exibe a descrição do programa
            break;
        }
    }

    return 0;
}
    return 0;