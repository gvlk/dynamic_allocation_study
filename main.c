#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product
{
    char name[30];
    int code;
    double price;
};

typedef struct node
{
    struct Product product;
    struct node *next;
} Node;

Node* createNode() {
    Node *new = (Node *) malloc (sizeof(Node));

    printf("Insira o nome: ");
    scanf("%s", new->product.name);
    printf("Insira o codigo: ");
    scanf("%d", &new->product.code);
    printf("Insira o preco: ");
    scanf("%lf", &new->product.price);

    new->next = NULL;
    return new;
}

int add(Node *node) {
    if(node->next) {
        return add(node->next);
    }

    Node *new = (Node *) malloc(sizeof(Node));
    new->next = NULL;

    printf("Insira o nome: ");
    scanf("%s", new->product.name);
    printf("Insira o codigo: ");
    scanf("%d", &new->product.code);
    printf("Insira o preco: ");
    scanf("%lf", &new->product.price);

    node->next = new;

    return 0;
}

int listProducts(Node *node) {
    printf("*\n");
    printf("Nome: %s \n", node->product.name);
    printf("Codigo: %d \n", node->product.code);
    printf("Preco: $%lf \n", node->product.price);
    printf("*\n");

    if (node->next)
    {
        return listProducts(node->next);
    }

    return 0;
}

int eraseNode(Node *node, int code) {
    if (node->product.code != code) {
        if(node->next) {
            return eraseNode(node->next, code);
        }    
        printf("Produto não existe\n");
        return 1;
    }

    if(node->next) {
        memcpy(node->product.name, node->next->product.name, sizeof(node->product.name));
        node->product.code = node->next->product.code;
        node->product.price = node->next->product.price;

        if(node->next->next) {
            node->next = node->next->next;
        }
        else {
            node->next = NULL;
        }
    } 

    return 0;
}

int removeProduct(Node *node) {
    int code;

    printf("Insira o codigo: ");
    scanf("%d", &code);

    return eraseNode(node, code);
}

int main() {
    int menu_entry;
    Node *node = NULL;

    do {
        printf("1 - Adicionar\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &menu_entry);

        switch (menu_entry) {
        case 1:
            if(!node) {
                node = createNode();
            }
            else {
                add(node);
            }
            break;
        case 2:
            removeProduct(node);
            break;
        case 3:
            listProducts(node);
            break;
        case 0:
            free(node);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (menu_entry != 0);

    return 0;
}