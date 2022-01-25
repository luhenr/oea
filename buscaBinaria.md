```cpp
#include <iostream>
#include <string.h>
using namespace std;

typedef struct Dados DE;

struct Dados{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"Erro");
        return 1;
    }
    FILE *arquivo;
    DE dados;
    int contador = 0, aux;
    long primeiro, meio, ultimo, tamanhoArquivo;
    arquivo = fopen("cep_ordenado.dat", "rb");
    fseek(arquivo, 0, SEEK_END);
    tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);
    primeiro = 0;
    ultimo = (tamanhoArquivo/sizeof(Dados))-1;
    while(primeiro <= ultimo){
        contador++;
        meio = (primeiro + ultimo)/2;
        fseek(arquivo, meio * sizeof(Dados), SEEK_SET);
        fread(&dados, sizeof(Dados), 1, arquivo);
        aux = strncmp(dados.cep, argv[1], 8);
        if(aux == 0){
            printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",dados.logradouro, dados.bairro, dados.cidade, dados.uf, dados.sigla, dados.cep);
            break;
        }
        else if(aux < 0){
            primeiro = meio + 1;
        }
        else{
            ultimo = meio - 1;
        }
    }
    fclose(arquivo);
    printf("\nForam feitas %d iteracoes\n\n", contador);
    return 0;
}
```
