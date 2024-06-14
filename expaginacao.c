#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define RAMSIZE 3
#define NROPAGINAS 10
int pf = 0;
char acessos[100];
int paginas_qde_acessos[NROPAGINAS];
int ram[RAMSIZE];
int encontrada = 0;
int ctoi(char ch){
	return (ch -'0');
}
int ramVazia(int ram[RAMSIZE], int pagina){
	for(int i = 0; i < RAMSIZE; i++){
		if(ram[i] == -100){
			ram[i] = pagina;
			pf++;
			return 1;
		}	
	}
	return 0;
}
int pagina_encontrada(int ram[RAMSIZE], int pagina){
	for(int i = 0; i < RAMSIZE; i++){
		if(ram[i] == pagina){
			encontrada++;
			return 1;
		}	
	}
	return 0;
}
void substituir(int ram[RAMSIZE], int pagina){
	int menor = 0;
	for(int i = 0; i < RAMSIZE; i++){
		if(paginas_qde_acessos[ram[i]] < paginas_qde_acessos[ram[menor]])
			menor = i;	
	}
	ram[menor] = pagina;
	pf++;
}
int main(int argc, char *argv[]){
		for(int i = 0; i < RAMSIZE; i++)
		ram[i] = -100;	
	for(int i = 0; i < NROPAGINAS; i++)
		paginas_qde_acessos[i] = 0;
	int result = 0; 
	FILE *arq = fopen(argv[1], "r");
	if(arq == NULL){
		printf("Problemas na abertura do arquivo\n");
		return 0;	
	}
	result = fread(acessos, 1, 100, arq);
	printf("NRO de bytes lidos: %i\n", result--);
	for(int i = 0; i < result; i++){
		if(!ramVazia(ram, ctoi(acessos[i]))){
			if(!pagina_encontrada(ram,ctoi(acessos[i])))
				substituir(ram,ctoi(acessos[i]));		
		}
		paginas_qde_acessos[ctoi(acessos[i])]++;
		for(int i = 0; i < RAMSIZE; i++)
			printf("Estado da ram: ram[%i] = %i\n\n\n",i,ram[i]);
				
	}
			
	printf("Page Faults: %i\n\n", pf);
	printf("Encontradas: %i\n\n", encontrada);
	return 0;
	
}























