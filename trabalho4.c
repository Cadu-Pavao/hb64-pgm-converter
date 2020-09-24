/*--------------------------------------------------------------
 * PROCESSAMENTO DE IMAGEM -                                               
 * Atividade 3 - Decodificador Huffman - Base64
 * Aluno: 
 *--------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSYMBS 256
#define MAXNODES 511
#define CREATOR "# Imagem criada por Luiz Eduardo da Silva\n"

typedef struct
{
    int freq;
    int father;
    int left;
    int right;
} nodetype;

nodetype node[MAXNODES];

int pqmindelete(int *rootnodes)
{
    int aux;
    aux = *rootnodes;
    *rootnodes = node[*rootnodes].father;
    return aux;
}

int pqinsert(int *rootnodes, int i)
{
    int k, ant, aux;
    aux = *rootnodes;
    ant = -1;
    while (aux != -1 && node[aux].freq <= node[i].freq)
    {
        ant = aux;
        aux = node[aux].father;
    }
    if (ant == -1)
    {
        node[i].father = *rootnodes;
        *rootnodes = i;
    }
    else
    {
        node[i].father = node[ant].father;
        node[ant].father = i;
    }
}

/*--------------------------------------------------------------
 * buildTree
 * Funcao que constroi a arvore de huffman
 * Parametros:
 *    h  - vetor de histograma (frequencia de cada pixel 0..mn+1)
 *    mn - maximo nivel de cinza
 * Retorna a raiz da árvore construida (2 * mn)
 *--------------------------------------------------------------*/
int buildTree(int *h, int mn)
{
    int i, k, p, p1, p2, rootnodes = -1, root, father;
    for (i = 0; i < mn + 1; i++)
    {
        node[i].freq = h[i];
        node[i].left = -1;
        node[i].right = -1;
        pqinsert(&rootnodes, i);
    }
    for (p = mn + 1; p < 2 * (mn + 1) - 1; p++)
    {
        p1 = pqmindelete(&rootnodes);
        p2 = pqmindelete(&rootnodes);
        node[p1].father = p;
        node[p2].father = p;
        node[p].freq = node[p1].freq + node[p2].freq;
        node[p].left = p1;
        node[p].right = p2;
        pqinsert(&rootnodes, p);
    }
    return pqmindelete(&rootnodes);
}

/*--------------------------------------------------------------
 * drawLinks, createDot
 * Rotinas que geram uma visualização da árvore de huffman
 * Para produzir uma imagem, deve-se ter graphViz instalado
 * e digitar em linha de comando:
 *    dot -Tpng tree.dot -o tree.png
 *--------------------------------------------------------------*/
void drawLinks(FILE *dot, int root)
{
    if (root != -1)
    {
        int hasLeft = node[root].left != -1;
        int hasRight = node[root].right != -1;
        if (!hasLeft && !hasRight)
            fprintf(dot, "\tn%d [shape = record, label=\"%d|%d\"]\n", root, root, node[root].freq);
        else
            fprintf(dot, "\tn%d [shape = circle, label=\"%d\"]\n", root, node[root].freq);
        drawLinks(dot, node[root].left);
        if (hasLeft)
            fprintf(dot, "\tn%d -> n%d [label=0]\n", root, node[root].left);
        drawLinks(dot, node[root].right);
        if (hasRight)
            fprintf(dot, "\tn%d -> n%d [label=1]\n", root, node[root].right);
    }
}

void error(char *s)
{
    puts(s);
    exit(10);
}

void createDot(int root)
{
    int i;
    FILE *dot;
    dot = fopen("tree.dot", "wt");
    if (!dot)
        error("Erro na criação do arquivo .DOT");
    fprintf(dot, "digraph {\n");
    fprintf(dot, "\tnode [fontename=\"Arial\"];\n");
    drawLinks(dot, root);
    fprintf(dot, "}\n");
    fclose(dot);
}

void hb64_pgm(char *nome)
{
    // INSERIR AQUI O CODIGO DO DESCOMPACTADOR
}

void msg(char *s)
{
    printf("\nConversor Huffman-Base64 para PGM");
    printf("\n---------------------------------");
    printf("\nUSO.:  %s  <IMG.HB64>", s);
    printf("\nONDE:\n");
    printf("    <IMG.HB64>  Arquivo da imagem em formato HB64\n\n");
}

/*+------------------------------------------------------+
  |        P R O G R A M A    P R I N C I P A L          |
  +------------------------------------------------------+*/
int main(int argc, char *argv[])
{
    int nc, nl, mn;
    char nome[100] = "./teste.pgm.hb64";
    if (argc < 2)
        msg(argv[0]);
    else
        strcpy(nome, argv[1]);
    printf("\nDecodificador HB64\n");
    hb64_pgm(nome);
    return 0;
}