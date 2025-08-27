#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#define MAX 50

typedef struct
{
    char nomeTarefa[MAX];
    bool tarefaFeita;
    int numeroTarefa;

} ToDo;

typedef struct No
{
    ToDo tarefa;
    struct No *proximo;
} No;

void showTarefas(No *cabecaDaLista, int tarefasNum)
{
    if (cabecaDaLista == NULL)
    {
        printf("A lista esta vazia, nao ha oque exibir!\n");
        return;
    }
    No *atual = cabecaDaLista;
    while (atual != NULL)
    {
        printf("%i° %s -- ", atual->tarefa.numeroTarefa, atual->tarefa.nomeTarefa);
        if (atual->tarefa.tarefaFeita == true)
        {
            printf("CONCLUIDA!\n");
        }
        else
            printf("PENDENTE\n");
        atual = atual->proximo;
    }
}

void addTarefa(No **cabecaDaLista_p, int *tarefasNum_p, int *proximoID)
{
    No *novaTarefa = malloc(sizeof(No));
    if (novaTarefa == NULL)
    {
        printf("Erro critico: Falha ao alocar memoria para a nova tarefa!\n");
        return;
    }

    printf("Digite a descricao da nova tarefa: ");
    fgets(novaTarefa->tarefa.nomeTarefa, MAX, stdin);
    novaTarefa->tarefa.nomeTarefa[strcspn(novaTarefa->tarefa.nomeTarefa, "\n")] = '\0';
    novaTarefa->tarefa.numeroTarefa = (*proximoID);
    (*proximoID)++; /*Essa variavel existe apenas para demonstrar o usuario o numero das tarefas corretamente, ela so cresce.*/
    novaTarefa->tarefa.tarefaFeita = false;
    novaTarefa->proximo = *cabecaDaLista_p; /*Guarda o endereço do proximo elemento */
    *cabecaDaLista_p = novaTarefa;

    (*tarefasNum_p)++;
    printf("Tarefa adicionada no inicio da lista!\n");
}

void removeTarefa(No **cabecaDaLista_p, int *tarefasNum_p)
{
    printf("Digite o numero da tarefa que deseja remover: ");
    int tarefaRemovida; /*Variavel que contem o numero da tarefa a ser removida*/
    char buffer_entrada[MAX];

    if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL)
    {
        if (sscanf(buffer_entrada, "%i", &tarefaRemovida) != 1)
        {
            printf("Erro: Digite apenas numeros.\n");
            return;
        }
    }
    else
    {
        printf("Erro: Nada foi digitado.\n");
        return;
    }

    if (*cabecaDaLista_p == NULL)
    {
        printf("A lista está vazia, impossível remover.\n");
        return;
    }

    No *anterior = NULL;
    No *atual = *cabecaDaLista_p;

    if (atual->tarefa.numeroTarefa == tarefaRemovida) /*Caso queira remover a cabeça da lista*/
    {
        *cabecaDaLista_p = atual->proximo;
        free(atual);
        (*tarefasNum_p)--;
        printf("Tarefa removida com sucesso!\n");
        return;
    }

    anterior = atual;
    atual = atual->proximo;

    while (atual != NULL)
    {
        if (atual->tarefa.numeroTarefa == tarefaRemovida)
        {
            anterior->proximo = atual->proximo;
            free(atual);
            (*tarefasNum_p)--;
            printf("Tarefa removida com sucesso!\n");
            return; // Já terminamos.
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Erro: Tarefa com o numero %d nao encontrada.\n", tarefaRemovida);
}

void concludeTarefa(No *cabecaDaLista, int *tarefasNum_p)
{
    int tarefaConcluida; /*tarefa que foi concluida, é input do usuario*/
    char buffer_entrada[MAX];

    printf("Digite o numero da tarefa que deseja validar: ");
    if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL)
    {
        if (sscanf(buffer_entrada, "%i", &tarefaConcluida) != 1)
        {
            printf("Erro, digite apenas numeros.\n");
            return;
        }
    }
    else
    {
        printf("Erro, nada foi digitado!\n");
        return;
    }

    No *atual = cabecaDaLista;

    while (atual != NULL)
    {
        if (atual->tarefa.numeroTarefa == tarefaConcluida)
        {
            atual->tarefa.tarefaFeita = true;
            printf("Tarefa marcada como concluida!\n");
            return;
        }
        atual = atual->proximo;
    }

    printf("Erro, a tarefa requisitada nao se encontra na lista.\n");
    return;
}

void cleanTarefas(No **cabecaDaLista_p, int *tarefasNum_p, int *proximoID_p)
{
    No *atual = *cabecaDaLista_p;
    No *proximo;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *cabecaDaLista_p = NULL;
    *tarefasNum_p = 0;
    *proximoID_p = 1;
    printf("Lista limpa com sucesso!\n");
}

int main()
{
    No *cabecaDaLista = NULL; 
    int tarefasNum = 0;
    int proximoId = 1;
    int opcao = 0;

    while (opcao != 6)
    {
        printf("Bem vindo a sua To-Do-List, o que deseja fazer?\n");
        printf("1) Exibir todas as tarefas.\n");
        printf("2) Adicionar uma nova tarefa.\n");
        printf("3) Remover uma tarefa.\n");
        printf("4) Marcar tarefa como concluída.\n");
        printf("5) Limpar a lista de tarefas.\n");
        printf("6) Sair da lista.\n");
        scanf("%i", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) /*Devido a utilização de Scanf junto com Fgets, esse loop é necessário para contornar o espaço invisível*/
            ;

        switch (opcao)
        {
        case 1:
            showTarefas(cabecaDaLista, tarefasNum);
            break;

        case 2:
            addTarefa(&cabecaDaLista, &tarefasNum, &proximoId);
            break;

        case 3:
            removeTarefa(&cabecaDaLista, &tarefasNum);
            break;

        case 4:
            concludeTarefa(cabecaDaLista, &tarefasNum);
            break;

        case 5:
            cleanTarefas(&cabecaDaLista, &tarefasNum, &proximoId);
            break;

        default:
            printf("Saindo da lista!\n");
            break;
        }
    }

    cleanTarefas(&cabecaDaLista, &tarefasNum, &proximoId);
    return 0;
}

