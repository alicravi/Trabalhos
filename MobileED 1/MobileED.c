#include <stdio.h>
#include <string.h>
#include <locale.h>

#define LIN 3
#define COL 4
#define APPS 15


typedef struct
{
    char nome[40];
    int num;
}App;

typedef struct
{
    char app[40];
    int num;
}Tela;

typedef struct
{
    char app[40];
    int num;
}AppRumED;

typedef struct 
{
	char app[40];
	int num;
}MeusAppsED;

typedef struct 
{
	char app[40];
	int num;
}Vet;


//protótipos das funções

//tarefas
int main();
void area_de_trab(App app[APPS],Tela tela[LIN][COL],MeusAppsED meusApps[APPS],AppRumED exe[APPS],Vet vet[12]);
void gravar(FILE *f);
void leitura(FILE *f,App app[APPS]);
void storeED(App app[APPS],Tela tela[LIN][COL],MeusAppsED meusApps[APPS]);
void instalar(int op,App app[APPS],Tela tela[LIN][COL]);
int instalados(int op, App app[APPS],MeusAppsED meusApps[APPS]);
void meusAppsED(MeusAppsED meusApps[APPS],Tela tela[LIN][COL], Vet vet[12],AppRumED exe[APPS]);
void executar(int op,AppRumED exe[APPS],MeusAppsED meusApps[APPS]);
void appRumED(AppRumED exe[APPS]);
int interromper(int op,AppRumED exe[APPS]);
int desinstalar(int op,MeusAppsED meusApps[APPS],Tela tela[LIN][COL],Vet vet[12],AppRumED exe[APPS]);

//auxiliares
void ini_mat(Tela tela[LIN][COL]);
void ini_vet(AppRumED exe[APPS],Vet vet[12],MeusAppsED meusApps[APPS]);


int main()
{

	setlocale(LC_ALL,"");


    FILE *f;
    App app[APPS];
    Tela tela[LIN][COL];
    MeusAppsED meusApps[APPS];
    AppRumED exe[APPS];
    Vet vet[APPS];

    ini_vet(exe,vet,meusApps);
    ini_mat(tela);
    gravar(f);
    leitura(f,app);
    area_de_trab(app,tela,meusApps,exe,vet);


	return 0;
}


/* Nome: area_de_trab();
 * Funcionalidade: atualiza os elementos da matriz e imprime na area de trabalho todos os Apps 
 * instalados pelo usuário. Chama outras funçoes de acordo com a opçao do usuário.
*/
void area_de_trab(App app[APPS],Tela tela[LIN][COL],MeusAppsED meusApps[APPS],AppRumED exe[APPS],Vet vet[12]){


	int op,op2;

	do{

		//printf("\n\n\t\t\t####ÁREA DE TRABALHO####\n");
		printf("\n\n\t /*  ############################################## */\n");
		printf("\t /*  -------------- ÁREA DE TRABALHO -------------- */\n");
		printf("\t /*  ############################################## */\n\n");

		for (int l = 0; l < LIN; ++l)
		{

			for (int c = 0; c < COL; ++c)
			{
				if (tela[l][c].num != 0)
					printf("\t\t\t\t%d. %s",tela[l][c].num,tela[l][c].app);
			}

		}

	    printf("\nENTRE COM UMA DAS OPÇÕES ABAIXO OU COM O CÓDIGO DO APP PARA INICIALIZÁ-LO: \n");
	    printf("(Para acompanhar melhor amplie a janela.)\n\n");
	    printf("16. StoreED [Apps disponíveis para download.]\n");
	    printf("17. MeusAppsED [Apps instalados.]\n");
	    printf("18. AppRumED [Apps inicializados.]\n");
	    printf("0. Sair\n");
	    scanf("%d", &op);

	    if (op < 0 || op > 18)
	    	printf("\n\n\n\n!!! %d É UMA OPÇÃO INVÁLIDA. TENTE NOVAMENTE !!!", op);

	    if (op >= 1 && op <= 15)
	    	executar(op,exe,meusApps);

	    switch(op)
	    {

	    	case 16: storeED(app,tela,meusApps);break;
	    	case 17: meusAppsED(meusApps,tela,vet,exe);break;
	    	case 18: appRumED(exe);break;
	    	case 0: return;

	    }

	    op = -1;

	}while(op < 0 || op > 18);


}


/* Nome: storeED();
 * Funcionalidade: imprime para o usuário as informaçoes dos Apps disponíveis no arquivo MobileED e a
 * opção para download.
*/
void storeED(App app[APPS],Tela tela[LIN][COL],MeusAppsED meusApps[APPS]){


	int app_cod = 0;

	do{

		do{

			//printf("\n\nAPPS DISPONÍVEIS:\n");
			printf("\n\n\t /*  ############################################## */\n");
			printf("\t /*  ------------------ StoreED ------------------- */\n");
			printf("\t /*  ############################################## */\n\n");			

			for (int j = 0; j < APPS; ++j)
			{

				printf("\t\t\t%d. %s",app[j].num,app[j].nome);//lista os Apps disponíves para download

			}

			if (app_cod < 0 || app_cod > 15)
				printf("\n!!! ERRO: ESTE CÓDIGO NÃO EXISTE. TENTE NOVAMENTE !!!\n");

			if (app_cod == 1)
				printf("\n!!! APP JÁ INSTALADO !!!\n");

			if (app_cod == 2)
				printf("\n!!! APP INSTALADO COM SUCESSO !!!\n");

			printf("\nDigite o código do App para download ou 0 para sair do StoreED: ");
			scanf("%d", &app_cod);

		}while(app_cod < 0 || app_cod > 15);

		if (app_cod > 0 && app_cod <= 15)
		{
			instalar(app_cod,app,tela);//chama funçao instalar();
			app_cod = instalados(app_cod,app,meusApps);//chama a função instalados();
		}

	}while(app_cod != 0);


	return;
}


/* Nome: instalar();
 * Funcionalidade: confere se o app ja está gravado na matriz tela[][] e, caso nao esteja,
 * armazena as informações na matriz tela[][][] e no vetor MeusAppsED[][].
*/
void instalar(int op,App app[APPS],Tela tela[LIN][COL]){


	/*laço para conferir se o app escolhido ja esta na matriz tela[][]*/
	for (int i = 0; i < APPS; ++i)
	{

	 	if (op == app[i].num)//verifica se a opçao escolhida bate com o numero do app
	 	{

	 		for (int l = 0; l < LIN; ++l) //percorre as linhas da matriz tela[][]
	 		{

	 			for (int c = 0; c < COL; ++c)//percorre as colunas da matriz tela[][]
	 			{

	 				if (!strcmp(tela[l][c].app,app[i].nome))//confere se o app já foi gravado na matriz tela[][]
	 					return;

	 			}

	 		}

	 	}

	}

	/*laço para conferir se há espaço livre  ("App") na matriz tela[][],caso sim, grava o app escolhido*/
	for (int i = 0; i < APPS; ++i)
	{

	 	if (op == app[i].num)//verifica se a opçao escolhida é igual o numero do app
	 	{

	 		for (int l = 0; l < LIN; ++l) //percorre as linhas da matriz tela[][]
	 		{

	 			for (int c = 0; c < COL; ++c)//percorre as colunas da matriz tela[][]
	 			{

	 				if (!strcmp(tela[l][c].app,"App"))//confere se ha espaço livre ("App") na matriz tela[][]
	 				{

	 					strcpy(tela[l][c].app, app[i].nome);//armazena o nome do App escolhido no espaço vazio
	 					tela[l][c].num = app[i].num;
	 					return;//retorna à função storeED();

	 				}

	 			}

	 		}

	 	}

	}


}


/* Nome: instalados();
 * Funcionalidade: armazena as informações dos Apps escolhidos para download no vetor MeusAppsED[][];
*/
int instalados(int op, App app[APPS],MeusAppsED meusApps[APPS]){


	/*laço para conferir se o app escolhido ja esta no vetor MeusAppsED[][]*/
	for (int i = 0; i < APPS; ++i)//percorre o vetor app
	{

		if (op == app[i].num)//verifica se a opçao escolhida é igual o numero do app no vetor app
		{

			for (int j = 0; j < APPS; ++j)//percorre o vetor MeusAppsED
			{

				if (!strcmp(meusApps[j].app,app[i].nome))//verifica se app ja esta gravado no vetor MeusAppsED[][]
					return 1;
			}

		}

	}


	/*laço para conferir se há espaço livre  ("App") no vetor MeusAppsED[][] e gravar o app escolhido*/
	for (int i = 0; i < APPS; ++i)//percorre o vetor app
	{

		if (op == app[i].num)//verifica se a opçao escolhida bate com o numero do app no vetor app
		{

			for (int j = 0; j < APPS; ++j)//percorre o vetor MeusAppsED
			{

				if (meusApps[j].num == 0)//verifica se há espaço vazio(com o nome App) no vetor meusApps[]
				{

					strcpy(meusApps[j].app,app[i].nome);//armazena o nome do app no vetor app
					meusApps[j].num = app[i].num;
					return 2;

				}

			}

		}

	}


}


/* Nome: meusAppsED();
 * Funcionalidade: imprime as informações dos apps ja gravados no vetor MeusAppsED[][];
*/
void meusAppsED(MeusAppsED meusApps[APPS],Tela tela[LIN][COL], Vet vet[12],AppRumED exe[APPS]){


	int sim,op;

	sim = 0;
	for (int i = 0; i < APPS; ++i)
	{
		if (meusApps[i].num != 0)
			sim = 1;
	}

	if(sim == 1)
	{

		do{

			//printf("\n\n\t\t\t####MeusAppsED####\n");
		printf("\n\n\t /*  ############################################## */\n");
		printf("\t /*  ------------------ MeusAppsED ---------------- */\n");
		printf("\t /*  ############################################## */\n\n");			
	 
			for (int i = 0; i < APPS; ++i)
			{

				if (meusApps[i].num != 0)
					printf("\t\t\t\t%d. %s",meusApps[i].num,meusApps[i].app);

			}

			if (op == 1)
				printf("\n\n\n!!! ESTE APP NÃO ESTÁ INSTALADO !!!");

			if (op == 2)
				printf("\n!!! APP DESINSTALADO COM SUCESSO !!!");
				

			printf("\nEntre com o código do App para desinstalação ou 0 para sair: ");
			scanf("%d", &op);	

	    	if (op < 0 || op > 15)
	    		printf("\n\n\n\n!!! %d É UMA OPÇÃO INVÁLIDA. TENTE NOVAMENTE !!!", op);

			if (op > 0 && op <= 15)
				op = desinstalar(op,meusApps,tela,vet,exe);

		}while ((op < 0 || op > 15) || (op > 0 && op <= 15));//(op > 0 && op <= 15);

	}else{
		printf("\t\t\t\n\n\n!!! NÃO HÁ APPS INSTALADOS !!!");
		return;
	}	


	return;
}


/* Nome: desinstalar();
 * Funcionalidade: remove as informações do App na matriz tela[][] e nos vetores exe[] e meusApps[].
 * Reordena a matriz e os vetores.
*/
int desinstalar(int op,MeusAppsED meusApps[APPS],Tela tela[LIN][COL],Vet vet[12],AppRumED exe[APPS]){


	int sim = 0,cont = 0;

	for (int i = 0; i < APPS; ++i)
	{
		if (meusApps[i].num == op)//verifica se o app esta instalado
			sim = 1;
	}
		
	if (sim == 1)		
	{
		
		/*exclui as informações do app e reorganiza o vetor meusApps[]*/
		for (int i = 0; i < APPS; ++i)
		{
			
			if (meusApps[i].num == op)
			{
				
				meusApps[i].num = 0;

				for (int j = 0; j < APPS; ++j)
				{

					if (meusApps[j].num == 0)
					{
						
					meusApps[j].num = meusApps[j+1].num;
					strcpy(meusApps[j].app,meusApps[j+1].app);
					meusApps[j+1].num = 0;

					}

				}
			}
		}
		
		/*exclui as informações do app na matriz tela[][]*/
		for (int l = 0; l < LIN; ++l)
		{
			for (int c = 0; c < COL; ++c)
			{
				if (tela[l][c].num == op)
				{
					tela[l][c].num = 0;
					strcpy(tela[l][c].app,"App");
				}

			}
		}

		/*passa as informações na matriz tela[][] para o vetor vet[]*/
		for (int l = 0; l < LIN; ++l)
		{
			for (int c = 0; c < COL; ++c)
			{
				vet[cont].num = tela[l][c].num;
				strcpy(vet[cont].app,tela[l][c].app);
				cont++;
			}
		}

		/*passa as informações no vetor vet[] para a matriz tela[][]*/
		cont = 0;
		for (int l = 0; l < LIN; ++l)
		{
			for (int c = 0; c < COL; ++c)
			{
				tela[l][c].num = vet[cont].num;
				strcpy(tela[l][c].app,vet[cont].app);
				cont++;
			}
		}

		interromper(op,exe);

	}else
		return 1;


	return 2;
}


/* Nome: executar();
 * Funcionalidade: grava no vetor exe[] o nome do App escolhido para ser executado
*/
void executar(int op,AppRumED exe[APPS],MeusAppsED meusApps[APPS]){
	

	for (int i = 0; i < APPS; ++i)
	{
		if (exe[i].num == op)
		{
			printf("\n\n!!! APP JÁ ESTÁ EM EXECUÇÃO !!!");
			return;
		}
	}

	for (int i = 0; i < APPS; ++i)
	{
		if (op == meusApps[i].num)
		{
			for (int j = 0; j < APPS; ++j)
			{
				if (exe[j].num == 0)
				{
					strcpy(exe[j].app,meusApps[i].app);
					exe[j].num = meusApps[i].num;
					printf("\n\n\n!!! %s INICIALIZADO !!!.",exe[j].app);
					return;				
				}
			}
		}
	}

	printf("\n\n\n!!! APP NÃO ESTÁ INSTALADO !!!\n");


}


/* Nome: appRumED();
 * Funcionalidade: imprime para o usuário os Apps em execução
*/
void appRumED(AppRumED exe[APPS]){


	int sim,op;

	sim = 0;
	for (int i = 0; i < APPS; ++i)
	{
		if (exe[i].num != 0)
			sim = 1;
	}	


	if(sim == 1)
	{

		do{

			//printf("\n\n\t\t\t####AppRumED####\n");
			printf("\n\n\t /*  ############################################## */\n");
			printf("\t /*  ------------------- AppRumED ----------------- */\n");
			printf("\t /*  ############################################## */\n\n");			
	 
			for (int i = 0; i < APPS; ++i)
			{

				if (exe[i].num != 0)
					printf("\t\t\t\t%d. %s",exe[i].num,exe[i].app);

			}



			if (op == 1)
				printf("\n\n!!! ESTE APP NÃO FOI INICIALIZADO !!!");

			if (op == 2)
				printf("\n!!! APP INTERROMPIDO !!!");
				

			printf("\nEntre com o código do App para interrompê-lo ou 0 para sair: ");
			scanf("%d", &op);	

	    	if (op < 0 || op > 15)
	    		printf("\n\n\n\n!!! %d É UMA OPÇÃO INVÁLIDA. TENTE NOVAMENTE !!!", op);			

			if (op > 0)
				op = interromper(op,exe);


		}while((op > 0 && op <= 15) || (op < 0 || op > 15));

	}else{
		printf("\t\t\t\n\n\n!!! NÃO HÁ APPS INICIALIZADOS !!!");
		return;
	}	


	return;
}


/* Nome: interromper();
 * Funcionalidade: retira as informações do app e ordena o vetor exe[].
*/
int interromper(int op,AppRumED exe[APPS]){


	int sim = 0,cont = 0;

	for (int i = 0; i < APPS; ++i)
	{
		if (exe[i].num == op)//verifica se o app esta instalado
			sim = 1;
	}
		
	if (sim == 1)		
	{
		
		/*exclui as informações do app e reorganiza o vetor exe[]*/
		for (int i = 0; i < APPS; ++i)
		{
			
			if (exe[i].num == op)
			{
				
				exe[i].num = 0;

				for (int j = 0; j < APPS-1; ++j)
				{

					if (exe[j].num == 0)
					{
						
					exe[j].num = exe[j+1].num;
					strcpy(exe[j].app,exe[j+1].app);
					exe[j+1].num = 0;

					}

				}
			}
		}

	}else
		return 1;


	return 2;
}


/* Funcionalidade: le todos os nomes de apps gravados previamente no arquivo MobileED e carrega
* Nome: leitura();
* as informações no vetor app[].
*/
void leitura(FILE *f,App app[15]){


	f = fopen ("MobileED.txt", "r");

	for (int i = 0; i < APPS; ++i)
	{

		fgets(app[i].nome, sizeof(app[i].nome),f);
		app[i].num = i+1;

	}


	return;
}


/* Nome: gravar();
* Funcionalidade: cria arquivo MobileED e grava todos os Apps.
*/
void gravar(FILE *f){


	f = fopen("MobileED.txt","w");
	if (f == NULL)
	{
		printf("Arquivo não pode ser criado.\n");
		return;
	}

	fprintf(f, "WhatsApp\n");
	fprintf(f, "Facebook\n");
	fprintf(f, "YouTube\n");
	fprintf(f, "Instagram\n");
	fprintf(f, "Twitter\n");
	fprintf(f, "Skype\n");
	fprintf(f, "Telegram\n");
	fprintf(f, "Netflix\n");
	fprintf(f, "Spotify\n");
	fprintf(f, "Linkedln\n");
	fprintf(f, "Moovit\n");
	fprintf(f, "Tumblr\n");
	fprintf(f, "Dead Trigger 2\n");
	fprintf(f, "Reddit\n");
	fprintf(f, "Snapchat\n");

	fclose(f);


	return;
}


/* Nome: ini_mat();
 * Funcionalidade: inicializa a matriz do tipo struct
*/
void ini_mat(Tela tela[LIN][COL]){


    for (int i = 0; i < LIN; ++i)
    {
    	for (int j = 0; j < COL; ++j)
    	{

    		strcpy(tela[i][j].app, "App");
    		tela[i][j].num = 0;

    	}
    }


	return;
}


/* Nome: ini_vet();
 * Funcionalidade: inicializa o vetores do tipo struct
*/
void ini_vet(AppRumED exe[APPS],Vet vet[12],MeusAppsED meusApps[APPS]){


	for (int i = 0; i < APPS; ++i)
	{

		vet[i].num = 0;
		strcpy(vet[i].app, "App");
		strcpy(meusApps[i].app,"App");
		meusApps[i].num = 0;
		strcpy(exe[i].app,"App");
		exe[i].num = 0;		

	}


	return;
}