/*
 *
 * Copyright (c) 2005-2013 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"



#define num_processors 3 //número de núcleos escravos
#define tam_vet 11 //tamanho do vetor de numeros randomicos


static volatile int flag = 0;
static volatile int print = 0;


static volatile long vet[tam_vet];//vetor para os números randomicos
static volatile double matriz[tam_vet][3];//matriz para armazenar o número a zaiz quadrada dele e o thread de calculo


static volatile long operacoes; //numero de operçoes para cada processador

int master(int id){

    int i;
    while(flag) {}
    operacoes = tam_vet/num_processors;

    for(i=0; i<tam_vet; i++) {//for para criar os némeros randomicos
        vet[i] = rand() % 1000000;//adiciona os números randomicos no vertor
    }

    flag = 1;
    while(print!=num_processors){}

    printf("\n Tabela com raiz quadrada dos numeros \n");
    for(i=0; i<tam_vet; i++) {//mostra os o valor inicial, a raiz desse valor e a thred que executou
        printf("        %.0f - %.4f - %.0f \n", matriz[i][0], matriz[i][1], matriz[i][2]);
    }

    flag = 0;
    return 1;
}

int slave(int id){
    

    while(!flag) {}

    int i;
    int indice = (id-1)*operacoes;
    long valor;
    long resto = 0; // variavel usada para realizra todos os calculos do vetor se (tam_vet % num_processors) != 0
    if(id == num_processors){
        resto = (tam_vet - (operacoes * num_processors));
    }
    for(i=0; i<(operacoes+resto); i++){
        valor = vet[indice+i];

        double x1;
        double x2, w1, w2;
        x1=valor/2;
        x2=((x1+(valor/x1))/2);
        do{
            w1 = x2;
            x1=x2;
            x2=((x1+(valor/x1))/2);
            w2 = x2;
        }while(w1 != w2);
        
        matriz[indice+i][0] = vet[indice+i];//salva o valor do vetor na matrix
        matriz[indice+i][1] = x2;
        matriz[indice+i][2] = id;
    }

    print++;
    while(flag){}

    return 1;
}



int main(int argc, char **argv) {

    int id = impProcessorId();

    printf("CPU %d starting...\n", id);

    if(id == 0){
        master(id);
    }else{
        slave(id);
    }

    return 1;
}
