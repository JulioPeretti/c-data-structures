#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MAX 10

typedef struct
{
    int itens[MAX];
    int top;
} Stack;

void startStack(Stack *p)
{
    p->top = -1;
}

bool isFull(Stack *p)
{
    return p->top == MAX - 1;
}

bool isEmpty(Stack *p)
{
    return p->top == -1;
}

void pushStack(Stack *p, int num)
{
    if (isFull(p))
    {
        printf("Erro: Pilha cheia!\n");
        return;
    }

    p->top++;
    p->itens[p->top] = num;
    printf("O %i foi empilhado!\n", num);
}

int popStack(Stack *p)
{
    if (isEmpty(p))
    {
        printf("Erro: Pilha vazia! Não há elementos para desempilhar\n");
        return -1;
    }
    int valor = p->itens[p->top];
    p->top--;
    printf("Desempilhou: %d\n", valor);
    return valor;
}

int peekStack(Stack *p)
{
    if (isEmpty(p))
    {
        printf("Erro: Pilha vazia! Não há elementos para desempilhar\n");
        return -1;
    }
    return p->itens[p->top];
}

void clearStack(Stack *p)
{
    if (isEmpty(p))
    {
        printf("Erro: A pilha ja esta vazia!\n");
        return;
    }
    p->top = -1;
    printf("A pilha foi limpa!\n");
}

int sizeStack(Stack *p)
{
    return p->top + 1;
}

void displayStack(Stack *p)
{
    if (isEmpty(p))
    {
        printf("Erro: Pilha vazia! Não há elementos para exibir\n");
        return;
    }

    for (int i = 0; i <= p->top; i++)
    {
        printf("O %dº elemento é: %d\n", i + 1, p->itens[i]);
    }
}

int main()
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    startStack(p);
    int opcao = 0;
    int valor;

    while (opcao != 9)
    {
        printf("-----------------------------------------------------\n");
        printf("O que deseja fazer com a pilha?\n");
        printf("1 - Adicionar um elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Verificar se a pilha esta vazia\n");
        printf("4 - Verificar se a pilha esta cheia\n");
        printf("5 - Ver o elemento do topo\n");
        printf("6 - Derrubar a pilha\n");
        printf("7 - Verifica o tamanho da pilha\n");
        printf("8 - Mostra todos os itens da pilha\n");
        printf("9 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Qual numero deseja adicionar?\n");
            scanf("%d", &valor);
            pushStack(p, valor);
            break;

        case 2:
            popStack(p);
            break;

        case 3:
            if (isEmpty(p))
                printf("A pilha esta vazia!\n");
            else
                printf("A pilha não esta vazia!\n");
            break;

        case 4:
            if (isFull(p))
                printf("A pilha esta cheia!\n");
            else
                printf("A pilha não esta cheia!\n");
            break;

        case 5:
            printf("O item do topo é: %d\n", peekStack(p));
            break;

        case 6:
            clearStack(p);
            break;

        case 7:
            printf("A pilha tem %d itens!\n", sizeStack(p));
            break;

        case 8:
            displayStack(p);
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }
    }

    free(p);
    return 0;
}
