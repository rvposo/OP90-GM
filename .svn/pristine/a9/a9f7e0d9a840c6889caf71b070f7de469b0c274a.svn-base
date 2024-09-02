
#define MIN_TENSAO_DA			0
#define	MAX_TENSAO_DA			5
#define MIN_TENSAO_DA4461		-10
#define	MAX_TENSAO_DA4461		10
#define MIN_TENSAO_AD			-10
#define	MAX_TENSAO_AD			+10
//#define PI					3.1415926535
#define SAMPLE_RATE_4461		200000.0000000000
#define SAMPLE_RATE_PADRAO		24000.000//200000.0000000000
#define  FREQUENCIA_PADRAO		1000
//#define SAMP_PER_CHANN_IN		50176
#define SAMP_PER_CHANN_IN		25088
#define SAMP_PER_CHANN_OUT		10000
#define QTDADE_HARMONICAS		3

#define FREQ_MIN_MONITORAR  	10 //10Hz
#define FREQ_MAX_MONITORAR  	22000 //22KHz

#define CICLO_POR_BUFFER		3

#define TERMIN_CONF_DIFERENCIAL	0
#define TERMIN_CONF_SING_ENDED	1


#define INPUT_CANAL_AUDIO_RF	0
#define INPUT_CANAL_AUDIO_LF	1
#define INPUT_CANAL_AUDIO_RR	2
#define INPUT_CANAL_AUDIO_LR	3
#define CORRENTE_VIA_SHUNT		4
#define VOUT_DUMMY				5
#define DAQ_CAN_HIGH			6
#define DAQ_CAN_LOW				7


#ifndef NUMERO_DE_BERCOS
#define NUMERO_DE_BERCOS		2
#endif


char 	canal_AD_DAQ_6210_string [NUMERO_DE_BERCOS+1][256],
		canal_DA_DAQ_6210_string [NUMERO_DE_BERCOS+1][256],
		canal_dig_string_6210	 [NUMERO_DE_BERCOS+1][256],
		DAQ_6210_string	[NUMERO_DE_BERCOS+1][256],
		canal_AD_4461_0_string[256],
		canal_DA_4461_0_string[256],
	 	canal_AD_4461_1_string[256],
		canal_DA_4461_1_string[256],
		_4461_string[256];


TaskHandle	
	analog_INP_handler_6210	[NUMERO_DE_BERCOS+1], 
	analog_OUT_handler_6210	[NUMERO_DE_BERCOS+1],
	digital_port_handler_6210[NUMERO_DE_BERCOS+1],
	entrada_4461_handler_0	,
	entrada_4461_handler_1	,
	saida_4461_handler_0	,   
	saida_4461_handler_1	,
	saida_4461_handler_ambos;
	

int Init_NI_daq_6210 (int berco);//inicializa o módulo USB DAQ
int Stop_NI_daq_6210 (int berco);//encerra e libera handlers 
int Init_NI_4461 (void);
int Stop_NI_4461 (void);//encerra e libera handlers 
void GenSineWave(int numElements, double amplitude, double frequency, double *phase, double sineWave[]);
int Saida_4461(int canal, double frequencia, double amplitude);
int SetSampleClockRate(TaskHandle taskHandle, float64 desiredFreq, int32 sampsPerBuff, float64 cyclesPerBuff, float64 *desiredSampClkRate, float64 *sampsPerCycle, float64 *resultingSampClkRate, float64 *resultingFreq);
int Ler_4461(int sincronizar, int canal, double  *level, double *freq, double *distorcao);

double Vmedio_NIdaq_6210_1ch //le e retorna o valor da média de tensão DC presente em um canal de A/D
	(int canal, double lim_min, double lim_max, int terminal_conf, int berco);
int Vmedio_NIdaq_6210_8ch//le o valor da média de tensão DC presente nos 8 canais de A/D. Retorna o erro 
	(double lim_min, double lim_max, double *canal0, double *canal1, double *canal2,double *canal3,double *canal4,double *canal5,double *canal6,double *canal7, int berco); 

int FormaOnda_NIdaq_6210_1ch //le e retorna a forma de onda presente em um canal de A/D
(double lim_min, double lim_max,int canal, int leit_por_seg, int quant_leit, double *leituras, int berco);

int FormaOnda_daq6009_4ch //le a forma de onda presente nos 4 primeiros canais de A/D. Retorna o erro
(double lim_min, double lim_max,int leit_por_seg, int num_leit,
	 double *canal0, double *canal1, double *canal2,double *canal3, int berco); 

double Vmedio_RapidoNIdaq_6210_1ch (int canal, double lim_min, double lim_max, int terminal_conf, int berco);
int Atualiza_DA_DAQ6009 (double tensao_ch0, double tensao_ch1, int berco);
int EscDigital6009_Byte(int porta, uInt32 valor_escrever, int berco);
int EscDigital6009_Bit(int porta, int linha, uInt32 valor_escrever, int berco);
int LerDigital6009_Bit (int porta,int *bits_lidos, int berco);
double  freq_anterior, rate_anterior, amplitude_anterior;
int canal_anterior;
