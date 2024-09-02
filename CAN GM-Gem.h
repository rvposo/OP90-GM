#include "nican.h"              //To CAN NI   


//#ifndef NUMERO_DE_BERCOS
//	#define NUMERO_DE_BERCOS	4
//#endif

#define CAN_NI      			1

#define MESS_STANDARD			0
#define MESS_EXTENDED			1

#define CAN_TIMER_10			0.010 //seg
#define CAN_TIMER_12			0.012 //seg
#define CAN_TIMER_14			0.014 //seg
#define CAN_TIMER_20			0.020 //seg
#define CAN_TIMER_30			0.030 //seg 
#define CAN_TIMER_50			0.050 //seg
#define CAN_TIMER_100			0.100 //seg
#define CAN_TIMER_200			0.200 //seg
#define CAN_TIMER_500			0.500 //seg
#define CAN_TIMER_1000			1.000 //seg
#define CAN_TIMER_2000			2.000 //seg
#define CAN_TIMER_TST_PRES		1.000 //seg

#define GAUGE_VELOCIMETRO		0x00
#define GAUGE_TACOMETRO			0x01
#define GAUGES_ALL				0xFF

#define ID_CAN_DIAG_TX			0x14DA60F1 
#define ID_CAN_DIAG_RX			0x14DAF160 

#define GAUGE_TORQUE_NORMAL		0
#define GAUGE_TORQUE_HIGH		1
#define GAUGE_TORQUE_LOW		2

#define MOVE_TOWARD_STOP 		0
#define MOVE_ABSOLUTO			1

#define FATOR_VELO_CAN_LIVE		32   //0.015625
#define FATOR_VELO_CAN_DIAG		64   //0.015625
#define FATOR_RPM_CAN_LIVE		2    //
#define FATOR_RPM_CAN_DIAG		4    //

#define HSCAN_BAUD_RATE 		500
#define MSCAN_BAUD_RATE 		125

#define PWM_ILUM_DEFAULT		50   //porcentagem 

#define CAN_CANAL_1				0
#define CAN_CANAL_2				1   

#define CAN_FLOW_CONTROL		1
								
#define CHECK_CAN_ERR_OFF		0
#define CHECK_HSCAN_ERR			1

#define TAMANH_LIVEKEY_M4 		32
#define TAMANH_LIVEKEY_M5 		15
#define NUM_ELEM_LIVE_KEY 		64
#define MAX_TAM_ARQ_LOG_CAN		2000000 //max 2Mbytes

#define MAX_TAMAN_RESP_CLUSTER  126
#define MAX_TAMAN_ENVIO_CLUSTER 64
#define MAX_MENS_CAN_TX_DIAG	20
#define MAX_MENS_CAN_RX_DIAG	30

#define MIN_ADD_NVM				0xFF204000 //inicio da NVM
#define TAMANHO_NVM				0x300
#define MAX_ADD_NVM				(MIN_ADD_NVM + TAMANHO_NVM + 0xC00)//fim da NVM

#define VELO_ROTOR_OFFSET_ADD   0xFF204068
#define TACO_ROTOR_OFFSET_ADD   0xFF2040B2

#define	COUNTS_POR_GRAU			12
/*------------- Counts padr�o ---------*/
#define COUNTS_0_KM					48
#define COUNTS_10_KM				207
#define COUNTS_20_KM				365
#define COUNTS_40_KM				683
#define COUNTS_60_KM				980
#define COUNTS_80_KM				1290
#define COUNTS_100_KM				1601
#define COUNTS_120_KM				1911
#define COUNTS_140_KM				2195
#define COUNTS_180_KM				2808
#define COUNTS_200_KM				3000

#define COUNTS_0_RPM				48
#define COUNTS_250_RPM				116
#define COUNTS_500_RPM				233
#define COUNTS_1000_RPM				417
#define COUNTS_2000_RPM				786
#define COUNTS_3000_RPM				1155
#define COUNTS_4000_RPM				1524
#define COUNTS_5000_RPM				1893
#define COUNTS_6000_RPM				2262
#define COUNTS_7000_RPM				2631
#define COUNTS_8000_RPM				3000

#define MIN_RPM					0		//RPM
#define MAX_RPM					8000.0  //RPM
#define MAX_SPEED  				200		//KM por hora

#define	FRENTE					0
#define	TRAS					1

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FALHA_GENERICA_CAN			FALHA
#define FALHA_NAO_ATUALIZ_MENS_CAN	-2	 //Foi solicitado um envio de mensagem CAN por�m o SW n�o est� atualizando as mensagens CAN
#define FALHA_TIMEOUT_CAN			-3   //Timeout ao tentar ler retorno da interface CAN
#define FALHA_CAN_SUB_FUNC_N_SUPP	-4   //Dado ou parametro incorreto para o servi�o solicitado - Ver detalhes na Spec Part II(resp do cluster) 
#define FALHA_CAN_BUSY_REP_REQ		-5   //Dado ou parametro incorreto para o servi�o solicitado - Ver detalhes na Spec Part II(resp do cluster) 
#define FALHA_CAN_COND_N_CORRECT	-6   //Dado ou parametro incorreto para o servi�o solicitado - Ver detalhes na Spec Part II(resp do cluster) 
#define FALHA_CAN_INVALID_KEY		-7   //Dado ou parametro incorreto para o servi�o solicitado - Ver detalhes na Spec Part II(resp do cluster)
#define FALHA_CAN_WRITING_FALURE	-8   //Dado ou parametro incorreto para o servi�o solicitado - Ver detalhes na Spec Part II(resp do cluster)
#define FALHA_CAN_NUM_CANAIS		-9   //N�o encontrado interface CAN no sistema
#define FALHA_CAN_OPEN_CANAL		-10  //Erro ao tentar abrir comunica��o com a interface ou m�dulo CAN 
#define FALHA_CAN_CFG_CANAL			-11  //Erro ao tentar configurar a interface do canal CAN
#define FALHA_CAN_TIPO_INDEFINIDO	-12  //O tipo de interface CAN a ser utilizada na maquina � inv�lido
#define FALHA_CAN_NOT_IN_DIAG		-13  //O cluster n�o est� em modo diagn�stico, que � necess�rio para se rodar um servi�o
#define FALHA_CAN_SERVICO_INVAL		-14  //O tipo de servi�o solicitado no modo diagn�stico n�o � v�lido. Para servi�os v�lidos consultar Spec partII
#define FALHA_CAN_MODE_ENTRY_INVAL	-15  //Modo ou tipo de sess�o escolhida para entrar em diagn�stico � invalido - detalhes no servi�o $10
#define FALHA_CAN_NOT_POSIT_RESP    -16  //A reposta do CAN diag n�o � a resposta positiva esperada
#define FALHA_CAN_TAMANHO_RESP      -17  //O n�mero de bytes de reposta do CAN diag n�o � o valor esperado
#define FALHA_CAN_PARAM_ERROR       -18  //Dado ou parametro incorreto enviado para o servi�o solicitado - Ver detalhes na Spec Part II(parametro p/ fun��o)
#define FALHA_CAN_RESP_TOO_LONG		-19  //Dados capturados resposta do cluster muito longo - acima do limite
#define FALHA_LEITURA_CAN			-20  //Falha leitura CAN
#define FALHA_CAN_MODO_INCOMPATIVEL	-21  //Modo diagn�stico n�o � compativel com servi�o solicitado
#define FALHA_INDEX_LKEY_ASC_OVER	-22  //O valor do indexador para leitura do arquivo ASC do live key ultrapassa o m�ximo permitido para o tamanho do arquivo
#define FALHA_ARQUIVO_M4_M5			-23  //Indica que houve falha ao tentar acessar o arquivo de coleta de dados do Live Key - Dados de Master/Unlock M4 e M5
#define FALHA_ARQUIVO_INDEX_LIVEKEY	-24  //Indica que houve falha ao tentar acessar o arquivo de index do Live Key
#define INDEX_LIVEKEY_OUT_OF_RANGE  -25  //Valor do indexador no arquivo de controle de index ultrapassou o limite

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CANRXOFF					-222
#define CANBUSOFF					-333
#define CANBITWARNING				-444
#define CANBITDLLRXFULL				-555
#define CANNOTOPENDED				-666
#define CANBITTX					-777

#define VAL_TT_AIRBAG_OFF 			0x80
#define VAL_TT_AIRBAG_ON 			0xC0
#define VAL_TT_PARKBRAKE_OFF 		0x08
#define VAL_TT_PARKBRAKE_ON 		0x0C
#define VAL_TT_ABS_OFF 				0x00
#define VAL_TT_ABS_ON 				0x20
#define VAL_TT_BATTERY_OFF			0x00
#define VAL_TT_BATTERY_ON			0x10
#define VAL_TT_SE_PARKBREAK_OFF		0x00
#define VAL_TT_SE_PARKBREAK_ON		0x02
#define VAL_TT_COOLANT_TEMP_OFF		0x00
#define VAL_TT_COOLANT_TEMP_ON		0x01
#define VAL_TT_CRUISE_ENGAGED_OFF	0x00
#define VAL_TT_CRUISE_ENGAGED_ON	0x80
#define VAL_TT_CRUISEON_OFF			0x00
#define VAL_TT_CRUISEON_ON			0x40
#define VAL_TT_FRONT_FOG_OFF		0x00
#define VAL_TT_FRONT_FOG_ON			0x20
#define VAL_TT_FUEL_LV_LOW_OFF		0x00
#define VAL_TT_FUEL_LV_LOW_ON		0x10
#define VAL_TT_HIGH_BEAM_OFF		0x00
#define VAL_TT_HIGH_BEAM_ON			0x08
#define VAL_TT_LIGHTON_OFF			0x00
#define VAL_TT_LIGHTON_ON			0x04
#define VAL_TT_OIL_PRESSURE_OFF		0x00
#define VAL_TT_OIL_PRESSURE_ON		0x02
#define VAL_TT_REAR_FOG_OFF			0x00
#define VAL_TT_REAR_FOG_ON			0x01
#define VAL_TT_SEATBELT_OFF			0x00
#define VAL_TT_SEATBELT_ON			0x80
#define VAL_TT_SECURITY_OFF			0x00
#define VAL_TT_SECURITY_ON			0x40
#define VAL_TT_SERV_ENG_SOON_OFF	0x00
#define VAL_TT_SERV_ENG_SOON_ON		0x20
#define VAL_TT_TIRE_PRESS_LOW_OFF	0x00
#define VAL_TT_TIRE_PRESS_LOW_ON	0x10
#define VAL_TT_TURN_LEFT_OFF		0x00
#define VAL_TT_TURN_LEFT_ON			0x08
#define VAL_TT_TURN_RIGHT_OFF		0x00
#define VAL_TT_TURN_RIGHT_ON		0x04
#define VAL_TT_ESCOFF_OFF			0x00
#define VAL_TT_ESCOFF_ON			0x02
#define VAL_TT_ESC_SERVICE_OFF		0x00
#define VAL_TT_ESC_SERVICE_ON		0x01
#define VAL_TT_PARKING_BRAKE_OFF	0xC0
#define VAL_TT_PARKING_BRAKE_ON		0x80
#define VAL_TT_PRESS_CLUTCH_OFF		0x00
#define VAL_TT_PRESS_CLUTCH_ON		0x20
#define VAL_TT_PASSEN_SEATBELT_OFF	0x00
#define VAL_TT_PASSEN_SEATBELT_ON	0x10
#define VAL_TT_TRACTION_CONTRL_OFF	0x00
#define VAL_TT_TRACTION_CONTRL_ON	0x08
#define VAL_TT_SERV_VEH_SOON_OFF	0x00
#define VAL_TT_SERV_VEH_SOON_ON		0x04
#define VAL_TT_EPS_OFF				0x00
#define VAL_TT_EPS_ON				0x02
#define VAL_TT_PARK_ASSIST_OFF		0x00
#define VAL_TT_PARK_ASSIST_ON		0x40
#define VAL_TT_GLOWPLUG_OFF			0x00
#define VAL_TT_GLOWPLUG_ON			0x20
#define VAL_TT_KMH_OFF				0x00
#define VAL_TT_KMH_ON				0x80
#define VAL_TT_MPH_OFF				0x00
#define VAL_TT_MPH_ON				0x01
#define VAL_TT_PEDESTRIAN_OFF		0x00
#define VAL_TT_PEDESTRIAN_ON		0x10
#define VAL_TT_LANE_KEEP_GREEN_OFF	0x00
//#define VAL_TT_LANE_KEEP_GREEN_ON	0x08
#define VAL_TT_LANE_KEEP_GREEN_ON	0x02
#define VAL_TT_LANE_KEEP_AMBER_OFF	0x00
#define VAL_TT_LANE_KEEP_AMBER_ON	0x04
#define VAL_TT_TRACK_LEAD_GREEN_OFF	0x00
#define VAL_TT_TRACK_LEAD_GREEN_ON  0x02
//#define VAL_TT_TRACK_LEAD_GREEN_ON	0x08
#define VAL_TT_TRACK_LEAD_AMBER_OFF	0x00
#define VAL_TT_TRACK_LEAD_AMBER_ON	0x01
#define VAL_TT_AUTOHOLD_WHITE_OFF	0x00
#define VAL_TT_AUTOHOLD_WHITE_ON	0x80
#define VAL_TT_AUTOHOLD_GREEN_OFF	0x00
#define VAL_TT_AUTOHOLD_GREEN_ON	0x40

#define VPPS_LENGHT                 14
#define DUNS_LENGHT                 9


/*----------------------------------------------------------------------------
 CAN Message Structure
----------------------------------------------------------------------------*/

typedef struct	{
	DWORD	dwID;						// CAN Message ID
	UCHAR	cFlags;						// Message Flags
	UCHAR	cLength;					// Message Length (0 - 8)
	UCHAR	cData[8];					// Message Data
	DWORD	dwTimeStamp;				// Time message was received from CAN Bus
	NCTYPE_ABS_TIME timestamp;
} EX_CAN_MSG;

////////////////////////////////////////
struct{
	char 
		nome[50];
	int
		canal;
}
can_defin[10];

////////////////////////////////////////
NCTYPE_ATTRID	
	AttrIdList[8];
	
NCTYPE_UINT32	
	AttrValueList[8],
	ActualDataSize;

NCTYPE_STATUS 
	status_can;  
	
NCTYPE_OBJH       //NI-CAN handles 
	TXRXHandle[NUMERO_DE_BERCOS+1];

/***************** Enumeracao para tabelas de calibra��o dos gauges ********************/
typedef enum
{
	VELO_CAN_MIN	 	, 
	VELO_CAN_MAX	 	, 
	VELO_CAN_POINT_0 	, 
	VELO_COUNTS_POINT_0 ,
	VELO_CAN_POINT_1 	, 
	VELO_COUNTS_POINT_1 ,
	VELO_CAN_POINT_2 	, 
	VELO_COUNTS_POINT_2 ,
	VELO_CAN_POINT_3 	, 
	VELO_COUNTS_POINT_3 ,
	VELO_CAN_POINT_4 	, 
	VELO_COUNTS_POINT_4 ,
	VELO_CAN_POINT_5 	, 
	VELO_COUNTS_POINT_5 ,
	VELO_CAN_POINT_6 	, 
	VELO_COUNTS_POINT_6 ,
	VELO_CAN_POINT_7 	, 
	VELO_COUNTS_POINT_7 ,
	VELO_ROTOR_OFFSET	,
	/////////////////////
	TACO_CAN_MIN	 	, 
	TACO_CAN_MAX	 	, 
	TACO_CAN_POINT_0 	, 
	TACO_COUNTS_POINT_0 ,
	TACO_CAN_POINT_1 	, 
	TACO_COUNTS_POINT_1 ,
	TACO_CAN_POINT_2 	, 
	TACO_COUNTS_POINT_2 ,
	TACO_CAN_POINT_3 	, 
	TACO_COUNTS_POINT_3 ,
	TACO_CAN_POINT_4 	, 
	TACO_COUNTS_POINT_4 ,
	TACO_CAN_POINT_5 	, 
	TACO_COUNTS_POINT_5 ,
	TACO_CAN_POINT_6 	, 
	TACO_COUNTS_POINT_6 ,
	TACO_CAN_POINT_7 	, 
	TACO_COUNTS_POINT_7 ,
	TACO_ROTOR_OFFSET	,
	
} ITEM_CALIB_TABLE;

/********** Enumeracao para pontos de calibra��o/verifica��o chaplets dos gauges ********************/
typedef enum
{
	//velocimetro
	CHAP_PONTO_0_KPH , 
	CHAP_PONTO_1_KPH , 
	CHAP_PONTO_2_KPH ,
	CHAP_PONTO_3_KPH ,
	CHAP_PONTO_4_KPH , //40 Km/h
	
	//tacometro
	CHAP_PONTO_0_RPM,
	CHAP_PONTO_1_RPM ,
	CHAP_PONTO_2_RPM ,
	CHAP_PONTO_3_RPM ,
} CHAPLET;

/***************** Enumeracao do modo diagnostico ********************/
typedef enum 
{ 
	NOT_DIAG			, 
	ENTRAR_DIAG_VISTEON	,
	ENTRAR_DIAG_CUSTOMER,
	MANTER_DIAG			,
	EM_DIAG_VISTEON		,
	EM_DIAG_CUSTOMER	,
	SAIR_DIAG
} MODO_DIAGNOSTICO;
MODO_DIAGNOSTICO 
	modo_diagnostico[NUMERO_DE_BERCOS+1],
	qual_diag_atual	[NUMERO_DE_BERCOS+1];

//////////////////////////////////////////////////////////////////
/*
typedef enum
{
	INPUT_ALL_OFF		,
	INPUT_OIL_VALUE		,
	INPUT_EXT_TEMP		,
	RUN_CRANK	  		,
	DIC_SWITCH	  		,
	DIC_ANALOG	  		,
	PASSIVE_START 		,
	FCA_OUT		  		,
	FCA_DN_OUT	  		,
	PASSIV_START_RUN_OUT,
	PASSIV_START_IS1_OUT,
	PASSIV_START_ACC_OUT,
	PASSIV_START_IS2_OUT,
	BATTERY_VOLTAGE		,
	PCB_TEMPERATURE_NTC ,
	MONITOR_5V		  	,
	LOW_FUEL_AD			,
	TIRE_PRESS_AD		,
	ABS_AD				,
	ESC_AD				,
	PARKING_AD			,
	BRAKE_AD			,
	AIRBAG_AD			
	
}INPUT_CLUSTER;
INPUT_CLUSTER input_cluster;
*/

/////////////// cluster inputs ///////////////////////////////////////////
typedef enum
{
	INPUT_ALL_OFF		,
	INPUT_OIL_VALUE		,
	INPUT_EXT_TEMP		,
	RUN_CRANK	  		,
	DIC_SWITCH	  		,
	DIC_ANALOG	  		,
	PASSIVE_START 		,

	DIC_ANALOG_604R		,
	DIC_ANALOG_1624R	,
	DIC_ANALOG_3534R	,
	PASSIVE_START_1300	,
	PASSIVE_START_4870	,
	FCA_OUT		  		,
	FCA_DN_OUT	  		,
	PASSIV_START_RUN_OUT,
	PASSIV_START_IS1_OUT,
	PASSIV_START_ACC_OUT,
	PASSIV_START_IS2_OUT,
	BATTERY_VOLTAGE		,
	PCB_TEMPERATURE_NTC ,
	MONITOR_5V		  	,
	LOW_FUEL_AD			,
	TIRE_PRESS_AD		,
	ABS_AD				,
	ESC_AD				,
	PARKING_AD			,
	BRAKE_AD			,
	AIRBAG_AD			
	
}INPUT_CLUSTER;
INPUT_CLUSTER input_cluster;

/////////////// cluster outputs ///////////////////////////////////////////
typedef struct 
{
	unsigned char
	out_fca,
	out_fca_dn,
	out_passiv_start_run,
	out_passiv_start_acc;
	
}DIAG_OUTPUT;
DIAG_OUTPUT diag_output[NUMERO_DE_BERCOS+1];
//////////////////////////////////////////////////////////////
typedef enum
{
	REGISTRO_ALL_OFF	,
	CRYSTAL_VERIF		,
	MEC_STATUS			,
	PN_STATUS			,
	BASE_STATUS			,
	MTC_STATUS			,
	SW_STATUS			,
	CLUSTER_INFO		,
}REGISTRO_CLUSTER;
//REGISTRO_CLUSTER registro_cluster;

/***************** Enumeracao dos servicos ********************/
typedef enum
{   	
	DIAG_SERVICE_OFF			,
	TELLT_DISP_DIAG_CUSTOMER	,
	TELLTALE_ON_OFF_DIAG		,
	LIMPAR_DTC					,
	FLOW_CONTROL				,
	ILLUM_GAUGE_ADJUST_DIAG		,
	ILLUM_LCD_ADJUST_DIAG		,
	ILLUM_POINTER_ADJUST_DIAG	,
	ILLUM_TELLTALE_ADJUST_DIAG	,
	LCD_SEGM_ALL_OFF_DIAG		,
	LCD_SEGM_ALL_ON_DIAG		,
	LCD_SEGM_PATT_3				,
	LCD_SEGM_PATT_4				,
	TFT_PATTERN_DIAG			,
	LER_RUN_CRANK_DIAG			,
	LER_DIC_SWITCH_DIAG			,
	LER_DIC_ANALOG_DIAG			,
	LER_PASSIV_START_DIAG		,
	LER_FCA_OUT_DIAG 			,
	ESC_FCA_OUT_DIAG 			,
	LER_FCA_DN_OUT_DIAG 		,
	ESC_FCA_DN_OUT_DIAG 		,
	ESC_PASS_START_RUN_OUT_DIAG	,
	ESC_PASS_START_ACC_OUT_DIAG	,
	LER_PASS_START_RUN_OUT_DIAG	,
	LER_PASS_START_IS1_OUT_DIAG	,
	LER_PASS_START_ACC_OUT_DIAG	,
	LER_PASS_START_IS2_OUT_DIAG	,
	LER_BATTERY_VOLTAGE_DIAG   	,
	LER_PCB_TEMPERATURE_NTC   	,
	LER_MONITOR_5V				,
	LER_LOW_FUEL_AD				,
	LER_TIRE_PRESS_AD			,
	LER_ESC_AD					,
	LER_ABS_AD					,
	LER_PARKING_AD				,
	LER_BRAKE_AD				,
	LER_AIRBAG_AD				,
	ENTRAR_SLEEP_MODE			,
	LER_CRYSTAL_VERIF			,
	PROGRAMAR_MEC				,
	PROGRAMAR_MEC_SERVICE       ,
	LER_MEC_STATUS				,
	PROGRAMAR_PN				,
	LER_PN_STATUS				,
	LER_BASE_STATUS				,
	LER_MTC_STATUS				,
	PROGRAMAR_MTC				,
	LER_SW_STATUS				,
	ENTRAR_PPLACEM_MODE			,
	STATUS_PPLACEM_MODE			,
	TACOMETRO_CUSTOMER			,
	VELOCIMETRO_CUSTOMER		,
	GAUGE_EOL_VISTEON			,
	ENABLE_GAUGE				,
	ECU_RESET					,
	CORRIGE_CHECKSUM			,
	LER_CLUSTER_INFO			, 
	LER_BYTES_NVM				,
	LER_BYTES_NVM_RES			,
	ESC_BYTES_NVM				,
	WATCH_DOG_CONTINUO			,
	WATCH_DOG_STOP				,
	WRITE_GENERAL_KEY2			,
	WRITE_GENERAL_KEY3			,
	WRITE_GENERAL_KEY4			,
	WRITE_GENERAL_KEY5			,
	WRITE_GENERAL_KEY6			,
	WRITE_GENERAL_KEY7			,
	WRITE_GENERAL_KEY8			,
	WRITE_GENERAL_KEY9			,
	WRITE_GENERAL_KEY10			,
	WRITE_GENERAL_KEY11			,
	WRITE_GENERAL_KEY12			,
	WRITE_GENERAL_KEY13			,
	WRITE_GENERAL_KEY14			,
	WRITE_GENERAL_KEY15			,
	WRITE_GENERAL_KEY16			,
	WRITE_GENERAL_KEY17			,
	WRITE_GENERAL_KEY18			,
	WRITE_GENERAL_KEY19			,
	WRITE_GENERAL_KEY20			,
	WRITE_MASTER_KEY			,
	WRITE_UNLOCK_KEY			,
	WRITE_ECU_ID				,
	LER_ECU_ID					,
	LER_STATUS_LIVE_KEY         ,
	
	LER_VPPS 			,
    ESC_VPPS            ,
    LER_DUNS 			,
    ESC_DUNS

								
} SERVICO_DIAG ;

SERVICO_DIAG servico_diagnostico[NUMERO_DE_BERCOS+1];


/***************** Enumeracao dos Modelos de Display ********************/
typedef enum
{   	
	DISPLAY_MODEL_INDEF	,
	DISPLAY_SEGMENTADO	,
	DISPLAY_TFT_MONO	,
	DISPLAY_TFT_COLOR	,
} MODELO_DISPLAY;
MODELO_DISPLAY  modelo_display[NUMERO_DE_BERCOS+1];

/***************** Enumeracao dos padr�es LCD ********************/
typedef enum
{   	
	PATTERN_LCD_ALL_OFF	,
	PATTERN_LCD_ALL_ON	,
	PATTERN_LCD_3		,
	PATTERN_LCD_4		,
	PATTERN_LCD_RED		,
	PATTERN_LCD_GREEN	,
	PATTERN_LCD_BLUE	,
	PATTERN_LCD_GRAY_LEVEL,
	PATTERN_LCD_COLOUR_BARS,
	PATTERN_LCD_EOL		,
} PADRAO_DISPLAY;	
/***************** Enumeracao dos LEDS ********************/
typedef enum
{   	
	AIRBAG				,
	BATTERY				, 
	PARK_BRAKE			, 
	SERVICE_ELETRIC_PARK_BRAKE,
	COOLANT_TEMP		,  
	CRUISE_ENGAGED		, 
	CRUISE_ON			, 
	FRONT_FOG			, 
	FUEL_LEVEL_LOW		,   
	HI_BEAM				,
	LIGHTS_ON			, 
	OIL_PRESSURE		, 
	REAR_FOG			,
	DRIVER_SEAT_BELT	,
	SECURITY			,
	SERVICE_ENGINE_SOON	,   
	TIRE_PRESSURE_LOW	,
	TURN_LEFT			,
	TURN_RIGHT			,
	ESC_OFF				,
	ESC_SERVICE			,
	PARKING_BRAKE		,
	PRESS_CLUTCH_START	,
	PASSENGER_SEAT_BELT	,
	TRACTION_CONTROL_OFF,
	SERVIVE_VEHICLE_SOON,
	EPS					,	
	ABS					,
	DOOR_OPEN			,
	FLUID_BRAKE			,
	SEAT_BELT			,
	PARK_ASSIST			,
	GLOW_PLUG			,
	KMH					,
	MPH					,
	PEDESTRIAN			,
	LANE_KEEPER_GREEN	,
	LANE_KEEPER_AMBER	,
	TRACKING_LEAD_GREEN	,
	TRACKING_LEAD_AMBER	,
	AUTOHOLD_WHITE		,
	AUTOHOLD_GREEN		,
	DISPLAY_PATTERN		,
	POINTER_BACKLIGHT	,
	GAUGE_BACKLIGHT		,
	LCD_BACKLIGHT		,
	TELLTALES_ILL		,
	ALL_TELLTALES_RED	,
	ALL_TELLTALES_GREEN	,
	ALL_TELLTALES_AMBER	,
	ALL_TELLTALES_WHITE	,
	ALL_TELLTALES_BLUE	,
	/////////////////////

} TELLTALES_GM_GEM ;


typedef struct 
{
	unsigned char  
	tt_airbag       ,	   
	tt_park_brake	, 
	tt_abs			,
	tt_battery		,
	tt_se_parkbrake	,
	tt_coolant_temp	,
	tt_cruise_engaged,
	tt_cruise_on	,
	tt_front_fog	,
	tt_fuel_level_low,
	tt_high_beam	,
	tt_light_on		,
	tt_oil_pressure	,
	tt_rear_fog		,
	tt_seat_belt	,
	tt_security		,
	tt_serv_eng_soon,
	tt_tire_press_low,
	tt_turn_left	,
	tt_turn_right	,
	tt_esc_off		,
	tt_esc_service	,
	tt_parking_brake,
	tt_press_clutch	,
	tt_passeng_seatbelt	,
	tt_traction_cntrl_off,
	tt_service_vehi_soon,
	tt_eps			,
	tt_park_assist	,
	tt_glow_plug	,
	tt_kmh			,
	tt_mph			,
	tt_pedestrian	,
	tt_lane_kepper_green,
	tt_lane_kepper_amber,
	tt_track_lead_green,
	tt_track_lead_amber,
	tt_auto_hold_white,
	tt_auto_hold_green; 
}DIAG_TELLTALES;
DIAG_TELLTALES diag_telltales[NUMERO_DE_BERCOS+1];

typedef struct 
{
	unsigned int
		velo_can_min	,
		velo_can_max	,
		velo_can_pt_0	,
		velo_counts_pt_0,
		velo_can_pt_1	,
		velo_counts_pt_1,
		velo_can_pt_2	,
		velo_counts_pt_2,
		velo_can_pt_3	,
		velo_counts_pt_3,
		velo_can_pt_4	,
		velo_counts_pt_4,
		velo_can_pt_5	,
		velo_counts_pt_5,
		velo_can_pt_6	,
		velo_counts_pt_6,
		velo_can_pt_7	,
		velo_counts_pt_7,
		////////////////
		taco_can_min	,
		taco_can_max	,
		taco_can_pt_0	,
		taco_counts_pt_0,
		taco_can_pt_1	,
		taco_counts_pt_1,
		taco_can_pt_2	,
		taco_counts_pt_2,
		taco_can_pt_3	,
		taco_counts_pt_3,
		taco_can_pt_4	,
		taco_counts_pt_4,
		taco_can_pt_5	,
		taco_counts_pt_5,
		taco_can_pt_6	,
		taco_counts_pt_6,
		taco_can_pt_7	,
		taco_counts_pt_7;
	
}DADOS_TAB_CAL_CLUSTER;
DADOS_TAB_CAL_CLUSTER dados_tab_cal[NUMERO_DE_BERCOS+1];

typedef struct 
{
	unsigned int
		velo_rotor_value,
		taco_rotor_value,
		velo_flip_value,
		taco_flip_value;
	
}DADOS_ROTOR_OFFSET;
DADOS_ROTOR_OFFSET dados_rotor_offset[NUMERO_DE_BERCOS+1];

/************************* Estrutura p/ LiveKey ***********************************************/
typedef struct 
{
	char		
		ecu_id[50],
		master_key_1[50],
		master_key_2[50],
		master_key_3[50],
		master_key_4[50],
		
		unlock_key_1[50],
		unlock_key_2[50],
		unlock_key_3[50],
		unlock_key_4[50],
		
		master_M4_1 [50],
		master_M4_2 [50],
		master_M5   [50],
		
		unlock_M4_1 [50],
		unlock_M4_2 [50],
		unlock_M5   [50],
		ecu_id_lido [50];
}
DADOS_LIVE_KEY ;
DADOS_LIVE_KEY 
	dados_live_key[NUMERO_DE_BERCOS+1];

/************************* Mensagens CAN - EX_CAN_MSG ******************************************/
EX_CAN_MSG 
	SysBkUpPwrMd			[NUMERO_DE_BERCOS+1], //enviada pelo cluster
	////////////////////////////////////////////
	SysPwrMd				[NUMERO_DE_BERCOS+1],
	VehSpdAugDrun			[NUMERO_DE_BERCOS+1],
	VehSpdAugNDrun			[NUMERO_DE_BERCOS+1],
	EngSpd					[NUMERO_DE_BERCOS+1],
	Exterior_Lighting_HS	[NUMERO_DE_BERCOS+1],
	PPEI_Engine_General_Status_1_0CB_M2[NUMERO_DE_BERCOS+1],
	Airbag_Indications_19A_M[NUMERO_DE_BERCOS+1],
	Airbag_Indications_198_M[NUMERO_DE_BERCOS+1],
	//////////////////////////////////////////////////////////////		 
	Tester_present			[NUMERO_DE_BERCOS+1],
	Diagnostico_TX			[MAX_MENS_CAN_TX_DIAG][NUMERO_DE_BERCOS+1],
	Resp_diagnostico_RX		[MAX_MENS_CAN_RX_DIAG][NUMERO_DE_BERCOS+1];

int 
	atual_index_live_key[NUMERO_DE_BERCOS+1],
	manual_index_live_key,
	maximo_index_live_key,
	atual_counts_velo[NUMERO_DE_BERCOS+1],
	atual_counts_taco[NUMERO_DE_BERCOS+1],
	CAN_error_n		,
	tipo_de_CAN		,
 	extend_frame_format[NUMERO_DE_BERCOS+1],
	status_comunic_CAN[NUMERO_DE_BERCOS+1],
    monitorar_comm_CAN,
	tipo_monitoramento_CAN,
	filtrar_mens_n_diag_CAN,
	can_baud_rate	,
	tipo_de_CAN		,  //CAN_TRIX or CAN_NI
	atualizar_mens_can[NUMERO_DE_BERCOS+1],
	check_can_err	, 

	max_rpm			,
	graus_offset_taco,
	counts_0_rpm	,
	counts_1000_rpm	,
	counts_2000_rpm	,
	counts_3000_rpm	,
	counts_4000_rpm	,
	counts_5000_rpm	,
	counts_6000_rpm	,
	counts_7000_rpm	,
	counts_8000_rpm	,
	
	veloc_max		,
	graus_offset_speed,
	counts_0_km		,
	counts_20_km	,
	counts_40_km	,
	counts_60_km	,
	counts_80_km	,
	counts_100_km	,
	counts_120_km	,
	counts_140_km	,
	counts_160_km	,
	counts_180_km	,
	counts_200_km	,
	modelo_index	;

unsigned long 
	add_eol_type_oper	[NUMERO_DE_BERCOS+1],
	add_eol_status_oper	[NUMERO_DE_BERCOS+1],
	////////////////////
	add_table_speed		[NUMERO_DE_BERCOS+1],
	add_CAN_min_speed	[NUMERO_DE_BERCOS+1],
	add_CAN_max_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_0_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_0_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_1_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_1_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_2_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_2_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_3_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_3_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_4_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_4_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_5_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_5_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_6_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_6_speed	[NUMERO_DE_BERCOS+1],
	add_inp_pt_7_speed	[NUMERO_DE_BERCOS+1],
	add_out_pt_7_speed	[NUMERO_DE_BERCOS+1],
	add_rot_offset_speed[NUMERO_DE_BERCOS+1], 
	///////////////////
	add_table_taco		[NUMERO_DE_BERCOS+1],
	add_CAN_min_taco   	[NUMERO_DE_BERCOS+1],  
	add_CAN_max_taco   	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_0_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_0_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_1_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_1_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_2_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_2_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_3_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_3_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_4_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_4_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_5_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_5_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_6_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_6_taco  	[NUMERO_DE_BERCOS+1],  
	add_inp_pt_7_taco  	[NUMERO_DE_BERCOS+1],  
	add_out_pt_7_taco  	[NUMERO_DE_BERCOS+1],  
	add_rot_offset_taco [NUMERO_DE_BERCOS+1], 
	
	add_teste_num		[NUMERO_DE_BERCOS+1],  
	add_num_serie		[NUMERO_DE_BERCOS+1],
	tamanho_nvm			[NUMERO_DE_BERCOS+1];   

char
	CAN_error_str [700][NUMERO_DE_BERCOS+1], //error info
	*ponteiro_logs_can;

double 
	tempo_inicial_log_CAN,
	timer_test_pres[NUMERO_DE_BERCOS+1];
	
unsigned short 
	graus_por_rpm	,
	graus_por_km	,
	correcao_0_km	,			
	correcao_20_km	,			
	correcao_40_km	,			
	correcao_60_km	,			
	correcao_80_km	,			
	correcao_100_km	,		
	correcao_120_km	,			
	correcao_140_km	,			
	correcao_160_km	,			
	correcao_180_km	,			
	correcao_200_km	;
unsigned char
	bytes_resp_CAN_diag	[MAX_TAMAN_RESP_CLUSTER] [NUMERO_DE_BERCOS+1];
int
	bytes_envio_CAN_diag[MAX_TAMAN_ENVIO_CLUSTER][NUMERO_DE_BERCOS+1];

//int
//	envio_can[MAX_TAMAN_ENVIO_CLUSTER][NUMERO_DE_BERCOS+1];
struct
{
int
	dados_can[MAX_TAMAN_ENVIO_CLUSTER];
}envio_can[NUMERO_DE_BERCOS+1];

int SetaMensTaco(int, int berco);
int SetaMensVelo(int, int berco);
int InicializaCAN(NCTYPE_STRING ObjName,DWORD dwChannel, int berco);
int set_cam_bit(EX_CAN_MSG *b_m,int can_id,int can_bit,int acao);
int Erros_CAN();
int RodaServicoDiagnostico(int berco);
int EntraModoEOL_GM(int berco);
void EnviaTestPresent(int berco);
int Ilumination_PWM_DIAG(TELLTALES_GM_GEM lamp, int valor, int berco);
int Acende_lampada_cluster_DIAG(TELLTALES_GM_GEM lamp, int acao, int berco);
int VerifCondicaoServicoDiag (MODO_DIAGNOSTICO modo_diag_correto, int berco, int delay_uir);
void Get_timestamp_CAN(int tx, char *tms) ;
int EnterSleepMode_Diag(int berco);
void Indica_comm_CAN_OK(int berco);
int Indica_comm_CAN_Not_OK(void) ;
int AtualizaMensagensCAN(int berco);
int Ler_DI_status(INPUT_CLUSTER input, int *valor, int berco);
int Ler_Analog_status(INPUT_CLUSTER input, int *valor, int berco);
int Esc_Digital_Output(INPUT_CLUSTER input, int valor, int berco);
int HS_InicializaCAN(void);
int EnviarEsperarRespDiag (int test_present, int berco);
int Display_pattern_CAN (PADRAO_DISPLAY pattern, int beco);
int Programar_MEC_Diag(int berco);
int Programar_MEC_Servico_Diag(int berco);
int EntraDiagCustomer_GM(int berco);
int Ler_Registro_status(REGISTRO_CLUSTER registro, int *valor, int berco);
int Programar_PN_Diag(unsigned long customer_pn, int berco);
int Programar_MTC_Diag(int berco);
void Reseta_dados_resp_cluster_CAN(int berco) ;
int EnterPointerPlacMode_Diag(int berco);
int SetTacometroCustomer_DIAG(int rpm, int berco);
int SetVelocimetroCustomer_DIAG(int kmh, int berco);
int SetGauge_eol_visteon_DIAG(int counts, int gauge, int move_absoluto, int torque, unsigned char speed, int esperar, int berco);
int Enable_gauge_Diag(int valor, int berco);
int ECU_reset_Diag(int berco);
int Whatch_dog_test_Diag(int berco);
int CorrigirChecksum_Diag(int berco);
void ReportClusterInfo(int berco);
int Ler_BytesNVM_Diag(unsigned long add_init, unsigned char quantos_bytes, int delay, int berco) ;
int Gravar_BytesNVM_Diag(unsigned long add_init, unsigned char quantos_bytes, int berco, int table_data);
void ResetaBytesEnvio_CAN(int berco) ;
void ResetaBytesResposta_CAN(int berco);

int Recebe_can_RX_NI(int index, int berco); 
void Reseta_MensDiag(int berco);
int Ler_Table_DataWord(ITEM_CALIB_TABLE item, unsigned *item_val, int delay_command,int berco);
int Ler_dados_tabelas_calibracao(int delay_command, int berco) ;
char *Word_to_string(unsigned int valor);
unsigned long Ret_endereco_item_cal_table(ITEM_CALIB_TABLE item, int berco);
int Esc_Table_DataWord(ITEM_CALIB_TABLE item, unsigned int item_val ,int berco);
void ResetManual_Controls(int ecu_reset, int berco);
int Ler_toda_NVM(int berco);
void MostraGroupLeds_Status(TELLTALES_GM_GEM telltales, int valor);
int LoadBytes_LiveKey(SERVICO_DIAG servico_diag, int berco) ;
int Gravar_General_Key(SERVICO_DIAG servico_diag, int berco);
int Gravar_Master_Key(int berco);
int Gravar_Unlock_Key(int berco);
int LedsDisplay_Customer_DIAG(int acao, int berco);
int LeDados_ASC_LiveKey(int index, int berco);
int LerStatus_LiveKey(int berco);
int Gravar_ECU_ID(int berco);
int Ler_ECU_ID(int berco);
int	LerMens_SysBkUpPwrMd(int berco, int *configurado);
int CarregaResp_LiveKey(int berco);
int GravaSequencia_general_keys(int berco);
int Modo_manual_general_key(SERVICO_DIAG item);
int ReturnPointersStop_Diag(int berco, int apenas_10_graus);
int Flip_Detect_Diag(int qual_gauge, int zerar_contador, int flip_detected, int berco);
void Set_DIC(INPUT_CLUSTER qual_dic, int acao, int berco);
void Set_PassiveStart(INPUT_CLUSTER qual_pass_st, int acao, int berco);
void Inicializa_LedsSaidas(int berco);


////////////////////////////////////////////////////
//18/06/2019
int F_read_VPPS(int berco, char *VPPS);
int F_write_VPPS(int berco, char *VPPS);


int F_read_DUNS(int berco, char *DUNS);
int F_write_DUNS(int berco, char *DUNS);
