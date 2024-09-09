#include "cvixml.h"       

#define VERSAO						"3.2.3"

#ifndef OFF
#define OFF	    					0
#endif /* OFF */

#ifndef ON
#define ON	    					1
#endif /* ON */

#ifndef off
#define off	    					0
#endif /* off */

//#ifndef on
//#define on	    					1
//#endif /* on */

/* 	A macro statusChk � �til para implementar uma verifica��o de erro para opera��es
	executadas em sequencia. Esta macro pode ser colocada em torno de chamadas de fun��o para
����ativar um 'flag' indicando a ocorr�ncia de uma falha, por meio da vari�vel statusErro.

����Esta macro faz as seguintes suposi��es:

��������1) As seguintes declara��es de vari�veis locais:

������������int status = 0;
			int statusErro = 0;

��������2) Toda chamada de fun��o ou c�digo de erro contido em uma macro statusChk ()
������������� assumido para retornar um inteiro que, se negativo, � o c�digo para
������������o erro que ocorreu. Se o valor for zero ou positivo, ent�o a o valor de
			statusErro se manter� inalterado.
*/

#ifndef statusChk
#define statusChk(fCall) if (status = (fCall), status < 0) \
{statusErro=1;} else
#endif

	
//BD1
#define	CAMINHO_BD_DADOS			"V:\\Gem\\TFCP\\Dados\\DadosBD"  

#define MAX_QUANT_MODELOS			100
#define	TABELAS_REDE_VERSAO			"Ver_2.3"
#define	PASTA_TAB_REDE				"V:\\GEM\\TFCP\\Tabelas\\"
#define	PASTA_REDE_CTR				"V:\\GEM\\"
#define	PASTA_TAB_LOCAIS			"Tabelas\\" 

#define TABELA_MODELOS_REDE			"\\Modelos.txt" 

#define TABELA_MODELOS_LOCAL		PASTA_TAB_LOCAIS"Modelos.txt"
#define ARQ_FTT						"..\\Dados\\ftt.txt"
#define PATH_LOG_CAN   		        "..\\Logs_CAN\\"        
#define DIR_TEMPLATES				"..\\Templates\\"   
#define ARQ_TIPO_ATUAL				"Tabelas\\ModeloAtual.txt"  
#define TAB_MODEL_SELECT			"Tabelas\\Model_Selecionado.txt"
	
#define CAMINHO_NVM    				"..\\Dados\\NVM\\"            


/*----------- cyber security -----------------*/
#define PATH_LIVE_KEY 				"E:\\Live_key\\"  
#define PATH_L_KEY_M4_M5			PATH_LIVE_KEY"M4_M5\\"  
#define PATH_L_KEY_LOCAL_1			PATH_LIVE_KEY"Local_1\\"  
#define PATH_L_KEY_LOCAL_2			PATH_LIVE_KEY"Local_2\\"  
#define ARQ_FLAG_ACESS_LKEY 		"LiveKeyFileBeenUsed"  
#define ARQ_REG_INDEX_LKEY 			"LiveKey_Index.txt" 
#define ARQ_ATUAL_ASC_LKEY 			"Atual_LiveKey_File.txt" 
#define MAX_TAM_ARQ_LKEY			2000000 //max 2Mbytes
#define MAXIMO_INDEX_LIVKEY 		100000  //maximo index permitido
#define MIN_TAMANHO_ARQ_ASC_LKEY 	300  		//bytes
#define MAX_TAMANHO_ARQ_ASC_LKEY 	2000000  	//bytes

#define OPERACAO_PCB_TEST		1 
#define OPERACAO_POINTER_PLACEM	2
#define OPERACAO_TFCP			3         
#define OPERACAO_VISION			4 
#define OPERACAO_RUNIN			5
#define OPERACAO_FALTANDO		0xFF

#define STATUS_OPER_NOT_TEST	0x00 
#define STATUS_OPER_IN_TEST		0x01 
#define STATUS_OPER_REJEITO		0x02
#define STATUS_OPER_APROVAD		0x03
#define STATUS_FALTANDO			0xFF

#define TAM_MAX_RESP_PIC			100
#define NUM_MAX_LINHAS_ARQ			150  //numero m�ximo de linhas permitido em um arquivo
#define	NAO_SAIR					0
#define SAIR_LOOP_SEM_ERRO			1
#define	SEM_ERRO					0
#define	SUCESSO						0
#define	FALHA						-1
#define	FALHA_TIMEOUT				-2
#define	EMERG_ACIONADA				-3
#define FALHA_MODELO_NAO_ENCONTRADO -12
#define FALHA_PRODUTO_AUSENTE		-14
#define FALHA_REJ_OPERADOR			-15
#define FALHA_MODULO_ABORTADO		-17
#define FALHA_GRAVE					-500
#define RES_FALHA					-999
#define	EXIT_PROGRAM				999

#define ABERTO			  			0
#define CONT			  			1
#define REJ			  				2
#define CONT_REJ	  				3
#define BOT_TIMEOUT	  				-1
#define BOT_ON			  			1
#define	BOT_OFF		  				0
#define	PRODUTO_OFF					0
#define	PRODUTO_TESTANDO			1
#define	PRODUTO_APROVADO			10
#define	PRODUTO_REJEITADO			-10

#define MONITOR_A					1
#define MONITOR_B					2

#define	CPK 						2
#define	HISTOR_CPK					3

#define	CAMINHO_DADOS	 			"..\\Dados\\"
#define	CAMINHO_APROVADOS 			CAMINHO_DADOS"Aprovados\\"
#define	CAMINHO_CPK_APROV   		CAMINHO_APROVADOS"CPK\\"
#define	CAMINHO_REJEITOS 			CAMINHO_DADOS"Rejeitados\\"
#define	CAMINHO_TEMPLATES 			"..\\Templates\\"
#define	CAMINHO_SONS 	 			"..\\Sons\\"


#define DIR_CONFIG					"..\\Config\\"
#define ARQ_CONFIG_MAQ				DIR_CONFIG"Config_Maq.txt"
#define	CAMINHO_ETIQUETAS 			"Etiquetas\\"

////////////////////////////////////////////////////////////////////////////////////
#define NUM_SCANNERS				2
#define LER_BCR_ENDITEM				1

#define	TAMANHO_NUM_SERIE_MTC		9  

#define	TAMANHO_PREFIXO_MTC			3
#define	TAMANHO_BARCODE_ENDITEM		11    
#define	TAMANHO_PREFIXO_ENDITEM		5
#define TIME_OUT_BCR_ENDITEM		5.0   //tempo em segundos  //
#define TEMPO_DESL_BCR				10.0  //tempo em segundos - DESLIGA barcode ap�s retirar o produto //

#define PADRAO_PREFIXO_GRUPO        "SJ"

//////////////////////////////////////////////////////////////
#define TAMANHO_DM                  65
#define INDEX_START_SN_DM			54

/////////////////////////////////////////////////////////////
	
#define	BARCODE_PADRAO_ENDITEM		"1XX01X00001"
#define	PADRAO_PREFIX_ENDITEM		"1XX01"

#define	BARCODE_PADRAO_ENDITEM_DM	"SJY01A00001"
#define	PADRAO_PREFIX_ENDITEM_DM	"SJY01"





#define TEMPO_MAX_BIMANUAL			1.00 // segundos
#define TEMPO_MAX_AUSENCIA			0.70 // segundos
	
#define TEMPO_MAX_PRESENCA			1 // segundos 	
	
#define TEMPO_MAX_SCANNER_LIGADO	120 // segundos

//////////    ENDERE�OS CART�ES DE I/O    //////////

#define END_CARTAO_1_ENTRADA		0x40
#define END_CARTAO_5_ENTRADA		0x4E
#define END_CARTAO_2_SAIDA			0x42
#define END_CARTAO_3_SAIDA			0x44
#define END_CARTAO_4_SAIDA			0x46

#define TEMPO_MOSTRAR_WARNING		4.0  //segundos
#define TIME_OUT_FOTO				4.0
#define DEBOUNCING_EMERGEN			5 //Quant leituras p/ debouncing

#define MODO_SLEEP					VAL_SLEEP_SOME  //VAL_SLEEP_MORE
#define NUMERO_DE_BERCOS			2

#define VOLTS_0 					0	
#define VOLTS_12_6 					1
#define VOLTS_13_5 					2	
#define VOLTS_15 					3	


#define R_604                       1
#define R_1624						2 
#define R_3534                      3     

#define QUANT_DEBOUNCING		    2  
	
#define timeout_TBC                 10 //15

#define	ABORTAR						-2 

#define CheckIf_Sucesso 	if(status != SUCESSO) return status;
	
enum  //aqui
{
	BERCO_1 = 1,
	BERCO_2 = 2,
} BERCOS;

enum
{
	MENS_OFF,
	MENS_BOT_TRAVADO,
	MENS_MODEL_FILE_ERROR,
	MENS_MODEL_CADAST_ERROR,
	MENS_MODEL_CONFIG_TAB_ERROR,
	MENS_TEST_TAB_ERROR,
	MENS_CIM_ON,
	MENS_CIM_OFF,
	MENS_CIM_ERROR,
	MENS_PRODUTO_AUSENTE,

}
MENS_WARNING;

enum
{
	RETESTA,
	NAO_RETESTA
} TRAT_REJ;

enum
{
	MENS_VERMELHO,
	MENS_AMARELO,
	MENS_AZUL,
	MENS_PRETO,
	MENS_CINZA,
	MENS_VERDE
}
COR_MENSAGENS;

typedef enum
{
	SEM_SOM,
	TOCAR_SOM,
	TOCOU_SOM
} ALARME_SOM;

enum
{
	SCANNER_1=0,
	SCANNER_2=1,
} SCANNERS;

/******* Enumeracao dos modos de funcionamento da thread de sistema *******/
typedef enum
{
	LEITURA_APENAS,
	ESCRITA_APENAS,
	ESCRITA_E_LEITURA,
	ESCRITA_MOTOR,
	PARAR_ESC_LEIT
} MODO_THREAD;
MODO_THREAD modo_thread;


/***************** Enumeracao dos modos de leitura de tens�o do CAN ********************/
typedef enum 
{ 
	CAN_HI_MIN=0,
	CAN_HI_MAX,
	CAN_LO_MIN,
	CAN_LO_MAX
} MODO_TENSAO_CAN;




typedef
	char TipoNomeArquivo[250];

/************************* Estrutura da Tabela ***********************************************/
struct TabelaTestes
{
	int
		Numero;
	char
		Nome[80],
		Unidade[10],
		Condicao[10];
	double
		LimAlto,
		LimBaixo,
		Resultado,
		Reteste,
		Tempo_teste;
} Teste[NUMERO_DE_BERCOS+1][150], TestNSample[NUMERO_DE_BERCOS+1][150];

/****************************** ESTRUTURA PORTAS I/O ******************************/
typedef struct //esta estrutura define o formato dos bits em uma porta
{
	unsigned int
		bit_a0:1,
		bit_a1:1,
		bit_a2:1,
		bit_a3:1,
		bit_a4:1,
		bit_a5:1,
		bit_a6:1,
		bit_a7:1,

		bit_b0:1,
		bit_b1:1,
		bit_b2:1,
		bit_b3:1,
		bit_b4:1,
		bit_b5:1,
		bit_b6:1,
		bit_b7:1;


	
}porta;

//****************************** Declara��o das vari�veis de ENTRADA ******************************/
struct
{
	/////////// cartao_1 ///////////
	unsigned int
		ClampRec_1 		:1,
		ClampAdv_1 		:1,
		ConectorAdv_1 	:1,
		PresCluster_1 	:1,
		Combitac_Berco1 :1,
		ClampRec_2 		:1,
		ClampAdv_2 		:1,
		ConectorAdv_2 	:1,
		PresCluster_2 	:1,
		Combitac_Berco2 :1,
		Spare_in_110 	:1,
		Spare_in_111 	:1,
		Bimanual 		:1,
		Rejeita 		:1,
		Continua 		:1,
		Status_Emergencia:1;
		
	/////////// cartao_5 ///////////

   /* Alternativa: Utilizar o cartão 5 para endereçamento dos LEDs, eliminando a necessidade de utilizar outro cartão */

	unsigned int
		Trava_Porta_Avc :1,
		Trava_Porta_Rec :1,
		Porta_Fechada 	:1,

		/*Utilizado os endereços placeholders Spare_in_503 até Spare_in_508 para endereçar os sensores*/

		StatusSensorSupEsq 	:1,
		StatusSensorSupDir	:1,
		StatusSensorInfEsq 	:1,
		StatusSensorInfDir 	:1,
		StatusSensorSupMid 	:1,
		StatusSensorInfMid 	:1,
		Spare_in_509 	:1,
		Spare_in_510 	:1,
		Spare_in_511 	:1,
		Spare_in_512 	:1,
		Spare_in_513 	:1,
		Spare_in_514 	:1,
		Spare_in_515 	:1;

	/* Status Sensores dos Parafusos	*/
	/* unsigned int

	    StatusSensorSupEsq	:1,
		StatusSensorSupDir	:1,
		StatusSensorInfEsq	:1,
		StatusSensorInfDir	:1,
		StatusSensorSupMid	:1,
		StatusSensorInfMid	:1;
*/

	
		

} STATUS;

/****************************** Declara��o das variaveis de SAIDA ******************************/

struct
{
	/////////// cartao_2 ///////////
	unsigned int
		Reseta_emerg :1,
		Habilita_emerg :1,
		Spare_Out_203 :1,
		Spare_Out_204 :1,
		Spare_Out_205 :1,
		Spare_Out_206 :1,
		Spare_Out_207 :1,
		Spare_Out_208 :1,
		SolClampCluster_1 :1,
		SolConectorCluster_1 :1,
		SolClampCluster_2 :1,
		SolConectorCluster_2 :1,
		TravaPorta :1,
		Sol_Combitac :1,
		ContatoraVibracao :1,
		Spare_Out_215 :1;

	/////////// cartao_3 ///////////
	unsigned int
		Battery_1 :1,
		Crank_Run_1 :1,
		Spare_Out_302 :1,
		Spare_Out_303 :1,
		DIC_SWINPUT_Dig_1 :1,
		ServiceEngineSoon_1 :1,
		Spare_Out_306 :1,
		Battery_2 :1,
		Crank_Run_2 :1,
		Spare_Out_309 :1,
		Spare_Out_310 :1,
		DIC_SWINPUT_Dig_2 :1,
		ServiceEngineSoon_2 :1,
		Spare_Out_313 :1,
		VccDireto_Shunt_1 :1,
		VccDireto_Shunt_2 :1;

	/////////// cartao_4 ///////////
	unsigned int
		HabilitaFonte_1 :1,
		HabilitaFonte_2 :1,
		PS_Inp_select1 :1,
		PS_Inp_select2 :1,
		FonteDut1_12_6V :1,
		FonteDut1_13_5V :1,
		FonteDut1_15V :1,
		FonteDut2_12_6V :1,
		FonteDut2_13_5V :1,
		FonteDut2_15V :1,
		DIC_SW1_ADJ_604R :1,
		DIC_SW1_ADJ_1624R :1,
		DIC_SW1_ADJ_3534R :1,
		DIC_SW2_ADJ_604R :1,
		DIC_SW2_ADJ_1624R :1,
		DIC_SW2_ADJ_3534R :1;
		
		/* CART�O 5 - SAIDA SENSORES */
		
		unsigned int
		
		SensorInfEsq	:1,
		SensorSupEsq	:1,
		SensorInfDir	:1,
		SensorSupDir	:1,
		SensorInfMid	:1,
		SensorSupMid	:1;

} SAIDA;

struct
{
	int
		retrabalho,
		cluster_type,
		solicitando_vision,
		amostra_tipo,
		quant_img_instrucao,
		index_img_instrucao,
		cor_mensagens,
		movein_feito,
		rejeitado,
		medindo_corrente,
		medindo_tensao,
		tipo_service,
		teste ,
		pos_teste,
		max_teste,   
		
		testar_produto,
		aborta_testes,
		modelo,
		modulo_em_teste,
		status_produto,
		parar_mensagens_auto,
		num_teste,
	
		retestar,
		rejeita_montagem,
		bcr_resetado,
		status_debounc_presenca_produto,
		barcode_enditem_lido,
		tamanho_sn_enditem_lido,
		iSwap,
		scanner_id,
		crtlID_presenca,
		crtlID_mensagem,
		crtlID_pic_instrucao,
		crtlID_pic_instrucao2,
		crtlID_teste,
		crtlID_nome,
		crtlID_status,
		crtlID_lim_inf,
		crtlID_lim_sup,
		crtlID_resultado,
		crtlID_unidade,
		crtlID_tempo,
		crtlID_mens_falha,
		crtlID_serial_enditem,
		crtlID_PN_Visteon ,
		crtlID_amostra,
		crtlID_descricao_modelo,
		cyber_sec_ativo,
		crtlID_tabela;
		
	double
		tempo_total,
		tempo_bcr_enditem,
		tempo_inicial_teste,
		tempo_inic_total_teste,
		tempo_tela_img_instrucao,
		tempo_mostra_warning;
	char
		nvm_version[50],
		descricao_modelo[50],
		visteon_end_item[30],
		
		tab_config[60],
		costumer_pn[20],
		ecu_hardware_number[30], 			
		descricao_modelo_atual[50],
		sw_version[20],
		tab_testes[60],
		pn_customer[20],
		pn_visteon[30],
	
		duns_code[50],
		vpps_code[20], 
	
		display[10],
		
		tipo_amostra[30],
		ref_GM[20],
		tab_CFG [60],
		prefixo_enditem[6],
		prefixo_anterior[6],    
		
		
		prefixo_enditem_DM[6],
		N_Serie_EndItem[20],
		N_Serie_EndItem_anterior[20],
		mens_montagem_1[200],
		mens_montagem_2[100],
		
		mens_montagem_3[100],
		mens_montagem_falha[100],
		MensagemFalha1[150];
	TipoNomeArquivo
		imagem_instrucao[10];
		
	//BD12
	CVIXMLDocument
		 SequenciaBD;
	
		
} dados_berco[NUMERO_DE_BERCOS + 1];

struct
{
	int
		ler_string_scanner,
		leitor_scanner_ativado,
		scanner_habilitado,
		comm_scanner,
		habilitar_leitor_enditem,
		desabilitar_leitor_enditem,
		leu_serial_scanner_manual;
	char
		strGotScanner[100];
	double
		tempo_scanner_enditem_ligado;

} dados_scanner[NUMERO_DE_BERCOS + 1];

//////////    Declara��o de variaveis    //////////

ALARME_SOM alarme_som;

char
	foto_TELLTALES_AMBER[100],
	foto_TELLTALES_BLUE[100],
	foto_TELLTALES_RED[100],
	foto_TELLTALES_GREEN[100],
	foto_TELLTALES_WHITE[100],
	foto_TELLTALES_ALL_ON[100],
	foto_TELLTALES_ALL_OFF[100],
	foto_COSMETICO_TFT[100],
	foto_COSMETICO_TACO[100],
	foto_COSMETICO_VELO[100],
	foto_LEDS_LIGASTD[100],
	foto_GAGES_0_0[100],
	foto_GAGES_3000_80[100],
	foto_GAGES_8000_200[100];

char 
	nome_arquivo_flag_live_key[500],
	nome_arq_ASC_live_key[500],
	*dados_arq_ASC_live_key; 


char
	img_comp [100],  
	nomeCADASTRO[80],
	Data[50],
	sprontuario[50],
	mens[100],
	texto[300],
	tab_config[50],
	Num_Maquina[15],
	Dtimer[50],
	DmesI[50],
	strGP0[10],
	strGP1[10],
	*Rodape,
	id_model_byte[MAX_QUANT_MODELOS][10],
	id_prefix_enditem[MAX_QUANT_MODELOS][10],
	index_alpha_code[180][MAX_QUANT_MODELOS],
	index_pn_custumer[180][MAX_QUANT_MODELOS],
	index_tab_config[180][MAX_QUANT_MODELOS],
	index_tabela_testes[180][MAX_QUANT_MODELOS],
	index_modelo_aplique[180][MAX_QUANT_MODELOS],
	index_pn_visteon[180][MAX_QUANT_MODELOS],
	index_prefix_enditem[180][MAX_QUANT_MODELOS],
	index_descricao_modelo[180][MAX_QUANT_MODELOS],
	index_display[180][MAX_QUANT_MODELOS],
	index_master_sample[180][MAX_QUANT_MODELOS];
	
int  
			ocup_1,
			ocup_2;
			
int
	test_diag,
	cont_remoto,
	rej_remoto,
    cont_remoto ,
	usar_porta,
	usar_printer,
	usar_runin,
	imprimir,
	oc_1,
	oc_2,
	tipo_aplique,
	horas,
	minutos,
	segundos,
	Mes,
	Dia,
	Ano,
	portGP0[16],
	portGP1[16],
	cim_conectado,
	coletando_dados,
	acesso_remoto,
	em_debug,
	sair_programa,
	esperando_ler_botoeira,
	finalizar_thread_sistema,
	retornar_movimentos,
	motions_clear_to_move,
	painel_auto,
	painel_manual,
	painel_logo,
	panel_CAN_diagnostico,
	painel_mensagens,
	painel_padrao,
	tipo_monitor,
    status_bimanual,
	status_emergencia,
	all_motions_home,
	comm_sistema,
	////////////////
	PoolHandle,
	////////////////
	loop_manual,
	modo_manual;

double
	i_ref_EOL[NUMERO_DE_BERCOS + 1],
	tempo_total,
	TotalAprovados ,
	TotalRejeitados,
	TotalTestados,
	TotalFTT,
	TotalTestados_ant,
	ftt;
	
//////////////////////////////////////	
int
	address[2048], // 14500 para Intel
	nTotalLines	,
	sair_programa,
	em_debug,
	comunicando_sistema,
	modo_sleep,
    cont  ,
  	max_teste,
  	teste ,
	panel_CAN_diagnostico ,
  	painel_manual,
  	modelo,
	tst,
	modelo_atual_index;	
	

/************************ Variaveis para uso no cim ************************/

char stationID[15],
	mensagem[500],
	host[20],
	service[20],
	descric_operacao[20],
	*resp_itostr,
	*resp_str_mid;
HRESULT
	rescim;
short
	sockID,
	resultcim;
long
	timestamp;
CAObjHandle
	cimsockets;

int	
	start_test,
	carga,
	parar_mensagem_auto; 
	
double 
	t_BC [NUMERO_DE_BERCOS + 1],
	tempo_presenca_off[NUMERO_DE_BERCOS + 1];
	
CmtThreadFunctionID	
	sistema_threadID,
	ciclo_threadID[NUMERO_DE_BERCOS + 1],
	CAN_threadID[NUMERO_DE_BERCOS + 1];
	
int	
	t_sinc_1,
	t_sinc_2,
	atual_counts_velo[NUMERO_DE_BERCOS+1],
	atual_counts_taco[NUMERO_DE_BERCOS+1],

	
	
   	add_mtc_1,
	add_mtc_2,
	add_mtc_3,

	add_sw_1,
	add_sw_2,
	add_sw_3,
	
	

   ctrlarrayinfoteste[NUMERO_DE_BERCOS + 1],
   painel_tab[NUMERO_DE_BERCOS + 1];	
	
unsigned long
	add_traceability,
	add_cluster_hardware_number,
	add_cluster_costumer_enditem_pn,
	add_cluster_visteon_config,
	add_nvm_ecu_calibration_data;
	
	
char 
	
	prefix_placa[10];
	
int
	db_cont,
	db_rej,
	
	db_cont_1,
	db_rej_1,
	
	db_bi,
	max_db_cont,
	max_db_rej,
	
	max_db_cont_1,
	max_db_rej_1,

	cont_remoto,
	rej_remoto,
	bimanual_remoto,

	my_prod_1,
	my_prod_2,
	HW_present;	

/*********************************************************************************************
 *						        		PROTOTIPOS DE FUN��ES  						         *
 *********************************************************************************************/
int SolicitaAtualizarTabela(void);
int CalendarioDiadoAno(void);
int    CVICALLBACK ThreadSistema (void *parametro);
void   Atualiza_Manual(void);
void   Status_Seguranca(void);
int    LeWORDfromMCP23017 ( int Add, int *PortA, int *PortB );
int    EscreveMCP23017byPIC ( char *send_data, int *GP0, int *GP1 );
int    EsperaRetornoPIC( char *bRetorno );
int    EnviaCommand_C_ToPIC ( int Add );
int    EnviaCommand_A_ToPIC ( int Add );
int    EsperaBimanual(int berco);
void   Delay_thread(double segundos);
int    LeBotoeira(int berco);
int    ResetarEmergencia(int testar_consistencia);
int    IniciaPortasDeSaida(char *mens_erro);
int	   Le_Entradas(int);
int	   AtualizaCartaoSaida(int cartao);
void   SetMensAutoAllOFF(char *mens1, char *mens2, char *mens3, int berco);
void   SetMensAuto_ON(char *mens1, int berco);
void   PrintMensWarning(ALARME_SOM alarme, int berco);
int    VerificaNoButton(void);
void   Habilita_Scanner(int num_scanner);
void   Desabilita_Scanner(int num_scanner);
int    MoveClampBerco1 (int acao);
int    MoveClampBerco2 (int acao);
int    MoveConectorBerco1 (int acao);
int    MoveConectorBerco2 (int acao);
int    MoveCombitac (int acao);
int    Ativa_Leitor(int berco);
void   AtualizaFTT(void);
void   ApresentaImagemInstrucao(void);
void   AdicionaImagemInstrucao(int ordem_apresentacao, char nome_imagem[], int berco);
int    CarregaTabela(int berco);
int    CVICALLBACK CicloAutomatico (void *parametro);
int	   CVICALLBACK Thread_CAN (void *berco);
void   ColetaDados(int Max_Test, int berco);
int    DefModel(char *prefixo, int tamanho_barcode, int tipo_leit, int berco);
int    FuncRejeitado(char *Rodape, char *mensagem_teste, int berco);
void   Finaliza_Loop_Principal(void);
int    InicializaCIM(void);
int    MoveIn_Cim (int berco);
int    InicializaMaquina(void);
void   InicializaPainelAuto(void);
int    InicializaPortasSeriais(int berco);
int    Inicializar_CircuitosSeguranca(int testar_consistencia );
int    LeBarcode(int tipo_leitura, int berco);
int    LoopPrincipal(void);
int    main (int argc, char *argv[]);
void   MensagensAuto(void);
void   MoveOut_Build_Cim(char *prefixo, double Res, int Rej, char* Test, int berco);
int    PresetaTeste(int berco);
void   ProntoParaTeste(void);
int    Reconect_CIM(void);
void   ResetBarcode(int bcr_enditem_pronto, int berco);
int    RetornaMovimentos(int testar_consistencia, char *mens_falha);
int    SetEmDebug(int berco);
int    SolicitaAtualizarTabela(void);
int    Verifica_Barcodes(int berco);
int    VerificaSerialScanner(int tamanho_barcode, int berco);
void   Zera(void);
int    InicializaTestes(int berco);
double ExecutaTestes(int pos_teste, char*tab_spare, char*pn_cliente, int modelo, int berco);
int    FinalizaTestes(double res, int berco);
int    VerificaExcecoesExecucao(double *resp, char * mens_falha, int berco);
int    VerificaExcecoesExecucaoBiManual(double *resp, char * mens_falha, int berco);
int    VerificaExcecoesRetornaMovimentos(int *resp, char * mens_falha);
int    VerificaExcecoesMovimentoAtuador(char titulo_atuador[], int status_atuador, double *resp, char * mens_falha, int berco);
int    StatusTeste(double res, int berco);
double Corrente_Bateria(char * mens_falha, int berco);
double Corrente_Leds_Ambar(char * mens_falha, int berco);
double Verificacao_Leds_Ambar_1(char * mens_falha, int berco);
double Verificacao_Leds_Ambar_2(char * mens_falha, int berco);
double Verificacao_Leds_Ambar_3(char * mens_falha, int berco);
double Corrente_Leds_Azul(char * mens_falha, int berco);
double Verificacao_Leds_Azul(char * mens_falha, int berco);
double Corrente_Leds_Vermelhos(char * mens_falha, int berco);
double Verificacao_Leds_Vermelhos_1(char * mens_falha, int berco);
double Verificacao_Leds_Vermelhos_2(char * mens_falha, int berco);
double Corrente_Leds_Verdes(char * mens_falha, int berco);
double Verificacao_Leds_Verdes_1(char * mens_falha, int berco);
double Verificacao_Leds_Verdes_2(char * mens_falha, int berco);
double Corrente_Leds_Brancos(char * mens_falha, int berco);
double Verificacao_Leds_Brancos(char * mens_falha, int berco);

double Verificacao_Leds_All_ON(char * mens_falha, int berco);
double Verificacao_Leds_All_OFF(char * mens_falha, int berco);
double Verificacao_Cosmetico_TFT(char * mens_falha, int berco) ;
double Verificacao_Cosmetico_TACO(char * mens_falha, int berco);
double Verificacao_Cosmetico_VELO(char * mens_falha, int berco);
double Verificacao_LEDS_Cluster_ON(char * mens_falha, int berco); 
double Gages_0_Kmh_0_RPM(char * mens_falha, int berco);
double Gages_80_Kmh_3000_RPM(char * mens_falha, int berco);
double Gages_200_Kmh_8000_RPM(char * mens_falha, int berco); 
double Verificacao_Padrao_Display_SEG_1(char * mens_falha, int berco);
double Verificacao_Padrao_Display_SEG_2(char * mens_falha, int berco);
double Verificacao_Padrao_Display_MONO_1(char * mens_falha, int berco);
double Verificacao_Padrao_Display_MONO_2(char * mens_falha, int berco);
double Verificacao_Padrao_Display_MONO_3(char * mens_falha, int berco);
double Verificacao_Padrao_Display_MONO_4(char * mens_falha, int berco);
double Verificacao_Padrao_Display_COLOR(int padrao, char * mens_falha, int berco);
double Get_i_ref_EOL (char * mens_falha, int berco);



double Entrar_Diag_Mode_Visteon(char * mens_falha, int berco);
double Sair_Diag_Mode_costumer(char * mens_falha, int berco);
double Entrar_Diag_Mode_costumer(char * mens_falha, int berco);
double Sair_Diag_Mode_Visteon(char * mens_falha, int berco);
double Verificacao_Padrao_Display_COLOR_7(char * mens_falha, int berco);
double Ligar_Vibracao(char * mens_falha, int berco);
double Deligar_Vibracao(char * mens_falha, int berco);
double Abrir_Porta(char * mens_falha, int berco);
double Fechar_Porta(char * mens_falha, int berco);


double ConfiguraCyberSecurity(char * mens_rejeito, int berco);
double Grava_ECU_ID(char * mens_rejeito, int berco); 
double Ver_CyberSecurity_Ativado (char * mens_rejeito, int berco); 
double LerSoftwareVersion (char * mens_rejeito, int berco);     
double VerificaClientePN(char * mens_rejeito, int berco);
double VerificaMEC(char * mens_rejeito, int berco);
double VerificaParafuso(char * mens_rejeito);
double VerificaBasePartNumber(char * mens_rejeito, int berco);
double GravaMEC(char * mens_rejeito, int berco); 
double GravaMEC_Service(char * mens_rejeito, int berco);
double GravaClientePN(char * mens_rejeito, int berco);
double GravaTraceability(char * mens_rejeito, int berco);  
double GravaStatusByte(int condicao, char * mens_rejeito, int berco);
double LeStatusByte(char * mens_rejeito, int berco);
double VerificaSNCluster(char * mens_rejeito, int berco);  

int twoASCIItoByte(const unsigned char * in, unsigned char * out);


//----------------- funcoes em geral.c -----------------
char   *itostr( int number, unsigned int casas );
int    CVICALLBACK CINT ( double );
void   Data_e_Hora ( char *Data, char *Time, char *Mlabel );
int    LeConfiguracoes(void);
void   Mensagem(char *Mens1, char *Mens2, char *Mens3,char *Mens4, int cor, int berco);
short  CVI_PlaySound (char *fileName, short asynchronous);
void   CVI_StopCurrentSound (void);
int    MensFinal(char *Rodape , int Mdl_Rj , double Tempo_Total , double res , double Hi_Lim , double Low_Lim , char *Nome_Teste , int teste, int berco); 


//************************ inserido ********************************
int TravaLigaCluster1 (int acao);
int TravaLigaCluster2 (int acao);
void LigarProduto1(void);
void LigarProduto2(void);
void DesligarProduto1(void);
void DesligarProduto2(void);
int Set_Vdut(int tensao, int berco);
int DIC_SW_adj(int valor, int berco);
int Foto_Display_Diag(int modelo_display, int pattern); 
int Trava (int acao) ;
int LeIndiceArquivo (void);
int LeEscolheIndiceArquivo (void);

void Wait_buttons(int *rej,int *cont);
int Atualiza_Tab_da_rede(void);

int LeArquivos_LiveKey(int berco);
int LeDados_ASC_LiveKey(int index, int berco);
int LerIndexar_arq_index_LiveKey(int gravar_apenas, int berco);
int ReadIndexFile (void) ;
int ReadChoicedIndexFile (void);
int AtualizaDadosModelo(void);
double VerificaNumSerie_NVM(char * mens_falha, int berco);
double VerificaClientePN(char * mens_falha, int berco);
//void Complet_EndItem(int berco);

double	TensaoCAN (MODO_TENSAO_CAN modo_tensao_can, int berco);
int CarregaArq_CFG(int berco);
double Ver_CyberSecurity_Ativado (char * mens_rejeito, int berco);
double ConfiguraCyberSecurity(char * mens_rejeito, int berco);
int AtualizaStationID(void);
int Gerar_etiqueta(char *costumer_pn,
				   char *NSerie,  
				   char *vpps,
				   char *duns,
				   char *bar_code_prefixo);


void Sinc_test (int berco); 

double Grava_VPPS (char * mens_rejeito, int berco);
double Grava_DUNS (char * mens_rejeito, int berco);
