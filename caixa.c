#include <stdio.h>
#include <string.h>

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

// Protótipos das funções
void cadastrarCliente();
void registrarTransacao();
void listarClientes();
void salvarClientes();
void carregarClientes();
void corrigirCadastro();
void calcularSomaSaldos();

// Função para salvar os clientes em um arquivo
void salvarClientes()
{
    FILE *arquivo = fopen("clientes.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < numClientes; i++)
    {
        fprintf(arquivo, "%s\n", clientes[i].nome);
        fprintf(arquivo, "%s\n", clientes[i].email);
        fprintf(arquivo, "%s\n", clientes[i].telefone);
        fprintf(arquivo, "%.2lf\n", clientes[i].saldo);
    }

    fclose(arquivo);
}

// Função para carregar os clientes de um arquivo
void carregarClientes()
{
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de clientes nao encontrado.\n");
        return;
    }

    while (fscanf(arquivo, " %[^\n]", clientes[numClientes].nome) == 1)
    {
        fscanf(arquivo, " %[^\n]", clientes[numClientes].email);
        fscanf(arquivo, " %[^\n]", clientes[numClientes].telefone);
        fscanf(arquivo, "%lf", &clientes[numClientes].saldo);
        numClientes++;
    }

    fclose(arquivo);
}

// Função para cadastrar um novo cliente
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
        printf("Informe o saldo inicial do cliente: "); // Adição do saldo inicial
        scanf("%lf", &novoCliente.saldo);               // Captura do saldo
        clientes[numClientes] = novoCliente;
        numClientes++;
        printf("=============================================\n");
        printf("    Cliente cadastrado com sucesso!          \n");
        printf("=============================================\n");
    }
    else
    {
        printf("=============================================\n");
        printf(" Limite maximo de clientes atingido.        \n");
        printf("=============================================\n");
    }
}

// Função para registrar uma transação no fluxo de caixa
void registrarTransacao()
{
    if (numClientes == 0)
    {
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
            printf("=============================================\n");
            printf("   Transacao registrada com sucesso!         \n");
            printf("=============================================\n");
            return;
        }
    }

    printf("=============================================\n");
    printf("      Cliente nao encontrado.                \n");
    printf("=============================================\n");
}

// Função para listar os clientes e seus saldos
void listarClientes()
{
    if (numClientes == 0)
    {
        printf("=============================================\n");
        printf("     Nenhum cliente cadastrado.             \n");
        printf("=============================================\n");
        return;
    }

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

// Função para corrigir o cadastro de um cliente
void corrigirCadastro()
{
    if (numClientes == 0)
    {
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
            printf("=============================================\n");
            printf("     Cadastro corrigido com sucesso!        \n");
            printf("=============================================\n");
            return;
        }
    }

    printf("=============================================\n");
    printf("      Cliente nao encontrado.                \n");
    printf("=============================================\n");
}

// Função para calcular a soma dos saldos de todos os clientes
void calcularSomaSaldos()
{
    double soma = 0;
    for (int i = 0; i < numClientes; i++)
    {
        soma += clientes[i].saldo;
    }
    printf("=============================================\n");
    printf("  Soma dos saldos de todos os clientes: R$%.2lf\n", soma);
    printf("=============================================\n");
}

int main()
{
    carregarClientes(); // Carregar os clientes do arquivo ao iniciar o programa

    int opcao;

    while (1)
    {
        printf("\n=============================================\n");
        printf("            MENU DE OPCOES                   \n");
        printf("=============================================\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Registrar transacao\n");
        printf("3. Corrigir cadastro\n");
        printf("4. Listar clientes\n");
        printf("5. Calcular soma dos saldos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            registrarTransacao();
            break;
        case 3:
            corrigirCadastro();
            break;
        case 4:
            listarClientes();
            break;
        case 5:
            calcularSomaSaldos();
            break;
        case 6:
            salvarClientes(); // Salvar os clientes no arquivo antes de sair
            return 0;
        default:
            printf("=============================================\n");
            printf("     Opcao invalida. Tente novamente.        \n");
            printf("=============================================\n");
        }
    }

    return 0;
}
