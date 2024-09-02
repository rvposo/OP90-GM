#include <windows.h> 
#include <rs232.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>

#include "cvixml.h"
#include "Main OP090 GM-GEM.h"  //<--- 
#include "CAN GM-Gem.h" 
#include "Diag GM-Gem.h"  
#include "Auto OP090 GM-GEM.h"    


/************************************* SetaMensTaco() ****************************************************************************/
//RPM 
int SetaMensTaco(int rpm, int berco)
{
unsigned int 
	msb		= 0,
	lsb		= 0;

	rpm = rpm * FATOR_RPM_CAN_LIVE;//can_fator_taco live mode;
	
	lsb 	= rpm&0x00FF;
	msb 	= rpm&0xFF00;
	msb 	= msb>>8;
	
	EngSpd[berco].cData [6] = lsb;
	EngSpd[berco].cData [5] = msb;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[4] = 0x80;

return 0;
}

/************************************* SetaMensVelo() ****************************************************************************/
//Speed
int SetaMensVelo(int km, int berco)
{
unsigned char 
			lsb=0;
unsigned int 
			msb=0;


	km = km * FATOR_VELO_CAN_LIVE;
	lsb = km&0x00FF;
	msb = km&0xFF00;
	msb = msb>>8;

	VehSpdAugDrun[berco].cData [5] = lsb;
	VehSpdAugDrun[berco].cData [4] = msb;
	
return 0;
}

/************************************* InicializaMensagens() ****************************************************************************/
//Start CAN messages
void InicializaMensagens(int berco)
{
int i;

	///////////////////////////////////////////////////
	SysBkUpPwrMd[berco].dwID 	 = 0x123; //recep��o(enviada pelo cluster
	SysBkUpPwrMd[berco].cLength  = 6;
	SysBkUpPwrMd[berco].cData[7] = 0x00;
	SysBkUpPwrMd[berco].cData[6] = 0x00; 
	SysBkUpPwrMd[berco].cData[5] = 0x00; 
	SysBkUpPwrMd[berco].cData[4] = 0x00; 
	SysBkUpPwrMd[berco].cData[3] = 0x00; 
	SysBkUpPwrMd[berco].cData[2] = 0x00; 
	SysBkUpPwrMd[berco].cData[1] = 0x00; 
	SysBkUpPwrMd[berco].cData[0] = 0x00; 
	///////////////////////////////////////////////////
	SysPwrMd[berco].dwID 	 = 0x207;  //0x1F6
	SysPwrMd[berco].cLength  = 8;
	SysPwrMd[berco].cData[7] = 0x00;
	SysPwrMd[berco].cData[6] = 0x00; 
	SysPwrMd[berco].cData[5] = 0x00; 
	SysPwrMd[berco].cData[4] = 0x00; 
	SysPwrMd[berco].cData[3] = 0x8A; 
	SysPwrMd[berco].cData[2] = 0x80; 
	SysPwrMd[berco].cData[1] = 0x00; 
	SysPwrMd[berco].cData[0] = 0x00; 
	
	VehSpdAugDrun[berco].dwID  	  = 0x3FF; //0x3EB
	VehSpdAugDrun[berco].cLength  = 7;
	VehSpdAugDrun[berco].cData[7] = 0x00;
	VehSpdAugDrun[berco].cData[6] = 0x00;
	VehSpdAugDrun[berco].cData[5] = 0x00;
	VehSpdAugDrun[berco].cData[4] = 0x00;
	VehSpdAugDrun[berco].cData[3] = 0x00;
	VehSpdAugDrun[berco].cData[2] = 0x00;
	VehSpdAugDrun[berco].cData[1] = 0x00;
	VehSpdAugDrun[berco].cData[0] = 0x00;
	
	VehSpdAugNDrun[berco].dwID     = 0x3DE; //0x3EC
	VehSpdAugNDrun[berco].cLength  = 7;
	VehSpdAugNDrun[berco].cData[7] = 0x00;
	VehSpdAugNDrun[berco].cData[6] = 0x00;
	VehSpdAugNDrun[berco].cData[5] = 0x00;
	VehSpdAugNDrun[berco].cData[4] = 0x00;
	VehSpdAugNDrun[berco].cData[3] = 0x00;
	VehSpdAugNDrun[berco].cData[2] = 0x00;
	VehSpdAugNDrun[berco].cData[1] = 0x00;
	VehSpdAugNDrun[berco].cData[0] = 0x00;
	
	EngSpd[berco].dwID     = 0x0CA;
	EngSpd[berco].cLength  = 8;
	EngSpd[berco].cData[7] = 0x00;
	EngSpd[berco].cData[6] = 0x00;
	EngSpd[berco].cData[5] = 0x00;
	EngSpd[berco].cData[4] = 0x00;
	EngSpd[berco].cData[3] = 0x00;
	EngSpd[berco].cData[2] = 0x00;
	EngSpd[berco].cData[1] = 0x00;
	EngSpd[berco].cData[0] = 0x00;
	
	PPEI_Engine_General_Status_1_0CB_M2[berco].dwID  	= 0x0C9; //0x0CB
	PPEI_Engine_General_Status_1_0CB_M2[berco].cLength  = 8;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[7] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[6] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[5] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[4] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[3] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[2] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[1] = 0x00;
	PPEI_Engine_General_Status_1_0CB_M2[berco].cData[0] = 0x00;
	
	Exterior_Lighting_HS[berco].dwID     = 0x141;
	Exterior_Lighting_HS[berco].cLength  = 7;
	Exterior_Lighting_HS[berco].cData[7] = 0x00;
	Exterior_Lighting_HS[berco].cData[6] = 0x00;
	Exterior_Lighting_HS[berco].cData[5] = 0x7F;
	Exterior_Lighting_HS[berco].cData[4] = 0x7F;
	Exterior_Lighting_HS[berco].cData[3] = 0x01;
	Exterior_Lighting_HS[berco].cData[2] = 0x00;
	Exterior_Lighting_HS[berco].cData[1] = 0x00;
	Exterior_Lighting_HS[berco].cData[0] = 0x00;
	
	
	Airbag_Indications_19A_M[berco].dwID     = 0x19A;
	Airbag_Indications_19A_M[berco].cLength  = 7;
	Airbag_Indications_19A_M[berco].cData[7] = 0x00;
	Airbag_Indications_19A_M[berco].cData[6] = 0x00;
	Airbag_Indications_19A_M[berco].cData[5] = 0x00;
	Airbag_Indications_19A_M[berco].cData[4] = 0x00;
	Airbag_Indications_19A_M[berco].cData[3] = 0x00;
	Airbag_Indications_19A_M[berco].cData[2] = 0x00;
	Airbag_Indications_19A_M[berco].cData[1] = 0x00;
	Airbag_Indications_19A_M[berco].cData[0] = 0x00;
	
	Airbag_Indications_198_M[berco].dwID     = 0x198;
	Airbag_Indications_198_M[berco].cLength  = 7;
	Airbag_Indications_198_M[berco].cData[7] = 0x00;
	Airbag_Indications_198_M[berco].cData[6] = 0x00;
	Airbag_Indications_198_M[berco].cData[5] = 0x00;
	Airbag_Indications_198_M[berco].cData[4] = 0x00;
	Airbag_Indications_198_M[berco].cData[3] = 0x00;
	Airbag_Indications_198_M[berco].cData[2] = 0x00;
	Airbag_Indications_198_M[berco].cData[1] = 0x00;
	Airbag_Indications_198_M[berco].cData[0] = 0x00;
	
	Reseta_MensDiag(berco);
	
	Tester_present[berco].dwID 	 	= ID_CAN_DIAG_TX;
	Tester_present[berco].cFlags 	= MESS_STANDARD;
	Tester_present[berco].cLength 	= 8;
	Tester_present[berco].cData [7] = 0x00;
	Tester_present[berco].cData [6] = 0x00;
	Tester_present[berco].cData [5] = 0x00;
	Tester_present[berco].cData [4] = 0x00;
	Tester_present[berco].cData [3] = 0x00;
	Tester_present[berco].cData [2] = 0x80;
	Tester_present[berco].cData [1] = 0x3E;
	Tester_present[berco].cData [0] = 0x02;
	
}


/************************************* Envia_can_TX_NI() ****************************************************************************/
NCTYPE_STATUS Envia_can_TX_NI(NCTYPE_OBJH Obj_handler, EX_CAN_MSG* data, int berco) 
{
NCTYPE_CAN_FRAME
	Transmit; 
NCTYPE_STATUS 
		status=0;
char 
	mens_can_str[200]={0},
	t_buf		[50] ={0},
	seq_bytes	[50] ={0},
	tmp			[20] ={0},
	i;

 
 	///////////////////////////////////////////////////
	 
	Transmit.IsRemote 		= OFF; 
	Transmit.ArbitrationId 	= data->dwID; 
	Transmit.DataLength 	= data->cLength; 
	for(i=0; i<8; i++)
		Transmit.Data[i] = data->cData[i];
	//extend_frame_format[berco] > 0 set the 30th bit to initialize extended Frame Format 
	if (extend_frame_format[berco] == ON)
	{
		Transmit.ArbitrationId = Transmit.ArbitrationId | 0x20000000;
	}
	
	status= ncWrite(Obj_handler, sizeof(Transmit), &Transmit);   //send message
	
	if (status < 0) 
    {
        ///status = ncCloseObject(Obj_handler);  //close the handles 
		strcpy(CAN_error_str[berco],"CAN falhou na escrita, a interface CAN foi fechada !!!");
	   	return -1;  //fail
    }
	
	if(filtrar_mens_n_diag_CAN && data->dwID != ID_CAN_DIAG_TX)
		return SUCESSO;
		
	if(monitorar_comm_CAN == ON)  
	{
		for(i=0; i<=7; i++)
		{
			if(Transmit.Data[i]< 0x10)
				Fmt(tmp, "%s<0%x ", Transmit.Data[i]);
			else
				Fmt(tmp, "%s<%x ",  Transmit.Data[i]);
			strcat(seq_bytes, tmp);
		}
		Get_timestamp_CAN(ON,&t_buf[0]);
		Fmt(mens_can_str, "%s<%s%x - %s\n", t_buf,  data->dwID, seq_bytes);
		StringUpperCase (mens_can_str);
		if(ponteiro_logs_can != NULL)
		{
			if(strlen(ponteiro_logs_can) < MAX_TAM_ARQ_LOG_CAN)
				strcat(ponteiro_logs_can, mens_can_str); 
		}
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, ATTR_CTRL_VAL, mens_can_str);
	} 
		

return SUCESSO;  
}

/************************************* Recebe_can_RX_NI() ****************************************************************************/
int Recebe_can_RX_NI(int index, int berco) 
{
NCTYPE_STATUS 
		status = 0;
NCTYPE_CAN_STRUCT
		buffer[1];
static NCTYPE_CAN_STRUCT
	 ultima_mens_recebida[1][NUMERO_DE_BERCOS + 1];
NCTYPE_ABS_TIME
	timestamp;
NCTYPE_STATE    
	state;
char 
	string_err[1024],
	mens_can_str[200]={0},
	t_buf		[50] ={0},
	seq_bytes	[50] ={0},
	tmp			[20] ={0},
	i,
	error_str;
double 
	t;
				
	//Delay(0.001);
	/*status = ncWaitForState (TXRXHandle[berco] , (NC_ST_READ_AVAIL), 500, &state);
	if (((state & 1) == 0) || status < 0)
	{
		ncStatusToString (status, sizeof(string_err), string_err);
		 return -1;
	}*/
	t = Timer();
	while(Timer()-t < 0.2)
	{
		status = ncRead( TXRXHandle[berco] , sizeof(buffer) , (void *)buffer);
		if(status < 0)
		{
			ncStatusToString (status, sizeof(string_err), string_err);
			return status; 
		}
		if((ultima_mens_recebida[0][berco].Timestamp.LowPart == buffer[0].Timestamp.LowPart) && 
			(ultima_mens_recebida[0][berco].Timestamp.HighPart == buffer[0].Timestamp.HighPart) &&
			(ultima_mens_recebida[0][berco].ArbitrationId == buffer[0].ArbitrationId))
		{
			continue;
		}
		else
			break;
	}
	Resp_diagnostico_RX[index][berco].cData[0] 	= buffer[0].Data[0];
	Resp_diagnostico_RX[index][berco].cData[1] 	= buffer[0].Data[1];
	Resp_diagnostico_RX[index][berco].cData[2] 	= buffer[0].Data[2];
	Resp_diagnostico_RX[index][berco].cData[3] 	= buffer[0].Data[3];
	Resp_diagnostico_RX[index][berco].cData[4] 	= buffer[0].Data[4];
	Resp_diagnostico_RX[index][berco].cData[5] 	= buffer[0].Data[5];
	Resp_diagnostico_RX[index][berco].cData[6] 	= buffer[0].Data[6];
	Resp_diagnostico_RX[index][berco].cData[7] 	= buffer[0].Data[7];
	Resp_diagnostico_RX[index][berco].dwID		= buffer[0].ArbitrationId;
	Resp_diagnostico_RX[index][berco].timestamp	= buffer[0].Timestamp;
	Resp_diagnostico_RX[index][berco].cLength	= buffer[0].DataLength;
	ultima_mens_recebida[0][berco].Data[0] = buffer[0].Data[0];
	ultima_mens_recebida[0][berco].Data[1] = buffer[0].Data[1];
	ultima_mens_recebida[0][berco].Data[2] = buffer[0].Data[2];
	ultima_mens_recebida[0][berco].Data[3] = buffer[0].Data[3];
	ultima_mens_recebida[0][berco].Data[4] = buffer[0].Data[4];
	ultima_mens_recebida[0][berco].Data[5] = buffer[0].Data[5];
	ultima_mens_recebida[0][berco].Data[6] = buffer[0].Data[6];
	ultima_mens_recebida[0][berco].Data[7] = buffer[0].Data[7];
	ultima_mens_recebida[0][berco].Timestamp		= buffer[0].Timestamp;
	ultima_mens_recebida[0][berco].ArbitrationId	= buffer[0].ArbitrationId;
	
	if (extend_frame_format[berco] == ON && status >= 0)
	{
			if((((Resp_diagnostico_RX[index][berco].dwID - 0x20000000) == ID_CAN_DIAG_RX) && monitorar_comm_CAN) || monitorar_comm_CAN == OFF)
				Resp_diagnostico_RX[index][berco].dwID = Resp_diagnostico_RX[index][berco].dwID - 0x20000000;
	}
	if(filtrar_mens_n_diag_CAN && Resp_diagnostico_RX[index][berco].dwID != ID_CAN_DIAG_RX)
		return SUCESSO;
	if(monitorar_comm_CAN == ON)  
	{
		for(i=0; i<=7; i++)
		{
			if(buffer[0].Data[i] < 0x10)
				Fmt(tmp, "%s<0%x ", buffer[0].Data[i]);
			else
				Fmt(tmp, "%s<%x ",  buffer[0].Data[i]);
			strcat(seq_bytes, tmp);
		}
		Get_timestamp_CAN(OFF,&t_buf[0]);
		Fmt(mens_can_str, "%s<%s%x - %s\n", t_buf,  Resp_diagnostico_RX[index][berco].dwID, seq_bytes);
		StringUpperCase (mens_can_str);
		if(ponteiro_logs_can != NULL)
		{
			if(strlen(ponteiro_logs_can) < MAX_TAM_ARQ_LOG_CAN)
				strcat(ponteiro_logs_can, mens_can_str);
		}
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, ATTR_CTRL_VAL, mens_can_str);
	} 
	
return SUCESSO;
}


/************************************* MensDiagFlowControl() ****************************************************************************/
//Send CAN flow control
void MensDiagFlowControl(int berco)
{
int 
	i=0;
			   
	for(i=1; i<=7; i++)
		Diagnostico_TX[0][berco].cData[i] = 0;
	
	Diagnostico_TX[0][berco].cData [0] = 0x30;
	
	Envia_can_TX_NI(TXRXHandle[berco],&Diagnostico_TX[0][berco], berco);
	
}  

/************************************* Reset_CAN() ****************************************************************************/
//reset NI CAN interface
void Reset_CAN(int berco)
{
	 ncCloseObject(TXRXHandle[berco]);
	 Delay_thread(1);
	 InicializaCAN(can_defin[berco].nome, can_defin[berco].canal, berco); 
}

/************************************* InicializaCAN() ****************************************************************************/
//start NI CAN interface
int InicializaCAN(NCTYPE_STRING ObjName,DWORD dwChannel, int berco)
{
int 
	num_canais 	= 0, 
	status     	= 0;
USHORT         
	wVersion   	= 0;
char
 	Interface[30]= {0};
NCTYPE_UINT32
	can_baudrate;

	atualizar_mens_can[berco] = OFF;
	Delay(0.1);
    ncCloseObject(TXRXHandle[berco]);//close the handles before terminating the application. 
	Delay(0.01);
	can_baudrate		= HSCAN_BAUD_RATE * 1000;
	AttrIdList[0] 		= NC_ATTR_BAUD_RATE;   
	AttrValueList[0] 	= can_baudrate;
	AttrIdList[1] 		= NC_ATTR_START_ON_OPEN;
	AttrValueList[1] 	= NC_TRUE;
	AttrIdList[2] 		= NC_ATTR_READ_Q_LEN;
	AttrValueList[2] 	= 300;
	AttrIdList[3] 		= NC_ATTR_WRITE_Q_LEN;
	AttrValueList[3] 	= 0;
	AttrIdList[4] 		= NC_ATTR_CAN_COMP_STD;
	AttrValueList[4] 	= 0;
	AttrIdList[5] 		= NC_ATTR_CAN_MASK_STD;
	AttrValueList[5] 	= NC_CAN_MASK_STD_DONTCARE;
	AttrIdList[6] 		= NC_ATTR_CAN_COMP_XTD;
	AttrValueList[6] 	= 0;
	AttrIdList[7] 		= NC_ATTR_CAN_MASK_XTD;
	AttrValueList[7] 	= NC_CAN_MASK_XTD_DONTCARE;
	
	strcpy(Interface,ObjName);
	ncConfig(Interface, 8, AttrIdList, AttrValueList); //CVI function

	status_can = ncOpenObject(Interface, &TXRXHandle[berco]); //open the CAN
    if (status_can < 0)    //CAN error !!!
    {
           ncCloseObject(TXRXHandle[berco]);//close the handles before terminating the application. 
		   Fmt(CAN_error_str[berco], "%s<%s%s%i%s%s\nContinuar ?" ,"Erro ao tentar abrir comunica��o com o canal CAN\n", "N�mero do canal=", dwChannel,"\nDescri��o do canal=", ObjName);
		   return -1;   
    }
	
	InicializaMensagens(berco);  //start CAN messages

	modo_diagnostico[berco]  = NOT_DIAG; //n�o esta em diag
	qual_diag_atual[berco]   = NOT_DIAG; 
	atualizar_mens_can[berco] = ON;
	
return SUCESSO;  //success
}



/************************************* Get_timestamp_CAN() ****************************************************************************/
void Get_timestamp_CAN(int tx, char *tms)
{
double 
	tempo;

	tempo = (Timer()-tempo_inicial_log_CAN);
	if(tempo < 10)
		Fmt (tms, "%s<  %f[p6]",tempo);
	else if(tempo > 10 && tempo < 100)
		Fmt (tms, "%s< %f[p6]", tempo);
	else 
		Fmt (tms, "%s<%f[p6]",  tempo);
	if (tx == ON)
		strcat (tms, " - TX - ");
	else
		strcat (tms, " - RX - "); 
	
}

/************************************* EnviarEsperarRespDiag() ****************************************************************************/
//Send diag commands by CAN and get response
int EnviarEsperarRespDiag (int test_present, int berco)
{
int
    i		=0,
	status	=0, 
	sair 	= OFF,
	cluster_resp_err,
	tamanho_resp_cluster;
double 
	t		=0, 
	timeout	=1.0;
char
	t_buf[100] 	= {0},
	c_tx [30]  	= {0},			
	log_st[1000]= {0};
unsigned char 
	flags_mult_mens[MAX_MENS_CAN_RX_DIAG]={0x10, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 
										   0x2F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D};
int
	taman_mult_mens[MAX_MENS_CAN_RX_DIAG+1]={0, 6, 13, 20, 27, 34, 41, 48, 55, 62, 69, 76, 83, 90, 97, 104,
										   111, 118, 125, 132, 139, 146, 153, 160, 167, 174, 181, 188, 195, 202, 209};

		/////////////////////////////
		Reseta_dados_resp_cluster_CAN(berco);
		////////////////////////////////////////////////////////////////
		if(test_present)
			status = Envia_can_TX_NI(TXRXHandle[berco],&Tester_present[berco], berco);
		else
			status = Envia_can_TX_NI(TXRXHandle[berco],&Diagnostico_TX[0][berco], berco);
		sair 	= OFF;
		status 	= 0;
		t = Timer();
		while(Timer() - t < timeout && sair == OFF) 
		{
			if(test_present && Timer() - t > 0.1)
			{
				status = Envia_can_TX_NI(TXRXHandle[berco],&Tester_present[berco], berco);
				Delay(0.001);
			}
			if(Recebe_can_RX_NI(0, berco) < 0)
				return FALHA_LEITURA_CAN;
			if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX)
			{
					//////////////////// Negativas /////////////////////
					if(Diagnostico_TX[0][berco].cData[0] == 0x10 && Resp_diagnostico_RX[0][berco].cData[0] != 0x30 && !test_present)// espera receber Flow control do cluster
						sair = OFF;
					
					else if(Resp_diagnostico_RX[0][berco].cData[0] == 0x02 && Resp_diagnostico_RX[0][berco].cData[1] == 0x7E && !test_present)  //apenas resposta ao test present
					{
						timer_test_pres[berco] = Timer();
						sair = OFF;
					}
					else if(Resp_diagnostico_RX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[1] == 0x7F && 
							 (Resp_diagnostico_RX[0][berco].cData[2] == Diagnostico_TX[0][berco].cData[1] || Resp_diagnostico_RX[0][berco].cData[2] == Diagnostico_TX[0][berco].cData[2]) && !test_present)// Resposta v�lida por�m sinaliza erros
					{
						//cluster_resp_err = cluster_resp_err+1;
						sair = OFF;
					}
					//////////////////// Positivas /////////////////////
					else if(Diagnostico_TX[0][berco].cData[0] == 0x10 && Resp_diagnostico_RX[0][berco].cData[0] == 0x30 && !test_present)// Recebeu Flow control 
						sair = ON;
					else if(Diagnostico_TX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[0] == 0x10 && Resp_diagnostico_RX[0][berco].cData[2] == (Diagnostico_TX[0][berco].cData[1]+0x40) && !test_present)// Resposta valida e sem erros
						sair = ON;
					else if(Diagnostico_TX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[1] == (Diagnostico_TX[0][berco].cData[1]+0x40) && !test_present)// Resposta valida e sem erros
						sair = ON;
					else if(Resp_diagnostico_RX[0][berco].cData[1] == 0x7E && test_present)// Resposta valida e sem erros
						sair = ON;
					else
						sair = OFF;
			}
		}
		if(Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX)
		{
			strcpy(CAN_error_str[berco],"Timeout, CAN n�o respondeu !!! \n Verifique a interface CAN.\n Verifique se o produto est� ligado e conectado ao m�dulo CAN.");
			return -1;
		}
	
		if((Timer() -t) > timeout || status < 0 || sair == OFF)
			return -100;
		//////////////////////////////////////////////////////////////////////////////////////////
		if(Resp_diagnostico_RX[0][berco].cData[0]==0x30 && Diagnostico_TX[0][berco].cData[0] == 0x10 && test_present == OFF)//Recebeu flow control?
		{	
			for(i=1; i < MAX_MENS_CAN_TX_DIAG; i++) //envias demais mensagens ap�s flow-control
			{
				//Delay(0.001);
				if(Diagnostico_TX[i][berco].cData[0] >= 0x20)
					status = Envia_can_TX_NI(TXRXHandle[berco],&Diagnostico_TX[i][berco], berco);   //<---send frame
				else
					break;
			}
			Resp_diagnostico_RX[0][berco].dwID=0;
			cluster_resp_err = 0;
			sair 	= OFF;
			t = Timer();
		 	while(Timer() - t < timeout && sair == OFF) 
			{	
				Resp_diagnostico_RX[0][berco].dwID  = 0;
				if(Recebe_can_RX_NI(0, berco) < 0)
					return FALHA_LEITURA_CAN;
				if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX)
				{		   
						//////////////////// Negativas /////////////////////
						if(Resp_diagnostico_RX[0][berco].cData[0] == 0x30 && Resp_diagnostico_RX[0][berco].cData[1] == 0x0)// recebeu Flow control do cluster
							sair = OFF;
						else if(Resp_diagnostico_RX[0][berco].cData[0] == 0x02 && Resp_diagnostico_RX[0][berco].cData[1] == 0x7E && Diagnostico_TX[0][berco].cData[0] != 0x02 && Diagnostico_TX[0][berco].cData[1] != 0x3E)  //recebeu resposta ao test present
							sair = OFF;
						//////////////////// Positivas /////////////////////
						else if(Resp_diagnostico_RX[0][berco].cData[0] == 0x10 && (Resp_diagnostico_RX[0][berco].cData[2] == (Diagnostico_TX[0][berco].cData[1]+0x40) || Resp_diagnostico_RX[0][berco].cData[2] == (Diagnostico_TX[0][berco].cData[2]+0x40)))// Resposta valida e sem erros
							sair = ON;
						else if(Resp_diagnostico_RX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[1] == (Diagnostico_TX[0][berco].cData[2]+0x40))// Resposta valida e sem erros
							sair = ON;
						else if(Resp_diagnostico_RX[0][berco].cData[0] <= 0x07 && Resp_diagnostico_RX[0][berco].cData[1] == 0x7F && (Resp_diagnostico_RX[0][berco].cData[2] == Diagnostico_TX[0][berco].cData[1] || Resp_diagnostico_RX[0][berco].cData[2] == Diagnostico_TX[0][berco].cData[2]))// Resposta v�lida por�m sinaliza erros
						{
							sair = OFF;
							cluster_resp_err = cluster_resp_err+100;
						}
						else
							sair = OFF;
		        }
			}
			if(sair == OFF)
				return FALHA_LEITURA_CAN;
			if(Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX)
			{
				strcpy(CAN_error_str[berco],"Timeout, CAN n�o respondeu !!! \n Verifique a interface CAN.\n Verifique se o produto est� ligado e conectado ao m�dulo CAN.");
				return -1;
			}
		
		}
		//////////////////////////////////////////////////////////////////////////////////////////		
		if(Resp_diagnostico_RX[0][berco].cData[0] == 0x30)   //flow control
			return CAN_FLOW_CONTROL;
		if(status < 0)
			return status;
			    		
		if(Resp_diagnostico_RX[0][berco].cData[0] == 0x10) 
			tamanho_resp_cluster = Resp_diagnostico_RX[0][berco].cData[1];
		else
			tamanho_resp_cluster = Resp_diagnostico_RX[0][berco].cData[0];
	
		if(Resp_diagnostico_RX[0][berco].cData[0] == 0x10 && tamanho_resp_cluster > 6) 
		{		
	   		MensDiagFlowControl(berco);
			//Delay(0.001);
			//////////////////////////////////////////////////////////////////////////////
			for(i=1; i < MAX_MENS_CAN_RX_DIAG; i++)
			{
				if(Resp_diagnostico_RX[i-1][berco].cData[0] == flags_mult_mens[i-1] && tamanho_resp_cluster > taman_mult_mens[i])
				{
					t = Timer();
					while(Timer() - t < timeout && (Resp_diagnostico_RX[i][berco].dwID != ID_CAN_DIAG_RX || Resp_diagnostico_RX[i][berco].cData[0] != flags_mult_mens[i]))
					{
						if(Recebe_can_RX_NI(i, berco) < 0)
							return FALHA_LEITURA_CAN;
					}
					if(Resp_diagnostico_RX[i][berco].dwID != ID_CAN_DIAG_RX || Resp_diagnostico_RX[i][berco].cData[0] != flags_mult_mens[i])
							return FALHA_LEITURA_CAN;
				}
				else
				{
					break;
				}
			}
		}
		if( status<0)   //fail
		{
			strcpy(CAN_error_str[berco],"Timeout, CAN n�o respondeu !!! \n Verifique a interface CAN.\n Verifique se o produto est� ligado e conectado ao m�dulo CAN.");
	 		modo_diagnostico[berco] = NOT_DIAG;
			qual_diag_atual[berco]  = NOT_DIAG;
			return status;
		}
	
	
return SUCESSO;
}


/********************************** Reseta_dados_resp_cluster_CAN() ************************************************************/
void Reseta_dados_resp_cluster_CAN(int berco)
{
int 
	i,
	x;
	
		for(i=0; i<MAX_MENS_CAN_RX_DIAG; i++)
			Resp_diagnostico_RX[i][berco].dwID=0;
		for (i=0;i<8;i++)
		{
			for(x=0; x<MAX_MENS_CAN_RX_DIAG; x++)
				Resp_diagnostico_RX[x][berco].cData[i]=0;
		}	
			
}
/********************************** Send_diag_commands ************************************************************/
//Send diag commands
int Send_diag_commands(int berco)
{
int 
	status 	= -1,
	quantos_bytes,
	configurado;
char 
	temp [20]={0};
double t;


	extend_frame_format[berco] = ON;
	
	switch(servico_diagnostico[berco])
	{	
		case LER_STATUS_LIVE_KEY:
			extend_frame_format[berco] = OFF;   
			t = Timer();
			do
			{
				status = LerMens_SysBkUpPwrMd(berco, &configurado);
				if(status == SUCESSO && configurado == ON)
						break;
			}while(Timer() - t < 2);
			break;
		case LER_ECU_ID:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xF3;//DID F0F3
			Diagnostico_TX[0][berco].cData [2] = 0xF0;  
			Diagnostico_TX[0][berco].cData [1] = 0x22;//Read Data By ID
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_ECU_ID:
			Diagnostico_TX[0][berco].cData [7] = 0xFF; 
			Diagnostico_TX[0][berco].cData [6] = 0x02; 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID FE20
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x1B;//Num BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [5] = 0x10; 
			Diagnostico_TX[1][berco].cData [4] = 0x00; 
			Diagnostico_TX[1][berco].cData [3] = 0x00;
			Diagnostico_TX[1][berco].cData [2] = 0x40;  
			Diagnostico_TX[1][berco].cData [1] = 0x20; 
			Diagnostico_TX[1][berco].cData [0] = 0x21;
			
			if(LoadBytes_LiveKey(WRITE_ECU_ID, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY20:
			Diagnostico_TX[0][berco].cData [6] = 0x14; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY20, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY19:
			Diagnostico_TX[0][berco].cData [6] = 0x13; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY19, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY18:
			Diagnostico_TX[0][berco].cData [6] = 0x12; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY18, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY17:
			Diagnostico_TX[0][berco].cData [6] = 0x11; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY17, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY16:
			Diagnostico_TX[0][berco].cData [6] = 0x10; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY16, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY15:
			Diagnostico_TX[0][berco].cData [6] = 0x0F; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY15, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY14:
			Diagnostico_TX[0][berco].cData [6] = 0x0E; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY14, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY13:
			Diagnostico_TX[0][berco].cData [6] = 0x0D; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY13, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY12:
			Diagnostico_TX[0][berco].cData [6] = 0x0C; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY12, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY11:
			Diagnostico_TX[0][berco].cData [6] = 0x0B; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY11, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY10:
			Diagnostico_TX[0][berco].cData [6] = 0x0A; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY10, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY9:
			Diagnostico_TX[0][berco].cData [6] = 0x09; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY9, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY8:
			Diagnostico_TX[0][berco].cData [6] = 0x08; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY8, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY7:
			Diagnostico_TX[0][berco].cData [6] = 0x07; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY7, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY6:
			Diagnostico_TX[0][berco].cData [6] = 0x06; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY6, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY5:
			Diagnostico_TX[0][berco].cData [6] = 0x05; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY5, berco) == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY4:
			Diagnostico_TX[0][berco].cData [6] = 0x04; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY4, berco)  == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY3:
			Diagnostico_TX[0][berco].cData [6] = 0x03; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY3, berco)  == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_GENERAL_KEY2:
			Diagnostico_TX[0][berco].cData [6] = 0x02; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_GENERAL_KEY2, berco) == SEM_ERRO)
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_UNLOCK_KEY:
			Diagnostico_TX[0][berco].cData [6] = 0x01; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_UNLOCK_KEY, berco)  == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WRITE_MASTER_KEY:
			Diagnostico_TX[0][berco].cData [6] = 0xFF; 
			Diagnostico_TX[0][berco].cData [5] = 0x72; 
			Diagnostico_TX[0][berco].cData [4] = 0x02; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;//DID 0272
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x45;//69 BYTES 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			if(LoadBytes_LiveKey(WRITE_MASTER_KEY, berco)  == SEM_ERRO) 
				status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case TELLT_DISP_DIAG_CUSTOMER:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			//Diagnostico_TX[0][berco].cData [5] = 0x??;0=OFF, 3=ON
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x0C; 
			Diagnostico_TX[0][berco].cData [2] = 0xF0;//DID F00C  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05; 
			
			status = EnviarEsperarRespDiag(OFF, berco);
			
			break;
		case LIMPAR_DTC:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0xFF; 
			Diagnostico_TX[0][berco].cData [3] = 0xFF; 
			Diagnostico_TX[0][berco].cData [2] = 0xFF; 
			Diagnostico_TX[0][berco].cData [1] = 0x14; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			
			break;
			
		case LER_BYTES_NVM_RES: 
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;  
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x20;  //DID FE20 
			Diagnostico_TX[0][berco].cData [3] = 0xFE;  
			Diagnostico_TX[0][berco].cData [2] = 0x03; //routine  results  
			Diagnostico_TX[0][berco].cData [1] = 0x31; //routine control request  
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
				    
		case LER_BYTES_NVM: 
			//Diagnostico_TX[0][berco].cData [7] = 0x??;//endere�o de inicio (1)
			Diagnostico_TX[0][berco].cData [6] = 0x01;  //<- read NVM 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;  //DID FE20 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  //start routine
			Diagnostico_TX[0][berco].cData [2] = 0x31;  //routine control request  
			Diagnostico_TX[0][berco].cData [1] = 0x0B; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0x00;
			//Diagnostico_TX[1][berco].cData [5] = 0x??;//num bytes a ler - lsb
			Diagnostico_TX[1][berco].cData [4] = 0x00;  //num bytes a ler - msb
			//Diagnostico_TX[1][berco].cData [3] =0x??;//<- endere�o de inicio (4)    
			//Diagnostico_TX[1][berco].cData [2] =0x??;//<- endere�o de inicio (3)    
			//Diagnostico_TX[1][berco].cData [1] =0x??;//<- endere�o de inicio (2)
			Diagnostico_TX[1][berco].cData [0] =0x21;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
			
		case ESC_BYTES_NVM:
			quantos_bytes = Diagnostico_TX[1][berco].cData [5];
			//Diagnostico_TX[0][berco].cData [7] = 0x??;//<- endere�o de inicio (1)
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<- Fun��o gravar 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;//DID FE20 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = (0x0B + quantos_bytes); 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] = envio_can[berco].dados_can[1]; //<- dado byte 2 
			Diagnostico_TX[1][berco].cData [6] = envio_can[berco].dados_can[0]; //<- dado byte 1
			//Diagnostico_TX[1][berco].cData [5] =0x??;//<- quant de bytes - lsb
			Diagnostico_TX[1][berco].cData [4] =0x00;  //<- quant de bytes - msb
			//Diagnostico_TX[1][berco].cData [3] =0x??;//<- endere�o de inicio (4)    
			//Diagnostico_TX[1][berco].cData [2] =0x??;//<- endere�o de inicio (3)    
			//Diagnostico_TX[1][berco].cData [1] =0x??;//<- endere�o de inicio (2)
			Diagnostico_TX[1][berco].cData [0] =0x21;
		
			Diagnostico_TX[2][berco].cData [7] =envio_can[berco].dados_can[8];//<- dado byte 9  
			Diagnostico_TX[2][berco].cData [6] =envio_can[berco].dados_can[7];//<- dado byte 8  
			Diagnostico_TX[2][berco].cData [5] =envio_can[berco].dados_can[6];//<- dado byte 7  
			Diagnostico_TX[2][berco].cData [4] =envio_can[berco].dados_can[5];//<- dado byte 6  
			Diagnostico_TX[2][berco].cData [3] =envio_can[berco].dados_can[4];//<- dado byte 5  
			Diagnostico_TX[2][berco].cData [2] =envio_can[berco].dados_can[3];//<- dado byte 4  
			Diagnostico_TX[2][berco].cData [1] =envio_can[berco].dados_can[2];//<- dado byte 3 
			if(quantos_bytes > 2)
				Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =envio_can[berco].dados_can[15];//<- dado byte 16 
			Diagnostico_TX[3][berco].cData [6] =envio_can[berco].dados_can[14];//<- dado byte 15 
			Diagnostico_TX[3][berco].cData [5] =envio_can[berco].dados_can[13];//<- dado byte 14 
			Diagnostico_TX[3][berco].cData [4] =envio_can[berco].dados_can[12];//<- dado byte 13 
			Diagnostico_TX[3][berco].cData [3] =envio_can[berco].dados_can[11];//<- dado byte 12  
			Diagnostico_TX[3][berco].cData [2] =envio_can[berco].dados_can[10];//<- dado byte 11  
			Diagnostico_TX[3][berco].cData [1] =envio_can[berco].dados_can[9]; //<- dado byte 10  
			if(quantos_bytes > 9)
				Diagnostico_TX[3][berco].cData [0] =0x23;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case PROGRAMAR_MTC: 
			Diagnostico_TX[0][berco].cData [7] = 0xFF;//<- endere�o de inicio (1)
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<- Fun��o gravar 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;//DID FE20 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x1B; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =envio_can[berco].dados_can[1]; //<- dado byte 2 
			Diagnostico_TX[1][berco].cData [6] =envio_can[berco].dados_can[0]; //<- dado byte 1
			Diagnostico_TX[1][berco].cData [5] =0x10; //<- Gravar 16 bytes
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] = add_mtc_3; //0x2A;//<- endere�o de inicio (4)    
			Diagnostico_TX[1][berco].cData [2] = add_mtc_2; //0x40;//<- endere�o de inicio (3)    
			Diagnostico_TX[1][berco].cData [1] = add_mtc_1; //0x20;//<- endere�o de inicio (2)
			Diagnostico_TX[1][berco].cData [0] =0x21;
		
			Diagnostico_TX[2][berco].cData [7] =envio_can[berco].dados_can[8];//<- dado byte 9  
			Diagnostico_TX[2][berco].cData [6] =envio_can[berco].dados_can[7];//<- dado byte 8  
			Diagnostico_TX[2][berco].cData [5] =envio_can[berco].dados_can[6];//<- dado byte 7  
			Diagnostico_TX[2][berco].cData [4] =envio_can[berco].dados_can[5];//<- dado byte 6  
			Diagnostico_TX[2][berco].cData [3] =envio_can[berco].dados_can[4];//<- dado byte 5  
			Diagnostico_TX[2][berco].cData [2] =envio_can[berco].dados_can[3];//<- dado byte 4  
			Diagnostico_TX[2][berco].cData [1] =envio_can[berco].dados_can[2];//<- dado byte 3  
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =envio_can[berco].dados_can[15];//<- dado byte 16 
			Diagnostico_TX[3][berco].cData [6] =envio_can[berco].dados_can[14];//<- dado byte 15 
			Diagnostico_TX[3][berco].cData [5] =envio_can[berco].dados_can[13];//<- dado byte 14 
			Diagnostico_TX[3][berco].cData [4] =envio_can[berco].dados_can[12];//<- dado byte 13 
			Diagnostico_TX[3][berco].cData [3] =envio_can[berco].dados_can[11];//<- dado byte 12  
			Diagnostico_TX[3][berco].cData [2] =envio_can[berco].dados_can[10];//<- dado byte 11  
			Diagnostico_TX[3][berco].cData [1] =envio_can[berco].dados_can[9];//<- dado byte 10  
			Diagnostico_TX[3][berco].cData [0] =0x23;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case PROGRAMAR_PN: //end model number(default - )
			Diagnostico_TX[0][berco].cData [7] = 0xFF;//<- endere�o de inicio (1)
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<- Fun��o gravar 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;//DID FE20 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x0F; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			//Diagnostico_TX[1][berco].cData [7] =0x00; <- dado byte 2 
			//Diagnostico_TX[1][berco].cData [6] =0x00; <- dado byte 1
			Diagnostico_TX[1][berco].cData [5] =0x04; //<- Gravar 4 bytes
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x10;//<- endere�o de inicio (4)    
			Diagnostico_TX[1][berco].cData [2] =0x40;//<- endere�o de inicio (3)    
			Diagnostico_TX[1][berco].cData [1] =0x20;//<- endere�o de inicio (2)
			Diagnostico_TX[1][berco].cData [0] =0x21;
		
			Diagnostico_TX[2][berco].cData [7] =0x00;
			Diagnostico_TX[2][berco].cData [6] =0x00;
			Diagnostico_TX[2][berco].cData [5] =0x00;
			Diagnostico_TX[2][berco].cData [4] =0x00;
			Diagnostico_TX[2][berco].cData [3] =0x00;
			//Diagnostico_TX[2][berco].cData [2] =0x00; <- dado byte 4 
			//Diagnostico_TX[2][berco].cData [1] =0x00; <- dado byte 3 
			Diagnostico_TX[2][berco].cData [0] =0x22;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case PROGRAMAR_MEC: 
			Diagnostico_TX[0][berco].cData [7] = 0xFF;//<- endere�o de inicio (1)  
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<- Fun��o gravar 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;//DID FE20     
			Diagnostico_TX[0][berco].cData [3] = 0x01; 
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x0C; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0xFE;// valor do byte a ser gravado
			Diagnostico_TX[1][berco].cData [5] =0x01;//<- Gravar 1 byte 
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x49;//<- endere�o de inicio (4) 
			Diagnostico_TX[1][berco].cData [2] =0x4D;//<- endere�o de inicio (3) 
			Diagnostico_TX[1][berco].cData [1] =0x20;//<- endere�o de inicio (2) 
			Diagnostico_TX[1][berco].cData [0] =0x21;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case PROGRAMAR_MEC_SERVICE: 
			Diagnostico_TX[0][berco].cData [7] = 0xFF;//<- endere�o de inicio (1)  
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<- Fun��o gravar 
			Diagnostico_TX[0][berco].cData [5] = 0x20; 
			Diagnostico_TX[0][berco].cData [4] = 0xFE;//DID FE20     
			Diagnostico_TX[0][berco].cData [3] = 0x01; 
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x0C; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0x00;// valor do byte a ser gravado(SERVI�O = 0x00)
			Diagnostico_TX[1][berco].cData [5] =0x01;//<- Gravar 1 byte 
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x49;//<- endere�o de inicio (4) 
			Diagnostico_TX[1][berco].cData [2] =0x4D;//<- endere�o de inicio (3) 
			Diagnostico_TX[1][berco].cData [1] =0x20;//<- endere�o de inicio (2) 
			Diagnostico_TX[1][berco].cData [0] =0x21;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
				
		case LER_SW_STATUS:
		case LER_CLUSTER_INFO:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0x40; //DID FE40 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LER_MEC_STATUS: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xA0; //DID F1A0 
			Diagnostico_TX[0][berco].cData [2] = 0xF1;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LER_PN_STATUS: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xCB; //DID F1CB
			Diagnostico_TX[0][berco].cData [2] = 0xF1;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LER_MTC_STATUS: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xB4; //DID F0B4
			Diagnostico_TX[0][berco].cData [2] = 0xF0;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LER_BASE_STATUS: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xCC; //DID F1CC
			Diagnostico_TX[0][berco].cData [2] = 0xF1;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
				  
		case WATCH_DOG_CONTINUO: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0xF8; //DID FEF8
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case WATCH_DOG_STOP: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x01; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0xF8; //DID FEF8
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			//status = EnviarEsperarRespDiag(OFF, berco);
			//status = EnviarEsperarRespDiag(OFF, berco);
			Envia_can_TX_NI(TXRXHandle[berco],&Diagnostico_TX[berco][0], berco);
			Delay_thread(0.1);
			servico_diagnostico[berco] = DIAG_SERVICE_OFF;
			status = SEM_ERRO;
			break;
		/*case VERIFICA_CHECKSUM: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x23; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE23 
			Diagnostico_TX[0][berco].cData [2] = 0x01;  
			Diagnostico_TX[0][berco].cData [1] = 0x31; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;*/	
		case CORRIGE_CHECKSUM: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x21; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE21 
			Diagnostico_TX[0][berco].cData [2] = 0x01;  
			Diagnostico_TX[0][berco].cData [1] = 0x31; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case STATUS_PPLACEM_MODE: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x61; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE61  - STATUS
			Diagnostico_TX[0][berco].cData [2] = 0x03;  
			Diagnostico_TX[0][berco].cData [1] = 0x31; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ENTRAR_PPLACEM_MODE: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x61; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE61 - START
			Diagnostico_TX[0][berco].cData [2] = 0x01;  
			Diagnostico_TX[0][berco].cData [1] = 0x31; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ENTRAR_SLEEP_MODE: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0xCA; 
			Diagnostico_TX[0][berco].cData [3] = 0x5F; //DID FD5F 
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2E; 
			Diagnostico_TX[0][berco].cData [0] = 0x04;
			//status = EnviarEsperarRespDiag(OFF, berco);
			Envia_can_TX_NI(TXRXHandle[berco],&Diagnostico_TX[berco][0], berco);
			Delay_thread(0.1);
			servico_diagnostico[berco] = DIAG_SERVICE_OFF;
			status = SEM_ERRO;
			break;
			 
		case ECU_RESET: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x40;//<- RESET  
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0xFD; 
			Diagnostico_TX[0][berco].cData [2] = 0xF0;//DID F0FD  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
			
		case ENABLE_GAUGE: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			//Diagnostico_TX[0][berco].cData [5] = 0x00;//00=OFF  01=ON  
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0xF5; //DID FEF5 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
			
		case GAUGE_EOL_VISTEON:
			Diagnostico_TX[0][berco].cData [7] = 0x01;//Velocity Mode - acc/desacc profile ON/OFF - 01=fixed  <- manter em FIXED conforme spec 'Gauge EOL Calibrations Version 0.2)
			//Diagnostico_TX[0][berco].cData [6] = 0x??;//gauge ID 
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0xF6;  
			Diagnostico_TX[0][berco].cData [3] = 0xFE;//DID FEF6  
			Diagnostico_TX[0][berco].cData [2] = 0x2F; 
			Diagnostico_TX[0][berco].cData [1] = 0x0B;
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0x00;
			//Diagnostico_TX[1][berco].cData [5] =0x00;//lsb counts 
			//Diagnostico_TX[1][berco].cData [4] =0x00;//msb counts
			//Diagnostico_TX[1][berco].cData [3] =0x00;//movement type 00=absolute, 01=Towards stop 
			//Diagnostico_TX[1][berco].cData [2] =0x00;//torque  -> 00=Normal, 01=High Torque,  02=Low Torque
			//Diagnostico_TX[1][berco].cData [1] =0x00;//speed  0x01=166.6graus/seg, 0x03=55.55graus/seg, 0x05=33.35graus/seg
			Diagnostico_TX[1][berco].cData [0] =0x21;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case LER_CRYSTAL_VERIF: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xF7; //DID FEF7 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case TACOMETRO_CUSTOMER: 
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			//Diagnostico_TX[0][berco].cData [6] = 0x00;//lsb 
			//Diagnostico_TX[0][berco].cData [5] = 0x00;//msb  
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x03;  
			Diagnostico_TX[0][berco].cData [2] = 0xF0;//DID F003  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case VELOCIMETRO_CUSTOMER: 
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			//Diagnostico_TX[0][berco].cData [6] = 0x00;//lsb 
			//Diagnostico_TX[0][berco].cData [5] = 0x00;//msb  
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x02;  
			Diagnostico_TX[0][berco].cData [2] = 0xF0;//DID F002  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case TELLTALE_ON_OFF_DIAG: 
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0x0D; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE0D 
			Diagnostico_TX[0][berco].cData [2] = 0x2F;  
			Diagnostico_TX[0][berco].cData [1] = 0x0A; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0x00;
			Diagnostico_TX[1][berco].cData [5] =0x00;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ILLUM_GAUGE_ADJUST_DIAG: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x25; //DID FD25 
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ILLUM_POINTER_ADJUST_DIAG: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x26; //DID FD26 
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ILLUM_LCD_ADJUST_DIAG: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x27; //DID FD27 
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
		case ILLUM_TELLTALE_ADJUST_DIAG: 
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			//Diagnostico_TX[0][berco].cData [6] = 0x00;LSB 
			//Diagnostico_TX[0][berco].cData [5] = 0x00;MSB 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x29; //DID FD29 
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x06;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
			
		case LER_RUN_CRANK_DIAG: 
		case LER_DIC_SWITCH_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0x00; //DID FE00
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;	
			
		case LER_DIC_ANALOG_DIAG			:
		case LER_PASSIV_START_DIAG			:
		case LER_FCA_OUT_DIAG				:
		case LER_FCA_DN_OUT_DIAG			:
		case LER_PASS_START_RUN_OUT_DIAG 	:
		case LER_PASS_START_IS1_OUT_DIAG 	:
		case LER_PASS_START_ACC_OUT_DIAG 	:
		case LER_PASS_START_IS2_OUT_DIAG 	:
		case LER_BATTERY_VOLTAGE_DIAG 		:
		case LER_PCB_TEMPERATURE_NTC		:
		case LER_MONITOR_5V					:
		case LER_LOW_FUEL_AD				:
		case LER_TIRE_PRESS_AD				:
		case LER_ESC_AD						:
		case LER_ABS_AD						:
		case LER_PARKING_AD					:
		case LER_BRAKE_AD					:
		case LER_AIRBAG_AD					:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0x03; //DID FE03
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case ESC_FCA_OUT_DIAG:
		case ESC_FCA_DN_OUT_DIAG:
		case ESC_PASS_START_RUN_OUT_DIAG:
		case ESC_PASS_START_ACC_OUT_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			//Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x15; //DID FD15
			Diagnostico_TX[0][berco].cData [2] = 0xFD;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x07;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case TFT_PATTERN_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			//Diagnostico_TX[0][berco].cData [5] = 0x??;
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x0A; //DID FE0A 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
			/*
		case LCD_SEGM_ALL_OFF_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			Diagnostico_TX[0][berco].cData [5] = 0x00;//<-- 
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x0B; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LCD_SEGM_ALL_ON_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			Diagnostico_TX[0][berco].cData [5] = 0x01;//<--  
			Diagnostico_TX[0][berco].cData [4] = 0x03; 
			Diagnostico_TX[0][berco].cData [3] = 0x0B; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0xFE;  
			Diagnostico_TX[0][berco].cData [1] = 0x2F; 
			Diagnostico_TX[0][berco].cData [0] = 0x05;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			*/
		case LCD_SEGM_ALL_OFF_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<-- 
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0x0B; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0x2F;  
			Diagnostico_TX[0][berco].cData [1] = 0x24; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x00;
			Diagnostico_TX[1][berco].cData [6] =0x00;
			Diagnostico_TX[1][berco].cData [5] =0x00;
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x00;
			Diagnostico_TX[1][berco].cData [2] =0x00;
			Diagnostico_TX[1][berco].cData [1] =0x00;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			Diagnostico_TX[2][berco].cData [7] =0x00;
			Diagnostico_TX[2][berco].cData [6] =0x00;
			Diagnostico_TX[2][berco].cData [5] =0x00;
			Diagnostico_TX[2][berco].cData [4] =0x00;
			Diagnostico_TX[2][berco].cData [3] =0x00;
			Diagnostico_TX[2][berco].cData [2] =0x00;
			Diagnostico_TX[2][berco].cData [1] =0x00;
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =0x00;
			Diagnostico_TX[3][berco].cData [6] =0x00;
			Diagnostico_TX[3][berco].cData [5] =0x00;
			Diagnostico_TX[3][berco].cData [4] =0x00;
			Diagnostico_TX[3][berco].cData [3] =0x00;
			Diagnostico_TX[3][berco].cData [2] =0x00;
			Diagnostico_TX[3][berco].cData [1] =0x00;
			Diagnostico_TX[3][berco].cData [0] =0x23;
			
			Diagnostico_TX[4][berco].cData [7] =0x00;
			Diagnostico_TX[4][berco].cData [6] =0x00;
			Diagnostico_TX[4][berco].cData [5] =0x00;
			Diagnostico_TX[4][berco].cData [4] =0x00;
			Diagnostico_TX[4][berco].cData [3] =0x00;
			Diagnostico_TX[4][berco].cData [2] =0x00;
			Diagnostico_TX[4][berco].cData [1] =0x00;
			Diagnostico_TX[4][berco].cData [0] =0x24;
			
			Diagnostico_TX[5][berco].cData [7] =0x00;
			Diagnostico_TX[5][berco].cData [6] =0x00;
			Diagnostico_TX[5][berco].cData [5] =0x00;
			Diagnostico_TX[5][berco].cData [4] =0x00;
			Diagnostico_TX[5][berco].cData [3] =0x00;
			Diagnostico_TX[5][berco].cData [2] =0x00;
			Diagnostico_TX[5][berco].cData [1] =0x00;
			Diagnostico_TX[5][berco].cData [0] =0x25; 
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LCD_SEGM_ALL_ON_DIAG:
			Diagnostico_TX[0][berco].cData [7] = 0xFF;
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<-- 
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0x0B; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0x2F;  
			Diagnostico_TX[0][berco].cData [1] = 0x24; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0xFF;
			Diagnostico_TX[1][berco].cData [6] =0xFF;
			Diagnostico_TX[1][berco].cData [5] =0xFF;
			Diagnostico_TX[1][berco].cData [4] =0xFF;
			Diagnostico_TX[1][berco].cData [3] =0xFF;
			Diagnostico_TX[1][berco].cData [2] =0xFF;
			Diagnostico_TX[1][berco].cData [1] =0xFF;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			Diagnostico_TX[2][berco].cData [7] =0xFF;
			Diagnostico_TX[2][berco].cData [6] =0xFF;
			Diagnostico_TX[2][berco].cData [5] =0xFF;
			Diagnostico_TX[2][berco].cData [4] =0xFF;
			Diagnostico_TX[2][berco].cData [3] =0xFF;
			Diagnostico_TX[2][berco].cData [2] =0xFF;
			Diagnostico_TX[2][berco].cData [1] =0xFF;
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =0xFF;
			Diagnostico_TX[3][berco].cData [6] =0xFF;
			Diagnostico_TX[3][berco].cData [5] =0xFF;
			Diagnostico_TX[3][berco].cData [4] =0xFF;
			Diagnostico_TX[3][berco].cData [3] =0xFF;
			Diagnostico_TX[3][berco].cData [2] =0xFF;
			Diagnostico_TX[3][berco].cData [1] =0xFF;
			Diagnostico_TX[3][berco].cData [0] =0x23;
			
			Diagnostico_TX[4][berco].cData [7] =0xFF;
			Diagnostico_TX[4][berco].cData [6] =0xFF;
			Diagnostico_TX[4][berco].cData [5] =0xFF;
			Diagnostico_TX[4][berco].cData [4] =0xFF;
			Diagnostico_TX[4][berco].cData [3] =0xFF;
			Diagnostico_TX[4][berco].cData [2] =0xFF;
			Diagnostico_TX[4][berco].cData [1] =0xFF;
			Diagnostico_TX[4][berco].cData [0] =0x24;
			
			Diagnostico_TX[5][berco].cData [7] =0x00;
			Diagnostico_TX[5][berco].cData [6] =0x00;
			Diagnostico_TX[5][berco].cData [5] =0x00;
			Diagnostico_TX[5][berco].cData [4] =0x00;
			Diagnostico_TX[5][berco].cData [3] =0x00;
			Diagnostico_TX[5][berco].cData [2] =0xFF;
			Diagnostico_TX[5][berco].cData [1] =0xFF;
			Diagnostico_TX[5][berco].cData [0] =0x25; 
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
		case LCD_SEGM_PATT_3:
			Diagnostico_TX[0][berco].cData [7] = 0xE5;
			Diagnostico_TX[0][berco].cData [6] = 0x02;//<-- 
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0x0B; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0x2F;  
			Diagnostico_TX[0][berco].cData [1] = 0x24; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0x49;
			Diagnostico_TX[1][berco].cData [6] =0x49;
			Diagnostico_TX[1][berco].cData [5] =0x49;
			Diagnostico_TX[1][berco].cData [4] =0x49;
			Diagnostico_TX[1][berco].cData [3] =0x49;
			Diagnostico_TX[1][berco].cData [2] =0x49;
			Diagnostico_TX[1][berco].cData [1] =0x31;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			Diagnostico_TX[2][berco].cData [7] =0x49;
			Diagnostico_TX[2][berco].cData [6] =0x49;
			Diagnostico_TX[2][berco].cData [5] =0x49;
			Diagnostico_TX[2][berco].cData [4] =0x49;
			Diagnostico_TX[2][berco].cData [3] =0x49;
			Diagnostico_TX[2][berco].cData [2] =0x49;
			Diagnostico_TX[2][berco].cData [1] =0x49;
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =0x49;
			Diagnostico_TX[3][berco].cData [6] =0x49;
			Diagnostico_TX[3][berco].cData [5] =0x49;
			Diagnostico_TX[3][berco].cData [4] =0x49;
			Diagnostico_TX[3][berco].cData [3] =0x49;
			Diagnostico_TX[3][berco].cData [2] =0x49;
			Diagnostico_TX[3][berco].cData [1] =0x49;
			Diagnostico_TX[3][berco].cData [0] =0x23;
			
			Diagnostico_TX[4][berco].cData [7] =0xAA;
			Diagnostico_TX[4][berco].cData [6] =0xAA;
			Diagnostico_TX[4][berco].cData [5] =0xAA;
			Diagnostico_TX[4][berco].cData [4] =0xAA;
			Diagnostico_TX[4][berco].cData [3] =0xAA;
			Diagnostico_TX[4][berco].cData [2] =0xAA;
			Diagnostico_TX[4][berco].cData [1] =0xAA;
			Diagnostico_TX[4][berco].cData [0] =0x24;
			
			Diagnostico_TX[5][berco].cData [7] =0x00;
			Diagnostico_TX[5][berco].cData [6] =0x00;
			Diagnostico_TX[5][berco].cData [5] =0x00;
			Diagnostico_TX[5][berco].cData [4] =0x00;
			Diagnostico_TX[5][berco].cData [3] =0x00;
			Diagnostico_TX[5][berco].cData [2] =0xAA;
			Diagnostico_TX[5][berco].cData [1] =0xAA;
			Diagnostico_TX[5][berco].cData [0] =0x25; 
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
		case LCD_SEGM_PATT_4:
			Diagnostico_TX[0][berco].cData [7] = 0x1A;
			Diagnostico_TX[0][berco].cData [6] = 0x02;
			Diagnostico_TX[0][berco].cData [5] = 0x03; 
			Diagnostico_TX[0][berco].cData [4] = 0x0B; 
			Diagnostico_TX[0][berco].cData [3] = 0xFE; //DID FE0B 
			Diagnostico_TX[0][berco].cData [2] = 0x2F;  
			Diagnostico_TX[0][berco].cData [1] = 0x24; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			
			Diagnostico_TX[1][berco].cData [7] =0xB6;
			Diagnostico_TX[1][berco].cData [6] =0xB6;
			Diagnostico_TX[1][berco].cData [5] =0xB6;
			Diagnostico_TX[1][berco].cData [4] =0xB6;
			Diagnostico_TX[1][berco].cData [3] =0xB6;
			Diagnostico_TX[1][berco].cData [2] =0xB6;
			Diagnostico_TX[1][berco].cData [1] =0xCE;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			Diagnostico_TX[2][berco].cData [7] =0xB6;
			Diagnostico_TX[2][berco].cData [6] =0xB6;
			Diagnostico_TX[2][berco].cData [5] =0xB6;
			Diagnostico_TX[2][berco].cData [4] =0xB6;
			Diagnostico_TX[2][berco].cData [3] =0xB6;
			Diagnostico_TX[2][berco].cData [2] =0xB6;
			Diagnostico_TX[2][berco].cData [1] =0xB6;
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[3][berco].cData [7] =0xB6;
			Diagnostico_TX[3][berco].cData [6] =0xB6;
			Diagnostico_TX[3][berco].cData [5] =0xB6;
			Diagnostico_TX[3][berco].cData [4] =0xB6;
			Diagnostico_TX[3][berco].cData [3] =0xB6;
			Diagnostico_TX[3][berco].cData [2] =0xB6;
			Diagnostico_TX[3][berco].cData [1] =0xB6;
			Diagnostico_TX[3][berco].cData [0] =0x23;
			
			Diagnostico_TX[4][berco].cData [7] =0x55;
			Diagnostico_TX[4][berco].cData [6] =0x55;
			Diagnostico_TX[4][berco].cData [5] =0x55;
			Diagnostico_TX[4][berco].cData [4] =0x55;
			Diagnostico_TX[4][berco].cData [3] =0x55;
			Diagnostico_TX[4][berco].cData [2] =0x55;
			Diagnostico_TX[4][berco].cData [1] =0x55;
			Diagnostico_TX[4][berco].cData [0] =0x24;
			
			Diagnostico_TX[5][berco].cData [7] =0x00;
			Diagnostico_TX[5][berco].cData [6] =0x00;
			Diagnostico_TX[5][berco].cData [5] =0x00;
			Diagnostico_TX[5][berco].cData [4] =0x00;
			Diagnostico_TX[5][berco].cData [3] =0x00;
			Diagnostico_TX[5][berco].cData [2] =0x55;
			Diagnostico_TX[5][berco].cData [1] =0x55;
			Diagnostico_TX[5][berco].cData [0] =0x25;
			status = EnviarEsperarRespDiag(OFF, berco);
			break;
			
			////////////////////////////////////////////////
			//18/06/2019
					///////////////////////////////////////////////////////	
		case LER_VPPS:	 //custumer diagnostic
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			Diagnostico_TX[0][berco].cData [5] = 0x00;
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xAB;  
			Diagnostico_TX[0][berco].cData [2] = 0xF0;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
            break;
	
		case ESC_VPPS:	   //EOL mode
		
			Diagnostico_TX[3][berco].cData [5] =bytes_envio_CAN_diag[13] [berco]; //data 13
			Diagnostico_TX[3][berco].cData [4] =bytes_envio_CAN_diag[12] [berco]; 
			Diagnostico_TX[3][berco].cData [3] =bytes_envio_CAN_diag[11] [berco]; 
			Diagnostico_TX[3][berco].cData [2] =bytes_envio_CAN_diag[10] [berco]; 
			Diagnostico_TX[3][berco].cData [1] =bytes_envio_CAN_diag[9]  [berco]; 
			Diagnostico_TX[3][berco].cData [0] =0x23;
			
			
			Diagnostico_TX[2][berco].cData [7] =bytes_envio_CAN_diag[8][berco];  
			Diagnostico_TX[2][berco].cData [6] =bytes_envio_CAN_diag[7][berco];  
			Diagnostico_TX[2][berco].cData [5] =bytes_envio_CAN_diag[6][berco];  
			Diagnostico_TX[2][berco].cData [4] =bytes_envio_CAN_diag[5][berco];  
			Diagnostico_TX[2][berco].cData [3] =bytes_envio_CAN_diag[4][berco];  
			Diagnostico_TX[2][berco].cData [2] =bytes_envio_CAN_diag[3][berco];  
			Diagnostico_TX[2][berco].cData [1] =bytes_envio_CAN_diag[2][berco];  
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			
			Diagnostico_TX[1][berco].cData [7] =bytes_envio_CAN_diag[1][berco];  
			Diagnostico_TX[1][berco].cData [6] =bytes_envio_CAN_diag[0][berco]; //data 0
			Diagnostico_TX[1][berco].cData [5] =0x0E;
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x1C;
			Diagnostico_TX[1][berco].cData [2] =0x40;
			Diagnostico_TX[1][berco].cData [1] =0x20;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			
			Diagnostico_TX[0][berco].cData [7] = 0xFF;
			Diagnostico_TX[0][berco].cData [6] = 0x02;
			Diagnostico_TX[0][berco].cData [5] = 0x20;
			Diagnostico_TX[0][berco].cData [4] = 0xFE; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x19; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			status = EnviarEsperarRespDiag(OFF, berco);
            break;
			
		case LER_DUNS:		//custumer diagnostic 
			Diagnostico_TX[0][berco].cData [7] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			Diagnostico_TX[0][berco].cData [5] = 0x00;
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0xB3;  
			Diagnostico_TX[0][berco].cData [2] = 0xF0;  
			Diagnostico_TX[0][berco].cData [1] = 0x22; 
			Diagnostico_TX[0][berco].cData [0] = 0x03;
			status = EnviarEsperarRespDiag(OFF, berco);
            break;
		case ESC_DUNS:  //EOL mode
			Diagnostico_TX[2][berco].cData [7] =bytes_envio_CAN_diag[8][berco];  
			Diagnostico_TX[2][berco].cData [6] =bytes_envio_CAN_diag[7][berco];  
			Diagnostico_TX[2][berco].cData [5] =bytes_envio_CAN_diag[6][berco];  
			Diagnostico_TX[2][berco].cData [4] =bytes_envio_CAN_diag[5][berco];  
			Diagnostico_TX[2][berco].cData [3] =bytes_envio_CAN_diag[4][berco];  
			Diagnostico_TX[2][berco].cData [2] =bytes_envio_CAN_diag[3][berco];  
			Diagnostico_TX[2][berco].cData [1] =bytes_envio_CAN_diag[2][berco];  
			Diagnostico_TX[2][berco].cData [0] =0x22;
			
			Diagnostico_TX[1][berco].cData [7] =bytes_envio_CAN_diag[1][berco];  
			Diagnostico_TX[1][berco].cData [6] =bytes_envio_CAN_diag[0][berco]; //data 0
			Diagnostico_TX[1][berco].cData [5] =0x09;
			Diagnostico_TX[1][berco].cData [4] =0x00;
			Diagnostico_TX[1][berco].cData [3] =0x3A;
			Diagnostico_TX[1][berco].cData [2] =0x40;
			Diagnostico_TX[1][berco].cData [1] =0x20;
			Diagnostico_TX[1][berco].cData [0] =0x21;
			
			
			Diagnostico_TX[0][berco].cData [7] = 0xFF;
			Diagnostico_TX[0][berco].cData [6] = 0x02;
			Diagnostico_TX[0][berco].cData [5] = 0x20;
			Diagnostico_TX[0][berco].cData [4] = 0xFE; 
			Diagnostico_TX[0][berco].cData [3] = 0x01;  
			Diagnostico_TX[0][berco].cData [2] = 0x31;  
			Diagnostico_TX[0][berco].cData [1] = 0x14; 
			Diagnostico_TX[0][berco].cData [0] = 0x10;
			status = EnviarEsperarRespDiag(OFF, berco);
		
            break;
			

			
	}

servico_diagnostico[berco] = DIAG_SERVICE_OFF;
return status;
}


//****************************** Fun��o  AbsTimeToString() ******************************
void AbsTimeToString(NCTYPE_ABS_TIME *time, char *TimeString)
{
//converts the absolute time obtained from ncReadMult into a string.

SYSTEMTIME	
	stime;
FILETIME		
	localftime;

	//////////////////////////////////////////////////
 	FileTimeToLocalFileTime((FILETIME *)(time), &localftime);
 	FileTimeToSystemTime(&localftime, &stime);
	  sprintf(TimeString, "%02d:%02d:%02d.%03d",
            stime.wHour, stime.wMinute, stime.wSecond, 
            stime.wMilliseconds);
	  
}


/********************************** AtualizaMensagensCAN ************************************************************/
int AtualizaMensagensCAN(int berco)
{
static double 
	timer_10_mili	[NUMERO_DE_BERCOS + 1]={0}, 
	timer_12_mili	[NUMERO_DE_BERCOS + 1]={0},   
	timer_14_mili	[NUMERO_DE_BERCOS + 1]={0},   
	timer_20_mili	[NUMERO_DE_BERCOS + 1]={0},   
	timer_30_mili	[NUMERO_DE_BERCOS + 1]={0},  
	timer_50_mili	[NUMERO_DE_BERCOS + 1]={0},  
	timer_100_mili	[NUMERO_DE_BERCOS + 1]={0},   
	timer_200_mili	[NUMERO_DE_BERCOS + 1]={0},   
	timer_500_mili	[NUMERO_DE_BERCOS + 1]={0},  
    timer_1000_mili	[NUMERO_DE_BERCOS + 1]={0},  
	timer_2000_mili	[NUMERO_DE_BERCOS + 1]={0};  
double 
	timeout	=2,
	tempo	=0,
	t		=0;
char 
	t_buf[50]	={0},
	resposta[50]={0}, 
	aux[10]		={0};
static int 
	cont_mens_diag=0 ;
int 
	j	=0,
	t_p	=0,
	i	=0,
	tg_can_2=0x50,
	m_val=0,
	status;   

	////////////////////////////////////////////
    SetBreakOnLibraryErrors(0); 
    ////////////////////////////////////////////
  
	strcpy(CAN_error_str[berco],"");  //clear error info
	
	status = RodaServicoDiagnostico(berco);
	if(status == 0)
		return 0;
	if(status < 0)
		return status;
	
	extend_frame_format[berco] = OFF;
	tempo = Timer();
	////////////////////// mens periodicas /////////////////////////////////
	if ((tempo - timer_10_mili[berco]) > CAN_TIMER_10)
	{
		timer_10_mili[berco] = tempo;
	}
	if ((tempo - timer_20_mili[berco]) > CAN_TIMER_20)
	{
		timer_20_mili[berco] = tempo;
	}
	if ((tempo - timer_12_mili[berco]) > CAN_TIMER_12)
	{
		status = Envia_can_TX_NI(TXRXHandle[berco],&EngSpd[berco], berco);
		status = Envia_can_TX_NI(TXRXHandle[berco],&PPEI_Engine_General_Status_1_0CB_M2[berco], berco);
		timer_12_mili[berco] = tempo;
	}
	if ((tempo - timer_30_mili[berco]) > CAN_TIMER_30)
	{
		status = Envia_can_TX_NI(TXRXHandle[berco],&SysPwrMd[berco], berco);     
		timer_30_mili[berco] = tempo;
	}
	if ((tempo - timer_50_mili[berco]) > CAN_TIMER_50)
	{
		timer_50_mili[berco] = tempo;
	}
	if ((tempo - timer_100_mili[berco]) > CAN_TIMER_100)
	{
		status = Envia_can_TX_NI(TXRXHandle[berco],&VehSpdAugDrun[berco], berco);
		status = Envia_can_TX_NI(TXRXHandle[berco],&VehSpdAugNDrun[berco], berco);  
		timer_100_mili[berco] = tempo;
	}
	if ((tempo - timer_200_mili[berco]) > CAN_TIMER_200)
	{
		status = Envia_can_TX_NI(TXRXHandle[berco],&Exterior_Lighting_HS[berco], berco);
		status = Envia_can_TX_NI(TXRXHandle[berco],&Airbag_Indications_19A_M[berco], berco);
		timer_200_mili[berco] = tempo; 
	}
	if (( tempo - timer_500_mili[berco]) > CAN_TIMER_500) 
	{	
		timer_500_mili[berco] = tempo;
		/*if(mostrar_comm_CAN == ON)  
		{
	     	ncRead( TXRXHandle[berco], sizeof(resp_cluster_0_1) , (void *)resp_cluster_0_1);  
	       // convert returned data into string
	        AbsTimeToString(&resp_cluster_0_1[0].Timestamp, &t_buf[0]);
	        strcpy(CharBuff_1,t_buf);
			sprintf (&t_buf[0], "    %8.8X   ", resp_cluster_0_1[0].dwID);
			strcat(CharBuff_1,t_buf);
			for (j=0; j<resp_cluster_0_1[0].DataLength; j++) 
	        {
		   		sprintf (t_buf, " %02X", resp_cluster_0_1[0].Data[j]); 
				strcat(CharBuff_1,t_buf);
	   		}
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, ATTR_CTRL_VAL, CharBuff_1);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, ATTR_CTRL_VAL, "\n");
		}*/
	} 					    
	if (( tempo - timer_1000_mili[berco]) > CAN_TIMER_1000) 
	{	
		
		status = Envia_can_TX_NI(TXRXHandle[berco],&Airbag_Indications_198_M[berco], berco);
		timer_1000_mili[berco] = tempo;
	} 					    
	if ((tempo - timer_2000_mili[berco]) > CAN_TIMER_2000)
	{
		timer_2000_mili[berco] = tempo;
	}
	Recebe_can_RX_NI(0, berco);//para esvaziar buffer CAN 

	
	
	
	return 0;
}

/********************************** RodaServicoDiagnostico ************************************************************/
// Retorna < 0 se houver erro
// Retorn 0 se tiver em modo diagn�stico e resposta OK
// Retorna 1 se n�o estiver em diagn�stico
int RodaServicoDiagnostico(int berco)
{
double 
	tempo;
int status = -1;	
	
	tempo = Timer();
	switch(modo_diagnostico[berco])		  
	{
		case NOT_DIAG: //not diag
			servico_diagnostico[berco] = DIAG_SERVICE_OFF ;
			break;
		
		case ENTRAR_DIAG_VISTEON:
			status = EntraModoEOL_GM(berco);
			if(status != SUCESSO)
				return -1;
			timer_test_pres[berco] = tempo;
			break;
		case ENTRAR_DIAG_CUSTOMER:
			status = EntraDiagCustomer_GM(berco);
			if(status != SUCESSO)
				return -1;
			timer_test_pres[berco] = tempo;
			break;
		case MANTER_DIAG:
			if (modo_diagnostico[berco] == MANTER_DIAG && ((tempo - timer_test_pres[berco]) > CAN_TIMER_TST_PRES)) //send test present
			{
				EnviaTestPresent(berco);
				timer_test_pres[berco] = tempo;
			}
			else
			{
				Recebe_can_RX_NI(0, berco);//para esvaziar buffer CAN 
			}
			break;
		
	    case SAIR_DIAG:
			break;
	}
	if (servico_diagnostico[berco] != DIAG_SERVICE_OFF && modo_diagnostico[berco] == MANTER_DIAG)
	{
		  status = Send_diag_commands(berco);
		  if(status < 0)
			  return status;
	}
	if(modo_diagnostico[berco] == MANTER_DIAG)
		  return 0;
	
	
return 1;
}


/********************************** EnviaTestPresent() ************************************************************/
void EnviaTestPresent(int berco)
{
int 
	status;

		extend_frame_format[berco] = ON;
		Tester_present[berco].cData [7] = 0x00; 
		Tester_present[berco].cData [6] = 0x00; 
		Tester_present[berco].cData [5] = 0x00; 
		Tester_present[berco].cData [4] = 0x00; 
		Tester_present[berco].cData [3] = 0x00; 
		Tester_present[berco].cData [2] = 0x00;//test present 
		Tester_present[berco].cData [1] = 0x3E; 
		Tester_present[berco].cData [0] = 0x02;
		status = EnviarEsperarRespDiag(ON, berco);
		
		if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
		   Resp_diagnostico_RX[0][berco].cData[0] == 0x02 && Resp_diagnostico_RX[0][berco].cData[1] == 0x7E &&
		   Resp_diagnostico_RX[0][berco].cData[2] == 0x00 && status == SUCESSO) //OK  
		{
		
			 modo_diagnostico[berco] = MANTER_DIAG;
		}
		else
		{
			modo_diagnostico[berco] 	= NOT_DIAG;
			servico_diagnostico[berco] 	= DIAG_SERVICE_OFF ;
			qual_diag_atual[berco]  	= NOT_DIAG;
			
		}	
}

/********************************** EntraDiagCustomer_GM() ************************************************************/
int EntraDiagCustomer_GM(int berco)
{
int status;

		extend_frame_format[berco] = ON;
		Diagnostico_TX[0][berco].cData [7] = 0x00; 
		Diagnostico_TX[0][berco].cData [6] = 0x00; 
		Diagnostico_TX[0][berco].cData [5] = 0x00; 
		Diagnostico_TX[0][berco].cData [4] = 0x00; 
		Diagnostico_TX[0][berco].cData [3] = 0x00; 
		Diagnostico_TX[0][berco].cData [2] = 0x03;//diagnostic Extended - Customer  
		Diagnostico_TX[0][berco].cData [1] = 0x10; 
		Diagnostico_TX[0][berco].cData [0] = 0x02;
		status=EnviarEsperarRespDiag(OFF, berco);
		
		if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
		   Resp_diagnostico_RX[0][berco].cData[0] == 0x06 && Resp_diagnostico_RX[0][berco].cData[1] == 0x50 &&
		   Resp_diagnostico_RX[0][berco].cData[2] == 0x03 && Resp_diagnostico_RX[0][berco].cData[3] == 0x00 &&
		   Resp_diagnostico_RX[0][berco].cData[4] == 0x32 && Resp_diagnostico_RX[0][berco].cData[5] == 0x01 &&
		   Resp_diagnostico_RX[0][berco].cData[6] == 0xF4 /*&& Resp_diagnostico_RX[0][berco].cData[7] == 0xAA*/ && status == SUCESSO) //OK send seed request 
		{
			Delay_thread(0.01);
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0x00; 
			Diagnostico_TX[0][berco].cData [2] = 0x0D;//seed request - Customer 
			Diagnostico_TX[0][berco].cData [1] = 0x27; 
			Diagnostico_TX[0][berco].cData [0] = 0x02;
			Delay_thread(0.1);
			status=EnviarEsperarRespDiag(OFF, berco);
				
			if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
			   Resp_diagnostico_RX[0][berco].cData[0] == 0x10 && Resp_diagnostico_RX[0][berco].cData[1] == 0x21 &&
			   Resp_diagnostico_RX[0][berco].cData[2] == 0x67 && Resp_diagnostico_RX[0][berco].cData[3] == 0x0D &&
			   Resp_diagnostico_RX[0][berco].cData[4] == 0xFF && status == SUCESSO) //OK send key
			   {
					Diagnostico_TX[0][berco].cData [7] = 0x00; 
					Diagnostico_TX[0][berco].cData [6] = 0x00; 
					Diagnostico_TX[0][berco].cData [5] = 0x00; 
					Diagnostico_TX[0][berco].cData [4] = 0x00; 
					Diagnostico_TX[0][berco].cData [3] = 0x0E;//key - CUSTOMER(1)
					Diagnostico_TX[0][berco].cData [2] = 0x27;
					Diagnostico_TX[0][berco].cData [1] = 0x0E;
					Diagnostico_TX[0][berco].cData [0] = 0x10;
					
					Diagnostico_TX[1][berco].cData [7] = 0x00; 
					Diagnostico_TX[1][berco].cData [6] = 0x00; 
					Diagnostico_TX[1][berco].cData [5] = 0x00; 
					Diagnostico_TX[1][berco].cData [4] = 0x00; 
					Diagnostico_TX[1][berco].cData [3] = 0x00;//key - CUSTOMER(2)
					Diagnostico_TX[1][berco].cData [2] = 0x00;
					Diagnostico_TX[1][berco].cData [1] = 0x00;
					Diagnostico_TX[1][berco].cData [0] = 0x21;
					
					Diagnostico_TX[2][berco].cData [7] = 0x00; 
					Diagnostico_TX[2][berco].cData [6] = 0x00; 
					Diagnostico_TX[2][berco].cData [5] = 0x00; 
					Diagnostico_TX[2][berco].cData [4] = 0x00; 
					Diagnostico_TX[2][berco].cData [3] = 0x00;//key - CUSTOMER(3)
					Diagnostico_TX[2][berco].cData [2] = 0x00;
					Diagnostico_TX[2][berco].cData [1] = 0x00;
					Diagnostico_TX[2][berco].cData [0] = 0x22;
					Delay_thread(0.01);
					status=EnviarEsperarRespDiag(OFF, berco);
			     
					if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
					   Resp_diagnostico_RX[0][berco].cData[0] == 0x02 && Resp_diagnostico_RX[0][berco].cData[1] == 0x67 &&
					   Resp_diagnostico_RX[0][berco].cData[2] == 0x0E && status == SUCESSO) 
				    {
				   		modo_diagnostico[berco] = MANTER_DIAG;
						qual_diag_atual[berco] 	= EM_DIAG_CUSTOMER;
				    }
					else
					{
						MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico CUSTOMER - KEY ERROR");
					}
			}
			else
			{
				MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico CUSTOMER - SEED ERROR");
			}
		}
		else
		{
			MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico Customer - EOL ERROR(02 10 03)");
		}
		if(modo_diagnostico[berco] != MANTER_DIAG || status != SUCESSO)
		{
			modo_diagnostico[berco] 	= NOT_DIAG; 
			qual_diag_atual[berco]  	= NOT_DIAG;
			servico_diagnostico[berco] 	= DIAG_SERVICE_OFF ;
			MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico Customer");
		   	return -1;
		}
		
return SUCESSO;
}

/********************************** EntraModoEOL_GM() ************************************************************/
int EntraModoEOL_GM(int berco)
{
int status;

		extend_frame_format[berco] = ON;
		Diagnostico_TX[0][berco].cData [7] = 0x00; 
		Diagnostico_TX[0][berco].cData [6] = 0x00; 
		Diagnostico_TX[0][berco].cData [5] = 0x00; 
		Diagnostico_TX[0][berco].cData [4] = 0x00; 
		Diagnostico_TX[0][berco].cData [3] = 0x00; 
		Diagnostico_TX[0][berco].cData [2] = 0x60;//diagnostic session Visteon  
		Diagnostico_TX[0][berco].cData [1] = 0x10; 
		Diagnostico_TX[0][berco].cData [0] = 0x02;
		status=EnviarEsperarRespDiag(OFF, berco);
		
		if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
		   Resp_diagnostico_RX[0][berco].cData[0] == 0x06 && Resp_diagnostico_RX[0][berco].cData[1] == 0x50 &&
		   Resp_diagnostico_RX[0][berco].cData[2] == 0x60 && Resp_diagnostico_RX[0][berco].cData[3] == 0x00 &&
		   Resp_diagnostico_RX[0][berco].cData[4] == 0x32 && Resp_diagnostico_RX[0][berco].cData[5] == 0x01 &&
		   Resp_diagnostico_RX[0][berco].cData[6] == 0xF4 && /*Resp_diagnostico_RX[0][berco].cData[7] == 0xAA &&*/ status == SUCESSO) //OK send seed request 
		{
			
			Diagnostico_TX[0][berco].cData [7] = 0x00; 
			Diagnostico_TX[0][berco].cData [6] = 0x00; 
			Diagnostico_TX[0][berco].cData [5] = 0x00; 
			Diagnostico_TX[0][berco].cData [4] = 0x00; 
			Diagnostico_TX[0][berco].cData [3] = 0x00; 
			Diagnostico_TX[0][berco].cData [2] = 0x61;//seed request  
			Diagnostico_TX[0][berco].cData [1] = 0x27; 
			Diagnostico_TX[0][berco].cData [0] = 0x02;
			status=EnviarEsperarRespDiag(OFF, berco);
				
			if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
			   Resp_diagnostico_RX[0][berco].cData[0] == 0x07 && Resp_diagnostico_RX[0][berco].cData[1] == 0x67 &&
			   Resp_diagnostico_RX[0][berco].cData[2] == 0x61 && Resp_diagnostico_RX[0][berco].cData[3] == 0x12 &&
			   Resp_diagnostico_RX[0][berco].cData[4] == 0x34 && Resp_diagnostico_RX[0][berco].cData[5] == 0x56 &&
			   Resp_diagnostico_RX[0][berco].cData[6] == 0x78 && Resp_diagnostico_RX[0][berco].cData[7] == 0x90 && status == SUCESSO) //OK send key
			 {
				    Diagnostico_TX[0][berco].cData [7] = 0xC5; 
					Diagnostico_TX[0][berco].cData [6] = 0x87; 
					Diagnostico_TX[0][berco].cData [5] = 0xA9; 
					Diagnostico_TX[0][berco].cData [4] = 0xCB; 
					Diagnostico_TX[0][berco].cData [3] = 0xED; 
					Diagnostico_TX[0][berco].cData [2] = 0x62;//key 
					Diagnostico_TX[0][berco].cData [1] = 0x27; 
					Diagnostico_TX[0][berco].cData [0] = 0x07;
					status=EnviarEsperarRespDiag(OFF, berco);
			     
					if(Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
					   Resp_diagnostico_RX[0][berco].cData[0] == 0x02 && Resp_diagnostico_RX[0][berco].cData[1] == 0x67 &&
					   Resp_diagnostico_RX[0][berco].cData[2] == 0x62 /*&& Resp_diagnostico_RX[0][berco].cData[3] == 0xAA &&
					   Resp_diagnostico_RX[0][berco].cData[4] == 0xAA && Resp_diagnostico_RX[0][berco].cData[5] == 0xAA &&
					   Resp_diagnostico_RX[0][berco].cData[6] == 0xAA && Resp_diagnostico_RX[0][berco].cData[7] == 0xAA */&& status == SUCESSO) 
					{
						modo_diagnostico[berco] = MANTER_DIAG;
						qual_diag_atual[berco] 	= EM_DIAG_VISTEON;
						atual_counts_taco[berco] = 0;
						atual_counts_velo[berco] = 0;
					}
					else
					{
						if(modo_manual)
							MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico EOL - Visteon- KEY ERROR");
					}
			 }
			 else
			 {
				 if(modo_manual)
					MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico EOL - Visteon- SEED ERROR");
			 }
		}
		else
		{
			if(modo_manual)
				MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico EOL - Visteon- EOL ERROR(02 10 60)");
		}
		if(modo_diagnostico[berco] != MANTER_DIAG || status != SUCESSO)
		{
			modo_diagnostico[berco] 	= NOT_DIAG; 
			qual_diag_atual[berco]  	= NOT_DIAG;
			servico_diagnostico[berco] 	= DIAG_SERVICE_OFF ;
			if(modo_manual)
				MessagePopup ("Falha ao entrar em Diag Mode", "Falha ao tentar entrar no modo Diagn�stico EOL - Visteon");
		   	return -1;
		}
		
return SUCESSO;
}

/********************************** Esc_Digital_Output() ************************************************************/
int Esc_Digital_Output(INPUT_CLUSTER input, int valor, int berco)
{
int 
	status = -1,
	res = 0;
double
	timeout = 1.0,
	t;
 SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
 
 	
	if(valor < 0 && valor > 1)
	{
		MessagePopup ("Setup incorreto - valor fora do range",
		  "Falha ao tentar Escrever na Saida Digital - Vor a ser escrito est� fora do Range");
		return -1;
	}
	
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------	 
	switch(input)
	{
		case FCA_OUT:
			qual_servico_diag 	= ESC_FCA_OUT_DIAG;
			diag_output[berco].out_fca	= valor;
			break;
		case FCA_DN_OUT:
			qual_servico_diag 	= ESC_FCA_DN_OUT_DIAG;
			diag_output[berco].out_fca_dn	= valor*2;
			break;
		case PASSIV_START_RUN_OUT:
			qual_servico_diag 	= ESC_PASS_START_RUN_OUT_DIAG;
			diag_output[berco].out_passiv_start_run = valor*4;
			break;
		case PASSIV_START_ACC_OUT:
			qual_servico_diag 	= ESC_PASS_START_ACC_OUT_DIAG;
			diag_output[berco].out_passiv_start_acc = valor*8;
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar ler Entradas Anal�gicas - Fun��o inexistente");
			return Indica_comm_CAN_Not_OK();
	}		 
	Diagnostico_TX[0][berco].cData [6] = diag_output[berco].out_fca;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_output[berco].out_fca_dn;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_output[berco].out_passiv_start_run;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_output[berco].out_passiv_start_acc;
	
	t = Timer();
	servico_diagnostico[berco] = qual_servico_diag;
	while(servico_diagnostico[berco] == qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x07 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F)
	{
		switch(input)
		{
			case FCA_OUT:
				diag_output[berco].out_fca	= 0xFF; //sinaliza erro
				break;
			case FCA_DN_OUT:
				diag_output[berco].out_fca_dn	= 0xFF; //sinaliza erro 
				break;
			case PASSIV_START_RUN_OUT:
				diag_output[berco].out_passiv_start_run = 0xFF; //sinaliza erro 
				break;
			case PASSIV_START_ACC_OUT:
				diag_output[berco].out_passiv_start_acc = 0xFF; //sinaliza erro 
				break;
		}		 
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	
return SUCESSO; 
}
/********************************** Ler_Registro_status() ************************************************************/
int Ler_Registro_status(REGISTRO_CLUSTER registro, int *valor, int berco)
{
int 
	status = -1,
	byte_retorn_0 		= 0x05	, // valor que deve retornar no byte 0
	byte_retorn_serv 	= 1		, // byte onde est� resposta do servi�o
	valor_resposta_OK   = 0x62	, // valor resposta OK ao servi�o 0x22
	i,
	delay_comand = ON;
double
	timeout = 1.0,
	t;
 SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
 unsigned long
	res = 0, res2 = 0;
	 
	//--------------------------------------------------------------	 
	switch(registro)
	{
		case CRYSTAL_VERIF:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON) < 0)
				return status;
			qual_servico_diag 	= LER_CRYSTAL_VERIF;
			byte_retorn_0		= 0x06;
			byte_retorn_serv	= 1;
			break;
		case MEC_STATUS:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON) < 0)
				return status;
			qual_servico_diag 	= LER_MEC_STATUS;
			byte_retorn_0		= 0x04;
			byte_retorn_serv	= 1;
			break;
		case PN_STATUS:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON) < 0)
				return status;
			qual_servico_diag 	= LER_PN_STATUS;
			byte_retorn_0		= 0x07;
			byte_retorn_serv	= 1;
			break;
		case BASE_STATUS:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON) < 0)
				return status;
			qual_servico_diag 	= LER_BASE_STATUS;
			byte_retorn_0		= 0x07;
			byte_retorn_serv	= 1;
			break;
		case MTC_STATUS:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON) < 0)
				return status;
			ResetaBytesResposta_CAN(berco);
			qual_servico_diag 	= LER_MTC_STATUS;
			byte_retorn_0		= 0x10;
			byte_retorn_serv	= 2;
			break;
		case SW_STATUS:
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON) < 0)
				return status;
			qual_servico_diag 	= LER_SW_STATUS;
			byte_retorn_0		= 0x10;
			byte_retorn_serv	= 2;
			break;
		case CLUSTER_INFO:
			if(modo_manual)
				delay_comand = OFF;
		 	if(status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, delay_comand) < 0)
				return status;
			qual_servico_diag 	= LER_CLUSTER_INFO;
			byte_retorn_0		= 0x10;
			byte_retorn_serv	= 2;
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar ler Registro do Cluster - Fun��o inexistente");
			return -1;
	}		 
	t = Timer();
	servico_diagnostico[berco] = qual_servico_diag;
	while(servico_diagnostico[berco] == qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != byte_retorn_0 || Resp_diagnostico_RX[0][berco].cData[byte_retorn_serv] != valor_resposta_OK)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	
	*valor = 0;
	switch(registro)
	{
		case CRYSTAL_VERIF:
			res = Resp_diagnostico_RX[0][berco].cData[4];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[5];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[6];
			*valor = res;
			break;
		case MEC_STATUS:
			res = Resp_diagnostico_RX[0][berco].cData[4];
			*valor = res;
			break;
		case PN_STATUS:
		case BASE_STATUS:
			res = Resp_diagnostico_RX[0][berco].cData[4];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[5];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[6];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[7];
			*valor = res;
			break;
		case MTC_STATUS:
			bytes_resp_CAN_diag[0][berco] = Resp_diagnostico_RX[0][berco].cData[5];
			bytes_resp_CAN_diag[1][berco] = Resp_diagnostico_RX[0][berco].cData[6];
			bytes_resp_CAN_diag[2][berco] = Resp_diagnostico_RX[0][berco].cData[7];
			
			bytes_resp_CAN_diag[3][berco] = Resp_diagnostico_RX[1][berco].cData[1];
			bytes_resp_CAN_diag[4][berco] = Resp_diagnostico_RX[1][berco].cData[2];
			bytes_resp_CAN_diag[5][berco] = Resp_diagnostico_RX[1][berco].cData[3];
			bytes_resp_CAN_diag[6][berco] = Resp_diagnostico_RX[1][berco].cData[4];
			bytes_resp_CAN_diag[7][berco] = Resp_diagnostico_RX[1][berco].cData[5];
			bytes_resp_CAN_diag[8][berco] = Resp_diagnostico_RX[1][berco].cData[6];
			bytes_resp_CAN_diag[9][berco] = Resp_diagnostico_RX[1][berco].cData[7];
			
			bytes_resp_CAN_diag[10][berco]= Resp_diagnostico_RX[2][berco].cData[1];
			bytes_resp_CAN_diag[11][berco]= Resp_diagnostico_RX[2][berco].cData[2];
			bytes_resp_CAN_diag[12][berco]= Resp_diagnostico_RX[2][berco].cData[3];
			bytes_resp_CAN_diag[13][berco]= Resp_diagnostico_RX[2][berco].cData[4];
			bytes_resp_CAN_diag[14][berco]= Resp_diagnostico_RX[2][berco].cData[5];
			bytes_resp_CAN_diag[15][berco]= Resp_diagnostico_RX[2][berco].cData[6];
			break;
		case SW_STATUS:
		case CLUSTER_INFO:
			res = Resp_diagnostico_RX[14][berco].cData[7];   //rx[2]
			res = res << 16;
			res2 = Resp_diagnostico_RX[15][berco].cData[1];
			res2 = res2 << 8;
			res = res + res2;
			res = res + Resp_diagnostico_RX[15][berco].cData[2];
			*valor = res;
			if(registro == CLUSTER_INFO)
				ReportClusterInfo(berco);
			break;
	}		 
    
return SUCESSO; 
}

/********************************** ReportClusterInfo() ************************************************************/
void ReportClusterInfo(int berco)
{
int 
	i,
	tmp;
unsigned long
	valor;

	for(i=0; i<MAX_TAMAN_RESP_CLUSTER; i++)
	{
		bytes_resp_CAN_diag[i][berco] = 0;
	}
	bytes_resp_CAN_diag[0][berco] = Resp_diagnostico_RX[0][berco].cData[5];//tamanho resposta			- 2 bytes
	bytes_resp_CAN_diag[1][berco] = Resp_diagnostico_RX[0][berco].cData[6]; 
	bytes_resp_CAN_diag[2][berco] = Resp_diagnostico_RX[0][berco].cData[7];//Table Type = 2			- 1 byte
	
	bytes_resp_CAN_diag[3][berco] = Resp_diagnostico_RX[1][berco].cData[1];//NVM_START_ADDRESS 		- 4 bytes
	bytes_resp_CAN_diag[4][berco] = Resp_diagnostico_RX[1][berco].cData[2];
	bytes_resp_CAN_diag[5][berco] = Resp_diagnostico_RX[1][berco].cData[3];
	bytes_resp_CAN_diag[6][berco] = Resp_diagnostico_RX[1][berco].cData[4];
	bytes_resp_CAN_diag[7][berco] = Resp_diagnostico_RX[1][berco].cData[5];//NVM_LENGTH - 2 bytes
	bytes_resp_CAN_diag[8][berco] = Resp_diagnostico_RX[1][berco].cData[6];
	bytes_resp_CAN_diag[9][berco] = Resp_diagnostico_RX[1][berco].cData[7];//I/O_REGISTER_ADDRESS 	- 4 bytes
	
	bytes_resp_CAN_diag[10][berco] = Resp_diagnostico_RX[2][berco].cData[1];
	bytes_resp_CAN_diag[11][berco] = Resp_diagnostico_RX[2][berco].cData[2];
	bytes_resp_CAN_diag[12][berco] = Resp_diagnostico_RX[2][berco].cData[3];
	bytes_resp_CAN_diag[13][berco] = Resp_diagnostico_RX[2][berco].cData[4];//ROM_MAJOR in ROM  		- 1 byte
	bytes_resp_CAN_diag[14][berco] = Resp_diagnostico_RX[2][berco].cData[5];//ROM_MINOR in ROM  		- 1 byte
	bytes_resp_CAN_diag[15][berco] = Resp_diagnostico_RX[2][berco].cData[6];//PTR_NVM_SPEED_TABLE 	- 4 bytes
	bytes_resp_CAN_diag[16][berco] = Resp_diagnostico_RX[2][berco].cData[7];
	
	bytes_resp_CAN_diag[17][berco] = Resp_diagnostico_RX[3][berco].cData[1];
	bytes_resp_CAN_diag[18][berco] = Resp_diagnostico_RX[3][berco].cData[2];
	bytes_resp_CAN_diag[19][berco] = Resp_diagnostico_RX[3][berco].cData[3];//NVM_SPEED_SIZE 			- 1 byte
	bytes_resp_CAN_diag[20][berco] = Resp_diagnostico_RX[3][berco].cData[4];//NUMBER_OF_SPEED_TABLES 	- 1 byte
	bytes_resp_CAN_diag[21][berco] = Resp_diagnostico_RX[3][berco].cData[5];//PTR_NVM_TACHO_TABLE 	- 4 bytes
	bytes_resp_CAN_diag[22][berco] = Resp_diagnostico_RX[3][berco].cData[6];
	bytes_resp_CAN_diag[23][berco] = Resp_diagnostico_RX[3][berco].cData[7];

	bytes_resp_CAN_diag[24][berco] = Resp_diagnostico_RX[4][berco].cData[1];
	bytes_resp_CAN_diag[25][berco] = Resp_diagnostico_RX[4][berco].cData[2];//NVM_TACHO_SIZE			- 1 byte
	bytes_resp_CAN_diag[26][berco] = Resp_diagnostico_RX[4][berco].cData[3];//NUMBER_OF_TACH_TABLES   - 1 byte
	bytes_resp_CAN_diag[27][berco] = Resp_diagnostico_RX[4][berco].cData[4];//PTR_NVM_FUEL_TABLE 		- 4 bytes
	bytes_resp_CAN_diag[28][berco] = Resp_diagnostico_RX[4][berco].cData[5];
	bytes_resp_CAN_diag[29][berco] = Resp_diagnostico_RX[4][berco].cData[6];
	bytes_resp_CAN_diag[30][berco] = Resp_diagnostico_RX[4][berco].cData[7];

	bytes_resp_CAN_diag[31][berco] = Resp_diagnostico_RX[5][berco].cData[1];//NVM_FUEL_SIZE			- 1 byte
	bytes_resp_CAN_diag[32][berco] = Resp_diagnostico_RX[5][berco].cData[2];//NUMBER_OF_FUEL_TABLES	- 1 byte
	bytes_resp_CAN_diag[33][berco] = Resp_diagnostico_RX[5][berco].cData[3];//PTR_NVM_TEMP_TABLE		- 4 bytes
	bytes_resp_CAN_diag[34][berco] = Resp_diagnostico_RX[5][berco].cData[4];
	bytes_resp_CAN_diag[35][berco] = Resp_diagnostico_RX[5][berco].cData[5];
	bytes_resp_CAN_diag[36][berco] = Resp_diagnostico_RX[5][berco].cData[6];
	bytes_resp_CAN_diag[37][berco] = Resp_diagnostico_RX[5][berco].cData[7];//NVM_TEMP_SIZE			- 1 byte 
					
	bytes_resp_CAN_diag[38][berco] = Resp_diagnostico_RX[6][berco].cData[1];//NUMBER_OF_TEMP_TABLES	- 1 byte
	bytes_resp_CAN_diag[39][berco] = Resp_diagnostico_RX[6][berco].cData[2];//PTR_NVM_OIL_TABLE		- 4 bytes
	bytes_resp_CAN_diag[40][berco] = Resp_diagnostico_RX[6][berco].cData[3];
	bytes_resp_CAN_diag[41][berco] = Resp_diagnostico_RX[6][berco].cData[4];
	bytes_resp_CAN_diag[42][berco] = Resp_diagnostico_RX[6][berco].cData[5];
	bytes_resp_CAN_diag[43][berco] = Resp_diagnostico_RX[6][berco].cData[6];//NVM_OIL_SIZE			- 1 byte
	bytes_resp_CAN_diag[44][berco] = Resp_diagnostico_RX[6][berco].cData[7];//NUMBER_OF_OIL_TABLES	- 1 byte 

	bytes_resp_CAN_diag[45][berco] = Resp_diagnostico_RX[7][berco].cData[1];//PTR_NVM_VOLT_TABLE		- 4 bytes
	bytes_resp_CAN_diag[46][berco] = Resp_diagnostico_RX[7][berco].cData[2];
	bytes_resp_CAN_diag[47][berco] = Resp_diagnostico_RX[7][berco].cData[3];
	bytes_resp_CAN_diag[48][berco] = Resp_diagnostico_RX[7][berco].cData[4];
	bytes_resp_CAN_diag[49][berco] = Resp_diagnostico_RX[7][berco].cData[5];//NVM_VOLT_SIZE			- 1 byte
	bytes_resp_CAN_diag[50][berco] = Resp_diagnostico_RX[7][berco].cData[6];//NUMBER_OF_VOLT_TABLES	- 1 byte
	bytes_resp_CAN_diag[51][berco] = Resp_diagnostico_RX[7][berco].cData[7];//PTR_NVM_EXTRA1_TABLE	- 4 bytes 

	bytes_resp_CAN_diag[52][berco] = Resp_diagnostico_RX[8][berco].cData[1];
	bytes_resp_CAN_diag[53][berco] = Resp_diagnostico_RX[8][berco].cData[2];
	bytes_resp_CAN_diag[54][berco] = Resp_diagnostico_RX[8][berco].cData[3];
	bytes_resp_CAN_diag[55][berco] = Resp_diagnostico_RX[8][berco].cData[4];//NVM_EXTRA1_SIZE     	- 1 byte
	bytes_resp_CAN_diag[56][berco] = Resp_diagnostico_RX[8][berco].cData[5];//NUMBER_OF_EXTRA1_TABLES	- 1 byte
	bytes_resp_CAN_diag[57][berco] = Resp_diagnostico_RX[8][berco].cData[6];//PTR_NVM_EXTRA2_TABLE	- 4 byte
	bytes_resp_CAN_diag[58][berco] = Resp_diagnostico_RX[8][berco].cData[7];

	bytes_resp_CAN_diag[59][berco] = Resp_diagnostico_RX[9][berco].cData[1];
	bytes_resp_CAN_diag[60][berco] = Resp_diagnostico_RX[9][berco].cData[2];
	bytes_resp_CAN_diag[61][berco] = Resp_diagnostico_RX[9][berco].cData[3];//NVM_EXTRA2_SIZE		- 1 byte
	bytes_resp_CAN_diag[62][berco] = Resp_diagnostico_RX[9][berco].cData[4];//NUMBER_OF_EXTRA2_TABLES- 1 byte
	bytes_resp_CAN_diag[63][berco] = Resp_diagnostico_RX[9][berco].cData[5];//LAST_NVM_CONSTANT_ADDRESS- 4 bytes
	bytes_resp_CAN_diag[64][berco] = Resp_diagnostico_RX[9][berco].cData[6];
	bytes_resp_CAN_diag[65][berco] = Resp_diagnostico_RX[9][berco].cData[7]; 

	bytes_resp_CAN_diag[66][berco] = Resp_diagnostico_RX[10][berco].cData[1];
	bytes_resp_CAN_diag[67][berco] = Resp_diagnostico_RX[10][berco].cData[2];//NVM_CHECK SUM			- 2 bytes
	bytes_resp_CAN_diag[68][berco] = Resp_diagnostico_RX[10][berco].cData[3];  
	bytes_resp_CAN_diag[69][berco] = Resp_diagnostico_RX[10][berco].cData[4];//PTR_NVM_ODO_TABLE		- 4 bytes
	bytes_resp_CAN_diag[70][berco] = Resp_diagnostico_RX[10][berco].cData[5];
	bytes_resp_CAN_diag[71][berco] = Resp_diagnostico_RX[10][berco].cData[6];
	bytes_resp_CAN_diag[72][berco] = Resp_diagnostico_RX[10][berco].cData[7]; 

	bytes_resp_CAN_diag[73][berco] = Resp_diagnostico_RX[11][berco].cData[1];//NVM_ODO_SIZE			- 1 byte
	bytes_resp_CAN_diag[74][berco] = Resp_diagnostico_RX[11][berco].cData[2];//ODO_DATA_SET_TYPE		- 1 byte
	bytes_resp_CAN_diag[75][berco] = Resp_diagnostico_RX[11][berco].cData[3];//PTR_B&A_DATA_TABLE		- 4 bytes  
	bytes_resp_CAN_diag[76][berco] = Resp_diagnostico_RX[11][berco].cData[4];
	bytes_resp_CAN_diag[77][berco] = Resp_diagnostico_RX[11][berco].cData[5];
	bytes_resp_CAN_diag[78][berco] = Resp_diagnostico_RX[11][berco].cData[6];
	bytes_resp_CAN_diag[79][berco] = Resp_diagnostico_RX[11][berco].cData[7];//NVM_B&A_SIZE			- 1 byte 
	
	bytes_resp_CAN_diag[80][berco] = Resp_diagnostico_RX[12][berco].cData[1];//PTR_EXTRA_TABLE		- 4 bytes
	bytes_resp_CAN_diag[81][berco] = Resp_diagnostico_RX[12][berco].cData[2];
	bytes_resp_CAN_diag[82][berco] = Resp_diagnostico_RX[12][berco].cData[3];
	bytes_resp_CAN_diag[83][berco] = Resp_diagnostico_RX[12][berco].cData[4];
	bytes_resp_CAN_diag[84][berco] = Resp_diagnostico_RX[12][berco].cData[5];//NVM_EXTRA_SIZE			- 1 byte                               
	bytes_resp_CAN_diag[85][berco] = Resp_diagnostico_RX[12][berco].cData[6];//Speedo gauge offset	- 1 byte                               
	bytes_resp_CAN_diag[86][berco] = Resp_diagnostico_RX[12][berco].cData[7];//Tacho gauge offset		- 1 byte                               
														     
	bytes_resp_CAN_diag[87][berco] = Resp_diagnostico_RX[13][berco].cData[1];//Fuel gauge offset		- 1 byte                               
	bytes_resp_CAN_diag[88][berco] = Resp_diagnostico_RX[13][berco].cData[2];//Temp gauge offset		- 1 byte                               
	bytes_resp_CAN_diag[89][berco] = Resp_diagnostico_RX[13][berco].cData[3];//Oil gauge offset		- 1 byte                               
	bytes_resp_CAN_diag[90][berco] = Resp_diagnostico_RX[13][berco].cData[4];//Volt gauge offset		- 1 byte                                                                 
	bytes_resp_CAN_diag[91][berco] = Resp_diagnostico_RX[13][berco].cData[5];//Extra1 gauge offset	- 1 byte                               
	bytes_resp_CAN_diag[92][berco] = Resp_diagnostico_RX[13][berco].cData[6];//Extra2 gauge offset	- 1 byte                               
	bytes_resp_CAN_diag[93][berco] = Resp_diagnostico_RX[13][berco].cData[7];//PTR_PATS_DATA_TABLE	- 4 byte                               
														                                 
	bytes_resp_CAN_diag[94][berco] = Resp_diagnostico_RX[14][berco].cData[1];                                                                
	bytes_resp_CAN_diag[95][berco] = Resp_diagnostico_RX[14][berco].cData[2];                                                                
	bytes_resp_CAN_diag[96][berco] = Resp_diagnostico_RX[14][berco].cData[3];                                                                
	bytes_resp_CAN_diag[97][berco] = Resp_diagnostico_RX[14][berco].cData[4];//NVM_PATS_SIZE			- 2 bytes                                                                  
	bytes_resp_CAN_diag[98][berco] = Resp_diagnostico_RX[14][berco].cData[5];                                                                
	bytes_resp_CAN_diag[99][berco] = Resp_diagnostico_RX[14][berco].cData[6];//PLL_LOCK_ERROR			- 1 byte                               
	bytes_resp_CAN_diag[100][berco]= Resp_diagnostico_RX[14][berco].cData[7];//ROM_MAJOR in NVM		- 1 byte                               
														                                 
	bytes_resp_CAN_diag[101][berco]= Resp_diagnostico_RX[15][berco].cData[1];//ROM_MINOR in NVM		- 1 byte                               
	bytes_resp_CAN_diag[102][berco]= Resp_diagnostico_RX[15][berco].cData[2];//NVM revision level		- 1 byte                               
	bytes_resp_CAN_diag[103][berco]= Resp_diagnostico_RX[15][berco].cData[3];//MFG_INFO_TABLE			- 4 bytes                                                                
	bytes_resp_CAN_diag[104][berco]= Resp_diagnostico_RX[15][berco].cData[4];                            
	bytes_resp_CAN_diag[105][berco]= Resp_diagnostico_RX[15][berco].cData[5];                                                                
	bytes_resp_CAN_diag[106][berco]= Resp_diagnostico_RX[15][berco].cData[6];                                                                
	bytes_resp_CAN_diag[107][berco]= Resp_diagnostico_RX[15][berco].cData[7];//MFG_INFO_SIZE			- 1 byte                                                                
														                                  
	bytes_resp_CAN_diag[108][berco]= Resp_diagnostico_RX[16][berco].cData[1];//Number microcontrollers- 1 byte                               
	bytes_resp_CAN_diag[109][berco]= Resp_diagnostico_RX[16][berco].cData[2];//Micro 1 Type			- 1 byte                               
	bytes_resp_CAN_diag[110][berco]= Resp_diagnostico_RX[16][berco].cData[3];//Micro 1 EEPROM Type	- 1 bytes                              
	bytes_resp_CAN_diag[111][berco]= Resp_diagnostico_RX[16][berco].cData[4];//resp_cluster_17_1		- 1 byte                                                                  
	bytes_resp_CAN_diag[112][berco]= Resp_diagnostico_RX[16][berco].cData[5];//Micro 1 Number of Pins - 2 bytes                              
	bytes_resp_CAN_diag[113][berco]= Resp_diagnostico_RX[16][berco].cData[6];                             
	bytes_resp_CAN_diag[114][berco]= Resp_diagnostico_RX[16][berco].cData[7];//Micro 2 Type = 0		- 1 byte                                                                
														                                  
	bytes_resp_CAN_diag[115][berco]= Resp_diagnostico_RX[17][berco].cData[1];//Micro 2 EEPROM Type = 0- 1 byte                               
	bytes_resp_CAN_diag[116][berco]= Resp_diagnostico_RX[17][berco].cData[2];//Micr 2 Flash Mem Type=0- 1 byte                               
	bytes_resp_CAN_diag[117][berco]= Resp_diagnostico_RX[17][berco].cData[3];//Micr 2 Number of Pins=0- 2 bytes                              
	bytes_resp_CAN_diag[118][berco]= Resp_diagnostico_RX[17][berco].cData[4];                                                                
	bytes_resp_CAN_diag[119][berco]= Resp_diagnostico_RX[17][berco].cData[5];//NVM Diagnostic Routine Block Size = 256 (Note 2) - 2 bytes                                                                
	bytes_resp_CAN_diag[120][berco]= Resp_diagnostico_RX[17][berco].cData[6];    
	bytes_resp_CAN_diag[121][berco]= Resp_diagnostico_RX[17][berco].cData[7];                                                              
														                                                                 
											                                                                 
	valor = bytes_resp_CAN_diag[15][berco];
	valor = valor << 24;
	tmp   = bytes_resp_CAN_diag[16][berco];
	tmp   = tmp << 16;
	valor = valor + tmp;
	tmp   = bytes_resp_CAN_diag[17][berco];
	tmp   = tmp << 8;
	valor = valor + tmp;
	valor = valor + bytes_resp_CAN_diag[18][berco];
	add_table_speed[berco] 	  = valor;
	add_CAN_min_speed[berco]  = add_table_speed[berco];
	add_CAN_max_speed[berco]  = add_table_speed[berco] + 2;
	add_inp_pt_0_speed[berco] = add_table_speed[berco] + 4;
	add_out_pt_0_speed[berco] = add_table_speed[berco] + 6;
	add_inp_pt_1_speed[berco] = add_table_speed[berco] + 8;
	add_out_pt_1_speed[berco] = add_table_speed[berco] + 10;
	add_inp_pt_2_speed[berco] = add_table_speed[berco] + 12;
	add_out_pt_2_speed[berco] = add_table_speed[berco] + 14;
	add_inp_pt_3_speed[berco] = add_table_speed[berco] + 16;
	add_out_pt_3_speed[berco] = add_table_speed[berco] + 18;
	add_inp_pt_4_speed[berco] = add_table_speed[berco] + 20;
	add_out_pt_4_speed[berco] = add_table_speed[berco] + 22;
	add_inp_pt_5_speed[berco] = add_table_speed[berco] + 24;
	add_out_pt_5_speed[berco] = add_table_speed[berco] + 26;
	add_inp_pt_6_speed[berco] = add_table_speed[berco] + 28;
	add_out_pt_6_speed[berco] = add_table_speed[berco] + 30;
	add_inp_pt_7_speed[berco] = add_table_speed[berco] + 32;
	add_out_pt_7_speed[berco] = add_table_speed[berco] + 34;
	add_rot_offset_speed[berco]= add_table_speed[berco] + 36; 
	//////////////////////////////////////////
	valor = bytes_resp_CAN_diag[21][berco];
	valor = valor << 24;
	tmp   = bytes_resp_CAN_diag[22][berco];
	tmp   = tmp << 16;		   
	valor = valor + tmp;
	tmp   = bytes_resp_CAN_diag[23][berco];
	tmp   = tmp << 8;
	valor = valor + tmp;
	valor = valor + bytes_resp_CAN_diag[24][berco];
	add_table_taco[berco] 	 = valor;
	add_CAN_min_taco[berco]  =  add_table_taco[berco];
	add_CAN_max_taco[berco]  =  add_table_taco[berco] + 2;
	add_inp_pt_0_taco[berco] =  add_table_taco[berco] + 4;
	add_out_pt_0_taco[berco] =  add_table_taco[berco] + 6;
	add_inp_pt_1_taco[berco] =  add_table_taco[berco] + 8;
	add_out_pt_1_taco[berco] =  add_table_taco[berco] + 10;
	add_inp_pt_2_taco[berco] =  add_table_taco[berco] + 12;
	add_out_pt_2_taco[berco] =  add_table_taco[berco] + 14;
	add_inp_pt_3_taco[berco] =  add_table_taco[berco] + 16;
	add_out_pt_3_taco[berco] =  add_table_taco[berco] + 18;
	add_inp_pt_4_taco[berco] =  add_table_taco[berco] + 20;
	add_out_pt_4_taco[berco] =  add_table_taco[berco] + 22;
	add_inp_pt_5_taco[berco] =  add_table_taco[berco] + 24;
	add_out_pt_5_taco[berco] =  add_table_taco[berco] + 26;
	add_inp_pt_6_taco[berco] =  add_table_taco[berco] + 28;
	add_out_pt_6_taco[berco] =  add_table_taco[berco] + 30;
	add_inp_pt_7_taco[berco] =  add_table_taco[berco] + 32;
	add_out_pt_7_taco[berco] =  add_table_taco[berco] + 34;
	add_rot_offset_taco[berco]= add_table_taco[berco] + 36; 
	/////////////////////////////////////////
	//tamanho_nvm[berco]= bytes_resp_CAN_diag[7][berco];
	//tamanho_nvm[berco]= tamanho_nvm[berco] << 8;
	//tamanho_nvm[berco]= tamanho_nvm[berco] + bytes_resp_CAN_diag[8][berco];
	//tamanho_nvm[berco] = 0x300; //comando n�o est� respondendo corretamente
	
}

/********************************** Ler_Analog_status() ************************************************************/
int Ler_Analog_status(INPUT_CLUSTER input, int *valor, int berco)
{
int 
	status = -1,
	byte_retorn_0 		= 0x10	, // valor que deve retornar no byte 0
	byte_retorn_serv 	= 2		, // byte onde est� resposta do servi�o
	valor_resposta_OK   = 0x62	; // valor resposta OK ao servi�o 0x22
double
	timeout = 2.0,
	t;
 SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
 unsigned long
	res = 0;
	 
	//--------------------------------------------------------------	 
	switch(input)
	{
		/*	
		case DIC_ANALOG_604R:
		case DIC_ANALOG_1624R:
		case DIC_ANALOG_3534R:
		*/
		case DIC_ANALOG:
			qual_servico_diag 	= LER_DIC_ANALOG_DIAG;
			break;
		case PASSIVE_START:
			qual_servico_diag 	= LER_PASSIV_START_DIAG;
			break;
		case FCA_OUT:
			qual_servico_diag 	= LER_FCA_OUT_DIAG;
			break;
		case FCA_DN_OUT:
			qual_servico_diag 	= LER_FCA_DN_OUT_DIAG;
			break;
		case PASSIV_START_RUN_OUT:
			qual_servico_diag 	= LER_PASS_START_RUN_OUT_DIAG;
			break;
		case PASSIV_START_IS1_OUT:
			qual_servico_diag 	= LER_PASS_START_IS1_OUT_DIAG;
			break;
		case PASSIV_START_ACC_OUT:
			qual_servico_diag 	= LER_PASS_START_ACC_OUT_DIAG;
			break;
		case PASSIV_START_IS2_OUT:
			qual_servico_diag 	= LER_PASS_START_IS2_OUT_DIAG;
			break;
		case BATTERY_VOLTAGE:
			qual_servico_diag 	= LER_BATTERY_VOLTAGE_DIAG;
			break;
		case PCB_TEMPERATURE_NTC:
			qual_servico_diag 	= LER_PCB_TEMPERATURE_NTC;
			break;
		case MONITOR_5V:
			qual_servico_diag 	= LER_MONITOR_5V;
			break;
		case LOW_FUEL_AD:
			qual_servico_diag 	= LER_LOW_FUEL_AD;
			break;
		case TIRE_PRESS_AD:
			qual_servico_diag 	= LER_TIRE_PRESS_AD;
			break;
		case ESC_AD:
			qual_servico_diag 	= LER_ESC_AD;
			break;
		case ABS_AD:
			qual_servico_diag 	= LER_ABS_AD;
			break;
		case PARKING_AD:
			qual_servico_diag 	= LER_PARKING_AD;
			break;
		case BRAKE_AD:
			qual_servico_diag 	= LER_BRAKE_AD;
			break;
		case AIRBAG_AD:
			qual_servico_diag 	= LER_AIRBAG_AD;
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar ler Entradas Anal�gicas - Fun��o inexistente");
			return -1;
	}		 
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco] = qual_servico_diag;
	while(servico_diagnostico[berco] == qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != byte_retorn_0 || Resp_diagnostico_RX[0][berco].cData[byte_retorn_serv] != valor_resposta_OK)
	{
		t = Timer() - t;
		
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	
	*valor = 0;
	switch(input)
	{
		case DIC_ANALOG:
			res = Resp_diagnostico_RX[0][berco].cData[5];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[0][berco].cData[6];
			*valor = res;
			break;
		case PASSIVE_START:
			res = Resp_diagnostico_RX[0][berco].cData[7];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[1][berco].cData[1];
			*valor = res;
			break;
		case FCA_OUT:
			res = Resp_diagnostico_RX[3][berco].cData[6];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[3][berco].cData[7];
			*valor = res;
			break;
		case FCA_DN_OUT:
			res = Resp_diagnostico_RX[4][berco].cData[1];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[4][berco].cData[2];
			*valor = res;
			break;
		case PASSIV_START_RUN_OUT:
			res = Resp_diagnostico_RX[4][berco].cData[5];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[4][berco].cData[6];
			*valor = res;
			break;
		case PASSIV_START_IS1_OUT:
			res = Resp_diagnostico_RX[5][berco].cData[2];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[5][berco].cData[3];
			*valor = res;
			break;
		case PASSIV_START_ACC_OUT:
			res = Resp_diagnostico_RX[4][berco].cData[7];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[5][berco].cData[1];
			*valor = res;
			break;
		case PASSIV_START_IS2_OUT:
			res = Resp_diagnostico_RX[5][berco].cData[4];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[5][berco].cData[5];
			*valor = res;
			break;
		case BATTERY_VOLTAGE:
			res = Resp_diagnostico_RX[1][berco].cData[2];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[1][berco].cData[3];
			*valor = res;
			break;
		case PCB_TEMPERATURE_NTC:
			res = Resp_diagnostico_RX[5][berco].cData[6];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[5][berco].cData[7];
			*valor = res;
			break;
		case MONITOR_5V:
			res = Resp_diagnostico_RX[4][berco].cData[3];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[4][berco].cData[4];
			*valor = res;
			break;
		case LOW_FUEL_AD:
			res = Resp_diagnostico_RX[2][berco].cData[3];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[2][berco].cData[4];
			*valor = res;
			break;
		case TIRE_PRESS_AD:
			res = Resp_diagnostico_RX[2][berco].cData[5];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[2][berco].cData[6];
			*valor = res;
			break;
		case ESC_AD:
			res = Resp_diagnostico_RX[3][berco].cData[2];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[3][berco].cData[3];
			*valor = res;
			break;
		case ABS_AD:
			res = Resp_diagnostico_RX[1][berco].cData[6];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[1][berco].cData[7];
			*valor = res;
			break;
		case PARKING_AD:
			res = Resp_diagnostico_RX[2][berco].cData[7];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[3][berco].cData[1];
			*valor = res;
			break;
		case BRAKE_AD:
			res = Resp_diagnostico_RX[1][berco].cData[4];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[1][berco].cData[5];
			*valor = res;
			break;
		case AIRBAG_AD:
			res = Resp_diagnostico_RX[2][berco].cData[1];
			res = res << 8;
			res = res +  Resp_diagnostico_RX[2][berco].cData[2];
			*valor = res;
			break;
	}		 
    
return SUCESSO; 
}

/********************************** Ler_DI_status() ************************************************************/
int Ler_DI_status(INPUT_CLUSTER input, int *valor, int berco)
{
int 
	status = -1,
	res = 0;
double
	timeout = 1.0,
	t;
 SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
 
	//--------------------------------------------------------------	 
	switch(input)
	{
		case RUN_CRANK:
			qual_servico_diag 	= LER_RUN_CRANK_DIAG;
			break;
		case DIC_SWITCH:
			qual_servico_diag 	= LER_DIC_SWITCH_DIAG;
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar ler Entradas Digitais - Fun��o inexistente");
			return -1;
	}		 
 	
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	
	t = Timer();
	servico_diagnostico[berco] = qual_servico_diag;
	while(servico_diagnostico[berco] == qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x62)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	
	*valor = 0;
	switch(input)
	{
		case RUN_CRANK:
			if((Resp_diagnostico_RX[0][berco].cData[5] & 0x02) == 0x02)
				*valor = 1;
			break;
		case DIC_SWITCH:
			if((Resp_diagnostico_RX[0][berco].cData[5] & 0x03) == 0X03)
				*valor = 1;
			break;
	}		 
	Indica_comm_CAN_OK(berco);
    
return SUCESSO; 
}


/********************************** Ilumination_PWM_DIAG() ************************************************************/
int Ilumination_PWM_DIAG(TELLTALES_GM_GEM lamp, int valor, int berco)
{
int 
	status = -1;
double
	timeout = 1.0,
	t;
SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
 
	switch(lamp)
	{
		
		case GAUGE_BACKLIGHT:
			qual_servico_diag 	= ILLUM_GAUGE_ADJUST_DIAG;
	   		break;
		case LCD_BACKLIGHT:
			qual_servico_diag 	= ILLUM_LCD_ADJUST_DIAG;
	   		break;	
		case POINTER_BACKLIGHT:
			qual_servico_diag 	= ILLUM_POINTER_ADJUST_DIAG;
	   		break;
		case TELLTALES_ILL:
			qual_servico_diag 	= ILLUM_TELLTALE_ADJUST_DIAG;
	   		break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar controlar PWM - Fun��o inexistente");
			return -1;
	}
	
	/////////////////////////////////////////////////////////////	 
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	
	/////////////////////////////////////////////////////////////	 
	switch (valor)
	{
		case 0:
			Diagnostico_TX[0][berco].cData [5] = 0x00;
			Diagnostico_TX[0][berco].cData [6] = 0x00;
			break;
		case PWM_ILUM_DEFAULT:
			Diagnostico_TX[0][berco].cData [5] = 0x01;
			Diagnostico_TX[0][berco].cData [6] = 0xF4;
			break;
		case 100:
			Diagnostico_TX[0][berco].cData [5] = 0x03;
			Diagnostico_TX[0][berco].cData [6] = 0xE8;
			break;
		default:
			if(modo_manual == ON)
			{
				MessagePopup ("Setup incorreto - fora de range",
				  "Falha ao tentar controlar PWM - O valor solicitado no comando est� fora de range");
			}
			return Indica_comm_CAN_Not_OK();
	}
	/////////////////////////////////////////////////////////////	 
	t = Timer();
	servico_diagnostico[berco] = qual_servico_diag;
	while(servico_diagnostico[berco] == qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
    
return SUCESSO; 
}


/********************************** Acende_lampada_cluster_DIAG() ************************************************************/
int Acende_lampada_cluster_DIAG(TELLTALES_GM_GEM lamp, int acao, int berco)
{
int 
	status = -1;
double
	timeout = 1.0,
	t;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------	 
	switch(lamp)
	{
		case ALL_TELLTALES_RED:
			if(acao)
			{
				diag_telltales[berco].tt_airbag 		= VAL_TT_AIRBAG_ON;
				diag_telltales[berco].tt_battery 		= VAL_TT_BATTERY_ON;
				diag_telltales[berco].tt_park_brake 	= VAL_TT_PARKBRAKE_ON;
				diag_telltales[berco].tt_coolant_temp 	= VAL_TT_COOLANT_TEMP_ON;
				diag_telltales[berco].tt_oil_pressure 	= VAL_TT_OIL_PRESSURE_ON;
				diag_telltales[berco].tt_seat_belt 		= VAL_TT_SEATBELT_ON;
				diag_telltales[berco].tt_parking_brake 	= VAL_TT_PARKING_BRAKE_ON;
				diag_telltales[berco].tt_passeng_seatbelt = VAL_TT_PASSEN_SEATBELT_ON;
			}
			else
			{
				diag_telltales[berco].tt_airbag 		= VAL_TT_AIRBAG_OFF;
				diag_telltales[berco].tt_battery 		= VAL_TT_BATTERY_OFF;
				diag_telltales[berco].tt_park_brake 	= VAL_TT_PARKBRAKE_OFF;
				diag_telltales[berco].tt_coolant_temp 	= VAL_TT_COOLANT_TEMP_OFF;
				diag_telltales[berco].tt_oil_pressure 	= VAL_TT_OIL_PRESSURE_OFF;
				diag_telltales[berco].tt_seat_belt 		= VAL_TT_SEATBELT_OFF;
				diag_telltales[berco].tt_parking_brake 	= VAL_TT_PARKING_BRAKE_OFF;
				diag_telltales[berco].tt_passeng_seatbelt = VAL_TT_PASSEN_SEATBELT_OFF;
			}
	   		break;	
		case ALL_TELLTALES_GREEN:
			if(acao)
			{
				diag_telltales[berco].tt_cruise_engaged 	= VAL_TT_CRUISE_ENGAGED_ON;
				diag_telltales[berco].tt_front_fog 			= VAL_TT_FRONT_FOG_ON;
				diag_telltales[berco].tt_light_on 			= VAL_TT_LIGHTON_ON;
				diag_telltales[berco].tt_turn_left 			= VAL_TT_TURN_LEFT_ON;
				diag_telltales[berco].tt_turn_right 		= VAL_TT_TURN_RIGHT_ON;
				diag_telltales[berco].tt_lane_kepper_green 	= VAL_TT_LANE_KEEP_GREEN_ON;
				diag_telltales[berco].tt_track_lead_green 	= VAL_TT_TRACK_LEAD_GREEN_ON;
				diag_telltales[berco].tt_auto_hold_green 	= VAL_TT_AUTOHOLD_GREEN_ON;
			}
			else
			{
				diag_telltales[berco].tt_cruise_engaged 	= VAL_TT_CRUISE_ENGAGED_OFF;
				diag_telltales[berco].tt_front_fog 			= VAL_TT_FRONT_FOG_OFF;					 
				diag_telltales[berco].tt_light_on 			= VAL_TT_LIGHTON_OFF;
				diag_telltales[berco].tt_turn_left 			= VAL_TT_TURN_LEFT_OFF;
				diag_telltales[berco].tt_turn_right 		= VAL_TT_TURN_RIGHT_OFF;
				diag_telltales[berco].tt_lane_kepper_green 	= VAL_TT_LANE_KEEP_GREEN_OFF;
				diag_telltales[berco].tt_track_lead_green 	= VAL_TT_TRACK_LEAD_GREEN_OFF;
				diag_telltales[berco].tt_auto_hold_green 	= VAL_TT_AUTOHOLD_GREEN_OFF;
			}
	   		break;	
		case ALL_TELLTALES_AMBER:
			if(acao)
			{
				diag_telltales[berco].tt_abs 				= VAL_TT_ABS_ON;
				diag_telltales[berco].tt_se_parkbrake 		= VAL_TT_SE_PARKBREAK_ON;
				diag_telltales[berco].tt_fuel_level_low 	= VAL_TT_FUEL_LV_LOW_ON;					 
				diag_telltales[berco].tt_rear_fog 			= VAL_TT_REAR_FOG_ON;
				diag_telltales[berco].tt_security 			= VAL_TT_SECURITY_ON;
				diag_telltales[berco].tt_serv_eng_soon 		= VAL_TT_SERV_ENG_SOON_ON;
				diag_telltales[berco].tt_tire_press_low 	= VAL_TT_TIRE_PRESS_LOW_ON;
				diag_telltales[berco].tt_esc_off 			= VAL_TT_ESCOFF_ON;
				diag_telltales[berco].tt_esc_service 		= VAL_TT_ESC_SERVICE_ON;
				diag_telltales[berco].tt_press_clutch 		= VAL_TT_PRESS_CLUTCH_ON;
				diag_telltales[berco].tt_traction_cntrl_off	= VAL_TT_TRACTION_CONTRL_ON;
				diag_telltales[berco].tt_service_vehi_soon 	= VAL_TT_SERV_VEH_SOON_ON;
				diag_telltales[berco].tt_eps 				= VAL_TT_EPS_ON;
				diag_telltales[berco].tt_park_assist 		= VAL_TT_PARK_ASSIST_ON;
				diag_telltales[berco].tt_glow_plug 			= VAL_TT_GLOWPLUG_ON;
				diag_telltales[berco].tt_pedestrian 		= VAL_TT_PEDESTRIAN_ON;
				diag_telltales[berco].tt_lane_kepper_amber 	= VAL_TT_LANE_KEEP_AMBER_ON;
				diag_telltales[berco].tt_track_lead_amber 	= VAL_TT_TRACK_LEAD_AMBER_ON;
			}
			else
			{
				diag_telltales[berco].tt_abs 				= VAL_TT_ABS_OFF;
				diag_telltales[berco].tt_se_parkbrake 		= VAL_TT_SE_PARKBREAK_OFF;
				diag_telltales[berco].tt_fuel_level_low 	= VAL_TT_FUEL_LV_LOW_OFF;					 
				diag_telltales[berco].tt_rear_fog 			= VAL_TT_REAR_FOG_OFF;
				diag_telltales[berco].tt_security 			= VAL_TT_SECURITY_OFF;
				diag_telltales[berco].tt_serv_eng_soon 		= VAL_TT_SERV_ENG_SOON_OFF;
				diag_telltales[berco].tt_tire_press_low 	= VAL_TT_TIRE_PRESS_LOW_OFF;
				diag_telltales[berco].tt_esc_off 			= VAL_TT_ESCOFF_OFF;
				diag_telltales[berco].tt_esc_service 		= VAL_TT_ESC_SERVICE_OFF;
				diag_telltales[berco].tt_press_clutch 		= VAL_TT_PRESS_CLUTCH_OFF;
				diag_telltales[berco].tt_traction_cntrl_off	= VAL_TT_TRACTION_CONTRL_OFF;
				diag_telltales[berco].tt_service_vehi_soon 	= VAL_TT_SERV_VEH_SOON_OFF;
				diag_telltales[berco].tt_eps 				= VAL_TT_EPS_OFF;
				diag_telltales[berco].tt_park_assist 		= VAL_TT_PARK_ASSIST_OFF;
				diag_telltales[berco].tt_glow_plug 			= VAL_TT_GLOWPLUG_OFF;
				diag_telltales[berco].tt_pedestrian 		= VAL_TT_PEDESTRIAN_OFF;
				diag_telltales[berco].tt_lane_kepper_amber 	= VAL_TT_LANE_KEEP_AMBER_OFF;
				diag_telltales[berco].tt_track_lead_amber 	= VAL_TT_TRACK_LEAD_AMBER_OFF;
			}
	   		break;	
		case ALL_TELLTALES_WHITE:
			if(acao)
			{
				diag_telltales[berco].tt_kmh 				= VAL_TT_KMH_ON;
				diag_telltales[berco].tt_mph 				= VAL_TT_MPH_ON;
				diag_telltales[berco].tt_auto_hold_white 	= VAL_TT_AUTOHOLD_WHITE_ON;
			}
			else
			{
				diag_telltales[berco].tt_kmh 				= VAL_TT_KMH_OFF;
				diag_telltales[berco].tt_mph 				= VAL_TT_MPH_OFF;
				diag_telltales[berco].tt_auto_hold_white 	= VAL_TT_AUTOHOLD_WHITE_OFF;
			}
	   		break;
			
		case AIRBAG:
			if(acao)
				diag_telltales[berco].tt_airbag = VAL_TT_AIRBAG_ON;
			else
				diag_telltales[berco].tt_airbag = VAL_TT_AIRBAG_OFF;
	   		break;	
		case ABS:	
			if(acao)
				diag_telltales[berco].tt_abs 	= VAL_TT_ABS_ON;
			else
				diag_telltales[berco].tt_abs 	= VAL_TT_ABS_OFF;
	   		break;	
		case BATTERY: 
			if(acao)
				diag_telltales[berco].tt_battery = VAL_TT_BATTERY_ON;
			else
				diag_telltales[berco].tt_battery = VAL_TT_BATTERY_OFF;
	   		break;	
		case PARK_BRAKE:  
			if(acao)
				diag_telltales[berco].tt_park_brake = VAL_TT_PARKBRAKE_ON;
			else
				diag_telltales[berco].tt_park_brake = VAL_TT_PARKBRAKE_OFF;
	   		break;	
		case SERVICE_ELETRIC_PARK_BRAKE: 
			if(acao)
				diag_telltales[berco].tt_se_parkbrake = VAL_TT_SE_PARKBREAK_ON;
			else
				diag_telltales[berco].tt_se_parkbrake = VAL_TT_SE_PARKBREAK_OFF;
	   		break;	
		case COOLANT_TEMP: 
			if(acao)
				diag_telltales[berco].tt_coolant_temp = VAL_TT_COOLANT_TEMP_ON;
			else
				diag_telltales[berco].tt_coolant_temp = VAL_TT_COOLANT_TEMP_OFF;
	   		break;	
		case CRUISE_ENGAGED:   //green	 
			if(acao)
				diag_telltales[berco].tt_cruise_engaged = VAL_TT_CRUISE_ENGAGED_ON;
			else
				diag_telltales[berco].tt_cruise_engaged = VAL_TT_CRUISE_ENGAGED_OFF;
	   		break;	
		case CRUISE_ON:        //white 
			if(acao)
				diag_telltales[berco].tt_cruise_on = VAL_TT_CRUISEON_ON;
			else
				diag_telltales[berco].tt_cruise_on = VAL_TT_CRUISEON_OFF;					 
	   		break;	
		case FRONT_FOG:  
			if(acao)
				diag_telltales[berco].tt_front_fog = VAL_TT_FRONT_FOG_ON;
			else
				diag_telltales[berco].tt_front_fog = VAL_TT_FRONT_FOG_OFF;					 
	   		break;	
		case FUEL_LEVEL_LOW:
			if(acao)
				diag_telltales[berco].tt_fuel_level_low = VAL_TT_FUEL_LV_LOW_ON;
			else
				diag_telltales[berco].tt_fuel_level_low = VAL_TT_FUEL_LV_LOW_OFF;					 
	   		break;	
		case ALL_TELLTALES_BLUE:
		case HI_BEAM:  
			if(acao)
				diag_telltales[berco].tt_high_beam = VAL_TT_HIGH_BEAM_ON;
			else
				diag_telltales[berco].tt_high_beam = VAL_TT_HIGH_BEAM_OFF;					 
	   		break;	
	 	case LIGHTS_ON:  
			if(acao)
				diag_telltales[berco].tt_light_on 	= VAL_TT_LIGHTON_ON;
			else
				diag_telltales[berco].tt_light_on 	= VAL_TT_LIGHTON_OFF;
	   		break;	
		case OIL_PRESSURE:   
			if(acao)
				diag_telltales[berco].tt_oil_pressure 	= VAL_TT_OIL_PRESSURE_ON;
			else
				diag_telltales[berco].tt_oil_pressure 	= VAL_TT_OIL_PRESSURE_OFF;
	   		break;	
		case REAR_FOG:  
			if(acao)
				diag_telltales[berco].tt_rear_fog 	= VAL_TT_REAR_FOG_ON;
			else
				diag_telltales[berco].tt_rear_fog 	= VAL_TT_REAR_FOG_OFF;
	   		break;	
		case DRIVER_SEAT_BELT: 
			if(acao)
				diag_telltales[berco].tt_seat_belt = VAL_TT_SEATBELT_ON;
			else
				diag_telltales[berco].tt_seat_belt = VAL_TT_SEATBELT_OFF;
	   		break;	
		case SECURITY:  
			if(acao)
				diag_telltales[berco].tt_security = VAL_TT_SECURITY_ON;
			else
				diag_telltales[berco].tt_security = VAL_TT_SECURITY_OFF;
	   		break;	
		case SERVICE_ENGINE_SOON: 
			if(acao)
				diag_telltales[berco].tt_serv_eng_soon = VAL_TT_SERV_ENG_SOON_ON;
			else
				diag_telltales[berco].tt_serv_eng_soon = VAL_TT_SERV_ENG_SOON_OFF;
	   		break;	
		case TIRE_PRESSURE_LOW:  
			if(acao)
				diag_telltales[berco].tt_tire_press_low = VAL_TT_TIRE_PRESS_LOW_ON;
			else
				diag_telltales[berco].tt_tire_press_low = VAL_TT_TIRE_PRESS_LOW_OFF;
	   		break;	
		case TURN_LEFT:  
			if(acao)
				diag_telltales[berco].tt_turn_left = VAL_TT_TURN_LEFT_ON;
			else
				diag_telltales[berco].tt_turn_left = VAL_TT_TURN_LEFT_OFF;
	   		break;	
		case TURN_RIGHT:   
			if(acao)
				diag_telltales[berco].tt_turn_right = VAL_TT_TURN_RIGHT_ON;
			else
				diag_telltales[berco].tt_turn_right = VAL_TT_TURN_RIGHT_OFF;
	   		break;	
		case ESC_OFF:  
			if(acao)
				diag_telltales[berco].tt_esc_off = VAL_TT_ESCOFF_ON;
			else
				diag_telltales[berco].tt_esc_off = VAL_TT_ESCOFF_OFF;
	   		break;	
		case ESC_SERVICE: 
			if(acao)
				diag_telltales[berco].tt_esc_service = VAL_TT_ESC_SERVICE_ON;
			else
				diag_telltales[berco].tt_esc_service = VAL_TT_ESC_SERVICE_OFF;
	   		break;	
		case PARKING_BRAKE: 
			if(acao)
				diag_telltales[berco].tt_parking_brake = VAL_TT_PARKING_BRAKE_ON;
			else
				diag_telltales[berco].tt_parking_brake = VAL_TT_PARKING_BRAKE_OFF;
	   		break;	
		case PRESS_CLUTCH_START: 
			if(acao)
				diag_telltales[berco].tt_press_clutch = VAL_TT_PRESS_CLUTCH_ON;
			else
				diag_telltales[berco].tt_press_clutch = VAL_TT_PRESS_CLUTCH_OFF;
	   		break;	
		case PASSENGER_SEAT_BELT: 
			if(acao)
				diag_telltales[berco].tt_passeng_seatbelt = VAL_TT_PASSEN_SEATBELT_ON;
			else
				diag_telltales[berco].tt_passeng_seatbelt = VAL_TT_PASSEN_SEATBELT_OFF;
	   		break;	
		case TRACTION_CONTROL_OFF: 
			if(acao)
				diag_telltales[berco].tt_traction_cntrl_off = VAL_TT_TRACTION_CONTRL_ON;
			else
				diag_telltales[berco].tt_traction_cntrl_off = VAL_TT_TRACTION_CONTRL_OFF;
	   		break;	
		case SERVIVE_VEHICLE_SOON:  
			if(acao)
				diag_telltales[berco].tt_service_vehi_soon = VAL_TT_SERV_VEH_SOON_ON;
			else
				diag_telltales[berco].tt_service_vehi_soon = VAL_TT_SERV_VEH_SOON_OFF;
	   		break;	
		case EPS:  
			if(acao)
				diag_telltales[berco].tt_eps = VAL_TT_EPS_ON;
			else
				diag_telltales[berco].tt_eps = VAL_TT_EPS_OFF;
	   		break;	
		case PARK_ASSIST:  
			if(acao)
				diag_telltales[berco].tt_park_assist = VAL_TT_PARK_ASSIST_ON;
			else
				diag_telltales[berco].tt_park_assist = VAL_TT_PARK_ASSIST_OFF;
	   		break;	
		case GLOW_PLUG:  
			if(acao)
				diag_telltales[berco].tt_glow_plug = VAL_TT_GLOWPLUG_ON;
			else
				diag_telltales[berco].tt_glow_plug = VAL_TT_GLOWPLUG_OFF;
	   		break;	
		case KMH:  
			if(acao)
				diag_telltales[berco].tt_kmh = VAL_TT_KMH_ON;
			else
				diag_telltales[berco].tt_kmh = VAL_TT_KMH_OFF;
	   		break;	
		case MPH:  
			if(acao)
				diag_telltales[berco].tt_mph = VAL_TT_MPH_ON;
			else
				diag_telltales[berco].tt_mph = VAL_TT_MPH_OFF;
	   		break;	
		case PEDESTRIAN:  
			if(acao)
				diag_telltales[berco].tt_pedestrian = VAL_TT_PEDESTRIAN_ON;
			else
				diag_telltales[berco].tt_pedestrian = VAL_TT_PEDESTRIAN_OFF;
	   		break;	
		case LANE_KEEPER_GREEN:  
			if(acao)
				diag_telltales[berco].tt_lane_kepper_green = VAL_TT_LANE_KEEP_GREEN_ON;
			else
				diag_telltales[berco].tt_lane_kepper_green = VAL_TT_LANE_KEEP_GREEN_OFF;
	   		break;	
		case LANE_KEEPER_AMBER:  
			if(acao)
				diag_telltales[berco].tt_lane_kepper_amber = VAL_TT_LANE_KEEP_AMBER_ON;
			else
				diag_telltales[berco].tt_lane_kepper_amber = VAL_TT_LANE_KEEP_AMBER_OFF;
	   		break;
		case TRACKING_LEAD_GREEN:  
			if(acao)
				diag_telltales[berco].tt_track_lead_green = VAL_TT_TRACK_LEAD_GREEN_ON;
			else
				diag_telltales[berco].tt_track_lead_green = VAL_TT_TRACK_LEAD_GREEN_OFF;
	   		break;
		case TRACKING_LEAD_AMBER:  
			if(acao)
				diag_telltales[berco].tt_track_lead_amber = VAL_TT_TRACK_LEAD_AMBER_ON;
			else
				diag_telltales[berco].tt_track_lead_amber = VAL_TT_TRACK_LEAD_AMBER_OFF;
	   		break;
		case AUTOHOLD_WHITE:  
			if(acao)
				diag_telltales[berco].tt_auto_hold_white = VAL_TT_AUTOHOLD_WHITE_ON;
			else
				diag_telltales[berco].tt_auto_hold_white = VAL_TT_AUTOHOLD_WHITE_OFF;
	   		break;
	
		case AUTOHOLD_GREEN:  
			if(acao)
				diag_telltales[berco].tt_auto_hold_green = VAL_TT_AUTOHOLD_GREEN_ON;
			else
				diag_telltales[berco].tt_auto_hold_green = VAL_TT_AUTOHOLD_GREEN_OFF;
	   		break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar acionar telltale - Fun��o inexistente");
			return Indica_comm_CAN_Not_OK();
	}
	Diagnostico_TX[0][berco].cData [6] = 0x00;
	Diagnostico_TX[0][berco].cData [7] = 0x00;
	Diagnostico_TX[1][berco].cData [1] = 0x00;
	Diagnostico_TX[1][berco].cData [2] = 0x00;
	Diagnostico_TX[1][berco].cData [3] = 0x00;
	Diagnostico_TX[1][berco].cData [4] = 0x00;
	//------------------------------//
	Diagnostico_TX[0][berco].cData [6] = diag_telltales[berco].tt_airbag;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_telltales[berco].tt_park_brake;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_telltales[berco].tt_abs;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_telltales[berco].tt_battery;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_telltales[berco].tt_se_parkbrake;
	Diagnostico_TX[0][berco].cData [6] = Diagnostico_TX[0][berco].cData [6] + diag_telltales[berco].tt_coolant_temp;
	//------------------------------//
	Diagnostico_TX[0][berco].cData [7] = diag_telltales[berco].tt_cruise_engaged;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_cruise_on;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_front_fog;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_fuel_level_low;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_high_beam;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_light_on;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_oil_pressure;
	Diagnostico_TX[0][berco].cData [7] = Diagnostico_TX[0][berco].cData [7] + diag_telltales[berco].tt_rear_fog;
	//------------------------------//
	Diagnostico_TX[1][berco].cData [1] = diag_telltales[berco].tt_seat_belt;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_serv_eng_soon;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_security;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_tire_press_low;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_turn_left;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_turn_right;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_esc_off;
	Diagnostico_TX[1][berco].cData [1] = Diagnostico_TX[1][berco].cData [1] + diag_telltales[berco].tt_esc_service;
	//------------------------------//
	Diagnostico_TX[1][berco].cData [2] = diag_telltales[berco].tt_parking_brake;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_press_clutch;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_passeng_seatbelt;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_traction_cntrl_off;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_service_vehi_soon;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_eps;
	Diagnostico_TX[1][berco].cData [2] = Diagnostico_TX[1][berco].cData [2] + diag_telltales[berco].tt_mph;
	//------------------------------//
	Diagnostico_TX[1][berco].cData [3] = diag_telltales[berco].tt_park_assist;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_glow_plug;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_pedestrian;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_lane_kepper_green;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_lane_kepper_amber;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_kmh;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_track_lead_green;
	Diagnostico_TX[1][berco].cData [3] = Diagnostico_TX[1][berco].cData [3] + diag_telltales[berco].tt_track_lead_amber;
	//------------------------------//
	Diagnostico_TX[1][berco].cData [4] = diag_telltales[berco].tt_auto_hold_white;
	Diagnostico_TX[1][berco].cData [4] = Diagnostico_TX[1][berco].cData [4] + diag_telltales[berco].tt_auto_hold_green;
	
	t = Timer();
	servico_diagnostico[berco] = TELLTALE_ON_OFF_DIAG;
	while(servico_diagnostico[berco] == TELLTALE_ON_OFF_DIAG && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[2] != 0x6F)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
    
return SUCESSO; 
}

/******************************** LedsDisplay_Customer_DIAG() *****************************************************/
int LedsDisplay_Customer_DIAG(int acao, int berco)
{
int 
	status = -1,
	byte;
double
	timeout = 1.0,
	t;

	
	if(acao < 0 || acao > 1)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar LEDS/DISPLAY em Customer Mode - O valor solicitado no comando est� fora de range");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	if(acao)
		Diagnostico_TX[0][berco].cData [5] = 0x03;
	else
		Diagnostico_TX[0][berco].cData [5] = 0x00;
	
	t = Timer();
	servico_diagnostico[berco] = TELLT_DISP_DIAG_CUSTOMER;
	while(servico_diagnostico[berco] == TELLT_DISP_DIAG_CUSTOMER && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xF0)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
return SUCESSO; 
}

/******************************** SetTacometroCustomer_DIAG() *****************************************************/
int SetTacometroCustomer_DIAG(int rpm, int berco)
{
int 
	status = -1,
	byte;
double
	timeout = 1.0,
	t;

	
	if(rpm < 0 || rpm > 8000)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar TAC�METRO - O valor solicitado no comando est� fora de range");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	rpm = rpm * FATOR_RPM_CAN_DIAG;
	byte = rpm & 0xFF00;
	byte = byte >> 8;
	Diagnostico_TX[0][berco].cData [5] = byte;//msb  
	byte = rpm & 0x00FF;
	Diagnostico_TX[0][berco].cData [6] = byte;//lsb 
	t = Timer();
	servico_diagnostico[berco] = TACOMETRO_CUSTOMER;
	while(servico_diagnostico[berco] == TACOMETRO_CUSTOMER && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xF0)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
return SUCESSO; 
}

/******************************** SetGauge_eol_visteon_DIAG() *****************************************************/
//     OBSERVA��ES
// Movimentos para frente(modo absoluto s� est� funcionando com velocidade = 1 ou seja 166 Graus/segundos
// Quando se faz um movimento para frente e logo ap�s um movimento para tras com o mesmo valor o cluster n�o responde. Para contornar este bug deve-se sempre retornar com valor diferente do movimento para frente
int SetGauge_eol_visteon_DIAG(int counts, int qual_gauge, int move_absoluto, int torque, unsigned char velocidade, int espera_fim_movmento, int berco)
{
int 
	status = -1,
	byte;
double
	timeout = 1.0,
	t,
	motor_speed,
	delay_espera,
	tempo_espera;

	
	if(counts < 0 || counts > 4000)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar GAUGE - O valor de COUNTS solicitado no comando est� fora de range");
		}
		return -1;
	}
	if(move_absoluto != MOVE_TOWARD_STOP && MOVE_ABSOLUTO != ON)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar GAUGE - O valor para mover ABSOLUTO est� fora de range");
		}
		return -2;
	}
	if(torque < GAUGE_TORQUE_NORMAL && torque > GAUGE_TORQUE_LOW)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar GAUGE - O valor para TORQUE est� fora de range");
		}
		return -3;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	Diagnostico_TX[1][berco].cData [3] = !move_absoluto; //movement type 00=absolute, 01=Towards stop
	Diagnostico_TX[1][berco].cData [2] = torque;		 //torque  -> 00=Normal, 01=High Torque,  02=Low Torque
	switch(qual_gauge)
	{
		case GAUGE_VELOCIMETRO:
	   		Diagnostico_TX[0][berco].cData [6] = 0x00;
			break;
		case GAUGE_TACOMETRO:
	   		Diagnostico_TX[0][berco].cData [6] = 0x01;
			break;
		case GAUGES_ALL:
	   		Diagnostico_TX[0][berco].cData [6] = 0xFF;
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar controlar GAUGE - Fun��o inexistente");
			return Indica_comm_CAN_Not_OK();
	}
	//Controls pointer speed by setting the delay between stepper motor micro-steps.Considering the minim gauge interrupt time by GEM software is 500us so that
	//0x01 = 1* 500us/micro-step = 166.6deg/s
	//0x03 = 3* 500us/micro-step = 55.55deg/s
	//0x05 = 5* 500us/micro-step = 33.35deg/s
	switch(velocidade)
	{
		case 0:
			motor_speed = 330.0; //valor aprox velocidade
			tempo_espera = 0.0005; //6/motor_speed;
			break;
		case 1:
			motor_speed  = 166.6; //valor aprox velocidade
			tempo_espera = 0.0010; //6/motor_speed;
			break;
		case 3:
			motor_speed = 55.55; //valor aprox velocidade
			tempo_espera = 0.0020; //
			break;
		case 5:
			motor_speed = 33.35; //valor aprox velocidade
			tempo_espera = 0.0032; //
			break;
		default:
			MessagePopup ("Setup incorreto - Velocidade fora de range",
				  "Falha ao tentar controlar GAUGE - Valor da Velocidade est� fora de Range");
			return Indica_comm_CAN_Not_OK();
	}
	Diagnostico_TX[1][berco].cData [1] = velocidade;
	/////////////////////////////////////////////////	
	byte = counts & 0xFF00;
	byte = byte >> 8;
	Diagnostico_TX[1][berco].cData [4] = byte;//msb  
	byte = counts & 0x00FF;
	Diagnostico_TX[1][berco].cData [5] = byte;//lsb 
	
	
	t = Timer();
	servico_diagnostico[berco] = GAUGE_EOL_VISTEON;
	while(servico_diagnostico[berco] == GAUGE_EOL_VISTEON && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[1] != 0x0B || Resp_diagnostico_RX[0][berco].cData[2] != 0x6F || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	if(espera_fim_movmento)
	{
		delay_espera = fabs(counts - atual_counts_velo[berco]);
		delay_espera = delay_espera*tempo_espera;
		Delay_thread(delay_espera);
	}
	
	if(qual_gauge == GAUGE_VELOCIMETRO || qual_gauge == GAUGES_ALL)
	{
		if(move_absoluto == ON)
			atual_counts_velo[berco] = counts;
		else
		{
			atual_counts_velo[berco] = atual_counts_velo[berco] - counts;
			if(atual_counts_velo[berco] < 0)
				atual_counts_velo[berco] = 0;
		}
	}
	if(qual_gauge == GAUGE_TACOMETRO || qual_gauge == GAUGES_ALL)
	{
		if(move_absoluto == ON)
			atual_counts_taco[berco] = counts;
		else
		{
			atual_counts_taco[berco] = atual_counts_taco[berco] - counts;
			if(atual_counts_taco[berco] < 0)
				atual_counts_taco[berco] = 0;
		}
	}
	
	
	Indica_comm_CAN_OK(berco);
	
return SUCESSO; 
}

/******************************** SetVelocimetroCustomer_DIAG() *****************************************************/
int SetVelocimetroCustomer_DIAG(int kmh, int berco)
{
int 
	status = -1,
	byte;
double
	timeout = 1.0,
	t;

	
	if(kmh < 0 || kmh > 200)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar controlar VELOC�METRO - O valor solicitado no comando est� fora de range");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	kmh		= kmh * FATOR_VELO_CAN_DIAG;
	byte 	= kmh & 0xFF00;
	byte 	= kmh >> 8;
	Diagnostico_TX[0][berco].cData [5] = byte;//msb  
	byte 	= kmh & 0x00FF;
	Diagnostico_TX[0][berco].cData [6] = byte;//lsb 
	t = Timer();
	servico_diagnostico[berco] = VELOCIMETRO_CUSTOMER;
	while(servico_diagnostico[berco] == VELOCIMETRO_CUSTOMER && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xF0)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
return SUCESSO; 
}
 


/******************************** LerStatus_LiveKey() *****************************************************/
int LerStatus_LiveKey(int berco)
{
int 
	valor;
double
	timeout = 2.0,
	t;

	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		Delay_thread(0.01);
	}
	t = Timer();
	servico_diagnostico[berco] = LER_STATUS_LIVE_KEY;
	while(servico_diagnostico[berco] == LER_STATUS_LIVE_KEY && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		Delay_thread(0.01);
	}
	if(SysBkUpPwrMd[berco].cData[0] !=0 && SysBkUpPwrMd[berco].cData[1] != 0 && SysBkUpPwrMd[berco].cData[1] !=0)
		 return ON;

return OFF; 
}	
	
	 
/********************************** Ler_ECU_ID() ************************************************************/
int Ler_ECU_ID(int berco)
{
int 
	status = -1,
	valor_resposta_OK   = 0x62	, // valor resposta OK ao servi�o 0x22
	i;
double
	timeout = 1.0,
	t;
char 
	tmp[50];


 	if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco] = LER_ECU_ID;
	while(servico_diagnostico[berco] == LER_ECU_ID && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[2] != valor_resposta_OK ||
	   Resp_diagnostico_RX[0][berco].cData[3] != 0xF0 || Resp_diagnostico_RX[0][berco].cData[4] != 0xF3)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	
	bytes_resp_CAN_diag[0][berco] = Resp_diagnostico_RX[0][berco].cData[5];
	bytes_resp_CAN_diag[1][berco] = Resp_diagnostico_RX[0][berco].cData[6];
	bytes_resp_CAN_diag[2][berco] = Resp_diagnostico_RX[0][berco].cData[7];
	
	bytes_resp_CAN_diag[3][berco] = Resp_diagnostico_RX[1][berco].cData[1];
	bytes_resp_CAN_diag[4][berco] = Resp_diagnostico_RX[1][berco].cData[2];
	bytes_resp_CAN_diag[5][berco] = Resp_diagnostico_RX[1][berco].cData[3];
	bytes_resp_CAN_diag[6][berco] = Resp_diagnostico_RX[1][berco].cData[4];
	bytes_resp_CAN_diag[7][berco] = Resp_diagnostico_RX[1][berco].cData[5];
	bytes_resp_CAN_diag[8][berco] = Resp_diagnostico_RX[1][berco].cData[6];
	bytes_resp_CAN_diag[9][berco] = Resp_diagnostico_RX[1][berco].cData[7];
	
	bytes_resp_CAN_diag[10][berco]= Resp_diagnostico_RX[2][berco].cData[1];
	bytes_resp_CAN_diag[11][berco]= Resp_diagnostico_RX[2][berco].cData[2];
	bytes_resp_CAN_diag[12][berco]= Resp_diagnostico_RX[2][berco].cData[3];
	bytes_resp_CAN_diag[13][berco]= Resp_diagnostico_RX[2][berco].cData[4];
	bytes_resp_CAN_diag[14][berco]= Resp_diagnostico_RX[2][berco].cData[5];
	bytes_resp_CAN_diag[15][berco]= Resp_diagnostico_RX[2][berco].cData[6];
	strcpy(dados_live_key[berco].ecu_id_lido,"");
	for(i=0; i<16; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].ecu_id_lido, tmp);
	}
	StringUpperCase (dados_live_key[berco].ecu_id_lido);
	
return SUCESSO; 
}

		 
/******************************** Gravar_ECU_ID() *****************************************************/
int Gravar_ECU_ID(int berco)
{
int 
	status = -1,
	tamanho_str_ecu_id = 32,
	i,
	j,
	valor;
double
	timeout = 1.0,
	t;
char 
	tmp[10];

	if( strlen(dados_live_key[berco].ecu_id) != tamanho_str_ecu_id)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Gravar ECU-ID",
						  "Houve um erro ao tentar Gravar ECU-ID - A strings do ECU-ID est� com tamanho inv�lido");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	j=0;
	for(i=0; i < tamanho_str_ecu_id; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].ecu_id, i, 2);
		Fmt(&valor , "%x<%s",tmp);
		envio_can[berco].dados_can[j] = valor;
		j++;
	}
	t = Timer();
	servico_diagnostico[berco] = WRITE_ECU_ID;
	while(servico_diagnostico[berco] == WRITE_ECU_ID && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 ||
	   Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	if(modo_manual)
	{
		if(ConfirmPopup ("Confirmar avan�o do INDEX",
			  "O indexador do Live Key ser� incrementado ap�s a grava��o com sucesso do ECU-ID. SIM para confirmar") != 1)
			return SUCESSO;
	}
	///////////// Opcional ///////////////////
	/*
	atual_index_live_key[berco]++;
	atual_index_live_key[berco] = manual_index_live_key;
	if(LerIndexar_arq_index_LiveKey(ON) < 0)
		return FALHA_ARQUIVO_INDEX_LIVEKEY;
	*/
	//////////////////////////////////////////
	
return SUCESSO; 
	
}	
	

/******************************** Gravar_Unlock_Key() *****************************************************/
int Gravar_Unlock_Key(int berco)
{
int 
	status = -1,
	tamanho_str_unlockkey = 32,
	i,
	j,
	valor,
	arquivo_m4_m5,
	first_line = OFF,
	mes,
	dia,
	ano,
	size;
	//bytes_envio_CAN_local[MAX_TAMAN_ENVIO_CLUSTER][NUMERO_DE_BERCOS+1]={0};
double
	timeout = 1.5,
	t;
char 
	tmp[10],
	*buff;


	if( strlen(dados_live_key[berco].unlock_key_1) != tamanho_str_unlockkey ||
		strlen(dados_live_key[berco].unlock_key_2) != tamanho_str_unlockkey ||
		strlen(dados_live_key[berco].unlock_key_3) != tamanho_str_unlockkey ||
		strlen(dados_live_key[berco].unlock_key_4) != tamanho_str_unlockkey)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Gravar Unlock Key",
						  "Houve um erro ao tentar Gravar Unlock Key - Uma ou mais strings do Unlock Key est� com tamanho inv�lido");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	j=0;
	for(i=0; i < tamanho_str_unlockkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].unlock_key_1, i, 2);
		Fmt(&envio_can[berco].dados_can[j] , "%x<%s",tmp);
		j++;
	}
	for(i=0; i < tamanho_str_unlockkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].unlock_key_2, i, 2);
		Fmt(&envio_can[berco].dados_can[j] , "%x<%s",tmp);
		j++;
	}
	for(i=0; i < tamanho_str_unlockkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].unlock_key_3, i, 2);
		Fmt(&envio_can[berco].dados_can[j] , "%x<%s",tmp);
		j++;
	}
	for(i=0; i < tamanho_str_unlockkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].unlock_key_4, i, 2);
		Fmt(&envio_can[berco].dados_can[j] , "%x<%s",tmp);
		j++;
	}
	//memcpy(envio_can[berco], bytes_envio_CAN_local[berco], sizeof(bytes_envio_CAN_local[berco]));
	t = Timer();
	servico_diagnostico[berco] = WRITE_UNLOCK_KEY;
	while(servico_diagnostico[berco] == WRITE_UNLOCK_KEY && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[2] != 0x71 || 
	   Resp_diagnostico_RX[0][berco].cData[3] != 0x01 || Resp_diagnostico_RX[0][berco].cData[4] != 0x02 ||
	   Resp_diagnostico_RX[0][berco].cData[5] != 0x72 || Resp_diagnostico_RX[0][berco].cData[6] != 0x00)
	{
		if(modo_manual)
		{
			MessagePopup ("Falha na grava��o do Unlock Key", "Falha na grava��o do Unlock Key - Talvez este dado ja esteja gravado no cluster");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  ATTR_DIMMED ,OFF);
		}
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
	ResetaBytesResposta_CAN(berco);
	
	CarregaResp_LiveKey(berco);

	strcpy(dados_live_key[berco].unlock_M4_1,"");
	for(i=0; i<16; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].unlock_M4_1, tmp);
	}
	strcpy(dados_live_key[berco].unlock_M4_2,"");
	for(i=16; i<32; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].unlock_M4_2, tmp);
	}
	strcpy(dados_live_key[berco].unlock_M5,"");
	for(i=32; i<48; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].unlock_M5, tmp);
	}
	buff = (char *)malloc(500);
	StringUpperCase (dados_live_key[berco].unlock_M4_1);
	StringUpperCase (dados_live_key[berco].unlock_M4_2);
	StringUpperCase (dados_live_key[berco].unlock_M5);
	if(modo_manual)
	{
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, "M4 - Unlock");
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].unlock_M4_1);
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].unlock_M4_2);
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, "M5 - Unlock");
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].unlock_M5);
	}
	
	first_line 	= OFF;
	GetSystemDate ( &mes, &dia, &ano);// faz o nome do arquivo 
	sprintf(buff,"%sLiveKey_M4_M5__%d-%d-%d.txt",PATH_L_KEY_M4_M5, dia,mes,ano);
	status = GetFileInfo(buff , &size);
	if (status == 1)
		 arquivo_m4_m5  = OpenFile(buff , VAL_WRITE_ONLY , VAL_APPEND , VAL_ASCII );
	else 
	{
		 arquivo_m4_m5  = OpenFile(buff , VAL_WRITE_ONLY , VAL_OPEN_AS_IS , VAL_ASCII );
		 first_line = ON;
	}
	if(arquivo_m4_m5 < 0)
	{
			MessagePopup ("Erro ao tentar coletar dados de Unlock M4/M5",
						  "Falha ao tentar abrir arquivo de coleta de dados para Live Key - Unlock M4/M5");
			free(buff);
			return FALHA_ARQUIVO_M4_M5;
	}
	if(first_line == OFF)
	{
		strcpy(buff,"----");
		status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	}
	else
		strcpy(buff, "");
	strcpy(buff,"SERIAL=");                                           
	strcat(buff,dados_berco[berco].N_Serie_EndItem);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"ECU_ID=");                                           
	strcat(buff,dados_live_key[berco].ecu_id);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Unlock_M4_1=");                                           
	strcat(buff,dados_live_key[berco].unlock_M4_1);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Unlock_M4_2=");                                           
	strcat(buff,dados_live_key[berco].unlock_M4_2);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Unlock_M5=");                                           
	strcat(buff,dados_live_key[berco].unlock_M5);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	free(buff);
	CloseFile (arquivo_m4_m5);
	if(modo_manual)
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  ATTR_DIMMED ,OFF);
		
return SUCESSO; 
	
}	
	

/******************************** Gravar_Master_Key() *****************************************************/
int Gravar_Master_Key(int berco)
{
int 
	status = -1,
	tamanho_str_masterkey = 32,
	i,
	valor,
	arquivo_m4_m5,
	first_line = OFF,
	mes,
	dia,
	ano,
	size,
	index;
double
	timeout = 1.5,
	t;
char 
	tmp[5],
	*buff;
	


	if( strlen(dados_live_key[berco].master_key_1) != tamanho_str_masterkey ||
		strlen(dados_live_key[berco].master_key_2) != tamanho_str_masterkey ||
		strlen(dados_live_key[berco].master_key_3) != tamanho_str_masterkey ||
		strlen(dados_live_key[berco].master_key_4) != tamanho_str_masterkey)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Gravar Master Key",
						  "Houve um erro ao tentar Gravar Master Key - Uma ou mais strings do Master Key est� com tamanho inv�lido");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	if(modo_manual)
		ResetTextBox (panel_CAN_diagnostico, TELA_DIAG_RESPOSTAS_M4_M5, "");
	index=0;
	for(i=0; i < tamanho_str_masterkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].master_key_1, i, 2);
		Fmt(&envio_can[berco].dados_can[index] , "%x<%s",tmp);
		index++;
	}
	for(i=0; i < tamanho_str_masterkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].master_key_2, i, 2);
		Fmt(&envio_can[berco].dados_can[index] , "%x<%s",tmp);
		index++;
	}
	for(i=0; i < tamanho_str_masterkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].master_key_3, i, 2);
		Fmt(&envio_can[berco].dados_can[index] , "%x<%s",tmp);
		index++;
	}
	for(i=0; i < tamanho_str_masterkey; i+=2)
	{
		CopyString (tmp, 0, dados_live_key[berco].master_key_4, i, 2);
		Fmt(&envio_can[berco].dados_can[index] , "%x<%s",tmp);
		index++;
	}
	t = Timer();
	servico_diagnostico[berco] = WRITE_MASTER_KEY;
	while(servico_diagnostico[berco] == WRITE_MASTER_KEY && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[2] != 0x71 || 
	   Resp_diagnostico_RX[0][berco].cData[3] != 0x01 || Resp_diagnostico_RX[0][berco].cData[4] != 0x02 ||
	   Resp_diagnostico_RX[0][berco].cData[5] != 0x72 || Resp_diagnostico_RX[0][berco].cData[6] != 0x00)
	{
		if(modo_manual)
		{
			MessagePopup ("Falha na grava��o do Master Key", "Falha na grava��o do Master Key - Talvez este dado ja esteja gravado no cluster");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	ATTR_DIMMED ,OFF);
		}
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
	
	ResetaBytesResposta_CAN(berco);
	
	CarregaResp_LiveKey(berco);

	strcpy(dados_live_key[berco].master_M4_1,"");
	for(i=0; i<16; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].master_M4_1, tmp);
	}
	strcpy(dados_live_key[berco].master_M4_2,"");
	for(i=16; i<32; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].master_M4_2, tmp);
	}
	strcpy(dados_live_key[berco].master_M5,"");
	for(i=32; i<48; i++)
	{
		if(bytes_resp_CAN_diag[i][berco] < 0x10)
			Fmt(tmp, "%s<0%x", bytes_resp_CAN_diag[i][berco]);
		else
			Fmt(tmp, "%s<%x",  bytes_resp_CAN_diag[i][berco]);
		strcat(dados_live_key[berco].master_M5, tmp);
	}
	buff = (char *)malloc(500);
	StringUpperCase (dados_live_key[berco].master_M4_1);
	StringUpperCase (dados_live_key[berco].master_M4_2);
	StringUpperCase (dados_live_key[berco].master_M5);
	if(modo_manual)
	{
		ResetTextBox 	  (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, 	   "M4 - Master");
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].master_M4_1);
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].master_M4_2);
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, "M5 - Master");
		InsertTextBoxLine (panel_CAN_diagnostico, 	TELA_DIAG_RESPOSTAS_M4_M5, -1, dados_live_key[berco].master_M5);
	}
	
	first_line 	= OFF;
	GetSystemDate ( &mes, &dia, &ano);// faz o nome do arquivo 
	sprintf(buff,"%sLiveKey_M4_M5__%d-%d-%d.txt",PATH_L_KEY_M4_M5, dia,mes,ano);
	status = GetFileInfo(buff , &size);
	if (status == 1)
		 arquivo_m4_m5  = OpenFile(buff , VAL_WRITE_ONLY , VAL_APPEND , VAL_ASCII );
	else 
	{
		 arquivo_m4_m5  = OpenFile(buff , VAL_WRITE_ONLY , VAL_OPEN_AS_IS , VAL_ASCII );
		 first_line = ON;
	}
	if(arquivo_m4_m5 < 0)
	{
			MessagePopup ("Erro ao tentar coletar dados de Master M4/M5",
						  "Falha ao tentar abrir arquivo de coleta de dados para Live Key - Master M4/M5");
			free(buff);
			return FALHA_ARQUIVO_M4_M5;
	}
	if(first_line == OFF)
	{
		strcpy(buff,"------------------------");
		status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	}
	else
		strcpy(buff, "");
	strcpy(buff,"SERIAL=");                                           
	strcat(buff,dados_berco[berco].N_Serie_EndItem);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"ECU_ID=");                                           
	strcat(buff,dados_live_key[berco].ecu_id);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Master_M4_1=");                                           
	strcat(buff,dados_live_key[berco].master_M4_1);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Master_M4_2=");                                           
	strcat(buff,dados_live_key[berco].master_M4_2);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	strcpy(buff,"Master_M5=");                                           
	strcat(buff,dados_live_key[berco].master_M5);
	status = WriteLine(arquivo_m4_m5 , buff , StringLength(buff));
	free(buff);
	CloseFile (arquivo_m4_m5);
	
	
return SUCESSO; 
	
}	
	
/******************************** CarregaResp_LiveKey() *****************************************************/
int CarregaResp_LiveKey(int berco)
{
	bytes_resp_CAN_diag[0][berco] = Resp_diagnostico_RX[0][berco].cData[7];//Valor BYTE 1
	
	bytes_resp_CAN_diag[1][berco] = Resp_diagnostico_RX[1][berco].cData[1]; 
	bytes_resp_CAN_diag[2][berco] = Resp_diagnostico_RX[1][berco].cData[2];//Valor BYTE 3  
	bytes_resp_CAN_diag[3][berco] = Resp_diagnostico_RX[1][berco].cData[3]; 
	bytes_resp_CAN_diag[4][berco] = Resp_diagnostico_RX[1][berco].cData[4];//Valor BYTE 5  
	bytes_resp_CAN_diag[5][berco] = Resp_diagnostico_RX[1][berco].cData[5]; 
	bytes_resp_CAN_diag[6][berco] = Resp_diagnostico_RX[1][berco].cData[6];//Valor BYTE 7  
	bytes_resp_CAN_diag[7][berco] = Resp_diagnostico_RX[1][berco].cData[7]; 
	
	bytes_resp_CAN_diag[8][berco] = Resp_diagnostico_RX[2][berco].cData[1];//Valor BYTE 9  
	bytes_resp_CAN_diag[9][berco] = Resp_diagnostico_RX[2][berco].cData[2]; 
	bytes_resp_CAN_diag[10][berco]= Resp_diagnostico_RX[2][berco].cData[3];//Valor BYTE 11  
	bytes_resp_CAN_diag[11][berco]= Resp_diagnostico_RX[2][berco].cData[4]; 
	bytes_resp_CAN_diag[12][berco]= Resp_diagnostico_RX[2][berco].cData[5];//Valor BYTE 13  
	bytes_resp_CAN_diag[13][berco]= Resp_diagnostico_RX[2][berco].cData[6]; 
	bytes_resp_CAN_diag[14][berco]= Resp_diagnostico_RX[2][berco].cData[7];//Valor BYTE 15
	
	bytes_resp_CAN_diag[15][berco]= Resp_diagnostico_RX[3][berco].cData[1];//Valor BYTE 16  
	bytes_resp_CAN_diag[16][berco]= Resp_diagnostico_RX[3][berco].cData[2];//Valor BYTE 17  
	bytes_resp_CAN_diag[17][berco]= Resp_diagnostico_RX[3][berco].cData[3];//Valor BYTE 18  
	bytes_resp_CAN_diag[18][berco]= Resp_diagnostico_RX[3][berco].cData[4];//Valor BYTE 19  
	bytes_resp_CAN_diag[19][berco]= Resp_diagnostico_RX[3][berco].cData[5];//Valor BYTE 20  
	bytes_resp_CAN_diag[20][berco]= Resp_diagnostico_RX[3][berco].cData[6];//Valor BYTE 21  
	bytes_resp_CAN_diag[21][berco]= Resp_diagnostico_RX[3][berco].cData[7];//Valor BYTE 22  
	
	bytes_resp_CAN_diag[22][berco]= Resp_diagnostico_RX[4][berco].cData[1];//Valor BYTE 23  
	bytes_resp_CAN_diag[23][berco]= Resp_diagnostico_RX[4][berco].cData[2];//Valor BYTE 24  
	bytes_resp_CAN_diag[24][berco]= Resp_diagnostico_RX[4][berco].cData[3];//Valor BYTE 25  
	bytes_resp_CAN_diag[25][berco]= Resp_diagnostico_RX[4][berco].cData[4];//Valor BYTE 26  
	bytes_resp_CAN_diag[26][berco]= Resp_diagnostico_RX[4][berco].cData[5];//Valor BYTE 27  
	bytes_resp_CAN_diag[27][berco]= Resp_diagnostico_RX[4][berco].cData[6];//Valor BYTE 28  
	bytes_resp_CAN_diag[28][berco]= Resp_diagnostico_RX[4][berco].cData[7];//Valor BYTE 29  
	
	bytes_resp_CAN_diag[29][berco]= Resp_diagnostico_RX[5][berco].cData[1];//Valor BYTE 30  
	bytes_resp_CAN_diag[30][berco]= Resp_diagnostico_RX[5][berco].cData[2];//Valor BYTE 31  
	bytes_resp_CAN_diag[31][berco]= Resp_diagnostico_RX[5][berco].cData[3];//Valor BYTE 32  
	bytes_resp_CAN_diag[32][berco]= Resp_diagnostico_RX[5][berco].cData[4];//Valor BYTE 33  
	bytes_resp_CAN_diag[33][berco]= Resp_diagnostico_RX[5][berco].cData[5];//Valor BYTE 34  
	bytes_resp_CAN_diag[34][berco]= Resp_diagnostico_RX[5][berco].cData[6];//Valor BYTE 35  
	bytes_resp_CAN_diag[35][berco]= Resp_diagnostico_RX[5][berco].cData[7];//Valor BYTE 36  
	
	bytes_resp_CAN_diag[36][berco]= Resp_diagnostico_RX[6][berco].cData[1];//Valor BYTE 37  
	bytes_resp_CAN_diag[37][berco]= Resp_diagnostico_RX[6][berco].cData[2];//Valor BYTE 38  
	bytes_resp_CAN_diag[38][berco]= Resp_diagnostico_RX[6][berco].cData[3];//Valor BYTE 39  
	bytes_resp_CAN_diag[39][berco]= Resp_diagnostico_RX[6][berco].cData[4];//Valor BYTE 40  
	bytes_resp_CAN_diag[40][berco]= Resp_diagnostico_RX[6][berco].cData[5];//Valor BYTE 41  
	bytes_resp_CAN_diag[41][berco]= Resp_diagnostico_RX[6][berco].cData[6];//Valor BYTE 42  
	bytes_resp_CAN_diag[42][berco]= Resp_diagnostico_RX[6][berco].cData[7];//Valor BYTE 43  
	
	bytes_resp_CAN_diag[43][berco]= Resp_diagnostico_RX[7][berco].cData[1];//Valor BYTE 44  
	bytes_resp_CAN_diag[44][berco]= Resp_diagnostico_RX[7][berco].cData[2];//Valor BYTE 45  
	bytes_resp_CAN_diag[45][berco]= Resp_diagnostico_RX[7][berco].cData[3];//Valor BYTE 46  
	bytes_resp_CAN_diag[46][berco]= Resp_diagnostico_RX[7][berco].cData[4];//Valor BYTE 47  
	bytes_resp_CAN_diag[47][berco]= Resp_diagnostico_RX[7][berco].cData[5];//Valor BYTE 48 
return SUCESSO;
}


/******************************** Gravar_General_Key() *****************************************************/
int Gravar_General_Key(SERVICO_DIAG servico_diag, int berco)
{
int 
	status = -1,
	byte_posit_resp,
	item;
double
	timeout = 1.0,
	t;
char
	tmp[100];
	
	if(servico_diag < WRITE_GENERAL_KEY2 || servico_diag > WRITE_GENERAL_KEY20)
	{
		if(modo_manual == ON)
		{
			MessagePopup ("Setup incorreto - fora de range",
			  "Falha ao tentar gravar General Key - O comando diagn�stico solicitado est� fora de range");
		}
		return -1;
	}

	if((status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco, ON)) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco] = servico_diag;
	while(servico_diagnostico[berco] == servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x10 || Resp_diagnostico_RX[0][berco].cData[2] != 0x71 || 
	   Resp_diagnostico_RX[0][berco].cData[3] != 0x01 || Resp_diagnostico_RX[0][berco].cData[4] != 0x02 ||
	   Resp_diagnostico_RX[0][berco].cData[5] != 0x72 || Resp_diagnostico_RX[0][berco].cData[6] != 0x00)
	{
		if(modo_manual)
		{
			item = (servico_diag - WRITE_GENERAL_KEY2) + 2;
			Fmt(tmp, "%s<%s%i%s", "Falha na grava��o dos General Keys - Item = ", item,  "\nEste dado pode ja estar gravado no cluster");
			MessagePopup ("Falha na grava��o dos General Key",  tmp);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  	ATTR_DIMMED ,OFF);
		}
		return Indica_comm_CAN_Not_OK();
	}
	
	Indica_comm_CAN_OK(berco);
return SUCESSO; 
}

/******************************** Ler_toda_NVM() *****************************************************/
int Ler_toda_NVM(int berco)
{
int 
	status,
	i,
	x,
	quant_bytes_por_vez = 16,
	delay_command		= OFF,
	file_handle;

	long Size = 0;	
	
unsigned int 
	temp;
unsigned long
	endereco;
char 
	nome_arquivo[500],
	*nvm_lida,
	valor_str[50],
	add_str[50];

	nvm_lida = (char *)malloc(10000);
	strcpy(nvm_lida,"");
	endereco = MIN_ADD_NVM;
	for(i=0; i < tamanho_nvm[berco]; i=(i+quant_bytes_por_vez))
	{
		Fmt(add_str, "%s<%x - ", endereco);
		StringUpperCase (add_str);
		strcat(nvm_lida, add_str);
		status = Ler_BytesNVM_Diag(endereco, quant_bytes_por_vez, delay_command ,berco);
		if(status == SUCESSO)
		{
			for(x=0; x<quant_bytes_por_vez; x++)
			{
				if(bytes_resp_CAN_diag[x][berco] < 0x10)
					Fmt(valor_str, "%s<0%x ", bytes_resp_CAN_diag[x][berco]);
				else
					Fmt(valor_str, "%s<%x ", bytes_resp_CAN_diag[x][berco]);
				StringUpperCase (valor_str);
				strcat(nvm_lida, valor_str);
				if(x== (quant_bytes_por_vez-1))
					nvm_lida[strlen(nvm_lida)-1] = '\n';
			}
			endereco = endereco + quant_bytes_por_vez;
		}
		else
			break;
	}
	if(status == SUCESSO)
	{
	        ///if (FileSelectPopupEx (PATH_LOG_CAN, "GM-Gem NVM_Dump.txt", "*.txt",
								   ///"Nome do arquivo", VAL_SAVE_BUTTON, 0, 1,
								   ///nome_arquivo) > 0)
				
			i=0;
			do
			{
				sprintf(nome_arquivo,CAMINHO_NVM"\\GM-Gem NVM_Dump_%i.txt",i);
				status = GetFileInfo(nome_arquivo , &Size);
				i++;
			}
			while((status) && (i<100));
			if(status == 0)
	        {
				file_handle = OpenFile (nome_arquivo, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
				if(file_handle < 0)
				{
					free(nvm_lida);
					MessagePopup ("Erro ao tentar abrir arquivo",
								  "Houve um erro ao tentar ABRIR arquivo para DUMP da NVM");
					return -1;
				}
				status  = WriteFile (file_handle, nvm_lida, strlen(nvm_lida));
				Delay_thread(0.3);
				CloseFile (file_handle);
				if(status < 0)
				{
					free(nvm_lida);
					MessagePopup ("Erro ao tentar gravar arquivo",
								  "Houve um erro ao tentar GRAVAR arquivo de DUMP da NVM");
					return -1;
				}
				
	        }
			MessagePopup ("SUCESSO", nome_arquivo);
			
			
			status = SUCESSO;
			
	}
	free(nvm_lida);
	
return status; 
}

/******************************** Ler_Table_DataWord() *****************************************************/
int Ler_Table_DataWord(ITEM_CALIB_TABLE item, unsigned *item_val, int delay_command ,int berco)
{
int 
	status;
unsigned int 
	temp;
unsigned long
	endereco;

	*item_val=0;
	if((endereco = Ret_endereco_item_cal_table(item, berco)) < MIN_ADD_NVM)
		return -1;
	if(item != VELO_ROTOR_OFFSET && item != TACO_ROTOR_OFFSET)
	{
		status = Ler_BytesNVM_Diag(endereco, 2, delay_command ,berco);
		if(status == SUCESSO)
		{ 
			temp = bytes_resp_CAN_diag[1][berco] ;
			temp = temp << 8;
			*item_val = (temp + bytes_resp_CAN_diag[0][berco]);
		}
	}
	else
	{
		status = Ler_BytesNVM_Diag(endereco, 1, delay_command ,berco);
		if(status == SUCESSO)
		{ 
			*item_val = bytes_resp_CAN_diag[0][berco];
		}
	}

return status; 
}

/******************************** Esc_Table_DataWord() *****************************************************/
int Esc_Table_DataWord(ITEM_CALIB_TABLE item, unsigned int item_val ,int berco)
{
int 
	status;
unsigned int 
	temp;
unsigned long
	endereco;

	if((endereco = Ret_endereco_item_cal_table(item, berco)) < MIN_ADD_NVM)
	//////////////////////////////////////////////////////////////
	if(endereco < MIN_ADD_NVM || endereco > MAX_ADD_NVM)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Gravar bytes na NVM",
						  "Falha na grava��o de dados da NVM  -  O dado do Endere�o est� fora do Range");
		}
		return -1;
	}
	envio_can[berco].dados_can[0] = item_val & 0x00FF;
	temp = item_val & 0xFF00;
	temp = temp >> 8;
	envio_can[berco].dados_can[1] = temp; 
		
	status = Gravar_BytesNVM_Diag(endereco, 2, berco, ON);
return status; 
}

/******************************** Ret_endereco_item_cal_table() *****************************************************/
unsigned long Ret_endereco_item_cal_table(ITEM_CALIB_TABLE item, int berco)
{
unsigned long
	endereco = 0;

	switch(item)
	{
		case VELO_CAN_MIN:
			endereco = add_CAN_min_speed[berco];
			break;
		case VELO_CAN_MAX:
			endereco = add_CAN_max_speed[berco];
			break;
		case VELO_CAN_POINT_0:
			endereco = add_inp_pt_0_speed[berco];
			break;
		case VELO_COUNTS_POINT_0:
			endereco = add_out_pt_0_speed[berco];
			break;
		case VELO_CAN_POINT_1:
			endereco = add_inp_pt_1_speed[berco];
			break;
		case VELO_COUNTS_POINT_1:
			endereco = add_out_pt_1_speed[berco];
			break;
		case VELO_CAN_POINT_2:
			endereco = add_inp_pt_2_speed[berco];
			break;
		case VELO_COUNTS_POINT_2:
			endereco = add_out_pt_2_speed[berco];
			break;
		case VELO_CAN_POINT_3:
			endereco = add_inp_pt_3_speed[berco];
			break;
		case VELO_COUNTS_POINT_3:
			endereco = add_out_pt_3_speed[berco];
			break;
		case VELO_CAN_POINT_4:
			endereco = add_inp_pt_4_speed[berco];
			break;
		case VELO_COUNTS_POINT_4:
			endereco = add_out_pt_4_speed[berco];
			break;
		case VELO_CAN_POINT_5:
			endereco = add_inp_pt_5_speed[berco];
			break;
		case VELO_COUNTS_POINT_5:
			endereco = add_out_pt_5_speed[berco];
			break;
		case VELO_CAN_POINT_6:
			endereco = add_inp_pt_6_speed[berco];
			break;
		case VELO_COUNTS_POINT_6:
			endereco = add_out_pt_6_speed[berco];
			break;
		case VELO_CAN_POINT_7:
			endereco = add_inp_pt_7_speed[berco];
			break;
		case VELO_COUNTS_POINT_7:
			endereco = add_out_pt_7_speed[berco];
			break;
		case VELO_ROTOR_OFFSET:
			endereco = add_rot_offset_speed[berco];
			break;
		///////////////////////////////////
		case TACO_CAN_MIN:
			endereco = add_CAN_min_taco[berco];
			break;
		case TACO_CAN_MAX:
			endereco = add_CAN_max_taco[berco];
			break;
		case TACO_CAN_POINT_0:
			endereco = add_inp_pt_0_taco[berco];
			break;
		case TACO_COUNTS_POINT_0:
			endereco = add_out_pt_0_taco[berco];
			break;
		case TACO_CAN_POINT_1:
			endereco = add_inp_pt_1_taco[berco];
			break;
		case TACO_COUNTS_POINT_1:
			endereco = add_out_pt_1_taco[berco];
			break;
		case TACO_CAN_POINT_2:
			endereco = add_inp_pt_2_taco[berco];
			break;
		case TACO_COUNTS_POINT_2:
			endereco = add_out_pt_2_taco[berco];
			break;
		case TACO_CAN_POINT_3:
			endereco = add_inp_pt_3_taco[berco];
			break;
		case TACO_COUNTS_POINT_3:
			endereco = add_out_pt_3_taco[berco];
			break;
		case TACO_CAN_POINT_4:
			endereco = add_inp_pt_4_taco[berco];
			break;
		case TACO_COUNTS_POINT_4:
			endereco = add_out_pt_4_taco[berco];
			break;
		case TACO_CAN_POINT_5:
			endereco = add_inp_pt_5_taco[berco];
			break;
		case TACO_COUNTS_POINT_5:
			endereco = add_out_pt_5_taco[berco];
			break;
		case TACO_CAN_POINT_6:
			endereco = add_inp_pt_6_taco[berco];
			break;
		case TACO_COUNTS_POINT_6:
			endereco = add_out_pt_6_taco[berco];
			break;
		case TACO_CAN_POINT_7:
			endereco = add_inp_pt_7_taco[berco];
			break;
		case TACO_COUNTS_POINT_7:
			endereco = add_out_pt_7_taco[berco];
			break;
		case TACO_ROTOR_OFFSET:
			endereco = add_rot_offset_taco[berco];
			break;
		default:
			if(modo_manual)
			{
				MessagePopup ("Erro ao tentar ler Tabela de calibra��o", 
					"Erro ao tentar ler tabela de calibra��o - A fun��o selecionada n�o existe");
			}
			return 0; //sinaliza erros pois n�o existe endere�o 0
	}
return endereco;
}

/******************************** Ler_BytesNVM_Diag() *****************************************************/
int Ler_BytesNVM_Diag(unsigned long add_init, unsigned char quantos_bytes, int delay_command, int berco)
{
int 
	status = -1,
	i,
	sair;
double
	t,
	t_2,
	timeout 	= 1.0,
	time_out_2  = 2.0;
unsigned long
	temp;

	if(add_init < MIN_ADD_NVM || add_init > MAX_ADD_NVM)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Ler bytes da NVM",
						  "Falha na leitura de dados da NVM  -  O dado do Endere�o(ADD) Inicial est� fora do Range");
		}
		return -1;
	}
	if(quantos_bytes < 1 || quantos_bytes > 16)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Ler bytes da NVM",
						  "Falha na leitura de dados da NVM  -  A quantidade de bytes a ler est� fora do Range");
		}
		return -2;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, delay_command)) < 0)
		return status;
	temp = add_init & 0xFF000000;
	temp = temp >> 24;
	Diagnostico_TX[0][berco].cData [7] = temp;
	temp = add_init & 0xFF0000;
	temp = temp >> 16;
	Diagnostico_TX[1][berco].cData [1] = temp;
	temp = add_init & 0xFF00;
	temp = temp >> 8;
	Diagnostico_TX[1][berco].cData [2] = temp;
	temp = add_init & 0xFF;
	Diagnostico_TX[1][berco].cData [3] = temp;
	//-------------------------------
	Diagnostico_TX[1][berco].cData [5] = quantos_bytes;
	ResetaBytesResposta_CAN(berco);

	t = Timer();
	servico_diagnostico[berco] = LER_BYTES_NVM;
	while(servico_diagnostico[berco] == LER_BYTES_NVM && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	//-----------------------------------
	sair = OFF;
	t_2  = Timer();
	do
	{
		t = Timer();
		servico_diagnostico[berco] = LER_BYTES_NVM_RES;
		while(servico_diagnostico[berco] == LER_BYTES_NVM_RES && Timer()-t <=timeout)
				Delay_thread(0.001);
		if(status_comunic_CAN[berco] >= 0 && Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
		   Resp_diagnostico_RX[0][berco].cData[0] == 0x10 && Resp_diagnostico_RX[0][berco].cData[2] == 0x71 && Resp_diagnostico_RX[0][berco].cData[3] == 0x03 &&
		   Resp_diagnostico_RX[0][berco].cData[4] == 0xFE && Resp_diagnostico_RX[0][berco].cData[6] == 0x03)
		{
			sair = ON;
		}
	}
	while(sair == OFF && Timer() - t_2 < time_out_2);
	if(sair == OFF)
			return Indica_comm_CAN_Not_OK();
	Indica_comm_CAN_OK(berco);
	
	ResetaBytesResposta_CAN(berco);
	bytes_resp_CAN_diag[0][berco] = Resp_diagnostico_RX[1][berco].cData[7];//Valor BYTE 1
	bytes_resp_CAN_diag[1][berco] = Resp_diagnostico_RX[2][berco].cData[1]; 
	bytes_resp_CAN_diag[2][berco] = Resp_diagnostico_RX[2][berco].cData[2];//Valor BYTE 3  
	bytes_resp_CAN_diag[3][berco] = Resp_diagnostico_RX[2][berco].cData[3]; 
	bytes_resp_CAN_diag[4][berco] = Resp_diagnostico_RX[2][berco].cData[4];//Valor BYTE 5  
	bytes_resp_CAN_diag[5][berco] = Resp_diagnostico_RX[2][berco].cData[5]; 
	bytes_resp_CAN_diag[6][berco] = Resp_diagnostico_RX[2][berco].cData[6];//Valor BYTE 7  
	bytes_resp_CAN_diag[7][berco] = Resp_diagnostico_RX[2][berco].cData[7]; 
	bytes_resp_CAN_diag[8][berco] = Resp_diagnostico_RX[3][berco].cData[1];//Valor BYTE 9  
	bytes_resp_CAN_diag[9][berco] = Resp_diagnostico_RX[3][berco].cData[2]; 
	bytes_resp_CAN_diag[10][berco]= Resp_diagnostico_RX[3][berco].cData[3];//Valor BYTE 11  
	bytes_resp_CAN_diag[11][berco]= Resp_diagnostico_RX[3][berco].cData[4]; 
	bytes_resp_CAN_diag[12][berco]= Resp_diagnostico_RX[3][berco].cData[5];//Valor BYTE 13  
	bytes_resp_CAN_diag[13][berco]= Resp_diagnostico_RX[3][berco].cData[6]; 
	bytes_resp_CAN_diag[14][berco]= Resp_diagnostico_RX[3][berco].cData[7];//Valor BYTE 15  
	bytes_resp_CAN_diag[15][berco]= Resp_diagnostico_RX[4][berco].cData[1];//Valor BYTE 16  
	
return SEM_ERRO;
}


/******************************** Gravar_BytesNVM_Diag() *****************************************************/
int Gravar_BytesNVM_Diag(unsigned long add_init, unsigned char quantos_bytes, int berco, int table_data)
{
int 
	status = -1,
	i;
double
	t,
	timeout = 1;
unsigned long
	temp;
char 
	alerta[500],
	temp_str[50];
	
	//////////////////////////////////////////////////////////////
	if(add_init < MIN_ADD_NVM || add_init > MAX_ADD_NVM)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar Gravar bytes na NVM",
						  "Falha na grava��o de dados da NVM  -  O dado do Endere�o(ADD) Inicial est� fora do Range");
		}
		return -1;
	}
	//////////////////////////////////////////////////////////////
	if(quantos_bytes < 1 || quantos_bytes > 16)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar gravar bytes da NVM",
						  "Falha na grava��o de dados da NVM  -  A quantidade de bytes a ler est� fora do Range");
		}
		return -2;
	}
	//////////////////////////////////////////////////////////////
	for(i=1; i<= quantos_bytes; i++)
	{
		if(envio_can[berco].dados_can[i-1] < 0 || envio_can[berco].dados_can[i-1] > 0xFF)
		{
			if(modo_manual)
			{
				Fmt(alerta, "%s<%s%i%s", "Falha na grava��o de dados da NVM  -  O valor do Byte " , i,  " est� fora do Range");
				MessagePopup ("Erro ao tentar gravar bytes da NVM", alerta);
			}
			return -3;
		}
	}
	for(i=quantos_bytes; i< MAX_TAMAN_ENVIO_CLUSTER; i++) //remove pr�vio flag de dado inv�lido
	{
		if(envio_can[berco].dados_can[i] == -1)
		{
			envio_can[berco].dados_can[i]	= 0;	
		}
	}
	//////////////////////////////////////////////////////////////
	if(modo_manual)
	{
		strcpy(alerta, "Voc� est� prestes a alterar dados na NVM e isto pode impactar no funcionamento do cluster.\n");
		strcat(alerta, "Voc� tem o conhecimento necess�rio para executar esta a��o e est� ciente das consequ�ncias?\n\n");
		strcat(alerta, "                                                               Deseja prosseguir?      ");
		if(ConfirmPopup ("Alerta Grava��o de dados NVM", alerta) != 1)
			return -4;
		if(table_data)
		{
			strcpy(alerta, "Voc� tem certeza que deseja gravar dados conforme as condi��es abaixo?\n\n");
			strcat(alerta, "Endere�o =");
			Fmt(temp_str, "%s<%x\n\n" , add_init);
			StringUpperCase (temp_str);
			strcat(alerta, temp_str);
			strcat(alerta, "Certifique-se que o item em 'Gauges Tables' est� selecionado corretamente)\n");								  
			strcat(alerta, "Verifique que o valor em HEXADECIMAL da WORD(2 bytes) que ir� gravar est� correto conforme aparece na tela -> 'Dado(word)'\n\n");
			strcat(alerta, "                                                                            Realmente deseja prosseguir?  ");
			if(ConfirmPopup ("Alerta Grava��o de dados NVM", alerta) != 1)
				return -6;
		}
		else
		{
			strcpy(alerta, "Voc� tem certeza que deseja gravar dados conforme as condi��es abaixo?\n\n");
			strcat(alerta, "Endere�o Inicial=");
			Fmt(temp_str, "%s<%x\n\n" , add_init);
			StringUpperCase (temp_str);
			strcat(alerta, temp_str);
			strcat(alerta, "Quantidade de Bytes=");
			Fmt(temp_str, "%s<%i\n\n" , quantos_bytes);
			strcat(alerta, temp_str);
			strcat(alerta, "Verifique se os valores em HEXADECIMAL dos bytes que ir� gravar est�o corretos conforme aparecem na tela(dados dos bytes)\n\n");
			strcat(alerta, "                                                                             Deseja prosseguir?  ");
			if(ConfirmPopup ("Alerta Grava��o de dados NVM", alerta) != 1)
				return -6;
		}
			
	}
	//////////////////////////////////////////////////////////////
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//////////////////////////////////////////////////////////////
	temp = add_init & 0xFF000000;
	temp = temp >> 24;
	Diagnostico_TX[0][berco].cData [7] = temp;
	temp = add_init & 0xFF0000;
	temp = temp >> 16;
	Diagnostico_TX[1][berco].cData [1] = temp;
	temp = add_init & 0xFF00;
	temp = temp >> 8;
	Diagnostico_TX[1][berco].cData [2] = temp;
	temp = add_init & 0xFF;
	Diagnostico_TX[1][berco].cData [3] = temp;
	//-------------------------------
	Diagnostico_TX[1][berco].cData [5] = quantos_bytes;

	t = Timer();
	servico_diagnostico[berco] = ESC_BYTES_NVM;
	while(servico_diagnostico[berco] == ESC_BYTES_NVM && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** VerifCondicaoServicoDiag() *****************************************************/
int VerifCondicaoServicoDiag (MODO_DIAGNOSTICO modo_diag_correto, int berco, int delay_uir)
{
	if(modo_manual == ON)
	{
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS,  ATTR_CTRL_VAL , OFF);
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK,  ATTR_OFF_TEXT ,"OFF");
		if(delay_uir)
			Delay_thread(0.1);
	}
	//----------- verifica condi��es ------------------------------	 
	if(modo_manual == ON && modo_diagnostico[berco] != MANTER_DIAG)
	{
		MessagePopup ("Setup incorreto - Cluster n�o est� no modo DIAG",
					  "Falha ao tentar rodar servi�o em CAN diagn�stico - o Cluster n�o est� no modo DIAGN�STICO");
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		return FALHA_CAN_NOT_IN_DIAG;
	}
	else if(modo_manual == ON && atualizar_mens_can[berco] == OFF)
	{
		MessagePopup ("Setup incorreto - Envio de mens CAN desligado",
					  "Falha ao tentar rodar servi�o em CAN diagn�stico - O envio de mensagens CAN est� desligado");
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		return FALHA_NAO_ATUALIZ_MENS_CAN;
	}
	else if(modo_manual == OFF && modo_diagnostico[berco] != MANTER_DIAG)
		return FALHA_CAN_NOT_IN_DIAG;
	else if(modo_manual == OFF && atualizar_mens_can[berco] == OFF)
		return FALHA_NAO_ATUALIZ_MENS_CAN;
	else if(modo_diag_correto != qual_diag_atual[berco] && modo_manual == ON)
	{
		MessagePopup ("Setup incorreto - Modo diagn�stico incompat�vel",
					  "Falha ao tentar rodar servi�o em CAN diagn�stico - O modo diagn�stico atual � incompat�vel com este servi�o");
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		return FALHA_CAN_MODO_INCOMPATIVEL;
	}
	else if(modo_diag_correto != qual_diag_atual[berco] && modo_manual == OFF)
	{
		return FALHA_CAN_MODO_INCOMPATIVEL;
	}

	Reseta_MensDiag(berco);
	
return SEM_ERRO;
}

/******************************** EnterSleepMode_Diag() *****************************************************/
int EnterSleepMode_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	t = Timer();
	servico_diagnostico[berco] = ENTRAR_SLEEP_MODE;
	while(servico_diagnostico[berco] == ENTRAR_SLEEP_MODE && Timer()-t <=timeout)
			Delay_thread(0.001);
	/*
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F)
	{
		return Indica_comm_CAN_Not_OK();
	}*/
	Indica_comm_CAN_OK(berco);
	modo_diagnostico[berco] 	= NOT_DIAG;
	atualizar_mens_can[berco]	= OFF;
	qual_diag_atual[berco]  	= NOT_DIAG;
	
return SEM_ERRO;
}


/******************************** Enable_gauge_Diag() *****************************************************/
int Enable_gauge_Diag(int valor, int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

	if(valor != OFF  && valor != ON)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar setar ENABLE GAUGE",
						  "Falha ao setar Enable/Disable dos gauges  -  O valor do dado est� fora do Range");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	t = Timer();
	Diagnostico_TX[0][berco].cData [5] = valor; //00=OFF  01=ON
	servico_diagnostico[berco] = ENABLE_GAUGE;
	while(servico_diagnostico[berco] == ENABLE_GAUGE && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xFE || Resp_diagnostico_RX[0][berco].cData[3] != 0xF5)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}


/******************************** CorrigirChecksum_Diag() *****************************************************/
int CorrigirChecksum_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco]= CORRIGE_CHECKSUM;
	while(servico_diagnostico[berco]== CORRIGE_CHECKSUM && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	} 
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** Whatch_dog_test_Diag() *****************************************************/
int Whatch_dog_test_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	
	
	t = Timer();
	servico_diagnostico[berco] = WATCH_DOG_CONTINUO;
	while(servico_diagnostico[berco]== WATCH_DOG_CONTINUO && Timer()-t <=timeout)
			Delay_thread(0.001);
	
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xFE || Resp_diagnostico_RX[0][berco].cData[3] != 0xF8)
	{
		return Indica_comm_CAN_Not_OK();
	} 
	Delay_thread(1);
	t = Timer();
	servico_diagnostico[berco] = WATCH_DOG_STOP;
	while(servico_diagnostico[berco]== WATCH_DOG_STOP && Timer()-t <=timeout)
			Delay_thread(0.001);
	/*
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xFE || Resp_diagnostico_RX[0][berco].cData[3] != 0xF8)
	{
		return Indica_comm_CAN_Not_OK();
	}*/ 
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** ECU_reset_Diag() *****************************************************/
int ECU_reset_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
 	//if(status = VerifCondicaoServicoDiag(EM_DIAG_CUSTOMER, berco) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco]= ECU_RESET;
	while(servico_diagnostico[berco]== ECU_RESET && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x6F || Resp_diagnostico_RX[0][berco].cData[2] != 0xF0 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFD)
	{
		return Indica_comm_CAN_Not_OK();
	} 
	Indica_comm_CAN_OK(berco);
	modo_diagnostico[berco] = NOT_DIAG;
	qual_diag_atual[berco]  = NOT_DIAG;
return SEM_ERRO;
}


/******************************** ReturnPointersStop_Diag() *****************************************************/
int ReturnPointersStop_Diag(int berco, int apenas_10_graus)
{
int 
	status = -1,
	sair,
	counts_graus;
double
	t,
	t_2,
	timeout 	= 1,
	timeout_2 	= 8;//segundos

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	if(apenas_10_graus == OFF)
	{
			status = Enable_gauge_Diag(ON, berco);
			if(status != SEM_ERRO)
			{
				if(modo_manual)
				{
					MessagePopup ("Falha ao enviar comando Enable Gauges",
							  "Comunica��o CAN falhou ao tentar enviar o comando Enble Gauges");
				}
				return -1;
			}
			if(modo_manual)
				counts_graus = COUNTS_POR_GRAU * 320;
			else
				counts_graus = COUNTS_POR_GRAU * 80;
			Delay_thread(0.100);
			status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_VELOCIMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_HIGH, 0x03 ,OFF, berco);//High Torque  - Mid Speed
			if(status != SUCESSO)
			{
				if(modo_manual)
				{
					MessagePopup ("Falha ao retornar VELOCIMETRO para Home Position",
							  "Comunica��o CAN falhou ao tentar retornar motores para posi��o de Home");
				}
				return -2;
			}
			status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_TACOMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_HIGH, 0x03 ,ON, berco);//High Torque  - Mid Speed
			if(status != SUCESSO)
			{
				if(modo_manual)
				{
					MessagePopup ("Falha ao retornar TACOMETRO para Home Position",
							  "Comunica��o CAN falhou ao tentar retornar motores para posi��o de Home");
				}
				return -2;
			}
	}
	counts_graus = COUNTS_POR_GRAU * 10;  //graus Pr�-Pre RO Homing
	status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_VELOCIMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_LOW, 0x05 ,OFF, berco); //Low torque / Low Speed
	if(status != SUCESSO)
	{
		if(modo_manual)
		{
			MessagePopup ("Falha ao retornar GAUGE VELOCIMETRO para Home Position",
					  "Comunica��o CAN falhou ao tentar retornar motores para posi��o de Pr�-Rotor Offset");
		}
		return -3;
	}
	status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_TACOMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_LOW, 0x05 ,ON, berco); //Low torque / Low Speed
	if(status != SUCESSO)
	{
		if(modo_manual)
		{
			MessagePopup ("Falha ao retornar GAUGE TACOMETRO para Home Position",
					  "Comunica��o CAN falhou ao tentar retornar motores para posi��o de Pr�-Rotor Offset");
		}
		return -3;
	}
	Delay_thread(0.100);
return status;
}


/******************************** Flip_Detect_Diag() *****************************************************/
int Flip_Detect_Diag(int qual_gauge, int zerar_contador, int flip_detected, int berco)
{
int 
	status = -1,
	sair,
	counts_graus;
double
	t,
	timeout 	= 1;//segundos

	switch(qual_gauge)
	{
		case GAUGE_TACOMETRO:
			if(zerar_contador)
			{
				dados_rotor_offset[berco].taco_rotor_value = 0xFF; //sinaliza n�o calculado(valores v�lidos s�o de 0 ... 24)
				dados_rotor_offset[berco].taco_flip_value  = 0;
				return SUCESSO;
			}
			if(flip_detected)
			{
				dados_rotor_offset[berco].taco_rotor_value = (156-dados_rotor_offset[berco].taco_flip_value) %24; // formula na Spec de calibra��o - Item 2.3 Calculate the RO_ [Step3]
				return SUCESSO;
			}
			if(dados_rotor_offset[berco].taco_rotor_value != 0xFF)
			{
				if(modo_manual)
				{
					MessagePopup ("Falha na fun��o de Clip Detect",
								  "A fun��o foi chamada por�m os valores de RO do Tacometro ja foi encontrado. A causa pode ter sido o n�o reset dos dados");
				}
				return - 1;	//se os RO foram encontrados esta fun��o n�o deveria estar sendo chamada
			}
			break;
		case GAUGE_VELOCIMETRO:
			if(zerar_contador)
			{
				dados_rotor_offset[berco].velo_rotor_value = 0xFF; //sinaliza n�o calculado(valores v�lidos s�o de 0 ... 24
				dados_rotor_offset[berco].velo_flip_value  = 0;
				return SUCESSO;
			}
			if(flip_detected)
			{
				dados_rotor_offset[berco].velo_rotor_value = (156-dados_rotor_offset[berco].velo_flip_value) %24; // formula na Spec de calibra��o - Item 2.3 Calculate the RO_ [Step3]
				return SUCESSO;
			}
			if(dados_rotor_offset[berco].velo_rotor_value != 0xFF)
			{
				if(modo_manual)
				{
					MessagePopup ("Falha na fun��o de Clip Detect",
								  "A fun��o foi chamada por�m os valores de RO do Veloc�metro ja foi encontrado. A causa pode ter sido o n�o reset dos dados");
				}
				return - 2;	//se os RO foram encontrados esta fun��o n�o deveria estar sendo chamada
			}
			break;
		case GAUGES_ALL:
			if(zerar_contador)
			{
				dados_rotor_offset[berco].taco_rotor_value = 0xFF;//sinaliza n�o calculado(valores v�lidos s�o de 0 ... 24
				dados_rotor_offset[berco].taco_flip_value  = 0;
				dados_rotor_offset[berco].velo_rotor_value = 0xFF;//sinaliza n�o calculado(valores v�lidos s�o de 0 ... 24
				dados_rotor_offset[berco].velo_flip_value  = 0;
				return SUCESSO;
			}
			if(flip_detected)
			{
				if(dados_rotor_offset[berco].taco_rotor_value == 0xFF)
					dados_rotor_offset[berco].taco_rotor_value = (156-dados_rotor_offset[berco].taco_flip_value) %24; // formula na Spec de calibra��o - Item 2.3 Calculate the RO_ [Step3]
				if(dados_rotor_offset[berco].velo_rotor_value == 0xFF)
					dados_rotor_offset[berco].velo_rotor_value = (156-dados_rotor_offset[berco].velo_flip_value) %24; // formula na Spec de calibra��o - Item 2.3 Calculate the RO_ [Step3]
				return SUCESSO;
			}
			/////////////////////
			if(dados_rotor_offset[berco].taco_rotor_value != 0xFF)
				qual_gauge = GAUGE_VELOCIMETRO;	//se ja encontrou RO do taco n�o incrementa o gauge do Taco
			if(dados_rotor_offset[berco].velo_rotor_value != 0xFF)
				qual_gauge = GAUGE_TACOMETRO;	//se ja encontrou RO do VELO n�o incrementa o gauge do Velo
			if((dados_rotor_offset[berco].velo_flip_value == 0) && (dados_rotor_offset[berco].taco_rotor_value !=0xFF || dados_rotor_offset[berco].velo_rotor_value !=0xFF))
			{
				if(modo_manual)
				{
					MessagePopup ("Falha na fun��o de Clip Detect",
								  "A fun��o foi chamada por�m os valores de RO ja foram encontrados. A causa pode ter sido o n�o reset dos dados");
				}
				return - 3;	//se os RO foram encontrados esta fun��o n�o deveria estar sendo chamada
			}
			break;
		default:
			MessagePopup ("Setup incorreto - fun��o inexistente",
			  "Falha ao tentar rodar Flip Detect GAUGE - Fun��o inexistente");
			return -4;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	counts_graus = 1;
	if(qual_gauge == GAUGES_ALL)
	{
		//status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_TACOMETRO, 	MOVE_TOWARD_STOP, GAUGE_TORQUE_HIGH, 0x00 , OFF,  berco);//Low Torque / Low Speed
		//Delay_thread(0.001);
		//status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_VELOCIMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_HIGH, 0x00 , ON, berco);//Low Torque / Low Speed
		status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_TACOMETRO, 	MOVE_TOWARD_STOP, GAUGE_TORQUE_LOW, 0x05 , OFF,  berco);//Low Torque / Low Speed
		Delay_thread(0.001);
		status = SetGauge_eol_visteon_DIAG(counts_graus, GAUGE_VELOCIMETRO, MOVE_TOWARD_STOP, GAUGE_TORQUE_LOW, 0x05 , ON, berco);//Low Torque / Low Speed
	}
	else
	{
		status = SetGauge_eol_visteon_DIAG(counts_graus, qual_gauge, MOVE_TOWARD_STOP, GAUGE_TORQUE_LOW, 0x05 , ON, berco);//Low Torque / Low Speed
	}
	if(status != SUCESSO)
	{
		if(modo_manual)
		{
			MessagePopup ("Falha ao retornar motores para Home Position",
					  "Comunica��o CAN falhou ao tentar retornar motores para Flip Detect");
		}
		return -5;
	}
	Delay_thread(0.001);
	switch(qual_gauge)
	{
		case GAUGE_TACOMETRO:
			dados_rotor_offset[berco].taco_flip_value++;
			break;
		case GAUGE_VELOCIMETRO:
			dados_rotor_offset[berco].velo_flip_value++;
			break;
		case GAUGES_ALL:
			dados_rotor_offset[berco].taco_flip_value++;
			dados_rotor_offset[berco].velo_flip_value++;
			break;
	}
return SUCESSO;
}

/******************************** EnterPointerPlacMode_Diag() *****************************************************/
int EnterPointerPlacMode_Diag(int berco)
{
int 
	status = -1,
	sair;
double
	t,
	t_2,
	timeout 	= 1,
	timeout_2 	= 8;//segundos

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	t = Timer();
	servico_diagnostico[berco]= ENTRAR_PPLACEM_MODE;
	while(servico_diagnostico[berco]== ENTRAR_PPLACEM_MODE && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	
	t_2  = Timer();
	sair = OFF;
	do
	{
		Delay_thread(0.100);
		t = Timer();
		servico_diagnostico[berco] = STATUS_PPLACEM_MODE;
		while(servico_diagnostico[berco]== STATUS_PPLACEM_MODE && Timer()-t <=timeout)
				Delay_thread(0.001);
		if(status_comunic_CAN[berco] >= 0 && Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
		   Resp_diagnostico_RX[0][berco].cData[0] == 0x05 && Resp_diagnostico_RX[0][berco].cData[1] == 0x71 && Resp_diagnostico_RX[0][berco].cData[2] == 0x03 &&
		   Resp_diagnostico_RX[0][berco].cData[3] == 0xFE && Resp_diagnostico_RX[0][berco].cData[5] == 0x03)
		{
			sair = ON;
		}
	}while(Timer() - t_2 < timeout_2 && sair == OFF);
	t_2 = Timer() - t_2;
	if(sair == OFF)
		return Indica_comm_CAN_Not_OK();
	else
		Indica_comm_CAN_OK(berco);
	
return SEM_ERRO;
}

/******************************** Programar_MEC_Diag() *****************************************************/
int Programar_MEC_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	t = Timer();
	servico_diagnostico[berco]= PROGRAMAR_MEC;
	while(servico_diagnostico[berco]== PROGRAMAR_MEC && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** Programar_MEC_Servico_Diag() *****************************************************/
int Programar_MEC_Servico_Diag(int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;

 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	t = Timer();
	servico_diagnostico[berco]= PROGRAMAR_MEC_SERVICE;
	while(servico_diagnostico[berco]== PROGRAMAR_MEC_SERVICE && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0x00)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** Programar_PN_Diag() *****************************************************/
int Programar_PN_Diag(unsigned long customer_pn, int berco)
{
int 
	status = -1;
double
	t,
	timeout = 1;
unsigned long
	temp;

	if(customer_pn < 0x01 || customer_pn > 0xFFFFFFFF)
	{
		if(modo_manual)
		{
			MessagePopup ("Erro ao tentar gravar CUSTOMER PART NUMBER",
						  "Falha na grava��o do Customer Part Number  -  O dado do PN est� fora do Range");
		}
		return -1;
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	//--------------------------------------------------------------
	//Diagnostico_TX[1][berco].cData [6] =0x00; <- dado 1 - MSB
	//Diagnostico_TX[1][berco].cData [7] =0x00; <- dado 2 
	//Diagnostico_TX[2][berco].cData [1] =0x00; <- dado 3 
	//Diagnostico_TX[2][berco].cData [2] =0x00; <- dado 4 - LSB
	temp = customer_pn & 0xFF000000;
	Diagnostico_TX[1][berco].cData [6] = temp >> 24;
	temp = customer_pn & 0xFF0000;
	Diagnostico_TX[1][berco].cData [7] = temp >> 16;
	temp = customer_pn & 0xFF00;
	Diagnostico_TX[2][berco].cData [1] = temp >> 8;
	temp = customer_pn & 0xFF;
	Diagnostico_TX[2][berco].cData [2] = temp;
	t = Timer();
	servico_diagnostico[berco]= PROGRAMAR_PN;
	while(servico_diagnostico[berco]== PROGRAMAR_PN && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}

/******************************** Programar_MTC_Diag() *****************************************************/
int Programar_MTC_Diag(int berco)
{
int 
	status = -1,
	i;
double
	t,
	timeout = 1;
unsigned long
	temp;


	for(i=0; i <= 15; i++)
	{
		if(envio_can[berco].dados_can[i] < 0x30 || envio_can[berco].dados_can[i] > 0x5A)//verifica se caracter � ASCII
		{
			if(modo_manual)
			{
				MessagePopup ("Erro ao tentar gravar MTC",
							  "Falha na grava��o do Manufacturing Traceability Characters  -  Vetor de dados com valores inv�lidos");
			}
			return -1;
		}
	}
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	t = Timer();
	servico_diagnostico[berco]= PROGRAMAR_MTC;
	while(servico_diagnostico[berco]== PROGRAMAR_MTC && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] < 0 || Resp_diagnostico_RX[0][berco].dwID != ID_CAN_DIAG_RX || 
	   Resp_diagnostico_RX[0][berco].cData[0] != 0x06 || Resp_diagnostico_RX[0][berco].cData[1] != 0x71 || Resp_diagnostico_RX[0][berco].cData[2] != 0x01 || Resp_diagnostico_RX[0][berco].cData[3] != 0xFE)
	{
		return Indica_comm_CAN_Not_OK();
	}
	Indica_comm_CAN_OK(berco);
return SEM_ERRO;
}



/********************************* Display_pattern_CAN() *******************************************************/
int Display_pattern_CAN (PADRAO_DISPLAY pattern, int berco)
{
int 
	status;
SERVICO_DIAG
	 qual_servico_diag = DIAG_SERVICE_OFF;
double
	t,
	timeout = 1.5; 

	//---------------------------------------------//
 	if((status = VerifCondicaoServicoDiag(EM_DIAG_VISTEON, berco, ON)) < 0)
		return status;
	qual_servico_diag = TFT_PATTERN_DIAG; //default
	switch (pattern)
	{	
		case PATTERN_LCD_ALL_OFF:
			if(modelo_display[berco] == DISPLAY_SEGMENTADO)
			 	qual_servico_diag = LCD_SEGM_ALL_OFF_DIAG;
			else
				Diagnostico_TX[0][berco].cData [5] = 0x00;
			break;
		case PATTERN_LCD_ALL_ON:
			if(modelo_display[berco] == DISPLAY_SEGMENTADO)
				qual_servico_diag = LCD_SEGM_ALL_ON_DIAG;
			else
				Diagnostico_TX[0][berco].cData [5] = 0x01;
			break;
		case PATTERN_LCD_3:
			if(modelo_display[berco] == DISPLAY_SEGMENTADO)
				qual_servico_diag = LCD_SEGM_PATT_3;
			else
				Diagnostico_TX[0][berco].cData [5] = 0x02;
			break;
		case PATTERN_LCD_4:
			if(modelo_display[berco] == DISPLAY_SEGMENTADO)
				qual_servico_diag = LCD_SEGM_PATT_4;
			else
				Diagnostico_TX[0][berco].cData [5] = 0x03;
			break;
		case PATTERN_LCD_RED:
				Diagnostico_TX[0][berco].cData [5] = 0x04;
			break;
		case PATTERN_LCD_GREEN:
				Diagnostico_TX[0][berco].cData [5] = 0x05;
			break;
		case PATTERN_LCD_BLUE:
				Diagnostico_TX[0][berco].cData [5] = 0x06;
			break;
		case PATTERN_LCD_GRAY_LEVEL:
				Diagnostico_TX[0][berco].cData [5] = 0x07;
			break;
		case PATTERN_LCD_COLOUR_BARS:
				Diagnostico_TX[0][berco].cData [5] = 0x08;
			break;
		default:
			if(modo_manual == ON)
			{
				SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
				MessagePopup ("Setup incorreto - fora de range",
				  "Falha ao tentar controlar DISPLAY - O valor solicitado no comando est� fora de range");
			}
			return Indica_comm_CAN_Not_OK();
	}
	
	t = Timer();
	servico_diagnostico[berco]= qual_servico_diag;
	while(servico_diagnostico[berco]== qual_servico_diag && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(status_comunic_CAN[berco] == 0 && Resp_diagnostico_RX[0][berco].dwID == ID_CAN_DIAG_RX && 
	   (Resp_diagnostico_RX[0][berco].cData[0] == 0x05 || Resp_diagnostico_RX[0][berco].cData[1] == 0x24) &&
	   (Resp_diagnostico_RX[0][berco].cData[1] == 0x6F || Resp_diagnostico_RX[0][berco].cData[2] == 0x6F))
	{
		Indica_comm_CAN_OK(berco);   // resposta segmentado ok 0x10 0x24 0x6F 0xFE 0x0B 
	}
	else
	{
		return Indica_comm_CAN_Not_OK();	 
	}
	
	
return SEM_ERRO;
}	 

/******************************** Indica_comm_CAN_OK() ***********************************************************/
void Indica_comm_CAN_OK(int berco)
{
	Diagnostico_TX[0][berco].cData[0] == 0x00;
	Diagnostico_TX[0][berco].cData[1] == 0x00;
	Diagnostico_TX[0][berco].cData[2] == 0x00;
	Diagnostico_TX[0][berco].cData[3] == 0x00;
	Diagnostico_TX[0][berco].cData[4] == 0x00;
	Diagnostico_TX[0][berco].cData[5] == 0x00;
	Diagnostico_TX[0][berco].cData[6] == 0x00;
	Diagnostico_TX[0][berco].cData[7] == 0x00;
	if(modo_manual == ON)
	{
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, ATTR_ON_COLOR, VAL_DK_GREEN); 
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, ATTR_CTRL_VAL, ON);
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
	}
}


/******************************** Indica_comm_CAN_Not_OK() ***********************************************************/
int Indica_comm_CAN_Not_OK(void)
{
	if(modo_manual == ON)
	{
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, ATTR_ON_COLOR, VAL_RED); 
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, ATTR_CTRL_VAL, ON);
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
	}
	return -1;
}


/******************************** set_cam_bit() ******************************************************************/
int set_cam_bit(EX_CAN_MSG *b_m,int can_id,int can_bit,int acao)
{
 //calcula can byte e bit
 int 
 	byte_=0,
    bit_=0,
	ativa_bit=0;
	
	
	 byte_=can_bit/8;
	 bit_=can_bit %8;
	
	
	 b_m->dwID =can_id;
	 b_m->cFlags = MESS_STANDARD; 
	 //b_m->cLength =8; 						 
	 b_m->cData;

	
	switch (byte_)	
	{
		case 0:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [0] = b_m->cData [0] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [0] = b_m->cData [0] & ativa_bit;
			}
   			break;
		case 1:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
			   	b_m->cData [1] = b_m->cData [1] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit;
				b_m->cData [1] = b_m->cData [1] & ativa_bit;
   			}
			break;		
		case 2:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [2] = b_m->cData [2] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [2] = b_m->cData [2] & ativa_bit;
			}
			break;																   
		case 3:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [3] = b_m->cData [3] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [3] = b_m->cData [3] & ativa_bit;
			}		
			break;
		case 4:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [4] = b_m->cData [4] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [4] = b_m->cData [4] & ativa_bit;
			}
		case 5:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [5] = b_m->cData [5] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [5] = b_m->cData [5] & ativa_bit;
			}
			break;
		case 6:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [6] = b_m->cData [6] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [6] = b_m->cData [6] & ativa_bit;
			}	
			break;
		case 7:
			ativa_bit = pow(2,bit_);  
			if (acao==1)
			{
				b_m->cData [7] = b_m->cData [7] | ativa_bit;
			}
			if (acao ==0) 
			{
				ativa_bit = 255-ativa_bit; 
				b_m->cData [7] = b_m->cData [7] & ativa_bit;
			}
			break;
	}	
			
	
	return ativa_bit;

}


/******************************** Erros_CAN() ******************************************************************/
int Erros_CAN()
{
double 
	time_out = 3,
	t;
int 
	status,
	res	= -1,
	sair = OFF;

retent:		
	
	t = Timer();
	do
	{
		/*if(resp_cluster_0_1[0].dwID == 0x51F)
		{
			res = resp_cluster_0_1[0].Data[1];
			if(res == 0)
				sair = ON;
		}*/
		Delay_thread(0.001);
	}while(sair == OFF && Timer() - t < time_out);
	
return res;
}


/******************************** ResetaBytesEnvio_CAN() ******************************************************************/
void ResetaBytesEnvio_CAN(int berco)
{
int 
	i=0;
	
	for(i=0; i < MAX_TAMAN_ENVIO_CLUSTER; i++) 
			envio_can[berco].dados_can[i] = -1;
}

/******************************** ResetaBytesEnvio_CAN() ******************************************************************/
void ResetaBytesResposta_CAN(int berco)
{
int 
	i=0;

	for(i=0; i<MAX_TAMAN_RESP_CLUSTER; i++)
	{
		bytes_resp_CAN_diag[i][berco] = 0;
	}
}
	
/******************************** Reseta_MensDiag() ******************************************************************/
void Reseta_MensDiag(int berco)
{
int 
	i=0;

	for(i=0; i<MAX_MENS_CAN_TX_DIAG; i++)
	{
		Diagnostico_TX[i][berco].dwID		= ID_CAN_DIAG_TX;		 
		Diagnostico_TX[i][berco].cFlags 	= MESS_STANDARD; 
		Diagnostico_TX[i][berco].cLength 	= 8; 						 
		Diagnostico_TX[i][berco].cData [7]	= 0x00; 
		Diagnostico_TX[i][berco].cData [6]	= 0x00; 
		Diagnostico_TX[i][berco].cData [5]	= 0x00; 
		Diagnostico_TX[i][berco].cData [4]	= 0x00; 
		Diagnostico_TX[i][berco].cData [3]	= 0x00; 
		Diagnostico_TX[i][berco].cData [2]	= 0x00; 
		Diagnostico_TX[i][berco].cData [1]	= 0x00; 
		Diagnostico_TX[i][berco].cData [0]	= 0x00;
	}
}	
/******************************** LoadBytes_LiveKey() ******************************************************************/
int LoadBytes_LiveKey(SERVICO_DIAG servico_diag, int berco)
{
int 
	atualizar_via_vetor;
unsigned char
	keyvalues[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	//////////////////////////////////
	key_values_2[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 
		0xE0, 0xD0, 0x8B, 0xC3, 0x17, 0x36, 0x34, 0x5A, 0x16, 0x78, 0x57, 0x2D, 0xF7, 0x1F, 0x22, 0xEC, 
	    0xA6, 0xCA, 0x2B, 0xBE, 0x12, 0x2D, 0xCA, 0x54, 0xBC, 0xC2, 0xBB, 0x91, 0x24, 0xBB, 0x70, 0x55, 
	    0x9A, 0x18, 0x3C, 0x12, 0x32, 0xD4, 0x07, 0x35, 0x57, 0x4F, 0xA8, 0x91, 0x74, 0x04, 0x80, 0xDE},
	//////////////////////////////////
	key_values_3[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x58, 0xD2, 0x44, 0x6E, 0x3F, 0xD4, 0x59, 0xD2, 0x29, 0x66, 0x1A, 0x64, 0x18, 0xF6, 0x0C, 0x3B},
	key_values_4[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x3A, 0x04, 0x88, 0xD2, 0xC2, 0x67, 0x1C, 0x4C, 0xE6, 0xAE, 0xD7, 0x9E, 0xF4, 0x08, 0x4B, 0x78},
	//////////////////////////////////
	key_values_5[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x99, 0x98, 0x5A, 0x14, 0x09, 0x1F, 0x99, 0x7B, 0x4E, 0x4E, 0x13, 0xEA, 0xAE, 0x1F, 0xEC, 0xAE},
	key_values_6[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x5B, 0x65, 0x57, 0x09, 0xDE, 0xBD, 0x8A, 0x58, 0x0C, 0x1D, 0xB2, 0xF7, 0xF4, 0x70, 0x07, 0x6A},
	//////////////////////////////////
	key_values_7[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x40, 0xA9, 0x5A, 0x37, 0xEF, 0x90, 0x56, 0xFF, 0xC1, 0xAB, 0x46, 0x2D, 0x31, 0xDB, 0x9F, 0x21},
	//////////////////////////////////
	key_values_8[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0xBE, 0x0E, 0xF7, 0x82, 0xEE, 0xE4, 0x2D, 0x9E, 0x02, 0xE1, 0x01, 0x39, 0x62, 0x89, 0x71, 0x91},
//////////////////////////////////
	key_values_9[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0x45, 0xB9, 0x78, 0x31, 0xB0, 0x98, 0x22, 0x61, 0xE1, 0x77, 0x87, 0xF7, 0x15, 0x52, 0x34, 0x77},
//////////////////////////////////
	key_values_10[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 
		0x49, 0x08, 0xAA, 0x46, 0xFC, 0x3B, 0x7B, 0xA7, 0x2F, 0xAC, 0x3F, 0x4D, 0x90, 0xBA, 0xB0, 0x7C, 
	    0x4A, 0xF7, 0x1E, 0x07, 0xDA, 0x3C, 0xF7, 0x6B, 0xBD, 0xE3, 0xD2, 0xC2, 0xDD, 0x2E, 0x86, 0x49, 
	    0xFA, 0xDB, 0x21, 0x75, 0x24, 0xD8, 0xFE, 0xAD, 0x68, 0x57, 0x9B, 0xBB, 0x91, 0xC5, 0x99, 0xFC},
	//////////////////////////////////
	key_values_11[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xEF, 0x8D, 0x4E, 0x3F, 0x08, 0xA6, 0xDF, 0xB3, 0xD1, 0x1A, 0x62, 0x05, 0xBF, 0xE5, 0x8F, 0x7A},
	//////////////////////////////////
	key_values_12[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0x39, 0x10, 0x3B, 0xE2, 0xAA, 0x94, 0x92, 0x48, 0xB0, 0x39, 0x1D, 0xE0, 0xAD, 0x59, 0x40, 0x9F},
	//////////////////////////////////
	key_values_13[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0x2A, 0x9F, 0xC0, 0x2A, 0x4A, 0xBA, 0x4C, 0xDB, 0xED, 0x6F, 0xD7, 0xC9, 0x7E, 0xA9, 0xEF, 0x16},
	//////////////////////////////////
	key_values_14[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0x9C, 0x84, 0xFC, 0x6D, 0x94, 0x7C, 0x56, 0x77, 0x1D, 0x6B, 0xC3, 0xB3, 0xCC, 0x7C, 0x3F, 0xC6},
	//////////////////////////////////
	key_values_15[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xE7, 0xE3, 0xF2, 0x9C, 0x46, 0x5B, 0xCD, 0xBC, 0xFA, 0x36, 0x59, 0x15, 0x85, 0x5E, 0xFA, 0x80},
	//////////////////////////////////
	key_values_16[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xA9, 0x55, 0xE6, 0x1C, 0x27, 0x34, 0x0D, 0xA8, 0x58, 0x8A, 0xD7, 0x93, 0xD6, 0xE2, 0x67, 0x88},
	//////////////////////////////////
	key_values_17[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xF1, 0xAA, 0x78, 0xCA, 0xED, 0x04, 0x90, 0x10, 0x9B, 0xC3, 0xF4, 0x24, 0xE5, 0x12, 0xB1, 0xDC},
 	//////////////////////////////////
	key_values_18[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xC0, 0x87, 0x30, 0xF9, 0x6A, 0xD7, 0x3E, 0x97, 0x9F, 0xE6, 0xD5, 0x4B, 0x7F, 0x11, 0x58, 0x91},
//////////////////////////////////
	key_values_19[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0x33, 0xE0, 0xE6, 0xE8, 0xEB, 0x31, 0xD3, 0xFD, 0xF0, 0xBB, 0xCE, 0x8D, 0x9D, 0xAE, 0x35, 0xDD},
	//////////////////////////////////
	key_values_20[NUM_ELEM_LIVE_KEY]=
	   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 
		0x23, 0x52, 0xA3, 0x01, 0xD5, 0xA3, 0x90, 0xBB, 0xD3, 0x2E, 0x35, 0xBF, 0xE1, 0x4C, 0x19, 0xF6, 
	    0x6C, 0x75, 0xBF, 0xFE, 0xD6, 0x80, 0x02, 0x4B, 0xBD, 0x6E, 0x5A, 0x95, 0x68, 0x1A, 0x73, 0x71, 
	    0xD1, 0x93, 0x21, 0xF2, 0x01, 0x93, 0x25, 0x63, 0x89, 0xB9, 0x9E, 0x00, 0x0F, 0xE3, 0x28, 0xDD};
	//////////////////////////////////
			
	atualizar_via_vetor = ON;
	switch(servico_diag)
	{
		case WRITE_MASTER_KEY:
		case WRITE_UNLOCK_KEY:
			atualizar_via_vetor = OFF;
			Diagnostico_TX[0][berco].cData [7] = envio_can[berco].dados_can[0];//Byte 0 at� 63
			
			Diagnostico_TX[1][berco].cData [7] = envio_can[berco].dados_can[7];
			Diagnostico_TX[1][berco].cData [6] = envio_can[berco].dados_can[6];
			Diagnostico_TX[1][berco].cData [5] = envio_can[berco].dados_can[5];
			Diagnostico_TX[1][berco].cData [4] = envio_can[berco].dados_can[4];
			Diagnostico_TX[1][berco].cData [3] = envio_can[berco].dados_can[3];
			Diagnostico_TX[1][berco].cData [2] = envio_can[berco].dados_can[2];
			Diagnostico_TX[1][berco].cData [1] = envio_can[berco].dados_can[1];
			Diagnostico_TX[1][berco].cData [0] = 0x21;
			
			Diagnostico_TX[2][berco].cData [7] = envio_can[berco].dados_can[14];
			Diagnostico_TX[2][berco].cData [6] = envio_can[berco].dados_can[13];
			Diagnostico_TX[2][berco].cData [5] = envio_can[berco].dados_can[12];
			Diagnostico_TX[2][berco].cData [4] = envio_can[berco].dados_can[11];
			Diagnostico_TX[2][berco].cData [3] = envio_can[berco].dados_can[10];
			Diagnostico_TX[2][berco].cData [2] = envio_can[berco].dados_can[9];
			Diagnostico_TX[2][berco].cData [1] = envio_can[berco].dados_can[8];
			Diagnostico_TX[2][berco].cData [0] = 0x22;
			
			Diagnostico_TX[3][berco].cData [7] = envio_can[berco].dados_can[21];
			Diagnostico_TX[3][berco].cData [6] = envio_can[berco].dados_can[20];
			Diagnostico_TX[3][berco].cData [5] = envio_can[berco].dados_can[19];
			Diagnostico_TX[3][berco].cData [4] = envio_can[berco].dados_can[18];
			Diagnostico_TX[3][berco].cData [3] = envio_can[berco].dados_can[17];
			Diagnostico_TX[3][berco].cData [2] = envio_can[berco].dados_can[16];
			Diagnostico_TX[3][berco].cData [1] = envio_can[berco].dados_can[15];
			Diagnostico_TX[3][berco].cData [0] = 0x23;
			
			Diagnostico_TX[4][berco].cData [7] = envio_can[berco].dados_can[28];
			Diagnostico_TX[4][berco].cData [6] = envio_can[berco].dados_can[27];
			Diagnostico_TX[4][berco].cData [5] = envio_can[berco].dados_can[26];
			Diagnostico_TX[4][berco].cData [4] = envio_can[berco].dados_can[25];
			Diagnostico_TX[4][berco].cData [3] = envio_can[berco].dados_can[24];
			Diagnostico_TX[4][berco].cData [2] = envio_can[berco].dados_can[23];
			Diagnostico_TX[4][berco].cData [1] = envio_can[berco].dados_can[22];
			Diagnostico_TX[4][berco].cData [0] = 0x24;
			
			Diagnostico_TX[5][berco].cData [7] = envio_can[berco].dados_can[35];
			Diagnostico_TX[5][berco].cData [6] = envio_can[berco].dados_can[34];
			Diagnostico_TX[5][berco].cData [5] = envio_can[berco].dados_can[33];
			Diagnostico_TX[5][berco].cData [4] = envio_can[berco].dados_can[32];
			Diagnostico_TX[5][berco].cData [3] = envio_can[berco].dados_can[31];
			Diagnostico_TX[5][berco].cData [2] = envio_can[berco].dados_can[30];
			Diagnostico_TX[5][berco].cData [1] = envio_can[berco].dados_can[29];
			Diagnostico_TX[5][berco].cData [0] = 0x25;
			
			Diagnostico_TX[6][berco].cData [7] = envio_can[berco].dados_can[42];
			Diagnostico_TX[6][berco].cData [6] = envio_can[berco].dados_can[41];
			Diagnostico_TX[6][berco].cData [5] = envio_can[berco].dados_can[40];
			Diagnostico_TX[6][berco].cData [4] = envio_can[berco].dados_can[39];
			Diagnostico_TX[6][berco].cData [3] = envio_can[berco].dados_can[38];
			Diagnostico_TX[6][berco].cData [2] = envio_can[berco].dados_can[37];
			Diagnostico_TX[6][berco].cData [1] = envio_can[berco].dados_can[36];
			Diagnostico_TX[6][berco].cData [0] = 0x26;
			
			Diagnostico_TX[7][berco].cData [7] = envio_can[berco].dados_can[49];
			Diagnostico_TX[7][berco].cData [6] = envio_can[berco].dados_can[48];
			Diagnostico_TX[7][berco].cData [5] = envio_can[berco].dados_can[47];
			Diagnostico_TX[7][berco].cData [4] = envio_can[berco].dados_can[46];
			Diagnostico_TX[7][berco].cData [3] = envio_can[berco].dados_can[45];
			Diagnostico_TX[7][berco].cData [2] = envio_can[berco].dados_can[44];
			Diagnostico_TX[7][berco].cData [1] = envio_can[berco].dados_can[43];
			Diagnostico_TX[7][berco].cData [0] = 0x27;
			
			Diagnostico_TX[8][berco].cData [7] = envio_can[berco].dados_can[56];
			Diagnostico_TX[8][berco].cData [6] = envio_can[berco].dados_can[55];
			Diagnostico_TX[8][berco].cData [5] = envio_can[berco].dados_can[54];
			Diagnostico_TX[8][berco].cData [4] = envio_can[berco].dados_can[53];
			Diagnostico_TX[8][berco].cData [3] = envio_can[berco].dados_can[52];
			Diagnostico_TX[8][berco].cData [2] = envio_can[berco].dados_can[51];
			Diagnostico_TX[8][berco].cData [1] = envio_can[berco].dados_can[50];
			Diagnostico_TX[8][berco].cData [0] = 0x28;
			
			Diagnostico_TX[9][berco].cData [7] = envio_can[berco].dados_can[63];
			Diagnostico_TX[9][berco].cData [6] = envio_can[berco].dados_can[62];
			Diagnostico_TX[9][berco].cData [5] = envio_can[berco].dados_can[61];
			Diagnostico_TX[9][berco].cData [4] = envio_can[berco].dados_can[60];
			Diagnostico_TX[9][berco].cData [3] = envio_can[berco].dados_can[59];
			Diagnostico_TX[9][berco].cData [2] = envio_can[berco].dados_can[58];
			Diagnostico_TX[9][berco].cData [1] = envio_can[berco].dados_can[57];
			Diagnostico_TX[9][berco].cData [0] = 0x29;
			break;
		case WRITE_GENERAL_KEY2:
			memcpy (keyvalues, key_values_2, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY3:
			memcpy (keyvalues, key_values_3, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY4:
			memcpy (keyvalues, key_values_4, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY5:
			memcpy (keyvalues, key_values_5, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY6:
			memcpy (keyvalues, key_values_6, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY7:
			memcpy (keyvalues, key_values_7, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY8:
			memcpy (keyvalues, key_values_8, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY9:
			memcpy (keyvalues, key_values_9, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY10:
			memcpy (keyvalues, key_values_10, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY11:
			memcpy (keyvalues, key_values_11, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY12:
			memcpy (keyvalues, key_values_12, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY13:
			memcpy (keyvalues, key_values_13, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY14:
			memcpy (keyvalues, key_values_14, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY15:
			memcpy (keyvalues, key_values_15, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY16:
			memcpy (keyvalues, key_values_16, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY17:
			memcpy (keyvalues, key_values_17, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY18:
			memcpy (keyvalues, key_values_18, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY19:
			memcpy (keyvalues, key_values_19, NUM_ELEM_LIVE_KEY );
			break;
		case WRITE_GENERAL_KEY20:
			memcpy (keyvalues, key_values_20, NUM_ELEM_LIVE_KEY );
			break;
			
		case WRITE_ECU_ID:
			atualizar_via_vetor = OFF;
			Diagnostico_TX[1][berco].cData [7] = envio_can[berco].dados_can[1]; 
			Diagnostico_TX[1][berco].cData [6] = envio_can[berco].dados_can[0];//Byte 0 at� 15 ; 
			
			Diagnostico_TX[2][berco].cData [7] = envio_can[berco].dados_can[8];
			Diagnostico_TX[2][berco].cData [6] = envio_can[berco].dados_can[7];
			Diagnostico_TX[2][berco].cData [5] = envio_can[berco].dados_can[6];
			Diagnostico_TX[2][berco].cData [4] = envio_can[berco].dados_can[5];
			Diagnostico_TX[2][berco].cData [3] = envio_can[berco].dados_can[4];
			Diagnostico_TX[2][berco].cData [2] = envio_can[berco].dados_can[3];
			Diagnostico_TX[2][berco].cData [1] = envio_can[berco].dados_can[2];
			Diagnostico_TX[2][berco].cData [0] = 0x22;
		
			Diagnostico_TX[3][berco].cData [7] = envio_can[berco].dados_can[15];
			Diagnostico_TX[3][berco].cData [6] = envio_can[berco].dados_can[14];
			Diagnostico_TX[3][berco].cData [5] = envio_can[berco].dados_can[13];
			Diagnostico_TX[3][berco].cData [4] = envio_can[berco].dados_can[12];
			Diagnostico_TX[3][berco].cData [3] = envio_can[berco].dados_can[11];
			Diagnostico_TX[3][berco].cData [2] = envio_can[berco].dados_can[10];
			Diagnostico_TX[3][berco].cData [1] = envio_can[berco].dados_can[9];
			Diagnostico_TX[3][berco].cData [0] = 0x23;
			break;
		default:
			return -1;
	}
	if(atualizar_via_vetor)
	{
			Diagnostico_TX[0][berco].cData [7] = keyvalues[0];//Byte 0 at� 63
			
			Diagnostico_TX[1][berco].cData [7] = keyvalues[7];//7
			Diagnostico_TX[1][berco].cData [6] = keyvalues[6];
			Diagnostico_TX[1][berco].cData [5] = keyvalues[5];
			Diagnostico_TX[1][berco].cData [4] = keyvalues[4];
			Diagnostico_TX[1][berco].cData [3] = keyvalues[3];
			Diagnostico_TX[1][berco].cData [2] = keyvalues[2];
			Diagnostico_TX[1][berco].cData [1] = keyvalues[1];
			Diagnostico_TX[1][berco].cData [0] = 0x21;
			
			Diagnostico_TX[2][berco].cData [7] = keyvalues[14];//14
			Diagnostico_TX[2][berco].cData [6] = keyvalues[13];
			Diagnostico_TX[2][berco].cData [5] = keyvalues[12];
			Diagnostico_TX[2][berco].cData [4] = keyvalues[11];
			Diagnostico_TX[2][berco].cData [3] = keyvalues[10];
			Diagnostico_TX[2][berco].cData [2] = keyvalues[9];
			Diagnostico_TX[2][berco].cData [1] = keyvalues[8];//8
			Diagnostico_TX[2][berco].cData [0] = 0x22;
			
			Diagnostico_TX[3][berco].cData [7] = keyvalues[21];
			Diagnostico_TX[3][berco].cData [6] = keyvalues[20];
			Diagnostico_TX[3][berco].cData [5] = keyvalues[19];
			Diagnostico_TX[3][berco].cData [4] = keyvalues[18];
			Diagnostico_TX[3][berco].cData [3] = keyvalues[17];
			Diagnostico_TX[3][berco].cData [2] = keyvalues[16];
			Diagnostico_TX[3][berco].cData [1] = keyvalues[15];
			Diagnostico_TX[3][berco].cData [0] = 0x23;
			
			Diagnostico_TX[4][berco].cData [7] = keyvalues[28];
			Diagnostico_TX[4][berco].cData [6] = keyvalues[27];
			Diagnostico_TX[4][berco].cData [5] = keyvalues[26];
			Diagnostico_TX[4][berco].cData [4] = keyvalues[25];
			Diagnostico_TX[4][berco].cData [3] = keyvalues[24];
			Diagnostico_TX[4][berco].cData [2] = keyvalues[23];
			Diagnostico_TX[4][berco].cData [1] = keyvalues[22];
			Diagnostico_TX[4][berco].cData [0] = 0x24;
			
			Diagnostico_TX[5][berco].cData [7] = keyvalues[35];
			Diagnostico_TX[5][berco].cData [6] = keyvalues[34];
			Diagnostico_TX[5][berco].cData [5] = keyvalues[33];
			Diagnostico_TX[5][berco].cData [4] = keyvalues[32];
			Diagnostico_TX[5][berco].cData [3] = keyvalues[31];
			Diagnostico_TX[5][berco].cData [2] = keyvalues[30];
			Diagnostico_TX[5][berco].cData [1] = keyvalues[29];
			Diagnostico_TX[5][berco].cData [0] = 0x25;
			
			Diagnostico_TX[6][berco].cData [7] = keyvalues[42];
			Diagnostico_TX[6][berco].cData [6] = keyvalues[41];
			Diagnostico_TX[6][berco].cData [5] = keyvalues[40];
			Diagnostico_TX[6][berco].cData [4] = keyvalues[39];
			Diagnostico_TX[6][berco].cData [3] = keyvalues[38];
			Diagnostico_TX[6][berco].cData [2] = keyvalues[37];
			Diagnostico_TX[6][berco].cData [1] = keyvalues[36];
			Diagnostico_TX[6][berco].cData [0] = 0x26;
			
			Diagnostico_TX[7][berco].cData [7] = keyvalues[49];
			Diagnostico_TX[7][berco].cData [6] = keyvalues[48];
			Diagnostico_TX[7][berco].cData [5] = keyvalues[47];
			Diagnostico_TX[7][berco].cData [4] = keyvalues[46];
			Diagnostico_TX[7][berco].cData [3] = keyvalues[45];
			Diagnostico_TX[7][berco].cData [2] = keyvalues[44];
			Diagnostico_TX[7][berco].cData [1] = keyvalues[43];
			Diagnostico_TX[7][berco].cData [0] = 0x27;
			
			Diagnostico_TX[8][berco].cData [7] = keyvalues[56];
			Diagnostico_TX[8][berco].cData [6] = keyvalues[55];
			Diagnostico_TX[8][berco].cData [5] = keyvalues[54];
			Diagnostico_TX[8][berco].cData [4] = keyvalues[53];
			Diagnostico_TX[8][berco].cData [3] = keyvalues[52];
			Diagnostico_TX[8][berco].cData [2] = keyvalues[51];
			Diagnostico_TX[8][berco].cData [1] = keyvalues[50];
			Diagnostico_TX[8][berco].cData [0] = 0x28;
			
			Diagnostico_TX[9][berco].cData [7] = keyvalues[63];
			Diagnostico_TX[9][berco].cData [6] = keyvalues[62];
			Diagnostico_TX[9][berco].cData [5] = keyvalues[61];
			Diagnostico_TX[9][berco].cData [4] = keyvalues[60];
			Diagnostico_TX[9][berco].cData [3] = keyvalues[59];
			Diagnostico_TX[9][berco].cData [2] = keyvalues[58];
			Diagnostico_TX[9][berco].cData [1] = keyvalues[57];
			Diagnostico_TX[9][berco].cData [0] = 0x29;
	}

return SEM_ERRO;
}

/******************************** LoadBytes_LiveKey() ******************************************************************/
int	LerMens_SysBkUpPwrMd(int berco, int *configurado)
{
int 
	status;
double
	t;

	Delay_thread(0.001);
	*configurado = OFF;
	SysBkUpPwrMd[berco].cData[0] = 0x00;
	SysBkUpPwrMd[berco].cData[1] = 0x00;
	SysBkUpPwrMd[berco].cData[2] = 0x00;
	SysBkUpPwrMd[berco].cData[3] = 0x00;
	SysBkUpPwrMd[berco].cData[4] = 0x00;
	SysBkUpPwrMd[berco].cData[5] = 0x00;
	SysBkUpPwrMd[berco].cData[6] = 0x00;
	SysBkUpPwrMd[berco].cData[7] = 0x00;
	Resp_diagnostico_RX[0][berco].dwID = 0x00;
	t = Timer();
	while((Resp_diagnostico_RX[0][berco].dwID != SysBkUpPwrMd[berco].dwID) && Timer()- t < 0.2)
	{
		Delay_thread(0.001);
		status = Recebe_can_RX_NI(0, berco);
	}
	if(status < 0)
		return status;
	SysBkUpPwrMd[berco].cData[0] = Resp_diagnostico_RX[0][berco].cData[0];
	SysBkUpPwrMd[berco].cData[1] = Resp_diagnostico_RX[0][berco].cData[1];
	SysBkUpPwrMd[berco].cData[2] = Resp_diagnostico_RX[0][berco].cData[2];
	SysBkUpPwrMd[berco].cData[3] = Resp_diagnostico_RX[0][berco].cData[3];
	SysBkUpPwrMd[berco].cData[4] = Resp_diagnostico_RX[0][berco].cData[4];
	SysBkUpPwrMd[berco].cData[5] = Resp_diagnostico_RX[0][berco].cData[5];
	SysBkUpPwrMd[berco].cData[6] = Resp_diagnostico_RX[0][berco].cData[6];
	SysBkUpPwrMd[berco].cData[7] = Resp_diagnostico_RX[0][berco].cData[7];
	if(Resp_diagnostico_RX[0][berco].dwID == SysBkUpPwrMd[berco].dwID && status == SUCESSO)
	{
		if( SysBkUpPwrMd[berco].cData[0] != 0 && 
			SysBkUpPwrMd[berco].cData[1] != 0 && SysBkUpPwrMd[berco].cData[2] != 0)
		{
			*configurado = ON;
		}
	}
	
return status;
}


 /*************************** GravaSequencia_general_keys() ******************************************************************/
int GravaSequencia_general_keys(int berco)
{
int 
	status;

			status = Gravar_General_Key(WRITE_GENERAL_KEY2, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY3) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY3, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY4) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY4, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY5) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY5, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY6) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY6, berco);
			CheckIf_Sucesso
			
			if(Modo_manual_general_key(WRITE_GENERAL_KEY7) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY7, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY8) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY8, berco);
			CheckIf_Sucesso
			
			if(Modo_manual_general_key(WRITE_GENERAL_KEY9) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY9, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY10) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY10, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY11) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY11, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY12) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY12, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY13) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY13, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY14) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY14, berco);
			CheckIf_Sucesso
			
			if(Modo_manual_general_key(WRITE_GENERAL_KEY15) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY15, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY16) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY16, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY17) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY17, berco);
			CheckIf_Sucesso
				
			if(Modo_manual_general_key(WRITE_GENERAL_KEY18) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY18, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY19) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY19, berco);
			CheckIf_Sucesso

			if(Modo_manual_general_key(WRITE_GENERAL_KEY20) < 1)
				return -1;
			status = Gravar_General_Key(WRITE_GENERAL_KEY20, berco);
			if(modo_manual && status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  	ATTR_DIMMED ,OFF);
			}
	
return status;
}

 /*************************** Modo_manual_general_key() ******************************************************************/
int Modo_manual_general_key(SERVICO_DIAG item)
{
int status = -1;

	if(modo_manual == OFF)
	{
		Delay_thread(0.070);//se for grava��es em sequencia n�o manual dar delay entre elas(ajustar durante debug da EOL & Vision)
		return 1;
	}
	switch(item)
	{
		case WRITE_GENERAL_KEY2:
			status = ConfirmPopup ("Confirmar grava��o do General Key-2",
						"Voc� confirma que deseja fazer a grava��o do General Key 2?");
			break;
		case WRITE_GENERAL_KEY3:
			status = ConfirmPopup ("Confirmar grava��o do General Key-3",
						"Voc� confirma que deseja fazer a grava��o do General Key 3?");
			break;
		case WRITE_GENERAL_KEY4:
			status = ConfirmPopup ("Confirmar grava��o do General Key-4",
						"Voc� confirma que deseja fazer a grava��o do General Key 4?");
			break;
		case WRITE_GENERAL_KEY5:
			status = ConfirmPopup ("Confirmar grava��o do General Key-5",
						"Voc� confirma que deseja fazer a grava��o do General Key 5?");
			break;
		case WRITE_GENERAL_KEY6:
			status = ConfirmPopup ("Confirmar grava��o do General Key-6",
						"Voc� confirma que deseja fazer a grava��o do General Key 6?");
			break;
		case WRITE_GENERAL_KEY7:
			status = ConfirmPopup ("Confirmar grava��o do General Key-7",
						"Voc� confirma que deseja fazer a grava��o do General Key 7?");
			break;
		case WRITE_GENERAL_KEY8:
			status = ConfirmPopup ("Confirmar grava��o do General Key-8",
						"Voc� confirma que deseja fazer a grava��o do General Key 8?");
			break;
		case WRITE_GENERAL_KEY9:
			status = ConfirmPopup ("Confirmar grava��o do General Key-9",
						"Voc� confirma que deseja fazer a grava��o do General Key 9?");
			break;
		case WRITE_GENERAL_KEY10:
			status = ConfirmPopup ("Confirmar grava��o do General Key-10",
						"Voc� confirma que deseja fazer a grava��o do General Key 10?");
			break;
		case WRITE_GENERAL_KEY11:
			status = ConfirmPopup ("Confirmar grava��o do General Key-11",
						"Voc� confirma que deseja fazer a grava��o do General Key 11?");
			break;
		case WRITE_GENERAL_KEY12:
			status = ConfirmPopup ("Confirmar grava��o do General Key-12",
						"Voc� confirma que deseja fazer a grava��o do General Key 12?");
			break;
		case WRITE_GENERAL_KEY13:
			status = ConfirmPopup ("Confirmar grava��o do General Key-13",
						"Voc� confirma que deseja fazer a grava��o do General Key 13?");
			break;
		case WRITE_GENERAL_KEY14:
			status = ConfirmPopup ("Confirmar grava��o do General Key-14",
						"Voc� confirma que deseja fazer a grava��o do General Key 14?");
			break;
		case WRITE_GENERAL_KEY15:
			status = ConfirmPopup ("Confirmar grava��o do General Key-15",
						"Voc� confirma que deseja fazer a grava��o do General Key 15?");
			break;
		case WRITE_GENERAL_KEY16:
			status = ConfirmPopup ("Confirmar grava��o do General Key-16",
						"Voc� confirma que deseja fazer a grava��o do General Key 16?");
			break;
		case WRITE_GENERAL_KEY17:
			status = ConfirmPopup ("Confirmar grava��o do General Key-17",
						"Voc� confirma que deseja fazer a grava��o do General Key 17?");
			break;
		case WRITE_GENERAL_KEY18:
			status = ConfirmPopup ("Confirmar grava��o do General Key-18",
						"Voc� confirma que deseja fazer a grava��o do General Key 18?");
			break;
		case WRITE_GENERAL_KEY19:
			status = ConfirmPopup ("Confirmar grava��o do General Key-19",
						"Voc� confirma que deseja fazer a grava��o do General Key 19?");
			break;
		case WRITE_GENERAL_KEY20:
			status = ConfirmPopup ("Confirmar grava��o do General Key-20",
						"Voc� confirma que deseja fazer a grava��o do General Key 20?");
			break;
		default:
			status = 0;
	}
return status;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//18/06/2019
int F_read_VPPS(int berco, char *VPPS) 
{
double
	timeout = 2.0,
	t;

	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		Delay_thread(0.01);
	}
	t = Timer();
	servico_diagnostico[berco] = LER_VPPS;
	while(servico_diagnostico[berco] == LER_VPPS && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		Delay_thread(0.01);
	}
	if(Resp_diagnostico_RX[0][berco].cData[0]  !=0x10 ||
	   Resp_diagnostico_RX[0][berco].cData[1]  !=0x11 ||	
	   Resp_diagnostico_RX[0][berco].cData[2]  !=0x62 ||
	   Resp_diagnostico_RX[0][berco].cData[3]  !=0xF0 ||
	   Resp_diagnostico_RX[0][berco].cData[4]  !=0xAB)
		return -1;

	 VPPS[0] = Resp_diagnostico_RX[0][berco].cData[5];
	 VPPS[1] = Resp_diagnostico_RX[0][berco].cData[6];   
	 VPPS[2] = Resp_diagnostico_RX[0][berco].cData[7]; 
	 
	 VPPS[3] = Resp_diagnostico_RX[1][berco].cData[1];   
	 VPPS[4] = Resp_diagnostico_RX[1][berco].cData[2];   
	 VPPS[5] = Resp_diagnostico_RX[1][berco].cData[3];   
	 VPPS[6] = Resp_diagnostico_RX[1][berco].cData[4];   
	 VPPS[7] = Resp_diagnostico_RX[1][berco].cData[5];   
	 VPPS[8] = Resp_diagnostico_RX[1][berco].cData[6];   
	 VPPS[9] = Resp_diagnostico_RX[1][berco].cData[7];   
	 
	 VPPS[10] = Resp_diagnostico_RX[2][berco].cData[1];   
	 VPPS[11] = Resp_diagnostico_RX[2][berco].cData[2];   
	 VPPS[12] = Resp_diagnostico_RX[2][berco].cData[3]; 
	 VPPS[13] = Resp_diagnostico_RX[2][berco].cData[4]; 
	
	 return SUCESSO; 
}



int F_write_VPPS(int berco, char *VPPS)
{
char 
	cluster_VPPS [30] = {0};	
double
	timeout = 2.0,
	t;

	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		Delay_thread(0.01);
	}
	
	if (strlen(VPPS) > VPPS_LENGHT)
			return -1;			
	
    strcpy(cluster_VPPS,VPPS);		
	
	bytes_envio_CAN_diag[13] [berco] = cluster_VPPS[13]; //data 13
	bytes_envio_CAN_diag[12] [berco] = cluster_VPPS[12]; 
	bytes_envio_CAN_diag[11] [berco] = cluster_VPPS[11]; 
	bytes_envio_CAN_diag[10] [berco] = cluster_VPPS[10]; 
	bytes_envio_CAN_diag[9]  [berco] = cluster_VPPS[9]; 
	
	bytes_envio_CAN_diag[8] [berco] = cluster_VPPS[8];  
	bytes_envio_CAN_diag[7] [berco] = cluster_VPPS[7];  
	bytes_envio_CAN_diag[6] [berco] = cluster_VPPS[6];  
	bytes_envio_CAN_diag[5] [berco] = cluster_VPPS[5];  
	bytes_envio_CAN_diag[4] [berco] = cluster_VPPS[4];  
	bytes_envio_CAN_diag[3] [berco] = cluster_VPPS[3];  
	bytes_envio_CAN_diag[2] [berco] = cluster_VPPS[2];  
	
	bytes_envio_CAN_diag[1] [berco] = cluster_VPPS[1];  
	bytes_envio_CAN_diag[0] [berco] = cluster_VPPS[0]; //data 0
	
	
	t = Timer(); 
	servico_diagnostico[berco] = ESC_VPPS;
	while(servico_diagnostico[berco] == ESC_VPPS && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		Delay_thread(0.01);
	}
	if(Resp_diagnostico_RX[0][berco].cData[0]  !=0x6  ||
	   Resp_diagnostico_RX[0][berco].cData[1]  !=0x71 ||	
	   /*Resp_diagnostico_RX[0][berco].cData[2]  !=0x03 || */
	   Resp_diagnostico_RX[0][berco].cData[3]  !=0xFE ||
	   Resp_diagnostico_RX[0][berco].cData[4]  !=0x20 ||
	   Resp_diagnostico_RX[0][berco].cData[5]  !=0x03 ||  
	   Resp_diagnostico_RX[0][berco].cData[6]  !=0x02)    
	   //|| Resp_diagnostico_RX[0][berco].cData[7]  !=0xAA)  
		return -2;
	
	 return SUCESSO; 
}



int F_read_DUNS(int berco, char *DUNS)
{
double
	timeout = 2.0,
	t;

	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		Delay_thread(0.01);
	}
	t = Timer();
	servico_diagnostico[berco] = LER_DUNS;
	while(servico_diagnostico[berco] == LER_DUNS && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		Delay_thread(0.01);
	}
	if(Resp_diagnostico_RX[0][berco].cData[0]  !=0x10 ||
	   Resp_diagnostico_RX[0][berco].cData[1]  !=0x0C ||	
	   Resp_diagnostico_RX[0][berco].cData[2]  !=0x62 ||
	   Resp_diagnostico_RX[0][berco].cData[3]  !=0xF0 ||
	   Resp_diagnostico_RX[0][berco].cData[4]  !=0xB3)
		return -1;

	 DUNS[0] = Resp_diagnostico_RX[0][berco].cData[5];
	 DUNS[1] = Resp_diagnostico_RX[0][berco].cData[6];   
	 DUNS[2] = Resp_diagnostico_RX[0][berco].cData[7]; 
	 
	 DUNS[3] = Resp_diagnostico_RX[1][berco].cData[1];   
	 DUNS[4] = Resp_diagnostico_RX[1][berco].cData[2];   
	 DUNS[5] = Resp_diagnostico_RX[1][berco].cData[3];   
	 DUNS[6] = Resp_diagnostico_RX[1][berco].cData[4];   
	 DUNS[7] = Resp_diagnostico_RX[1][berco].cData[5];   
	 DUNS[8] = Resp_diagnostico_RX[1][berco].cData[6];   
	 DUNS[9] = Resp_diagnostico_RX[1][berco].cData[7];   
	 
	
	 return SUCESSO; 
}



int F_write_DUNS(int berco, char *DUNS) 
{
char 
	cluster_DUNS [30] = {0};	
double
	timeout = 2.0,
	t;

	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, ON);
		Delay_thread(0.01);
	}
	
	if (strlen(DUNS) > DUNS_LENGHT)
		return -1;			
	
	strcpy (cluster_DUNS,DUNS);
	
	bytes_envio_CAN_diag[8] [berco] = cluster_DUNS[8]; //data 9
	bytes_envio_CAN_diag[7] [berco] = cluster_DUNS[7];  
	bytes_envio_CAN_diag[6] [berco] = cluster_DUNS[6];  
	bytes_envio_CAN_diag[5] [berco] = cluster_DUNS[5];  
	bytes_envio_CAN_diag[4] [berco] = cluster_DUNS[4];  
	bytes_envio_CAN_diag[3] [berco] = cluster_DUNS[3];  
	bytes_envio_CAN_diag[2] [berco] = cluster_DUNS[2];  
	
	bytes_envio_CAN_diag[1] [berco] = cluster_DUNS[1];  
	bytes_envio_CAN_diag[0] [berco] = cluster_DUNS[0]; //data 0
	
	t = Timer();
	servico_diagnostico[berco] = ESC_DUNS;
	while(servico_diagnostico[berco] == ESC_DUNS && Timer()-t <=timeout)
			Delay_thread(0.001);
	if(modo_manual == ON)
	{
		SetPanelAttribute (panel_CAN_diagnostico, ATTR_DIMMED, OFF);
		Delay_thread(0.01);
	}
	if(Resp_diagnostico_RX[0][berco].cData[0]  !=0x6  ||
	   Resp_diagnostico_RX[0][berco].cData[1]  !=0x71 ||	
	   /*Resp_diagnostico_RX[0][berco].cData[2]  !=0x03 || */
	   Resp_diagnostico_RX[0][berco].cData[3]  !=0xFE ||
	   Resp_diagnostico_RX[0][berco].cData[4]  !=0x20 ||
	   Resp_diagnostico_RX[0][berco].cData[5]  !=0x03 ||  
	   Resp_diagnostico_RX[0][berco].cData[6]  !=0x02)    
	   //|| Resp_diagnostico_RX[0][berco].cData[7]  !=0xAA)  
		return -2;
	

	
	 return SUCESSO; 
}
