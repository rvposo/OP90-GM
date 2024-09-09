
#include "cvixml.h"
#include "Windows.h"
#include <formatio.h>
#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "Adm Equip.h"
#include "Global Error Tracking.h"
#include "Main OP090 GM-GEM.h"
#include "Auto OP090 GM-GEM.h"
#include "Manual OP090 GM-GEM.h"
#include "CAN GM-GEM.h"

//
// Fun��o: ThreadSistema()
//
int CVICALLBACK ThreadSistema (void *parametro)
{
	static double
		tempo_presenca_berco_1,
		tempo_presenca_berco_2;
	int
		i,
		i2c_sist_err_quant=0,
		status,
		t_str_serial,
		tamanho;

	////////////////////////////////

	tempo_presenca_berco_1 = 0;
	tempo_presenca_berco_2 = 0;
	SetSleepPolicy (MODO_SLEEP);
	CmtSetCurrentThreadPriority (THREAD_PRIORITY_HIGHEST);
	while (!finalizar_thread_sistema)
	{
		if (HW_present == OFF)
			Delay_thread(.1);
		
		switch(modo_thread)
		{
			case LEITURA_APENAS:
				status = Le_Entradas(END_CARTAO_1_ENTRADA);
				CheckI2C_err
				status = Le_Entradas(END_CARTAO_5_ENTRADA);
				CheckI2C_err
				break;
			case ESCRITA_APENAS:
				status = AtualizaCartaoSaida(END_CARTAO_2_SAIDA);
				CheckI2C_err
				status = AtualizaCartaoSaida(END_CARTAO_3_SAIDA);
				CheckI2C_err
				status = AtualizaCartaoSaida(END_CARTAO_4_SAIDA);
				CheckI2C_err
				//////
				STATUS.Continua = OFF;
				STATUS.Rejeita = OFF;
				motions_clear_to_move = OFF;
				status_bimanual = OFF;
				break;

			case ESCRITA_E_LEITURA:

				Status_Seguranca();
				status = Le_Entradas(END_CARTAO_1_ENTRADA);
				CheckI2C_err
				status = Le_Entradas(END_CARTAO_5_ENTRADA);
				CheckI2C_err
				status = AtualizaCartaoSaida(END_CARTAO_2_SAIDA);
				CheckI2C_err
				status = AtualizaCartaoSaida(END_CARTAO_3_SAIDA);
				CheckI2C_err
				status = AtualizaCartaoSaida(END_CARTAO_4_SAIDA);
				CheckI2C_err
				for (i=0;i<NUM_SCANNERS;i++)
				{
					if( dados_scanner[i].habilitar_leitor_enditem == ON )
					{
						Habilita_Scanner(i);
						dados_scanner[i].habilitar_leitor_enditem = OFF;
					}
					if( dados_scanner[i].desabilitar_leitor_enditem == ON )
					{
						Desabilita_Scanner(i);
						dados_scanner[i].desabilitar_leitor_enditem = OFF;
					}
					
					if (HW_present  == ON)
					{	
						if( dados_scanner[i].ler_string_scanner == ON )
						{
							//Delay_thread(.1);
							t_str_serial = VM_GetInQLen (dados_scanner[i].comm_scanner);
							if(t_str_serial  > 0 )
							{
								strcpy(dados_scanner[i].strGotScanner, "\0" );
								Delay(0.005);
								for(tamanho =0; tamanho < t_str_serial; tamanho++)
								{
									dados_scanner[i].strGotScanner[tamanho] = 0;
								}
								status = VM_ComRdTerm (dados_scanner[i].comm_scanner, dados_scanner[i].strGotScanner, tamanho, 13 ); //aqui
							
								dados_scanner[i].leitor_scanner_ativado = OFF;
								dados_scanner[i].tempo_scanner_enditem_ligado = 0;
								Delay(0.001);
							
								VM_FlushInQ (dados_scanner[i].comm_scanner);
							}
						}
					}	
				}
				break;

			case PARAR_ESC_LEIT:
				STATUS.Continua = OFF;
				STATUS.Rejeita = OFF;
				motions_clear_to_move = OFF;
				status_bimanual = OFF;
				break;
		}

		if(modo_thread == LEITURA_APENAS || modo_thread == ESCRITA_E_LEITURA)
		{
			Status_Seguranca();
			// verifica Presen�a do Produto no Ber�o 1
			if(STATUS.PresCluster_1 == OFF && (Timer()-tempo_presenca_berco_1) >  TEMPO_MAX_AUSENCIA)
				dados_berco[BERCO_1].status_debounc_presenca_produto = OFF;
			else if(STATUS.PresCluster_1 == ON && (Timer()-tempo_presenca_berco_1) >  TEMPO_MAX_PRESENCA)
			{
				tempo_presenca_berco_1 = Timer();
				dados_berco[BERCO_1].status_debounc_presenca_produto = ON;
			}
			// verifica Presen�a do Produto no Ber�o 2
			if(STATUS.PresCluster_2 == OFF && (Timer()-tempo_presenca_berco_2) >  TEMPO_MAX_AUSENCIA)
				dados_berco[BERCO_2].status_debounc_presenca_produto = OFF;
			else if(STATUS.PresCluster_2 == ON && (Timer()-tempo_presenca_berco_2) >  TEMPO_MAX_PRESENCA) 
			{
				tempo_presenca_berco_2 = Timer();
				dados_berco[BERCO_2].status_debounc_presenca_produto = ON;
			}
			
			//////////////////////////////////////////////////////////////
			if(dados_berco[BERCO_1].status_debounc_presenca_produto == ON)
				tempo_presenca_off[BERCO_1] = 0;
			else
				tempo_presenca_off[BERCO_1] = Timer()-tempo_presenca_berco_1;
			////////////////////////
			if(dados_berco[BERCO_2].status_debounc_presenca_produto == ON)
				tempo_presenca_off[BERCO_2] = 0;
			else
				tempo_presenca_off[BERCO_2] = Timer()-tempo_presenca_berco_2;
			//////////////////////////////////////////////////////////////
			
			SetCtrlAttribute (painel_auto, dados_berco[BERCO_1].crtlID_presenca, ATTR_CTRL_VAL, dados_berco[BERCO_1].status_debounc_presenca_produto);
			SetCtrlAttribute (painel_auto, dados_berco[BERCO_2].crtlID_presenca, ATTR_CTRL_VAL, dados_berco[BERCO_2].status_debounc_presenca_produto);
		}
		
		ProcessSystemEvents ();//equalizar tempo da thread
		
	}
	return 0;
}



//
// Fun��o: Habilita_Scanner()
//
void Habilita_Scanner(int num_scanner)
{
	char
		send_data[100];

	strcpy(send_data,"LON");
	strcat(send_data,"\r");
	VM_ComWrt(dados_scanner[num_scanner].comm_scanner, send_data, strlen(send_data));//habilita leitura de codigo de barras
	dados_scanner[num_scanner].scanner_habilitado = ON;
	VM_FlushInQ(dados_scanner[num_scanner].comm_scanner);
}

//
// Fun��o: Desabilita_Scanner()
//
void Desabilita_Scanner(int num_scanner)
{
	char
		send_data[100];

	strcpy(send_data,"LOFF");
	strcat(send_data,"\r");
	VM_ComWrt(dados_scanner[num_scanner].comm_scanner, send_data, strlen(send_data));//desabilita leitura de codigo de barras
	dados_scanner[num_scanner].scanner_habilitado = OFF;
	VM_FlushInQ(dados_scanner[num_scanner].comm_scanner);
}

//
// Fun��o: IniciaPortasDeSaida()
// 
// Descri��o: Inicia as portas de sa�da das placas.
//
int IniciaPortasDeSaida(char *mens_erro)
{

	int
		status;

	
	// Inicializa a porta de sa�da 'CARTAO_2'
	Delay_thread(0.15);
	status = EnviaCommand_C_ToPIC (END_CARTAO_2_SAIDA);//Placa  0x42
	status = EnviaCommand_C_ToPIC (END_CARTAO_2_SAIDA);//Placa  0x42
	if(status==0)
	{
		status = EnviaCommand_A_ToPIC (END_CARTAO_2_SAIDA);
		portGP0[(END_CARTAO_2_SAIDA-0x40)] = 0x00;
		portGP1[(END_CARTAO_2_SAIDA-0x40)] = 0x00;
	}
	if(status != 0)
	{
		strcpy(mens_erro, "Cart�o de SAIDA('CARTAO_2') endere�o 0x42 n�o respondeu!\rErro na comunica��o I2C do Sistema" );
		return FALHA;
	}
	else
	{
		AtualizaCartaoSaida(END_CARTAO_2_SAIDA);
	}
	
	// Inicializa a porta de sa�da 'CARTAO_3'
	Delay_thread(0.15);
	status = EnviaCommand_C_ToPIC (END_CARTAO_3_SAIDA);//Placa  0x44
	status = EnviaCommand_C_ToPIC (END_CARTAO_3_SAIDA);//Placa  0x44
	if(status==0)
	{
		status = EnviaCommand_A_ToPIC (END_CARTAO_3_SAIDA);
		portGP0[(END_CARTAO_3_SAIDA-0x40)] = 0x00;
		portGP1[(END_CARTAO_3_SAIDA-0x40)] = 0x00;
	}
	if(status != 0)
	{
		strcpy(mens_erro, "Cart�o de SAIDA('CARTAO_3') endere�o 0x44 n�o respondeu!\rErro na comunica��o I2C do Sistema" );
		return FALHA;
	}
	else
	{
		AtualizaCartaoSaida(END_CARTAO_3_SAIDA);
	}
	
	// Inicializa a porta de sa�da 'CARTAO_4'
	Delay_thread(0.15);
	status = EnviaCommand_C_ToPIC (END_CARTAO_4_SAIDA);//Placa  0x46
	status = EnviaCommand_C_ToPIC (END_CARTAO_4_SAIDA);//Placa  0x46
	if(status==0)
	{
		status = EnviaCommand_A_ToPIC (END_CARTAO_4_SAIDA);
		portGP0[(END_CARTAO_4_SAIDA-0x40)] = 0x00;
		portGP1[(END_CARTAO_4_SAIDA-0x40)] = 0x00;
	}
	if(status != 0)
	{
		strcpy(mens_erro, "Cart�o de SAIDA('CARTAO_4') endere�o 0x46 n�o respondeu!\rErro na comunica��o I2C do Sistema" );
		return FALHA;
	}
	else
	{
		AtualizaCartaoSaida(END_CARTAO_4_SAIDA);
	}
	
	return 0;
}

//
// Fun��o: Le_Entradas()
// 
// Descri��o: Respons�vel pela leitura dos cart�es de entrada.
//
int	Le_Entradas(int endereco_cartao)
{
	int 
		porta_a = 0,
		porta_b = 0,
		status, 
		a;
	porta 
		matrix;

	status = LeWORDfromMCP23017 (endereco_cartao, &porta_a, &porta_b);
	if(status <0)
	{
		matrix.bit_a0 = 0;
		matrix.bit_a1 = 0;
		matrix.bit_a2 = 0;
		matrix.bit_a3 = 0;
		matrix.bit_a4 = 0;
		matrix.bit_a5 = 0;
		matrix.bit_a6 = 0;
		matrix.bit_a7 = 0;
		///
		matrix.bit_b0 = 0;
		matrix.bit_b1 = 0;
		matrix.bit_b2 = 0;
		matrix.bit_b3 = 0;
		matrix.bit_b4 = 0;
		matrix.bit_b5 = 0;
		matrix.bit_b6 = 0;
		matrix.bit_b7 = 0;

	}
	else
	{
		a = porta_a & 0x1  	;matrix.bit_a0 = !(a/0x1);
		a = porta_a & 0x2  	;matrix.bit_a1 = !(a/0x2);
		a = porta_a & 0x4  	;matrix.bit_a2 = !(a/0x4);
		a = porta_a & 0x8  	;matrix.bit_a3 = !(a/0x8);
		a = porta_a & 0x10 	;matrix.bit_a4 = !(a/0x10);
		a = porta_a & 0x20 	;matrix.bit_a5 = !(a/0x20); 
		a = porta_a & 0x40 	;matrix.bit_a6 = !(a/0x40); 
		a = porta_a & 0x80 	;matrix.bit_a7 = !(a/0x80);
		///
		a = porta_b & 0x1  ;matrix.bit_b0 = !(a/0x1);
		a = porta_b & 0x2  ;matrix.bit_b1 = !(a/0x2);
		a = porta_b & 0x4  ;matrix.bit_b2 = !(a/0x4);
		a = porta_b & 0x8  ;matrix.bit_b3 = !(a/0x8);
		a = porta_b & 0x10 ;matrix.bit_b4 = !(a/0x10);
		a = porta_b & 0x20 ;matrix.bit_b5 = !(a/0x20); 
		a = porta_b & 0x40 ;matrix.bit_b6 = !(a/0x40); 
		a = porta_b & 0x80 ;matrix.bit_b7 = !(a/0x80);
	}

	switch(endereco_cartao)
	{

		case END_CARTAO_1_ENTRADA:
			if (HW_present == OFF)
			{	
				 matrix.bit_a1 = OFF; //ClampAdv_1
				 matrix.bit_a2 = OFF; //ConectorAdv_1
				
				 ////////////////////////////////////////////////
				 if (my_prod_1 == ON)  //virual sensor product present
				 {
				 	  matrix.bit_a3 = ON; //PresCluster_1
				 }	 
				 else
				 {
				 	 matrix.bit_a3 = OFF;
				 }	
				 
				 matrix.bit_a6 = OFF; //ClampAdv_2
				 matrix.bit_a7 = OFF; //ConectorAdv_2
				 
				 if (my_prod_2 == ON)  //virual sensor product present
				 {
				 	  matrix.bit_b0 = ON; //PresCluster_2
				 }	 
				 else
				 {
				 	  matrix.bit_b0 = OFF;
				 }	
			}
		
			
			
			STATUS.ClampRec_1 = matrix.bit_a0;
			STATUS.ClampAdv_1 = matrix.bit_a1;
			STATUS.ConectorAdv_1 = matrix.bit_a2;
			STATUS.PresCluster_1 = matrix.bit_a3;
			STATUS.Combitac_Berco1 = matrix.bit_a4;
			STATUS.ClampRec_2 = matrix.bit_a5;
			STATUS.ClampAdv_2 = matrix.bit_a6;
			STATUS.ConectorAdv_2 = matrix.bit_a7;
			///
			STATUS.PresCluster_2 = matrix.bit_b0;
			STATUS.Combitac_Berco2 = matrix.bit_b1;
			STATUS.Spare_in_110 = matrix.bit_b2;
			STATUS.Spare_in_111 = matrix.bit_b3;
			
			
			////////////////////////////////////////////////////////////////
			//bimanual remoto
			if(acesso_remoto)
			{	
				STATUS.Bimanual = bimanual_remoto;
				db_bi = bimanual_remoto;
			}
			else
			{	
				STATUS.Bimanual = matrix.bit_b4;// 

				if ((matrix.bit_b5 == ON && matrix.bit_b6 == ON) || STATUS.Bimanual == ON)
				{
					 db_bi   = ON;
					 db_rej  = 0;
					 db_cont = 0;
					 goto jp_1;
				}
				else
					 db_bi = OFF;
			}
			
			//rejeita remoto
			if(acesso_remoto)
				STATUS.Rejeita = rej_remoto;
			else
			{
				STATUS.Rejeita						= matrix.bit_b5;// 
				/*
				if (matrix.bit_b5 == ON && STATUS.Bimanual == OFF && db_bi == OFF && matrix.bit_b6 == OFF)
					 db_rej=db_rej+1;
				
				if(db_rej > max_db_rej)
				{	
					STATUS.Rejeita	= ON;
					db_rej_1= db_rej_1 +1;	
					if (db_rej_1 > max_db_rej_1)
					{	
						db_rej   = 0;
						db_rej_1 = 0;
						STATUS.Rejeita	= OFF;
					}
				}
				else
				{
					STATUS.Rejeita	= OFF;
				}
				*/	
			}
			//continua remoto
			if(acesso_remoto)
				STATUS.Continua = cont_remoto;
			else
			{
				STATUS.Continua						= matrix.bit_b6;//
				/*
				if (matrix.bit_b6 == ON && STATUS.Bimanual == OFF && db_bi == OFF && matrix.bit_b5 == OFF)
					 db_cont=db_cont+1;
				
				if(db_cont > max_db_cont)
				{
					STATUS.Continua	= ON;
					
					db_cont_1=db_cont_1+1;
					if (db_cont_1 > max_db_cont_1)
					{	
							db_cont   = 0;
							db_cont_1 = 0;
							STATUS.Continua	= OFF;
					}	
				}
				else
				{
					STATUS.Continua	= OFF;
				}
				*/
			}
			
			if (sair_programa == OFF)
			{	
				SetCtrlVal (painel_auto,AUTO_LED_CONT, STATUS.Continua);
				SetCtrlVal (painel_auto,AUTO_LED_REJ, STATUS.Rejeita);  
			}	
jp_1:
			if (sair_programa == OFF)    
				SetCtrlVal (painel_auto,AUTO_LED_BI, db_bi);  
			/////////////////////////////////////////////////////////////////

			if (HW_present == OFF) 
				STATUS.Status_Emergencia = ON;
			else
				STATUS.Status_Emergencia = matrix.bit_b7;
			
			break;
			

		case END_CARTAO_5_ENTRADA:
			if (HW_present == OFF)
			{	
			   matrix.bit_a0 == OFF; //Trava_Porta_Avc
			}   
			
			STATUS.Trava_Porta_Avc = matrix.bit_a0;
			STATUS.Trava_Porta_Rec = matrix.bit_a1;
			STATUS.Porta_Fechada = matrix.bit_a2;
				 /* Endere�os Sensores */	
	        STATUS.StatusSensorSupEsq = matrix.bit_a3;		            
	        STATUS.StatusSensorSupDir = matrix.bit_a4;		            
	        STATUS.StatusSensorInfEsq = matrix.bit_a5;		            
	        STATUS.StatusSensorInfDir = matrix.bit_a6;		          
	        STATUS.StatusSensorSupMid = matrix.bit_a7;		
	        STATUS.StatusSensorInfMid = matrix.bit_b0;		
	            /*-+-+-+-+-+-+-+-+-+-+*/
			STATUS.Spare_in_509 = matrix.bit_b1;
			STATUS.Spare_in_510 = matrix.bit_b2;
			STATUS.Spare_in_511 = matrix.bit_b3;
			STATUS.Spare_in_512 = matrix.bit_b4;
			STATUS.Spare_in_513 = matrix.bit_b5;
			STATUS.Spare_in_514 = matrix.bit_b6;
			STATUS.Spare_in_515 = matrix.bit_b7;
			break;
		
		default:
			return -1;
	}

	return status;
}

//
// Fun��o: AtualizaCartaoSaida()
// 
// Descri��o: Envia informa��es para os cart�es de sa�da das placas.
//
int	AtualizaCartaoSaida(int endereco_cartao)
{
	int
		status = SEM_ERRO;
	char 
		buffer[40], 
		aux_send[20];
	porta 
		matrix = {0};
	static int
		saida1_cartao_2_anterior=999,
		saida2_cartao_2_anterior=999,
		saida1_cartao_3_anterior=999,
		saida2_cartao_3_anterior=999,
		saida1_cartao_4_anterior=999,
		saida2_cartao_4_anterior=999,
		saida1, 
		saida2;
	
	if(global_error.i2c_sistem_err == ON)
		return -1;

	switch (endereco_cartao)
	{
		
		case END_CARTAO_2_SAIDA:  //0x42
			matrix.bit_a0 = SAIDA.Reseta_emerg;
			matrix.bit_a1 = SAIDA.Habilita_emerg;
			matrix.bit_a2 = SAIDA.Spare_Out_203;
			matrix.bit_a3 = SAIDA.Spare_Out_204;
			matrix.bit_a4 = SAIDA.Spare_Out_205;
			matrix.bit_a5 = SAIDA.Spare_Out_206;
			matrix.bit_a6 = SAIDA.Spare_Out_207;
			matrix.bit_a7 = SAIDA.Spare_Out_208;				  
			///
			matrix.bit_b0 = SAIDA.SolClampCluster_1;
			matrix.bit_b1 = SAIDA.SolConectorCluster_1;
			matrix.bit_b2 = SAIDA.SolClampCluster_2;
			matrix.bit_b3 = SAIDA.SolConectorCluster_2;
			matrix.bit_b4 = SAIDA.TravaPorta;
			matrix.bit_b5 = SAIDA.Sol_Combitac;
			matrix.bit_b6 = SAIDA.ContatoraVibracao;
			matrix.bit_b7 = SAIDA.Spare_Out_215;
			break;
		
		case END_CARTAO_3_SAIDA:  //0x44
			matrix.bit_a0 = SAIDA.Battery_1;
			matrix.bit_a1 = SAIDA.Crank_Run_1;
			matrix.bit_a2 = SAIDA.Spare_Out_302;
			matrix.bit_a3 = SAIDA.Spare_Out_303;
			matrix.bit_a4 = SAIDA.DIC_SWINPUT_Dig_1;
			matrix.bit_a5 = SAIDA.ServiceEngineSoon_1;
			matrix.bit_a6 = SAIDA.Spare_Out_306;
			matrix.bit_a7 = SAIDA.Battery_2;				  
			///
			matrix.bit_b0 = SAIDA.Crank_Run_2;
			matrix.bit_b1 = SAIDA.Spare_Out_309;
			matrix.bit_b2 = SAIDA.Spare_Out_310;
			matrix.bit_b3 = SAIDA.DIC_SWINPUT_Dig_2;
			matrix.bit_b4 = SAIDA.ServiceEngineSoon_2;
			matrix.bit_b5 = SAIDA.Spare_Out_313;
			matrix.bit_b6 = SAIDA.VccDireto_Shunt_1;
			matrix.bit_b7 = SAIDA.VccDireto_Shunt_2;
			break;
		
		case END_CARTAO_4_SAIDA:  //0x46
			matrix.bit_a0 = SAIDA.HabilitaFonte_1;
			matrix.bit_a1 = SAIDA.HabilitaFonte_2;
			matrix.bit_a2 = SAIDA.PS_Inp_select1;
			matrix.bit_a3 = SAIDA.PS_Inp_select2;
			matrix.bit_a4 = SAIDA.FonteDut1_12_6V;
			matrix.bit_a5 = SAIDA.FonteDut1_13_5V;
			matrix.bit_a6 = SAIDA.FonteDut1_15V;
			matrix.bit_a7 = SAIDA.FonteDut2_12_6V;				  
			///
			matrix.bit_b0 = SAIDA.FonteDut2_13_5V;
			matrix.bit_b1 = SAIDA.FonteDut2_15V;
			matrix.bit_b2 = SAIDA.DIC_SW1_ADJ_604R;
			matrix.bit_b3 = SAIDA.DIC_SW1_ADJ_1624R;
			matrix.bit_b4 = SAIDA.DIC_SW1_ADJ_3534R;
			matrix.bit_b5 = SAIDA.DIC_SW2_ADJ_604R;
			matrix.bit_b6 = SAIDA.DIC_SW2_ADJ_1624R;
			matrix.bit_b7 = SAIDA.DIC_SW2_ADJ_3534R;
			break;

		default:
			break;						  
	}									  

	saida1 =  matrix.bit_a0 * 0x1			;
	saida1 =  saida1 + matrix.bit_a1 * 0x2	;
	saida1 =  saida1 + matrix.bit_a2 * 0x4	;
	saida1 =  saida1 + matrix.bit_a3 * 0x8	;
	saida1 =  saida1 + matrix.bit_a4 * 0x10	;
	saida1 =  saida1 + matrix.bit_a5 * 0x20	;
	saida1 =  saida1 + matrix.bit_a6 * 0x40	;
	saida1 =  saida1 + matrix.bit_a7 * 0x80	;
	
	saida2 =  matrix.bit_b0 * 0x1 			;
	saida2 =  saida2 + matrix.bit_b1 * 0x2	;
	saida2 =  saida2 + matrix.bit_b2 * 0x4	;
	saida2 =  saida2 + matrix.bit_b3 * 0x8	;
	saida2 =  saida2 + matrix.bit_b4 * 0x10	;
	saida2 =  saida2 + matrix.bit_b5 * 0x20	;
	saida2 =  saida2 + matrix.bit_b6 * 0x40	;
	saida2 =  saida2 + matrix.bit_b7 * 0x80	;
	
	switch (endereco_cartao)
	{

		case END_CARTAO_2_SAIDA:  //0x42
			if(saida1 != saida1_cartao_2_anterior || saida2 != saida2_cartao_2_anterior)
			{
				strcpy(buffer, "B");
				Fmt(aux_send, "%s<%s%i", "000",endereco_cartao);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida1);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida2);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);
				status = EscreveMCP23017byPIC ( buffer, &saida1_cartao_2_anterior, &saida2_cartao_2_anterior );
			}
			break;

		case END_CARTAO_3_SAIDA:  //0x44
			if(saida1 != saida1_cartao_3_anterior || saida2 != saida2_cartao_3_anterior)
			{
				strcpy(buffer, "B");
				Fmt(aux_send, "%s<%s%i", "000",endereco_cartao);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida1);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida2);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);
				status = EscreveMCP23017byPIC ( buffer, &saida1_cartao_3_anterior, &saida2_cartao_3_anterior );
			}
			break;

		case END_CARTAO_4_SAIDA:  //0x46
			if(saida1 != saida1_cartao_4_anterior || saida2 != saida2_cartao_4_anterior)
			{
				strcpy(buffer, "B");
				Fmt(aux_send, "%s<%s%i", "000",endereco_cartao);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida1);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);

				Fmt(aux_send, "%s<%s%i", "000",saida2);
				CopyString (aux_send, 0, aux_send,strlen(aux_send)-3 , 3);
				strcat(buffer, aux_send);
				status = EscreveMCP23017byPIC ( buffer, &saida1_cartao_4_anterior, &saida2_cartao_4_anterior );
			}
			break;

			default:
			break;						  
	}

	return status;
}

//
// Fun��o: Status_Seguranca()
//
void Status_Seguranca(void)
{
	static int
		cont_emergencia	= 0;

	status_bimanual = STATUS.Bimanual;
	
	/////// status da emerg�ncia ///////
	if( !STATUS.Status_Emergencia )
		cont_emergencia++;
	else
		cont_emergencia = 0;
	if(cont_emergencia >= DEBOUNCING_EMERGEN)
	{
		status_emergencia = OFF;
		cont_emergencia = DEBOUNCING_EMERGEN;
	}
	else
		status_emergencia = ON;

	/////// verifica home position ///////
	if(( STATUS.ClampAdv_1==OFF && STATUS.ClampRec_1==ON ) // Status [Clamp_Berco_1] == [RECUADO] //
		&& ( STATUS.ClampAdv_2==OFF && STATUS.ClampRec_2==ON ) // Status [Clamp_Berco_2] == [RECUADO] //
		&& ( STATUS.ConectorAdv_1==OFF ) // Status [Conector_Berco_1] == [RECUADO] //
		&& ( STATUS.ConectorAdv_2==OFF ) // Status [Conector_Berco_2] == [RECUADO] //
		&& ( STATUS.Combitac_Berco1==ON && STATUS.Combitac_Berco2==ON ) // Status [Combitac] == [AVANCADO] //
		&& ( STATUS.ConectorAdv_1==OFF )
		&& ( STATUS.ConectorAdv_2==OFF )
	
		)
		all_motions_home = ON;
	else
		all_motions_home = OFF;
	
	/////// motions clear ///////
	if( status_emergencia )
		motions_clear_to_move = ON;
	else
		motions_clear_to_move = OFF;
}

//
// Fun��o: ResetarEmergencia()
//
int ResetarEmergencia(int ver_consistencia)
{
	
	if(ver_consistencia)
	{
		if(modo_thread != ESCRITA_E_LEITURA)
			return FALHA;
		SAIDA.Reseta_emerg = OFF;
		SAIDA.Habilita_emerg = OFF;
   		Delay_thread(0.4);
		SAIDA.Habilita_emerg = ON;
   		Delay_thread(0.5);

	   if (HW_present  == OFF)
		   STATUS.Status_Emergencia == OFF;		
	   
		if(STATUS.Status_Emergencia != OFF)
			return FALHA;
	   
	   if (HW_present  == OFF)
		   STATUS.Status_Emergencia == OFF;		
	   
	   
	}
	if(SAIDA.Habilita_emerg != ON)
	{
		SAIDA.Habilita_emerg = ON;
   		Delay_thread(0.5);
	}
	SAIDA.Reseta_emerg = ON;
	Delay_thread(0.5);
	SAIDA.Reseta_emerg = OFF;
   	Delay_thread(0.6);
	return SEM_ERRO;
}

//
// Fun��o: LeBotoeira()
//
int LeBotoeira(int berco)
{
	double
		t = Timer();
	int
		botao_acionado = OFF,
		cont = BOT_OFF,
		rej = BOT_OFF;
		
	do
	{
		Delay_thread(0.01);
		rej = STATUS.Rejeita;
		cont = STATUS.Continua;
		if (cont == BOT_ON || rej == BOT_ON || dados_berco[berco].rejeita_montagem == ON )             // Oper. apertou algum botao
			botao_acionado = ON;
	}
	while(((Timer() - t) < 0.3) && (botao_acionado == OFF));// Espera apertar bot. ate 300ms

	if (botao_acionado	== OFF)
	{
		// Time out para botoeira
		ProcessDrawEvents();                                 // Desenha tela apos timeout
		return BOT_TIMEOUT;
	}

	//------------------------- Verifica qual botao, espera soltar ou sai se tempo > 1.9------
	cont = OFF;
	rej = OFF;
	t = Timer();
	while ((botao_acionado	== ON) && (Timer() - t < 2))  
	{
		Delay_thread(0.1);
		botao_acionado = OFF;
		if (STATUS.Rejeita == BOT_ON  || dados_berco[berco].rejeita_montagem == ON)   // Verifica botao de REJEITA
		{
			rej = REJ;
			botao_acionado = ON;
		}
		if (STATUS.Continua == BOT_ON)  // Verifica botao de CONT
		{
			cont = CONT;
			botao_acionado = ON;
		}
	}// Fim do laco while
	//-------------------- Retorna Botao Lido -------------------------------
	if(!dados_berco[berco].status_debounc_presenca_produto && dados_berco[berco].rejeitado)//Retirou o produto
		return FALHA_PRODUTO_AUSENTE;

	if (rej && cont)
		return CONT_REJ;
	else if (rej)
		return REJ;
	else if (cont)
		return CONT;
	else
		return BOT_OFF;
}

//
// Fun��o: VerificaNoButton()
//
int VerificaNoButton(void)
{
	if(STATUS.Continua == OFF && STATUS.Rejeita == OFF)
		return SEM_ERRO;
	MENS_WARNING = MENS_BOT_TRAVADO;
	do
	{
		Delay_thread(0.05);
	}
	while((STATUS.Continua != OFF || STATUS.Rejeita != OFF) && status_emergencia && !sair_programa);
	if(STATUS.Continua == OFF && STATUS.Rejeita == OFF)
		return SEM_ERRO;
	return FALHA;
}

//
// Fun��o: Delay_thread()
//
void Delay_thread(double segundos)
{
	double
		t = Timer();

	while(Timer() - t < segundos)
		ProcessSystemEvents ();
}

//
// Fun��o: EnviaCommand_A_ToPIC()
//
int EnviaCommand_A_ToPIC ( int Add )
{
int
	x,
	status;
char
	aux_send[50],
	receive[TAM_MAX_RESP_PIC]= {0};

	
	
	if (HW_present == OFF)	
		return SEM_ERRO;	

	
	///////////////////////////////////////////
	strcpy( aux_send, "A");
	strcat( aux_send, itostr( Add, 3 ));
	strcat( aux_send, "\r");
	x = strlen(aux_send);
	status = VM_ComWrt( comm_sistema, aux_send, x );
	if (status != x )
	{
		global_error.status = -1;
		strcpy(global_error.global_error_desc, "Falha ao enviar string ao PIC");	
		strcpy(global_error.funcao_error_name, "ComWrt() - chamada por EnviaCommand_A_ToPIC()");
		GlobalErrDetect();
		return global_error.status;
	}		
	global_error.status = EsperaRetornoPIC(receive);
	if(global_error.status != SEM_ERRO)
	{
		global_error.status = -2;
		Fmt(global_error.funcao_error_name, "%s%x ", "EsperaRetornoPIC() - chamado por EnviaCommand_A_ToPIC() - ADD=", Add);
		GlobalErrDetect();
		return global_error.status;
	}
	if(strcmp(receive,"A") != 0)
	{
		global_error.status = -3;
		strcpy(global_error.global_error_desc, "Resposta do PIC faltou carater 'A'");	
		Fmt(global_error.funcao_error_name, "%s%x ", "EnviaCommand_A_ToPIC() - ADD=", Add);
		GlobalErrDetect();
		return global_error.status;
	}

	return SEM_ERRO;
}

//
// Fun��o: EnviaCommand_C_ToPIC()
//
int EnviaCommand_C_ToPIC ( int Add )
{
	int
		x,
		status;
	char
		aux_send[50],
		receive[TAM_MAX_RESP_PIC]= {0};

		
	if (HW_present == OFF);
		return 	SEM_ERRO;
	
	/////////////////////////////////////////
	strcpy( aux_send, "C");
	strcat( aux_send, itostr( Add, 3 ) );
	strcat( aux_send, "\r");
	x = strlen(aux_send);
	status = VM_ComWrt( comm_sistema, aux_send, x );
	if (status != x )
	{
		global_error.status = -1;
		strcpy(global_error.global_error_desc, "Falha ao enviar string ao PIC");	
		strcpy(global_error.funcao_error_name, "ComWrt() - chamada por EnviaCommand_C_ToPIC()");
		GlobalErrDetect();
		return global_error.status;
	}		
	global_error.status = EsperaRetornoPIC(receive);
	if(global_error.status != SEM_ERRO)
	{
		global_error.status = -2;
		Fmt(global_error.funcao_error_name, "%s%x ", "EsperaRetornoPIC() - chamado por EnviaCommand_C_ToPIC() - ADD=", Add);
		GlobalErrDetect();
		return global_error.status;
	}
	if(strcmp(receive,"C") != 0)
	{
		global_error.status = -3;
		strcpy(global_error.global_error_desc, "Resposta do PIC faltou carater 'C'");	
		Fmt(global_error.funcao_error_name, "%s%x ", "EnviaCommand_C_ToPIC() - ADD=", Add);
		GlobalErrDetect();
		return global_error.status;
	}

	return SEM_ERRO;
}

//
// Fun��o: EscreveMCP23017byPIC()
//
int EscreveMCP23017byPIC ( char *send_data, int *GP0, int *GP1 )
{
	int
		x,
		y,
		k=0,
		k_ant,
		status;
	char
		receive[TAM_MAX_RESP_PIC],
		aux_resp[20],
		strGP0[10],
		strGP1[10];
		
	if (HW_present == OFF)  	
		return SEM_ERRO;
	

	///////////////////////////////////////
	strcat(send_data, "\r");
	x = strlen(send_data);
	status = VM_ComWrt( comm_sistema, send_data, x );
	if (status != x )
	{
		global_error.status = -1;
		strcpy(global_error.global_error_desc, "Falha ao enviar string ao PIC");	
		strcpy(global_error.funcao_error_name, "ComWrt() - chamada por LeWORDfromMCP23017()");
		GlobalErrDetect();
		return global_error.status;
	}		
	global_error.status = EsperaRetornoPIC(receive);
	if(global_error.status != SEM_ERRO)
	{
		global_error.status = -2;
		strcpy(global_error.funcao_error_name, "EsperaRetornoPIC() - chamado por EscreveMCP23017byPIC()");
		GlobalErrDetect();
		return global_error.status;
	}
	k = FindPattern (receive, 0, -1, ";", 0, 0);
	if(k < 0)
	{
		global_error.status = -3;
		strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
		strcpy(global_error.funcao_error_name, "FindPattern() - chamado por EscreveMCP23017byPIC()");
		GlobalErrDetect();
		return global_error.status;
	}
	if(k >= sizeof(aux_resp))
	{
		global_error.status = -4;
		strcpy(global_error.global_error_desc, "Index 'k' > tamanho da Target String ");	
		strcpy(global_error.funcao_error_name, "FindPattern() - chamado por EscreveMCP23017byPIC(1) - 1");
		GlobalErrDetect();
		return global_error.status;
	}
	CopyString (aux_resp, 0 , receive, 0, k);
	if(strcmp(aux_resp,"B") != 0 || strlen(receive)< 6)
	{
		global_error.status = -5;
		strcpy(global_error.global_error_desc, "Resposta do PIC curta ou faltou carater 'B'");	
		strcpy(global_error.funcao_error_name, "EscreveMCP23017byPIC()");
		GlobalErrDetect();
		return global_error.status;
	}
	k_ant=k+1;
	k = FindPattern (receive, k+1, -1, ";", 0, 0);
	if(k < 0)
	{
		global_error.status = -6;
		strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
		strcpy(global_error.funcao_error_name, "FindPattern() - chamado por EscreveMCP23017byPIC() - 2");
		GlobalErrDetect();
		return global_error.status;
	}
	CopyString (strGP0, 0 , receive, k_ant, k-k_ant);
	k_ant=k+1;
	k = FindPattern (receive, k+1, -1, ";", 0, 0);
	if(k < 0)
	{
		global_error.status = -7;
		strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
		strcpy(global_error.funcao_error_name, "FindPattern() - chamado por EscreveMCP23017byPIC() - 3");
		GlobalErrDetect();
		return global_error.status;
	}
	CopyString (strGP1, 0 , receive, k_ant, k-k_ant);
	Scan ( strGP0, "%s>%i", &x);
	if( x<0 ) 
		x += 256;
	*GP0 = x;
	Scan ( strGP1, "%s>%i", &y);
	if( y<0 ) 
		y += 256;
	*GP1 = y;
	
	return SEM_ERRO;
}

//
// Fun��o: EsperaBimanual()
//
int EsperaBimanual(int berco)
{
	if(status_bimanual)
		return SEM_ERRO;
	dados_berco[berco].cor_mensagens = MENS_VERMELHO;
	strcpy(dados_berco[berco].mens_montagem_2, "MANTENHA BIMANUAL PRESSIONADO");
	strcpy(dados_berco[berco].mens_montagem_3, " ");
	do
	{
		Delay_thread(0.05);
	}
	while(!status_bimanual && status_emergencia && !sair_programa);
	if(status_bimanual)
		return SEM_ERRO;
	return FALHA;
}

//
// Fun��o: EsperaRetornoPIC()
//
int EsperaRetornoPIC( char *bRetorno )
{
	int
		decimal;
	double
		t,
		time_out = 0.100;

	if (HW_present == OFF)  	
		return SEM_ERRO;

	///////////////////////////////////////
	SetComTime (comm_sistema, time_out); //set timeout da COM
	decimal = 0;
	t = Timer();
	while( decimal == 0 &&  (Timer() - t < time_out) )
		decimal = GetInQLen ( comm_sistema);

	if ( decimal == 0 )
	{
		strcpy(global_error.global_error_desc, "Timeout - PIC n�o respondeu-1");	
		return -1;
	}
	decimal = ComRdTerm (comm_sistema, bRetorno, TAM_MAX_RESP_PIC, '\r' );
	if(decimal < (TAM_MAX_RESP_PIC-1))
	{
		bRetorno[decimal] = 0;
	}
	if(decimal < 0)
	{
		strcpy(global_error.global_error_desc, "Timeout - PIC n�o respondeu-2");	
		return -2;
	}
	if(strlen(bRetorno) >= (TAM_MAX_RESP_PIC-1))
	{
		strcpy(global_error.global_error_desc, "Resposta PIC excedeu tamanho do buffer");	
		return -3;
	}
	return SEM_ERRO;
}

//
// Fun��o: LeWORDfromMCP23017()
//
int LeWORDfromMCP23017 ( int Add, int *PortA, int *PortB )
{
	int
		status,
		x,
		y,
		k=0,
		k_ant;
	char
		aux_send[50],
		receive[TAM_MAX_RESP_PIC],
		aux_resp[10],
		strGP0[10],
		strGP1[10];

		
	if (HW_present == OFF)  	
		return SEM_ERRO;
	
		
	///////////////////////////////////
	VM_FlushInQ (comm_sistema);
	strcpy( aux_send, "D" );
	strcat( aux_send, itostr( Add, 3 ) );
	strcat( aux_send, "\r");
	x = strlen(aux_send);
	status = VM_ComWrt( comm_sistema, aux_send, x );
	if (status == x )
	{
		global_error.status = EsperaRetornoPIC( receive );
		if(global_error.status != SEM_ERRO)
		{
			global_error.status = -1;
			strcpy(global_error.funcao_error_name, "EsperaRetornoPIC() - chamado por LeWORDfromMCP23017()");
			GlobalErrDetect();
			return global_error.status;
		}

		k = FindPattern (receive, 0, -1, ";", 0, 0);
		if(k < 0)
		{
			global_error.status = -2;
			strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
			strcpy(global_error.funcao_error_name, "FindPattern() - chamado por LeWORDfromMCP23017()");
			GlobalErrDetect();
			return global_error.status;
		}
		if(k >= sizeof(aux_resp))
		{
			global_error.status = -3;
			strcpy(global_error.global_error_desc, "Index 'k' > tamanho da Target String ");	
			strcpy(global_error.funcao_error_name, "FindPattern() - chamado por LeWORDfromMCP23017(1) - 1");
			GlobalErrDetect();
			return global_error.status;
		}
		CopyString (aux_resp, 0 , receive, 0, k);
		if(strcmp(aux_resp,"R") != 0 || strlen(receive)< 6)
		{
			global_error.status = -4;
			strcpy(global_error.global_error_desc, "Resposta do PIC curta ou faltou carater 'R'");	
			strcpy(global_error.funcao_error_name, "LeWORDfromMCP23017()");
			GlobalErrDetect();
			return global_error.status;
		}
		
		k_ant=k+1;
		k = FindPattern (receive, k+1, -1, ";", 0, 0);
		if(k < 0)
		{
			global_error.status = -5;
			strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
			strcpy(global_error.funcao_error_name, "FindPattern() - chamado por LeWORDfromMCP23017() - 2");
			GlobalErrDetect();
			return global_error.status;
		}
		CopyString (strGP0, 0 , receive, k_ant, k-k_ant);
		k_ant=k+1;
		k = FindPattern (receive, k+1, -1, ";", 0, 0);
		if(k < 0)
		{
			global_error.status = -6;
			strcpy(global_error.global_error_desc, "N�o encontrou Pattern ';' ");	
			strcpy(global_error.funcao_error_name, "FindPattern() - chamado por LeWORDfromMCP23017() - 3");
			GlobalErrDetect();
			return global_error.status;
		}
		CopyString (strGP1, 0 , receive, k_ant, k-k_ant);
		Scan ( strGP0, "%s>%i", &x);
		if( x<0 ) 
			x += 256;
		Scan ( strGP1, "%s>%i", &y);
		if( y<0 ) 
			y += 256;
		*PortA = x;
		*PortB = y;
		return SEM_ERRO;
	
	}
	global_error.status = -7;
	strcpy(global_error.global_error_desc, "Falha ao enviar string ao PIC");	
	strcpy(global_error.funcao_error_name, "ComWrt() - chamada por LeWORDfromMCP23017()");
	GlobalErrDetect();
	return global_error.status;
}


//
// Fun��o: Trava()
//
// Descri��o: Utilizada para travar a porta.
//
int Trava (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o trava j� esta avan�ada 
		if ( STATUS.Trava_Porta_Avc==OFF )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para travar a porta!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar trava
			//
			SAIDA.TravaPorta = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.Trava_Porta_Avc==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut na trava da porta!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Conector_Berco_1 j� esta recuado .
		if ( STATUS.Trava_Porta_Avc==ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover a trava da porta!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Conector_Berco_1
			//
			SAIDA.TravaPorta = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.Trava_Porta_Avc==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut na trava da porta!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}



///////////////////////////////////////////////////////////////////////////////

//
// Fun��o: MoveClampBerco1()
//
// Descri��o: Utilizada para executar o movimento do Clamp_Berco_1.
//
int MoveClampBerco1 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	if (HW_present == OFF)  	
		return SEM_ERRO;
	
		
	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Clamp_Berco_1 j� esta avan�ado 
		if ( STATUS.ClampAdv_1==OFF || STATUS.ClampRec_1==ON )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clamp_Berco_1!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar o Clamp_Berco_1
			//
			SAIDA.SolClampCluster_1 = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.ClampAdv_1==OFF || STATUS.ClampRec_1==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Clamp_Berco_1!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Clamp_Berco_1 j� esta recuado .
		if ( STATUS.ClampAdv_1==ON || STATUS.ClampRec_1==OFF )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clamp_Berco_1!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Clamp_Berco_1
			//
			SAIDA.SolClampCluster_1 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ClampAdv_1==ON || STATUS.ClampRec_1==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Clamp_Berco_1!");
				return FALHA_TIMEOUT;
			}
		 
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//
// Fun��o: MoveClampBerco2()
//
// Descri��o: Utilizada para executar o movimento do Clamp_Berco_2.
//
int MoveClampBerco2 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;
		
	if (HW_present == OFF)  	
		return SEM_ERRO;
	

	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Clamp_Berco_2 j� esta avan�ado 
		if ( STATUS.ClampAdv_2==OFF || STATUS.ClampRec_2==ON )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clamp_Berco_2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar o Clamp_Berco_2
			//
			SAIDA.SolClampCluster_2 = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.ClampAdv_2==OFF || STATUS.ClampRec_2==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Clamp_Berco_2!"); 
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Clamp_Berco_2 j� esta recuado .
		if ( STATUS.ClampAdv_2==ON || STATUS.ClampRec_2==OFF )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clamp_Berco_2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Clamp_Berco_2
			//
			SAIDA.SolClampCluster_2 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ClampAdv_2==ON || STATUS.ClampRec_2==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Clamp_Berco_2!");
				return FALHA_TIMEOUT;
			}
		
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//
// Fun��o: MoveConectorBerco1()
//
// Descri��o: Utilizada para executar o movimento do Conector_Berco_1.
//
int MoveConectorBerco1 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	if (HW_present == OFF)  	
		return SEM_ERRO;
	
		
	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Conector_Berco_1 j� esta avan�ado 
		if ( STATUS.ConectorAdv_1==OFF )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector_Berco_1!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar o Conector_Berco_1
			//
			SAIDA.SolConectorCluster_1 = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.ConectorAdv_1==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector_Berco_1!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Conector_Berco_1 j� esta recuado .
		if ( STATUS.ConectorAdv_1==ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector_Berco_1!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Conector_Berco_1
			//
			SAIDA.SolConectorCluster_1 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ConectorAdv_1==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector_Berco_1!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//
// Fun��o: MoveConectorBerco2()
//
// Descri��o: Utilizada para executar o movimento do Conector_Berco_2.
//
int MoveConectorBerco2 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	if (HW_present == OFF)  	
		return SEM_ERRO;
	
	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Conector_Berco_2 j� esta avan�ado 
		if ( STATUS.ConectorAdv_2==OFF )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector_Berco_2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar o Conector_Berco_2
			//
			SAIDA.SolConectorCluster_2 = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.ConectorAdv_2==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector_Berco_2!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Conector_Berco_2 j� esta recuado .
		if ( STATUS.ConectorAdv_2==ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector_Berco_2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Conector_Berco_2
			//
			SAIDA.SolConectorCluster_2 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ConectorAdv_2==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector_Berco_2!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//
// Fun��o: MoveCombitac()
//
// Descri��o: Utilizada para executar o movimento do Combitac.
//
int MoveCombitac (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;
		
	if (HW_present == OFF)  	
		return SEM_ERRO;
	

	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Combitac j� esta avan�ado 
		if ( STATUS.Combitac_Berco1==OFF || STATUS.Combitac_Berco2==OFF )
		{

			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Combitac!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();

			//
			// Comando para avan�ar o Combitac
			//
			SAIDA.Sol_Combitac = OFF;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}
			while( ( STATUS.Combitac_Berco1==OFF || STATUS.Combitac_Berco2==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Combitac!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Combitac j� esta recuado .
		if ( STATUS.Combitac_Berco1==ON || STATUS.Combitac_Berco2==ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Combitac!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Combitac
			//
			SAIDA.Sol_Combitac = ON;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.Combitac_Berco1==ON || STATUS.Combitac_Berco2==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Combitac!");
				return FALHA_TIMEOUT;
			}
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//-------------------------TravaLigaCluster1--------------------------------------/

int TravaLigaCluster1 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Clamp 1 j� esta avan�ado 
		if (( STATUS.ClampRec_1==OFF && STATUS.ConectorAdv_1==OFF ) || !sair_programa )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clamp 1!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			
			t = Timer();

			//
			// Comando para avan�ar o Clamp cluster 1
			//
			SAIDA.SolClampCluster_1 = ON;

			// Aguarda conclus�o do avan�o do clamp 1
			do
			{
				Delay_thread(0.100);
			}

			while( ( STATUS.ClampAdv_1==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector 1!");
				return FALHA_TIMEOUT;
			}
			
			// Comando para avan�ar o conector 1
			SAIDA.SolConectorCluster_1 = ON;
			
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Clamp 1 j� esta recuado .
		if ( STATUS.ClampAdv_1==ON && STATUS.ConectorAdv_1==ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Conector 1
			//
			SAIDA.SolConectorCluster_1 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ConectorAdv_1 == ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector!");
				return FALHA_TIMEOUT;
			}
	
			// Comando para recuar o Clamp 1
			SAIDA.SolClampCluster_1 = OFF;
			
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}

//-------------------------TravaLigaCluster2--------------------------------------/
int TravaLigaCluster2 (int acao)
{
	// == Inicializa variaveis ==
	double
		t=Timer(),
		timeOut = 5.0;

	ProcessSystemEvents();

	if (acao == ON)
	{
		// Verifica se o Clamp 2 j� esta avan�ado 
		if (( STATUS.ClampRec_2 == OFF && STATUS.ConectorAdv_2 == OFF) || !sair_programa )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Clmap 2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			
			t = Timer();

			//
			// Comando para avan�ar o Clamp 2
			//
			SAIDA.SolClampCluster_2 = ON;

			// Aguarda conclus�o do avan�o
			do
			{
				Delay_thread(0.100);
			}

			while( ( STATUS.ClampAdv_2==OFF ) && Timer()-t <= timeOut && status_emergencia && !sair_programa );

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Conector 2!");
				return FALHA_TIMEOUT;
			}
			
			SAIDA.SolConectorCluster_2 = ON;
			
			ProcessSystemEvents();
		}
	}
	else if (acao == OFF)
	{
		// Verifica se o Clamp j� esta recuado .
		if ( STATUS.ClampAdv_2 == ON && STATUS.ConectorAdv_2 == ON )
		{
			// Verifica��o de seguran�a
			if(modo_manual && motions_clear_to_move == OFF)
			{
				MessagePopup ("Condi��o incorreta", "Condi��o inv�lida para mover o Conector 2!");
				return FALHA;
			}
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			t = Timer();
			//
			// Comando para recuar o Conector 2
			//
			SAIDA.SolConectorCluster_2 = OFF;

			// Aguarda conclus�o do recuo
			do
			{
				Delay_thread(0.100);
			}
			while (	( STATUS.ConectorAdv_2==ON ) && Timer()-t <= timeOut && status_emergencia && !sair_programa);

			// Tratamento de falhas
			if(!status_emergencia  || sair_programa)
				return EMERG_ACIONADA;

			if( Timer()-t > timeOut )
			{
				if(modo_manual)
					MessagePopup("Condi��o incorreta", "TimeOut no Clamp 2!");
				return FALHA_TIMEOUT;
			}

			// Comando para recuar o Clamp 2
			SAIDA.SolClampCluster_2 = OFF;
			
			ProcessSystemEvents();
		}
	}
	// tratamento de falha por Timeout
	if(Timer() - t >timeOut)
		return FALHA_TIMEOUT;
	else
		return SEM_ERRO;
}
//------------------------Ligar Produto 1 ----------------------------------------//
void LigarProduto1(void)
{
	
	Set_Vdut(VOLTS_13_5, 1);
	SAIDA.VccDireto_Shunt_1  = ON;
	SAIDA.HabilitaFonte_1	 = ON;

	SAIDA.Battery_1 	= ON; //liga BATERIA
	SAIDA.Crank_Run_1 	= ON;
	Delay_thread(0.01);
}
//---------------------------  DesligarProduto1 -----------------------------------------//
void DesligarProduto1(void)
{
	SAIDA.Battery_1	   		 = OFF;
	SAIDA.Crank_Run_1 		 = OFF;
	Delay_thread(0.01);
	
	Set_Vdut(VOLTS_0, 1);
	
	SAIDA.VccDireto_Shunt_1  = OFF; 
	SAIDA.HabilitaFonte_1 	 = OFF;
	Delay_thread(0.01);   

}



//------------------------Ligar Produto 2 ----------------------------------------//
void LigarProduto2(void)
{
	
	Set_Vdut(VOLTS_13_5, 2);
	
	SAIDA.VccDireto_Shunt_2  = ON;
	SAIDA.HabilitaFonte_2	 = ON;

	SAIDA.Battery_2 		 = ON; //liga BATERIA
	SAIDA.Crank_Run_2 		 = ON;
	Delay_thread(.1);
}
//---------------------------  DesligarProduto2 -----------------------------------------//
void DesligarProduto2(void)
{
	SAIDA.Battery_2	   		 = OFF;
	SAIDA.Crank_Run_2 		 = OFF;
	Delay_thread(0.01);
	
	Set_Vdut(VOLTS_0, 2);

	SAIDA.VccDireto_Shunt_2  = OFF; 
	SAIDA.HabilitaFonte_2 	 = OFF;
	Delay_thread(0.01);   
}

int Set_Vdut(int tensao, int berco)
{
double 
	valor;
 
	
	if (berco == 1)
	{
	 	switch (tensao)
		{
			case VOLTS_0:
				SAIDA.FonteDut1_12_6V	 = ON;
				SAIDA.FonteDut1_13_5V	 = ON;          
				SAIDA.FonteDut1_15V		 = ON; 
				break;
			case VOLTS_12_6:
				SAIDA.FonteDut1_12_6V	 = ON;
				SAIDA.FonteDut1_13_5V	 = OFF;          
				SAIDA.FonteDut1_15V		 = OFF; 
		   		break;
			case VOLTS_13_5:
				SAIDA.FonteDut1_12_6V	 = OFF;
				SAIDA.FonteDut1_13_5V	 = ON;          
				SAIDA.FonteDut1_15V		 = OFF; 
		   		break;
			case VOLTS_15:
				SAIDA.FonteDut1_12_6V	 = OFF;
				SAIDA.FonteDut1_13_5V	 = OFF;          
				SAIDA.FonteDut1_15V		 = ON; 
		   	break;
			
		}
	}

	if (berco == 2)
	{
	 	switch (tensao)
		{
			case VOLTS_0:
				SAIDA.FonteDut2_12_6V	 = ON;
				SAIDA.FonteDut2_13_5V	 = ON;          
				SAIDA.FonteDut2_15V		 = ON; 
				break;
			case VOLTS_12_6:
				SAIDA.FonteDut2_12_6V	 = ON;
				SAIDA.FonteDut2_13_5V	 = OFF;          
				SAIDA.FonteDut2_15V		 = OFF; 
		   		break;
			case VOLTS_13_5:
				SAIDA.FonteDut2_12_6V	 = OFF;
				SAIDA.FonteDut2_13_5V	 = ON;          
				SAIDA.FonteDut2_15V		 = OFF; 
		   		break;
			case VOLTS_15:
				SAIDA.FonteDut2_12_6V	 = OFF;
				SAIDA.FonteDut2_13_5V	 = OFF;          
				SAIDA.FonteDut2_15V		 = ON; 
		   	break;
			
		}
	}
	
	Delay_thread(0.01);
	
return 0;	
	
	
}



int DIC_SW_adj(int valor, int berco)
{
 
	
	if (berco == 1)
	{
	 	switch (valor)
		{
			case R_604:
				SAIDA.DIC_SW1_ADJ_3534R	 = OFF;
				SAIDA.DIC_SW1_ADJ_604R	 = ON;          
				SAIDA.DIC_SW1_ADJ_1624R	 = OFF; 
		   	break;
			case R_1624:
				SAIDA.DIC_SW1_ADJ_3534R	 = OFF;
				SAIDA.DIC_SW1_ADJ_604R	 = OFF;          
				SAIDA.DIC_SW1_ADJ_1624R	 = ON; 
		   	break;
			case R_3534:
				SAIDA.DIC_SW1_ADJ_3534R	 = ON;
				SAIDA.DIC_SW1_ADJ_604R	 = OFF;          
				SAIDA.DIC_SW1_ADJ_1624R	 = OFF; 
			break;
		}
	}

	if (berco == 2)
	{
	 	switch (valor)
		{
			case R_604:
				SAIDA.DIC_SW2_ADJ_3534R	 = OFF;
				SAIDA.DIC_SW2_ADJ_604R	 = ON;          
				SAIDA.DIC_SW2_ADJ_1624R	 = OFF; 
		   	break;
			case R_1624:
				SAIDA.DIC_SW2_ADJ_3534R	 = OFF;
				SAIDA.DIC_SW2_ADJ_604R	 = OFF;          
				SAIDA.DIC_SW2_ADJ_1624R	 = ON; 
		   	break;
			case R_3534:
				SAIDA.DIC_SW2_ADJ_3534R	 = ON;
				SAIDA.DIC_SW2_ADJ_604R	 = OFF;          
				SAIDA.DIC_SW2_ADJ_1624R	 = OFF; 
			break;
	
		}
	}
	
	Delay_thread(0.1);
	
return 0;	
	
	
}



//
// Fun��o: InicializaPainelAuto()
//
void InicializaPainelAuto(void)
{
	int
		i,
		ctrlArray;
	
	for (i=1;i<=NUMERO_DE_BERCOS;i++) 
	{
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYMENSAGEM);
		dados_berco[i].crtlID_mensagem = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYPICINSTRUCAO);
		dados_berco[i].crtlID_pic_instrucao = GetCtrlArrayItem(ctrlArray, i-1);
	
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYTESTE );		 	
		dados_berco[i].crtlID_teste = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYNOME);
		dados_berco[i].crtlID_nome = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYSTATUS);
		dados_berco[i].crtlID_status = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYLIMINF);
		dados_berco[i].crtlID_lim_inf = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYRESULTADO);
		dados_berco[i].crtlID_resultado = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYLIMSUP);
		dados_berco[i].crtlID_lim_sup = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYUNIDADE);
		dados_berco[i].crtlID_unidade = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYTEMPO);
		dados_berco[i].crtlID_tempo = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYMENSFALHA);
		dados_berco[i].crtlID_mens_falha = GetCtrlArrayItem(ctrlArray, i-1);
		
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, ARRAYPRESENCA);
		dados_berco[i].crtlID_presenca = GetCtrlArrayItem(ctrlArray, i-1);
		
		
		/////////////////////////////////////////////////////////////////////
		ctrlArray = GetCtrlArrayFromResourceID (painel_auto, A_SERIAL_ENDITEM);
        dados_berco[i].crtlID_serial_enditem = GetCtrlArrayItem(ctrlArray, i-1);
		
	    //ctrlArray = GetCtrlArrayFromResourceID (painel_auto, A_PN_VISTEON);
        //dados_berco[i].crtlID_PN_Visteon = GetCtrlArrayItem(ctrlArray, i-1);
		
		//ctrlArray = GetCtrlArrayFromResourceID (painel_auto, A_AMOSTRA);
        //dados_berco[i].crtlID_amostra = GetCtrlArrayItem(ctrlArray, i-1);
		
		//ctrlArray = GetCtrlArrayFromResourceID (painel_auto, A_DESCRICAO_MODELO);
        //dados_berco[i].crtlID_descricao_modelo = GetCtrlArrayItem(ctrlArray, i-1);
		
		//ctrlArray = GetCtrlArrayFromResourceID (painel_auto, A_TABELA);
        //dados_berco[i].crtlID_tabela = GetCtrlArrayItem(ctrlArray, i-1);
		/////////////////////////////////////////////////////////////////////
	
	}

}

void Wait_buttons(int *rej,int *cont)
{
int cont_cont=0,
	cont_rej=0;


		*rej=*cont=OFF; 
		if(acesso_remoto )
		{
			  
			cont_remoto=OFF;
			rej_remoto =OFF;
			do
			{
			  Delay_thread(0.1); 
			}while(!rej_remoto && !cont_remoto && status_emergencia && !sair_programa);	
			
			if (cont_remoto)
			   *cont = ON;
			
			if (rej_remoto)
			   *rej = ON;
		
		}
		else
		{
	
			
			do
			{
				Delay_thread(0.1);  
				if(STATUS.Rejeita)
					cont_rej++;
				else
					cont_rej=0;
			
				if(STATUS.Continua)
					cont_cont++;
				else
					cont_cont=0;
				if(cont_cont > QUANT_DEBOUNCING)
					*cont = ON;
				if(cont_rej > QUANT_DEBOUNCING)
					*rej = ON;
				
			}while(!*rej && !*cont && status_emergencia && !sair_programa);
		}
}
/*		
int DIC_SW_adj(int valor, int berco)
{
 
	
	if (berco == 1)
	{
		switch (value)
		{
			case R_605:
				SAIDA.DIC_SW2_ADJ_3534R	 = ON;
				SAIDA.DIC_SW2_ADJ_604R	 = ON;          
				SAIDA.DIC_SW2_ADJ_1624R	 = OFF; 
		   	break;
			case R_1625:
				SAIDA.DIC_SW2_ADJ_3534R	 = OFF;
				SAIDA.DIC_SW2_ADJ_604R	 = OFF;          
				SAIDA.DIC_SW2_ADJ_1624R	 = ON; 
		   	break;
			case R_3535:
				SAIDA.DIC_SW2_ADJ_3534R	 = ON;
				SAIDA.DIC_SW2_ADJ_604R	 = ON;          
				SAIDA.DIC_SW2_ADJ_1624R	 = OFF; 
			break;
		}
	}
}
*/
