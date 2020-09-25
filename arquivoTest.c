#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { // Cria uma STRUCT para armazenar cada elemento da nossa tabela.
    char key;   // Define o campo key, que corresponde a chave do valor.
    int cod[6]; // Define o vetor código, que contem o codigo da determinada chave na base 64.
} dado_tabela; // Define o nome do novo tipo criado.

dado_tabela tabela[64]; //Define um vetor com 64 elementos dentro.

char tabela_caracteres[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                '4', '5', '6', '7', '8', '9', '+', '/'}; // declara os caracteres da tabela de base 64.

int * converte_binario(int num){ //converte numero decimal em binário

    int i;
    int * bin = malloc (8 * sizeof (int));

    for (int i = 7; i >= 0; i--) {
          if (num % 2 == 0)
            bin[i] = 0;
          else
            bin[i] = 1;
          num = num / 2;
    }

   return bin;
}

int * create_table (){ //cria a tabela de consulta com a letra chave e o codigo de 6 bits da mesma.
    for (int i = 0; i < 64; i++){
        tabela[i].key = tabela_caracteres[i];
        int numero_binario = i;
        int * binario = converte_binario(numero_binario);
        for (int j = 0; j < 6; j++){
            tabela[i].cod[j] = binario[j+2];
        }
    }

    return tabela;
};

int consultar_tabela(char pesquisa){ //pesquisa uma letra na tabela e devolve sua posição dentro dela.
    for (int i = 0; i<64 ; i++){
        if (pesquisa == tabela[i].key){
            return i;
        }
    }   
}

void main() {

    char pesquisa_char;

    create_table();
    printf("Digite um caracter que deseja encontrar: \n");
    scanf("%c", &pesquisa_char);
    int posicao_consulta = consultar_tabela(pesquisa_char);

    /**for (int i = 0; i < 64; i++){
        printf("Key: %c \n", tabela[i].key);
        printf("Codigo: ");
        printf("%d", tabela[i].cod[0]);
        printf("%d", tabela[i].cod[1]);
        printf("%d", tabela[i].cod[2]);
        printf("%d", tabela[i].cod[3]);
        printf("%d", tabela[i].cod[4]);
        printf("%d \n\n", tabela[i].cod[5]);
    }**/
};