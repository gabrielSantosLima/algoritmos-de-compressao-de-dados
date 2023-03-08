#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 9

char int_to_char(int value)
{
    return (char)value;
}

typedef struct node
{
    int length;
    char digit;
    struct node *next;
} node;

typedef struct list
{
    node *root;
    int length;
} list;

list *new_list()
{
    list *nlist = (list *)malloc(sizeof(list));
    nlist->length = 0;
    nlist->root = NULL;
    return nlist;
}

node *new_node(int length, char digit)
{
    node *nnode = (node *)malloc(sizeof(node));
    nnode->digit = digit;
    nnode->length = length;
    nnode->next = NULL;
    return nnode;
}

void add_2_list(list *nlist, int length, char digit)
{
    node *nnode = new_node(length, digit);
    if (nlist->root == NULL)
    {
        nlist->root = nnode;
        nlist->length++;
        return;
    }
    node *aux = nlist->root;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = nnode;
    nlist->length++;
}

char *list_2_encoding(list *nlist)
{
    if (nlist->length == 0)
        return "";
    char *encoding = (char *)malloc(nlist->length * 2 + 1);
    int i = 0;
    node *aux = nlist->root;
    while (aux != NULL)
    {
        encoding[i] = int_to_char(aux->length + 48);
        encoding[i + 1] = aux->digit;
        i += 2;
        aux = aux->next;
    }
    return encoding;
}

char *RLE(char *text)
{
    list *encoding = new_list();
    int size = strlen(text);
    char digit = text[0];
    int length = 1;

    for (int index = 1; index < size; index++)
    {
        if (text[index] == digit && length < MAX)
        {
            length++;
            if (index == size - 1)
                add_2_list(encoding, length, digit);
        }
        else
        {
            add_2_list(encoding, length, digit);
            digit = text[index];
            length = 1;
        }
    }
    return list_2_encoding(encoding);
}

int main()
{
    char *text = "aaaaabbcc";
    char *compressed_text = RLE(text);
    printf("Texto original: %s\n", text);
    printf("Texto comprimido: %s\n", compressed_text);
    printf("Tamanho do texto original (bytes): %d\n", strlen(text));
    printf("Tamanho do texto comprimido (bytes): %d\n", strlen(compressed_text));
    printf("Ganho de %d bytes\n", strlen(text) - strlen(compressed_text));
    return 0;
}