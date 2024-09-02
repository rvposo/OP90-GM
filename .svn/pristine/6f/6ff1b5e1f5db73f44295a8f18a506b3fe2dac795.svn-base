/* Header para a biblioteca SenhaParametros
	Por Eng. de Testes - Cícero
	
	Maio/2006
	
	NÃO MOFIFIQUE ESTE ARQUIVO
*/

#define		ABORTA_SENHA				-1
#define	 	USUARIO_INVALIDO			-2
#define	 	SENHA_INVALIDA				-3
#define		CADAST_NAO_PERMIT   		-4
#define		ABORTA_PARAMETROS   		-5
#define		ERRO_ARQ_PARAMETROS   		-6

#define 	NULO_SENHA					0
#define 	SUCESSO_SENHA				1
#define 	SAIR_GRAVAR_SENHA			2
#define 	VOLTAR_SENHA				3
#define		CADASTRAR_SENHA				4
#define		DELETAR_SENHA				5
#define		MODIFICAR_SENHA				6
#define		CONTINUAR_SENHA				7
#define		CONTINUAR_SENHA_ENTER		8
#define		SAIR_GRAVAR_PARAMETROS 		9
#define		SUCESSO_GRAVAR_PARAMETROS 	10

#define		NUMERO_MAX_PARAM			12

#define		PARAMETRO_VAZIO				-999999999 //significa parametro não utilizado pelo usuario

	
/*	Para utilizar a biblioteca de monitoramento de senhas
	1 - Acrescente ao seu projeto o arquivo 'SenhaParametros.lib'
	2 - Inclua no diretorio do projeto os arquivos 'SenhaParametros.h', 'Senha.uir' e 'Alterar Parametros.uir'
	3 - Chame do seu programa a funcao desejada;
	4 - Ela retornará 0 se tiver sucesso ou -1 para falha  */
int ValidarAcesso (char *nome_acao);  
/*	  Função int ValidarAcesso (char *nome_tela)
		- Possibilita a verificação da validação de uma senha além de monitorar os cadastros das mesmas.
		- Ela retornará 0 se senha ACEITA ou -1 para senha NÃO ACEITA.
		- Caso o usuario faça apenas modificação no cadastro ela retornará -1. */

int GeraCopiaArquivoLog(char *nome_do_arquivo_destino);
/*  Função int GeraCopiaArquivoLog(char *nome_do_arquivo_destino);
		- Possibilita a geração de arquivo com o log de todos os acessos realizados.
		- Retornará 0 se tiver sucesso ou -1 para falha.*/


int LeParametros(char *nome_do_arquivo, double Parametros[]);
/*  Função int LeParametros(char *, double[])
		- Possibilita a leitura dos parametros de um determinado arquivo de cadastros.
		- Retornará 0 se tiver sucesso ou -1 para falha.
		- Os dados lidos retornarão na array 'Parametros'.
		- O tamanho da array 'Parametros' deve ser definido igual ou maior que NUMERO_MAX_PARAM.*/
int LeParametrosBiDimen(char *nome_do_arquivo, double Parametros1[], double Parametros2[]);
/*  Função int LeParametrosBiDimen(char *, double[], double[])
		- Possibilita a leitura dos parametros de um determinado arquivo de cadastros.
		- Retornará 0 se tiver sucesso ou -1 para falha.
		- Os dados lidos retornarão nas arrays 'Parametros1' e 'Parametros2'.
		- O tamanho das arrays 'Parametros1' e 'Parametros2' devem ser definidos igual ou maior que NUMERO_MAX_PARAM.*/
		
int EditAlteraParametros (char *nome_do_arquivo ,double Parametros[] , int senha);
/*  Função int EditAlteraParametros(char *, double[], int)
		- Possibilita a leitura e alteração dos parametros de um determinado arquivo de cadastros.
		- Retornará 0 se tiver sucesso ou -1 para falha.
		- Para alteração com senha o argumento 'senha' deve ser == 1 ou 0 para alteração sem senha.
		- Os dados alterados e lidos retornarão na array 'Parametros'.
		- O tamanho da array 'Parametros' deve ser definido igual ou maior que NUMERO_MAX_PARAM.*/
int EditAlteraParametrosBiDimen(char *nome_do_arquivo ,double Parametros1[],double Parametros2[] , int senha);
/*  Função int EditAlteraParametrosBiDimen(char *, double[], double[], int)
		- Possibilita a leitura e alteração dos parametros de um determinado arquivo de cadastros com duas dimensões.
		- Retornará 0 se tiver sucesso ou -1 para falha.
		- Para alteração com senha o argumento 'senha' deve ser == 1 ou 0 para alteração sem senha.
		- Os dados alterados e lidos retornarão nas arrays 'Parametros1' e 'Parametros2'.
		- O tamanho das arrays 'Parametros1' e 'Parametros2' devem ser definidos igual ou maior que NUMERO_MAX_PARAM.*/


