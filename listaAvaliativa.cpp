#include <iostream>
#include <string.h>
using namespace std;

typedef struct _sinasc sinasc;

struct _sinasc {
    char CODMUNNASC[6]; /* Código do Município de Nascimento */
    char CODESTAB[7]; /* Código do Estabelecimento */
    char CODMUNRES[6]; /* Código do Município de Residência */
    char DTNASC[8]; /* Data de Nascimento no formato DDMMAAAA */
    char SEMAGESTAC[2]; /* Número de Semanas de Gestação */
    char SEXO[1]; /* Sexo 0 não informado, 1 Masculino ou 2 Feminino */
    char PESO[4]; /* Peso em gramas */
    char DTNASCMAE[8]; /* Data de Nascimento no formato DDMMAAAA */
};

int compara(const void *e1, const void *e2){
	return strncmp(((sinasc*)e1)->CODESTAB,((sinasc*)e2)->CODESTAB,7);
}

int main(){

    FILE* arquivo, *f;
    sinasc Dados;
    long tamanhoArq;
    arquivo = fopen("sinasc-sp-2018.dat", "rb");
    fseek(arquivo, 0, SEEK_END);
    tamanhoArq = ftell(arquivo);
    rewind(arquivo);
    
    printf("Tamanho do arquivo: %ld\n", tamanhoArq);
    printf("Tamanho de cada registro: %ld\n", sizeof(sinasc));
    printf("Quantidade de registros: %ld\n", tamanhoArq/sizeof(sinasc));

    FILE* aux;
    aux = fopen("sinasc-sp-capital-2018.dat", "wb");

    int qtd = fread(&Dados, sizeof(Dados), 1, arquivo), santos = 0, abaixoPeso = 0;
    while(qtd > 0){
        if(strncmp(Dados.CODMUNNASC, "354850", 6) == 0){
            if(strncmp(Dados.SEXO, "2", 1) == 0){
                santos++;
            }
        }
        if(strncmp(Dados.CODMUNNASC, "350950", 6) == 0){
            string a = Dados.DTNASC;
            string b = a.substr(4, 4);
            if(b == "2018"){
                if(strncmp(Dados.PESO, "2500", 4) < 0){
                    abaixoPeso++;
                }
            }
        }
        if(strncmp(Dados.CODMUNNASC, "355030", 6) == 0){
            fwrite(&Dados, sizeof(Dados), 1, aux);
        }
        qtd = fread(&Dados, sizeof(Dados), 1, arquivo);
    }

    printf("Nascimentos em Santos: %d\n", santos);
    printf("Nascimentos abaixo do peso em Campinas: %d\n", abaixoPeso);

    sinasc* e = (sinasc*) malloc(tamanhoArq);
    qsort(e, tamanhoArq/sizeof(sinasc), sizeof(sinasc), compara);
    f = fopen("sinasc-sp-2018-ordenado.dat", "wb");
    fwrite(e, sizeof(sinasc), tamanhoArq/sizeof(sinasc), f);

    fclose(arquivo);
    fclose(aux);
    fclose(f);
    free(e);

    FILE* gh = fopen("sinasc-sp-2018-ordenado.dat", "rb");
    sinasc ghDados;
    int ghqtd = fread(&ghDados, sizeof(sinasc), 1, gh);
    while(ghqtd > 0){
        printf("1:%.6s\n2:%.7s\n3:%.6s\n4:%.8s\n5:%.2s\n6:%.1s\n7:%.4s\n8:%.8s\n", ghDados.CODMUNNASC, ghDados.CODESTAB, ghDados.CODMUNRES, ghDados.DTNASC, ghDados.SEMAGESTAC, ghDados.SEXO, ghDados.PESO, ghDados.DTNASCMAE);
        ghqtd = fread(&ghDados, sizeof(sinasc), 1, gh);
    }
    fclose(gh);
    return 0;
}

