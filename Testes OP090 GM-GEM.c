#include <windows.h> 
#include "CIMSockets.h"
#include <cviauto.h>
#include <analysis.h>
#include <formatio.h>
#include <ansi_c.h>
#include <utility.h>
#include <NIDAQmx.h> 

//BD13
#include "bd-support.h"


#include "niModInstCustCtrl.h"

#include "Main OP090 GM-GEM.h"
#include "Auto OP090 GM-GEM.h"
#include "CAN GM-GEM.h"
#include "Manual OP090 GM-GEM.h"
#include "Master_e_Negative_Samples.h"

#include "DAQ_MX.h"   
#include "Padrao.h" 
#include "CyberXML.h"

#include "b64.h"

/******************************** ExecutaTestes() *****************************************************************/
// Função: ExecutaTestes()
double ExecutaTestes(int pos_teste, char*tab_spare, char*pn_cliente, int modelo, int berco)    
{ 
	double 
		res=RES_FALHA;
		
	int tent = 0;
	
	
	if (berco == 1)
	{	
	 	SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, "");  
	}
	
	if (berco == 2)
	{	
	 	SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA_2, ATTR_CTRL_VAL, "");  
	}
	

	switch (pos_teste)
	{
			/* Chamado da função de verificação dos parafusos na tabela */
	case 550:
		 res = VerificaParafusos(dados_berco[berco].MensagemFalha1);
		break;
			/* -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
	case 1:
		res = Corrente_Bateria( dados_berco[berco].MensagemFalha1, berco );  //ck
		break;
	case 2:
		res = Corrente_Leds_Ambar( dados_berco[berco].MensagemFalha1, berco );  
		break;
	case 3:
		res = Verificacao_Leds_Ambar_1( dados_berco[berco].MensagemFalha1, berco );   //sinc
		break;
	case 4:
		res = ConfiguraCyberSecurity(dados_berco[berco].MensagemFalha1, berco);
		break;
	case 6:
		res = Corrente_Leds_Azul( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 7:
		res = Verificacao_Leds_Azul( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 8:
		res = Corrente_Leds_Vermelhos( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 9:
		res = Verificacao_Leds_Vermelhos_1( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 11:
		res = Corrente_Leds_Verdes( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 12:
		res = Verificacao_Leds_Verdes_1( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 14:
		res = Corrente_Leds_Brancos( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 15:
		res = Verificacao_Leds_Brancos( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 17:
		res = Verificacao_Leds_All_ON( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 18:
		res = Verificacao_Leds_All_OFF( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 19:
		res = Verificacao_Padrao_Display_SEG_1( dados_berco[berco].MensagemFalha1, berco );  
		break;
	case 20:																				
		res = Verificacao_Padrao_Display_SEG_2( dados_berco[berco].MensagemFalha1, berco );    
		break;
	case 21:
		res = Verificacao_Padrao_Display_MONO_1( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 22:
		res = Verificacao_Padrao_Display_MONO_2( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 23:
		res = Verificacao_Padrao_Display_MONO_3( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 24:
		res = Verificacao_Padrao_Display_MONO_4( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 25:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_ALL_OFF, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 26:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_ALL_ON, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 27:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_3, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 28:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_4, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 29:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_RED, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 30:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_GREEN, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 31:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_BLUE, dados_berco[berco].MensagemFalha1, berco );
		break;
   	case 32:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_GRAY_LEVEL, dados_berco[berco].MensagemFalha1, berco );
		break;
	case 33:
		res = Verificacao_Padrao_Display_COLOR(PATTERN_LCD_COLOUR_BARS, dados_berco[berco].MensagemFalha1, berco ); 
		break;
	//Gages
	case 40:
		res = Gages_0_Kmh_0_RPM( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 41:
		res = Gages_80_Kmh_3000_RPM( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 42:
		res = Gages_200_Kmh_8000_RPM( dados_berco[berco].MensagemFalha1, berco );   //sinc  
		break;

	case 45:
		res = VerificaNumSerie_NVM( dados_berco[berco].MensagemFalha1, berco );
		break;
	
	case 46:
		res = VerificaClientePN( dados_berco[berco].MensagemFalha1, berco );
		break;
		
	
		
	//sistema	
	case 97:
		res = Fechar_Porta(dados_berco[berco].MensagemFalha1, berco );
		break;
	
	case 98:
		res = Abrir_Porta( dados_berco[berco].MensagemFalha1, berco );
		break;	
	case 100:
		res = Ligar_Vibracao( dados_berco[berco].MensagemFalha1, berco );   
		break;
	case 101:
		res = Deligar_Vibracao( dados_berco[berco].MensagemFalha1, berco ); 
		break;
		
	case 105:
		res = Entrar_Diag_Mode_Visteon( dados_berco[berco].MensagemFalha1, berco ); 
		break;
	case 106:
		res = Sair_Diag_Mode_Visteon( dados_berco[berco].MensagemFalha1, berco );	
		break;
	case 107:
		res = Get_i_ref_EOL( dados_berco[berco].MensagemFalha1, berco );	
		break;

	case 1100:
		res = Entrar_Diag_Mode_costumer( dados_berco[berco].MensagemFalha1, berco );
		break;
	case 111:
		res = Sair_Diag_Mode_costumer( dados_berco[berco].MensagemFalha1, berco );	
		break;

	case 120:
		res = Ver_CyberSecurity_Ativado(dados_berco[berco].MensagemFalha1, berco); 
		break;
	case 121:
		res = Verificacao_Cosmetico_TFT(dados_berco[berco].MensagemFalha1, berco); 
		break;
	case 122:
		res = Verificacao_Cosmetico_TACO(dados_berco[berco].MensagemFalha1, berco); 
		break;
	case 123:
		res = Verificacao_Cosmetico_VELO(dados_berco[berco].MensagemFalha1, berco); 
		break;
	case 124:
		res = Verificacao_LEDS_Cluster_ON(dados_berco[berco].MensagemFalha1, berco); 
		break; 

	
	////////////////////////////////////////////////////////////////////////////////////
	//05/02/2018 
	//inversão de posição TFCP / VISION 
	case 300:
		///res = ConfiguraCyberSecurity(dados_berco[berco].MensagemFalha1, berco);
		break;

	case 510:
		///res = Grava_ECU_ID(dados_berco[berco].MensagemFalha1, berco);
		break;

	case 730:
		res = LerSoftwareVersion (dados_berco[berco].MensagemFalha1, berco);   //v
		break;

	case 1150:
		res = VerificaClientePN(dados_berco[berco].MensagemFalha1, berco);
		break;
	case 1160:
		res = VerificaMEC(dados_berco[berco].MensagemFalha1, berco);
		break;
	case 1170:
		res = VerificaBasePartNumber(dados_berco[berco].MensagemFalha1, berco);
		break;
	case 1180:
		res = GravaMEC(dados_berco[berco].MensagemFalha1, berco);   //g1  v
		break;
	case 1181:
		res = GravaMEC_Service(dados_berco[berco].MensagemFalha1, berco);   
		break;
	case 1190:
		res = GravaClientePN(dados_berco[berco].MensagemFalha1, berco); //g2
		break;
	case 1200:
		res = GravaTraceability(dados_berco[berco].MensagemFalha1, berco); //g3
		break;
	case 1210:
		res = GravaStatusByte(PRODUTO_APROVADO, dados_berco[berco].MensagemFalha1, berco);  //  end 
		break;
	case 1220:
		res = GravaStatusByte(PRODUTO_REJEITADO, dados_berco[berco].MensagemFalha1, berco);  // end
		break;
	case 1230:
		res = LeStatusByte(dados_berco[berco].MensagemFalha1, berco);  // end
		break;
	case 1240:
		res = VerificaSNCluster(dados_berco[berco].MensagemFalha1, berco);
		break;
	
	case 1300:
		res = Grava_VPPS (dados_berco[berco].MensagemFalha1, berco);
		break;	  
	case 1301:
		res = Grava_DUNS (dados_berco[berco].MensagemFalha1, berco);
		break;	  
		
	//////////////////////////////////////////////////////////////////////////////////////
	
	case 420:
	tent = 0;
	try_420:
		res = TensaoCAN (CAN_HI_MIN, berco); //ck  
		if (res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto)
		{
			Delay_thread(.3);
			tent = tent+1;
			if (tent<=3)
				goto try_420;
		}
			
				break;
    case 425:
	tent = 0;
	try_425:
		res = TensaoCAN (CAN_HI_MAX, berco); //ck
		if (res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto)
		{
			Delay_thread(.3);
			tent = tent+1;
			if (tent<=3)
				goto try_425;
		}
			
				break;
	case 430:
	tent = 0;
	try_430:
		res = TensaoCAN (CAN_LO_MIN, berco); //ck
		if (res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto)
		{
			Delay_thread(.3);
			tent = tent+1;
			if (tent<=3)
				goto try_430;
		}
		break;
	case 435:
	tent = 0;
	try_435:
		res = TensaoCAN (CAN_LO_MAX, berco); //ck
		if (res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto)
		{
			Delay_thread(.3);
			tent = tent+1;
			if (tent<=3)
				goto try_435;
		}
			
				break;
	default:
		MessagePopup ("ERRO NA TABELA", "Teste inexistente..." );
		return res;
	}
	
	if (berco == 1)
	{	
	 	SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, dados_berco[berco].MensagemFalha1);  
	}
	
	if (berco == 2)
	{	
	 	SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA_2, ATTR_CTRL_VAL, dados_berco[berco].MensagemFalha1);  
	}
	
	return res;
}

/******************************** FinalizaTestes() *****************************************************************/
// Função: FinalizaTestes()
//
int FinalizaTestes(double res, int berco)
{
int 
	file,
	i,
	status;
char 
	tmp[90],
	path[50];
	
//BD18
int
	resp [NUMERO_DE_BERCOS+1];
	
char 
	tmp_id_berco[20],
	mens_falha[BDSUPPORT_TAM_MAX_DESC_ERROR]={0};
enum tipo_seq_testes
	tmp_tipo_seq [NUMERO_DE_BERCOS+1];
	
	
	//////////////////////////////////
	while(oc_1 == 1)	  //sinc
		Delay_thread(0.01);
	oc_1=1;
	//////////////////////////////////
	
    //////////////////////////////////		
	atualizar_mens_can[berco] = OFF; //<---    
	Set_Vdut(VOLTS_0, berco);	
	Trava(OFF);
	start_test = OFF;
	if (berco == BERCO_1)
	{
		SAIDA.Battery_1 		= OFF;
		SAIDA.Crank_Run_1 		= OFF;
		SAIDA.VccDireto_Shunt_1 = OFF;
		SAIDA.HabilitaFonte_1	= OFF; 
		MoveConectorBerco1(OFF);
		Delay_thread(0.01);
		MoveClampBerco1(OFF);  
	}		
	if (berco == BERCO_2)
	{
		SAIDA.Battery_2 		= OFF;
		SAIDA.Crank_Run_2 		= OFF;
		SAIDA.VccDireto_Shunt_2 = OFF;
		SAIDA.HabilitaFonte_2	= OFF; 
		MoveConectorBerco2(OFF);
		Delay_thread(0.01);
		MoveClampBerco2(OFF);
	}			
	/////////////////////////////////	
	//if (dados_berco[BERCO_1].modulo_em_teste == OFF   && dados_berco[BERCO_2].modulo_em_teste == OFF) 
	//	SAIDA.ContatoraVibracao = OFF;
	 
	Delay_thread(0.01);

	
	
	///AdicionaImagemInstrucao(1, "Ler_Barcode_1.jpg", berco);
	///Delay_thread(0.050);
	strcpy(path,CAMINHO_SONS);
	if(sair_programa)
		return 0;
	
	if( res==FALHA_GRAVE )
	{
		Mensagem("Chame o técnico", dados_berco[berco].MensagemFalha1, "Aperte CONTINUE para abortar", "", MENS_VERMELHO, berco);
		do{
			Delay_thread(0.100);			
		}while( STATUS.Continua==OFF );
		ResetTextBox (painel_auto, dados_berco[berco].crtlID_mensagem , "" );
		if(!sair_programa) sair_programa=ON;
		return FALHA_GRAVE;
	}
	tempo_total=Timer()-dados_berco[berco].tempo_inic_total_teste;
	if( dados_berco[berco].rejeitado )
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
 		dados_berco[berco].status_produto = PRODUTO_REJEITADO;
		if( res != FALHA_TIMEOUT && res != FALHA_PRODUTO_AUSENTE && res != EMERG_ACIONADA )
		{
			TotalRejeitados++;
	      	TotalTestados++;
		}
	}
	else
	{
		dados_berco[berco].cor_mensagens  = MENS_VERDE;
	 	dados_berco[berco].status_produto = PRODUTO_APROVADO;
	    TotalAprovados ++;
	    TotalTestados++;
		strcat(path,"Sininho01.wav");	 
		CVI_PlaySound (path, ON );
		Delay_thread(0.7);	
		CVI_StopCurrentSound ();
	}
	sprintf(tmp_id_berco, "berco_%i", berco);
	
	if (berco == 1)
	{	
		switch (amostra_tipo_1)
		{
			case TESTE:
			case REPETIBILIDADE:	
				tmp_tipo_seq [berco] = BD_TESTE;
				break;
			case NEGATIVE_SAMPLE:
				tmp_tipo_seq [berco] = BD_AMOSTRA_NEGATIVA;
				break;
			case MASTER_SAMPLE:
				tmp_tipo_seq [berco] = BD_AMOSTRA_POSITIVA;
				break;
		}
	}
	else
	{	
		switch (amostra_tipo_2)
		{
			case TESTE:
			case REPETIBILIDADE:	
				tmp_tipo_seq [berco] = BD_TESTE;
				break;
			case NEGATIVE_SAMPLE:
				tmp_tipo_seq [berco] = BD_AMOSTRA_NEGATIVA;
				break;
			case MASTER_SAMPLE:
				tmp_tipo_seq [berco] = BD_AMOSTRA_POSITIVA;
				break;
		}
	}
	resp[berco]=BDSupport_Salvar_Sequencia_Testes(dados_berco[berco].SequenciaBD,
										   VERSAO, 
										   tmp_tipo_seq[berco],
										   tmp_id_berco,
										   dados_berco[berco].N_Serie_EndItem,
										   (dados_berco[berco].status_produto == PRODUTO_APROVADO?BD_APROVADO:BD_REJEITADO), 
										   tempo_total,
										   mens_falha);

	if( cim_conectado == ON && res != FALHA_PRODUTO_AUSENTE && res != FALHA_TIMEOUT && res != EMERG_ACIONADA  && (strstr(dados_berco[berco].tipo_amostra,"Teste") != NULL) )
	{
		MoveOut_Build_Cim( dados_berco[berco].prefixo_enditem, res, 
						   
						   dados_berco[berco].rejeitado, 
						   Teste[berco][dados_berco[berco].num_teste].Nome, berco );
	}
	//Grava as estatisticas em arquivo
	file = OpenFile( ARQ_FTT , VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII );
	Fmt( tmp, "%f[p0]", TotalTestados);
	WriteLine ( file, tmp, strlen(tmp) );
	Fmt( tmp, "%f[p0]", TotalAprovados);
	WriteLine ( file, tmp, strlen(tmp) );
	Fmt( tmp, "%f[p0]", TotalRejeitados);
	WriteLine ( file, tmp, strlen(tmp) );
	Fmt( tmp, "%f[p1]", ftt);
	WriteLine ( file, tmp, strlen(tmp) );
	CloseFile ( file );
	AtualizaFTT();
	// -----------------------  Coleta Dados ----------------------------------              
	if( coletando_dados && res != FALHA_TIMEOUT && res != FALHA_PRODUTO_AUSENTE && res != EMERG_ACIONADA )
		ColetaDados(dados_berco[berco].max_teste, berco);	
	if (berco == 1)
	{	
		SetCtrlVal (painel_auto, AUTO_RETRABALHO_1,dados_berco[1].retrabalho);
	}
	
	if (berco == 2)
	{	
		SetCtrlVal (painel_auto, AUTO_RETRABALHO_2,dados_berco[2].retrabalho); 
	}
	i=0;
 	while(i <= dados_berco[berco].max_teste)
	{
 		Teste[berco][i].Resultado = RES_FALHA;
 		strcpy(Teste[berco][i].Condicao ,"N.T.");
	 	i++;
 	}
	status = MensFinal( Rodape, TotalRejeitados, tempo_total, res, Teste[berco][dados_berco[berco].num_teste].LimAlto, Teste[berco][dados_berco[berco].num_teste].LimBaixo, Teste[berco][dados_berco[berco].num_teste].Nome, dados_berco[berco].num_teste, berco );
	
	if (berco ==BERCO_1)
		SetCtrlAttribute (painel_auto, AUTO_TEMPO_TOTAL, ATTR_CTRL_VAL,tempo_total);
 	
	if (berco ==BERCO_2)
		SetCtrlAttribute (painel_auto, AUTO_TEMPO_TOTAL_2, ATTR_CTRL_VAL,tempo_total);

	dados_berco[berco].status_produto 	= PRODUTO_OFF;
	Deligar_Vibracao( dados_berco[berco].MensagemFalha1, berco );    

	// -------------------- Espera retirar Produto ------------------------------
	while( dados_berco[berco].status_debounc_presenca_produto && !sair_programa && status_emergencia && !sair_programa )
	{
		dados_berco[berco].parar_mensagens_auto = ON;
		Mensagem( " ", "-- Retire o Produto no berço de Testes --", " ", "", MENS_AZUL, berco);
		Delay_thread(0.001);
		dados_berco[berco].parar_mensagens_auto = OFF;
	}
	HidePanel(painel_mensagens);
	dados_berco[BERCO_1].iSwap = 0; 
	dados_berco[BERCO_2].iSwap = 0;
	Delay_thread(0.001);
	oc_1=0;  //<-- 
	
	
	// ----------------- Imprime etiqueta do produto ----------------------------
	if(strstr(dados_berco[berco].tipo_amostra,"Teste") != NULL) 
	{
		if(!dados_berco[berco].rejeitado && imprimir && usar_printer == ON && dados_berco[berco].retrabalho == OFF)
		{
		 	Gerar_etiqueta(dados_berco[berco].ref_GM,
						   dados_berco[berco].N_Serie_EndItem,
						   dados_berco[berco].vpps_code,
						   dados_berco[berco].duns_code,
						   dados_berco[berco].prefixo_enditem);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	Delay_thread(0.001);
	///dados_berco[berco].testar_produto = OFF;
	///dados_berco[berco].modulo_em_teste = OFF;
	///dados_berco[berco].barcode_enditem_lido = OFF;
	HidePanel(painel_mensagens);
	
	if (berco ==1)
		ResetTextBox( painel_auto,AUTO_TXT_SERIE_1, "\0");
	if (berco ==2)
	{
		//Delay_thread(.3);
		ResetTextBox( painel_auto,AUTO_TXT_SERIE_2, "\0");
	}
	dados_berco[berco].retrabalho = OFF;

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, ""); 
	ResetBarcode(OFF,  berco);
	
	return 0;
}

/******************************** StatusTeste() *****************************************************************/
// Função: StatusTeste()
//
int StatusTeste( double res, int berco )
{
	int 
		status,
		
//BD15
	resp [NUMERO_DE_BERCOS+1];
	
		
		
	char 
		tmp[90];
		
//BD16
char
	mens_falha[BDSUPPORT_TAM_MAX_DESC_ERROR];
		
	
	if( sair_programa )
		return 0;

	if( res==FALHA_GRAVE ){
		return FALHA_GRAVE;
	}

	Rodape = "";
	dados_berco[berco].retestar = OFF;
	Teste[berco][dados_berco[berco].num_teste].Resultado = res;
	Teste[berco][dados_berco[berco].num_teste].Tempo_teste = Timer()-dados_berco[berco].tempo_inicial_teste;
	if ((res > Teste[berco][dados_berco[berco].num_teste].LimAlto) | (res < Teste[berco][dados_berco[berco].num_teste].LimBaixo) || dados_berco[berco].rejeita_montagem)
	{ 
		dados_berco[berco].rejeitado = ON;
		SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_status, ATTR_TEXT_COLOR, VAL_DK_RED);
	 	strcpy(Teste[berco][dados_berco[berco].num_teste].Condicao,"Rejeit");
	}
	else
	{
		SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_status, ATTR_TEXT_COLOR, VAL_DK_BLUE);
	 	strcpy(Teste[berco][dados_berco[berco].num_teste].Condicao,"Aprov");
	}  
	
	
	//BD14
	resp[berco]=BDSupport_Adiciona_Teste_Executado_Na_Sequencia(&dados_berco[berco].SequenciaBD, 
								Teste[berco][dados_berco[berco].num_teste].Nome, 
								Teste[berco][dados_berco[berco].num_teste].LimBaixo,
								Teste[berco][dados_berco[berco].num_teste].Resultado,
								Teste[berco][dados_berco[berco].num_teste].LimAlto,
								Teste[berco][dados_berco[berco].num_teste].Unidade,
								(strcmp(Teste[berco][dados_berco[berco].num_teste].Condicao,"Aprov")==0?BD_APROVADO:BD_REJEITADO),
								Teste[berco][dados_berco[berco].num_teste].Tempo_teste,
								mens_falha);

	
	
	
	ReplaceTextBoxLine (painel_auto, dados_berco[berco].crtlID_status, 0, Teste[berco][dados_berco[berco].num_teste].Condicao);
	Fmt(tmp, "%f[p2]", res);
	ReplaceTextBoxLine (painel_auto, dados_berco[berco].crtlID_resultado, 0, tmp);
	Fmt(tmp, "%f[p2]", Teste[berco][dados_berco[berco].num_teste].Tempo_teste);
	ReplaceTextBoxLine (painel_auto, dados_berco[berco].crtlID_tempo, 0, tmp);
	if( dados_berco[berco].rejeitado )
	{
    	status = FuncRejeitado(Rodape, dados_berco[berco].MensagemFalha1, berco);
	 	if (status != CONT)
		{
			dados_berco[berco].aborta_testes = ON;
			dados_berco[berco].retestar  = OFF;
			dados_berco[berco].rejeitado = ON;
		}
		if (status == CONT)
	 	{
			dados_berco[berco].aborta_testes = OFF;
			dados_berco[berco].retestar  = ON;
			dados_berco[berco].rejeitado = OFF;
	 	}
	}
	Fmt(tmp, "%f[p2]", Teste[berco][dados_berco[berco].num_teste].Tempo_teste);
	status = ReplaceTextBoxLine (painel_auto, dados_berco[berco].crtlID_tempo, 0, tmp);
	if(!dados_berco[berco].rejeitado && !dados_berco[berco].retestar) 
	{
		dados_berco[berco].num_teste ++;   
		dados_berco[berco].retestar 	= OFF;
	}
	return 0;
}

/******************************** InicializaTestes() *****************************************************************/
// Função: InicializaTestes()
//
int InicializaTestes(int berco)
{
int status = 0;	
	char
		group_id[6];
		
//BD11
char
	mens_falha[BDSUPPORT_TAM_MAX_DESC_ERROR]={0};	
		
	 
		//BD10
	    BDSupport_Criar_Sequencia_Testes(&dados_berco[berco].SequenciaBD, mens_falha);
		
		SetCtrlVal(painel_auto,AUTO_LED_TRD,OFF); 
		SetCtrlVal(painel_auto,AUTO_LED_LC,OFF); 
		
		if (cim_conectado && (strstr(dados_berco[berco].tipo_amostra,"Teste") != NULL))
		{
			if (MoveIn_Cim(berco) < 0)
				goto error;
		}
		
		if (berco == 1)
		{
			atualizar_mens_can[BERCO_1] = OFF; //<---    
			Desabilita_Scanner(SCANNER_1);
			status = MoveClampBerco1(ON);
			if(status == SEM_ERRO)
				status = MoveConectorBerco1(ON);
		}
		if (berco == 2)
		{
			atualizar_mens_can[BERCO_2] = OFF; //<---    
			Desabilita_Scanner(SCANNER_2);
			status = MoveClampBerco2(ON);
			if(status == SEM_ERRO)
				status = MoveConectorBerco2(ON);
		}
		Inicializa_LedsSaidas(berco);
		
		if(status != SEM_ERRO || dados_berco[berco].status_debounc_presenca_produto==OFF)
		{   
	 		if(dados_berco[berco].status_debounc_presenca_produto==OFF)
				status = -999;
			 goto error;
		} 	
	
	t_sinc_1 = 0;
	t_sinc_2 = 0;	
	strcpy(group_id, dados_berco[berco].prefixo_enditem);
	dados_berco[berco].rejeita_montagem = OFF;
	dados_berco[berco].tempo_inic_total_teste = dados_berco[berco].tempo_inicial_teste=Timer ();
	
	dados_berco[berco].status_produto = PRODUTO_TESTANDO;
	dados_berco[berco].aborta_testes = OFF;
	dados_berco[berco].retestar = OFF;
	dados_berco[berco].num_teste = 1;

	return 0;

error:
	if (HW_present == ON)   
    {			
	
	 //////////////////////////////
	 if (berco == 1)
		 MoveConectorBerco1(OFF);
	 
	 if (berco == 2)
		 MoveConectorBerco2(OFF);  
	 
	 Delay_thread(2);
	 
	 if (berco == 1)
		 MoveClampBerco1(OFF);
	 
	 if (berco == 2)
		 MoveClampBerco2(OFF);
	 /////////////////////////////
	 
	}
	 dados_berco[berco].rejeitado = ON;
	 if(status == -999)
	 {
		 	Mensagem( "ERRO ao travar cluster","O produto foi removido do berço",  "" ,"", MENS_VERMELHO, berco) ;
	 }
	 else
	 {
		 if (status == -1 || status == -2 )
		 	Mensagem( "ERRO ao mover conector","Retire o produto do berço",  "" ,"", MENS_VERMELHO, berco) ;
 
		 if (status == -11 || status == -12)
			 Mensagem( "Time out !!!", "", "Retire o produto do berço" ,"", MENS_VERMELHO, berco); 
 	 }
	 strcpy( dados_scanner[berco].strGotScanner,"");
	 dados_berco[berco].barcode_enditem_lido = OFF;
	 while(dados_berco[berco].status_debounc_presenca_produto == ON)
	 	Delay_thread(0.1);
	 dados_berco[berco].rejeitado = OFF;
	 
	ResetBarcode(OFF, berco);
 	dados_berco[berco].status_produto = PRODUTO_OFF;
	dados_berco[berco].testar_produto = OFF;
	dados_berco[berco].modulo_em_teste = OFF;
	return -1;
}
/******************************** Complet_EndItem() *****************************************************************/
void Complet_EndItem(int berco)
{
char temp [50] ={0};
				 
	
	strcpy(temp, dados_berco[berco].prefixo_enditem);
	CopyString(temp,5,dados_berco[berco].N_Serie_EndItem,3,-1);
	strcpy(dados_berco[berco].N_Serie_EndItem,temp);
	
}


/******************************** VerificaExcecoesExecucao() *****************************************************************/
// Função: VerificaExcecoesExecucao()
//
// Descrição: Esta função é utilizada para realizar validações básicas
//            durante os laços para aguardar ações em testes.
//
// Parametros:
//
//   - resp: caso uma excecao seja identifcada, retorna o número da mesma.
//
//   - mens_falha: caso uma excecao seja identifcada, retorna a sua descrição.
//
// Retorno : Retorna o valor '0' caso não tenha ocorrido qualquer excecao.
//
int VerificaExcecoesExecucao(double *resp, char * mens_falha, int berco)
{
	if( dados_berco[berco].rejeita_montagem==ON )  //|| STATUS.Rejeita==ON 
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		strcpy(mens_falha,"Produto rejeitado pelo operador.");
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = FALHA_REJ_OPERADOR;
		return -1;
	}
	if( !status_emergencia )
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		strcpy(mens_falha,"Produto rejeitado pelo operador - Emergência Acionada.");
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = EMERG_ACIONADA;
		return -1;
	}
	if( !dados_berco[berco].status_debounc_presenca_produto )
	{
		MENS_WARNING = MENS_PRODUTO_AUSENTE;
		*resp = FALHA_PRODUTO_AUSENTE;
		Delay_thread(0.010);
		return -1;
	}
	if ( sair_programa )
	{
		*resp = EXIT_PROGRAM;
		return -1;
	}

	return 0;
}

//
//
// Função: VerificaExcecoesExecucaoBiManual()
//
// Descrição: Esta função é utilizada para realizar validações básicas
//            durante os laços para aguardar bimanual em testes.
//
// Parametros:
//
//   - resp: caso uma excecao seja identifcada, retorna o número da mesma.
//
//   - mens_falha: caso uma excecao seja identifcada, retorna a sua descrição.
//
// Retorno : Retorna o valor '0' caso não tenha ocorrido qualquer excecao.
//
int VerificaExcecoesExecucaoBiManual(double *resp, char * mens_falha, int berco)
{
	if( dados_berco[berco].rejeita_montagem==ON)
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		strcpy(mens_falha,"Produto rejeitado pelo operador.");
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = FALHA_REJ_OPERADOR;
		return -1;
	}
	if( !status_emergencia )
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		strcpy(mens_falha,"Produto rejeitado pelo operador - Emergência Acionada.");
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = EMERG_ACIONADA;
		return -1;
	}
	if( !dados_berco[berco].status_debounc_presenca_produto )
	{
		MENS_WARNING = MENS_PRODUTO_AUSENTE;
		*resp = FALHA_PRODUTO_AUSENTE;
		Delay_thread(0.010);
		return -1;
	}
	if ( sair_programa )
	{
		*resp = EXIT_PROGRAM;
		return -1;
	}

	return 0;
}

//
//
// Função: VerificaExcecoesMovimentoAtuador()
//
// Descrição: Esta função é utilizada para realizar validações básicas
//            após mover atuadores.
//
// Parametros:
//
//   - resp: caso uma excecao seja identifcada, retorna o número da mesma.
//
//   - mens_falha: caso uma excecao seja identifcada, retorna a sua descrição.
//
// Retorno : Retorna o valor '0' caso não tenha ocorrido qualquer excecao.
//
int VerificaExcecoesMovimentoAtuador(char titulo_atuador[], int status_atuador, double *resp, char * mens_falha, int berco)
{
	if( !status_emergencia )
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		strcpy(mens_falha,"Produto rejeitado pelo operador - Emergência Acionada.");
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = EMERG_ACIONADA;
		return -1;
	}
	if ( sair_programa )
	{
		*resp = EXIT_PROGRAM;
		return -1;
	}
	if ( status_atuador == FALHA_TIMEOUT )
	{
		dados_berco[berco].cor_mensagens = MENS_VERMELHO;
		Fmt(mens_falha,"Time Out - %s", titulo_atuador);
		strcpy(dados_berco[berco].mens_montagem_2,"");
		strcpy(dados_berco[berco].mens_montagem_3,"");
		Fmt(dados_berco[berco].mens_montagem_falha,"Falha ao mover o atuador '%s'", titulo_atuador);
		SetCtrlAttribute (painel_auto, AUTO_MENS_FALHA, ATTR_CTRL_VAL, mens_falha);
		*resp = FALHA_TIMEOUT;
		return -1;
	}

	return 0;
}


void DAQ_manager (int berco)
{
double
	t   = 0,
	time_out = 10;

		//////////////////////////////////////////////////////////////////////////////////
		if(berco == 1)
		{
			if(dados_berco[2].medindo_tensao == ON)
			{
				t = Timer();
				while(dados_berco[2].medindo_tensao == ON && Timer()- t < time_out)
					Delay_thread(0.010);
				if(dados_berco[2].medindo_tensao == ON)
					return -5;
			}
			dados_berco[1].medindo_tensao 	= ON;
		}
		if(berco == 2)
		{
			if(dados_berco[1].medindo_tensao == ON)
			{
				t = Timer();
				while(dados_berco[1].medindo_tensao == ON && Timer()- t < time_out)
					Delay_thread(0.010);
				if(dados_berco[1].medindo_tensao == ON)
					return -6;
			}
			dados_berco[2].medindo_tensao 	= ON;
		}
		////////////////////////////////////////////////////////////////////////////////////
}

//
// Função: Corrente_Bateria()
//
double Corrente_Bateria(char * mens_falha, int berco)
{
double 
	limite_corrente_alta = 1200, //mA
	res = 0, 
	t   = 0,

   	timeout	 = 2.0;
int 
	i = 0,

	canal 		 = 0,

	tent 		 = 0;
	
char 
	mens1[100] = {0},
	i_s[5] = {0};	
	
	
    canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	t= 0;
		
try_1:
	Set_Vdut(VOLTS_13_5, berco);
	
	InicializaCAN(can_defin[berco].nome,  can_defin[berco].canal, berco);
	if (berco == BERCO_1)
	{
		//Delay_thread(0.1);
		canal = 0; 
		SAIDA.Battery_1 		= ON;
		SAIDA.Crank_Run_1 		= ON;
		SAIDA.VccDireto_Shunt_1 = OFF; //<---*
		Delay_thread(0.1);  
		SAIDA.HabilitaFonte_1	= ON; 
		atualizar_mens_can[BERCO_1] = ON; //<---
	}		
	if (berco == BERCO_2)
	{
		//Delay_thread(0.1);  
		canal = 8;
		SAIDA.Battery_2 		= ON;
		SAIDA.Crank_Run_2 		= ON;
		SAIDA.VccDireto_Shunt_2 = OFF; //<--*
		Delay_thread(0.1);  
		SAIDA.HabilitaFonte_2	= ON; 
		atualizar_mens_can[BERCO_2] = ON; //<---
	}
	Delay_thread(0.1);
	
	if (dados_berco[berco].retestar == OFF)
	{	
		parar_mensagem_auto = ON;
		//waiting product start  
		for (i=1; i<=5; i++)
		{	
		    Fmt(i_s,"%s<%i" ,i);
			strcpy(mens1,"> Aguarde ligando produto ... ");  
			strcat (mens1, i_s);
			Mensagem(mens1, "", "","", MENS_AZUL, berco); 
		    Delay_thread(1);
		}
		strcpy(mens1,""); 
		parar_mensagem_auto = OFF;
    }
 
	strcpy(mens_falha, " "); 
	
	
	tent = 0;
	
	
	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
	t=Timer();
	do
	{
	        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
			res = res * 1000 ;// res em mA  
			if(res>limite_corrente_alta)
			{
				strcpy(mens_falha, "Produto em curto ...");
				Set_Vdut(VOLTS_0, berco);
				break;
			}
			Delay_thread(0.01);
	}
	while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	if(res>limite_corrente_alta)
	{
		dados_berco[berco].medindo_tensao 	= OFF;
		return res;
	}
	if ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && tent <=3)
	{			
		tent = tent+1;
		goto try_1;
	}
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	t=Timer();
	while((dados_berco[1].medindo_tensao == ON || dados_berco[2].medindo_tensao == ON) && Timer()-t < timeout)//sincronizar berços
		Delay_thread(0.010);
		
	
return res;
}



double Get_i_ref_EOL (char * mens_falha, int berco)
{

double  
		res = 0, 
		t   = 0,
		leitura	 = 0,
       	timeout	 = 7.0,
		lim_min	 = -5,
		lim_max	 = 5;

int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	
	tent 		 = 0;
char 
	mens1[30] = {0},
	i_s[5] = {0};			

	modo_thread = ESCRITA_E_LEITURA;
	Mensagem( "Medição da Corrente de", "ref EOL", "","",MENS_AZUL, berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	
  
	t= 0;
	
		
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	
	Delay_thread(.1);


	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
	t=Timer();
	do
	{
	    res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
		res = res * 1000 ;// res em mA
		Delay_thread(.1);
	}
	while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////

	i_ref_EOL [berco] = res; //get i ref

	return res;

}


//
// Função: Corrente_Leds_Ambar()
//
double Corrente_Leds_Ambar(char * mens_falha, int berco)
{
int status = 0;
double  
	res = 0, 
	t   = 0,
	leitura	 = 0,
   	timeout	 = 7.0,
	lim_min	 = -5,
	lim_max	 = 5;

int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	sair		 = OFF,
	tent 		 = 0,
	atualizar_painel = ON;
char 
	mens1[30] 	 = {0},
	i_s[5] 		 = {0};			

	
	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
			atualizar_painel = OFF;

	Mensagem( "Medição da Corrente de", "LEDS Ambar", "","", MENS_AZUL, berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	
  
	t= 0;
	
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, ON, berco); 
	Ilumination_PWM_DIAG(TELLTALES_ILL, 100, berco); 
	
	Delay_thread(.1);

	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
		t=Timer();
		do
	   	{
	        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
			res = res * 1000 ;// res em mA
			Delay_thread(.1);
		}
		while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	
	res = res - i_ref_EOL[berco];
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, OFF, berco);
	
	return res;



}

//
// Função: Verificacao_Leds_Ambar_1()
//
double Verificacao_Leds_Ambar_1(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	st = 0,
	status = 0,
	status_bot,
	atualizar_painel = ON;
		
		modo_thread = ESCRITA_E_LEITURA;
		
		///////////////////
		Sinc_test (berco);  
		///////////////////
		
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
				///atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_AMBER);
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (AMBAR)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template);
			DisplayPanel (painel_padrao); 
		}
	
		Delay_thread(0.1);
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, ON, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds AMBER");
			return -1;
		}
		status = Ilumination_PWM_DIAG(TELLTALES_ILL, 100, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controle do PWM Telltales");
			return -2;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, " ");
		strcpy(dados_berco[berco].mens_montagem_3, " ");
		
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, OFF, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar leds AMBER");
			return -3;
		}
		///HidePanel (painel_padrao);
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);	
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		dados_berco[berco].rejeita_montagem = OFF;
		 
		parar_mensagem_auto = OFF;
return res;
}




//
// Função: Corrente_Leds_Azul()
//
double Corrente_Leds_Azul(char * mens_falha, int berco)
{

double  
		res = 0, 
		t   = 0,
		leitura	 = 0,
       	timeout	 = 7.0,
		lim_min	 = -5,
		lim_max	 = 5;

int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	sair		 = OFF,
	tent 		 = 0,
	atualizar_painel = ON;
char 
	mens1[30] = {0},
	i_s[5] = {0};

	
	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
			atualizar_painel = OFF;

	Mensagem( "Medição da Corrente de", "LED Azul", "","",MENS_AZUL, berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	
	t= 0;
	
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE, ON, berco); 
	
	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////

	t=Timer();
	do
   	{
        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
		res = res * 1000 ;// res em mA
		Delay_thread(.1);
	}
	while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	
	res = res - i_ref_EOL[berco];
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE, OFF, berco);
	
	return res;

}

//
// Função: Verificacao_Leds_Azul()
//
double Verificacao_Leds_Azul(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		 
		Mensagem("", "", "","", MENS_AZUL, berco); 
	
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
				///atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_BLUE);
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (AZUL)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE, ON, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds BLUE");
			return -1;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1); 
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE, OFF, berco);  
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar leds BLUE");
			return -2;
		}
		///HidePanel (painel_padrao);
		
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1); 
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	   
		dados_berco[berco].rejeita_montagem = OFF;
		
		parar_mensagem_auto = OFF; 
		return res;
}




//
// Função: Corrente_Leds_Vermelhos()
//
double Corrente_Leds_Vermelhos(char * mens_falha, int berco)
{

double  
	res = 0, 
	t   = 0,
	leitura	 = 0,
   	timeout	 = 7.0,
	lim_min	 = -5,
	lim_max	 = 5;

int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	sair		 = OFF,
	tent 		 = 0,
	atualizar_painel = ON;
char 
	mens1[30] 	= {0},
	i_s[5] 		= {0};			

	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
			atualizar_painel = OFF;
	
	Mensagem( "Medição da Corrente de", "LED vermelho", "","",MENS_AZUL,berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	
  
	t= 0;
	
		
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, ON, berco); 
	

	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
		t=Timer();
		do
	   	{
	        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
			res = res * 1000 ;// res em mA
			Delay_thread(.1);
		}
		while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	
	res = res - i_ref_EOL[berco];
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, OFF, berco);
	
	return res;

}

//
// Função: Verificacao_Leds_Vermelhos_1()
//
double Verificacao_Leds_Vermelhos_1(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		 
		Mensagem("", "", "","", MENS_AZUL, berco); 
	
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
				///atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_RED);
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (VERMELHO)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, ON, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds RED");
			return -1;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, OFF, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar leds RED");
			return -2;
		}
		///HidePanel (painel_padrao);
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	 
		dados_berco[berco].rejeita_montagem = OFF;
		
		parar_mensagem_auto = OFF; 
		return res;
}



//
// Função: Corrente_Leds_Verdes()
//
double Corrente_Leds_Verdes(char * mens_falha, int berco)
{

double  
	res = 0, 
	t   = 0,
	leitura	 = 0,
   	timeout	 = 7.0,
	lim_min	 = -5,
	lim_max	 = 5;
int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	sair		 = OFF,
	tent 		 = 0,
	atualizar_painel = ON;
char 
	mens1[30] = {0},
	i_s[5] = {0};			

	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
			atualizar_painel = OFF;
	Mensagem( "Medição da Corrente de", "LED verdes", "","",MENS_AZUL,berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
  
	t= 0;
		
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, ON, berco); 
	

	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
		t=Timer();
		do
	   	{
	        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
			res = res * 1000 ;// res em mA
			Delay_thread(.1);
		}
		while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	
	res = res - i_ref_EOL[berco];
	Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, OFF, berco);
	
	return res;

}

//
// Função: Verificacao_Leds_Verdes_1()
//
double Verificacao_Leds_Verdes_1(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
				///atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_GREEN);
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (VERDE)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
			
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, ON, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds GREEN");
			return -1;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);  
		dados_berco[berco].cor_mensagens = MENS_AZUL;
	
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, OFF, berco);   
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar leds GREEN");
			return -2;
		}
		///HidePanel (painel_padrao);
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	   
		parar_mensagem_auto = OFF;
		dados_berco[berco].rejeita_montagem = OFF;
		
return res;
}



//
// Função: Corrente_Leds_Brancos()
//
double Corrente_Leds_Brancos(char * mens_falha, int berco)
{

double  
	res = 0, 
	t   = 0,
	leitura	 = 0,
   	timeout	 = 7.0,
	lim_min	 = -5,
	lim_max	 = 5;

int 
	i = 0,
	leit_por_seg = 1000, 
	quant_leit	 = 2000,
	canal 		 = 0,
	sair		 = OFF,
	tent 		 = 0,
	atualizar_painel = ON,
	status;
char 
	mens1[30] = {0},
	i_s[5] = {0};			


	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
			atualizar_painel = OFF;
	
	Mensagem( "Medição da Corrente de", "LED branco", "","",MENS_AZUL,berco);
	Delay_thread(.1); 
	
	canal 				= 0; 
	MENS_WARNING 		= MENS_OFF;
	
  
	t= 0;
	
		
	if (berco == BERCO_1) 
		 canal = 0;
	
	if (berco == BERCO_2) 
		 canal = 8;

	modo_thread = ESCRITA_E_LEITURA;
	status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, ON, berco);
	if(status == SUCESSO)
		status = Acende_lampada_cluster_DIAG(CRUISE_ON,ON, berco);
	if(status == SUCESSO)
		status = Ilumination_PWM_DIAG(TELLTALES_ILL, 100, berco);
	if(status != SUCESSO)
	{
		strcpy(mens_falha, "Falha na comunicação CAN para acender leds GREEN");
		return -1;
	}

	

	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
		t=Timer();
		do
	   	{
	        res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1); 
			res = res * 1000 ;// res em mA
			Delay_thread(.1);
		}
		while ((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo|| res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && Timer()-t < timeout) ; 
	
	//////////////////////////////////////////
	dados_berco[berco].medindo_tensao 	= OFF;
	//////////////////////////////////////////
	
	res = res - i_ref_EOL[berco];
	
	
	return res;

}

//
// Função: Verificacao_Leds_Brancos()
//
double Verificacao_Leds_Brancos(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
		
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_WHITE);
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (BRANCO)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao); 
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, ON, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds WHITE");
			return -1;
		}
		status = Acende_lampada_cluster_DIAG(CRUISE_ON,ON, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para acender leds CRUISE ON");
			return -2;
		}
		status = Ilumination_PWM_DIAG(TELLTALES_ILL, 100, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controlar PWM Telltales");
			return -3;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot =  BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, OFF, berco); 
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar leds White");
			return -4;
		}
		status = Acende_lampada_cluster_DIAG(CRUISE_ON,OFF, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para apagar led CRUISE ON");
			return -5;
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	   
		parar_mensagem_auto = OFF;
		dados_berco[berco].rejeita_montagem = OFF;
	
		
		return res;
}



//
// Função: Verificacao_Leds_All_ON()
//
double Verificacao_Leds_All_ON(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_ALL_ON);
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS acendem (TODOS)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE,  ON, berco);
		if(status == SUCESSO)
	    	status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED,   ON, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, ON, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, ON, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, ON, berco);
		if(status == SUCESSO)
			status = Ilumination_PWM_DIAG(TELLTALES_ILL, 100, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para Acender All Leds ON");
			return -1;
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);   
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE,  OFF, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED,   OFF, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, OFF, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, OFF, berco);
		if(status == SUCESSO)
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, OFF, berco);
		if(status != SUCESSO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para Apagar All Leds ON");
			return -2;
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
		
		parar_mensagem_auto = OFF;  
return res;
		
}

//
// Função: Verificacao_Leds_All_OFF()
//
double Verificacao_Leds_All_OFF(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_TELLTALES_ALL_OFF); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique se os LEDS apagam (TODOS)");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 
return res;
}

//
// Função: Gages_0_Kmh_0_RPM()
//
double Gages_0_Kmh_0_RPM(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	
		///while (STATUS.Continua == ON)
			///Delay_thread(.1);
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
		//		atualizar_painel = OFF;
				
		if(atualizar_painel)
		{
			
			strcpy(img_comp, foto_GAGES_0_0); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique  os Ponteiros");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		if (test_diag == 1)
		{	
			status = SetTacometroCustomer_DIAG(0,berco); 
			Delay_thread(.1);
			status = SetTacometroCustomer_DIAG(0,berco);
			if(status == SUCESSO)
			{				
				status = SetVelocimetroCustomer_DIAG(0, berco);
				Delay_thread(.1); 
				status = SetVelocimetroCustomer_DIAG(0, berco); 
			}
			if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em modo DIAG CUSTOMER");
				return -1;
			}
		}
		else
		{
			status = SetaMensTaco(0, berco);	
			if(status == SUCESSO)
				status = SetaMensVelo(0, berco);
				if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em Live mode ");
				return -1;
			}
		   
		}
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 	
return res;
		
 }




//
// Função: Gages_80_Kmh_3000_RPM()
//
double Gages_80_Kmh_3000_RPM(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	///while (STATUS.Continua == ON)
		///Delay_thread(.1);
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_GAGES_3000_80);
		
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique  os Ponteiros");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		if (test_diag == 1)
		{
			status = SetTacometroCustomer_DIAG(3000,berco);
			Delay_thread(.1);
			status = SetTacometroCustomer_DIAG(3000,berco);
			if(status == SUCESSO)
			{
				status = SetVelocimetroCustomer_DIAG(80, berco);
				Delay_thread(1);
				status = SetVelocimetroCustomer_DIAG(80, berco);
			}
			if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em modo DIAG CUSTOMER");
				return -1;
			}
		}
		else
		{
			status = SetaMensTaco(3000, berco);	
			if(status == SUCESSO)
				status = SetaMensVelo(80, berco);
				if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em Live mode ");
				return -1;
			}
		   
		}
		
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		 
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF;    
		return res;
		
 }


//
// Função: Gages_200_Kmh_8000_RPM()
//
double Gages_200_Kmh_8000_RPM(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	
	while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	 
	///////////////////
	Sinc_test (berco);  
	///////////////////
	 
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_GAGES_8000_200);
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique  os Ponteiros");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
	
		if (test_diag == 1)
		{
			status = SetTacometroCustomer_DIAG(8000,berco);
			Delay_thread(.1);
			status = SetTacometroCustomer_DIAG(8000,berco); 
			
			if(status == SUCESSO)
			{
				status = SetVelocimetroCustomer_DIAG(200, berco);
				Delay_thread(.1);
				status = SetVelocimetroCustomer_DIAG(200, berco);
			}	
			if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em modo DIAG CUSTOMER");
				return -1;
			}
		}
		else
		{
			status = SetaMensTaco(8000, berco);	
			if(status == SUCESSO)
				status = SetaMensVelo(200, berco);
				if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos GAGES em Live mode ");
				return -1;
			}
		   
		}
		
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
	
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
				
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 
return res;
		
}



//
// Função: Verificacao_Padrao_Display_SEG_1()
//
double Verificacao_Padrao_Display_SEG_1(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	atualizar_painel = ON;
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "Disp_TFT_All_OFF.png");
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_SEGMENTADO;
		status = Display_pattern_CAN (PATTERN_LCD_ALL_OFF, berco);
		if(status != SEM_ERRO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controle do display PATTERN ALL OFF");
			return -1;
		}
		
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1); 
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		
		if(status_emergencia == ON)
		{
			while (status != CONT  && status != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	
		if(status == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF;    
		return res;
 }



//
// Função: Verificacao_Padrao_Display_SEG_2()
//
double Verificacao_Padrao_Display_SEG_2(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	atualizar_painel = ON;
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "Disp_Segm_All_ON.png");
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao); 
		}
		modelo_display[berco] = DISPLAY_SEGMENTADO;
		status = Display_pattern_CAN (PATTERN_LCD_ALL_ON, berco);
		if(status != SEM_ERRO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controle do display PATTERN ALL ON");
			return -1;
		}
		
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		
		if(status_emergencia == ON)
		{
			while (status != CONT  && status != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao);  
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	  
		
		if(status == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF;  
		return res;
 }

//
// Função: Verificacao_Padrao_Display_MONO_1()
//
double Verificacao_Padrao_Display_MONO_1(char * mens_falha, int berco)
{

	double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
	
	while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	 
	///////////////////
	Sinc_test (berco);  
	///////////////////
	 
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "Disp_TFT_All_OFF.png");
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_TFT_MONO;
		status = Display_pattern_CAN (PATTERN_LCD_ALL_OFF, berco);
		if(status != SEM_ERRO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controle do display PATTERN ALL OFF");
			return -1;
		}
		
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);

			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
			
		parar_mensagem_auto = OFF;
		return res;
		

}

//
// Função: Verificacao_Padrao_Display_MONO_2()
//
double Verificacao_Padrao_Display_MONO_2(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "TFT_All_ON.png");
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_TFT_MONO;
		status = Display_pattern_CAN (PATTERN_LCD_ALL_ON, berco);
		if(status != SEM_ERRO)
		{
			strcpy(mens_falha, "Falha na comunicação CAN para controle do display PATTERN LCD ALL OFF");
			return -1;
		}
		
		
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF;  
		return res;
		

}

//
// Função: Verificacao_Padrao_Display_MONO_3()
//
double Verificacao_Padrao_Display_MONO_3(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	atualizar_painel = ON;
	
	Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "TFT_Mono_Patt3.png");
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_TFT_MONO;
		Display_pattern_CAN (PATTERN_LCD_3, berco);
		
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
	while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	 
	///////////////////
	Sinc_test (berco);  
	///////////////////
		
		if(status_emergencia == ON)
		{
			while (status != CONT  && status != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);

			
		if(status == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
			
		parar_mensagem_auto = OFF;
		return res;
		

}

//
// Função: Verificacao_Padrao_Display_MONO_4()
//
double Verificacao_Padrao_Display_MONO_4(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco);
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		if(atualizar_painel)
		{
			strcpy(img_comp, "TFT_Mono_Patt4.png");
		
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_TFT_MONO;
		Display_pattern_CAN (PATTERN_LCD_4, berco);
		
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		while(STATUS.Continua || STATUS.Rejeita)
				Delay_thread(.1);
	 
		///////////////////
		Sinc_test (berco);  
		///////////////////
		
		if(status_emergencia == ON)
		{
			while (status != CONT  && status != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	
			
		if(status == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
		
		parar_mensagem_auto = OFF; 
		return res;
		

}
//
// Função: Verificacao_Padrao_Display_COLOR()
//
double Verificacao_Padrao_Display_COLOR(int padrao, char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200] = {0},
	img_comp[200] = {0};

int 
	status = 0,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco);
		
//		if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
//				atualizar_painel = OFF;
		switch(padrao)
		{
			case PATTERN_LCD_ALL_OFF:
				strcpy(img_comp, "Disp_TFT_All_OFF.png");
				break;
			case PATTERN_LCD_ALL_ON:
				strcpy(img_comp, "TFT_All_ON.png");
				break;
			case PATTERN_LCD_3:
				strcpy(img_comp, "TFT_Color_Patt3.png");
				break;
			case PATTERN_LCD_4:
				strcpy(img_comp, "TFT_Color_Patt4.png");
				break;
			case PATTERN_LCD_RED:
				strcpy(img_comp, "TFT_Color_red.png");
				break;
			case PATTERN_LCD_GREEN:
				strcpy(img_comp, "TFT_Color_green.png");
				break;
			case PATTERN_LCD_BLUE:
				strcpy(img_comp, "TFT_Color_blue.png");
				break;
			case PATTERN_LCD_GRAY_LEVEL:
				strcpy(img_comp, "TFT_Color_Gray_level.png");
				break;
			case PATTERN_LCD_COLOUR_BARS:
				strcpy(img_comp, "TFT_Color_ColourBars.png");
				break;
			default:
				strcpy(img_comp, "Disp_TFT_All_OFF.png");
				break;
		}
		if(atualizar_painel)
		{
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verifique o padrão do display");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);  
		}
		modelo_display[berco] = DISPLAY_TFT_COLOR;
		status = Display_pattern_CAN (padrao, berco);
		if(status != SUCESSO)
			return -1;
		Delay_thread(0.1);
	
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		
		if(status_emergencia == ON)
		{
			while (status != CONT  && status != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
	
			
		if(status == CONT)
		{
			res =1; //pass
		}
		dados_berco[berco].rejeita_montagem = OFF;
		
		parar_mensagem_auto = OFF;    
return res;
}

/************************* VerificaNumSerie_NVM() ****************************************************/
// Função: VerificaNumSerie_NVM()
double VerificaNumSerie_NVM(char * mens_falha, int berco)
{
int valor=0,
	status,
	i,
	atualizar_painel = ON;
double
	res = 0;
char
	serial_lido_nvm[20]		={0},
	serial_lido_etiquet[20]	={0},
	tmp[10]			={0};
		
		 
		if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
				atualizar_painel = OFF;
		
		CopyString (serial_lido_etiquet, 0, dados_berco[berco].N_Serie_EndItem, (TAMANHO_BARCODE_ENDITEM-TAMANHO_NUM_SERIE_MTC), TAMANHO_NUM_SERIE_MTC);
		if(strlen(serial_lido_etiquet) != TAMANHO_NUM_SERIE_MTC)
			return -1;
		status = Ler_Registro_status(MTC_STATUS, &valor, berco);
		if(status == SUCESSO)
		{
			for(i=7; i<16; i++)
				serial_lido_nvm[i-7] =  bytes_resp_CAN_diag[i][berco];
			serial_lido_nvm[10] = 0;
		}
		res = 0;
		if(strstr(dados_berco[berco].N_Serie_EndItem, serial_lido_nvm) != NULL && (strlen(serial_lido_nvm) == TAMANHO_NUM_SERIE_MTC))
			res = 1;
		Delay_thread(0.1);
	
return res;
		
}

// Função: Entrar_Diag_Mode_Visteon()
//
double Entrar_Diag_Mode_Visteon(char * mens_falha, int berco)
{
char 
	i_s [40] = {0},
	mens1[40] = {0}, 
	Mens[40] = {0};
double 
	timeout=2,
	t=0;
int 
	i = 0,
	modo_diag = 0;
	
double
	res = 0;
	
			qual_diag_atual[berco] 	= NOT_DIAG;
			modo_diagnostico[berco] 	= ENTRAR_DIAG_VISTEON;
			
			t=Timer(); 
			while(modo_diagnostico[berco] != MANTER_DIAG && Timer()-t<timeout)
				Delay_thread(0.01);
			
			ResetManual_Controls(OFF, berco);
			if(modo_diagnostico[berco] == MANTER_DIAG)
			{
				qual_diag_atual[berco] = EM_DIAG_VISTEON;
				res = 1;
			}
			
	return res;

}



//
// Função: Sair_Diag_Mode_Visteon()
//
double Sair_Diag_Mode_Visteon(char * mens_falha, int berco)
{
char 
	mens1[40] = {0}; 

double 
	timeout=2,
	t=0;
int 
	i = 0,
	modo_diag = 0;
	
double
	res = 1;
	

	dados_berco[berco].cor_mensagens = MENS_AZUL;
	strcpy(dados_berco[berco].mens_montagem_2, "Cluster Saindo de");
	strcpy(dados_berco[berco].mens_montagem_3, "Modo Diagnóstico Visteon");
	modo_diagnostico[berco] = NOT_DIAG;
	qual_diag_atual[berco]  = NOT_DIAG;
	Delay_thread(0.1);

	
	return res;

}



//
// Função: Entrar_Diag_Mode_costumer()
//
double Entrar_Diag_Mode_costumer(char * mens_falha, int berco)
{
char 
	i_s [40] = {0},
	mens1[40] = {0}; 

double 
	timeout=2,
	t=0;
int 
	i = 0;

	
double
	res = 0;
	
		HidePanel (painel_padrao); 
		ECU_reset_Diag(berco);
		
		parar_mensagem_auto = ON;
		//waiting product start  	
		for (i=1; i<=10; i++)
		{	
		    Fmt(i_s,"%s<%i" ,i);
  
			strcpy(mens1,"> Aguarde ... ");  
			strcat (mens1, i_s);

			Mensagem(mens1, "", "","", MENS_AZUL, berco); 
		    Delay_thread(1);
		}
		strcpy(mens1,""); 
		parar_mensagem_auto = OFF;
		
		qual_diag_atual[berco] 	= NOT_DIAG;
		modo_diagnostico[berco] = ENTRAR_DIAG_CUSTOMER;
		
		t=Timer(); 
		while(modo_diagnostico[berco] != MANTER_DIAG && Timer()-t<timeout)
			Delay_thread(0.01);
		
		ResetManual_Controls(OFF, berco);
		if(modo_diagnostico[berco] == MANTER_DIAG && qual_diag_atual[berco] == EM_DIAG_CUSTOMER)
		{
			res = 1;
		}
		else
			res = 0;
		
return res;

}

//
// Função: Sair_Diag_Mode_costumer()
//
double Sair_Diag_Mode_costumer(char * mens_falha, int berco)
{
	double
		res = 1;

	dados_berco[berco].cor_mensagens = MENS_AZUL;
	strcpy(dados_berco[berco].mens_montagem_2, "Cluster Saindo de");
	strcpy(dados_berco[berco].mens_montagem_3, "Modo Diagnóstico costumer");
	modo_diagnostico[berco] = NOT_DIAG;
	qual_diag_atual[berco]  = NOT_DIAG;
	Delay_thread(0.01);
	return res;

}




//
// Função: Ligar_Vibracao()
//
double Ligar_Vibracao(char * mens_falha, int berco)
{
	double
		res = 1;

		
		
	SAIDA.ContatoraVibracao = ON;
	Delay_thread(.1);
	
	
	return res;

}

//
// Função: Deligar_Vibracao()
//
double Deligar_Vibracao(char * mens_falha, int berco)
{
	double
		res = 1;

	HidePanel (painel_padrao); 
	SAIDA.ContatoraVibracao = OFF;
	Delay_thread(.1);
	return res;

}

//
// Função: Abrir_Porta()
//
double Abrir_Porta(char * mens_falha, int berco)
{
	double
		res = 0;

	int st;	

	dados_berco[berco].cor_mensagens = MENS_AZUL;
	
	if (usar_porta==OFF) 
	{
		strcpy(dados_berco[berco].mens_montagem_2, "OPCIONALMENTE ABRA A PORTA");
		Delay_thread(1);
		strcpy(dados_berco[berco].mens_montagem_2, ""); 
		res = 1;
		return res;
	}
	
	modo_thread = ESCRITA_E_LEITURA;
	Delay_thread(0.1);

	strcpy(dados_berco[berco].mens_montagem_2, "ABRA A PORTA");
	
	
	motions_clear_to_move=ON;
	Trava(OFF);
	motions_clear_to_move=OFF;

	
	do
	{
		Delay_thread(.1);  
	}while(STATUS.Porta_Fechada == ON && status_emergencia == ON && sair_programa == OFF);
	strcpy(dados_berco[berco].mens_montagem_2, ""); 	 

		 
	if (st==0)
	{	 
		 res=1;
		 	
	}
	else
	{
		 res=0;
		 SAIDA.TravaPorta = OFF; 
	}
	return res;
}




//
// Função: Fechar_Porta()
//
double Fechar_Porta(char * mens_falha, int berco)
{
	double
		res = 1;

	int st;	
	

	dados_berco[berco].cor_mensagens = MENS_AZUL;
	
	if (usar_porta==OFF) 
	{
		strcpy(dados_berco[berco].mens_montagem_2, "OPCIONALMENTE FECHE A PORTA");
		Delay_thread(1);
		strcpy(dados_berco[berco].mens_montagem_2, "");  
		res = 1;
		return res;
	}
	
	modo_thread = ESCRITA_E_LEITURA;
	Delay_thread(0.1);

	strcpy(dados_berco[berco].mens_montagem_2, "FECHE A PORTA");
	do
	{
		Delay_thread(.1);  
		
	}while(STATUS.Porta_Fechada == OFF && status_emergencia == ON && sair_programa == OFF);
	strcpy(dados_berco[berco].mens_montagem_2, ""); 	 

	motions_clear_to_move=ON;
	st=Trava(ON);
	motions_clear_to_move=OFF;
		 
	if (st==0)
	{	 
		 res=1;
		 	
	}
	else
	{
		 res=0;
		 SAIDA.TravaPorta = OFF; 
	}
	 
	return res;
	
}


/******************************* Inicializa_LedsSaidas() ***********************************************************************/
void Inicializa_LedsSaidas(int berco)
{
	diag_telltales[berco].tt_airbag 			= VAL_TT_AIRBAG_OFF		;
	diag_telltales[berco].tt_battery 			= VAL_TT_BATTERY_OFF	;
	diag_telltales[berco].tt_park_brake 		= VAL_TT_PARKBRAKE_OFF	;
	diag_telltales[berco].tt_coolant_temp 		= VAL_TT_COOLANT_TEMP_OFF;
	diag_telltales[berco].tt_oil_pressure 		= VAL_TT_OIL_PRESSURE_OFF;
	diag_telltales[berco].tt_seat_belt 			= VAL_TT_SEATBELT_OFF	;
	diag_telltales[berco].tt_parking_brake 		= VAL_TT_PARKING_BRAKE_OFF;
	diag_telltales[berco].tt_passeng_seatbelt 	= VAL_TT_PASSEN_SEATBELT_OFF;
	diag_telltales[berco].tt_cruise_engaged 	= VAL_TT_CRUISE_ENGAGED_OFF;
	diag_telltales[berco].tt_front_fog 			= VAL_TT_FRONT_FOG_OFF	;					 
	diag_telltales[berco].tt_light_on 			= VAL_TT_LIGHTON_OFF	;
	diag_telltales[berco].tt_turn_left 			= VAL_TT_TURN_LEFT_OFF	;
	diag_telltales[berco].tt_turn_right 		= VAL_TT_TURN_RIGHT_OFF	;
	diag_telltales[berco].tt_lane_kepper_green 	= VAL_TT_LANE_KEEP_GREEN_OFF;
	diag_telltales[berco].tt_track_lead_green 	= VAL_TT_TRACK_LEAD_GREEN_OFF;
	diag_telltales[berco].tt_auto_hold_green 	= VAL_TT_AUTOHOLD_GREEN_OFF;
	diag_telltales[berco].tt_abs 				= VAL_TT_ABS_OFF		;
	diag_telltales[berco].tt_se_parkbrake 		= VAL_TT_SE_PARKBREAK_OFF;
	diag_telltales[berco].tt_fuel_level_low 	= VAL_TT_FUEL_LV_LOW_OFF;					 
	diag_telltales[berco].tt_rear_fog 			= VAL_TT_REAR_FOG_OFF	;
	diag_telltales[berco].tt_security 			= VAL_TT_SECURITY_OFF	;
	diag_telltales[berco].tt_serv_eng_soon 		= VAL_TT_SERV_ENG_SOON_OFF;
	diag_telltales[berco].tt_tire_press_low 	= VAL_TT_TIRE_PRESS_LOW_OFF;
	diag_telltales[berco].tt_esc_off 			= VAL_TT_ESCOFF_OFF		;
	diag_telltales[berco].tt_esc_service 		= VAL_TT_ESC_SERVICE_OFF;
	diag_telltales[berco].tt_press_clutch 		= VAL_TT_PRESS_CLUTCH_OFF;
	diag_telltales[berco].tt_traction_cntrl_off	= VAL_TT_TRACTION_CONTRL_OFF;
	diag_telltales[berco].tt_service_vehi_soon 	= VAL_TT_SERV_VEH_SOON_OFF;
	diag_telltales[berco].tt_eps 				= VAL_TT_EPS_OFF		;
	diag_telltales[berco].tt_park_assist 		= VAL_TT_PARK_ASSIST_OFF;
	diag_telltales[berco].tt_glow_plug 			= VAL_TT_GLOWPLUG_OFF	;
	diag_telltales[berco].tt_pedestrian 		= VAL_TT_PEDESTRIAN_OFF	;
	diag_telltales[berco].tt_lane_kepper_amber 	= VAL_TT_LANE_KEEP_AMBER_OFF;
	diag_telltales[berco].tt_track_lead_amber 	= VAL_TT_TRACK_LEAD_AMBER_OFF;
	diag_telltales[berco].tt_kmh 				= VAL_TT_KMH_OFF		;
	diag_telltales[berco].tt_mph 				= VAL_TT_MPH_OFF		;
	diag_telltales[berco].tt_auto_hold_white 	= VAL_TT_AUTOHOLD_WHITE_OFF;
	diag_telltales[berco].tt_high_beam 			= VAL_TT_HIGH_BEAM_OFF	;
	
	diag_output[berco].out_fca 				= OFF;
	diag_output[berco].out_fca_dn 			= OFF;
	diag_output[berco].out_passiv_start_run = OFF;
	diag_output[berco].out_passiv_start_acc = OFF;
}




/*/////////////////////////////////////////////////////////////////////////////////////////////
Test Name			:Tensão CAN Bus

Test Description	: 

						   Lower Limit		Upper Limit		  Units:
Tensão CAN Bus HImáx			3.3				4.3				V
Tensão CAN Bus HImin			2				2.7				V
Tensão CAN Bus LOmáx			2.2				2.8				V
Tensão CAN Bus LOmin			0.9				1.5				V  
/////////////////////////////////////////////////////////////////////////////////////////////*/
double	TensaoCAN (MODO_TENSAO_CAN modo_tensao_can, int berco)
{
double
	time_out = 10,
	res =0, 
	t   = 0,
	t2  = 0,
	*leituras,
	val_min = -999;
static double
	val_max = -999;
int canal = 6, 
	ler_daq = 0, 
	status  = 0,
	tent    = 0,
	leit_daq_por_seg = 40000,
	index_max = 0,
	index_min = 0;
	
size_t  
	length			 = 2000 ;
	
	if( atualizar_mens_can[berco] 	== OFF)
	{
		atualizar_mens_can[berco] 	= ON;
		Delay_thread(0.1);
	}
	leituras     	= (double *)malloc(sizeof(double)*(length+1) ) ;
	
	if (berco == BERCO_1)
	{
		switch(modo_tensao_can)
		{
			case CAN_HI_MIN:
				canal = 2;
				break;
			case CAN_HI_MAX:
				canal = 2;
				if(dados_berco[berco].retestar == OFF && (val_max >=  Teste[berco][dados_berco[berco].num_teste].LimBaixo && val_max <= Teste[berco][dados_berco[berco].num_teste].LimAlto))
					return val_max;
				
				break;
			case CAN_LO_MIN:
				canal = 10;
				break;
			case CAN_LO_MAX:
				canal = 10; 
				if(dados_berco[berco].retestar == OFF && (val_max >=  Teste[berco][dados_berco[berco].num_teste].LimBaixo && val_max <= Teste[berco][dados_berco[berco].num_teste].LimAlto))
					return val_max;
			
				break;
		}
	}

	if (berco == BERCO_2)
	{
		switch(modo_tensao_can)
		{
			case CAN_HI_MIN:
				canal = 3;
				break;
			case CAN_HI_MAX:
				canal = 3;
				if(dados_berco[berco].retestar == OFF && (val_max >=  Teste[berco][dados_berco[berco].num_teste].LimBaixo && val_max <= Teste[berco][dados_berco[berco].num_teste].LimAlto))
					return val_max;
				break;
			case CAN_LO_MIN:
				canal = 11;
				break;
			case CAN_LO_MAX:
				canal = 11;    
				if(dados_berco[berco].retestar == OFF && (val_max >=  Teste[berco][dados_berco[berco].num_teste].LimBaixo && val_max <= Teste[berco][dados_berco[berco].num_teste].LimAlto))
					return val_max;
				break;
		}
	}
	
retent:

	
	/////////////////////////////////////////
	DAQ_manager(berco);		
	/////////////////////////////////////////
	
	if(FormaOnda_NIdaq_6210_1ch (-5 , 5, canal, leit_daq_por_seg, length, leituras, berco) < 0)
	{
		dados_berco[berco].medindo_tensao = OFF;  
		return -100;
	}

	Delay_thread(.1);
	
	MaxMin1D (leituras, length-1, &val_max, &index_max, &val_min, &index_min );
	switch(modo_tensao_can)
	{
		case CAN_HI_MIN:
			res = val_min;
			break;
			
		case CAN_LO_MIN:
			res = val_min;
			break;
		case CAN_HI_MAX:
			res = val_max;
			break;
			
		case CAN_LO_MAX:
			res = val_max;
			break;
	}
	
	if((res < Teste[berco][dados_berco[berco].num_teste].LimBaixo || res > Teste[berco][dados_berco[berco].num_teste].LimAlto) && tent <= 3)
	{
		tent++;
		goto retent;
	}
	
	////////////////////////////////////////
	dados_berco[berco].medindo_tensao = OFF;
	////////////////////////////////////////
	
	return res;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////
//05/02/2018 
//inversão de posição TFCP / VISION 

/*--------------------------------------------------------------------------------------------------
          Configura cyber security
---------------------------------------------------------------------------------------------------*/
double ConfiguraCyberSecurity(char * mens_rejeito, int berco)
{
int 
	size,
	sair = OFF,
	handle_iecs,
	status = 0;
double
	res = FALHA;


		if(dados_berco[berco].cyber_sec_ativo == ON)
			return 2;  //Sinaliza que o cluster já estava gravado
		strcpy(dados_berco[berco].mens_montagem_2, "Configurando o cyber security");
		strcpy(dados_berco[berco].mens_montagem_3, " ");
		
		ProcessSystemEvents ();
		
		if(!dados_berco[berco].retestar)
		{
			status = LerIndexar_arq_index_LiveKey(OFF, berco);
			if(status != SUCESSO)
			{
				strcpy(mens_rejeito, "Erro para obter o index das keys");
				goto Error;
			}
		}
		status = LeDados_ASC_LiveKey( atual_index_live_key[berco], berco);
		if(status != SUCESSO)
		{
			Fmt(mens_rejeito, "%s%s%i", "Erro na leitura do live key: ", "status = ", status);
			goto Error;
		}
		status = Gravar_Master_Key(berco);
		if(status == SUCESSO)
		{
			status = Gravar_Unlock_Key(berco);
			if(status == SUCESSO)
			{
				status = GravaSequencia_general_keys(berco);
				if(status == SUCESSO)
				{
					res = 1;
				}
				else
				{
					Fmt(mens_rejeito, "%s%s%i", "Erro na gravação do general key: ", "status = ", status);
					goto Error;
				}
			}
			else
			{
				Fmt(mens_rejeito,"%s%s%i", "Erro na gravação do unlock key: ", "status = ", status);
				goto Error;
			}
		}
		else
		{
			Fmt(mens_rejeito,"%s%s%i", "Erro na gravação do master key: ", "status = ", status);
			goto Error;
		}
		modo_thread = ESCRITA_E_LEITURA;
		ProcessSystemEvents ();
return res;
Error:
		modo_thread = ESCRITA_E_LEITURA;
		ProcessSystemEvents ();
return FALHA;
}



/*--------------------------------------------------------------------------------------------------
                  Grava o ECU ID
---------------------------------------------------------------------------------------------------*/
double Grava_ECU_ID(char * mens_rejeito, int berco)
{
int 
	mes,
	dia,
	ano,
	hh,
	mm,
	ss,
	size,
	sair = OFF,
	handle_iecs,
	status = 0;
double
	res = FALHA,
	time_out = 4.0,
	t;
char
	path_m4_m5[MAX_PATHNAME_LEN],
	path_local[MAX_PATHNAME_LEN],
	path_local_out[MAX_PATHNAME_LEN],
	arq_local[MAX_PATHNAME_LEN],
	path_online[MAX_PATHNAME_LEN],
	path_tool[MAX_PATHNAME_LEN],
	aux[MAX_PATHNAME_LEN],
	*enc;
unsigned char
	out[100]={0};
	
HRESULT    error = S_OK;
DADOS_ECU_XML dados_ecu;

		strcpy(dados_berco[berco].mens_montagem_2, "Gravando o ECU ID");
		strcpy(dados_berco[berco].mens_montagem_3, " ");
		
		GetSystemDate ( &mes, &dia, &ano); 
		GetSystemTime ( &hh,  &mm,  &ss);
		/*------------------------------------------------------------------------------
		path M4 M5 = "..\\Live_Key\\M4_M5\\LiveKey_M4_M5__25-8-2018.txt"
		path local = "LocalKeyVerOutput-yyyy-mm-ddhh-mm-ss-<input_file_name>.xml"
		path online = "KeyVerOutput-<YYYY-MM-DDHH-MM-SS>-mkuk1_5.xml".
		-------------------------------------------------------------------------------*/
		//monta os nomes dos arquivos
		sprintf(path_online,"%sKeyVerOutput-%d-%d-%d-mkuk1_5.xml", PATH_LIVE_KEY, ano,mes,dia);
		sprintf(path_m4_m5,"%sLiveKey_M4_M5__%d-%d-%d.txt",        PATH_L_KEY_M4_M5, dia,mes,ano);
		//verifica se o arquivo m4_m5 existe
		status = GetFileInfo(path_m4_m5 , &size);
		if (status != 1)
		{
			if(dia>1 && dia<31)
			{
				dia -= 1;
				sprintf(path_m4_m5,"%sLiveKey_M4_M5__%d-%d-%d.txt", PATH_L_KEY_M4_M5, dia,mes,ano);
				status = GetFileInfo(path_m4_m5 , &size);
				if (status != 1)
				{
					Fmt(mens_rejeito,"%s<%s%s%s", "Arquivo m4 m5 ", path_m4_m5," não encontrado");
					goto Error;
				}
				dia++;
			}
		}
		// verifica se o live key foi gravado
		if(dados_berco[berco].cyber_sec_ativo == ON) 
		{
			status = CarregaECUIDArqLiveKey(path_m4_m5, &dados_ecu, dados_berco[berco].N_Serie_EndItem);
			if(status == 1)
			{   //recupera o ecuid gravado para este numero de serie
				strcpy(dados_live_key[berco].ecu_id, dados_ecu.ecuid);
			}
			else
			{
				Fmt (mens_rejeito,"%s<%s%s%s", "Serial ", dados_berco[berco].N_Serie_EndItem," não encontrado no diretorio M4 M5");
				goto Error;
			}
		}
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando o ECU ID no arquivo");
		//grava o ecu id
		status = Gravar_ECU_ID(berco);
		if(status == SUCESSO)
		{
			res = 1;
		}
		else
		{
			Fmt(mens_rejeito,"%s%s%i", "Erro na gravação do ECU ID: ", "status = ", status);
			goto Error;
		}
		strcpy(dados_berco[berco].mens_montagem_2, "Convertendo os dados para base 64");
		if(res == 1)
		{   //codifica para base 64
			//não converte o numero de serie
			strcpy(dados_ecu.serial, dados_berco[berco].N_Serie_EndItem); 
			//converte dois ascii to byte
			status = twoASCIItoByte(dados_live_key[berco].master_key_1, out);
			enc = b64_encode(out, 16);
			strcpy(dados_ecu.mkm1, enc);
			//converte dois ascii to byte
			strcpy(aux, dados_live_key[berco].master_key_2);
			strcat(aux, dados_live_key[berco].master_key_3);
			status = twoASCIItoByte(aux, out);
			enc = b64_encode(out, 32);
			strcpy(dados_ecu.mkm2, enc);
			//converte dois ascii to byte
			status = twoASCIItoByte(dados_live_key[berco].master_key_4, out);
			enc = b64_encode(out, 16);
			strcpy(dados_ecu.mkm3, enc);
			//converte dois ascii to byte
			status = twoASCIItoByte(dados_live_key[berco].unlock_key_1, out);
			enc = b64_encode(out, 16);
			strcpy(dados_ecu.ukm1, enc);
			//converte dois ascii to byte
			strcpy(aux, dados_live_key[berco].unlock_key_2);
			strcat(aux, dados_live_key[berco].unlock_key_3);
			status = twoASCIItoByte(aux, out);
			enc = b64_encode(out, 32);
			strcpy(dados_ecu.ukm2, enc);
			//converte dois ascii to byte
			status = twoASCIItoByte(dados_live_key[berco].unlock_key_4, out);
			enc = b64_encode(out, 16);
			strcpy(dados_ecu.ukm3, enc);
			if(berco == 1)
				sprintf(path_local_out,"%s%s.xml",PATH_L_KEY_LOCAL_1, dados_live_key[berco].ecu_id);
			else
				sprintf(path_local_out,"%s%s.xml",PATH_L_KEY_LOCAL_2, dados_live_key[berco].ecu_id);
			sprintf(arq_local,"%s.xml",dados_live_key[berco].ecu_id);
			status = CarregaArqLiveKey(path_m4_m5, &dados_ecu, dados_live_key[berco].ecu_id);
			if(status == 1)
			{   //codifica para base 64
				//converte dois ascii to byte
				status = twoASCIItoByte(dados_live_key[berco].ecu_id, out);
				enc = b64_encode(out, 16);
				strcpy(dados_ecu.ecuid, enc);
				//converte dois ascii to byte
				status = twoASCIItoByte(dados_ecu.mkm4, out);
				enc = b64_encode(out, 32);
				strcpy(dados_ecu.mkm4, enc);
				//converte dois ascii to byte
				status = twoASCIItoByte(dados_ecu.mkm5, out);
				enc = b64_encode(out, 16);
				strcpy(dados_ecu.mkm5, enc);
				//converte dois ascii to byte
				status = twoASCIItoByte(dados_ecu.ukm4, out);
				enc = b64_encode(out, 32);
				strcpy(dados_ecu.ukm4, enc);
				//converte dois ascii to byte
				status = twoASCIItoByte(dados_ecu.ukm5, out);
				enc = b64_encode(out, 16);
				strcpy(dados_ecu.ukm5, enc);
				//salva no formato xml para verificação local
				hrChk (SaveEcuRecord(path_local_out, TABULAR_ON, SAVE_CHECK_LOCAL, dados_ecu));
				res = 1;
			}
			else
			{
				Fmt (mens_rejeito,"%s<%s%s%s", "Ecu ID ",dados_live_key[berco].ecu_id," não encontrado no diretorio M4_M5");
				goto Error;
			}
			//faz a validação local das chaves
			//comando:"java -jar %sIecsM4M5Local.jar %s" path_local_out
			if(berco == 1)
				sprintf(path_tool,"%sLocal_verification.bat %s",PATH_L_KEY_LOCAL_1, arq_local);
			else
				sprintf(path_tool,"%sLocal_verification.bat %s",PATH_L_KEY_LOCAL_2, arq_local);
			status = LaunchExecutableEx (path_tool, LE_SHOWMINIMIZED, &handle_iecs);
			
			sair = OFF;
			t = Timer();
			while(sair == OFF && Timer() - t < time_out)
			{
				if(berco == 1)
					status = GetFirstFile (PATH_L_KEY_LOCAL_1"LocalKeyVerOutput*.xml", 1, 0, 0, 0, 0, 0, aux);
				else
					status = GetFirstFile (PATH_L_KEY_LOCAL_2"LocalKeyVerOutput*.xml", 1, 0, 0, 0, 0, 0, aux);
				if(status == SUCESSO)
					sair = ON;
			}
			if(sair == OFF)
				goto Error;
			
			//espera o arquivo ser gerado e procura o arquivo de saida da verificação local
			cont = 0;
			sair = OFF;
			if(berco == 1)
				status = GetFirstFile (PATH_L_KEY_LOCAL_1"*.xml", 1, 0, 0, 0, 0, 0, aux);
			else
				status = GetFirstFile (PATH_L_KEY_LOCAL_2"*.xml", 1, 0, 0, 0, 0, 0, aux);
			if(status == SUCESSO)
			{
				while(cont<200 && sair == OFF && status == 0)
				{
					if(strstr(aux,dados_live_key[berco].ecu_id) != NULL)
					{
						if(strstr(aux,"LocalKeyVerOutput") != NULL)
						{
							if(berco == 1)
								strcpy(path_local, PATH_L_KEY_LOCAL_1);
							else
								strcpy(path_local, PATH_L_KEY_LOCAL_2);
							strcat(path_local, aux);
							sair = ON;
						}
					}
					status = GetNextFile (aux);
					cont++;
				}
			}
			if(sair != ON)
			{
				Fmt (mens_rejeito,"%s<%s%s%s", "Arquivo LocalKeyVerOutput ",dados_live_key[berco].ecu_id, " não encontrado");
				goto Error;
			}
			Delay_thread(0.05);
			hrChk (GetResultXMLRecord(path_local, "", &dados_ecu));
			if(dados_ecu.mkValid == ON && dados_ecu.ukValid == ON)
			{   //salva os keys para verificação online
				hrChk (SaveEcuRecord(path_online, TABULAR_ON, SAVE_CHECK_ONLINE, dados_ecu));
				res = 1;
				if(berco == 1)
					DeleteFile (PATH_L_KEY_LOCAL_1"LocalKeyVerOutput*.*");
				else
					DeleteFile (PATH_L_KEY_LOCAL_2"LocalKeyVerOutput*.*");
				
				DeleteFile (path_local);
			}
			else
			{
				strcpy (mens_rejeito, "Verificação local das Key falhou");
				res = FALHA;
			}
		}
		ProcessSystemEvents ();
return res;
Error:
		ProcessSystemEvents ();
return FALHA;
}


/******************************* Ver_CyberSecurity_Ativado ******************************************/  
double Ver_CyberSecurity_Ativado (char * mens_rejeito, int berco)
{

		strcpy(dados_berco[berco].mens_montagem_2,"Lendo status do Live Key...");
		dados_berco[berco].cyber_sec_ativo = OFF;
		dados_berco[berco].cyber_sec_ativo = LerStatus_LiveKey(berco);
	    Delay_thread(0.001);
return dados_berco[berco].cyber_sec_ativo;
}


/******************************* LerSoftwareVersion ******************************************/  
double LerSoftwareVersion (char * mens_rejeito, int berco)
{
int 
	cmp,
	status,
	result,
	tent = 0;
double
	res = 0;
char 
	version [10]={0},
	version_level [10]={0};	

		
		strcpy(dados_berco[berco].mens_montagem_2,"Lendo versão do sw");
	    Delay_thread(0.1);
		dados_berco[berco].solicitando_vision = ON;

retent:
		status = Ler_Registro_status(CLUSTER_INFO, &result, berco);
		if(status == SUCESSO)
		{
			status = sprintf(version_level, "%06x", result);
			if(status<0)
			{
				Fmt(mens_rejeito, "%s<%s", "Erro na formatação da versão");
				return FALHA;
			}
			
			StringUpperCase (version_level);
			status = SUCESSO;
		}
		if(strcmp(version_level, dados_berco[berco].sw_version) == 0 && strlen(version_level) > 3 && status == SUCESSO)
		{
			res = 1;
		}
		else 
		{
			if(tent < 3)
			{
				Delay_thread(0.050);
				tent++;
				goto retent;
			}
			Fmt(mens_rejeito, "%s<%s%s%s%s", " versão sw = ", dados_berco[berco].sw_version, " Lido = ", version_level);
		}
return res;
}



/*-----------------------------------------------------------------------------------------
				Verificaa o pn cliente
-----------------------------------------------------------------------------------------*/
double VerificaClientePN(char * mens_rejeito, int berco)
{
int
	status=0,
	tent = 0,
	byte,
	dado_byte;
double
	res = 1;
unsigned char
	aux[20] = {0},
	r_pn_cliente[20] = {0};
	

		strcpy(mens_rejeito,"");
		///SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Verificando o part number cliente");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");

reteste:
		status = Ler_Registro_status(PN_STATUS, &byte, berco);
		if(status == SUCESSO)
		{
			Fmt(aux, "%s<%i", byte);
			StringUpperCase (aux);
			strcpy(r_pn_cliente, aux);
		}
		else
		{
			res = FALHA;
			strcpy(mens_rejeito,"Erro na leitura do pn cliente");
			goto Error;
		}
		if(strcmp (dados_berco[berco].ref_GM, r_pn_cliente) == 0)
		{
			res = 1;
		}
		else
		{
			tent++;
			if(tent<2)
			{ 
				goto reteste ;
			}
			else
			{
				res = FALHA;
				Fmt(mens_rejeito, "%s<%s%s%s%s", " Escrito cliente pn = ", dados_berco[berco].costumer_pn, " Lido = ", r_pn_cliente);
				goto Error;
			}
		}
	
Error:
return res;
	
}
/*-----------------------------------------------------------------------------------------
				Verifica o valor do MEC - numero de resets do cluster
-----------------------------------------------------------------------------------------*/
double VerificaMEC(char * mens_rejeito, int berco)
{
int
	status=0,
	byte,
	dado_byte;
double
	res = 1;
unsigned char
	aux[20] = {0};
	

		strcpy(mens_rejeito,"");
		///SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Verificando o valor MEC");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");

		status = Ler_Registro_status(MEC_STATUS, &byte, berco);
		if(status == SUCESSO)
		{
			if(byte < 0x10)
				Fmt(aux, "%s<0%x", byte);
			else
				Fmt(aux, "%s<%x" , byte);
			StringUpperCase (aux);
		}
		else
		{
			res = FALHA;
			strcpy(mens_rejeito,"Erro na leitura do valor MEC");
			goto Error;
		}
		if(byte > 0x00 || byte < 0xFF)
		{
			res = byte;
		}
		else
		{
			res = FALHA;
			Fmt(mens_rejeito, "%s<%s%s%s%s", " Escrito MEC = ", "0xFE", " Lido = ", aux);
			goto Error;
		}
	
Error:
return res;
	
}
  /* Função para verificação dos parafusos */
    double VerificaParafuso(char * mens_rejeito)
{
int
	/* Variáveis para duas novas posições de parafusos */
	res_sup_mid = 0,
	res_inf_mid = 0,

	res_sup_esq = 0,
	res_sup_dir = 0,
    res_inf_esq = 0,
	res_inf_dir = 0,
	status = 0,
	tent = 0,
	max_tent = 3;
unsigned char
	board_serial[25] = {0},
	sulfixo_serial[25] = {0},
	prefixo_serial[25] = {0},
	r_board_serial[25] = {0};
	
double
	res = 0;
	

	

		strcpy(mens_rejeito,"");
		strcpy(mens_montagem_2, "Verificando a presen?as das travas esquerda e direita");
		strcpy(mens_montagem_3,   " ");
reteste:
		/* Condicionais para verificação na presença dos parafusos */
		/* 
		TO DO: Identificar as portas no cartão I/O, declara-las e atribui-las no Main.h
		TO DO: Adicionar nas condicionais, substituindo as variáveis placeholder.
		*/
		
		if (STATUS.TravaSupEsquerda) //OK
		{
		  	 res_sup_esq=1;
		}
		else
		{
				
			   Fmt(mens_rejeito, "%s<%s%s%s%s", "Falha ao verificar presen?a do parafuso Superior Esquerdo ", "", "", "");
		        res_sup_esq = 0;
		}
		
		if (STATUS.TravaSupDireita) //OK
		{
		  	 	res_sup_dir=1;
		}
		else
		{
				
			   Fmt(mens_rejeito, "%s<%s%s%s%s", "Falha ao verificar presen?a do parafuso Superior Direito ", "", "", "");
		        	res_sup_dir = 0;
		}
		if (STATUS.TravaInfEsquerda) //OK
		{
		  	 res_inf_esq=1;
		}
		else
		{
				
			   Fmt(mens_rejeito, "%s<%s%s%s%s", "Falha ao verificar presen?a do parafuso Inferior Esquerdo ", "", "", "");
		        res_inf_esq = 0;
		}
		
		if (STATUS.TravaInfDireita) //OK
		{
		  	 	res_inf_dir=1;
		}
		else
		{
				
			   Fmt(mens_rejeito, "%s<%s%s%s%s", "Falha ao verificar presen?a do parafuso Inferior Direita ", "", "", "");
		        	res_inf_dir = 0;
		}
		
		
	   if (res_sup_esq==1 && res_sup_dir==1 && res_inf_esq==1 && res_inf_dir==1 && res_sup_mid==1 & res_inf_mid==1){
	      res=1; 
	   }
	   else
	   {
		  res=-101; 
	   }
	
		
	

		if(((res > Teste[teste].LimAlto) || (res < Teste[teste].LimBaixo)) && tent <= max_tent)
		{
			tent++;
			Delay_thread(0.05);
			goto reteste;
		}
		
return res;
		
}
  /* -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */


/*-----------------------------------------------------------------------------------------
				Verifica o part number base
-----------------------------------------------------------------------------------------*/
double VerificaBasePartNumber(char * mens_rejeito, int berco)
{
	int
	status=0,
	byte;

	double
	res = 1;
	unsigned char
	aux[20] = {0},
			  r_pn_base[20] = {0};


	strcpy(mens_rejeito,"");
	///SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
	COR_MENSAGENS= MENS_AZUL;
	strcpy(dados_berco[berco].mens_montagem_2, "Verificando o base part number");
	strcpy(dados_berco[berco].mens_montagem_3,   " ");

	//part number base somente leitura
	status = Ler_Registro_status(BASE_STATUS, &byte, berco);
	if(status == SUCESSO)
	{
		if(byte < 0x10)
			Fmt(aux, "0%i", byte);
		else
			Fmt(aux, "%i" , byte);
		StringUpperCase (aux);
		strcpy(r_pn_base, aux);
	}
	else
	{
		res = FALHA;
		strcpy(mens_rejeito,"Erro na leitura do part number base");
		goto Error;
	}
	if(strcmp (dados_berco[berco].ecu_hardware_number, r_pn_base) == 0)
	{
		res = 1;
	}
	else
	{
		res = FALHA;
		Fmt(mens_rejeito, "%s<%s%s%s%s", " Escrito part number base = ", dados_berco[berco].ecu_hardware_number, " Lido = ", r_pn_base);
		goto Error;
	}

Error:
	return res;

}


/*-----------------------------------------------------------------------------------------
				Grava MEC com 0xFE
-----------------------------------------------------------------------------------------*/
double GravaMEC(char * mens_rejeito, int berco)
{
int
	status=0,
	tent = 0;
double
	res = 1;
	
		//////////////////////////////////////////
		/*if(dados_berco[berco].tipo_service != OFF)
		{
			strcpy(mens_rejeito,"Erro no cadastro do tipo de SERVIÇO");
			return -100;
		}*/
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		
		strcpy(mens_rejeito,"");
		//SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando o MEC-Não Serviço");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
reteste:
		//MEC
		status = Programar_MEC_Diag(berco);
		if(status != SUCESSO)
		{
			tent++;
			if(tent<2)
			{ 
				goto reteste ;
			}
			else
			{
				res = -101;
				strcpy(mens_rejeito,"Erro na escrita do MEC-não Serviço");
				goto Error;
			}
		}
	
Error:
return res;
	
}

/*-----------------------------------------------------------------------------------------
				Grava MEC - SERVIÇO ->  0x00
-----------------------------------------------------------------------------------------*/
double GravaMEC_Service(char * mens_rejeito, int berco)
{
int
	status=0,
	tent = 0;
double
	res = 1;
	
		//////////////////////////////////////////
		if(dados_berco[berco].tipo_service == OFF)
		{
			strcpy(mens_rejeito,"Erro no cadastro do tipo de SERVIÇO");
			return -100;
		}
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		
		strcpy(mens_rejeito,"");
		//SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando o MEC - SERVIÇO");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
reteste:
		//MEC
		status = Programar_MEC_Servico_Diag(berco);
		if(status != SUCESSO)
		{
			tent++;
			if(tent<2)
			{ 
				goto reteste ;
			}
			else
			{
				res = -101;
				strcpy(mens_rejeito,"Erro na escrita do MEC-SERVIÇO");
				goto Error;
			}
		}
Error:
return res;
	
}

/*-----------------------------------------------------------------------------------------
				Configura o cluster
-----------------------------------------------------------------------------------------*/
double GravaClientePN(char * mens_rejeito, int berco)
{
int
	status=0,
	tent = 0,

	dado_byte;
double
	res = 1;
char
	*a;
	
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		

		strcpy(mens_rejeito,"");
		///SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando pn cliente");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		
reteste:
		//part number
		
		dado_byte = strtol(dados_berco[berco].ref_GM , &a, 10);  //costumer PN 
		
		status = Programar_PN_Diag(dado_byte, berco);
		if(status != SUCESSO)
		{
			tent++;
			if(tent<2)
			{ 
				goto reteste ;
			}
			else
			{
				res = FALHA;
				strcpy(mens_rejeito,"Erro na escrita do pn cliente");
				goto Error;
			}
		}
	
Error:
return res;
	
}


/*-----------------------------------------------------------------------------------------
				Grava o codigo de traceability
-----------------------------------------------------------------------------------------*/
double GravaTraceability(char * mens_rejeito, int berco)
{
int
	status=0,
	day,
	month,
	year,


	tent = 0,
	dado_manuf_date;

double
	res = 1;
unsigned char
	atualdate[10] = {0},
	aux[20] = {0},
	serial[12] = {0},

	*data;
	

		if (dados_berco[berco].retrabalho == ON)
			return 1;
	
	
		strcpy(mens_rejeito,"");
		///SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando traceability");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		Delay_thread(0.05) ;

		GetSystemDate (&month, &day, &year);
		data = DateStr ();
		
		dado_manuf_date = CalendarioDiadoAno();
		status = sprintf(atualdate, "%03i", dado_manuf_date);
		if(status < 0)
		{
			strcpy(mens_rejeito, "Erro na formatação da data");
			return FALHA;
		}
		
		CopyString(aux, 0, dados_berco[berco].N_Serie_EndItem, TAMANHO_PREFIXO_ENDITEM-3, -1);
		status = Fmt(serial, "%s", aux);
		if(status < 0)
		{
			strcpy(mens_rejeito, "Erro na formatação do número de série ");
			return FALHA;
		}
		
		envio_can[berco].dados_can[0] = 'G'; //celula
		envio_can[berco].dados_can[1] = 49 ;//shift
		envio_can[berco].dados_can[2] = data[8];//ano
		envio_can[berco].dados_can[3] = data[9];//ano
		envio_can[berco].dados_can[4] = atualdate[0];
		envio_can[berco].dados_can[5] = atualdate[1];
		envio_can[berco].dados_can[6] = atualdate[2];
		envio_can[berco].dados_can[7] = serial[0];
		envio_can[berco].dados_can[8] = serial[1];
		envio_can[berco].dados_can[9] = serial[2];
		envio_can[berco].dados_can[10] = serial[3];
		envio_can[berco].dados_can[11] = serial[4];
		envio_can[berco].dados_can[12] = serial[5];
		envio_can[berco].dados_can[13] = serial[6];
		envio_can[berco].dados_can[14] = serial[7];
		envio_can[berco].dados_can[15] = serial[8];
		
reteste:
		status = Programar_MTC_Diag(berco);
		if(status != SUCESSO)
		{
			tent++;
			if(tent<2)
			{ 
				goto reteste ;
			}
			else
			{
				res = FALHA;
				strcpy(mens_rejeito,"Erro na escrita do traceability");
				goto Error;
			}
		}
	
Error:
return res;
	
}


/*-----------------------------------------------------------------------------------------
				Grava o status byte aprovado ou rejeitado no cluster
-----------------------------------------------------------------------------------------*/
double GravaStatusByte(int condicao, char * mens_rejeito, int berco)
{
int
	status=0,
	tent = 0,

	status_byte = STATUS_OPER_REJEITO,

	r_status_byte = STATUS_OPER_REJEITO;

double
	res = 0;

	
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		
	
		if(dados_berco[berco].amostra_tipo != TESTE)
			  //return  Teste[berco][teste[berco]].LimBaixo;
			  return  Teste[berco][teste].LimBaixo;
		
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando Status Byte");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		Delay_thread(0.05) ;
reteste:		
		strcpy(mens_rejeito,"");
		if(dados_berco[berco].rejeitado || condicao == PRODUTO_REJEITADO)
		{
			status_byte = STATUS_OPER_REJEITO;
		}
		else 
		{
			status_byte = STATUS_OPER_APROVAD;
		}
		//status = GravaBytes(OP_ADD, OPERACAO_VISION, UM_BYTE);
		if(status < 0){
			res = FALHA;
			strcpy(mens_rejeito,"Erro na escrita");
			goto Error;
		}
		//status = GravaBytes(STATUS_ADD, status_byte, UM_BYTE);
		if(status < 0){
			res = FALHA;
			strcpy(mens_rejeito,"Erro na escrita");
			goto Error;
		}
		Delay_thread(0.2) ;
		//r_status_byte = LerByteNVM(STATUS_ADD);
		if(r_status_byte < 0){
			res = FALHA;
			strcpy(mens_rejeito,"Erro na leitura");
			goto Error;
		}
		if(status_byte == r_status_byte )
		{
			res = 1;
		}
		else
		{
			res = 0;
			strcpy(mens_rejeito,"Erro na gravação");
		}
		
Error:
		///if ((res > Teste[berco][teste[berco]].LimAlto) | (res < Teste[berco][teste[berco]].LimBaixo) && tent<2)
		if ((res > Teste[berco][teste].LimAlto) | (res < Teste[berco][teste].LimBaixo) && tent<2)
		{
			Delay_thread(0.5) ;
			//if(modo_diag)
			tent++;
			goto reteste;
		}
		if( condicao == PRODUTO_APROVADO)
		{
			//status=EnviaDadosBootCluster("F",  mens);
			//if(status!=COMM_SERIAL_SUCESSO)
			//		res = -1;
		}
return res;
		
}
/*-----------------------------------------------------------------------------------------
			Le o status byte aprovado ou rejeitado no cluster vindo da estação anterior
-----------------------------------------------------------------------------------------*/
double LeStatusByte(char * mens_rejeito, int berco)
{
int
	status = -1,
	manuf_device_number = 0,
	r_status_byte = 0,
	r_manuf_device_number = 0;
double
	res = 0;

		////////////////////////////////////////////
		if(dados_berco[berco].amostra_tipo != TESTE)
			  return  1;
		
		strcpy(mens_rejeito,"");
		strcpy(dados_berco[berco].mens_montagem_2, "lendo o status byte");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		Delay_thread(0.05) ;
		
		status =Ler_BytesNVM_Diag(add_traceability, 2, ON, berco);  
		if (status != SUCESSO)	
		{
			res = -100;
			strcpy(mens_rejeito,"Erro na leitura do status byte");
			goto Error;
		}
	
		r_manuf_device_number = bytes_resp_CAN_diag[0][berco]; //station
		r_status_byte         = bytes_resp_CAN_diag[1][berco]; //status
		Delay_thread(0.05) ;
	
		if (usar_runin == OFF)
		{	
			if( r_status_byte == STATUS_OPER_APROVAD && (r_manuf_device_number == OPERACAO_POINTER_PLACEM || r_manuf_device_number == OPERACAO_TFCP ))		
			{
				res = 1;
			}
			else if( r_status_byte == STATUS_OPER_REJEITO)		
			{
				res = -101;
				strcpy(mens_rejeito,"Não foi aprovado na estação anterior");
			}
		}
		else  //ON
		{
		/*	if (dados_berco[berco].retrabalho == ON )
			{
			   	if(r_manuf_device_number < 0x30 || r_manuf_device_number >= 0x5B || r_status_byte < 0x30 || r_status_byte >= 0x5B)
				{
					 strcpy(mens_rejeito,"Conflito da etiqueta com dados de traceability");
					 res = -102;
				}
				else
					res = 1;
			}  
			else   */
			{
				if( r_status_byte == STATUS_OPER_APROVAD && (r_manuf_device_number == OPERACAO_RUNIN || r_manuf_device_number == OPERACAO_TFCP ))		
				{
					res = 1;
				}
				else if( r_status_byte == STATUS_OPER_REJEITO)		
				{
					res = -103;
					strcpy(mens_rejeito,"Não foi aprovado na estação anterior");
				}
				else if (r_manuf_device_number > 0x30 && r_status_byte > 0x30 )
				{
					 res = 1;
				}
			}
	}	
		
Error:
return res;
		
}


/*-----------------------------------------------------------------------------------------
		Verifica se o numero de serie da placa do cluster esta igual a etiqueta
-----------------------------------------------------------------------------------------*/
double VerificaSNCluster(char * mens_rejeito, int berco)
{
int
	status = 0,
	tent = 0;
unsigned char
	board_serial[25] = {0},
	sulfixo_serial[25] = {0},
	prefixo_serial[25] = {0},
	r_board_serial[25] = {0};
	
double
	res = 0;

		CopyString (board_serial, 0, dados_berco[berco].N_Serie_EndItem, TAMANHO_PREFIXO_ENDITEM, -1);

		strcpy(mens_rejeito,"");
		SetCtrlAttribute (painel_tab[berco], GetCtrlArrayItem (ctrlarrayinfoteste[berco], 1), ATTR_CTRL_VAL, ""); // 1 mens_falha
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Verificando numero de serie da placa");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		Delay_thread(0.05) ;
reteste:
		
		Delay_thread(0.1) ;
		 //status = Read_SN_Board_Manuf (r_board_serial, add_cluster_sn_board);
		if(status != SUCESSO){
			res = -101;
			strcpy(mens_rejeito,"Erro na leitura");
			goto Error;
		}
		CopyString (sulfixo_serial, 0, r_board_serial, TAMANHO_PREFIXO_ENDITEM, -1);
		CopyString (prefixo_serial, 0, r_board_serial, 0, TAMANHO_PREFIXO_ENDITEM);
		if(strcmp( board_serial, sulfixo_serial) == 0)
		{
			if(strcmp( prefix_placa, prefixo_serial) == 0)
			{
				res = 1;
			}
			else
			{
				strcpy(mens_rejeito,"Erro na leitura do prefixo do numero de serie serie");
				res = -102;
				goto Error;
			}
		}
		else
		{
			strcpy(mens_rejeito,"Erro na leitura do sulfixo numero de serie");
			res = -103;
		}
Error:
		//if(((res > Teste[berco][teste[berco]].LimAlto) || (res < Teste[berco][teste[berco]].LimBaixo)) && tent < 2)
		if(((res > Teste[berco][teste].LimAlto) || (res < Teste[berco][teste].LimBaixo)) && tent < 2)
		{
			tent++;
			Delay_thread(0.05);
			goto reteste;
		}
		
return res;
		
}


////////////////////////////////////////////////////////////////////////////////////
//18/06/2019
double Grava_VPPS (char * mens_rejeito, int berco)
{
int
	status=0,
	max_tent = 3,
	tent = 0;
	

double
	res = 1;
char
	cluster_VPPS [30] = {0};

	
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		

		strcpy(mens_rejeito,"");
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando VPPS");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		
reteste:
		//get VVPS
		strcpy(cluster_VPPS,dados_berco[berco].vpps_code);
		status = F_write_VPPS(berco, &cluster_VPPS[0]); 
		
		if(status != SUCESSO)
		{
			tent++;
			if(tent<=max_tent)
			{ 
				Delay_thread(.1);
				goto reteste ;
			}
			else
			{
				res = FALHA;
				strcpy(mens_rejeito,"Erro na escrita do VPPS");
				goto Error;
			}
		}
	
Error:
return res;
	
}


double Grava_DUNS (char * mens_rejeito, int berco)
{
int
	status=0,
	max_tent = 3,  
	tent = 0;

double
	res = 1;
char
	cluster_DUNS [30] = {0};

	
		if (dados_berco[berco].retrabalho == ON)
			return 1;
		

		strcpy(mens_rejeito,"");
		COR_MENSAGENS= MENS_AZUL;
		strcpy(dados_berco[berco].mens_montagem_2, "Gravando DUNS");
		strcpy(dados_berco[berco].mens_montagem_3,   " ");
		
reteste:
		//get DUNS
		strcpy(cluster_DUNS,dados_berco[berco].duns_code);
		status = F_write_DUNS(berco, &cluster_DUNS[0]); 
		
		if(status != SUCESSO)
		{
			tent++;
			if(tent<= max_tent)
			{ 
				Delay_thread(.1); 
				goto reteste;
			}
			else
			{
				res = FALHA;
				strcpy(mens_rejeito,"Erro na escrita do DUNS");
				goto Error;
			}
		}
	
Error:
return res;
	
}




void Sinc_test (int berco)
{
	if (dados_berco[1].status_debounc_presenca_produto==ON && dados_berco[2].status_debounc_presenca_produto==ON)
	{
		if (berco == 1)
			t_sinc_1 = 1;

		if (berco == 2)
			t_sinc_2 = 1;
	
		while(1)
		{
			  
			  if  (dados_berco[1].status_debounc_presenca_produto==OFF)
				  break;
		  
			  if  (dados_berco[2].status_debounc_presenca_produto==OFF)
		  		  break;
			  
			  if (t_sinc_1 == 1 && t_sinc_2 == 1)
				  break;
		  
			  Delay_thread(0.1);
	     }
		 if (t_sinc_1 == 1 && t_sinc_2 == 1)
		 {	 
			Delay_thread(1);
			t_sinc_1 = 0;
			t_sinc_2 = 0;	
		   
			
		 }
		 
	 }
}


double Verificacao_Cosmetico_TFT(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_COSMETICO_TFT); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verificação cosmética do TFT");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 
return res;
}
double Verificacao_Cosmetico_TACO(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_COSMETICO_TACO); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verificação cosmética do TACO");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 
return res;
}
double Verificacao_Cosmetico_VELO(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
	//	if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
	//			atualizar_painel = OFF;
		
		
		if(atualizar_painel)
		{
			strcpy(img_comp, foto_COSMETICO_VELO); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verificação cosmética do VELO");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		parar_mensagem_auto = ON;
		Delay_thread(0.1);
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		///HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
			
		if(status_bot == CONT)
		{
			res =1; //pass
		}
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 
return res;
}
//LEDS PADRÃO ON
double Verificacao_LEDS_Cluster_ON(char * mens_falha, int berco)
{
double
		res = 0;
char
	arquivo_template[200]={0};

int 
	status = 0,
	status_bot,
	atualizar_painel = ON;
	
	
		///while (STATUS.Continua == ON)
			///Delay_thread(.1);
	
		Mensagem("", "", "","", MENS_AZUL, berco); 
		
		///if(dados_berco[1].modulo_em_teste && dados_berco[2].modulo_em_teste &&  berco != BERCO_1)
		//		atualizar_painel = OFF;
				
		if(atualizar_painel)
		{
			
			strcpy(img_comp, foto_LEDS_LIGASTD); 
			
			strcpy(arquivo_template, DIR_TEMPLATES);
			strcat(arquivo_template, img_comp);
			SetCtrlVal(painel_padrao,PADROES_T_MENS_PADRAO,"Verificação dos LEDs Ligados Padrão");
			DisplayImageFile(painel_padrao  , PADROES_T_TELA_PADRAO , arquivo_template); 
			DisplayPanel (painel_padrao);
		}
		
		if (test_diag == 1)
		{	
			status = SetTacometroCustomer_DIAG(0,berco); 
			Delay_thread(.1);
			status = SetTacometroCustomer_DIAG(0,berco);
			if(status == SUCESSO)
			{				
				status = SetVelocimetroCustomer_DIAG(0, berco);
				Delay_thread(.1); 
				status = SetVelocimetroCustomer_DIAG(0, berco); 
			}
			if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos LEDs");
				return -1;
			}
		}
		else
		{
			status = SetaMensTaco(0, berco);	
			if(status == SUCESSO)
				status = SetaMensVelo(0, berco);
				if(status != SUCESSO)
			{
				strcpy(mens_falha, "Falha na comunicação CAN para controle dos LEDs em Live mode ");
				return -1;
			}
		   
		}
		parar_mensagem_auto = ON;
		dados_berco[berco].cor_mensagens = MENS_AZUL;
		status_bot = BOT_OFF;
		if(status_emergencia == ON)
		{
			while (status_bot != CONT  && status_bot != REJ)
			{
				//forca leitura de rej. ou cont
				esperando_ler_botoeira = ON;
				status_bot = LeBotoeira(berco);
			}
		}
		HidePanel (painel_padrao); 
		while(STATUS.Continua || STATUS.Rejeita)
			Delay_thread(.1);
		
		if(status_bot == CONT)
		{
			res =1; //pass
		}
	    
		
		dados_berco[berco].rejeita_montagem = OFF;
	
		parar_mensagem_auto = OFF; 	
return res;
		
 }

