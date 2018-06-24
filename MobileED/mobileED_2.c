#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define namesize 50
#define APPS 15
#define LIN 3
#define COL 3
#define MFila 3


//structs para LLV
typedef struct
{
	char stat[namesize];
	char nome[namesize];
	int cod;
}App;

typedef struct 
{
	App apps[APPS];
	int IA,FA,IL,FL;
}LLV;


//structs para LLSE
typedef struct {
	App info;
	int prox;
} meusAppsED;

typedef struct {
	meusAppsED vet[APPS];
	int disp;
	int ini;
} LLSE;

//structs FILA e LLDE
typedef struct {
	App info;
	int prox, ant;
}NO_LLDE;

typedef struct {
	NO_LLDE vet[APPS];
	int disp;
	int ini;
}LLDE;

typedef struct {
	NO_LLDE vet[MFila];
	int disp;
	int ini;
}FILA;


//prototipos das funções
void leitura (LLV *storeED);
void area_de_trab (LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha);
void StoreED(LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha);
void AppsED(LLSE *meusApps,LLDE *exe,FILA *fila,App tela[LIN][COL]);
void appsRum(LLDE *exe,FILA *fila);
int appsRum_op(LLDE *exe,FILA *fila);
void apps_pilha(LLSE *pilha);
int meusAppsED_op(LLSE *meusApps,LLDE *exe,FILA *fila,App tela[LIN][COL]);
int menu_pilha(LLSE *pilha);
void download_storeED(LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha);
int verif_storeED(LLV *storeED,char nome[namesize]);
void run_app(LLSE *meusApps, LLDE *exe, int pos);
void stop_app(App tela[LIN][COL], LLDE *exe, LLSE *meusApps, int posicao);
void pipilha(LLSE *pilha);

void print_store(LLV *storeED);
void print_tela(App tela[LIN][COL]);
void print_apps_exec(LLDE *exe);
void print_pilha(LLSE * pilha);
void print_instalados(LLSE *meusApps);

void add_meusApps(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL],int pos);
int add_fila(LLSE *meusApps, FILA *fila, App app);
void add_ini_LLDE_fila(FILA *fila, int disp);
void add_LLSE(LLSE *meusApps, App app, int disp, int pos, int local);
void add_LLV(LLV *storeED, App *temp);
void add_LLDE(LLDE *exe, App app, int disp, int pos, int local);
void add_ini_pilha(LLSE *pilha, int disp);
void add_pilha(LLSE * pilha);

void ordena_LLSE(LLSE *v, App app);
void ordena_LLDE(LLDE *exe, App app) ;

int busca_pos(LLSE *meusApps, int x);
int busca_app_fila(FILA *fila, char nome[namesize]);
int busca_app_LLSE(LLSE *meusApps,char nome[namesize]);
int busca_LLDEfila(FILA *v, int x);
int busca_LLDE(LLDE *v, int x);
int busca_exe(LLDE *exe, char nome[namesize]);

int alocaNo(LLSE *v);
int aloca_na_fila(FILA * fila);
int aloca_LLDE(LLDE *exe);

void remove_fila(FILA *fila, int x);
void remove_LLDE(LLDE *exe, int x);
void remove_LLSE(LLSE *meusApps, int x);
void remove_pilha(LLSE *pilha);

void ini_LLDE(LLDE *exe);
void ini_tela(App tela[LIN][COL], LLSE *meusApps);
void ini_LLSE(LLSE *meusApps);
void ini_FILA(FILA *fila);
void ini_LLV(LLV *storeED);

int main(int argc, char const *argv[]){


	App tela[LIN][COL];
	FILE *f;

	//intanciando LLV
	LLV apps;
	LLV *storeED;
	storeED = &apps;

	//instanciando LLSE
	LLSE meusA;
	LLSE *meusApps;
	meusApps = &meusA;
	LLSE p;
	LLSE *pilha;
	pilha = &p;

	//instancianado LLDE
	LLDE appsRumED;
	LLDE *exe;
	exe = &appsRumED;

	//instanciando a FILA
	FILA FILA_app;
	FILA *fila;
	fila = &FILA_app;

	ini_LLDE(exe);
	ini_LLV(storeED);
	ini_LLSE(meusApps);
	ini_LLSE(pilha);
	ini_FILA(fila);
	leitura(storeED);
	ini_tela(tela,meusApps);
	area_de_trab(storeED,meusApps,fila,exe,tela,pilha);

	return 0;
}


/*
* Nome: area_de_trab(exibe menu com opçoes do mobileED)
* Função: exibe menu com opções do mobileED
* Funcionalidade: imprime opções para o usuario
* Retorno: void
*/
void area_de_trab (LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha){


	int op;


	while(1){
		print_tela(tela);
		printf("\n");
		printf("1. StoreED\t 2. meusAppsED\t 3. AppRumED\t 4. Pilha\t 0. Sair\nMobileED:\\>");
		scanf("%d", &op);


		switch(op){

			case 0: exit(1);
			case 1: StoreED(storeED,meusApps,fila,exe,tela,pilha);break;
			case 2: AppsED(meusApps,exe,fila,tela);break;
			case 3: appsRum(exe,fila);break;
			case 4: pipilha(pilha);break;

		}
	}

	return;
}


void pipilha(LLSE *pilha){

	int op;

	system("cls");
	printf("#################################\n");
	printf("#              Pilha            #\n");
	printf("#################################\n\n");
	print_pilha(pilha);
	op = menu_pilha(pilha);
	if (op == 0)
	{
		system("cls");
		return;
	}

	return;
}


int menu_pilha(LLSE *pilha){

	int op;

	printf("\n\n");
	printf("1. inserir\t 2. remover\t 0. voltar\nMobileED:\\>");
	scanf("%d",&op);

	if (op == 0)
		return 0;

	if (op == 1)
	{
		add_pilha(pilha);
		system("cls");
	}else if (op == 2){
		remove_pilha(pilha);
		system("cls");
	}


	pipilha(pilha);
}


void add_pilha(LLSE * pilha) {

	int pos;
	char temp[APPS];
	char tam[20];

	pos = alocaNo(pilha);
	if(pos == -5)
		return;

	strcpy(temp, "");
	strcat(temp, "App ");

	sprintf(tam, "%d", pos);

	strcat(temp, tam);
	strcpy(pilha->vet[pos].info.nome, temp);

	pilha->vet[pos].info.cod = pos;

	add_ini_pilha(pilha,pos);
}


void remove_pilha(LLSE *pilha) {

	int i, pos;

	pos = busca_app_LLSE(pilha, pilha->vet[pilha->ini].info.nome);

	if(pos == -1) {
		printf("Nao foi possivel desempilhar.\n");
	} else {
		pilha->ini = pilha->vet[pos].prox;
		pilha->vet[pos].prox = pilha->disp;
		pilha->disp = pos;
	}
}


void print_pilha(LLSE * pilha) {
	int i;

	apps_pilha(pilha);
}


void apps_pilha(LLSE *pilha) {
	int i;

	for(i = pilha->ini; i != -1; i = pilha->vet[i].prox) {
		printf("%s  \t\n", pilha->vet[i].info.nome);
	}
}



void add_ini_pilha(LLSE *pilha, int disp) {
	pilha->vet[disp].prox = pilha->ini;
	pilha->ini = disp;
}



void appsRum(LLDE *exe,FILA *fila){

	int op;

	system("cls");
	printf("#################################\n");
	printf("#            AppsRumED          #\n");
	printf("#################################\n\n");
	print_apps_exec(exe);
	printf("\n\n");
	op = appsRum_op(exe,fila);
	if (op == 0)
	{
		system("cls");
		return;
	}

}


int appsRum_op(LLDE *exe,FILA *fila){

	char nome[namesize];
	int pos,op,op2;
	FILA *aux;

	printf("\n");
	printf("1. Interromper\t0. Sair\nMobileED:\\>");
	scanf("%d",&op);

	if(op == 1){

		printf("Digita o nome do App:\nMobileED:\\>");
		scanf("%s",nome);
		pos = busca_exe(exe,nome);
		if (pos < 0)
		{
			system("cls");
			appsRum(exe,fila);
			printf("App nao encontrado.\n");
		}else{
			printf("Deseja interromper o App %s ?\n1. sim\t2. nao\nMobileED:\\>",nome);
			scanf("%d",&op2);
			if (op2 == 1)
			{
				aux = fila;
				remove_LLDE(exe,pos);
				fila = aux;
			}
		}

	}

}



void print_tela(App tela[LIN][COL]){

	int i, j;


	for(i = 0; i < LIN; i++) {
		for(j = 0; j < COL; j++) {
			printf("%.2d. %s",tela[j][i].cod,tela[j][i].nome);
			printf("\t");
		}
		printf("\n");
	}
}


void AppsED(LLSE *meusApps,LLDE *exe,FILA *fila,App tela[LIN][COL]){

	int op;

	system("cls");
	printf("#################################\n");
	printf("#            meusAppsED         #\n");
	printf("#################################\n\n");
	print_instalados(meusApps);
	printf("\n\n");
	op = meusAppsED_op(meusApps,exe,fila,tela);
	if (op == 0)
	{
		system("cls");
		return;
	}

	return;
}


void print_instalados(LLSE *meusApps) {
	int i;

	for(i = meusApps->ini; i != -1; i = meusApps->vet[i].prox) {
		printf("\t%.2d. %s\n", meusApps->vet[i].info.cod,meusApps->vet[i].info.nome);

	}
}


int meusAppsED_op(LLSE *meusApps,LLDE *exe,FILA *fila,App tela[LIN][COL]){

	int op1,op2,pos;
	FILA *aux;
	char nome[namesize];

	printf("1. Inicializar\t2. Desinstalar\t 0. Voltar\nMobileED:\\>");
	scanf("%d",&op1);

	if(op1 < 0 || op1 > 2){
		printf("Opcao invalida. Tente novamente.\n");
		meusAppsED_op(meusApps,exe,fila,tela);
	}

	switch(op1){

		case 0: 

				break;
		case 1:

				printf("Digite o nome do App: \nMobileED:\\>");
				scanf("%s",nome);
				pos = busca_app_LLSE(meusApps,nome);
				if (pos < 0)
				{
					system("cls");
					AppsED(meusApps,exe,fila,tela);
					printf("App nao encontrado.\n");
				}else{
					printf("%s foi encontrado!\n",nome);
					printf("Deseja inicializar o aplicativo? \n1. sim\t2. nao\nMobileED:\\>");
					scanf("%d",&op2);
					if (op2 == 1)
					{
						run_app(meusApps,exe,pos);
					}

				}
				break;

		case 2:

				printf("Digite o nome do App: \nMobileED:\\>");
				scanf("%s",nome);

				pos = busca_app_LLSE(meusApps,nome);

				if (pos == -1)
				{
					system("cls");
					AppsED(meusApps,exe,fila,tela);
					printf("App não encontrado.\n");
				}else{
					printf("%s foi encontrado!\n",nome);
					printf("Deseja desinstalar o App? \n1. sim\t2. nao\nMobileED:\\>");
					scanf("%d",&op2);
					if (op2 == 1)
					{
						aux = fila;
						stop_app(tela,exe,meusApps,pos);
						fila = aux;
					}
				}
				break;
		
	}


	return 0;
}


void run_app(LLSE *meusApps, LLDE *exe, int pos){

	if(busca_exe(exe, meusApps->vet[pos].info.nome) > -1) {
		printf("%s ja esta em execucao.\n", meusApps->vet[pos].info.nome);
	} else {
		App aux;
		aux.cod = meusApps->vet[pos].info.cod;
		strcpy(aux.nome, meusApps->vet[pos].info.nome);
		strcpy(aux.stat, "Em Exec.");
		ordena_LLDE(exe, aux);
	}
}



void stop_app(App tela[LIN][COL], LLDE *exe, LLSE *meusApps, int posicao) {

	int i, j, cont;
	int pos = busca_exe(exe,meusApps->vet[posicao].info.nome);

	App aux;
	aux.cod = exe->vet[pos].info.cod;
	strcpy(aux.nome, exe->vet[pos].info.nome);
	strcpy(aux.stat, "Disponivel");

	if(pos > -1) {
		remove_LLDE(exe,pos);
		remove_LLSE(meusApps,posicao);
	} else { 
		remove_LLSE(meusApps,posicao);
	}

	for(i = 0; i < LIN; i++) {
		for(j = 0; j < COL; j++) {
			printf("%s ---- %s\n", tela[i][j].nome, meusApps->vet[posicao].info.nome);
			if(!strcmp(tela[i][j].nome, meusApps->vet[posicao].info.nome)) {
				strcpy(tela[i][j].nome, "\t");
				tela[i][j].cod = 0;
				cont = 1;
				break;
			}
		}
		if(cont) {
			break;
		}
	}
	printf("%s foi desinstalado com sucesso.\n", exe->vet[posicao].info.nome);
}



void remove_LLSE(LLSE *meusApps, int x) {

	int i, j, k, controle;
	
	i = busca_pos(meusApps,x);

	if(x == meusApps->ini) {
		meusApps->ini = meusApps->vet[x].prox;
		meusApps->vet[x].prox = meusApps->disp;
		meusApps->disp = x;
	} else { 
		meusApps->vet[i].prox = meusApps->vet[x].prox;
		meusApps->vet[x].prox = meusApps->disp;
		meusApps->disp = x;
	}

	return;
}



/*
* Nome: StoreED(lista aplicativos para donwload)
* Função: lista aplicativos disponíveis para download
* Funcionalidade: imprime aplicativos disponíveis para download, verifica se o aplicativo existe e se já se encontra
* no vetor meusApps(se já está instalado)
* Retorno: void
*/
void StoreED(LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha){

	system("cls");
	printf("#####################################\n");
	printf("#               StoreED             #\n");
	printf("#####################################\n\n");
	print_store(storeED);
	download_storeED(storeED,meusApps,fila,exe,tela,pilha);

	return;	

}


void print_apps_exec(LLDE *exe) {
	
	int i;

	for(i = exe->ini; i != -1; i = exe->vet[i].prox) {
		printf("\t%.2d. %s", exe->vet[i].info.cod,exe->vet[i].info.nome);

	}
}



/*
* Nome: download_storeED(pede o nome do aplicativo para o usuario e informa se existe ou nao, e se deseja insta-
* lar.)
* Função: pede o nome do app, informa se ele nao existe, se deseja instalar e se deseja instalar outro app  
* Funcionalidade: após usuario entrar com o nome do app, chama a funçao que verifica se o app existe e a funcao
* para instalaçao, caso ele exista
* Retorno: void
*/
void download_storeED(LLV *storeED,LLSE *meusApps,FILA *fila,LLDE *exe,App tela[LIN][COL],LLSE *pilha){

	int op1,op2 = 1,pos = 0;
	char nome[namesize];

	while(op2 == 1){

		printf("\nEntre com o nome do app para instalar:\nMobileED:\\>");
		scanf("%s",nome);
		pos = verif_storeED(storeED,nome);//pega a posiçao do app na lista LLV
		if(pos < 0){
			system("cls");
			print_store(storeED);
			printf("\nAplicativo nao encontrado.\n");
		}else{
			printf("\nDeseja instalar %s?\n1.sim\t2.nao\nMobileED:\\>",nome);
			scanf("%d",&op1);
			if(op1 == 1)
				if (busca_app_fila(fila,nome) > -1)//verifica se app ja esta na fila
				{
					printf("%s já está na fila de downloads.\n",nome);
				}else{
					add_meusApps(storeED,meusApps,fila,tela,pos);
				}
		}

		do{
			printf("Deseja instalar outro app?\n1.sim\t2.nao\nMobileED:\\>");
			scanf("%d",&op2);
			if (op2 > 2 || op2 < 1)
				printf("Opção invalida.\n");
		}while(op2 > 2 || op2 < 1);

		if (op2 == 2){
			system("cls");
			area_de_trab(storeED,meusApps,fila,exe,tela,pilha);
			return;
		}else{
			system("cls");
			print_store(storeED);
		}

	}


	return;
}


/*
* Nome: add_meusApps(insere na fila e, quando cheia, insere na LLSE meusApps e no vetor tela)
* Função: insere app na fila e, quando cheia, insere o app na LLSE meusApps
* Funcionalidade: insere na fila e, qdo cheia, insere na LLSE meusApps e no vetor tela 
* Retorno: void
*/
void add_meusApps(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL],int pos){

	int i,j,k,cont = 0,stat;
	App aux;


	if (busca_app_LLSE(meusApps,storeED->apps[pos].nome) > -1)
	{
		printf("%s ja esta instalado.\n",storeED->apps[pos].nome);
		return;
	}else{
		aux.cod = storeED->apps[pos].cod;
		strcpy(aux.nome, storeED->apps[pos].nome);
		strcpy(aux.stat, storeED->apps[pos].stat);

		stat = add_fila(meusApps,fila,aux);

		if(stat) {

			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					strcpy(tela[i][j].nome, "\t");
					strcpy(tela[i][j].stat, "\t");
					tela[i][j].cod = 0;
				}
			}

			k = meusApps->ini;
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					if(tela[i][j].cod == 0 && k != -1) {
						strcpy(tela[i][j].nome, meusApps->vet[k].info.nome);
						tela[i][j].cod = meusApps->vet[k].info.cod;
						k = meusApps->vet[k].prox;
					}
				}
			}

		}
	}

	system("cls");
	print_store(storeED);
	printf("\n%s foi adicionado a fila de downloads.\n",storeED->apps[pos].nome);
	


	return;
}


void add_LLDE(LLDE *exe, App app, int disp, int pos, int local) {

	int i, x;

	switch(local) {

	case 1:
		exe->vet[disp].prox = exe->ini;
		exe->vet[disp].ant = exe->vet[exe->ini].ant;
		exe->vet[exe->ini].ant = disp;
		exe->ini = disp;

		break;

	case 2:
		for(i = exe->ini; i != -1; i = exe->vet[i].prox)
			if(app.cod < exe->vet[i].info.cod)
				break;
		x = exe->vet[i].ant;
		exe->vet[disp].prox = exe->vet[x].prox;
		exe->vet[x].prox = disp;
		exe->vet[disp].ant = x;
		exe->vet[exe->vet[disp].prox].ant = disp;

		break;

	case 3:
		exe->vet[disp].prox = exe->vet[pos].prox;
		exe->vet[pos].prox = disp;
		exe->vet[disp].ant = pos;

		break;
	}
}


void remove_LLDE(LLDE *exe, int x) {

	int i;

	i = busca_LLDE(exe, -1);

	if(x == exe->ini) {
		exe->ini = exe->vet[x].prox;
		exe->vet[exe->vet[x].prox].ant = exe->vet[x].ant;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
		exe->vet[x].ant = i;
	}

	else if(exe->vet[x].prox == -1) {
		exe->vet[exe->vet[x].ant].prox = exe->vet[x].prox;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
	} else { 
		exe->vet[exe->vet[x].ant].prox = exe->vet[x].prox;
		exe->vet[exe->vet[x].prox].ant = exe->vet[x].ant;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
		exe->vet[x].ant = i;
	}


	return;
}


void ordena_LLDE(LLDE *exe, App app) {
	int y, x;


	x = aloca_LLDE(exe);
	
	y = busca_LLDE(exe, -1);
	
	exe->vet[x].info = app;
	
	if(x != -5) {
		
		if(exe->ini == -1) {
			exe->vet[x].prox = exe->ini;
			exe->ini = x;
		} else if ( (app.cod< exe->vet[exe->ini].info.cod) )
			add_LLDE(exe,app,x,y,1);
		else if (app.cod >=  exe->vet[y].info.cod)
			add_LLDE(exe,app,x,y,3);
		else
			add_LLDE(exe,app,x,y,2);
	}
}



/*
* Nome: add_fila(insere na fila)
* Função: insere na fila
* Funcionalidade: insere o app na fila ou, caso esteja cheia,insere o app na lista meusApps
* Retorno: int
*/
int add_fila(LLSE *meusApps, FILA *fila, App app) {
	
	int x, y, i, j, cont;

	
	App aux;
	
	x = aloca_na_fila(fila);

	
	if(x == -5) {
		
		y = busca_LLDEfila(fila, -1);
		aux = fila->vet[y].info;
		remove_fila(fila, y);
		ordena_LLSE(meusApps, aux);
		x = aloca_na_fila(fila);
		fila->vet[x].info = app;
		add_ini_LLDE_fila(fila, x);

		return 1;
	} else {
		fila->vet[x].info = app;
		if(fila->ini == -1) {
			fila->vet[x].prox = fila->ini;
			fila->ini = x;
		} else
			add_ini_LLDE_fila(fila, x);

		return 0;
	}
}


/*
* Nome: add_ini_LLDE_fila(insere no fim da fila)
* Função: insere app no fim da fila, ou seja, no inicio do LLDE
* Funcionalidade: no LLDE insere no inicio, significa o fim da fila
* Retorno: void
*/
void add_ini_LLDE_fila(FILA *fila, int disp){

	fila->vet[disp].prox = fila->ini;
	fila->vet[disp].ant = fila->vet[fila->ini].ant;
	fila->vet[fila->ini].ant = disp;
	fila->ini = disp;

	return;

}


/*
* Nome: remove_lista()
* Função: remove app da fila de downloads
* Funcionalidade: remove o primeiro elemento da fila
* Retorno: void
*/
void remove_fila(FILA *fila, int x) {
	
	fila->vet[fila->vet[x].ant].prox = fila->vet[x].prox;
	fila->vet[x].prox = fila->disp;
	fila->disp = x;

	return;
}


/*
* Nome: ordena_LLSE(controla a ordenação do LLSE)
* Função: controla a ordenação do LLSE
* Funcionalidade: busca posicao disp para inserçao, se ha espaço disp, insere na posicao e ordena a lista se a
* inserçao tiver sido no inicio, meio ou fim
* Retorno: void
*/
void ordena_LLSE(LLSE *v, App app){

	int x, y;

	x = alocaNo(v);
	y = busca_pos(v, -1);
	v->vet[x].info = app;
	if(x != -5) {
		if ((app.cod < v->vet[v->ini].info.cod) || v->ini == -1 )
			add_LLSE(v,app,x,y,1);
		else if (app.cod >=  v->vet[y].info.cod)
			add_LLSE(v,app,x,y,3);
		else
			add_LLSE(v,app,x,y,2);
	}
}


/*
* Nome: add_LLSE(insere app na LLSE)
* Função: insere app na LLSE
* Funcionalidade: insere elemento no inicio, meio ou fim da LLSE
* Retorno: void
*/
void add_LLSE(LLSE *meusApps, App app, int disp, int pos, int local) {

	int i, j;

	switch(local) {

		case 1:
			meusApps->vet[disp].prox = meusApps->ini;
			meusApps->ini = disp;
			break;

		case 2:
			for(i = meusApps->ini; i != -1; i = meusApps->vet[i].prox)
				if(app.cod < meusApps->vet[i].info.cod)
					break;
			j = busca_pos(meusApps, i);
			meusApps->vet[disp].prox = meusApps->vet[j].prox;
			meusApps->vet[j].prox = disp;
			break;

		case 3:
			meusApps->vet[disp].prox = meusApps->vet[pos].prox;
			meusApps->vet[pos].prox = disp;
			break;
		default:
			printf("Erro: opcao de insercao invalida.\n");
			return;
	}
}


/*
* Nome: busca_pos(busca posicao do ultimo app da LLSE)
* Função: busca a posiçao do ultimo app da LLSE
* Funcionalidade: percorre a LLSE ate encontrar o ultimo elemento nela e retorna a posiçao dele
* Retorno: int (posiçao do ultimo elemento)
*/
int busca_pos(LLSE *meusApps, int x) {

	int i;

	i = meusApps->ini;

	while(i != -1) {
		if(meusApps->vet[i].prox == x)
			break;
		i = meusApps->vet[i].prox;
	}

	return i;
}


/*
* Nome: busca_app_fila(busca posiçao do app na fila)
* Função: busca a posiçao do app na fila
* Funcionalidade: percorre fila ate encontrar o app procurado, retornando sua posiçao
* Retorno: int (posicao do elemento na fila)
*/
int busca_app_fila(FILA *fila, char nome[namesize]) {
	
	int i;

	for(i = fila->ini; i != -1; i = fila->vet[i].prox)
		if(!strcmp(fila->vet[i].info.nome, nome))
			return i;

	return -1;
}


/*
* Nome: busca_app_LLSE(busca posiçao do elemento na LLSE)
* Função: busca posiçao do app na LLSE
* Funcionalidade: percorre a lista ate encontrar o elemento procurado, retorna sua posiçao
* Retorno: int (posiçao do elemento na lista)
*/
int busca_app_LLSE(LLSE *meusApps,char nome[namesize]){

	int i;

	for(i = meusApps->ini; i != -1; i = meusApps->vet[i].prox){
		if(!strcmp(meusApps->vet[i].info.nome, nome)){
			return i;
		}
	}

	return -1;
}


/*
* Nome: busca_LLDEfila(busca na LLDE a posiçao do elemento)
* Função: busca na LLDE a posicao do app procurado
* Funcionalidade: percorre a LLDE ate encontrar o elemento procurado, retornando sua posiçao
* Retorno: int (posiçao do elemento na lista)
*/
int busca_LLDEfila(FILA *v, int x) {

	int i;

	i = v->ini;
	while(i != -1) {
		if(v->vet[i].prox == x)
			break;
		i = v->vet[i].prox;
	}

	return i;
}


int busca_exe(LLDE *exe, char nome[namesize]) {
	int i;
	for(i = exe->ini; i != -1; i = exe->vet[i].prox) {
		if(!strcmp(exe->vet[i].info.nome, nome)) {
			return i;
		}
	}
	return -1;
}


int busca_LLDE(LLDE *v, int x) {

	int i;

	i = v->ini;

	while(i != -1) {
		if(v->vet[i].prox == x)
			break;
		i = v->vet[i].prox;
	}

	return i;
}


/*
* Nome: alocaNo(pega o disp na lista e seta o novo disp)
* Função: pega o disp na lista e seta o novo disp
* Funcionalidade: verifica se a lista esta cheia, se nao, pega o disp na lista e seta o novo disp (prox do disp)
* Retorno: int (o disp)
*/
int alocaNo(LLSE *v){

	int d;

	if(v->disp == -2)
		return -5;

	d = v->disp;
	v->disp = v->vet[v->disp].prox;

	return d;
}


/*
* Nome: aloca_na_fila(pega o disp na fila e seta o novo disp)
* Função: pega o disp da fila e seta o novo disp
* Funcionalidade: verifica se a fila esta cheia, se nao, pega o disp da fila e seta o novo disp (prox do disp)
* Retorno: int (o disp)
*/
int aloca_na_fila(FILA * fila) {

	int x;

	if(fila->disp == -2)
		return -5;

	x = fila->disp;
	fila->disp = fila->vet[fila->disp].prox;

	return x;
}


int aloca_LLDE(LLDE *exe) {

	int x;

	if(exe->disp == -2)
		return -5;

	x = exe->disp;
	exe->disp = exe->vet[exe->disp].prox;

	return x;
}


/*
* Nome: verif_storeED(verifica se o nome existe na lista)
* Função: verifica se o nome digitado pelo usuario existe na lista
* Funcionalidade: compara o nome digitado pelo usuario com os nomes existentes na lista de aplicativos para
* download, retorna 0 se nao existir e 1 se existir.
* Retorno: int
*/
int verif_storeED(LLV *storeED,char nome[namesize]){

	int i;

	for (i = storeED->IL; i <= storeED->FL; ++i)
		if (!strcmp(storeED->apps[i].nome,nome))
			return i;


	return -1;
}


/*
* Nome: add_LLV(insere, em ordem LLV, os dados que estavam no arquivo txt no vetor)
* Função: passa os dados que estavam no arquivo txt para o vetor 
* Funcionalidade: conceitos LLV sao usados para organizar a passagem dos dados que estavam no arquivo txt para
* o vetor
* Retorno: void
*/
void add_LLV(LLV *storeED, App *temp){

	int i,aux = 0;

	if((storeED->IA == storeED-> IL) && (storeED->FA == storeED->FL)){
		printf("A lista está cheia.\n");
		return;
	}

	if (storeED->IL == -1)
	{
		storeED->IL = storeED->FL = storeED->IA;
		storeED->apps[storeED->IL].cod = temp->cod;
		strcpy(storeED->apps[storeED->IL].nome,temp->nome);
		strcpy(storeED->apps[storeED->IL].stat,temp->stat);
		return;
	}

	if(temp->cod < storeED->apps[storeED->IL].cod){
		if (storeED->IL > storeED->IA)
		{
			(storeED->IL)--;
		}else{
			for(i = storeED->FL; i >= storeED->IL; i--){
				storeED->apps[i+1].cod = storeED->apps[i].cod;
				strcpy(storeED->apps[i+1].nome,storeED->apps[i].nome);
				strcpy(storeED->apps[i+1].stat,storeED->apps[i].stat);
			}
			(storeED->FL)++;
		}
		
		storeED->apps[storeED->IL].cod = temp->cod;
		strcpy(storeED->apps[storeED->IL].nome,temp->nome);
		strcpy(storeED->apps[storeED->IL].stat,temp->stat);
		return;	

	}else if(temp->cod > storeED->apps[storeED->FL].cod){
	
		if (storeED->FA > storeED->FL)
		{
			(storeED->FL)++;
		}else{
			for(i = storeED->IL; i <= storeED->FL; i++){
				storeED->apps[i-1].cod = storeED->apps[i].cod;
				strcpy(storeED->apps[i-1].nome,storeED->apps[i].nome);
				strcpy(storeED->apps[i-1].stat,storeED->apps[i].stat);
			}
			(storeED->IL)--;
		}
		storeED->apps[storeED->FL].cod = temp->cod;
		strcpy(storeED->apps[storeED->FL].nome,temp->nome);
		strcpy(storeED->apps[storeED->FL].stat,temp->stat);
		return;
	}else{
		//insere no meio
		for(i = storeED->IL; i <= storeED->FL;i++){
			if (temp->cod < storeED->apps[i].cod)
			{
				aux = i;
				break;
			}
		}
		if((storeED->IA == storeED->IL && storeED->FA == storeED->FL) || (aux > (storeED->FL - storeED->IL) + 2) || (aux < storeED->IA) || (storeED->IL == -1 && aux != 1)){
			return;
		}else{
			if(storeED->FL != storeED->FA) {
				for(i = storeED->FL; i >= storeED->IL + aux - 1; i--) {
					storeED->apps[i + 1].cod = storeED->apps[i].cod;
					strcpy(storeED->apps[i + 1].stat, storeED->apps[i].stat);
					strcpy(storeED->apps[i + 1].nome, storeED->apps[i].nome);
				}
				storeED->FL++;
				storeED->apps[storeED->IL + aux].cod = temp->cod;
				strcpy(storeED->apps[storeED->IL + aux].stat, temp->stat);
				strcpy(storeED->apps[storeED->IL + aux].nome, temp->nome);
			} else {
				for(i = storeED->IL; i <= storeED->IL + aux - 2; i++) {
					storeED->apps[i - 1].cod = storeED->apps[i].cod;
					strcpy(storeED->apps[i - 1].stat, storeED->apps[i].stat);
					strcpy(storeED->apps[i - 1].nome, storeED->apps[i].nome);
				}
				storeED->IL--;
				storeED->apps[storeED->IL + aux].cod = temp->cod;
				strcpy(storeED->apps[storeED->IL + aux].stat, temp->stat);
				strcpy(storeED->apps[storeED->IL + aux].nome, temp->nome);
			}
		}

		return;
	}

	return;
}


void ini_tela(App tela[LIN][COL], LLSE *meusApps){
	
	int i, j, cont = 0;

	for(i = 0; i < LIN; i++) {
		for(j = 0; j < COL; j++) {
			strcpy(tela[i][j].nome, "\t");
			strcpy(tela[i][j].stat, "\t");
			tela[i][j].cod = 0;
		}
	}

	cont = meusApps->ini;
	for(i = 0; i < LIN; i++) {
		for(j = 0; j < COL; j++) {
			if(meusApps->ini != -1) {
				strcpy(tela[i][j].nome, meusApps->vet[cont].info.nome);
				strcpy(tela[i][j].stat, meusApps->vet[cont].info.stat);
				tela[i][j].cod = meusApps->vet[cont].info.cod;
			} else {
				strcpy(tela[i][j].nome, "\t");
				strcpy(tela[i][j].stat, "\t");
				tela[i][j].cod = 0;
			}
			cont = meusApps->vet[cont].prox;
		}
	}
}


/*
* Nome: ini_FILA(inicializa as variaveis q controlam a fila)
* Função: inicializa as variaveis que controlam a fila
* Funcionalidade: insere valores nas variáveis pertencentes a struct fila
* Retorno: void
*/
void ini_FILA(FILA *fila) {

	int i;

	fila->disp = 0;
	fila->ini = -1;
	for(i = 0; i < MFila; i++) {
		fila->vet[i].prox = i + 1;
		fila->vet[i].ant = i - 1;
	}
	fila->vet[MFila - 1].prox = -2;
}


void ini_LLDE(LLDE *exe) {

	int i;

	exe->disp = 0;
	exe->ini = -1;
	for(i = 0; i < APPS; i++) {
		exe->vet[i].prox = i + 1;
		exe->vet[i].ant = i - 1;
	}
	exe->vet[APPS - 1].prox = -2;
}


/*
* Nome: ini_LLV(inicializa as variáveis controladoras da estrutura LLV)
* Função: inicializa as variaveis que controlam a estrutura LLV
* Funcionalidade: insere valores nas variáveis pertencentes a struct LLV
* Retorno: void
*/
void ini_LLV(LLV *storeED){

	storeED->IA = 0;
	storeED->FA = APPS;
	storeED->IL = storeED->FL = -1;

	for (int i = 0; i < APPS; ++i)
	{
		strcpy(storeED->apps[i].nome,"");
		strcpy(storeED->apps[i].stat,"");
		storeED->apps[i].cod = 0;
	}

	return;
}


void ini_LLSE(LLSE *meusApps) {

	int i;

	
	meusApps->disp = 0;
	meusApps->ini = -1;
	meusApps->vet[APPS - 1].prox = -2;
	for(i = 0; i < (APPS - 1); i++)
		meusApps->vet[i].prox = i + 1;


	return;
}


/*
* Nome: print_store(exibe a lista de aplicativos em sua ordem)
* Função: exibe a lista de aplicativos para download
* Funcionalidade: imprime os aplicativos em sua ordem para o usuario escolher
* Retorno: void
*/
void print_store(LLV *storeED){

	int i;

	for (i = storeED->IL; i <= storeED->FL; ++i)
		printf("%d. %s\n",storeED->apps[i].cod,storeED->apps[i].nome);

	return;
}


/*
* Nome: leitura(ler os dados no arquivo txt)
* Função: le o arquivo txt e passa os dados para a função de estrutura LLV
* Funcionalidade: le o arquivo txt, grava os dados nas variaveis e chama a funçao de inserir na estrutura LLV
* Retorno: void
*/
void leitura (LLV *storeED){

	FILE *f;
	int i;
	App temp;

	f = fopen("MobileED.txt", "r");

	if (f == NULL){
		printf("Erro ao abrir o arquivo MobileED.txt\n");
		exit(1);
	}else{
		while(!feof(f)){
			fscanf(f," %s %s %d ", temp.nome, temp.stat, &temp.cod);
			add_LLV(storeED, &temp);
		}
	}

	fclose(f);

	return;
}
