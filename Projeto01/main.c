#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>


#if defined(__MINGW32__) || defined(_MSC_VER)//Função responsável por indentificar o sistema operacional da máquina
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#else
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#endif

int esc1, esc2, esc3;
//Bloco de Struct
typedef struct endereco{
    char cidade[50];
    char bairro[50];
    char rua[50];
    int numero;
}t_endereco;

typedef struct CASA{
    int id;
    char areaConstruida[10];
    char titulo[50];
    char areaTerreno[10];
    int numeroQuartos;
    int posicaoSituada;
    int pavimentos;
    int situacao;
    float preco;
    char descricao[200];
    t_endereco end;
}t_casa;

typedef struct TERRENO{
    int id;
    float area;
    int situacao;
    float preco;
    char descricao[200];
    t_endereco end;
}t_terreno;

typedef struct{
    int id;
    char medida[10];
    int numeroQuartos;
    int posicaoSituada;
    int andar;
    float preco;
    int vagasGaragem;
    int situacao;
    char descricao[200];
    t_endereco end;
}t_apartamento;

t_apartamento apartamentos[500];
t_casa casas[500];
t_terreno terrenos[500];

//Fim bloco de struct e inicio das funções

int comparar(char texto1[], int tamanho, char texto2[]){//Função responsável por comparar os valores, usado para pesquisas
    int cont;
    for(cont = 0; cont < tamanho; cont++){
        texto1[cont] = toupper(texto1[cont]);
        texto2[cont] = toupper(texto2[cont]);
    }
    if(strstr(texto1, texto2) != NULL){
        return 1;//Retorna 1 se achou
    }else{
        return 0;//0 se nao achou
    }
}

FILE* openConecction(char nomeArquivo[], char tipoEntrada[]){//Função responsável pela maioria das conexões com os arquivos txt, todos eles
    FILE *fl = fopen(nomeArquivo, tipoEntrada);//Abre a conexão com o arquivo txt
    if(fl == NULL){
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
    }
    return fl;
}

void closeConnection(FILE *fl){//Finaliza a conexão com o arquivo
    fclose(fl);
}

int testeArquivo(char nome[]){//Testa se o arquivo existe
    int arquivo = access(nome, F_OK);
    if(arquivo == ENOENT){
        return 0;
    }else{
        return 1;
    }
}

void verificaExistencia(){
    int arq = testeArquivo("apartamentos.txt");
        FILE *fl = openConecction("apartamentos.txt", "a");
        closeConnection(fl);
        fl = openConecction("apCfg.txt", "a");
        closeConnection(fl);
        fl = openConecction("casa.txt", "a");
        closeConnection(fl);
        fl = openConecction("csCfg.txt", "a");
        closeConnection(fl);
        fl = openConecction("terrenos.txt", "a");
        closeConnection(fl);
        fl = openConecction("teCfg.txt", "a");
        closeConnection(fl);
}

int buscarID(char arquivo[]){//Essa função pega o ultimo id dos usuarios, esse id é salvo em um txt separado
    int r = testeArquivo(arquivo);//Chama a função para verificar se o arquivo existe
    int id = 0;
    if(r == 0){
        FILE *ff = fopen(arquivo, "w");
        fclose(ff);
        return -5;
    }else{
        FILE *fl = fopen(arquivo, "r");
        if(fl == NULL){
            fl = fopen(arquivo, "w");
            fclose(fl);
        }
        fscanf(fl, "%i", &id);
        fclose(fl);
        return id;
    }
}
void inserirID(char arquivo[], int id){//Essa função Insere o id como citado acima
    FILE *fl = fopen(arquivo, "w+");
    fprintf(fl, "%i", id+1);
    fclose(fl);
}

int cadastroApartamento(t_apartamento apartamentos){//Cadastro de apartamento
    int cont = 0;
    int id = buscarID("apCfg.txt");//Busca o id
    if(id == -5){
        id = buscarID("apCfg.txt");
    }
    inserirID("apCfg.txt", id);
    FILE *fl = openConecction("apartamentos.txt", "a");//Abre o arquivo de texto para salvar dados
    //fprintf salva os dados no arquivo
    fprintf(fl, "%i\n", id+1);
    fprintf(fl, "%i\n", apartamentos.andar);
    fprintf(fl, "%s", apartamentos.descricao);
    fprintf(fl, "%s", apartamentos.end.rua);
    fprintf(fl, "%s", apartamentos.end.bairro);
    fprintf(fl, "%s", apartamentos.end.cidade);
    fprintf(fl, "%i\n", apartamentos.end.numero);
    fprintf(fl, "%s", apartamentos.medida);
    fprintf(fl, "%i\n", apartamentos.numeroQuartos);
    fprintf(fl, "%i\n", apartamentos.posicaoSituada);
    fprintf(fl, "%f\n", apartamentos.preco);
    fprintf(fl, "%i\n", apartamentos.situacao);
    fprintf(fl, "%i\n", apartamentos.vagasGaragem);

    closeConnection(fl);
}

int cadastroCasa(t_casa casa){//Cadastro de casa
    int cont = 0;
    int id = buscarID("csCfg.txt");
    if(id == -5){
        id = buscarID("csCfg.txt");
    }
    inserirID("csCfg.txt", id);
    FILE *fl = openConecction("casa.txt", "a");

    fprintf(fl, "%i\n", id+1);
    fprintf(fl, "%i\n", casa.pavimentos);
    fprintf(fl, "%s", casa.descricao);
    fprintf(fl, "%s", casa.titulo);
    fprintf(fl, "%s", casa.end.rua);
    fprintf(fl, "%s", casa.end.bairro);
    fprintf(fl, "%s", casa.end.cidade);
    fprintf(fl, "%i\n", casa.end.numero);
    fprintf(fl, "%s", casa.areaConstruida);
    fprintf(fl, "%s", casa.areaTerreno);
    fprintf(fl, "%i\n", casa.numeroQuartos);
    fprintf(fl, "%i\n", casa.posicaoSituada);
    fprintf(fl, "%f\n", casa.preco);
    fprintf(fl, "%i\n", casa.situacao);

    closeConnection(fl);
}

int cadastroTerreno(t_terreno terreno){//Cadastro de terrenos
    int cont = 0;
    int id = buscarID("teCfg.txt");
    if(id == -5){
        id = buscarID("teCfg.txt");
    }
    inserirID("teCfg.txt", id);
    FILE *fl = openConecction("terrenos.txt", "a");

    fprintf(fl, "%i\n", id+1);
    fprintf(fl, "%s", terreno.descricao);
    fprintf(fl, "%s", terreno.end.rua);
    fprintf(fl, "%s", terreno.end.bairro);
    fprintf(fl, "%s", terreno.end.cidade);
    fprintf(fl, "%i", terreno.end.numero);
    fprintf(fl, "%f", terreno.area);
    fprintf(fl, "%f\n", terreno.preco);
    fprintf(fl, "%i\n", terreno.situacao);

    closeConnection(fl);
}

void listagemApartamentos(){//Essa função lista os apartamentos
    int id = buscarID("apCfg.txt");
    FILE *fl = fopen("apartamentos.txt", "r");
    int cont;
    for(cont = 0; cont < id; cont++){
        fscanf(fl, "%i%*c", &apartamentos[cont].id);
        fscanf(fl, "%i%*c", &apartamentos[cont].andar);
        fgets(apartamentos[cont].descricao, 200, fl);
        fgets(apartamentos[cont].end.rua, 50, fl);
        fgets(apartamentos[cont].end.bairro, 50, fl);
        fgets(apartamentos[cont].end.cidade, 50, fl);
        fscanf(fl, "%i%*c", &apartamentos[cont].end.numero);
        fgets(apartamentos[cont].medida, 10, fl);
        fscanf(fl, "%i%*c", &apartamentos[cont].numeroQuartos);
        fscanf(fl, "%i%*c", &apartamentos[cont].posicaoSituada);
        fscanf(fl, "%f%*c", &apartamentos[cont].preco);
        fscanf(fl, "%i%*c", &apartamentos[cont].situacao);
        fscanf(fl, "%i%*c", &apartamentos[cont].vagasGaragem);
    }
    fclose(fl);
}

void listagemCasas(){//Essa função lista as casas
    int id = buscarID("csCfg.txt");
    FILE *fl = openConecction("casa.txt", "r");
    int cont;
    for(cont = 0; cont < id; cont++){
        fscanf(fl, "%i%*c", &casas[cont].id);
        fscanf(fl, "%i%*c", &casas[cont].pavimentos);
        fgets(casas[cont].descricao, 200, fl);
        fgets(casas[cont].titulo, 50, fl);
        fgets(casas[cont].end.rua, 50, fl);
        fgets(casas[cont].end.bairro, 50, fl);
        fgets(casas[cont].end.cidade, 50, fl);
        fscanf(fl, "%i%*c", &casas[cont].end.numero);
        fgets(casas[cont].areaConstruida, 10, fl);
        fgets(casas[cont].areaTerreno, 10, fl);
        fscanf(fl, "%i%*c", &casas[cont].numeroQuartos);
        fscanf(fl, "%i%*c", &casas[cont].posicaoSituada);
        fscanf(fl, "%f%*c", &casas[cont].preco);
        fscanf(fl, "%i%*c", &casas[cont].situacao);

    }
    fclose(fl);
}

void listagemTerrenos(){//Essa função lista os terrenos
    int id = buscarID("teCfg.txt");
    FILE *fl = fopen("terrenos.txt", "r");//Abre o arquivo para leitura
    int cont;
    for(cont = 0; cont < id; cont++){
        fscanf(fl, "%i%*c", &terrenos[cont].id);
        fgets(terrenos[cont].descricao, 200, fl);
        fgets(terrenos[cont].end.rua, 50, fl);
        fgets(terrenos[cont].end.bairro, 50, fl);
        fgets(terrenos[cont].end.cidade, 50, fl);
        fscanf(fl, "%i%*c", &terrenos[cont].end.numero);
        fscanf(fl, "%f%*c", &terrenos[cont].area);
        fscanf(fl, "%f%*c", &terrenos[cont].preco);
        fscanf(fl, "%i%*c", &terrenos[cont].situacao);
    }
    fclose(fl);
}
//Bloco de menssagens que aparecerão nos menus
void menssagemEntrada(){
    printf("Bem vindo ao sistema!\nPorfavor escolha uma das opções no menu digitando seu ID\n\n");
}
void menu(){
    printf("-------O que voce deseja fazer?-------\n1->Voltar\n2->Apartamentos\n3->Casas\n4->Terrenos\n5->Sair\n------------------\n");
}
void subMenu(){
    printf("-----Listar-----\n\n1->Voltar\n2->Listar todos\n3->Listar por Descricao\n4->Disponiveis para alugar -Tipo-\n5->Disporniveis para vender -Tipo-\n6->Disponivel para alugar por bairro\n7->Disponivel para vender por bairro\n8->Descricao dos imoveis por cidade\n9->Sair\n---------------\n");
}

void menuOpcoes(){
    printf("------Menu------\n1->Cadastrar\n2->Listar\n");
    printf("3->Sair\n--------------\n");
}
//Finalizacao do bloco
//Inicio do bloco dos menus, essas funçoes mostram o menu na tela
int menuListarTodos(){
    int escolha = 0;
    printf("--------Listar Todos--------\n\n1->Voltar\n2->Todos\n3->Apartamentos\n4->Casas\n5->Terrenos\n6->Sair\nDigite:");
    scanf("%i", &escolha);
    while(escolha < 1 || escolha > 6){
        printf("Digite o codigo corretamente!\n");
        printf("--------Listar Todos--------\n\n1->Voltar\n2->Todos\n3->Apartamentos\n4->Casas\n5->Terrenos\n6->Sair\nDigite:");
        scanf("%i", &escolha);
    }
    return escolha;
}

int subMenuListar(){
    subMenu();
    int escolha = 0;
    printf("Digite o codigo: ");
    scanf("%i", &escolha);
    while(escolha < 1 || escolha > 9){
        printf("Digite corretamente!\n");
        subMenu();
        scanf("%i", &escolha);
    }
    return escolha;
}

int entrada(){
    int escolha2 = 0;
    menssagemEntrada();
    menuOpcoes();
    printf("Digite o codigo: ");
    scanf("%i", &escolha2);
    while(escolha2 < 1 || escolha2 > 12){
        printf("Digite o codigo correto\n");
        menuOpcoes();
        scanf("%i", &escolha2);
    }
    puts("\n");
    return escolha2;
}
int escolha1(){
    menu();
    int escolha = 0;
    printf("Digite o codigo: ");
    scanf("%i", &escolha);
    while(escolha < 1 || escolha > 5){
        limpar_tela();
        printf("\nDigite o codigo correto\n");
        menu();
        scanf("%i", &escolha);
    }
    return escolha;
}
//Finalizacao do bloco
int cadastrarApartamento(){//Função responsável por receber os dados para cadastrar apartamento
    while(1){
        int escolha = 0;
        t_apartamento apartamento;
        printf("1->Alugar\n2->Vender\n3->Alugar/Vender\nDigite o codigo: ");
        scanf("%i%*c", &apartamento.situacao);
        printf("Andar: ");
        scanf("%i%*c", &apartamento.andar);
        printf("Descricao: ");
        fgets(apartamento.descricao, 200, stdin);
        printf("Cidade: ");
        fgets(apartamento.end.cidade, 50, stdin);
        printf("Bairro: ");
        fgets(apartamento.end.bairro, 50, stdin);
        printf("Rua: ");
        fgets(apartamento.end.rua, 50, stdin);
        printf("Numero: ");
        scanf("%i%*c", &apartamento.end.numero);
        printf("Medida em metros(Ex: 30x30): ");
        fgets(apartamento.medida, 10, stdin);
        printf("Numero de quartos: ");
        scanf("%i%*c", &apartamento.numeroQuartos);
        printf("Posicao do predio\n1->Norte\n2->Sul\n3->Leste\n4->Oeste\nDigite: ");
        scanf("%i%*c", &apartamento.posicaoSituada);
        printf("Preco: ");
        scanf("%f%*c", &apartamento.preco);
        printf("Vagas na garagem: ");
        scanf("%i%*c", &apartamento.vagasGaragem);
        limpar_tela();
        printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
        scanf("%i", &escolha);
        while(escolha < 1 || escolha > 2){
            printf("Digite o codigo correto!\n\n");
            printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
            scanf("%i", &escolha);
        }
        if(escolha == 1){
            limpar_tela();
            cadastroApartamento(apartamento);
            printf("Cadastro realizado com sucesso!\n\nDeseja realizar um novo cadastro?\n1->Sim\nQualquer outro para nao\nDigite: ");
            int escolher = 0;
            scanf("%i", &escolher);
            if(escolher == 1){
                limpar_tela();
                continue;
            }else{
                return 5;
            }
        }else{
            return 0;
        }
    }
}

int cadastrarCasa(){//Função responsável por receber os dados para cadastrar apartamento
    while(1){
        int escolha = 0;
        t_casa casa;
        scanf("%*c");
        printf("Titulo: ");
        fgets(casa.titulo, 50, stdin);
        printf("\n1->Alugar\n2->Vender\n3->Alugar/Vender\nDigite o codigo: ");
        scanf("%i%*c", &casa.situacao);
        printf("\nPavimentos: ");
        scanf("%i%*c", &casa.pavimentos);
        printf("Descricao: ");
        fgets(casa.descricao, 200, stdin);
        printf("Cidade: ");
        fgets(casa.end.cidade, 50, stdin);
        printf("Bairro: ");
        fgets(casa.end.bairro, 50, stdin);
        printf("Rua: ");
        fgets(casa.end.rua, 50, stdin);
        printf("Numero: ");
        scanf("%i%*c", &casa.end.numero);
        printf("Area construida (em metros quadrados): ");
        fgets(casa.areaConstruida, 10, stdin);
        printf("Area do terreno da casa (em metros quadrados): ");
        fgets(casa.areaTerreno, 10, stdin);
        printf("Numero de quartos: ");
        scanf("%i%*c", &casa.numeroQuartos);
        printf("Posicao da casa\n1->Norte\n2->Sul\n3->Leste\n4->Oeste\nDigite: ");
        scanf("%i%*c", &casa.posicaoSituada);
        printf("Preco: ");
        scanf("%f%*c", &casa.preco);
        limpar_tela();
        printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
        scanf("%i", &escolha);
        while(escolha < 1 || escolha > 2){
            printf("Digite o codigo correto!\n\n");
            printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
            scanf("%i", &escolha);
        }
        if(escolha == 1){
            cadastroCasa(casa);
            printf("\nCadastrado com sucesso!!!\n\n");
            printf("Deseja realizar um novo cadastro?\n1->Sim\nQualquer outro numero para nao\nDigite: ");
            int escolher = 0;
            scanf("%i", &escolher);
            if(escolher == 1){
                limpar_tela();
                continue;
            }else{
                limpar_tela();
                return 5;
            }
        }else{
            return 0;
        }
    }
}

int cadastrarTerreno(){//Função responsável por receber os dados para cadastrar apartamento
    while(1){
        int escolha = 0;
        t_terreno terreno;
        printf("\n1->Alugar\n2->Vender\n3->Alugar/Vender\nDigite o codigo: ");
        scanf("%i%*c", &terreno.situacao);
        printf("\nDescricao: ");
        fgets(terreno.descricao, 200, stdin);
        printf("Cidade: ");
        fgets(terreno.end.cidade, 50, stdin);
        printf("Bairro: ");
        fgets(terreno.end.bairro, 50, stdin);
        printf("Rua: ");
        fgets(terreno.end.rua, 50, stdin);
        printf("Numero: ");
        scanf("%i%*c", &terreno.end.numero);
        printf("Area (em metros quadrados): ");
        scanf("%f%*c", &terreno.area);
        printf("Preco: ");
        scanf("%f%*c", &terreno.preco);
        limpar_tela();
        printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
        scanf("%i", &escolha);
        while(escolha < 1 || escolha > 2){
            printf("Digite o codigo correto!\n\n");
            printf("Salvar dados?\n1->Sim\n2->Nao\nDigite: ");
            scanf("%i", &escolha);
        }
        if(escolha == 1){
            cadastroTerreno(terreno);
            printf("\nCadastrado com sucesso!!!\n\n");
            printf("Deseja realizar um novo cadastro?\n1->Sim\nQualquer outro numero para nao\nDigite: ");
            int escolher = 0;
            scanf("%i", &escolher);
            if(escolher == 1){
                limpar_tela();
                continue;
            }else{
                limpar_tela();
                return 5;
            }
        }else{
            return 0;
        }
    }
}

int listarApartamentos(int escolhaListagem){//Funcao para realizar a leitura dos dados
    int id = buscarID("apCfg.txt");
    listagemApartamentos();
    int cont;
    limpar_tela();
    for(cont = 0; cont < id; cont++){
        if(apartamentos[cont].situacao == escolhaListagem || apartamentos[cont].situacao == 3){
            printf("ID: %i\n", apartamentos[cont].id);
            printf("Andar: %i\n", apartamentos[cont].andar);
            printf("Descricao: %s", apartamentos[cont].descricao);
            printf("Rua: %s", apartamentos[cont].end.rua);
            printf("Bairro: %s", apartamentos[cont].end.bairro);
            printf("Cidade: %s", apartamentos[cont].end.cidade);
            printf("Numero: %i\n", apartamentos[cont].end.numero);
            printf("Medida: %s", apartamentos[cont].medida);
            printf("Numero de Quartos: %i\n", apartamentos[cont].numeroQuartos);
            switch(apartamentos[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n", apartamentos[cont].preco);
            printf("Vagas Garagem: %i\n\n---------------------------\n\n", apartamentos[cont].vagasGaragem);
        }
    }
    printf("\nMenu:\n1->Voltar\n2-Sair\nDigite:");
    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int listarCasas(int e){//Funcao para realizar a leitura dos dados
    limpar_tela();
    int id = buscarID("csCfg.txt");
    listagemCasas();
    int cont;
    for(cont = 0; cont < id; cont++){
        if(casas[cont].situacao == e || casas[cont].situacao == 3){
            printf("ID: %i\n", casas[cont].id);
            printf("Titulo: %s", casas[cont].titulo);
            printf("Numero de pavimentos: %i\n", casas[cont].pavimentos);
            printf("Descricao: %s", casas[cont].descricao);
            printf("Rua: %s", casas[cont].end.rua);
            printf("Bairro: %s", casas[cont].end.bairro);
            printf("Cidade: %s", casas[cont].end.cidade);
            printf("Numero: %i\n", casas[cont].end.numero);
            printf("Medida da casa: %s", casas[cont].areaConstruida);
            printf("Medida do terreno: %s", casas[cont].areaTerreno);
            printf("Numero de Quartos: %i\n", casas[cont].numeroQuartos);
            switch(casas[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n\n---------------------------\n\n", casas[cont].preco);
        }
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        limpar_tela();
        printf("Digite corretamente!\n");
        printf("\nMenu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int listarTerrenos(int escolhaListagem){//Funcao para realizar a leitura dos dados
    int id = buscarID("teCfg.txt");
    listagemTerrenos();
    int cont;
    limpar_tela();
    for(cont = 0; cont < id; cont++){
        if(terrenos[cont].situacao == escolhaListagem || terrenos[cont].situacao == 3){
            printf("ID: %i\n", terrenos[cont].id);
            printf("Descricao: %s", terrenos[cont].descricao);
            printf("Rua: %s", terrenos[cont].end.rua);
            printf("Bairro: %s", terrenos[cont].end.bairro);
            printf("Cidade: %s", terrenos[cont].end.cidade);
            printf("Numero: %i\n", terrenos[cont].end.numero);
            printf("Area: %f\n", terrenos[cont].area);
            printf("Preco: %.2f\n\n---------------------------\n\n", terrenos[cont].preco);
    }
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");

    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int listarApartamentosTodos(){//Funcao para realizar a leitura dos dados
    int id = buscarID("apCfg.txt");
    listagemApartamentos();
    int cont;
    limpar_tela();
    printf("----------- Apartamentos -----------\n");

    for(cont = 0; cont < id; cont++){
            printf("ID: %i\n", apartamentos[cont].id);
            printf("Andar: %i\n", apartamentos[cont].andar);
            printf("Descricao: %s", apartamentos[cont].descricao);
            printf("Rua: %s", apartamentos[cont].end.rua);
            printf("Bairro: %s", apartamentos[cont].end.bairro);
            printf("Cidade: %s", apartamentos[cont].end.cidade);
            printf("Numero: %i\n", apartamentos[cont].end.numero);
            printf("Medida: %s", apartamentos[cont].medida);
            printf("Numero de Quartos: %i\n", apartamentos[cont].numeroQuartos);
            switch(apartamentos[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n", apartamentos[cont].preco);
            printf("Vagas Garagem: %i\n\n---------------------------\n\n", apartamentos[cont].vagasGaragem);
    }
    return 0;
}

int listarCasasTodos(){//Funcao para realizar a leitura dos dados
    int id = buscarID("csCfg.txt");
    listagemCasas();
    int cont;
    printf("----------- Casas -----------\n");
    for(cont = 0; cont < id; cont++){
            printf("ID: %i\n", casas[cont].id);
            printf("Titulo: %s", casas[cont].titulo);
            printf("Numero de pavimentos: %i\n", casas[cont].pavimentos);
            printf("Descricao: %s", casas[cont].descricao);
            printf("Rua: %s", casas[cont].end.rua);
            printf("Bairro: %s", casas[cont].end.bairro);
            printf("Cidade: %s", casas[cont].end.cidade);
            printf("Numero: %i\n", casas[cont].end.numero);
            printf("Medida da casa: %s", casas[cont].areaConstruida);
            printf("Medida do terreno: %s", casas[cont].areaTerreno);
            printf("Numero de Quartos: %i\n", casas[cont].numeroQuartos);
            switch(casas[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n\n---------------------------\n\n", casas[cont].preco);
    }
    return 0;
}

int listarTerrenosTodos(){//Funcao para realizar a leitura dos dados
    int id = buscarID("teCfg.txt");
    listagemTerrenos();
    printf("----------- Terrenos -----------\n");
    int cont;
    for(cont = 0; cont < id; cont++){
            printf("ID: %i\n", terrenos[cont].id);
            printf("Descricao: %s", terrenos[cont].descricao);
            printf("Rua: %s", terrenos[cont].end.rua);
            printf("Bairro: %s", terrenos[cont].end.bairro);
            printf("Cidade: %s", terrenos[cont].end.cidade);
            printf("Numero: %i\n", terrenos[cont].end.numero);
            printf("Area: %f\n", terrenos[cont].area);
            printf("Preco: %.2f\n\n---------------------------\n\n", terrenos[cont].preco);
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");

    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int pesquisarPorDescricao(){
    int id = buscarID("apCfg.txt");
    listagemApartamentos();
    int cont;
    limpar_tela();

    printf("--------Pesquisar por descricao--------\n\nDigite:");
    char descricao[200];
    scanf("%*c");
    fgets(descricao, 200, stdin);

    printf("\n----------- Apartamentos -----------\n");

    for(cont = 0; cont < id; cont++){
        if(comparar(apartamentos[cont].descricao, 200, descricao)){
            printf("ID: %i\n", apartamentos[cont].id);
            printf("Andar: %i\n", apartamentos[cont].andar);
            printf("Descricao: %s", apartamentos[cont].descricao);
            printf("Rua: %s", apartamentos[cont].end.rua);
            printf("Bairro: %s", apartamentos[cont].end.bairro);
            printf("Cidade: %s", apartamentos[cont].end.cidade);
            printf("Numero: %i\n", apartamentos[cont].end.numero);
            printf("Medida: %s", apartamentos[cont].medida);
            printf("Numero de Quartos: %i\n", apartamentos[cont].numeroQuartos);
            switch(apartamentos[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n", apartamentos[cont].preco);
            printf("Vagas Garagem: %i\n\n---------------------------\n\n", apartamentos[cont].vagasGaragem);
    }
    }
    id = buscarID("csCfg.txt");
    listagemCasas();
    printf("----------- Casas -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(casas[cont].descricao, 200, descricao)){
            printf("ID: %i\n", casas[cont].id);
            printf("Titulo: %s", casas[cont].titulo);
            printf("Numero de pavimentos: %i\n", casas[cont].pavimentos);
            printf("Descricao: %s", casas[cont].descricao);
            printf("Rua: %s", casas[cont].end.rua);
            printf("Bairro: %s", casas[cont].end.bairro);
            printf("Cidade: %s", casas[cont].end.cidade);
            printf("Numero: %i\n", casas[cont].end.numero);
            printf("Medida da casa: %s", casas[cont].areaConstruida);
            printf("Medida do terreno: %s", casas[cont].areaTerreno);
            printf("Numero de Quartos: %i\n", casas[cont].numeroQuartos);
            switch(casas[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n\n---------------------------\n\n", casas[cont].preco);
    }
    }
    id = buscarID("teCfg.txt");
    listagemTerrenos();
    printf("----------- Terrenos -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(terrenos[cont].descricao, 200, descricao)){
            printf("ID: %i\n", terrenos[cont].id);
            printf("Descricao: %s", terrenos[cont].descricao);
            printf("Rua: %s", terrenos[cont].end.rua);
            printf("Bairro: %s", terrenos[cont].end.bairro);
            printf("Cidade: %s", terrenos[cont].end.cidade);
            printf("Numero: %i\n", terrenos[cont].end.numero);
            printf("Area: %f\n", terrenos[cont].area);
            printf("Preco: %.2f\n\n---------------------------\n\n", terrenos[cont].preco);
    }
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");

    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int pesquisarPorBairro(int i){
    int id = buscarID("apCfg.txt");
    listagemApartamentos();
    int cont;
    limpar_tela();

    printf("--------Pesquisar Disponiveis para Alugar por Bairro--------\n\nDigite:");
    char bairro[50];
    scanf("%*c");
    fgets(bairro, 50, stdin);

    printf("\n----------- Apartamentos -----------\n");

    for(cont = 0; cont < id; cont++){
        if(comparar(apartamentos[cont].end.bairro, 50, bairro)){
            printf("ID: %i\n", apartamentos[cont].id);
            printf("Andar: %i\n", apartamentos[cont].andar);
            printf("Descricao: %s", apartamentos[cont].descricao);
            printf("Rua: %s", apartamentos[cont].end.rua);
            printf("Bairro: %s", apartamentos[cont].end.bairro);
            printf("Cidade: %s", apartamentos[cont].end.cidade);
            printf("Numero: %i\n", apartamentos[cont].end.numero);
            printf("Medida: %s", apartamentos[cont].medida);
            printf("Numero de Quartos: %i\n", apartamentos[cont].numeroQuartos);
            switch(apartamentos[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n", apartamentos[cont].preco);
            printf("Vagas Garagem: %i\n\n---------------------------\n\n", apartamentos[cont].vagasGaragem);
    }
    }
    id = buscarID("csCfg.txt");
    listagemCasas();
    printf("----------- Casas -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(casas[cont].end.bairro, 50, bairro)){
            printf("ID: %i\n", casas[cont].id);
            printf("Titulo: %s", casas[cont].titulo);
            printf("Numero de pavimentos: %i\n", casas[cont].pavimentos);
            printf("Descricao: %s", casas[cont].descricao);
            printf("Rua: %s", casas[cont].end.rua);
            printf("Bairro: %s", casas[cont].end.bairro);
            printf("Cidade: %s", casas[cont].end.cidade);
            printf("Numero: %i\n", casas[cont].end.numero);
            printf("Medida da casa: %s", casas[cont].areaConstruida);
            printf("Medida do terreno: %s", casas[cont].areaTerreno);
            printf("Numero de Quartos: %i\n", casas[cont].numeroQuartos);
            switch(casas[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n\n---------------------------\n\n", casas[cont].preco);
    }
    }
    id = buscarID("teCfg.txt");
    listagemTerrenos();
    printf("----------- Terrenos -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(terrenos[cont].end.bairro, 50, bairro)){
            printf("ID: %i\n", terrenos[cont].id);
            printf("Descricao: %s", terrenos[cont].descricao);
            printf("Rua: %s", terrenos[cont].end.rua);
            printf("Bairro: %s", terrenos[cont].end.bairro);
            printf("Cidade: %s", terrenos[cont].end.cidade);
            printf("Numero: %i\n", terrenos[cont].end.numero);
            printf("Area: %f\n", terrenos[cont].area);
            printf("Preco: %.2f\n\n---------------------------\n\n", terrenos[cont].preco);
    }
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");

    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int pesquisarPorCidade(){
    int id = buscarID("apCfg.txt");
    listagemApartamentos();
    int cont;
    limpar_tela();

    printf("--------Pesquisar por cidade--------\n\nDigite:");
    char cidade[50];
    scanf("%*c");
    fgets(cidade, 50, stdin);

    printf("\n----------- Apartamentos -----------\n");

    for(cont = 0; cont < id; cont++){
        if(comparar(apartamentos[cont].end.cidade, 50, cidade)){
            printf("ID: %i\n", apartamentos[cont].id);
            printf("Andar: %i\n", apartamentos[cont].andar);
            printf("Descricao: %s", apartamentos[cont].descricao);
            printf("Rua: %s", apartamentos[cont].end.rua);
            printf("Bairro: %s", apartamentos[cont].end.bairro);
            printf("Cidade: %s", apartamentos[cont].end.cidade);
            printf("Numero: %i\n", apartamentos[cont].end.numero);
            printf("Medida: %s", apartamentos[cont].medida);
            printf("Numero de Quartos: %i\n", apartamentos[cont].numeroQuartos);
            switch(apartamentos[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %f\n", apartamentos[cont].preco);
            printf("Vagas Garagem: %i\n\n---------------------------\n\n", apartamentos[cont].vagasGaragem);
    }
    }
    id = buscarID("csCfg.txt");
    listagemCasas();
    printf("----------- Casas -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(casas[cont].end.cidade, 50, cidade)){
            printf("ID: %i\n", casas[cont].id);
            printf("Titulo: %s", casas[cont].titulo);
            printf("Numero de pavimentos: %i\n", casas[cont].pavimentos);
            printf("Descricao: %s", casas[cont].descricao);
            printf("Rua: %s", casas[cont].end.rua);
            printf("Bairro: %s", casas[cont].end.bairro);
            printf("Cidade: %s", casas[cont].end.cidade);
            printf("Numero: %i\n", casas[cont].end.numero);
            printf("Medida da casa: %s", casas[cont].areaConstruida);
            printf("Medida do terreno: %s", casas[cont].areaTerreno);
            printf("Numero de Quartos: %i\n", casas[cont].numeroQuartos);
            switch(casas[cont].posicaoSituada){
                case 1: printf("Posicao Situada: NORTE\n");
                break;
                case 2: printf("Posicao Situada: SUL\n");
                break;
                case 3: printf("Posicao Situada: LESTE\n");
                break;
                case 4: printf("Posicao Situada: OESTE\n");
                break;
            }
            printf("Preco: %.2f\n\n---------------------------\n\n", casas[cont].preco);
    }
    }
    id = buscarID("teCfg.txt");
    listagemTerrenos();
    printf("----------- Terrenos -----------\n");
    for(cont = 0; cont < id; cont++){
        if(comparar(terrenos[cont].end.cidade, 50, cidade)){
            printf("ID: %i\n", terrenos[cont].id);
            printf("Descricao: %s", terrenos[cont].descricao);
            printf("Rua: %s", terrenos[cont].end.rua);
            printf("Bairro: %s", terrenos[cont].end.bairro);
            printf("Cidade: %s", terrenos[cont].end.cidade);
            printf("Numero: %i\n", terrenos[cont].end.numero);
            printf("Area: %f\n", terrenos[cont].area);
            printf("Preco: %.2f\n\n---------------------------\n\n", terrenos[cont].preco);
    }
    }
    printf("Menu:\n1->Voltar\n2-Sair\nDigite:");

    int es = 0;
    scanf("%i", &es);
    while(es < 1 || es >2){
        printf("Digite corretamente!\n");
        printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
        scanf("%i", &es);
    }
    return es;
}

int main(int argc, char** argv) {
    verificaExistencia();
    while(1){
        int vInicio = entrada();//Primeiro Menu com as opçoes - Primeira camada -
        limpar_tela();
        if(vInicio == 3){
            return 0;
        }
        while(1){//Bloco da primeira escolha
            limpar_tela();
            if(vInicio == 2){
                int escolha = subMenuListar();//Segundo menu com as opcoes - Segunda camada -
                limpar_tela();
                if(escolha == 1){
                        limpar_tela();
                        break;
                    }
                if(escolha == 2){//Listar todos os imoveis
                    int es = menuListarTodos();
                    while(1){
                        if(es == 1){
                            limpar_input();
                            break;
                        }
                        if(es == 2){
                            limpar_tela();
                            listarApartamentosTodos();
                            listarCasasTodos();
                            int opcoes = listarTerrenosTodos();
                            if(opcoes == 1){
                                break;
                            }else{
                                return 0;
                            }
                        }
                        if(es == 3){
                            limpar_tela();
                            listarApartamentosTodos();
                            int es = 0;
                            printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
                            scanf("%i", &es);
                            while(es < 1 || es >2){
                                printf("Digite corretamente!\n");
                                printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
                                scanf("%i", &es);
                            }
                            if(es == 1){
                                break;
                            }else{
                                return 0;
                            }
                        }

                        if(es == 4){
                            limpar_tela();
                            listarCasasTodos();
                            int es = 0;
                            printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
                            scanf("%i", &es);
                            while(es < 1 || es >2){
                                printf("Digite corretamente!\n");
                                printf("Menu:\n1->Voltar\n2-Sair\nDigite:");
                                scanf("%i", &es);
                            }
                            if(es == 1){
                                break;
                            }else{
                                return 0;
                            }
                        }
                        if(es == 5){
                            limpar_tela();
                            int opcoes = listarTerrenosTodos();
                            if(opcoes == 1){
                                break;
                            }else{
                                return 0;
                            }
                        }
                        if(es == 6){
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 3){//Pesquisar em todos os imoveis por descricao
                    while(1){
                        limpar_tela();
                        int retorno = pesquisarPorDescricao();
                        if(retorno == 1){
                            limpar_tela();
                            break;
                        }else{
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 4){//Listar disponivel para alugar por tipo
                    while(1){
                        limpar_tela();
                        int v = escolha1();//terceiro menu com as opções - Terceira camada -
                        if(v == 1){
                            break;
                        }
                        if(v == 2){//Escolha -> Apartamentos
                           int escolhas = listarApartamentos(1);
                           if(escolhas == 1){
                               break;
                           }else{
                               return 0;
                           }
                        }
                        if(v == 3){//Escolha -> Casa
                           int escolhas = listarCasas(1);
                           if(escolhas == 1){
                               break;
                           }else{
                               return 0;
                           }
                        }
                        if(v == 4){//Escolha -> Terreno
                           int escolhas = listarTerrenos(1);
                           if(escolhas == 1){
                               break;
                           }else{
                               return 0;
                           }
                        }
                        if(v == 5){//Sair
                            return 0;
                        }
                    }
                }
                if(escolha == 5){//Listar disponivel para vender por tipo
                    while(1){
                        limpar_tela();
                        int v = escolha1();//terceiro menu com as opções - Terceira camada -
                        if(v == 1){
                            limpar_tela();
                            break;
                        }
                        if(v == 2){//Escolha -> Apartamentos
                           int escolhas = listarApartamentos(2);
                           if(escolhas == 1){
                               limpar_tela();
                               break;
                           }else{
                               limpar_tela();
                               return 0;
                           }
                        }
                        if(v == 3){//Escolha -> Casas
                            limpar_tela();
                           int escolhas = listarCasas(2);
                           if(escolhas == 1){
                               limpar_tela();
                               break;
                           }else{
                               limpar_tela();
                               return 0;
                           }
                        }
                        if(v == 4){//Escolha -> Terrenos
                           limpar_tela();
                           int escolhas = listarTerrenos(2);
                           if(escolhas == 1){
                               limpar_tela();
                               break;
                           }else{
                               limpar_tela();
                               return 0;
                           }
                        }
                        if(v == 5){//Sair
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 6){//Pesquisar em todos os imoveis por descricao
                    while(1){
                        limpar_tela();
                        int retorno = pesquisarPorBairro(1);
                        if(retorno == 1){
                            limpar_tela();
                            break;
                        }else{
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 7){//Pesquisar em todos os imoveis por descricao
                    while(1){
                        limpar_tela();
                        int retorno = pesquisarPorBairro(2);
                        if(retorno == 1){
                            limpar_tela();
                            break;
                        }else{
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 8){//Pesquisar em todos os imoveis por descricao
                    while(1){
                        limpar_tela();
                        int retorno = pesquisarPorCidade();
                        if(retorno == 1){
                            limpar_tela();
                            break;
                        }else{
                            limpar_tela();
                            return 0;
                        }
                    }
                }
                if(escolha == 9){//Sair do sistema
                        limpar_tela();
                        return 0;
                    }
            }
            else if(vInicio == 1){
                limpar_tela();
                int vE1 = escolha1();
                if(vE1 == 1){
                    limpar_tela();
                    break;
                }
                else if(vE1 == 2){
                    limpar_tela();
                    int i = cadastrarApartamento();//Cadastrar apartamentos
                    if(i == 5){
                        limpar_tela();
                        break;
                    }
                }
                else if(vE1 == 3){
                    limpar_tela();
                    int i = cadastrarCasa();//Cadastrar casas
                    if(i == 5){
                        limpar_tela();
                        break;
                    }
                }
                else if(vE1 == 4){
                    limpar_tela();
                    int i = cadastrarTerreno();//Cadastrar terrenos
                    if(i == 5){
                        limpar_tela();
                        break;
                    }
                }
                else if(vE1 == 5){
                    limpar_tela();
                    return 0;//Sair do sistema
                }
            }
        }
    }
    return 0;
}
