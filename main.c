#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#define TAM 100

typedef struct usuario {
	char nConta[10];
	char nome[TAM];
	char cpf[12];
	char telefone[20];
	float saldo;
	int status;  // 1-ATIVO  0-DELETADO
}Tusuario;

void menu(void);
void conta(void);
int busca(FILE* arq, char numConta[]);
void cadastrar(FILE* arq, char numConta[]);
int existeArq(char nomeArq[]);
void deposito(FILE* arq, char numConta);
void saque(FILE* arq, char numConta);
void exibir(FILE* arq, char numConta);
void logica(FILE* arq, char numConta); //Apenas altera o campo status do usuário para 0
void fisica(FILE* arq, char numConta); //remove todos os usuários com status = 0

int main() {
	char op, op2, num[10];
	char nomeArq1[] = "contaCorrente";
	char nomeArq2[] = "contaPoupanca";
	int resp, qtd = 0, status;
	Tusuario usuarios[TAM];
	FILE* arq1;
	FILE* arq2;
	setlocale(LC_ALL, "portuguese_brazil");
	menu();
	printf("Informe sua opção: ");
	op = getchar(); fflush(stdin);

	switch (op) {
	case '1': //CADASTRAR
		printf("Digite o numero da nova conta: ");
		gets(num); fflush(stdin);
		do {
			conta(); //1-CORRENTE  2-POUPANÇA
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JA EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					cadastrar(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //ARQUIVO NAO EXISTE ENTÃO CRIA
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					cadastrar(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JA EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					cadastrar(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //ARQUIVO NAO EXISTE ENTÃO CRIA
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao criar o arquivo\n\n");
				}
				else {
					cadastrar(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '2': //CONSULTA
		printf("Digite o numero da conta: ");
		gets(num); fflush(stdin);
		do {
			conta();
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JÁ EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					consulta(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					consulta(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JÁ EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					consulta(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					consulta(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '3': //DEPÓSITO
		printf("Digite o numero da conta: ");
		gets(num); fflush(stdin);
		do {
			conta();
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JÁ EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					deposito(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					deposito(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JÁ EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					deposito(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					deposito(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '4': //SAQUE
		printf("Digite o numero da conta: ");
		gets(num); fflush(stdin);
		do {
			conta();
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JÁ EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					saque(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					saque(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JÁ EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					saque(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					saque(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '5': //EXIBIR
		printf("Digite o numero da conta: ");
		gets(num); fflush(stdin);
		do {
			conta();
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JÁ EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					exibir(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					exibir(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JÁ EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					exibir(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					exibir(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '6': //REMOVER-(LÓGICA)
		printf("Digite o numero da conta: ");
		gets(num); fflush(stdin);
		do {
			conta();
			op2 = getchar(); fflush(stdin);
		} while (op2 != '1' && op2 != '2');
		if (op2 == '1') { //CONTA CORRENTE
			if (existeArq(nomeArq1) == 1) { //ARQUIVO JÁ EXISTE
				arq1 = fopen(nomeArq1, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					logica(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq1 = fopen(nomeArq1, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq1 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					logica(arq1, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq1);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		else { //CONTA POUPANÇA
			if (existeArq(nomeArq2) == 1) { //ARQUIVO JÁ EXISTE
				arq2 = fopen(nomeArq2, "r + b"); //ABRE ARQUIVO PARA LEITURA E GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					logica(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
			else { //CRIAR ARQUIVO
				arq2 = fopen(nomeArq2, "w + b"); //CRIA ARQUIVO PARA GRAVAÇÃO
				if (arq2 == NULL) {
					printf("Erro ao abrir o arquivo\n\n");
				}
				else {
					logica(arq2, num); //ARQUIVO JÁ ABERTO SEM PROBLEMAS
				}
				status = fclose(arq2);
				if (status == 0) {
					printf("Arquivo fechado com sucesso\n\n");
				}
				else {
					printf("Erro ao fechar o arquivo\n\n");
				}
			}
		}
		break;
	case '7': //SAIR - REMOVER-(FÍSICA)

		break;
	default: printf("Opção inválida\n\n");
		break;
	}
	return 0;
}

void menu(void) {
	printf("1 - CADASTRAR\n");
	printf("2 - CONSULTAR\n");
	printf("3 - DEPÓSITO\n");
	printf("4 - SAQUE\n");
	printf("5 - EXIBIR\n");
	printf("6 - REMOVER\n");
	printf("7 - SAIR\n\n");
}

int busca(FILE* arq, char numConta[]) {
	int status;
	Tusuario usu;
	while (!feof(arq)) {
		status = fread(&usu, sizeof(Tusuario), 1, arq);
		if (status == 1) {
			if (strcmp(usu.nConta, numConta) == 0) {
				return -3; //ACHOU OU ERRO
			}
		}
		else {
			if (!feof(arq)) {
				printf("Erro na leitura\n\n");
				return -1;  //NÃO HÁ CADASTRO COM ESSE NUMERO
			}
		}
	}
	return -2; //VAZIO
}

void cadastrar(FILE* arq, char numConta[]) { //ARQUIVO JA ESTA ABERTO E SERÁ FECHADO NO MAIN
	int i = 0;
	int status1, status;
	Tusuario usu;
	status1 = busca(arq, numConta);
	if (status1 == -1) {
		fseek(arq, sizeof(Tusuario), 2);
		strcpy(usu.nConta, numConta);
		printf("Digite o nome: ");
		gets(usu.nome); fflush(stdin);
		printf("Digite o CPF: ");
		gets(usu.cpf); fflush(stdin);
		printf("Digite o telefone: ");
		gets(usu.telefone); fflush(stdin);
		printf("Digite o saldo: ");
		scanf("%f", &usu.saldo);
		usu.status = 1;
		status = fwrite(&usu, sizeof(Tusuario), 1, arq); //
		if (status == 1) {
			printf("Registo gravado com sucesso\n\n");
		}
		else {
			printf("Erro na gravação\n\n");
		}
	}
	else if (status == -2) {
		fseek(arq, sizeof(Tusuario), 0);
		strcpy(usu.nConta, numConta);
		printf("Digite o nome: ");
		gets(usu.nome); fflush(stdin);
		printf("Digite o CPF: ");
		gets(usu.cpf); fflush(stdin);
		printf("Digite o telefone: ");
		gets(usu.telefone); fflush(stdin);
		printf("Digite o saldo: ");
		scanf("%f", &usu.saldo);
		usu.status = 1;
		status = fwrite(&usu, sizeof(Tusuario), 1, arq);
		if (status == 1) {
			printf("Registo gravado com sucesso\n\n");
		}
		else {
			printf("Erro na gravação\n\n");
		}
	}
	else {
		printf("ERRO AO CADASTRAR UM NOVO NUMERO DE CONTA\n\n");
	}
}

void conta(void) {
	printf("1 - CONTA CORRENTE\n");
	printf("2 - CONTA POUPANÇA\n");
	printf("Informe a conta: ");
}

int existeArq(char nomeArq[]) {
	FILE* arq;
	arq = fopen(nomeArq, "rb"); //ABRE ARQUIVO P/ LEITURA
	if (arq == NULL) {
		return 0;
	}
	else {
		fclose(arq);
		return 1;
	}
}

void consulta(FILE* arq, char numConta[]) {
	Tusuario usu;
	int statusBusca, status;
	statusBusca = busca(arq, numConta);
	if (statusBusca == -2) {
		printf("NÃO HÁ CONTAS REGISTRADAS\n\n");
	}
	else if (statusBusca == -1) {
		printf("NÃO HÁ CADASTROS COM ESSE NUMERO\n\n");
	}
	else {
		while (!feof(arq)) {
			status = fread(&usu, sizeof(Tusuario), 1, arq);
			if (status == 1) {
				if (strcmp(numConta, usu.nConta) == 0) {
					printf("Saldo: %.2f\n\n", usu.saldo);
					break;
				}
			}
			else {
				if (!feof(arq)) {
					printf("Erro de leitura\n\n");
				}
			}
		}
	}
}

void deposito(FILE* arq, char numConta) {
	int i, status, aux = 0;
	Tusuario usu;
	float dep;
	fseek(arq, 0, 0);
	status = busca(arq, numConta);
	if (status == -1) {
		printf("Não há cadastros com esse numero de conta\n\n");
	}
	else if (status == -2) {
		printf("Não há cadastros\n\n");
	}
	else {
		while (!feof(arq)) {
			status = fread(&usu, sizeof(Tusuario), 1, arq);
			if (status == 1) {
				if (strcmp(usu.nConta, numConta) == 0) {
					printf("Informe o valor para depositar: ");
					scanf("%f", &dep);
					aux = 1;
					break;
				}
			}
			else {
				printf("Erro na leitura do registro\n\n");
			}
		}
		if (aux == 1) {
			usu.saldo = usu.saldo + dep;
			status = fwrite(&usu, sizeof(Tusuario), 1, arq);
			if (status != 1) {
				printf("Erro na gravação do depósito\n\n");
			}
		}
	}
}

void saque(FILE* arq, char numConta) {
	int i, status, aux = 0;
	Tusuario usu;
	float saq;
	fseek(arq, 0, 0);
	status = busca(arq, numConta);
	if (status == -1) {
		printf("Não há cadastros com esse numero de conta\n\n");
	}
	else if (status == -2) {
		printf("Não há cadastros\n\n");
	}
	else {
		while (!feof(arq)) {
			status = fread(&usu, sizeof(Tusuario), 1, arq);
			if (status == 1) {
				if (strcmp(usu.nConta, numConta) == 0) {
					printf("Informe o valor para sacar: ");
					scanf("%f", &saq);
					aux = 1;
					break;
				}
			}
			else {
				printf("Erro na leitura do registro\n\n");
			}
		}
		if (aux == 1) {
			usu.saldo = usu.saldo - saq;
			status = fwrite(&usu, sizeof(Tusuario), 1, arq);
			if (status != 1) {
				printf("Erro na gravação do saque\n\n");
			}
		}
	}
}

void exibir(FILE* arq, char numConta) {
	int i, status, aux = 0;;
	Tusuario usu;
	fseek(arq, 0, 0);
	while (1) {
		fread(&usu, sizeof(Tusuario), 1, arq);
		if (!feof(arq)) {
			if (strcmp(usu.nConta, numConta) == 0) {
				aux = 1;
				break;
			}
		}
	}
	if (aux == 1) {
		printf("Numero da conta: %s\n", numConta);
		printf("Nome: %s\n", usu.nome);
		printf("CPF: %s\n", usu.cpf);
		printf("Telefone: %s\n", usu.telefone);
		printf("Saldo: %.2f\n", usu.saldo);
		printf("Status: %d\n\n", usu.status);
	}
}

void logica(FILE* arq, char numConta) {

}