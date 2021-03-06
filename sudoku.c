#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Amaury Mario Ribeiro Neto

int vidas = 3;

float tempo,tempo2=0; //tempo 2 é o tempo carregado de um save
time_t t_iniciar,t_fim;  //tempo de jogo
int tabuleirox[9][9]; //matriz principal onde será salvo o jogo
int predefinida[9][9]; //matriz com o tabuleiro pre-definido

void imprime_regras(){
	system("clear");
	printf("\n-----------------------REGRAS DO JOGO SUDOKU------------------------\n\n");
	printf("O Sudoku E um passatempo, pra ser jogado por apenas uma pessoa\n");
	printf("que envolve raciocinio e logica.\n A ideia do jogo E bem simples:\n"); 
	printf("completar todas as 81 celulas usando numeros de 1 a 9 sem repetir\n");
	printf("os numeros numa mesma linha, coluna ou grade (3x3).\n\n");
	printf("---------------------------TEMPO DO JOGO----------------------------\n");
	printf("\nO tempo de jogo pode variar, os tres melhores tempos serao registrados");
	printf("para jogador e dificuldade.\n\n");
	printf("---------------------------VIDAS----------------------------\n");
	printf("\nO jogador inicia com 3 vidas, a cada inserção incorreta uma vida será perdida.\n");
	printf(" Caso o jogador perca zere vidas o jogo é finalizado;");
	printf("---------------------------LEGENDA----------------------------\n");
	printf("\nOs valores em verde ja sao preenchidos inicialmente e nao podem ser modificados.\n");
	printf(" Enquanto os valores inserido pelo usuario estaram com numeracao em branco.\n");
	printf(" As linhas e as colunas possuem numeracao em alaranjado para facilitar");
	printf(" a visualizacao das coordenadas.\n\n\n");
	printf("APERTE ENTER PARA RETORNAR AO MENU...\n");
	while(getchar()!='\n');
    getchar();
	system("clear");
	return;
}

void imprime_records(){
	char nome1[25], nome2[25], nome3[25];
	float tempo_record1,tempo_record2,tempo_record3; //tempo dos recordistas
	system("clear");
	printf("\n-----------------------------RECORDS--------------------------------\n\n");

	FILE *record=fopen("recordes.txt","r");
	if(record == NULL){
		system("clear");
		printf("ERRO NA ABERTURA DO ARQUIVO\n");
		sleep(1);
		return;
	}else{
		fscanf(record,"%f",&tempo_record1);
		fscanf(record,"%s",nome1);
		fscanf(record,"%f",&tempo_record2);
		fscanf(record,"%s",nome2);
		fscanf(record,"%f",&tempo_record3);
		fscanf(record,"%s",nome3);
		fclose(record);
		printf("--------------------------------------------------------------------\n");
		printf("1- %s\t\t\t\t\t\t %.3f minutos\n",nome1,tempo_record1);
		printf("2- %s\t\t\t\t\t\t %.3f minutos\n",nome2,tempo_record2);
		printf("3- %s\t\t\t\t\t\t %.3f minutos\n",nome3,tempo_record3);
	}
	
	printf("\nINSIRA QUALQUER VALOR PARA RETORNAR AO MENU...\n");
	while(getchar()!='\n');
    getchar();
	system("clear");
	return;	
}

//funçoes de verificacao sudoku----------------------------------------------------------

int verifica_linha(int col, int numero){

	for (int j = 0; j < 9; j++) {     //conferindo se possui o mesmo valor naquela linha
		//debug
		//printf("v %d na linha %d, coluna %d é igual a %d! ", numero, j+1, col+1, tabuleirox[j][col]); 
		if (tabuleirox[j][col] == numero)
			return 0;
	}
	return 1;
}

int verifica_coluna(int li, int numero){
	//printf("\ncoluna\n");
	for (int j = 0; j < 9; j++) {    //conferindo se possui o mesmo valor naquela coluna
		//debug
		//printf("!v: %d na linha %d, coluna %d é igual a %d! ", numero, li+1, j+1, tabuleirox[li][j]);
		if (tabuleirox[li][j] == numero) 
			return 0;
	}  

	return 1;
}

int verifica_submatriz(int li, int col, int numero){

	for (int j = li - (li % 3); j < (li - (li % 3)) +3; j++){
		for (int i= col - (col % 3); i < (col - (col % 3)) + 3; i++){
			//debug
			//printf("verificando submatriz... se %d na linha %d, coluna %d é igual a %d! ", numero, j+1, i+1, tabuleirox[j][i]);
			if (tabuleirox[j][i] == numero) 
				return 0;
		}
	}
	return 1;
}

int tentativa_de_colocar_numero (int li, int col, int numero){ //examina se o jogador acertou na inserção
	
	if(tabuleirox[li][col] == numero) //valor ja foi adicionado (bug caso repetisse)
		return 1;
	
	if ( !verifica_linha(col,numero) )
		return 0;

	if ( !verifica_coluna(li, numero) )
		return 0;
	
	if( !verifica_submatriz(li, col, numero))
		return 0;

	return 1; //valor passou nos testes e foi inserito corretamente
}

int checar_coordenada (int linha, int coluna){ //verificando se as coordenas são validas
	if (linha >= 0 && linha <9 && coluna >= 0 && coluna < 9) {
		if(predefinida[linha][coluna]== 0){
			return 1;
		}else{
			return 0;
		}
	}
	else
		return 0;
}

int checar_valor(int linha, int coluna, int numero){//verificando se o valor é válido
	if (numero >0 && numero <= 9) {
		return 1;
	}
	else {
		return 0;
  }
}

//funções auxiliares --------------------------------------------------------------------------------
int escolha_tabuleiro(int tabuleirox[][9],int predefinida[][9]){
	FILE *file;
	printf("Disponibilizamos 9 tabuleiros de sudokus.\n");
	int jogo_escolhido=-1;
	sleep(0.4);
	while(jogo_escolhido < 0 || jogo_escolhido > 9){

		printf("\nPor favor escolha um numero de 1 a 9 corresponde ao tabuleiro desejado:\n");
		scanf("%d", &jogo_escolhido);
		switch(jogo_escolhido){   //carrengar tabuleiro escolhido
			case 1: //jogo1
				file=fopen("tabuleiros/jogo1.txt","r");
				break;
			case 2: //jogo2
				file=fopen("tabuleiros/jogo2.txt","r");
				break;
			case 3: //jogo3
				file=fopen("tabuleiros/jogo3.txt","r");
				break;
			case 4: //jogo4
				file=fopen("tabuleiros/jogo4.txt","r");
				break;
			case 5: //jogo5
				file=fopen("tabuleiros/jogo5.txt","r");
				break;
			case 6: //jogo6
				file=fopen("tabuleiros/jogo6.txt","r");
				break;
			case 7: //jogo7
				file=fopen("tabuleiros/jogo7.txt","r");
				break;
			case 8: //jogo8
				file=fopen("tabuleiros/jogo8.txt","r");
				break;
			case 9: //jogo9
				file=fopen("tabuleiros/jogo9.txt","r");
				break;
			default: //jogo invalido retorna ao inicio dessa funçao
				printf("\nOpcao Invalida\n");
		}
	}
	if(file == NULL){
		system("clear");
		printf("ERRO! ARQUIVO DO TABULEIRO NAO ENCONTRADO.\n");
		sleep(1);
		exit(1);
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fscanf(file,"%d",&tabuleirox[i][j]);
		}
	}
	fclose(file);
	//salvando a matriz predefinida
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(tabuleirox[i][j]==0){
				predefinida[i][j]=0;
			}else{
				predefinida[i][j]=1;
			}
		}
	}
	system("clear");
	printf("Tabuleiro %d Iniciado\n", jogo_escolhido);
	sleep(0.4);
	printf("Bom Jogo\n\n");
	sleep(0.4);
	return jogo_escolhido;
}

void imprime_tabuleiro(int tabuleirox[][9],int predefinida[][9]){

	printf(" \x1b[33m  1  2  3   4  5  6   7  8  9\x1b[0m  \n");
	printf("++---------+---------+---------+\n");
	for (int i = 0; i < 9; i++) {
		printf("\x1b[33m%d\x1b[0m|",i+1);
		for (int j = 0; j < 9; j++) {
			if (tabuleirox[i][j] != 0)
				if(predefinida[i][j]== 0)  //if somente para printar colorido
					printf(" %d ", tabuleirox[i][j]);
				else
					printf(" \x1b[32m%d\x1b[0m ", tabuleirox[i][j]);
			else
				printf("   ");
			if (j % 3 == 2)
				printf("|");
		}
		if (i % 3 == 2)
			printf("\n++---------+---------+---------+");
		printf("\n");
	}
	printf("\n");
	sleep(0.4);
}

void salvar(int tabuleirox[][9],int jogo_escolhido,float tempo,int predefinida[][9]){
	FILE *salvo=fopen("salvo.txt","w");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fprintf(salvo,"%d ",tabuleirox[i][j]);  //salvando o jogo
		}
		fprintf(salvo,"\n");  //salvando o jogo
	}
	fprintf(salvo,"\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fprintf(salvo,"%d ",predefinida[i][j]);  //salvando o jogo
		}
		fprintf(salvo,"\n");
	}
	fprintf(salvo,"\n");
	fprintf(salvo,"%d\n", jogo_escolhido); //salvando o numero do tabuleiro
	t_fim = time(NULL);
	tempo= difftime(t_fim,t_iniciar);
	tempo= tempo/60;
	tempo= tempo + tempo2;
	fprintf(salvo,"%f\n", tempo); //salvando tempo
	fprintf(salvo,"%d",vidas);  //salvando o jogo
	fclose(salvo);
	printf("JOGO SALVO COM SUCESSO\n");
}

void melhores_tempos(float tempo,char jogador[]){
	char nome1[25], nome2[25], nome3[25];
	float tempo_record1,tempo_record2,tempo_record3; //tempo dos recordistas

	FILE *record=fopen("recordes.txt","r");
	if(record == NULL){
		printf("ERRO ARQUIVO RECORDES NAO ENCONTRADO\n");
		return;
	}
	fscanf(record,"%f",&tempo_record1);
	fscanf(record,"%s",nome1);
	fscanf(record,"%f",&tempo_record2);
	fscanf(record,"%s",nome2);
	fscanf(record,"%f",&tempo_record3);
	fscanf(record,"%s",nome3);
	fclose(record);
	if(tempo<tempo_record1){
		FILE *record=fopen("recordes.txt","w");
		tempo_record3=tempo_record2;
		tempo_record2=tempo_record1;
		tempo_record1=tempo;
		strcpy(nome3, nome2);
		strcpy(nome2, nome1);
		strcpy(nome1, jogador);
		fprintf(record,"%f\t",tempo_record1);
		fprintf(record,"%s\n",nome1);
		fprintf(record,"%f\t",tempo_record2);
		fprintf(record,"%s\n",nome2);
		fprintf(record,"%f\t",tempo_record3);
		fprintf(record,"%s\n",nome3);
		fclose(record);
	}else{
		if(tempo<tempo_record2){
		FILE *record=fopen("recordes.txt","w");
		tempo_record3=tempo_record2;
		tempo_record2=tempo;
		strcpy(nome3, nome2);
		strcpy(nome2, jogador);
		fprintf(record,"%f\t",tempo_record1);
		fprintf(record,"%s\n",nome1);
		fprintf(record,"%f\t",tempo_record2);
		fprintf(record,"%s\n",nome2);
		fprintf(record,"%f\t",tempo_record3);
		fprintf(record,"%s\n",nome3);
		fclose(record);
		}else{
			if(tempo<tempo_record3){
				FILE *record=fopen("recordes.txt","w");
				tempo_record3=tempo;
				strcpy(nome3, jogador);
				fprintf(record,"%f\t",tempo_record1);
				fprintf(record,"%s\n",nome1);
				fprintf(record,"%f\t",tempo_record2);
				fprintf(record,"%s\n",nome2);
				fprintf(record,"%f\t",tempo_record3);
				fprintf(record,"%s\n",nome3);
				fclose(record);
			}else{
				return;
			}
		}
	}
}

int final(){ //função para verificar se o tabuleiro foi concluido e para finalizar o jogo
	
	if(!vidas){
		printf("VOCE NAO TEM MAIS VIDAS");
		printf("\nAPERTE ENTER PARA RETORNAR AO MENU DO JOGO...\n");	
		while(getchar()!='\n');
			getchar();
		return 1;
	}
  	for (int i = 0; i < 9; i++) {
    	for (int j = 0; j < 9; j++) {
      		if (tabuleirox[i][j] == 0) { //celula nao preenchida jogo ainda n terminou
        		return 0; 
      		}
    	}
  	}
	printf("PARABENS TABULEIRO PREENCHIDO\n");
	char jogador[25];
	t_fim = time(NULL);
	tempo= difftime(t_fim,t_iniciar);
	tempo= tempo + tempo2;
	tempo= tempo/60;
	printf("DIGITE SEU NOME JOGADOR:\n");
	scanf("%s",jogador);
	printf("VOCE CONCLUIU O JOGO EM %.2f MINUTOS\n",tempo);
	printf("OBRIGADO POR JOGAR %s!!!\n\n",jogador);
	melhores_tempos(tempo,jogador);
	printf("\nAPERTE ENTER PARA RETORNAR AO MENU DO JOGO...\n");	
	while(getchar()!='\n');
		getchar();
	return 1;
}

int unica_submatriz(int li, int col, int numero){//é o unico valor possivel naquela submatriz
	
	//verifica se o valor também é possivel em mais alguma celula daquela submatriz
	for (int l = li - (li % 3); l < (li - (li % 3)) +3; l++){ //linha
		for (int c= col - (col % 3); c < (col - (col % 3)) + 3; c++){ //coluna
			if(tabuleirox[l][c] == 0){
				if(l != li || c != col){ //examinar celulas diferentes da celula passada
					//debug
					//printf("\n\nveri valor %d para a linha %d e a coluna %d\n", numero, l+1, c+1);
					if( verifica_linha(c,numero) && verifica_coluna(l,numero) )
						return 0;	
				}	
			}
		}
	}
	return 1;
}

//funções para o menu do jogo ------------------------------------------------------------------------
void dica(){
	
	int numero, resposta, possiveis_valores;
	for(int l=0; l<9; l++){ //percorrendo linhas
		for(int c=0; c<9; c++){ // percorrendo colunas
			if ( checar_coordenada(l, c) ) { //verificando se é uma celula vazio
				
				possiveis_valores = 0;
				for (int numero = 1; numero<10; numero++){  //testando todos os possiveis números para aquela celula vazia
					
					if(tabuleirox[l][c] == 0){
						if ( tentativa_de_colocar_numero(l, c, numero) ){
							//debug
							//printf("valor encontrado: LINHA %d E A COLUNA %d COM O VALOR %d.\n\n", l+1, c+1, numero);
							possiveis_valores++;
							resposta = numero;
							if( unica_submatriz(l,c,numero) ){
								printf("\x1b[32mDica: PREENCHER A LINHA %d E A COLUNA %d COM O VALOR %d\x1b[0m\n", l+1, c+1, resposta);
								//tabuleirox[l][c] = resposta;
								return;
							}
						}	
					}		
				}

				if(possiveis_valores == 1){ // encontra se so existe um valor possivel naquela celula
					printf("\x1b[32mDica: PREENCHER A LINHA %d E A COLUNA %d COM O VALOR %d\x1b[0m\n", l+1, c+1, resposta);
					//tabuleirox[l][c] = resposta;
					return;
				}
			}
		}
	}
	printf("Ops: NAO FOI POSSIVEL ENCONTRAR DICAS\n");
}

void resposta_tabuleiro(int jogo_escolhido, int matriz_resposta[][9]){
	FILE *file;

	switch(jogo_escolhido){
		case 1: //jogo1
			file=fopen("respostas/resposta1.txt","r");
			break;
		case 2: //jogo2
			file=fopen("respostas/resposta2.txt","r");
			break;
		case 3: //jogo3
			file=fopen("respostas/resposta3.txt","r");
			break;
		case 4: //jogo4
			file=fopen("respostas/resposta4.txt","r");
			break;
		case 5: //jogo5
			file=fopen("respostas/resposta5.txt","r");
			break;
		case 6: //jogo6
			file=fopen("respostas/resposta6.txt","r");
			break;
		case 7: //jogo7
			file=fopen("respotas/resposta7.txt","r");
			break;
		case 8: //jogo8
			file=fopen("respostas/resposta8.txt","r");
			break;
		case 9: //jogo9
			file=fopen("respostas/resposta9.txt","r");
			break;
	}
	if(file == NULL){
		system("clear");
		printf("ERRO! NAO FOI POSSIVEL ENCONTRAR ARQUIVO DE RESPOSTA\n");
		sleep(0.4);
		return;
	}
	system("clear");
	printf("RESPOSTA\n\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fscanf(file,"%d",&matriz_resposta[i][j]);
		}
	}
	fclose(file);
}

void remover_jogada(){
	int linha, coluna;
	printf("DIGITE A LINHA DO NUMERO QUE DESEJA REMOVER\n");
	scanf("%d",&linha);
  	printf("DIGITE A COLUNA DO NUMERO QUE DESEJA REMOVER\n");
  	scanf("%d",&coluna);
	if (checar_coordenada(linha-1, coluna-1) == 1) {  //checando numero entre 1 e 9
		tabuleirox[linha-1][coluna-1] = 0;
		system("clear");
		printf("VALOR REMOVIDO\n");
	}else{
      	system("clear");
		imprime_tabuleiro(tabuleirox,predefinida);
     	printf("NAO E POSSIVEL REMOVER ESSE NUMERO\n");
    }
}

void adicionar_jogada(){
	int linha, coluna, numero;
	printf("INSIRA A LINHA QUE DESEJA INSERIR O NUMERO\n");
	scanf("%d",&linha);
    printf("INSIRA A COLUNA QUE DESEJA INSERIR O NUMERO\n");
    scanf("%d",&coluna);
    printf("INSIRA O NUMERO ENTRE 1 A 9 QUE DESEJA INSERIR:\n");
    scanf("%d",&numero);
    if ( checar_coordenada(linha-1, coluna-1) ) {  //chamando função verificar numero
      	if ( checar_valor(linha-1, coluna-1, numero) ) {
          	if ( tentativa_de_colocar_numero(linha-1, coluna-1, numero) ) {
				tabuleirox[linha-1][coluna-1] = numero;
				system("clear");
				printf("VALOR ADICIONADO COM SUCESSO\n\n");
          	}else{
				imprime_tabuleiro(tabuleirox,predefinida);
				printf("VALOR INSERIDO NAO PODE SER ADICIONADO NESTA COORDENADA. UMA VIDA FOI PERDIDA.\n\n");
				vidas--;
          	}

        }else{
			imprime_tabuleiro(tabuleirox,predefinida);
			printf("NUMERO DIGITADO E INVALIDO.\n\n");
			return;
      	}

    }else{
		system("clear");
		imprime_tabuleiro(tabuleirox,predefinida);
		printf("COORDENADA DIGITADA E INVALIDA\n\n");
		return;
    }
}

int carregar_jogo(){
	int jogo_escolhido;
	FILE *save= fopen("salvo.txt","r");
	if(save == NULL){
		system("clear");
		printf("ERRO! NAO E POSSIVEL ENCONTRAR ARQUIVO SAVE\n");
		sleep(1);
		exit(0);
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fscanf(save,"%d",&tabuleirox[i][j]);
		}
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fscanf(save,"%d",&predefinida[i][j]);
		}
	}
	fscanf(save,"%d",&jogo_escolhido);
	fscanf(save,"%f",&tempo2);
	fscanf(save,"%d",&vidas);
	fclose(save);
	return jogo_escolhido;
}

void menu_jogo(int jogo_escolhido){//onde são printadas e decididas as escolhas dentro do jogo
	int alternativa = -1;
	t_iniciar = time(NULL); //iniciar
	int matriz_resposta[9][9];

	while(alternativa!=0 && !final() ){
		printf("\t\tTABULEIRO %d - VIDAS = %d\n\n", jogo_escolhido, vidas);
		imprime_tabuleiro(tabuleirox,predefinida); //imprimindo o jogo
		printf("1)ADICIONAR JOGADA\n2)REMOVER JOGADA\n3)DICA\n");
		printf("4)DESISTIR E OBTER A RESPOSTA DO SUDOKU\n5)SALVAR\n6)RETORNAR AO MENU PRINCIPAL\n0)SAIR\n");
		printf("INSIRA O NUMERO CORRESPONDENTE A SUA ACAO:\n");
		scanf("%d",&alternativa);
		switch (alternativa) {  
			case 0:
				system("clear");
				alternativa = -1;
				while(alternativa != 0 && alternativa!=1){
					printf("DESEJA SALVAR SEU PROGRESSO?\n");
					sleep(0.1);
					printf("APENAS 1 SAVE PODE EXISTIR,");
					printf(" CASO JA EXISTA OUTRO JOGO, SERA SOBREESCRITO)\n 1-SIM, SALVAR.\t\t\t0-NAO.\n\n");
					scanf("%d",&alternativa);
					switch (alternativa)
					{
						case 0:
							exit(0);
						case 1:
							salvar(tabuleirox,jogo_escolhido,tempo,predefinida);
							exit(0);
						default:
							system("clear");
							printf("OPCAO INVALIDA\n");
							sleep(0.4);
					}
				}
			case 1:
				system("clear");
				printf("----------INSERCAO---------\n");
				imprime_tabuleiro(tabuleirox, predefinida);
				adicionar_jogada();
				break;
			case 2:
				system("clear");
				printf("-----------REMOCAO-----------\n");
				imprime_tabuleiro(tabuleirox, predefinida);
				remover_jogada();
				break;
			case 3:
				system("clear");
				imprime_tabuleiro(tabuleirox, predefinida);
				dica();
				printf("\nAPERTE ENTER PARA RETORNAR AO MENU DO JOGO...\n");	
				while(getchar()!='\n');
        		getchar();
				break;
			case 4:
				system("clear");
				resposta_tabuleiro(jogo_escolhido, matriz_resposta);
				imprime_tabuleiro(matriz_resposta,predefinida);	
				printf("\nAPERTE ENTER PARA RETORNAR AO MENU PRINCIPAL...\n");
				while(getchar()!='\n');
        		getchar();	
				return;
			case 5:
				system("clear");
				while (alternativa != 0 && alternativa != 1){
					printf("APENAS 1 SAVE PODE EXISTIR, CASO JA EXISTA OUTRO JOGO ESTE SERA SOBREESCRITO)\nDESEJA CONTINUAR? 1- SALVAR\t\t\t0- CANCELAR\n\n");
					scanf("%d",&alternativa);
					switch (alternativa){
						case 0:
							break;
						case 1:
							salvar(tabuleirox,jogo_escolhido,tempo,predefinida);
							break;
						default:
							system("clear");
							printf("OPCAO INVALIDA\n");
							sleep(0.4);
					}
				}
				break;
			case 6:
			system("clear");
				alternativa = -1;
				while(alternativa != 0 && alternativa!=1){
					printf("DESEJA SALVAR SEU PROGRESSO?\n");
					sleep(0.1);
					printf("APENAS 1 SAVE PODE EXISTIR,");
					printf(" CASO JA EXISTA OUTRO JOGO, SERA SOBREESCRITO)\n 1-SIM, SALVAR.\t\t\t0-NAO.\n\n");
					scanf("%d",&alternativa);
					switch (alternativa)
					{
						case 0:
							return;
						case 1:
							salvar(tabuleirox,jogo_escolhido,tempo,predefinida);
							return;
						default:
							system("clear");
							printf("OPCAO INVALIDA\n");
							sleep(0.4);
					}
				}
			default:
				system("clear");
				printf("OPCAO INVALIDA\n");
				sleep(0.4);
		}
	}
}

// main --------------------------------
int main(){
	int escolha_inicial= 1, jogo_escolhido;
	printf("\nFeito por Amaury");
	while(escolha_inicial != 0){
		printf("\n-------------------------BEM-VINDO AO SUDOKU------------------------\n\n");
		printf("\t\t\t1-NOVO JOGO.\n\t\t\t2-CONTINUAR JOGO.\n\t\t\t3- LER REGRAS\n\t\t\t4- RECORDS\n\t\t\t0- SAIR.\n\n");
		printf("INSIRA ABAIXO O NUMERO CORRESPONDENTE A SUA ESCOLHA:\n");
		//setbuf(stdin,NULL);
		scanf("%d",&escolha_inicial);
		switch (escolha_inicial){
			case 0:
				exit(0);
			case 1:
				jogo_escolhido = escolha_tabuleiro(tabuleirox,predefinida);
				vidas = 3;
				menu_jogo(jogo_escolhido);
				break;
			case 2:
				jogo_escolhido = carregar_jogo();
				menu_jogo(jogo_escolhido);
				break;
			case 3:
				imprime_regras();
				break;
			case 4:
				imprime_records();
				break;
			case 99:
				system("clear");
				printf("Easter egg??? :O \n");
				printf("ESTE PROJETO FOI CRIADO POR AMAURY NETO\n");
				printf("Algoritmo e Estrutura de Dados - CURSO DE CIÊNCIA DA COMPUTAÇÃO UFSF 2017/2 (primeiro periodo)\n");
				break;
			default:
				system("clear");
				printf("ESCOLHA INVALIDA! PoR FAVOR DIGITE UMA OPCAO VALIDA\n\n");
		}
	}
	return 0;
}


//setbuf(stdin,NULL); LIMPEZA DE BUFFER
