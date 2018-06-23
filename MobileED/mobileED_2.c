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
void area_de_trab (LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]);
void StoreED(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]);
void print_LLV(LLV *storeED);
void download_storeED(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]);
int verif_storeED(LLV *storeED,char nome[namesize]);
void add_meusApps(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL],int pos);
int add_fila(LLSE *meusApps, FILA *fila, App app);
void add_ini_LLDE_fila(FILA *fila, int disp);
void add_LLSE(LLSE *meusApps, App app, int disp, int pos, int local);
void add_LLV(LLV *storeED, App *temp);
void ordena_LLSE(LLSE *v, App app);
int busca_pos(LLSE *meusApps, int x);
int busca_app_fila(FILA *fila, char nome[namesize]);
int busca_app_LLSE(LLSE *meusApps,char nome[namesize]);
int busca_LLDEfila(FILA *v, int x);
int alocaNo(LLSE *v);
int aloca_na_fila(FILA * fila);
void remove_fila(FILA *fila, int x);
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


	//instanciando a FILA
	FILA FILA_app;
	FILA *fila;
	fila = &FILA_app;

	ini_LLV(storeED);
	ini_LLSE(meusApps);
	ini_FILA(fila);
	leitura(storeED);
	ini_tela(tela,meusApps);
	area_de_trab(storeED,meusApps,fila,tela);

	return 0;
}


/*
* Nome: area_de_trab(exibe menu com opçoes do mobileED)
* Função: exibe menu com opções do mobileED
* Funcionalidade: imprime opções para o usuario
* Retorno: void
*/
void area_de_trab (LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]){

	int op;

	printf("1. StoreED\nMobileED:\\>");
	scanf("%d", &op);

	switch(op){

		case 1: StoreED(storeED,meusApps,fila,tela);

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
void StoreED(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]){

	int i;

	system("cls");
	printf("#############################\n");
	printf("#  APLICATIVOS DISPONIVEIS  #\n");
	printf("#############################\n\n");
	print_LLV(storeED);
	download_storeED(storeED,meusApps,fila,tela);

	return;	

}


/*
* Nome: download_storeED(pede o nome do aplicativo para o usuario e informa se existe ou nao, e se deseja insta-
* lar.)
* Função: pede o nome do app, informa se ele nao existe, se deseja instalar e se deseja instalar outro app  
* Funcionalidade: após usuario entrar com o nome do app, chama a funçao que verifica se o app existe e a funcao
* para instalaçao, caso ele exista
* Retorno: void
*/
void download_storeED(LLV *storeED,LLSE *meusApps,FILA *fila,App tela[LIN][COL]){

	int op1,op2 = 1,pos = 0;
	char nome[namesize];

	while(op2 == 1){

		printf("\nEntre com o nome do app para instalar:\nMobileED:\\>");
		scanf("%s",nome);
		pos = verif_storeED(storeED,nome);//pega a posiçao do app na lista LLV
		if(pos < 0){
			system("cls");
			print_LLV(storeED);
			printf("\nAplicativo não encontrado.\n");
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
			return;
		}else{
			system("cls");
			print_LLV(storeED);
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
		printf("%s já está instalado.\n",storeED->apps[pos].nome);
		return;
	}else{

		// construindo auxiliar
		
		aux.cod = storeED->apps[pos].cod;
		strcpy(aux.nome, storeED->apps[pos].nome);
		strcpy(aux.stat, storeED->apps[pos].stat);

		// insere na fila e depois de cheia, insere na LLSE
		stat = add_fila(meusApps,fila,aux);

		// se inseriu na lista meusApps, insere no menu
		if(stat) {

			// resetando menu
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
	print_LLV(storeED);
	printf("\n%s foi adicionado a fila de downloads.\n",storeED->apps[pos].nome);
	


	return;
}


void add_LLDE(LLDE *exe, App app, int disp, int pos, int local) {

	int i, x;

	switch(local) {
		// insere no inicio
	case 1:
		exe->vet[disp].prox = exe->ini;
		exe->vet[disp].ant = exe->vet[exe->ini].ant;
		exe->vet[exe->ini].ant = disp;
		exe->ini = disp;

		break;

		// insere no meio
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

		// insere no fim
	case 3:
		exe->vet[disp].prox = exe->vet[pos].prox;
		exe->vet[pos].prox = disp;
		exe->vet[disp].ant = pos;

		break;
	}
}


void removeLLDE(LLDE *exe, int x) {

	int i;

	i = buscaPosicaoLLDE(exe, -1);
	// removendo do inicio
	if(x == exe->ini) {
		exe->ini = exe->vet[x].prox;
		exe->vet[exe->vet[x].prox].ant = exe->vet[x].ant;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
		exe->vet[x].ant = i;
	}
	// removendo do fim
	else if(exe->vet[x].prox == -1) {
		exe->vet[exe->vet[x].ant].prox = exe->vet[x].prox;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
	} else { // removendo do meio
		exe->vet[exe->vet[x].ant].prox = exe->vet[x].prox;
		exe->vet[exe->vet[x].prox].ant = exe->vet[x].ant;
		exe->vet[x].prox = exe->disp;
		exe->disp = x;
		exe->vet[x].ant = i;
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

	// instanciando auxiliar
	App aux;
	// captura posicao disponivel
	x = aloca_na_fila(fila);

	// se fila estiver cheia
	if(x == -5) {

		// buscar a posicao do ultimo, para inseri-lo na LLSE
		y = busca_LLDEfila(fila, -1);
		// guarda o elemento y na variavel auxiliar
		aux = fila->vet[y].info;
		// remove o primeiro da fila
		remove_fila(fila, y);
		// insere o elemento removido nos meusApps
		ordena_LLSE(meusApps, aux);

		x = aloca_na_fila(fila);
		// elemento a ser inserido no fim da fila
		fila->vet[x].info = app;
		add_ini_LLDE_fila(fila, x);

		return 1;
	} else {
		fila->vet[x].info = app;
		// inserindo o primeiro elemento
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
	// guardando posicao disponivel para insercao
	x = alocaNo(v);
	// verificando se ha espaco para insercao
	y = busca_pos(v, -1);
	// guardando dado na posicao disponivel
	v->vet[x].info = app;
	// se LLSE nao esta cheio, pode inserir
	if(x != -5) {
		// inserindo no inicio
		if ( (app.cod < v->vet[v->ini].info.cod) || v->ini == -1 )
			add_LLSE(v,app,x,y,1);
		// inserindo no fim
		else if (app.cod >=  v->vet[y].info.cod)
			add_LLSE(v,app,x,y,3);
		// inseriondo no meio
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
		// insere no inicio
	case 1:
		meusApps->vet[disp].prox = meusApps->ini;
		meusApps->ini = disp;
		break;
		// insere no meio
	case 2:
		for(i = meusApps->ini; i != -1; i = meusApps->vet[i].prox)
			if(app.cod < meusApps->vet[i].info.cod)
				break;
		j = busca_pos(meusApps, i);
		meusApps->vet[disp].prox = meusApps->vet[j].prox;
		meusApps->vet[j].prox = disp;
		break;
		// inserir no fim
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
	// pega inicio do LLSE
	i = meusApps->ini;
	// percorre enquanto nao encontrar o fim
	while(i != -1) {
		// se proximo for igual a posicao procurada, achou a posicao de manipulacao
		if(meusApps->vet[i].prox == x)
			break;
		// seta o proximo
		i = meusApps->vet[i].prox;
	}
	// retorna posicao procurada
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

	// pega inicio do LLDE
	i = v->ini;
	// percorre enquanto nao encontrar o fim
	while(i != -1) {
		// se proximo for igual a posicao procurada, achou a posicao de manipulacao
		if(v->vet[i].prox == x)
			break;
		// seta o proximo
		i = v->vet[i].prox;
	}
	// retorna posicao procurada
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

	// se o disponivel por -2, significa que a lista esta cheia
	if(v->disp == -2)
		return -5;

	// pega disponivel
	d = v->disp;
	// seta o disponivel para o proximo
	v->disp = v->vet[v->disp].prox;
	// retorna o disponivel
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

	// se o disponivel for -2, significa que a lista esta cheia
	if(fila->disp == -2)
		return -5;

	// pega disponivel
	x = fila->disp;
	// seta o disponivel para o proximo
	fila->disp = fila->vet[fila->disp].prox;
	// retorna o disponivel
	return x;
}


int aloca_LLDE(LLDE *exe) {

	int x;

	// se o disponivel for -2, significa que a lista esta cheia
	if(exe->disp == -2)
		return -5;

	// pega disponivel
	x = exe->disp;
	// seta o disponivel para o proximo
	exe->disp = exe->vet[exe->disp].prox;
	// retorna o disponivel
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

	//verifica se a lista está cheia
	if((storeED->IA == storeED-> IL) && (storeED->FA == storeED->FL)){
		printf("A lista está cheia.\n");
		return;
	}

	if (storeED->IL == -1)//verifica se a lista está vazia e insere o primeiro elemento
	{
		storeED->IL = storeED->FL = storeED->IA;
		storeED->apps[storeED->IL].cod = temp->cod;
		strcpy(storeED->apps[storeED->IL].nome,temp->nome);
		strcpy(storeED->apps[storeED->IL].stat,temp->stat);
		return;
	}

	//verifica se o codigo do elemento é menor que o do primeiro elemento da lista
	if(temp->cod < storeED->apps[storeED->IL].cod){
		if (storeED->IL > storeED->IA)//verifica se há espaço à esquerda do primeira elemento
		{
			(storeED->IL)--;//novo inicio da lista
		}else{//ha espaço à direita
			for(i = storeED->FL; i >= storeED->IL; i--){//move os elementos para a direita liberando espaço no início
				storeED->apps[i+1].cod = storeED->apps[i].cod;
				strcpy(storeED->apps[i+1].nome,storeED->apps[i].nome);
				strcpy(storeED->apps[i+1].stat,storeED->apps[i].stat);
			}
			(storeED->FL)++;//reajusta o FL
		}
		//adiciona o elemento no IL
		storeED->apps[storeED->IL].cod = temp->cod;
		strcpy(storeED->apps[storeED->IL].nome,temp->nome);
		strcpy(storeED->apps[storeED->IL].stat,temp->stat);
		return;	

	//inserindo no fim da lista (caso o codigo do elemento seja maior que o do ultimo elemento da lista)
	}else if(temp->cod > storeED->apps[storeED->FL].cod){
	
		if (storeED->FA > storeED->FL)//verifica se ha espaço à direita do ultimo elemento
		{
			(storeED->FL)++;//novo fim da lista
		}else{//ha espaço à esquerda
			for(i = storeED->IL; i <= storeED->FL; i++){//move os elementos para à esquerda liberando espaço no final
				storeED->apps[i-1].cod = storeED->apps[i].cod;
				strcpy(storeED->apps[i-1].nome,storeED->apps[i].nome);
				strcpy(storeED->apps[i-1].stat,storeED->apps[i].stat);
			}
			(storeED->IL)--;//novo inicio da lista
		}
		storeED->apps[storeED->FL].cod = temp->cod;
		strcpy(storeED->apps[storeED->FL].nome,temp->nome);
		strcpy(storeED->apps[storeED->FL].stat,temp->stat);
		return;
	}else{
		//insere no meio
		for(i = storeED->IL; i <= storeED->FL;i++){
			if (temp->cod < storeED->apps[i].cod)//verifica se o codigo é menor que algum elemento do meio da lista
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

	// resetando menu
	for(i = 0; i < LIN; i++) {
		for(j = 0; j < COL; j++) {
			strcpy(tela[i][j].nome, "\t");
			strcpy(tela[i][j].stat, "\t");
			tela[i][j].cod = 0;
		}
	}

	cont = meusApps->ini;
	// preenchendo menu[][]
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

	// primeiro disponivel
	fila->disp = 0;
	// inicio da LLDE, mostrando que a lista esta vazia
	fila->ini = -1;
	// percorrendo todo o vetor e encadeando LLDE
	for(i = 0; i < MFila; i++) {
		fila->vet[i].prox = i + 1;
		fila->vet[i].ant = i - 1;
	}
	// setando ultimo elemento com -2
	fila->vet[MFila - 1].prox = -2;
}


void ini_LLDE(LLDE *exe) {

	int i;

	// primeiro disponivel
	exe->disp = 0;
	// inicio da LLDE, mostrando que a lista esta vazia
	exe->ini = -1;
	// percorrendo todo o vetor e encadeando LLDE
	for(i = 0; i < APPS; i++) {
		exe->vet[i].prox = i + 1;
		exe->vet[i].ant = i - 1;
	}
	// setando ultimo elemento com -2
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

	// primeiro disponivel
	meusApps->disp = 0;
	// inicio da LLSE, aponta para -1, simbolizando q a lista esta vazia
	meusApps->ini = -1;
	// o ultimo aponta para null, no caso -2
	meusApps->vet[APPS - 1].prox = -2;
	// o atual aponta para o proximo
	for(i = 0; i < (APPS - 1); i++)
		meusApps->vet[i].prox = i + 1;


	return;
}


/*
* Nome: print_LLV(exibe a lista de aplicativos em sua ordem)
* Função: exibe a lista de aplicativos para download
* Funcionalidade: imprime os aplicativos em sua ordem para o usuario escolher
* Retorno: void
*/
void print_LLV(LLV *storeED){

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
