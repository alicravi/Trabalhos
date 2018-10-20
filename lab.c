#include <stdio.h>
#include <string.h>
#define L 4
#define C 4
#define namesize 50


typedef struct{

	char nome[namesize];
	int idade;
	char curso;

}Estudante;


typedef struct{

	Estudante estud;
	char status;

}Apartamento;


//prototipos das funçoes
int main(int argc, char const *argv[]);
void menu (Apartamento M[L][C]);
void inicializar(Apartamento M[L][C]);
void consultar(Apartamento M[L][C]);
void adicionar(Apartamento M[L][C]);
void edificio(Apartamento M[L][C]);


int main(int argc, char const *argv[])
{
	

	Apartamento M[L][C];
	inicializar(M);
	menu(M);

	return 0;
}


/*
*Nome: menu();
* Função: exibir o menu principal
* Funcionamento: leva o usuario a opçao escolhida ou sai do programa.
*/
void menu (Apartamento M[L][C]){


	int op;

	while(1){

		do{
			printf("\n");
			printf("\n####################\n");
			printf("#  Menu principal  #");
			printf("\n####################\n\n");

			printf("1 - Consultar quarto.\n");
			printf("2 - Adicionar estudante.\n");
			printf("3 - Mostrar edificio.\n");
			printf("0 - Sair\n");
			printf("Opcao: ");
			scanf("%d", &op);
			if (op < 0 || op > 3)
				printf("\n\nErro: opção invalida. Tente novamente.");
		}while(op < 0 || op > 3);

		switch (op){

			case 1: consultar(M);break;
			case 2: adicionar(M);break;
			case 3: edificio(M);break;
			case 0: return;
		}

	}
}


/*
*Nome: inicializar();
* Função: inicializar a matriz
* Funcionamento: modifica a variável 'status' de todos os elementos da matriz do tipo struct.
*/
void inicializar(Apartamento M[L][C]){

	for (int i = 0; i < L; ++i)
		for (int j = 0; j < C; ++j)
			M[i][j].status = 'L';

}


/*
*Nome: consultar();
* Função: saber informaçoes sobre quem está alojado nos apartamentos ou se o mesmo está livre.
* Funcionamento: imprime informaçoes sobre quem esta alojado no apartamento ou imprime se o apartamento 
* esta livre.
*/
void consultar(Apartamento M[L][C]){


	int num,ocupado = 0,cont = 13;

	printf("\n");
	printf("######################\n");
	printf("#  Consultar quarto  #\n");
	printf("######################\n\n");
	while(num < 1 || num > 16){
		printf("Numero do apartamento (1 a 16): ");
		scanf("%d", &num);
		if(num < 1 || num > 16)
			printf("Numero de apartamento incorreto. Tente novamente!\n");
	}

	for (int i = L - 1; i >= 0; --i)
	{
		for (int j = 0; j < C; ++j)
		{
			if (num == cont)
				if (M[i][j].status == 'O'){
					printf("Apartamento ocupado!\n");
					printf("Nome: %s\n",M[i][j].estud.nome);
					printf("Idade: %d\n",M[i][j].estud.idade);
					printf("Curso: '%c'\n",M[i][j].estud.curso);
					return;
				}
			cont++;
		}
		cont-=8;
	}

	printf("Apartamento livre!\n");

	return;
}


/*
*Nome: adicionar();
* Função: faz o cadastro do estudante para alojamento no apartamento escolhido.
* Funcionamento: solicita dados do usuario,imprime todos os apartamentos livres e grava os dados do usuario na opçao
* de apartamento escolhida.
*/
void adicionar(Apartamento M[L][C]){


	int i,j,cont = 0,idade,ape;
	char nome[namesize],curso;

	printf("\n");
	printf("#########################\n");
	printf("#  Adicionar estudante  #\n");
	printf("#########################\n\n");
	for (i = 0; i < L; ++i)
		for (j = 0; j < C; ++j){
			if(M[i][j].status == 'O')
				cont++;
		}
		
	if (cont == 16){
		printf("Nao ha vagas!\n");
		return;
	}else
		printf("Ha vagas!\n");

	cont = 13;

	printf("Nome: ");
	scanf("%s",nome);
	printf("Idade: ");
	scanf("%d",&idade);
	while(1){
		printf("Cursos aceitos:\n'B' Biologia\n'C' Ciencia da Computacao\n'F' Fisica\n'M' Matematica\n'Q' Quimica\n");
		printf("Curso: ");
		scanf("%*c%c",&curso);
		if(curso != 'B' && curso != 'C' && curso != 'F' && curso != 'M' && curso != 'Q')
			printf("\n\nErro: curso nao aceito. Tente novamente!\n");
		else
			break;
	}

	printf("\n########################\n");
	printf("#  Apartamentos vagos  #");
	printf("\n########################\n\n");
	for (i = L - 1; i >= 0; --i){
		printf("Andar %d\n",i+1);
		for (j = 0; j < C; ++j){
			if(M[i][j].status == 'L')
				printf("Apartamento %d\n",cont);
			cont++;
		}
		printf("\n");
		cont-=8;
	}

	cont = 13;

	printf("Entre com o numero do apartamento desejado: ");
	scanf ("%d",&ape);
	for(i = L - 1; i >= 0; i--){
		for (j = 0; j < C; j++){
			if (ape == cont){
				M[i][j].status = 'O';
				strcpy(M[i][j].estud.nome,nome);
				M[i][j].estud.idade = idade;
				M[i][j].estud.curso = curso;
				printf("Adicionado com sucesso!\n");
				return;
			}
			cont++;
		}
		cont-=8;
	}

	return;
}


/*
*Nome: edificio();
* Função: exibir os apartamentos do edificio
* Funcionamento: imprimir todos os numeros dos apartamentos e o curso do estudante, caso o apartamento
* esteja ocupado.
*/
void edificio(Apartamento M[L][C]){

	int cont = 13,i,j;

	printf("\n");
	printf("\n\t   ##############\n");
	printf("\t   #  Edificio  #");
	printf("\n\t   ##############\n\n");
	for (i = L - 1; i >= 0 ; i--){
		printf("-----------------------------------------\n");
		for(j = 0; j < C; j++){
			if  (M[i][j].status == 'O'){
				printf("|%3d -'%c' ",cont,M[i][j].estud.curso);
			}else
				printf("|%5d -  ",cont);
			cont++;
		}
		cont-=8;
		printf("|");
		printf("\n");
	}
	printf("-----------------------------------------\n");	

}

