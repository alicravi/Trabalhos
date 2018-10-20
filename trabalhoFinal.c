#include <stdio.h>
#include <string.h>

#define MAXSERV 10
#define MAXPROF 20
#define MAXCLI 200
#define MAXATEND 50

#define nameSize 100
#define phoneSize 15


typedef struct {
    int dia;
    int mes;
    int ano;
}tdata;

typedef struct {
    int codigo;
    char cpf[12];
    tdata data;
    int serv[MAXSERV];
    int prof[MAXSERV];
}tAtendimento;

typedef struct {
    char nome[nameSize];
    char cpf[12];
    char tel[phoneSize];
    int codProfs[MAXSERV];
    int codAtendimento;
    tdata aniversario;
    tAtendimento ultimoAtendimentoPago;
}tCliente;

typedef struct {
    int cod;
    char nome[nameSize];
    float valor;
}tServico;

typedef struct {
    int cod;
    char nome[nameSize];
}tProfissional;


//prototipos das funçoes

//menus
void menuPrincipal(tCliente vetCli[MAXCLI],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV],tAtendimento vetAtend[MAXATEND], int *pserv, int *pcli, int *pprof, int *plist);
void menuCadastro(tCliente vetCli[MAXCLI],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV], int *pserv, int *pcli, int *pprof);
void menuRelatorio(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF],tCliente vetCli[MAXCLI],int *pprof,int *pcli,int *pserv);
void menuAtend(tAtendimento vetAtend[MAXATEND], tCliente vetCli[MAXCLI], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv, int *pprof, int *plist,int *pcli);

//tarefas
void cadastrarProf(tProfissional vetProf[MAXPROF], int *pprof);
void excluirProf(tProfissional vetProf[MAXPROF], int *pprof);
void alterarProf (tProfissional vetProf[MAXPROF]);
void cadastrarCliente(tCliente vetCli[MAXCLI], int *pcli);
void alterarCliente(tCliente vetCli[MAXCLI],int *pcli);
void cadastrarServicos(tServico vetServ[MAXSERV],int *pserv);
void alterarServico(tServico vetServ[MAXSERV],int *pserv);
void listarServicos(tServico vetServ[MAXSERV],int *pserv);
void listarProfs(tProfissional vetProf[MAXPROF],int *pprof);
void listarClientes(tCliente vetCli[MAXCLI],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF],tAtendimento vetAtend[MAXATEND], int *pcli);
void cadastrarAtend (tAtendimento vetAtend[MAXATEND], tCliente vetCli[MAXCLI], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv,int *plist,int *pcli,int *pprof);
void alterarAtend(tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv,int *plist);
void iniciarServico(tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pprof);
void finalizarServico(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *plist);
void pagarAtend(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tCliente vetCli[MAXCLI],int *plist,int *pcli);
void consultarAtend(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF]);

//auxiliares
void limparCPFs(tCliente vetCli[MAXCLI]);
void inicializarCodigos(tProfissional vetProf[MAXPROF],tAtendimento vetAtend[MAXATEND],tCliente vetCli[MAXCLI]);
int verificarEspacoLivre(tCliente vetCli[MAXCLI],char cpf[12]);
int verificarExisteCPF(tCliente vetCli[MAXCLI],int *pcli, char cpf[12]);
int verificarCodProf (tProfissional vetProf[MAXPROF],int cod);
int verificarAtend(tAtendimento vetAtend [MAXATEND]);
int verifVetorAtendCOD(int cod,tAtendimento vetAtend[MAXATEND]);
int verifVetorAtendCPF(char cpf[12], tAtendimento vetAtend[MAXATEND]);
int menuAlterarAtend(int op, int cod, int atend,tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV],int *pserv,int *plist);
int verificarCodServico(tServico vetServ[MAXSERV],int cod);
void servicosReqNaoFinalizado(int atend,tAtendimento vetAtend[MAXATEND],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV]);
void listarAtendIniciado(int atend,tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF], tAtendimento vetAtend[MAXATEND]);
void listarAtendCadastrado(int atend,tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF], tAtendimento vetAtend[MAXATEND]);
void listarServicosPendentes(int atend,tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV]);
void listaConsultarAtend(tServico vetServ[MAXSERV],tProfissional[MAXPROF],int atend,tAtendimento vetAtend[MAXATEND]);
void cancelarPendentes(tAtendimento vetAtend[MAXATEND],int atend,int *plist);




int main(){


    int serv = 0, cli = 0, prof = 0, list = 0;

    tProfissional vetProf[MAXPROF];
    tServico vetServ[MAXSERV];
    tCliente vetCli[MAXCLI];
    tAtendimento vetAtend[MAXATEND];
    inicializarCodigos(vetProf,vetAtend,vetCli);
    limparCPFs(vetCli);
    menuPrincipal(vetCli,vetProf,vetServ,vetAtend,&serv,&cli,&prof,&list);

    return 0;
}



/*
*Nome: menuPrincpal();
* Função: imprimir o menu principal.
* Funcionamento: leva o usuário a outro menu de acordo com sua escolha.
*/
void menuPrincipal(tCliente vetCli[MAXCLI],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV],tAtendimento vetAtend[MAXATEND], int *pserv, int *pcli, int *pprof,int *plist){
    int op;

    do{

        printf("\n\n");
        printf("MENU PRINCIPAL\n");
        printf("1 - CADASTRO\n");
        printf("2 - ATENDIMENTO\n");
        printf("3 - RELATÓRIOS/CONSULTAS\n");
        printf("0 - SAIR\n");
        scanf("%d", &op);
        if (op > 3 || op < 0)
            printf("Opçao inválida.\n");


        switch(op){
            case 1: menuCadastro(vetCli,vetProf,vetServ, pserv, pcli, pprof);break;
            case 2: menuAtend(vetAtend,vetCli,vetServ,vetProf,pserv,pprof,plist,pcli);break;
            case 3: menuRelatorio(vetAtend,vetServ,vetProf,vetCli,pprof,pcli,pserv);break;
            case 0: return;
        }

        op = -1;

    }while(op > 3 || op < 0);


}



/*
*Nome: menuCadastro();
* Função: imprimir o menu com as opções relativas a cadastros e alterações destes.
* Funcionamento: cadastra ou altera o que ja foi cadastrado.
*/
void menuCadastro(tCliente vetCli[MAXCLI],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV], int *pserv, int *pcli, int *pprof){


    int op;

    do{

        printf("\n\nMENU CADASTRO:\n");
        printf("1 - CADASTRAR CLIENTE\n");
        printf("2 - ALTERAR CLIENTE\n");
        printf("3 - CADASTRAR SERVIÇO\n");
        printf("4 - ALTERAR SERVIÇO\n");
        printf("5 - CADASTRAR PROFISSIONAL\n");
        printf("6 - ALTERAR PROFISSIONAL\n");
        printf("7 - EXCLUIR PROFISSIONAL\n");
        printf("0 - SAIR\n");
        scanf("%d", &op);
        if (op > 7 || op < 0)
            printf("Opçao inválida.\n");




        switch(op){
            case 1: cadastrarCliente(vetCli, pcli);break;
            case 2: alterarCliente(vetCli,pcli);break;
            case 3: cadastrarServicos(vetServ,pserv);break;
            case 4: alterarServico(vetServ,pserv);break;
            case 5: cadastrarProf(vetProf, pprof);break;
            case 6: alterarProf(vetProf);break;
            case 7: excluirProf(vetProf, pprof);break;
            case 0: return;
        }

        op = -1;

    }while (op > 7 || op < 0);

    return;

}



/*
*Nome: menuRelatorio();
* Função: imprimir menu com opções para exibir informações já cadastradas.
* Funcionamento: lista informações cadastradas anteriormente.
*/
void menuRelatorio(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF],tCliente vetCli[MAXCLI],int *pprof,int *pcli,int *pserv){

    int op;

        do{

            printf("\n\nMENU RELATÓRIO/CONSULTAS:\n");
            printf("1 - LISTAR SERVIÇOS\n");
            printf("2 - LISTAR PROFISSIONAIS\n");
            printf("3 - LISTAR CLIENTES\n");
            printf("0 - SAIR\n");
            scanf("%d", &op);
            if (op > 3 || op < 0)
                printf("Opçao inválida.\n");


            switch(op){
                case 1:listarServicos(vetServ,pserv); break;
                case 3:listarClientes(vetCli,vetServ,vetProf,vetAtend, pcli); break;
                case 2:listarProfs(vetProf, pprof); break;
                case 0:return;
            }

            op = -1;

        }while(op > 3 || op < 0);

        return;

}




/*
*Nome: menuAtend();
* Função: imprimir menu com opções relativas a atendimento.
* Funcionamento: cadastra, altera, inicializa, finaliza, paga e consulta atendimento.
*/
void menuAtend(tAtendimento vetAtend[MAXATEND], tCliente vetCli[MAXCLI], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv,int *pprof,int *plist,int *pcli){


    int op;

    do{

        printf("1 - CADASTRAR ATENDIMENTO\n");
        printf("2 - ALTERAR ATENDIMENTO\n");
        printf("3 - INICIAR SERVIÇO\n");
        printf("4 - FINALIZAR SERVIÇO\n");
        printf("5 - PAGAR ATENDIMENTO\n");
        printf("6 - CONSULTAR ATENDIMENTO\n");
        printf("0 - SAIR\n");
        scanf("%d", &op);
        if (op > 6 || op < 0)
            printf("Opçao inválida.\n");



        switch(op){
            case 0: return;
            case 1: cadastrarAtend(vetAtend,vetCli,vetServ,vetProf,pserv,plist,pcli,pprof);break;
            case 2: alterarAtend(vetAtend,vetServ,vetProf,pserv,plist);break;
            case 3: iniciarServico(vetAtend,vetServ,vetProf,pprof);break;
            case 4: finalizarServico(vetAtend,vetServ,vetProf,plist);break;
            case 5: pagarAtend(vetAtend,vetServ,vetCli,plist,pcli);break;
            case 6: consultarAtend(vetAtend,vetServ,vetProf);break;
        }

        op = -1;

    }while (op > 6 || op < 0);

    return;

}




/*
*Nome: menuAtend();
* Função: Cadastra o atendimento.
* Funcionamento:
* 1º - Antes de proceder verifica se o CPF do cliente já esta cadastrado.
* 2º - Antes de proceder verifica se o atendimento para o cliente cadastrado já foi marcado.
* 3º - Antes de proceder verifica se o vetor de atendimento ja esta preenchido.
* 4º - É cadastrado uma data para atendimento e a opção de preferencia por profissional.
* 5º - É listada as informaçoes previamente cadastradas.
*/
void cadastrarAtend (tAtendimento vetAtend[MAXATEND], tCliente vetCli[MAXCLI], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv,int *plist,int *pcli,int *pprof){


    int atend,i,op,cod,cliente;
    char cpf[12],op2;


    if (*pserv == 0){
        printf("Não há serviços cadastrados para atendimento\n");
        return;
    }

    printf("Qual o CPF do cliente? ");
    scanf("%s", cpf);
    cliente = verificarExisteCPF(vetCli,pcli,cpf);

    if (cliente == -1){
        printf("Erro: CPF não cadastrado.\n");
        return;
    }


    if (vetCli[cliente].codAtendimento != -1){
        printf("Erro: atendimento para o cliente já cadastrado.\n");
        return;
    }

    atend = verificarAtend(vetAtend);

    if (atend == -1){
        printf("Erro: atendimentos lotados.\n");
        return;
    }

    for (i = 0; i < 11; i++) //cadastrar cpf no vetor vetAtend.cpf
        vetAtend[atend].cpf[i] = cpf[i];


    vetCli[cliente].codAtendimento = atend+1;

    printf("Qual a data? \n");
    printf("Dia: ");
    scanf("%d", &vetAtend[atend].data.dia);
    printf("Mês: ");
    scanf("%d", &vetAtend[atend].data.mes);


    for (i = 0; i < MAXSERV; i++){
        vetAtend[atend].serv[i] = 0;
        vetAtend[atend].prof[i] = 0;
    }

    do{

        for (i = 0; i < *pserv; i++) //lista serviços
            printf("%d - Serviço <%s>\n", i+1, vetServ[i].nome);
        printf("0 - Sair\n");
        scanf("%d", &op);
        if (op > *pserv || op < 0)
            printf("Opçao inválida.Tente novamente.\n");
        else if (op >= 1 && op <= *pserv){
            vetAtend[atend].serv[op-1] = 1;
            *plist = *plist + 1;

            do{

                printf("Possui preferencia por profissional? [s-sim, n- nao]");
                scanf(" %c", &op2);

                if (op2 != 'n' && op2 != 'N' && op2 != 's' && op2 != 'S')
                    printf("Inválido. Tente novamente.\n");

            }while(op2 != 'n' && op2 != 'N' && op2 != 's' && op2 != 'S');

            if ((op2 == 's' || op2 == 'S') && *pprof == 0){
                printf("Não há profissionais cadastrados para atendimento!\n");
                break;
            }


            if (op2 == 's' || op2 == 'S'){
                do{

                    printf("Digite o codigo: ");
                    scanf("%d", &cod);
                    if (verificarCodProf(vetProf,cod) == 0)
                        printf("Código não existe. Tente novamente.\n");

                }while(verificarCodProf(vetProf,cod) == 0);

                vetAtend[atend].prof[op-1] = cod;
            }else
                break;

        }

    }while(op != 0 || op >= *pserv);

    listarAtendCadastrado(atend,vetServ,vetProf,vetAtend);


    return;

}




/*
*Nome: alterarAtend();
* Função: Altera o atendimento já cadastrado.
* Funcionamento:
* 1º - Antes de proceder verifica se o CPF do cliente ou codigo de atendimento tem atendimento marcado/se o codigo existe.
* 2º - Lista os serviços cadastrados para atendimento com a escolha, ou nao, do profissional.
* 3º - Imprime um menu com opções para excluir, inserir ou excluir profissional escolhido para atendimento.
* 4º - Verifica se o codigo do serviço existe antes de proceder com a opção escolhida do menu.
*/
void alterarAtend(tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pserv, int *plist){

    int op,cod,atend,menu;
    char cpf[12],op2;

    do{

        do{

            printf("Deseja localizar o atendimento pelo seu codigo(1) ou pelo CPF do cliente(2)? ");
            scanf("%d", &op);
            if (op != 1 && op != 2)
                printf("Opçao inválida. Tente novamente.\n");

        }while(op != 1 && op != 2);

        if (op == 1){
            printf("Entre com o código: ");
            scanf("%d", &cod);
            atend = verifVetorAtendCOD(cod,vetAtend);
        }

        if (op == 2){
            printf("Entre com o CPF: ");
            scanf(" %s", cpf);
            atend = verifVetorAtendCPF(cpf,vetAtend);
        }

        if (atend == -1){
            do{

                printf("Erro: atendimento não encontrado! Deseja procurar novamente? [s-sim,n-nao]");
                scanf(" %c", &op2);
                if (op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N')
                    printf("Inválido. Tente novamente.\n");

            }while(op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N');

            if (op2 == 'n' || op2 == 'N')
                return;

            printf("\n\n");
        }else
            break;

    }while(op2 == 's' || op2 == 'S');

    listarAtendCadastrado(atend,vetServ,vetProf,vetAtend);


    do{

        do{

            printf("1 - Excluir serviço.\n");
            printf("2 - Inserir serviço.\n");
            printf("3 - Excluir preferência por profissional.\n");
            printf("0 - Voltar ao menu cadastro.\n");
            scanf("%d", &op);
            if (op > 3 || op < 0)
                printf("Opção inválida. Tente novamente.\n");

        }while(op > 3 ||  op < 0);

        if (op == 0)
            return;

        printf("Qual o codigo de serviço? ");
        scanf("%d", &cod);

        menu = menuAlterarAtend(op,cod,atend,vetAtend,vetServ,pserv,plist);

        if (menu == 0)
            printf("Código de serviço não é válido.\n\n");

    }while(menu == 0);

    return;

}




/*
*Nome: iniciarServico();
* Função: Inicializa os serviços previamente marcados para atendimento.
* Funcionamento:
* 1º - Antes de proceder verifica se o CPF do cliente ou codigo de atendimento tem atendimento marcado/se o codigo existe.
* 2º - Lista os serviços cadastrados para atendimento com a escolha, ou nao, do profissional.
* 3º - Antes de proceder verifica se o codigo do serviço fornecido pelo usuário existe e se serviço foi cadastrado
* para atendimento.
* 4º - Antes de proceder verifica se o codigo do profissional fornecido pelo usuário existe e se ja tem outro
* profissional marcado para o serviço.
*/
void iniciarServico(tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *pprof){


    int op,cod,cod_p,cod_s,atend,serv;
    char cpf[12],op2;



    if (*pprof == 0){
        printf("Nao há profissionais cadastrados para atendimento!\n\n");
        return;
    }

    do{


        do{

            printf("Deseja localizar o atendimento pelo seu codigo(1) ou pelo CPF do cliente(2)? ");
            scanf("%d", &op);
            if (op != 1 && op != 2)
                printf("Opçao inválida. Tente novamente.\n");

        }while(op != 1 && op != 2);

        if (op == 1){
            printf("Entre com o código: ");
            scanf("%d", &cod);
            atend = verifVetorAtendCOD(cod,vetAtend);
        }

        if (op == 2){
            printf("Entre com o CPF: ");
            scanf(" %s", cpf);
            atend = verifVetorAtendCPF(cpf,vetAtend);
        }

        if (atend == -1){
            do{

                printf("Erro: atendimento não encontrado! Deseja procurar novamente? [s-sim,n-nao]");
                scanf(" %c", &op2);

                if (op2 == 'n' || op2 == 'N')
                    return;

                if (op2 == 's' || op2 == 'S')
                    break;

                if (op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N')
                    printf("Inválido. Tente novamente.\n");

            }while(op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N');



            printf("\n\n");
        }else
            break;

    }while(op2 == 's' || op2 == 'S');

    listarAtendCadastrado(atend,vetServ,vetProf,vetAtend);


    printf("Qual o codigo do serviço que será iniciado? ");
    scanf("%d", &cod_s);

    serv = verificarCodServico(vetServ,cod_s);


    if (serv == -1){
        printf("Erro: Serviço não existe.\n\n");
        return;
    }


    if (vetAtend[atend].serv[serv] != 1){
        printf("Erro: Serviço não solicitado!\n");
        return;
    }



    do{

        printf("Qual o codigo do profissional? ");
        scanf("%d", &cod_p);


        if (verificarCodProf (vetProf,cod_p) == 0)
            printf("Codigo incorreto. Tente novamente.\n\n");

    }while(verificarCodProf(vetProf,cod_p) == 0);

    if (vetAtend[atend].prof[serv] == 0){
        vetAtend[atend].serv[serv] = 2;
        vetAtend[atend].prof[serv] = cod_p;
    }else{
        if (vetAtend[atend].prof[serv] != cod_p){
            printf("Erro: Há preferência pelo profissional de codigo %d\n", vetAtend[atend].prof[serv]);
            return;
        }else
            vetAtend[atend].serv[serv] = 2;

    }

    return;

}





/*
*Nome: finalizarServico();
* Função: Finaliza o serviço que foi previamente inicializado.
* Funcionamento:
* 1º - Antes de proceder verifica se o CPF do cliente ou codigo de atendimento tem atendimento marcado/se o codigo existe.
* 2º - Lista os serviços inicializados com a escolha do profissional.
* 3º - Antes de proceder verifica se o codigo do serviço fornecido pelo usuário existe e se serviço foi inicializado
* ou cadastrado para atendimento.
* 4º - Lista os serviços inicializados que ainda não foram finalizados.
*/
void finalizarServico(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV], tProfissional vetProf[MAXPROF],int *plist){


    int op,cod,atend,serv;
    char cpf[12],op2;

    if (*plist == 0){
        printf("Nenhum serviço foi inicializado.\n");
        return;
    }


    do{

        do{

            printf("Deseja localizar o atendimento pelo seu codigo(1) ou pelo CPF do cliente(2)? ");
            scanf("%d", &op);
            if (op != 1 && op != 2)
                printf("Opçao inválida. Tente novamente.\n");

        }while(op != 1 && op != 2);

        if (op == 1){
            printf("Entre com o código: ");
            scanf("%d", &cod);
            atend = verifVetorAtendCOD(cod,vetAtend);
        }

        if (op == 2){
            printf("Entre com o CPF: ");
            scanf(" %s", cpf);
            atend = verifVetorAtendCPF(cpf,vetAtend);
        }

        if (atend == -1){
            do{

                printf("Erro: atendimento não encontrado! Deseja procurar novamente? [s-sim,n-nao]");
                scanf(" %c", &op2);

                if (op2 == 'n' || op2 == 'N')
                    return;
                if (op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N')
                    printf("Inválido. Tente novamente.\n");

            }while(op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N');



            printf("\n\n");
        }else
            break;


    }while(op2 == 's' || op2 == 'S');

    listarAtendIniciado(atend,vetServ,vetProf,vetAtend);

    printf("Qual o código do serviço que será finalizado? ");
    scanf("%d",&cod);

    serv = verificarCodServico(vetServ,cod);

    if (serv == -1){
        printf("Erro: serviço não existe!\n");
        return;
    }

    if (vetAtend[atend].serv[serv] != 2){
        printf("Erro: serviço ainda não foi iniciado ou solicitado!\n");
        return;
    }

    vetAtend[atend].serv[serv] = 3;

    servicosReqNaoFinalizado(atend,vetAtend,vetProf,vetServ);

    printf("\n\n");

    return;

}





/*
*Nome: finalizarServico();
* Função: Finaliza o serviço que foi previamente inicializado.
* Funcionamento:
* 1º - Antes de proceder verifica se o CPF do cliente ou codigo de atendimento tem atendimento marcado/se o codigo existe.
* 2º - Lista os serviços inicializados com a escolha do profissional.
* 3º - Antes de proceder verifica se o codigo do serviço fornecido pelo usuário existe e se serviço foi inicializado
* ou cadastrado para atendimento.
* 4º - Lista os serviços inicializados que ainda não foram finalizados.
*/
void pagarAtend(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tCliente vetCli[MAXCLI],int *plist,int *pcli){

    char cpf[12],op;
    int i,j,atend,cliente,cont = 0;
    float total = 0;

    do{

        printf("Qual o CPF do cliente? ");
        scanf(" %s", cpf);
        atend = verifVetorAtendCPF(cpf,vetAtend);

        if (atend == -1){
            do{

                printf("Erro: Atendimento não encontrado! Deseja procurar novamente? [s-sim,n-nao] ");
                scanf(" %c", &op);
                if (op != 's' && op != 'S' && op != 'n' && op != 'N')
                    printf("Inválido. Tente novamente.\n\n");

            }while(op != 's' && op != 'S' && op != 'n' && op != 'N');
        }else
            break;

        if (op == 'n' || op == 'N')
            return;


    }while(op == 's' || op == 'S');


    cliente = verificarExisteCPF(vetCli,pcli,cpf);


    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 1 || vetAtend[atend].serv[i] == 2){
            listarServicosPendentes(atend,vetAtend,vetServ);
            printf("\n\n");

            do{

                printf("Deseja cancelar os serviços pendentes? [s-sim,n-nao] ");
                scanf(" %c", &op);
                if (op != 's' && op != 'S' && op != 'n' && op != 'N')
                    printf("Invalido. Tente novamente.\n");

            }while(op != 's' && op != 'S' && op != 'n' && op != 'N');

            if (op == 'n' || op == 'N'){
                printf("Pagamento cancelado!\n");
                return;
            }

            if (op == 's' || op == 'S'){
                cancelarPendentes(vetAtend,atend,plist);
                break;
            }
        }

    }

    printf("\n");

    for (i = 0; i < *plist; i++){
        if (vetAtend[atend].serv[i] == 3){
            printf("Serviço <%s>. Valor: R$ %.2f\n", vetServ[i].nome,vetServ[i].valor);
            total = total + vetServ[i].valor;
        }
    }

    printf("\nTotal a pagar: %.2f\n\n", total);

    do{

        printf("Atendimento pago? [s-sim,n-nao] ");
        scanf(" %c", &op);
        if (op != 's' && op != 'S' && op != 'N' && op != 'n')
            printf("Inválido. Tente novamente.\n");

    }while(op != 's' && op != 'S' && op != 'N' && op != 'n');

    if (op == 'n' || op == 'N'){
        printf("Pagamento cancelado!\n");
        return;
    }else{
        for (i = 0; i < MAXSERV; i++)
            vetCli[cliente].codProfs[i] = 0;
        vetCli[cliente].codAtendimento = -1;
        vetAtend[atend].codigo = -1;
    }

    return;

}


void consultarAtend(tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF]){

    int op,cod,atend;
    char cpf[12],op2;


    do{


        do{

            printf("Deseja localizar o atendimento pelo seu codigo(1) ou pelo CPF do cliente(2)? ");
            scanf("%d", &op);
            if (op != 1 && op != 2)
                printf("Opçao inválida. Tente novamente.\n");

        }while(op != 1 && op != 2);

        if (op == 1){
            printf("Entre com o código: ");
            scanf("%d", &cod);
            atend = verifVetorAtendCOD(cod,vetAtend);
        }

        if (op == 2){
            printf("Entre com o CPF: ");
            scanf(" %s", cpf);
            atend = verifVetorAtendCPF(cpf,vetAtend);
        }

        if (atend == -1){

            do{

                printf("Erro: atendimento não encontrado! Deseja procurar novamente? [s-sim,n-nao]");
                scanf(" %c", &op2);

                if (op2 == 'n' || op2 == 'N')
                    return;

                if (op2 == 's' || op2 == 'S')
                    break;

                if (op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N')
                    printf("Inválido. Tente novamente.\n");

            }while(op2 != 's' && op2 != 'S' && op2 != 'n' && op2 != 'N');



            printf("\n\n");
        }else
            break;

    }while(op2 == 's' || op2 == 'S');

    if (vetAtend[atend].codigo == -1){
        printf("O cliente não está em atendimento!\n");
        return;
    }

    printf("\n\n");
    printf("Data do atendimento: %d/%d\n", vetAtend[atend].data.dia,vetAtend[atend].data.mes);
    printf("Código do atendimento: %d\n\n", vetAtend[atend].codigo);
    listaConsultarAtend(vetServ,vetProf,atend,vetAtend);

    return;

}


void cadastrarServicos(tServico vetServ[MAXSERV],int *pserv){

    int i;

    *pserv = *pserv + 1;
    if (*pserv > MAXSERV){
        printf("Todos os serviços já foram cadastrados.\n");
        *pserv = *pserv - 1;
        return;
    }

    vetServ[*pserv-1].cod = *pserv;
    printf("Qual o nome do serviço? ");
    scanf(" %s", vetServ[*pserv-1].nome);
    printf("Qual o valor do serviço? ");
    scanf("%f", &vetServ[*pserv-1].valor);
    printf("\n");

    return;
}




void alterarServico(tServico vetServ[MAXSERV],int *pserv){

    int i,cod,op, teste = 0;

    do{
        printf("Qual o código do serviço? ");
        scanf("%d", &cod);
        for (i = 0; i < *pserv; i++){
            if (vetServ[i].cod == cod){
                do{
                    teste = 1;
                    printf("Nome do serviço:  %s\n", vetServ[i].nome);
                    printf("Valor do serviço: %.2f\n", vetServ[i].valor);
                    printf("1 - ALTERAR NOME\n");
                    printf("2 - ALTERAR VALOR\n");
                    printf("0 - VOLTAR AO MENU PRINCIPAL\n");
                    printf("Escolha a opção: ");
                    scanf("%d", &op);

                    if (op == 0)
                        return;

                    if (op == 1){
                        printf("Qual o novo nome? ");
                        scanf(" %s", vetServ[i].nome);
                        return;
                    }

                    if (op == 2){
                        printf("Qual o novo valor: ");
                        scanf("%f", &vetServ[i].valor);
                        return;
                    }

                    if (op > 2 || op < 0)
                        printf("\nOpção errada. Tente novamente.\n");
                }while(op > 2 || op < 0);
            }
        }
        if (teste == 0){
            printf("Erro: código de serviço não existe.\n");
            printf("SERVIÇOS CADASTRADOS\n");
            for (i = 0; i < *pserv; i++){
                printf(" %s\n", vetServ[i].nome);
                printf("%.2f\n", vetServ[i].valor);
            }
            printf("\nDigite o código do serviço ou -1 para voltar ao Menu Cadastro\n\n");
        }
    }while(cod != -1);

}



void cadastrarProf(tProfissional vetProf[MAXPROF], int *pprof){

    int i,j,codigo;


    for (i = 0; i < MAXPROF; i++){

        do{

            printf("Entre com o código: ");
            scanf("%d", &codigo);

            for (j = 0; j < MAXPROF; j++){
                if (vetProf[j].cod == codigo)
                    codigo = -1;
            }

            if (codigo == -1)
                printf("Codigo ja existe ou igual a 0. Tente novamente.\n");


        }while(codigo == 0 || codigo == -1);

        for (i = 0; i < MAXPROF; i++){
            if (vetProf[i].cod == 0){
                *pprof = *pprof + 1;
                vetProf[i].cod = codigo;
                printf("Entre com o nome: ");
                scanf(" %s", vetProf[i].nome);
                printf("\n");
                return;
            }
        }

    }

}



void excluirProf(tProfissional vetProf[MAXPROF], int *pprof){

    int i,cod,op,del;
    char teste = 'n';

    do{
        printf("EXCLUIR PROFISSIONAL\n");
        printf("Qual o código? ");
        scanf("%d", &cod);
        for (i = 0; i < MAXPROF; i++){
            if (vetProf[i].cod == cod)
                teste = 's';
        }
        if (teste == 'n'){
            printf("Erro: Código nao existe.\n");
            printf("Digite o código do profissional ou -1 para voltar ao Menu Cadastro.\n\n");
        }else{

            do{
                printf("Tem certeza que deseja deletar as informações do profissional? [1- sim, 0 - não] ");
                scanf("%d", &op);
                if (op != 1 && op != 0)
                    printf("Inválido. Entre com 1 ou 0.\n");
            }while(op != 1 && op != 0);

            if (op == 1)
                *pprof = *pprof - 1;
                for (i = 0; i < MAXPROF; i++){
                    if (cod == vetProf[i].cod)
                        del = i;
                }
                for (i = del;  i < MAXPROF; i++)
                    vetProf[i] = vetProf[i+1];

        }
    }while(teste == 'n' && cod != -1);

    return;
}



void alterarProf (tProfissional vetProf[MAXPROF]){

    int i,cod,j;
    char teste = 'n';

    do{
        printf("ALTERAR PROFISSIONAL\n");
        printf("Qual o código? ");
        scanf("%d", &cod);
        if (cod == -1)
            break;
        for (i = 0; i < MAXPROF; i++){
            if (cod == vetProf[i].cod){
                teste = 's';
                j = i;
            }

        }
        if (teste == 'n'){
            printf("Erro. Codigo não existe.\n");
            printf("Digite o codigo do profissional ou -1 para voltar ao Menu Cadastro.\n\n");
        }else{
            printf("Nome atual: %s\n", vetProf[j].nome);
            printf("Qual o novo nome? ");
            scanf(" %s", vetProf[j].nome);
            break;
        }
    }while(teste == 'n' && cod != -1);

    return;

}




void cadastrarCliente(tCliente vetCli[MAXCLI], int *pcli){

    int i,cliente,confCPF;
    char cpf[12];

    printf("Qual o CPF? ");
    scanf(" %s", cpf);
    confCPF = verificarExisteCPF(vetCli,pcli,cpf);

    if (confCPF != -1){
        printf("Erro: CPF já cadastrado.\n");
        return ;
    }

    cliente = verificarEspacoLivre(vetCli,cpf);

    if (cliente == -1){
        printf("Máximo de cliente cadastrados.\n");
        return;
    }

    for (i = 0; i < 11; i++)
        vetCli[cliente].cpf[i] = cpf[i];


    *pcli = *pcli + 1;
    printf("Qual o nome? ");
    scanf(" %s", vetCli[cliente].nome);
    printf("Qual o telefone? ");
    scanf(" %s", vetCli[cliente].tel);
    printf("Qual a data de aniversário? \n");
    printf("Dia: ");
    scanf("%d", &vetCli[cliente].aniversario.dia);
    printf("Mês: ");
    scanf("%d", &vetCli[cliente].aniversario.mes);
    vetCli[cliente].aniversario.ano = -1;
    vetCli[cliente].ultimoAtendimentoPago.codigo = 0;
    for (i = 0; i < MAXSERV; i++)
        vetCli[cliente].codProfs[i] = 0;
    return;

}



void alterarCliente(tCliente vetCli[MAXCLI],int *pcli){

    char cpf[12], tel[phoneSize];
    int op,cliente,i;



    printf("Qual o CPF do cliente? ");
    scanf(" %s", cpf);


    cliente = verificarExisteCPF(vetCli,pcli,cpf);
    if (cliente == -1){
        printf("Erro: CPF não cadastrado.\n");
        return;
    }



    do{

        printf("\nALTERAR CLIENTE\n");
        printf("1 - Alterar CPF\n");
        printf("2 - Alterar nome\n");
        printf("3 - Alterar telefone\n");
        printf("4 - Alterar data de aniversário\n");
        printf("0 - Voltar ao menu cadastro.\n");
        scanf("%d", &op);
        if (op > 4 || op < 0)
            printf("Opçao inválida.\n\n");


        switch(op){
            case 1:
                printf("Qual o novo CPF? ");
                scanf(" %s", cpf);
                if (verificarExisteCPF(vetCli,pcli,cpf) != -1){
                    printf("Erro: CPF já cadastrado.\n");
                    return;
                }
                for (i = 0; i < 11; i++)
                    vetCli[cliente].cpf[i] = cpf[i];
                break;
            case 2:
                printf("Qual o novo nome? ");
                scanf(" %s", vetCli[cliente].nome);break;
            case 3:
                printf("Qual o novo telefone? ");
                scanf(" %s", vetCli[cliente].tel);break;
            case 4:
                printf("Qual a nova data? \n");
                printf("Dia: ");
                scanf("%d", &vetCli[cliente].aniversario.dia);
                printf("Mês: ");
                scanf("%d", &vetCli[cliente].aniversario.mes);
                vetCli[cliente].aniversario.ano = -1;break;
            case 0: return;

        }

    }while(op > 4);

    return;

}



void listarServicos(tServico vetServ[MAXSERV],int *pserv){

    int i;

    printf("\nSERVIÇOS CADASTRADOS\n");
    for (i = 0; i < *pserv; i++){
        printf("Código: %d\n", vetServ[i].cod);
        printf("Nome: %s\n", vetServ[i].nome);
        printf("Valor: %.2f\n", vetServ[i].valor);
        printf("\n");
    }

    return;
}



void listarProfs(tProfissional vetProf[MAXPROF],int *pprof){

        int i;

        printf("%d\n", *pprof);
        printf("\nPROFISSIONAIS CADASTRADOS\n");
        for (i = 0; i < *pprof; i++){
            printf("Código: %d\n", vetProf[i].cod);
            printf("Nome: %s\n", vetProf[i].nome);
            printf("\n");
        }

        return;

}



void listarClientes(tCliente vetCli[MAXCLI],tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF],tAtendimento vetAtend[MAXATEND], int *pcli){


    int i,atend,j;
    char cpf[12];

    printf("\nCLIENTES CADASTRADOS\n");
    for (i = 0; i < *pcli; i++){
        printf("Nome: %s\n", vetCli[i].nome);
        printf("CPF: %s\n", vetCli[i].cpf);
        printf("Telefone: %s\n", vetCli[i].tel);
        printf("Data de aniversario: %d/%d\n\n", vetCli[i].aniversario.dia,vetCli[i].aniversario.mes);

        for (j = 0; j < 11; j++)
            cpf[j] = vetCli[i].cpf[j];

        atend = verifVetorAtendCPF(cpf,vetAtend);

        if (vetAtend[atend].codigo == -1){
            printf("ÚLTIMOS SERVIÇOS:");
            listaConsultarAtend(vetServ,vetProf,atend,vetAtend);
        }else if (vetAtend[atend].codigo > 0){
            printf("O cliente está em atendimento.\n");
            printf("Código do atendimento: %d",vetAtend[atend].codigo);
        }
        printf("\n\n");
    }

    return;

}



void inicializarCodigos(tProfissional vetProf[MAXPROF],tAtendimento vetAtend[MAXATEND],tCliente vetCli[MAXCLI]){

    int i;

    for (i = 0; i < MAXATEND; i++)
        vetAtend[i].codigo = -1;

    for (i = 0; i < MAXCLI; i++)
        vetCli[i].codAtendimento = -1;

    for (i = 0; i < MAXPROF; i++)
        vetProf[i].cod = 0;

}



//zerar os CPFs no vetor para posterior verificaçao na funcao verificarEspaçoLivre
void limparCPFs(tCliente vetCli[MAXCLI]){

    int i,j;

    for (i = 0; i < MAXCLI; i++){
        for (j = 0; j < 11; j++)
            vetCli[i].cpf[j] = 0;
    }
}




//verificar se CPF ja esta cadastrado
int verificarExisteCPF(tCliente vetCli[MAXCLI],int *pcli, char cpf[12]){


    int i,j,cont;

    for (i = 0; i < *pcli; i++){
        if(strcmp(vetCli[i].cpf,cpf) == 0)
            return i;
    }

    return -1;

}




//verificar espaço livre no vetor pra cadastrar cpf
int verificarEspacoLivre(tCliente vetCli[MAXCLI],char cpf[12]){

    int i,j,cont;

    for (i = 0; i < MAXCLI; i++){
        cont = 0;
        for (j = 0; j < 11; j++){
            if (vetCli[i].cpf[j] == 0)
                cont++;
        }
        if (cont == 11)
            return i;
    }

    return -1;
}




//verificar se o atendimento ja esta cadastrado
int verificarAtend(tAtendimento vetAtend [MAXATEND]){

    int i;

    for (i = 0; i < MAXATEND; i++){
        if (vetAtend[i].codigo == -1){
            vetAtend[i].codigo = i+1;
            return i;
        }
    }

    return -1;
}




//verificar se o codigo do profissional existe
int verificarCodProf (tProfissional vetProf[MAXPROF],int cod){

    int i;

    for (i = 0; i < MAXPROF; i++){
        if (vetProf[i].cod == cod)
            return 1;
    }

    return 0;
}




//verificar se o codigo do servico existe
int verificarCodServico(tServico vetServ[MAXSERV],int cod){

    int i;

    for (i = 0; i < MAXSERV; i++){
        if (vetServ[i].cod == cod)
            return i;
    }

    return -1;
}




//listar serviços e profissionais do atendimento CADASTRADO
void listarAtendCadastrado(int atend,tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF], tAtendimento vetAtend[MAXATEND]){

    int i,j;

    printf("\n\n");
    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 1){
            printf("Serviço <%s>\n", vetServ[i].nome);
            if (vetAtend[atend].prof[i] != 0){
                for (j = 0; j < MAXPROF; j++){
                    if (vetProf[j].cod == vetAtend[atend].prof[i])
                        printf("Profissional escolhido: <%s>\n\n", vetProf[j].nome);
                }
            }else
                printf("Sem profissional escolhido\n\n");
        }

    }

}




//listar serviços e profissionais do atendimento que foi INICIALIZADO
void listarAtendIniciado(int atend,tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF], tAtendimento vetAtend[MAXATEND]){

    int i,j;

    printf("\n");
    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 2){
            printf("Serviço <%s>\n", vetServ[i].nome);
            if (vetAtend[atend].prof[i] != 0){
                for (j = 0; j < MAXPROF; j++){
                    if (vetProf[j].cod == vetAtend[atend].prof[i])
                        printf("Profissional escolhido: <%s>\n\n", vetProf[j].nome);
                }
            }else
                printf("Sem profissional escolhido.\n\n");
        }

    }

}




//verificar se o codigo esta cadastrado no vetor Atend e, se estiver, retornar a posiçao neste vetor
int verifVetorAtendCOD(int cod,tAtendimento vetAtend[MAXATEND]){

    int i,cont;


    for (i = 0; i < MAXATEND; i++){
        if (vetAtend[i].codigo == cod)
            return i;
    }

    return -1;
}




//verificar se CPF esta cadastrado no vetor Atend e, se estiver, retornar a posiçao neste vetor
int verifVetorAtendCPF(char cpf[12], tAtendimento vetAtend[MAXATEND]){

    int i,cont;

    for (i = 0; i < MAXATEND; i++){
        if (strcmp(vetAtend[i].cpf,cpf) == 0)
            return i;
    }

    return -1;

}




//tarefas do submenu da funcao alterarAtend
int menuAlterarAtend(int op, int cod, int atend,tAtendimento vetAtend[MAXATEND], tServico vetServ[MAXSERV],int *pserv, int *plist){

    int i;


    if (op == 1){
        if (cod  > 0 && cod <= *pserv){
            vetAtend[atend].serv[cod-1] = 0;
            vetAtend[atend].prof[cod-1] = 0;
            *plist = *plist - 1;
            return 1;
        }

    }

    if (op == 2){
        if (cod  > 0 && cod <= *pserv){
            vetAtend[atend].serv[cod-1] = 1;
            return 1;
        }

    }

    if (op == 3){
        if (cod  > 0 && cod <= *pserv){
            vetAtend[atend].prof[cod-1] = 0;
            return 1;
        }
    }

    return 0;

}





void listarServicosPendentes(int atend,tAtendimento vetAtend[MAXATEND],tServico vetServ[MAXSERV]){

    int i;

    printf("\n\nSERVIÇOS PENDENTES: \n");
    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 1 || vetAtend[atend].serv[i] == 2){
            printf("%d - Serviço <%s>\n", vetServ[i].cod, vetServ[i].nome );
        }
    }

}





//lista os serviços requeridos que não foram finalizados
void servicosReqNaoFinalizado(int atend,tAtendimento vetAtend[MAXATEND],tProfissional vetProf[MAXPROF],tServico vetServ[MAXSERV]){

    int i,j;

    printf("\nSERVIÇOS AINDA NÃO FINALIZADOS:\n");
    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 2){
            printf("Código do serviço: %d\n", vetServ[i].cod);
            printf("Serviço <%s>\n", vetServ[i].nome);
            if (vetAtend[atend].prof[i] != 0){
                printf("Código do profissional: %d\n", vetAtend[atend].prof[i]);
                for (j = 0; j < MAXPROF; j++){
                    if (vetAtend[atend].prof[i] == vetProf[j].cod)
                        printf("Profissional: %s\n\n", vetProf[j].nome);
                }
            }else
                printf("\n\n");
        }
    }
}





//lista os serviços requeridos, iniciados e finalizados
void listaConsultarAtend(tServico vetServ[MAXSERV],tProfissional vetProf[MAXPROF],int atend,tAtendimento vetAtend[MAXATEND]){

    int i,j;

    for (i = 0; i < MAXSERV; i++){
        if (vetAtend[atend].serv[i] == 1 || vetAtend[atend].serv[i] == 2 || vetAtend[atend].serv[i] == 3){
            printf("\nCodigo do serviço: <%d>\n", vetServ[i].cod);
            printf("Serviço <%s>\n",vetServ[i].nome);
            if (vetAtend[atend].prof[i] != 0){
                for (j = 0; j < MAXPROF; j++){
                    if (vetAtend[atend].prof[i] == vetProf[j].cod){
                        printf("Codigo do profissional para atendimento: <%d>\n", vetAtend[atend].prof[i]);
                        printf("Nome do profissional para atendimento: <%s>\n\n", vetProf[j].nome);
                    }
                }
            }else
                printf("Não escolheu profissional.\n\n");
        }
    }

}





//cancela os serviços do atendimento q não foram finalizados
void cancelarPendentes(tAtendimento vetAtend[MAXATEND],int atend,int *plist){

    int i;

    for (i = 0; i < *plist; i++){
        if (vetAtend[atend].serv[i] == 1)
            vetAtend[atend].serv[i] = 0;
    }
    printf("Serviços pendentes cancelados!\n\n");

}

