/**
* @file  bd-support.h
* @version 1.21
*/

#define BDSUPPORT_TAM_MAX_DESC_ERROR 	300
#define MNS_MAX_TAM_NOME_AMOSTRA 50


//==============================================================================
// Include files

#include "cvixml.h"

//==============================================================================
// Enums
/**
* Status válidos para uma sequência de testes.
*/
enum status_seq_testes
{
	BD_APROVADO, ///< Sequência de testes concluída com sucesso.
	BD_REJEITADO, ///< Sequência de testes concluída com falha.
};

/**
* Tipo válidos para uma sequência de testes.
*/
enum tipo_seq_testes
{
	BD_TESTE, ///< Sequência de testes do tipo normal
	BD_AMOSTRA_NEGATIVA, ///< Sequência de testes realizada para validação de uma amostra negativa.
	BD_AMOSTRA_POSITIVA, ///< Sequência de testes realizada para validação de uma amostra positiva.
};

/**
* Frequencia de execução para amostras negativa
*/
enum msn_frequencia_amostra
{
	MNS_FREQ_DIARIA, ///< Frequencia diária de execução para uma amostra negativa
	MNS_FREQ_SEMANAL ///< Frequencia semanal de execução para uma amostra negativa
};


//==============================================================================
// Global functions
int  BDSupport_Inicializa(char *id_linha_producao, char *id_equipamento, char *caminho_bd, char *caminho_log_erros, char *mens_falha);
void BDSupport_Finaliza (void);
int  BDSupport_Emergencia_Acionada(char *mens_falha);
int  BDSupport_Criar_Sequencia_Testes(CVIXMLDocument *sequencia_testes, char *mens_falha);
int  BDSupport_Adiciona_Teste_Executado_Na_Sequencia(CVIXMLDocument *sequencia_testes, char *nome, double limite_inferior, double resultado, double limite_superior, char *unidade, enum status_seq_testes condicao, double tempo_teste, char *mens_falha);
int  BDSupport_Adiciona_Versao_Software_Produto(CVIXMLDocument *sequencia_testes, char *versao_software_produto, char *mens_falha);
int  BDSupport_Adiciona_Part_Number_Cliente(CVIXMLDocument *sequencia_testes, char *part_number_cliente, char *mens_falha);
int  BDSupport_Adiciona_Part_Number_Visteon( CVIXMLDocument *sequencia_testes, char *part_number_visteon, char *mens_falha);
int  BDSupport_Salvar_Sequencia_Testes(CVIXMLDocument sequencia_testes, char *versao_software_teste, enum tipo_seq_testes tipo, char *berco, char *numero_serie, enum status_seq_testes status, double tempo_total, char *mens_falha);
int  BDSupport_Registrar_Alteracao_Configuracao(char *nome_parametro_alterado, char *mens_falha);

//==============================================================================
// Global functions
int MNSSupport_Inicializa (char *caminho_config_mss, int modo_opcional, char *mens_falha);
int MNSSupport_LerTipoSequencia (char *prefixo, enum tipo_seq_testes *tipo, char *mens_falha);
int MNSSupport_AtivaCriarAmostraNegativa(char *nome, enum msn_frequencia_amostra frequencia, char *mens_falha);
int MNSSupport_DesativaCriarAmostraNegativa(char *mens_falha);
int MNSSupport_Analise_Inicial_Seq_Testes(char *numero_serie, int berco, char *mens_falha);
int MNSSupport_Analise_Final_Seq_Testes(CVIXMLDocument sequencia_testes, char *numero_serie, int berco, char *mens_falha);
int MNSSupport_StatusAmostraPositiva(int berco);
int MNSSupport_StatusAmostraNegativa(int berco);
int MNSSupport_StatusCriarAmostraNegativa(void);
int MNSSupport_VerificaPendenciasBerco(int berco, enum tipo_seq_testes *tipo_amostra_pendente, char * numero_serie_pendencia, char * nome_pendencia, char *mens_pendencia);
