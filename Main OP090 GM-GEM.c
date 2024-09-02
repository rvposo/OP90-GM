#include "CIMSockets.h"
#include "toolbox.h"
#include <formatio.h>
#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include <NIDAQmx.h> 
#include "Global Error Tracking.h"
#include "Adm Equip.h"

#include "Auto OP090 GM-GEM.h"
#include "Manual OP090 GM-GEM.h"
#include "Padrao.h"  
#include "Diag GM-Gem.h"  

//BD6
#include "cvixml.h"
#include "Main OP090 GM-GEM.h"

#include "CAN GM-Gem.h"  
#include "Master_e_Negative_Samples.h"

#include "DAQ_MX.h"  
#include "Mensagens.h";
#include "Padrao.h" 

//BD5
#include "bd-support.h"

char 
	id_model_byte_temp[MAX_QUANT_MODELOS][10]={0,1,2},
	id_prefix_enditem_temp[MAX_QUANT_MODELOS][10]={"--","SJ","SK"};


//
// Função: main()
//
int main (int argc, char *argv[])
{

char
	mens_falha[BDSUPPORT_TAM_MAX_DESC_ERROR]={0};
int
	i,
	status, 
	another_inst;

	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */

	status = CheckForDuplicateAppInstance (DO_NOT_ACTIVATE_OTHER_INSTANCE, &another_inst);
	if( another_inst )
		return -1;
	

	resp_itostr = (char *)malloc(30);
	resp_str_mid = (char *)malloc(100);
	////////////// inicializa geral /////////////////////

	if(InicializaMaquina() < 0)
		return -1;

	AtualizaStationID();
	status=BDSupport_Inicializa( "GEM", stationID, CAMINHO_BD_DADOS, CAMINHO_ERR_LOGS, mens_falha);

	////////////// cria pool de 4 threads(sistema, ciclo p/ carga 1 //////////////
	CmtNewThreadPool (10, &PoolHandle);

	////////////// inicia thread sistema //////////////
	CmtScheduleThreadPoolFunction (PoolHandle, ThreadSistema, (void*)0, &sistema_threadID);
  
	for (i=1; i<=NUMERO_DE_BERCOS; i++)
	{
		ResetTextBox (painel_auto, dados_berco[i].crtlID_mensagem, "");
		if (i ==1)
			SetCtrlAttribute (painel_auto, AUTO_TXT_SERIE_1, ATTR_DIMMED, 0);
		if (i ==2)
			SetCtrlAttribute (painel_auto, AUTO_TXT_SERIE_2, ATTR_DIMMED, 0);
		
		extend_frame_format[i] = ON;	//  set extended frame format
	}
	
	
	////////////// loop principal //////////////
	LoopPrincipal();
  
	BDSupport_Finaliza();

	//////////////////// FIM ////////////////////////////
	return 0;
}

//
// Função: Atualiza_Manual()
//
void Atualiza_Manual(void)
{
	Ativa_Leitor(BERCO_1);
	Ativa_Leitor(BERCO_2);

	// Atualiza status sensores de Clamp_Berco_1
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPBERCO1, ATTR_CTRL_VAL, ( STATUS.ClampAdv_1==ON && STATUS.ClampRec_1==OFF ));
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPADV1, ATTR_CTRL_VAL, STATUS.ClampAdv_1);
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPREC1, ATTR_CTRL_VAL, STATUS.ClampRec_1);

	// Atualiza status sensores de Clamp_Berco_2
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPBERCO2, ATTR_CTRL_VAL, ( STATUS.ClampAdv_2==ON && STATUS.ClampRec_2==OFF ));
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPADV2, ATTR_CTRL_VAL, STATUS.ClampAdv_2);
	SetCtrlAttribute (painel_manual, MANUAL_CLAMPREC2, ATTR_CTRL_VAL, STATUS.ClampRec_2);

	// Atualiza status sensores de Conector_Berco_1
	SetCtrlAttribute (painel_manual, MANUAL_CONECTORBERCO1, ATTR_CTRL_VAL, ( STATUS.ConectorAdv_1==ON ));
	SetCtrlAttribute (painel_manual, MANUAL_CONECTORADV1, ATTR_CTRL_VAL, STATUS.ConectorAdv_1);

	// Atualiza status sensores de Conector_Berco_2
	SetCtrlAttribute (painel_manual, MANUAL_CONECTORBERCO2, ATTR_CTRL_VAL, ( STATUS.ConectorAdv_2==ON ));
	SetCtrlAttribute (painel_manual, MANUAL_CONECTORADV2, ATTR_CTRL_VAL, STATUS.ConectorAdv_2);

	// Atualiza status sensores de Combitac
	SetCtrlAttribute (painel_manual, MANUAL_COMBITAC, ATTR_CTRL_VAL, ( STATUS.Combitac_Berco1==ON && STATUS.Combitac_Berco2==ON ));
	SetCtrlAttribute (painel_manual, MANUAL_COMBITACBERCO1, ATTR_CTRL_VAL, STATUS.Combitac_Berco1);
	SetCtrlAttribute (painel_manual, MANUAL_COMBITACBERCO2, ATTR_CTRL_VAL, STATUS.Combitac_Berco2);	
	
	// Atualiza status sensores de segurança, botoeiras e demais recursos
	SetCtrlAttribute (painel_manual, MANUAL_STATUS_EMERGENCIA, ATTR_CTRL_VAL, STATUS.Status_Emergencia);
	SetCtrlAttribute (painel_manual, MANUAL_CONTINUA, ATTR_CTRL_VAL, STATUS.Continua);
	SetCtrlAttribute (painel_manual, MANUAL_REJEITA, ATTR_CTRL_VAL, STATUS.Rejeita);
	SetCtrlAttribute (painel_manual, MANUAL_BIMANUAL, ATTR_CTRL_VAL, STATUS.Bimanual);
	
	// Atualiza status sensores da Porta
	SetCtrlAttribute (painel_manual, MANUAL_TRAVA_PORTA_REC, ATTR_CTRL_VAL, STATUS.Trava_Porta_Rec);
	SetCtrlAttribute (painel_manual, MANUAL_TRAVA_PORTA_AVC, ATTR_CTRL_VAL, STATUS.Trava_Porta_Avc);
	SetCtrlAttribute (painel_manual, MANUAL_PORTA_FECHADA, ATTR_CTRL_VAL, STATUS.Porta_Fechada);


	// Atualiza status demais recursos
	SetCtrlAttribute (painel_manual, MANUAL_PRESCLUSTER1, ATTR_CTRL_VAL, STATUS.PresCluster_1);
	SetCtrlAttribute (painel_manual, MANUAL_PRESCLUSTER2, ATTR_CTRL_VAL, STATUS.PresCluster_2);
	SetCtrlAttribute (painel_manual, MANUAL_TRAVAPORTA, ATTR_CTRL_VAL, SAIDA.TravaPorta);
	SetCtrlAttribute (painel_manual, MANUAL_CONTATORAVIBRACAO, ATTR_CTRL_VAL, SAIDA.ContatoraVibracao);
	SetCtrlAttribute (painel_manual, MANUAL_BATTERY_1, ATTR_CTRL_VAL, SAIDA.Battery_1);
	SetCtrlAttribute (painel_manual, MANUAL_CRANK_RUN1, ATTR_CTRL_VAL, SAIDA.Crank_Run_1);
	SetCtrlAttribute (painel_manual, MANUAL_DIC_SWINPUT_DIG_1, ATTR_CTRL_VAL, SAIDA.DIC_SWINPUT_Dig_1);
	SetCtrlAttribute (painel_manual, MANUAL_SERVICEENGINESOON_1, ATTR_CTRL_VAL, SAIDA.ServiceEngineSoon_1);
	SetCtrlAttribute (painel_manual, MANUAL_VCCDIRETO_SHUNT_1, ATTR_CTRL_VAL, SAIDA.VccDireto_Shunt_1);
	SetCtrlAttribute (painel_manual, MANUAL_HABILITAFONTE1, ATTR_CTRL_VAL, SAIDA.HabilitaFonte_1);
	SetCtrlAttribute (painel_manual, MANUAL_PS_INP_SELECT1, ATTR_CTRL_VAL, SAIDA.PS_Inp_select1);
	
	
	SetCtrlAttribute (painel_manual, MANUAL_BATTERY_2, ATTR_CTRL_VAL, SAIDA.Battery_2);
	SetCtrlAttribute (painel_manual, MANUAL_CRANK_RUN2, ATTR_CTRL_VAL, SAIDA.Crank_Run_2);
	SetCtrlAttribute (painel_manual, MANUAL_DIC_SWINPUT_DIG_2, ATTR_CTRL_VAL, SAIDA.DIC_SWINPUT_Dig_2);
	SetCtrlAttribute (painel_manual, MANUAL_SERVICEENGINESOON_2, ATTR_CTRL_VAL, SAIDA.ServiceEngineSoon_2);
	SetCtrlAttribute (painel_manual, MANUAL_VCCDIRETO_SHUNT_2, ATTR_CTRL_VAL, SAIDA.VccDireto_Shunt_2);
	SetCtrlAttribute (painel_manual, MANUAL_HABILITAFONTE2, ATTR_CTRL_VAL, SAIDA.HabilitaFonte_2);
	SetCtrlAttribute (painel_manual, MANUAL_PS_INP_SELECT2, ATTR_CTRL_VAL, SAIDA.PS_Inp_select2);
	
}

//
// Função: InicializaMaquina()
//
int InicializaMaquina(void)
{
	int
		i,
		status;
	char
		mens_erro[200];
		
		
	max_db_cont = 1;
	max_db_cont_1 = 1;
	max_db_rej = 1;
	max_db_rej_1 = 1;
	
	
	t_sinc_1 = 0;   
	parar_mensagem_auto = OFF;
	vm_mode = OFF;
	modo_thread = PARAR_ESC_LEIT;
	em_debug = OFF;
	modo_manual	= OFF;
	status_emergencia = ON;
	TRAT_REJ = NAO_RETESTA;// RETESTA
	for (i=0; i<NUM_SCANNERS; i++)
	{
		dados_scanner[i].leitor_scanner_ativado = OFF;
		dados_scanner[i].ler_string_scanner = OFF;
		dados_scanner[i].leu_serial_scanner_manual = OFF;
		dados_scanner[i].tempo_scanner_enditem_ligado = 0;
	}
	dados_berco[BERCO_1].scanner_id = SCANNER_1;
	dados_berco[BERCO_2].scanner_id = SCANNER_2;	
	MENS_WARNING = MENS_OFF;
	esperando_ler_botoeira = OFF;
	finalizar_thread_sistema = OFF;
	coletando_dados = HISTOR_CPK;
	loop_manual = OFF;
	test_diag = 0;   	// test gage in live mode
	
	bimanual_remoto                = OFF;

	if(ConfigGlobal_ErrorTrack(ERR_TRACK_GRAVA) < 0)
	{
		MessagePopup ("Erro ao inicializar config de tracking",
					  "Falha ao inicializar Error Tracking ou não conseguiu abrir arquivo de tracking");
		return -1;
	}
	if ( LeConfiguracoes() < 0 )  //Configurações
		return -1;
	if ((painel_auto = LoadPanel (0, "Auto OP090 GM-GEM.uir", AUTO)) < 0)
		return -1;
	if((painel_manual = LoadPanel (0, "Manual OP090 GM-GEM.uir", MANUAL)) < 0)
		return -1;
	if ((painel_logo = LoadPanel (0, "Auto OP090 GM-GEM.uir", LOGO_BAR)) < 0)
		return -1;
    if ((panel_CAN_diagnostico = LoadPanel (0, "Diag GM-Gem.uir", TELA_DIAG)) < 0)
		return -1;
	if ((painel_mensagens = LoadPanel( 0, "Mensagens.uir", MENSAGEM )) <0) 
		return -1;
	if ((painel_padrao = LoadPanel( 0, "Padrao.uir", PADROES_T )) <0) 
		return -1;

	if(acesso_remoto)
	{
		SetCtrlAttribute (painel_auto, AUTO_CONT_REMOTO, ATTR_VISIBLE, ON);
		SetCtrlAttribute (painel_auto, AUTO_REJ_REMOTO, ATTR_VISIBLE,  ON);
		SetCtrlAttribute (painel_auto, AUTO_BIMANUAL_REMOTO, ATTR_VISIBLE, ON);
	}
	else
	{
		SetCtrlAttribute (painel_auto, AUTO_CONT_REMOTO, ATTR_VISIBLE, OFF);
		SetCtrlAttribute (painel_auto, AUTO_REJ_REMOTO, ATTR_VISIBLE,  OFF);
		SetCtrlAttribute (painel_auto, AUTO_BIMANUAL_REMOTO, ATTR_VISIBLE, OFF);
	}

	
	if (HW_present == ON)
	{	
		SetCtrlAttribute (painel_auto, AUTO_PP_1, ATTR_VISIBLE,   OFF);
		SetCtrlAttribute (painel_auto, AUTO_S_BC_1, ATTR_VISIBLE, OFF);
		SetCtrlAttribute (painel_auto, AUTO_PP_2, ATTR_VISIBLE,   OFF);
		SetCtrlAttribute (painel_auto, AUTO_S_BC_2, ATTR_VISIBLE, OFF);
		
		SetCtrlAttribute (painel_auto, AUTO_LED_CONT, ATTR_VISIBLE, OFF); 
		SetCtrlAttribute (painel_auto, AUTO_LED_REJ, ATTR_VISIBLE,  OFF); 
		SetCtrlAttribute (painel_auto, AUTO_LED_BI, ATTR_VISIBLE,   OFF); 
	}
	else
	{
		SetCtrlAttribute (painel_auto, AUTO_PP_1, ATTR_VISIBLE,   ON);
		SetCtrlAttribute (painel_auto, AUTO_S_BC_1, ATTR_VISIBLE, ON);
		SetCtrlAttribute (painel_auto, AUTO_PP_2, ATTR_VISIBLE,   ON);
		SetCtrlAttribute (painel_auto, AUTO_S_BC_2, ATTR_VISIBLE, ON);
		
		SetCtrlAttribute (painel_auto, AUTO_LED_CONT, ATTR_VISIBLE, ON); 
		SetCtrlAttribute (painel_auto, AUTO_LED_REJ, ATTR_VISIBLE,  ON); 
		SetCtrlAttribute (painel_auto, AUTO_LED_BI, ATTR_VISIBLE,   ON); 
	}	

	
	CAN_error_n=0;
	
	////////////////////////////
	tipo_de_CAN = CAN_NI;
	////////////////////////////	

//	data_length_1 		= 8;
//	data_length_2 		= 8; 
	

	if (HW_present == ON)
    {		
		for(i=1; i<= NUMERO_DE_BERCOS; i++)
		{
		   	if (InicializaCAN( can_defin[i].nome, can_defin[i].canal, i) <0)     //start CAN     
			{
				if(ConfirmPopup ("Erro ao tentar abrir comunicação com módulo NI-USB CAN",CAN_error_str[i] ) != 1)
					return -1;
			}
			atualizar_mens_can[i] = OFF;
		}
    }
	modo_thread 				= PARAR_ESC_LEIT;
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	if(Atualiza_Tab_da_rede() < 0)
		return -1;
	////////////////////////////////////////////////////////////////////////////////////////////////

	
	InicializaPainelAuto();   //<--
	
	if(tipo_monitor == MONITOR_B)
	{
		SetPanelAttribute (painel_auto, ATTR_HEIGHT, 940 );
		SetPanelAttribute (painel_auto, ATTR_TOP, VAL_AUTO_CENTER);
		SetPanelAttribute (painel_manual, ATTR_HEIGHT, 940 );
		SetPanelAttribute (painel_manual, ATTR_TOP, VAL_AUTO_CENTER);
		SetPanelAttribute (painel_auto, ATTR_WIDTH, 1280 );
		SetPanelAttribute (painel_auto, ATTR_LEFT, VAL_AUTO_CENTER);
		SetPanelAttribute (painel_manual, ATTR_WIDTH, 1280 );
		SetPanelAttribute (painel_manual, ATTR_LEFT, VAL_AUTO_CENTER);
	}

	DisplayPanel(painel_auto);//mostra painel auto
	cim_conectado = InicializaCIM();//CIM
	

	if(!cim_conectado)
	{
		if(ConfirmPopup ("Falha no CIM", "Deseja continuar e trabalhar com o CIM desligado?")==0)
			return -1;
		else
			SetPanelAttribute (painel_auto, ATTR_BACKCOLOR,0x00FF0000 ); //Seta a cor do background para vermelho
			
	}
	SetCtrlVal (painel_auto, AUTO_TXT_VERSAO , VERSAO);
	SetCtrlVal (painel_auto, AUTO_VERSAO_TABS, TABELAS_REDE_VERSAO );
	// Indice de modelos de Tabelas
	if(LeIndiceArquivo () < 0)
	{
		MessagePopup ( " ERRO AO CARREGAR index de modelos !!!" , "") ;
		return -1 ;//erro nas cargas de tabela   
	}

	if (HW_present == ON)
	{	
		if(InicializaPortasSeriais(NUMERO_DE_BERCOS) < 0)// Portas seriais
			return -1;
	}
	SetCtrlVal (painel_auto, 	AUTO_TXT_VERSAO, 	VERSAO);
	SetCtrlVal (painel_logo, 	LOGO_BAR_VERSAO, 	VERSAO);
	modo_thread = PARAR_ESC_LEIT;
	Delay_thread(0.600);
    Mensagem( "Aguarde...","Configurando os cartões de I/O",  "" ,"", MENS_CINZA, 0);
	
	if (HW_present == ON)
	{	
		status = IniciaPortasDeSaida(mens_erro);
		if( status < 0 )
		{
			MessagePopup ("Erro ao tentar Inicializar portas de saida dos cartões de I/O",
					  mens_erro);
			return FALHA;
		}
	}
	
	
	for (i=1; i<= NUMERO_DE_BERCOS; i++)
	{
		strcpy(dados_berco[i].N_Serie_EndItem_anterior, "");
		dados_berco[i].parar_mensagens_auto = OFF;
		dados_berco[i].rejeita_montagem = OFF;
		dados_berco[i].bcr_resetado = OFF;
		Desabilita_Scanner(i-1);
		tempo_presenca_off[i] = 0;
	}
	
	Set_Vdut(VOLTS_12_6, 1);
	Set_Vdut(VOLTS_12_6, 2); 
    ///////////////////////////////////////////////////////////////////////////////////
	// Abertura do Index 
	//status = ReadIndexFile () ;
	if (usar_printer == OFF) //no printer
	{

		if(ReadIndexFile () != SEM_ERRO)
		{
			MessagePopup ( " ERRO AO CARREGAR index de modelos !!!" , "") ;
			return -1 ;//erro nas cargas de tabela   
		}

		if(ReadChoicedIndexFile () != SEM_ERRO)
		{
			MessagePopup ( " ERRO AO CARREGAR tabela de modelos !!!" , "") ;
			return -1 ;//erro nas cargas de tabela   
		}
	}
	
	return 0;
}

//
// Função: Verifica_Barcodes()
//
int Verifica_Barcodes(int berco)
{
int
	num_scanner;

	num_scanner = dados_berco[berco].scanner_id;	
	if(Ativa_Leitor(berco) <= 0)
		return 0;

	if(dados_berco[berco].testar_produto==OFF && (dados_berco[berco].status_debounc_presenca_produto==ON || tempo_presenca_off[berco] < TEMPO_DESL_BCR))
	{
		if( VerificaSerialScanner(-1, berco) > 0 || dados_scanner[num_scanner].leu_serial_scanner_manual==ON)
			LeBarcode(LER_BCR_ENDITEM, berco) ;

		dados_berco[berco].tamanho_sn_enditem_lido = strlen(dados_berco[berco].N_Serie_EndItem);
		if(dados_berco[berco].tamanho_sn_enditem_lido>0)
				dados_berco[berco].bcr_resetado=OFF;
	}
	else
	{
		dados_scanner[num_scanner].leu_serial_scanner_manual = OFF;
		return 0;
	}
	////////////////// Verifica timeout ou BCR pronto ////////////////////
	if( dados_berco[berco].tamanho_sn_enditem_lido == TAMANHO_BARCODE_ENDITEM )
	{
		if(!dados_berco[berco].testar_produto)
		{
			if(Timer()-dados_berco[berco].tempo_bcr_enditem > TIME_OUT_BCR_ENDITEM)
				ResetBarcode(OFF, berco);
			else
				ResetBarcode(ON, berco);
		}
	}
	else
	{
		if(dados_berco[berco].testar_produto==OFF && dados_berco[berco].bcr_resetado==OFF)
			Delay_thread(0.01);
			ResetBarcode(OFF, berco);
	}

	return 0;
}

//
// Função: InicializaPortasSeriais()
//
int InicializaPortasSeriais(int berco)
{
	char
		resposta[100];
	int
		i,
		status;


	Mensagem( "Aguarde...","Configurando comunicação Scanner.", "", "", MENS_CINZA, berco);	      
	DisableBreakOnLibraryErrors ();

	//////////////////////////// Scanner //////////////////////////////
	for(i=0; i<NUM_SCANNERS; i++)
	{
		if(dados_scanner[i].comm_scanner > 0)
		{
			status = VM_OpenComConfig (dados_scanner[i].comm_scanner, "", 115200, 0, 8, 1, 512, -1);
			if ( status < 0 )
			{
				VM_CloseCom (dados_scanner[i].comm_scanner);
				Fmt( resposta, "Porta de comunicação com 'SCANNER(%d)' não disponível.\rO Programa será finalizado.",i);
				MessagePopup ( " Alerta ", resposta );
				EnableBreakOnLibraryErrors();
				return -1;
			}
			else
			{
				status = VM_SetComTime(dados_scanner[i].comm_scanner, 1 );
				dados_scanner[i].leitor_scanner_ativado = OFF;
			}
		}
	}
	for (i=1; i<=NUMERO_DE_BERCOS; i++)
	{
		ResetTextBox (painel_auto, dados_berco[i].crtlID_mensagem , "Aguarde...");
		InsertTextBoxLine (painel_auto, dados_berco[i].crtlID_mensagem ,-1, "Configurando cartões de I/O - PIC.");
	}
	

	ProcessDrawEvents ();

	//////////////////////////// Sistema //////////////////////////////

	status = VM_OpenComConfig (comm_sistema, "", 115200, 0, 8, 1, 512, -1);

	if ( status < 0 )
	{
		VM_CloseCom (comm_sistema);
		Fmt( resposta, "Porta de comunicação com PIC MASTER não disponível.\rO Programa será finalizado.");
		MessagePopup ( " Alerta ", resposta );
		EnableBreakOnLibraryErrors ();
		return -1;
	}
	else
	{
		status = VM_SetComTime(comm_sistema, 1 );
	}
	EnableBreakOnLibraryErrors ();

	return 0;
}

//
// Função: SetMensAuto_ON()
//
void SetMensAuto_ON(char *mens1, int berco)
{
	// mens1
	if(dados_berco[berco].status_produto == PRODUTO_TESTANDO && dados_berco[berco].rejeitado == OFF)
	{
		///strcpy(mens1,"Testando o produto ...");
		strcpy(mens1,"                         "); 
	}
	else if(dados_berco[berco].status_produto == PRODUTO_TESTANDO && dados_berco[berco].rejeitado && TRAT_REJ == RETESTA)
	{
		strcpy(mens1,"APROVADO - ");
	}
	else if(dados_berco[berco].status_produto == PRODUTO_TESTANDO && dados_berco[berco].rejeitado && TRAT_REJ != RETESTA)
	{
		strcpy(mens1,"REJEITADO - 'CONT' p/ Retestar ou 'REJ' p/ Abortar");
	}
	else if(dados_berco[berco].status_produto == PRODUTO_REJEITADO)
	{
		strcpy(mens1,"REJEITADO - Coloque etiqueta de rejeitado");
	}
	else if(dados_berco[berco].status_produto == PRODUTO_APROVADO)
	{
		strcpy(mens1,"APROVADO - Envie para a próxima estação");
	}
}

//
// Função: SetMensAutoAllOFF()
//
void SetMensAutoAllOFF(char *mens1, char *mens2, char *mens3, int berco)
{
	int
		num_scanner,
		tamanho_end_item;
	static int
		index;

	num_scanner = dados_berco[berco].scanner_id;
	strcpy(mens1," ");
	strcpy(mens2," ");
	strcpy(mens3," ");
	strcpy(dados_berco[berco].mens_montagem_falha,"");
	strcpy(dados_berco[berco].MensagemFalha1,"");
	dados_berco[berco].cor_mensagens = MENS_AZUL;
	tamanho_end_item=strlen(dados_berco[berco].N_Serie_EndItem);
	if(tamanho_end_item == TAMANHO_BARCODE_ENDITEM)  //bar code lido
	{
		if(dados_berco[berco].status_debounc_presenca_produto==ON  && dados_berco[berco].testar_produto == ON)
		{
			//strcpy(mens1,"-*- Aguarde... iniciando os testes");
			strcpy(mens1,">>> Pressione < CONTINUA > para iniciar os testes"); 
			strcpy(mens2," ");
			strcpy(mens3," ");
		}
	}
	else
	{
		if(dados_berco[berco].status_debounc_presenca_produto==ON && dados_berco[berco].testar_produto == OFF)
		{
			strcpy(mens1," Retire o produto do berço");
			strcpy(mens2," ");
			strcpy(mens3," ");
		} 
		else 
		{
			if(dados_scanner[num_scanner].leitor_scanner_ativado == OFF && dados_berco[berco].status_debounc_presenca_produto==OFF && dados_scanner[num_scanner].tempo_scanner_enditem_ligado != 0 && dados_berco[berco].barcode_enditem_lido==OFF)
			{
				dados_berco[berco].cor_mensagens = MENS_VERMELHO;
				strcpy(mens1,"");
				strcpy(mens2," Leitor de Código de Barras desligado");
				strcpy(mens3," Aperte 'CONT' ou 'REJ'");
				index++;
				if(index > 2 && index <= 4)
				{
					dados_berco[berco].cor_mensagens = MENS_PRETO;
				}
				else if(index > 4)
					index = 0;
			}
			else
			{
				if(dados_berco[berco].barcode_enditem_lido == ON)
				{
					dados_berco[berco].cor_mensagens = MENS_AZUL;
					strcpy(mens1,"Aguarde iniciando os testes");
					strcpy(mens2," ");
					strcpy(mens3," ");
				}
				else
				{
					dados_berco[berco].cor_mensagens = MENS_AZUL;
					strcpy(mens1," ");
					strcpy(mens2,"Posicione o Produto no Berço");
					strcpy(mens3,"");
				}
			}
		}
	}
}

//
// Função: CircuitosSeguranca()
//
int CircuitosSeguranca(int testar_consistencia)
{
	
	modo_thread = ESCRITA_E_LEITURA;
	retornar_movimentos = ON;
	Delay_thread(0.200);
	
	// Reset Emergencia
	Mensagem( "Aguarde...", "Resetando Emergencia", "", "", MENS_CINZA, 0);
	if(  Inicializar_CircuitosSeguranca(testar_consistencia) < 0 )
	{
		return FALHA;
	}		
	return SUCESSO;
}

//
// Função: HomePosition()
//
int HomePosition (char *mens_falha)
{
	int
		i,
		status;
		

	status = RetornaMovimentos( ON, mens_falha );
	if( status < 0)
		return FALHA;

	if (HW_present == OFF) 
		return 0;
	
	
	while((dados_berco[BERCO_1].status_debounc_presenca_produto || dados_berco[BERCO_2].status_debounc_presenca_produto
		  ) && !sair_programa)
	{
		for (i=1; i<=NUMERO_DE_BERCOS; i++)
		{
			dados_berco[i].parar_mensagens_auto = ON;
			if (dados_berco[i].status_debounc_presenca_produto == ON )
				Mensagem( "", "Remova o produto do berço", "", "", MENS_VERMELHO, i );
			else
				Mensagem( "", "Produto removido do berço", "", "", MENS_CINZA, i ); 
			
			Delay_thread(0.100); 
			dados_berco[i].parar_mensagens_auto = OFF;
		}
	}

	if(sair_programa)
		return FALHA;

	return 0;
}

//
// Função: PrintMensWarning()
//
void PrintMensWarning(ALARME_SOM alarme, int berco)
{
	char
		path[200];
	
	if(MENS_WARNING == MENS_BOT_TRAVADO)
	
	{
		Mensagem( "Botão REJ ou CONT travado(s)","Libere as botoeiras p/ prosseguir.","", "", MENS_VERMELHO, berco);
	}
	else if(MENS_WARNING == MENS_MODEL_FILE_ERROR) 
	{
		Mensagem( "Falha cadastro Modelo","Erro ao abrir o arquivo de modelos","", "", MENS_VERMELHO, berco);
	}
	else if(MENS_WARNING == MENS_MODEL_CADAST_ERROR) 
	{
		Mensagem( "Falha cadastro Modelo","Modelo com erro no cadastro na tabela de Modelos","", "", MENS_VERMELHO, berco);
	}
	else if(MENS_WARNING == MENS_TEST_TAB_ERROR) 
	{
		Mensagem( "","ERRO NA CARGA DA TABELA DE TESTES", "", "", MENS_VERMELHO, berco); 
	}
	else if(MENS_WARNING == MENS_MODEL_CONFIG_TAB_ERROR) 
	{
		Mensagem( "","ERRO NA CARGA DA TABELA DE CONFIG DO MODELO", "", "", MENS_VERMELHO, berco); 
	}
	else if(MENS_WARNING == MENS_CIM_OFF) 
	{
		Mensagem( "","CIM DESLIGADO", "", "", MENS_VERMELHO, berco);
	}
	else if(MENS_WARNING == MENS_CIM_ON) 
	{
		Mensagem( "","CIM ACIONADO", "", "", MENS_CINZA, berco);
	}
	else if(MENS_WARNING == MENS_PRODUTO_AUSENTE) 
	{
		Mensagem( "","Produto rejeitado !!", "Produto Removido do Berço", "", MENS_VERMELHO, berco);
	}
	else if(MENS_WARNING == MENS_CIM_ERROR) 
	{
		Mensagem( "Erro na comunicação com o CIM","","", "", MENS_VERMELHO, berco);
	}
	
	if(dados_berco[berco].tempo_mostra_warning == 0)
		dados_berco[berco].tempo_mostra_warning = Timer();
	if((Timer() - dados_berco[berco].tempo_mostra_warning) > TEMPO_MOSTRAR_WARNING)
	{
		MENS_WARNING = MENS_OFF;
		dados_berco[berco].tempo_mostra_warning = 0;
	}
	SetActiveCtrl (painel_auto, AUTO_TXT_SERIE_1);
	if(alarme == TOCAR_SOM)
	{
		strcpy(path,CAMINHO_SONS);
		strcat(path,"Laser_curto.wav");	 
		CVI_PlaySound (path, ON );
		Delay_thread(1.5);
		CVI_StopCurrentSound();
	}
}

//
// Função: Ativa_Leitor()
//
int Ativa_Leitor(int berco)
{
	int
		num_scanner;

	num_scanner=dados_berco[berco].scanner_id;
	if(modo_manual)
	{
		if(dados_scanner[num_scanner].leitor_scanner_ativado)
		{
			dados_scanner[num_scanner].leitor_scanner_ativado = OFF;
			dados_scanner[num_scanner].desabilitar_leitor_enditem = ON;
			Delay_thread(0.100);
		}
		return 0;
	}

	if(dados_scanner[num_scanner].leitor_scanner_ativado == OFF && 
			!dados_berco[berco].testar_produto && dados_berco[berco].status_debounc_presenca_produto && dados_berco[berco].tamanho_sn_enditem_lido != TAMANHO_BARCODE_ENDITEM)
	{
		
		dados_scanner[num_scanner].habilitar_leitor_enditem = ON;
		dados_scanner[num_scanner].ler_string_scanner = ON;
		Delay_thread(0.001);
		dados_scanner[num_scanner].leitor_scanner_ativado = ON;
	}
	else if(dados_scanner[num_scanner].leitor_scanner_ativado == ON && 
			(dados_berco[berco].testar_produto || 
			 (dados_berco[berco].status_debounc_presenca_produto==OFF && tempo_presenca_off[berco] > TEMPO_DESL_BCR) || 
			 dados_berco[berco].tamanho_sn_enditem_lido == TAMANHO_BARCODE_ENDITEM))
	{
		///if (berco == 1)
			///MoveClampBerco1 (OFF);
		
		///if (berco == 2)
			////MoveClampBerco2 (OFF);
	
		dados_scanner[num_scanner].desabilitar_leitor_enditem = ON;
		dados_scanner[num_scanner].ler_string_scanner = OFF;
		Delay_thread(0.001);
		dados_scanner[num_scanner].leitor_scanner_ativado = OFF;
	}

	return dados_scanner[num_scanner].leitor_scanner_ativado;
}

//
// Função: VerificaSerialScanner()
//
int VerificaSerialScanner(int tamanho_barcode, int berco)
{
	char
		buffer[70]="";
	int
		num_scanner,
		tamanho;

	num_scanner = dados_berco[berco].scanner_id;
	if( strlen(dados_scanner[num_scanner].strGotScanner) == 0)
		return 0;
	Delay_thread(0.050);
	strcpy( buffer, dados_scanner[num_scanner].strGotScanner );
	if (berco ==1)
		ResetTextBox( painel_auto,AUTO_TXT_SERIE_1, "\0");
	if (berco ==2)
		ResetTextBox( painel_auto,AUTO_TXT_SERIE_2, "\0");

	tamanho=strlen(buffer);
	
	
	if (tamanho_barcode == -1)
	{	
		if( tamanho != TAMANHO_BARCODE_ENDITEM && tamanho != TAMANHO_DM) 
		{
			strcpy( buffer,"err leit");
			tamanho = -1;
		}
	}
	else
	{
		if( tamanho != tamanho_barcode) 
		{
			strcpy( buffer,"err leit");
			tamanho = 0;
		}
	}	
	
	/////////////////////////////////////////////////////////////////////////
	if(tamanho == TAMANHO_DM)  
		CopyString(buffer,0,buffer,INDEX_START_SN_DM,TAMANHO_NUM_SERIE_MTC);
	//////////////////////////////////////////////////////////////////////////
	
	if (berco ==1)
		SetCtrlVal  ( painel_auto,AUTO_TXT_SERIE_1 , buffer);
	if (berco ==2)
		SetCtrlVal  ( painel_auto,AUTO_TXT_SERIE_2 , buffer);

	strcpy( dados_scanner[num_scanner].strGotScanner, "");

	return tamanho;
}

//
// Função: ProntoParaTeste()
//
void ProntoParaTeste(void)
{
	int
		berco;
	TipoNomeArquivo
		path,
		path2;
	double
		t_tela_2=0,
		t_tela=0;
		
	
	
	
	for (berco=1; berco<= NUMERO_DE_BERCOS; berco++)
	{
		
	
		if( dados_berco[berco].barcode_enditem_lido == ON && dados_berco[berco].status_debounc_presenca_produto == ON && dados_berco[berco].testar_produto == OFF /*&& STATUS.Bimanual*/ )
		{
			dados_berco[berco].testar_produto  = ON;
		}
		///else 
		///if(dados_berco[berco].barcode_enditem_lido == OFF && dados_berco[berco].modulo_em_teste == OFF && dados_berco[berco].testar_produto == OFF)
		
	
		if (dados_berco[BERCO_1].status_debounc_presenca_produto == OFF)
		{
			
			strcpy(path,CAMINHO_TEMPLATES);
			if( (Timer()-t_tela)>TIME_OUT_FOTO )
			{
				if(dados_berco[BERCO_1].iSwap == 3)
						dados_berco[BERCO_1].iSwap = 0;
				switch(dados_berco[BERCO_1].iSwap)
				{
					case 0:
						strcat(path,"Ler_Barcode_1_1.jpg");       
						break;
					case 1:
						strcat(path,"Ler_Barcode_1_2.jpg");
						break;
					case 2:
						strcat(path,"Ler_Barcode_1_3.jpg");
						break;
					default:
						break;
				}
			
				SetBreakOnLibraryErrors (0);  
				DisplayImageFile (painel_auto, dados_berco[BERCO_1].crtlID_pic_instrucao, path);
				SetBreakOnLibraryErrors (1);   
				
				t_tela = Timer();
				dados_berco[BERCO_1].iSwap ++;
			}
		}
		
		if (dados_berco[BERCO_2].status_debounc_presenca_produto == OFF)
		{
		
			strcpy(path2,CAMINHO_TEMPLATES);
			if( (Timer()-t_tela_2)>TIME_OUT_FOTO )
			{
				if(dados_berco[BERCO_2].iSwap == 3)
						dados_berco[BERCO_2].iSwap = 0;
				switch(dados_berco[BERCO_2].iSwap)
				{
					case 0:
						strcat(path2,"Ler_Barcode_2_1.jpg");       
						break;
					case 1:
						strcat(path2,"Ler_Barcode_2_2.jpg");
						break;
					case 2:
						strcat(path2,"Ler_Barcode_2_3.jpg");
						break;
					default:
						break;
				}
			
				SetBreakOnLibraryErrors (0);  
				DisplayImageFile (painel_auto, dados_berco[BERCO_2].crtlID_pic_instrucao, path2);
				SetBreakOnLibraryErrors (1);   
				
				t_tela_2 = Timer();
				dados_berco[BERCO_2].iSwap ++;
			}
		}
		
	}
}

//
// Função: Inicializar_CircuitosSeguranca()
//
int Inicializar_CircuitosSeguranca(int testar_consistencia )
{
	int
		berco;

	if(!status_emergencia || testar_consistencia)
	{
		if(ResetarEmergencia(testar_consistencia) != SEM_ERRO)
		{
			MessagePopup ("Erro no Hardware de Emergência", "Falha na consistência do circuito de Emergência");
			return FALHA;
		}
	}
	while(!status_emergencia)
	{
		if( status_emergencia == OFF )
		{
			for (berco=1; berco<=NUMERO_DE_BERCOS; berco++)
			{
				SetCtrlAttribute  (painel_auto, dados_berco[berco].crtlID_mensagem, ATTR_TEXT_COLOR ,VAL_RED);
				ResetTextBox (painel_auto, dados_berco[berco].crtlID_mensagem , "Emergencia acionada...");
				InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_mensagem ,-1, "Libere o botão de emergência.");
				InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_mensagem ,-1, "Acione BIMANUAL para retornar movimentos à posição inicial.");
			}
			while(!status_emergencia && !sair_programa)
			{
				Delay_thread(0.1);
				if(status_bimanual)
					ResetarEmergencia(OFF);
			}
		}
	
	}
	return SUCESSO;
}



//
// Função: FuncRejeitado()
//
int FuncRejeitado(char *Rodape, char *mensagem_teste, int berco)
{
	double
		t;
	int
		status;

	Delay_thread(0.1);
	status = ResetTextBox (painel_auto, dados_berco[berco].crtlID_mensagem , "");
	status = SetCtrlAttribute  (painel_auto, dados_berco[berco].crtlID_mensagem, ATTR_TEXT_COLOR ,0x000080L);
	DisplayPanel (painel_auto);
	status = BOT_TIMEOUT;//zera status
	t= Timer();
	if(!status_emergencia)
	{
		while (status != CONT  && status != REJ)
		{
			//forca leitura de rej. ou cont
			esperando_ler_botoeira = ON;
			status = LeBotoeira(berco);
		}
	}
	else
	{
		while (status != CONT  && status != REJ && status != CONT_REJ && status != FALHA_PRODUTO_AUSENTE && !sair_programa)//forca leitura de rej., cont ou cont_rej
		{
			esperando_ler_botoeira = ON;
			status = LeBotoeira(berco);
		}
		if(status == CONT_REJ)
		{
			DisplayPanel (painel_auto);
			esperando_ler_botoeira = OFF;
			return CONT_REJ;
		}
	}
	esperando_ler_botoeira = OFF;
	if(status == CONT)
	{
		strcpy(mensagem_teste,"");
		DisplayPanel (painel_auto);
		return CONT;
	}
	if(status == FALHA_PRODUTO_AUSENTE)
	{
		strcpy(mensagem_teste, "");
		return FALHA_PRODUTO_AUSENTE;
	}
	return (REJ);
}

//
// Função: Finaliza_Loop_Principal()
//
void Finaliza_Loop_Principal(void)
{
	int
		i;

	SuspendTimerCallbacks ();
	for(i=0; i<NUM_SCANNERS; i++)
	{
		dados_scanner[i].desabilitar_leitor_enditem = ON;
		Desabilita_Scanner(i);
	}
	modo_thread = ESCRITA_E_LEITURA;

	Delay_thread(1);

	finalizar_thread_sistema = ON;
	DiscardPanel (painel_auto);
}


/******************************** CVICALLBACK Thread_CAN *******************************************************/
int CVICALLBACK Thread_CAN (void *berco)
{
int
	qual_berco,
	i;

	qual_berco = *(int*)berco;
	
	SetSleepPolicy (MODO_SLEEP);
	CmtSetCurrentThreadPriority (THREAD_PRIORITY_HIGHEST);
 	while (!sair_programa && !retornar_movimentos)
 	{ 
		for(i=1; i<=NUMERO_DE_BERCOS; i++) 
		{
			Delay_thread(0.001);
			if(atualizar_mens_can[i])
				status_comunic_CAN[i] = AtualizaMensagensCAN(i);
		}	
	}
return 0;
}

	



//
// Função: CicloAutomatico()
//
int CVICALLBACK CicloAutomatico (void *qual_berco)
{
	int
		berco;
	double
		res=FALHA;

	berco = *(int*)qual_berco;

	CmtSetCurrentThreadPriority (THREAD_PRIORITY_HIGHEST);
	SetSleepPolicy (MODO_SLEEP);
	if(InicializaTestes(berco) < 0)
		return -1;
	// -------------  Executa sequência dos testes -------------
	while (dados_berco[berco].num_teste <= dados_berco[berco].max_teste  && !dados_berco[berco].aborta_testes && !sair_programa && !retornar_movimentos && res!=FALHA_GRAVE)
	{
		if (berco == 2)
			Delay_thread(.1);
		if(PresetaTeste(berco) != RES_FALHA)
		{
			res = ExecutaTestes(dados_berco[berco].pos_teste, "", dados_berco[berco].pn_customer, dados_berco[berco].modelo, berco);
		}
		else
			res = RES_FALHA;

		StatusTeste(res, berco);
	}
	FinalizaTestes(res, berco);

	return 0;
}

//
// Função: LeBarcode()
//
int LeBarcode(int tipo_leitura, int berco)
{
char
	prefix_mtc[12]={0},
	sufix_mtc [20]={0},
	aux[70]={0},
	aux2[50]={0};
int
	num_scanner,
	n = 0,
	i = 0,
	j = 0,
	status;
char
	path_som[50] = {0};

	num_scanner=dados_berco[berco].scanner_id;
	if (berco == 1)
		GetCtrlVal (painel_auto, AUTO_TXT_SERIE_1, aux);
	if (berco == 2)
		GetCtrlVal (painel_auto, AUTO_TXT_SERIE_2, aux);

	do
	{
		if(aux[i] != 32)//elimina espacos
		{
			aux2[j] = aux[i];
			j++;
			aux2[j+1]=0;
		}
		i++;
	} while(aux[i] != 0 && i < TAMANHO_BARCODE_ENDITEM); //aqui
	dados_scanner[num_scanner].leu_serial_scanner_manual = OFF; //reseta flag do leitor manual
	n = StringLength (aux2);
	StringUpperCase (aux2);
	if(strcmp(aux2, dados_berco[BERCO_1].N_Serie_EndItem_anterior) == 0
		|| strcmp(aux2, dados_berco[BERCO_2].N_Serie_EndItem_anterior) == 0
	)
	{
		if (berco == 1)
			ResetTextBox (painel_auto, AUTO_TXT_SERIE_1, "DUPLICADO");
		if (berco == 2)
			ResetTextBox (painel_auto, AUTO_TXT_SERIE_2, "DUPLICADO");
	
		return 2;
	}
	if(strcmp(aux2, dados_berco[BERCO_1].N_Serie_EndItem)==0 || strcmp(aux2, dados_berco[BERCO_2].N_Serie_EndItem) == 0)
	{
		if (berco == 1)
			ResetTextBox (painel_auto, AUTO_TXT_SERIE_1, "SERIE IGUAL");
		if (berco == 2)
			ResetTextBox (painel_auto, AUTO_TXT_SERIE_2, "SERIE IGUAL");
	
		return 2;
	}
	if (strcmp (aux2, "CIMON")==0)//conecta o cim
	{
		SetPanelAttribute (painel_auto, ATTR_BACKCOLOR,0x0000CCCC ); //Seta a cor do background para o padrão 
		cim_conectado = 1;
		SetCtrlVal (painel_auto, AUTO_TXT_SERIE_1, "\0");
		MENS_WARNING == MENS_CIM_ON;
		SetCtrlVal (painel_auto, AUTO_LED_CIM, ON);
		SetCtrlAttribute (painel_auto, AUTO_LED_CIM, ATTR_LABEL_TEXT, "CIM Conectado");
		Delay_thread(0.01);
		return 2;
	}
	else if (strcmp (aux2, "CIMOFF")==0)//desconecta o cim
	{
		SetPanelAttribute (painel_auto, ATTR_BACKCOLOR,0x00FF0000 ); //Seta a cor do background para vermelho
		cim_conectado = 0;
		SetCtrlVal (painel_auto, AUTO_TXT_SERIE_1, "\0");
		MENS_WARNING = MENS_CIM_OFF;
		SetCtrlVal (painel_auto, AUTO_LED_CIM, OFF);
		SetCtrlAttribute (painel_auto, AUTO_LED_CIM, ATTR_LABEL_TEXT, "CIM Desconectado");
		Delay_thread(0.01);
		return 2;
	}
	else if (strcmp (aux2, "REMOTOON") == 0)
	{
		cim_conectado = OFF;
		acesso_remoto = ON;
		SetCtrlVal (painel_auto, AUTO_TXT_SERIE_1, "");
	}
	else if (strcmp (aux2, "REMOTOOFF") == 0)
	{
		cim_conectado = ON;
		acesso_remoto = OFF;
		SetCtrlVal (painel_auto, AUTO_TXT_SERIE_1, "");
	}
	else if (strcmp (aux2, "FIM")==0)//finaliza o programa
	{
		sair_programa=ON;
		return 3;
	}
	n = StringLength (aux2);  //<---1
	if( n != TAMANHO_NUM_SERIE_MTC  && n != TAMANHO_BARCODE_ENDITEM)
		return n;

	///////////////////// ENDITEM /////////////////////

	if(tipo_leitura == LER_BCR_ENDITEM)
	{
		///////////////////// Etiqueta de produto lida /////////////////////////////////////////////////////////////////
		if( n == TAMANHO_NUM_SERIE_MTC)	   //DM 9
		{
			id_prefix_enditem[modelo_atual_index];
			strcpy(prefix_mtc,id_prefix_enditem_temp[modelo_atual_index]);
			CopyString(prefix_mtc, 2, aux2, 0, TAMANHO_PREFIXO_MTC);
			CopyString(sufix_mtc, 0, aux2, TAMANHO_PREFIXO_MTC, (TAMANHO_BARCODE_ENDITEM-TAMANHO_PREFIXO_ENDITEM));
			
			if (usar_printer == OFF)
			{	
				if(strstr(index_alpha_code[modelo_atual_index], prefix_mtc) == NULL)
				{
					MessagePopup ("Erro no setup de modelo",
								  "O modelo lido na etiqueta é diferente do modelo configurado na seleção de modelo manual");
					return -1;
				}
				strcpy(dados_berco[berco].prefixo_enditem, index_alpha_code[modelo_atual_index]);
			}
			else
			{	
				strcpy(dados_berco[berco].prefixo_enditem, prefix_mtc);
			}	
			dados_berco[berco].retrabalho = ON;
			
		}
		else if( n == TAMANHO_BARCODE_ENDITEM)   //11
		{
			CopyString(prefix_mtc, 0, aux2, 0, TAMANHO_PREFIXO_ENDITEM);
			CopyString(sufix_mtc, 0, aux2, TAMANHO_PREFIXO_ENDITEM, (TAMANHO_BARCODE_ENDITEM-TAMANHO_PREFIXO_ENDITEM));
			strcpy(dados_berco[berco].prefixo_enditem, prefix_mtc);
			dados_berco[berco].retrabalho = OFF;   
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		
		if (berco == 1)
			SetCtrlVal (painel_auto, AUTO_RETRABALHO_1,dados_berco[1].retrabalho);
		
		if (berco == 2)
			SetCtrlVal (painel_auto, AUTO_RETRABALHO_2,dados_berco[2].retrabalho); 
		
		//<---*
	
		status = SolicitaAtualizarTabela();		 //aqui 

		if(strcmp(dados_berco[berco].prefixo_anterior, dados_berco[berco].prefixo_enditem) != 0 || !cim_conectado || status == 0)
		{	
			strcpy(dados_berco[berco].prefixo_anterior, dados_berco[berco].prefixo_enditem);
		
		
			status = DefModel(dados_berco[berco].prefixo_enditem, TAMANHO_BARCODE_ENDITEM, LER_BCR_ENDITEM, berco);
			if( status != SEM_ERRO)
			{
				if(status == FALHA_MODELO_NAO_ENCONTRADO)
					MENS_WARNING = MENS_MODEL_CADAST_ERROR;
				else
					MENS_WARNING = MENS_MODEL_FILE_ERROR;
				SetActiveCtrl (painel_auto, AUTO_TXT_SERIE_1);
				Delay_thread(0.01);
				return 2;//erro nas cargas de tabela
			}
		
			status = CarregaTabela(berco); //carrega tab de testes
			if(status != SEM_ERRO)//erro na carga de tabela
			{
				MENS_WARNING = MENS_TEST_TAB_ERROR;
				Delay_thread(0.01);
				return 2;//erro nas cargas de tabela
			}
		
			if(CarregaArq_CFG(berco) != 0)
			{
				MENS_WARNING = MENS_TEST_TAB_ERROR;
				Delay_thread(0.01);        
				return 2;
			}
		}	
		
		//aciona o beep para indicar leitura do barcode
		if(dados_berco[berco].barcode_enditem_lido && !dados_berco[berco].modulo_em_teste)
		{
			strcpy(path_som,CAMINHO_SONS);
			strcat(path_som,"beep-07.wav");
			CVI_PlaySound (path_som, ON );
			Delay_thread(1.00);
			CVI_StopCurrentSound ();
		}
		strcpy(dados_berco[berco].N_Serie_EndItem,  dados_berco[berco].prefixo_enditem);
		strcat(dados_berco[berco].N_Serie_EndItem,  sufix_mtc);
		strcpy(dados_berco[berco].MensagemFalha1,"");
		dados_berco[berco].tempo_bcr_enditem=Timer();
		
		
		
	}
	return n;
}

//
// Função: SetEmDebug()
//
int SetEmDebug(int berco)
{
	char
		comando[50];
	int
		status;

	EnableBreakOnLibraryErrors ();
	CopyString(comando, 0, BARCODE_PADRAO_ENDITEM, 0, TAMANHO_PREFIXO_ENDITEM);
	strcpy(dados_berco[berco].prefixo_enditem, comando);
	status = DefModel(comando, TAMANHO_BARCODE_ENDITEM, LER_BCR_ENDITEM, berco);
	status = CarregaTabela(berco); //carrega tab de testes
	status = DefModel(comando, TAMANHO_BARCODE_ENDITEM, LER_BCR_ENDITEM, berco);
	status = CarregaTabela(berco); //carrega tab de testes
	if(modo_manual)
		return 0;

	cim_conectado = OFF;

	return 0;
}

//
// Função: CarregaTabela()
//
int CarregaTabela(int berco) //coloca valores da tab na estrut. Teste
{
	int
		i = 0,
		file_exists,
		arquivo = 0;
	char
		lim_alto[15],
		lim_baixo[15],
		virgula[5],
		num_teste[300],
		reteste	[15],
		linha_da_tabela[150]={0},
		versao[120],
		error_msg[80]={0};
	ssize_t
		size;

	file_exists = FileExists (dados_berco[berco].tab_testes,&size );
	if (!file_exists)
	{
		Fmt(error_msg,"%s%s%s", "Tabela '", dados_berco[berco].tab_testes, "' não encontrada.");
		MessagePopup ("Erro ao abrir arquivo", error_msg);
	    return -1;
	}
	if (size == 0)
	{
		Fmt(error_msg,"%s%s%s", "Tabela '", dados_berco[berco].tab_testes, "' vazia.");
		MessagePopup ("Erro ao abrir arquivo", error_msg);
	    return -1;
	}
	
	
	arquivo = OpenFile (dados_berco[berco].tab_testes, VAL_READ_ONLY, VAL_APPEND, VAL_ASCII);
	ReadLine ( arquivo, versao , 110 ); //le 1° linha
	i=1;
	while (ReadLine(arquivo,linha_da_tabela , 120) > 0)//le 2° linha em diante
	{
		if(strlen(linha_da_tabela) <10)
			break;
		Scan(linha_da_tabela, "%s>%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s",num_teste , virgula,
		Teste[berco][i].Nome, virgula, lim_baixo, virgula, lim_alto, virgula, Teste[berco][i].Unidade, virgula, reteste);
		Teste[berco][i].Numero 	= atoi(num_teste);
		Teste[berco][i].LimBaixo 	= atof(lim_baixo);
		Teste[berco][i].LimAlto  	= atof(lim_alto);
		Teste[berco][i].Reteste 	= atoi(reteste);
		if (Teste[berco][i].Numero>0)
			i++;	//elimina testes com simbolo negativo
	}
	dados_berco[berco].max_teste = i-1;
	CloseFile (arquivo);
	if (arquivo>0)
		arquivo = SEM_ERRO;
	
	
	return arquivo;
}

//
// Função: ResetBarcode()
//
void ResetBarcode(int bcr_enditem_pronto, int berco)
{
int
	num_scanner;

	num_scanner = dados_berco[berco].scanner_id;
	if( bcr_enditem_pronto )
	{
		switch(berco)
		{
			case BERCO_1:
				SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_1, 	ATTR_CTRL_VAL , dados_berco[1].N_Serie_EndItem);
				break;
			case BERCO_2:
				SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_2, 	ATTR_CTRL_VAL , dados_berco[2].N_Serie_EndItem);
				break;
		}

		return;
	}
	strcpy(dados_berco[berco].N_Serie_EndItem, "");
	strcpy(dados_scanner[num_scanner].strGotScanner, "");
	
 
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_nome, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_status, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_resultado , "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_teste, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_tempo, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_lim_inf, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_lim_sup, "");
	ResetTextBox (painel_auto, dados_berco[berco].crtlID_unidade, "");
	dados_berco[berco].tamanho_sn_enditem_lido = 0;
	
	
	///dados_berco[berco].rejeitado 		= OFF;   //aq_1
	dados_berco[berco].retestar 		= OFF;
	dados_berco[berco].testar_produto 	= OFF;
	dados_berco[berco].bcr_resetado 	= ON;
	dados_berco[berco].modulo_em_teste 	= OFF;
	dados_berco[berco].barcode_enditem_lido = OFF;

	//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_serial_enditem, ATTR_CTRL_VAL , ""); 
	//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_PN_Visteon, ATTR_CTRL_VAL , ""); 
	//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_amostra, ATTR_CTRL_VAL , ""); 
	//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_descricao_modelo, ATTR_CTRL_VAL , ""); 
	//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_tabela, ATTR_CTRL_VAL , ""); 
	if(strlen(dados_berco[1].N_Serie_EndItem) == 0 && strlen(dados_berco[2].N_Serie_EndItem) == 0)
		berco = (BERCO_1+BERCO_2);
	switch(berco)
	{
		case BERCO_1:
			SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_1, 	ATTR_CTRL_VAL , "");
			break;
		case BERCO_2:
			SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_2, 	ATTR_CTRL_VAL , "");
			break;
		case (BERCO_1+BERCO_2):
			/*
			SetCtrlAttribute (painel_auto, AUTO_PN_VISTEON, 		ATTR_CTRL_VAL , ""); 
			SetCtrlAttribute (painel_auto, AUTO_PN_GM, 				ATTR_CTRL_VAL , "");
			SetCtrlAttribute (painel_auto, AUTO_DESCRICAO_MODELO, 	ATTR_CTRL_VAL , "");
			SetCtrlAttribute (painel_auto, AUTO_MODELO_DISPLAY, 	ATTR_CTRL_VAL , "");
			SetCtrlAttribute (painel_auto, AUTO_AMOSTRA_TIPO, 		ATTR_CTRL_VAL , "");
			SetCtrlAttribute (painel_auto, AUTO_TABELA, 			ATTR_CTRL_VAL , "");
			*/
			SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_1, 	ATTR_CTRL_VAL , "");
			SetCtrlAttribute (painel_auto, AUTO_SERIAL_ENDITEM_2, 	ATTR_CTRL_VAL , "");
			
			break;
	}

	
}


/////////////// Le arquivo de CONFIGURAÇÃO //////////////////////////////////////////////////// 
int CarregaArq_CFG(int berco)
{
int 
	i=0,
	arquivo=0, 
	tamanho, 
	base,   
	erro_correcao, 
	erro = 0; 
char  
	linha_da_tabela[200]="", 
	resposta[100], 
	aux[250], 
	*a;

	////////////////////////////////////////////////////////////////////
	erro_correcao			= 0;
	///strcpy(ref_sup,"");
	///strcpy(dados_berco[berco].sw_version,"");
	///strcpy(dados_berco[berco].descricao_modelo,"");

	strcpy(tab_config,dados_berco[berco].tab_CFG);
	
	
	arquivo = OpenFile( tab_config, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII ) ;
	if (arquivo < 0)
	{
		MessagePopup ("Erro ao abrir arquivo",
					  "Arquivo de CFG não encontrado.");
	    return -1;
	}
	for(i=0; i < 200 ; i++) //le até 200 linhas
	{
    
		if(ReadLine (arquivo, linha_da_tabela, 80)<0)//fim do arquivo
		   break;
		strcpy (resposta, linha_da_tabela);
		tamanho = strlen(resposta);
		if (!tamanho) continue; //continua no loop se string for vazia
		StringUpperCase (resposta);
	    if(strcmp(resposta, "FIM") == 0)
    		break;
    		
		else if (strstr (resposta, "TELLTALES_AMBER=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_AMBER="), -1);
			strcpy(foto_TELLTALES_AMBER, aux);

		}
		else if (strstr (resposta, "TELLTALES_BLUE=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_BLUE="), -1);
			strcpy(foto_TELLTALES_BLUE, aux);

		}
		else if (strstr (resposta, "TELLTALES_RED=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_RED="), -1);
			strcpy(foto_TELLTALES_RED, aux);

		}
		else if (strstr (resposta, "TELLTALES_GREEN=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_GREEN="), -1);
			strcpy(foto_TELLTALES_GREEN, aux);

		}
		else if (strstr (resposta, "TELLTALES_WHITE=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_WHITE="), -1);
			strcpy(foto_TELLTALES_WHITE, aux);

		}
		else if (strstr (resposta, "TELLTALES_ALL_ON=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_ALL_ON="), -1);
			strcpy(foto_TELLTALES_ALL_ON, aux);

		}
		else if (strstr (resposta, "TELLTALES_ALL_OFF=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("TELLTALES_ALL_OFF="), -1);
			strcpy(foto_TELLTALES_ALL_OFF, aux);

		}
		else if (strstr (resposta, "LEDS_LIGASTD=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("LEDS_LIGASTD="), -1);
			strcpy(foto_LEDS_LIGASTD, aux);

		}
		
		else if (strstr (resposta, "COSMETICO_TFT=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("COSMETICO_TFT="), -1);
			strcpy(foto_COSMETICO_TFT, aux);

		}
		else if (strstr (resposta, "COSMETICO_VELO=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("COSMETICO_VELO="), -1);
			strcpy(foto_COSMETICO_VELO, aux);

		}
		else if (strstr (resposta, "COSMETICO_TACO=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("COSMETICO_TACO="), -1);
			strcpy(foto_COSMETICO_TACO, aux);

		}
		else if (strstr (resposta, "GAGES_0_0=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("GAGES_0_0="), -1);
			strcpy(foto_GAGES_0_0, aux);

		}
		else if (strstr (resposta, "GAGES_3000_80=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("GAGES_3000_80="), -1);
			strcpy(foto_GAGES_3000_80, aux);

		}
		else if (strstr (resposta, "GAGES_8000_200=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("GAGES_8000_200="), -1);
			strcpy(foto_GAGES_8000_200, aux);

		}
		////////////////////////////////////////////////////////////////////////////
		//05/02/2018 
		//inversão de posição TFCP / VISION 
		
		/* traceability */
		else if (strstr (resposta, "ADD_MTC_1=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_MTC_1="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_mtc_1 = strtol (aux, &a, base);
		}
		else if (strstr (resposta, "ADD_MTC_2=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_MTC_2="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_mtc_2 = strtol (aux, &a, base);
		}
		else if (strstr (resposta, "ADD_MTC_3=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_MTC_3="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_mtc_3 = strtol (aux, &a, base);
		}
		
		
		else if (strstr (resposta, "ADD_TRACEABILITY=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_TRACEABILITY="), 10);
			if ((strstr (aux, "0x") != NULL) || (strstr (aux, "0X") != NULL)) 
				base = 16; 
			else  
				base = 10;
			add_traceability = strtol (aux, &a, base);
			add_traceability = add_traceability + 0xFF000000;
		}
		/*  sw version*/
		else if (strstr (resposta, "ADD_SW_VERSION_1=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_SW_VERSION_1="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_sw_1 = strtol (aux, &a, base);
		}
		else if (strstr (resposta, "ADD_SW_VERSION_2=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_SW_VERSION_2="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_sw_2 = strtol (aux, &a, base);
		}
		else if (strstr (resposta, "ADD_SW_VERSION_3=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_SW_VERSION_3="), 6);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_sw_3 = strtol (aux, &a, base);
		}

				else if (strstr (resposta, "SW_VERSION=") != NULL)
		{
			CopyString (aux, 0, resposta, 11, -1);
			strcpy(dados_berco[berco].sw_version, aux);

			if(strlen(dados_berco[berco].sw_version) < 4)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de SW_VERSION do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		else if (strstr (resposta, "NVM_VERSION=") != NULL)
		{
			CopyString (aux, 0, resposta, 12, -1);
			strcpy(dados_berco[berco].nvm_version, aux);

			if(strlen(dados_berco[berco].nvm_version) < 7)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de NVM_VERSION do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		else if (strstr (resposta, "DESC_MODEL=") != NULL)
		{
			CopyString (aux, 0, resposta, 11, -1);
			strcpy(dados_berco[berco].descricao_modelo, aux);

			if(strlen(dados_berco[berco].descricao_modelo) < 4)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de DESC_MODEL do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
			else if(strstr(dados_berco[berco].descricao_modelo, "JUBC") == NULL && strstr(dados_berco[berco].descricao_modelo, "JUBA")== NULL)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de DESC_MODEL do cluster - Arq = ", dados_berco[berco].tab_config);
				MessagePopup ("Erro definição de modelo",
							  "Não ha definição se o modelo é JUBC ou JUBA");
				erro =1;
			}
			else
			{
				if(strstr(dados_berco[berco].descricao_modelo, "JUBA") != NULL)
					dados_berco[berco].cluster_type = 1;
				else
					dados_berco[berco].cluster_type = 2;
			}
		}
		
		else if (strstr (resposta, "VISTEON_END_ITEM_PN=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("VISTEON_END_ITEM_PN="), -1);
			strcpy(dados_berco[berco].visteon_end_item, aux);
		
			if(strlen(dados_berco[berco].visteon_end_item) < 15)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de VISTEON_END_ITEM_PN do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
	
		else if (strstr (resposta, "DUNS_CODE=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("DUNS_CODE="), -1);
			strcpy(dados_berco[berco].duns_code, aux);
		
			if(strlen(dados_berco[berco].duns_code) < 9)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de DUNS_CODE do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
	
		else if (strstr (resposta, "ADD_HARDWARE_NUMBER=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_HARDWARE_NUMBER="), -1);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_cluster_hardware_number = strtol (aux, &a, base);

			if(strlen(aux) != 5)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de ADD_HARDWARE_NUMBER do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		
		else if (strstr (resposta, "ADD_COSTUMER_ENDITEM_PN=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_COSTUMER_ENDITEM_PN="), -1);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_cluster_costumer_enditem_pn = strtol (aux, &a, base);

			if(strlen(aux) != 5)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de ADD_COSTUMER_ENDITEM_PN do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		
		else if (strstr (resposta, "ADD_VISTEON_CONFIG=") != NULL)
		{
			CopyString (aux, 0, resposta, strlen("ADD_VISTEON_CONFIG="), -1);
			if (strstr (aux, "0X") != NULL) 
				base = 16; 
			else  
				base = 10;
			add_cluster_visteon_config = strtol (aux, &a, base);

			if(strlen(aux) != 5)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de ADD_VISTEON_CONFIG do cluster - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		///////////////////////////////////////////////////////////////////////////
		//data to cluster records
		//1
		else if (strstr (resposta, "DT_HARDWARE_NUMBER=") != NULL)
		{
			CopyString (aux, 0, resposta,strlen("DT_HARDWARE_NUMBER="), -1);
			strcpy(dados_berco[berco].ecu_hardware_number, aux);

			if(strlen(dados_berco[berco].ecu_hardware_number) != 8)
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de DT_HARDWARE_NUMBER - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		
		else if (strstr (resposta, "VPPS_CODE=") != NULL)
		{
			CopyString (aux, 0, resposta,strlen("VPPS_CODE="), -1);
			strcpy(dados_berco[berco].vpps_code, aux);

			if(strlen(dados_berco[berco].vpps_code) < 7 )
			{
				Fmt(mensagem,"%s<%s%s","Falha no dado de VPPS_CODE - Arq = ", dados_berco[berco].tab_config);
				erro =1;
			}
		}
		else if (strstr (resposta, "IMPRIMIR=") != NULL)   //ck
		{
			CopyString (aux, 0, resposta, 9, -1);
			if((strcmp(aux, "SIM") == 0) || (strcmp(aux, "ON") == 0))
				imprimir=ON;
			else if((strcmp(aux, "NAO") == 0) || (strcmp(aux, "OFF") == 0) || (strcmp(aux, "NÂO") == 0))
				imprimir=OFF;
			else
			{
				imprimir = OFF;
				Fmt(mensagem,"%s<%s%s","Falha no dado de Imprimir - Arq = ", tab_config);
				erro =1;
			}
		}
	}
	
	
		
	CloseFile (arquivo);
			
		
 return SEM_ERRO;
}




//
// Função: DefModel()
//
int DefModel(char *prefixo, int tamanho_barcode, int tipo_leit, int berco)
{
	int
		file_exists,
		arquivo, 
		i=0;
	ssize_t
		size;
	char 
		linha[300], 
		virgula[3],
		
		dado1[200]="",
		dado2[50]="",
		dado3[50]="",
		dado4[50]="",
		dado5[50]="",
		dado6[50]="",
		dado7[50]="", 
		dado8[200],
		dado9[50]="",
		dado10[50]="",
		dado11[50]="",
		dado12[50]="",
		dado13[50]="",
	
		arq_tabs_rede[60]="",
		arq_modelos[60]={0},
		error_msg[80]={0};
	
	//------------- Seleciona tabelas local ou driver de rede -------------
	strcpy(arq_tabs_rede,  PASTA_TAB_REDE);
	strcat(arq_tabs_rede,  TABELAS_REDE_VERSAO);
	if(cim_conectado)
	{
		Fmt(dados_berco[berco].tab_testes,"%s%s",arq_tabs_rede, "\\TST\\"); 
		Fmt(dados_berco[berco].tab_CFG,"%s%s",arq_tabs_rede, "\\CFG\\"); 
		Fmt(arq_modelos,"%s%s",arq_tabs_rede, TABELA_MODELOS_REDE);
		SetCtrlVal(painel_auto,AUTO_LED_TRD,ON); 
	}
	else
	{
		Fmt(dados_berco[berco].tab_testes, "%s%s",PASTA_TAB_LOCAIS, "TST\\");
		Fmt(dados_berco[berco].tab_CFG,"%s%s",PASTA_TAB_LOCAIS, "\\CFG\\"); 
		strcpy(arq_modelos, TABELA_MODELOS_LOCAL);
		SetCtrlVal(painel_auto,AUTO_LED_LC,ON); 
	}
	
	file_exists = FileExists (arq_modelos, &size);   
	if (!file_exists)
	{
		Fmt(error_msg,"%s%s%s", "Arquivo ", arq_modelos, " não encontrado.");
		MessagePopup ("Erro ao abrir arquivo", error_msg);
	    return -2;
	}
	if (size == 0)
	{
		Fmt(error_msg,"%s%s%s", "Arquivo ", arq_modelos, " vazio.");
		MessagePopup ("Erro ao abrir arquivo", error_msg);
	    return -2;
	}
	arquivo = OpenFile ( arq_modelos, VAL_READ_ONLY, VAL_APPEND, VAL_ASCII );
	if (arquivo < 0)
	{
		Fmt(error_msg,"%s%s%s", "Falha ao abrir o arquivo ", arq_modelos, ".");
		MessagePopup ("Erro ao abrir arquivo", error_msg);
	    return -2;
	}
	
	while (ReadLine(arquivo,linha, 250) > 0){//le demais linhas ate o fim do arquivo 
		StringUpperCase (linha);    	
		
  		Scan(linha, "%s>%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]",
			  		 dado1,virgula, 
					 dado2,virgula, 
					 dado3,virgula,
					 dado4,virgula,
					 dado5,virgula,
					 dado6,virgula,
					 dado7,virgula,
					 dado8,virgula,	
					 dado9,virgula,
					 dado10,virgula,
					 dado11,virgula,
					 dado12,virgula,
					 dado13 
					 );
				
		Scan(dado1, "%s>%s", dado1);//elimina possivel tab ou espaco apos a string
  		Scan(dado2, "%s>%s", dado2);//elimina possivel tab ou espaco apos a string
  		Scan(dado3, "%s>%s", dado3);//elimina possivel tab ou espaco apos a string
  		Scan(dado4, "%s>%s", dado4);//elimina possivel tab ou espaco apos a string
  		Scan(dado5, "%s>%s", dado5);//elimina possivel tab ou espaco apos a string
  		Scan(dado6, "%s>%s", dado6);//elimina possivel tab ou espaco apos a string
  		Scan(dado7, "%s>%s", dado7);//elimina possivel tab ou espaco apos a string
  		Scan(dado8, "%s>%s", dado8);//elimina possivel tab ou espaco apos a string
  		Scan(dado9, "%s>%s", dado9);//elimina possivel tab ou espaco apos a string
  		Scan(dado10, "%s>%s", dado10);//elimina possivel tab ou espaco apos a string
  		Scan(dado11, "%s>%s", dado11);//elimina possivel tab ou espaco apos a string
  		Scan(dado12, "%s>%s", dado12);//elimina possivel tab ou espaco apos a string
		Scan(dado13, "%s>%s", dado13);//elimina possivel tab ou espaco apos a string 
 		
		if (strcmp (dado1, prefixo)==0)
 		{
			strcpy(dados_berco[berco].ref_GM, 		dado2); //ref GM 
			strcat(dados_berco[berco].tab_CFG, 		dado3); // tab CFG
			strcat(dados_berco[berco].tab_testes, 	dado4); // tab test
			
			strcpy(dados_berco[berco].tipo_amostra, dado5); // tipo amostra
			
			strcpy(dados_berco[berco].pn_visteon, 	dado6); // PN Visteon
			strcpy(dados_berco[berco].descricao_modelo, dado8); // descricao do modelo de produto  
			strcpy(dados_berco[berco].prefixo_enditem, dado9); // Prefixo enditem
			strcpy(dados_berco[berco].display, dado10); //display
			
			dados_berco[berco].barcode_enditem_lido = ON;
			
			if(strcmp(dado12, "SIM") == 0)//cluster serviço??
				dados_berco[berco].tipo_service = ON;
			else
				dados_berco[berco].tipo_service = OFF;
			t_BC [berco] = Timer();
			i = 1;
		
			
			SetCtrlVal ( painel_auto, AUTO_PN_GM, 				dados_berco[berco].ref_GM ) ;  	  // ref GM
			SetCtrlVal ( painel_auto, AUTO_PN_VISTEON, 			dados_berco[berco].pn_visteon ) ; // PN Visteon 
			SetCtrlVal ( painel_auto, AUTO_TABELA, 				dados_berco[berco].tab_testes ) ; // tab test

			SetCtrlVal ( painel_auto, AUTO_MODELO_DISPLAY, 		dados_berco[berco].display ) ;	  // display
			SetCtrlVal ( painel_auto, AUTO_DESCRICAO_MODELO, 	dados_berco[berco].descricao_modelo ) ; // descricao do modelo de produto
			SetCtrlVal ( painel_auto, AUTO_AMOSTRA_TIPO,		dados_berco[berco].tipo_amostra ) ;     // tipo amostra
	
		
			break;
		}	
 	  
		if(strcmp(dado1,"FIM")==0) 
			break;
	}

	CloseFile (arquivo);
	

	if(i==1 )
	{
		modelo_display[berco] = DISPLAY_MODEL_INDEF;
		if(strstr(dado10,"SEG") != NULL)	
			modelo_display[berco] = DISPLAY_SEGMENTADO;
		
		if(strstr(dado10,"MONO") != NULL)	
			modelo_display[berco] = DISPLAY_TFT_MONO;
		
		if(strstr(dado10,"COLOR") != NULL)	
			modelo_display[berco] = DISPLAY_TFT_COLOR;
		
		
		tipo_aplique = 0;
		if(strstr(dado11,"DF") != NULL)	
		   tipo_aplique=1;
		
		if(strstr(dado11,"LB") != NULL)	
		   tipo_aplique=2;
		
		if(strstr(dado11,"LC") != NULL)	
		   tipo_aplique=3;
		
	if(strstr(dados_berco[berco].tipo_amostra,"MSAMPLE") != NULL)	
		{
			if(berco == 1)
				amostra_tipo_1	= MASTER_SAMPLE;
			else
				amostra_tipo_2	= MASTER_SAMPLE;
			strcpy(dados_berco[berco].tipo_amostra, "Master Sample");
		}
	
		else if(strstr(dados_berco[berco].tipo_amostra,"NEGATIVA") != NULL)	
		{
			if(berco == 1)
				amostra_tipo_1		= NEGATIVE_SAMPLE;
			else
				amostra_tipo_2		= NEGATIVE_SAMPLE;
			strcpy(dados_berco[berco].tipo_amostra, "Amostra Negativa");
		}
		else 
		{
			strcpy(dados_berco[berco].tipo_amostra, "Teste"); 
			if(berco == 1)
				amostra_tipo_1		= TESTE;
			else
				amostra_tipo_2		= TESTE;
		}
		
	
		//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_serial_enditem, ATTR_CTRL_VAL , dados_berco[berco].prefixo_enditem); 
		//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_PN_Visteon, ATTR_CTRL_VAL , dados_berco[berco].pn_visteon); 
		//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_amostra, ATTR_CTRL_VAL , dados_berco[berco].tipo_amostra); 
		//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_descricao_modelo, ATTR_CTRL_VAL , dados_berco[berco].descricao_modelo); 
		//SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_tabela, ATTR_CTRL_VAL , dados_berco[berco].tab_testes); 
		
		
	}
	 else
	{
		dados_berco[berco].barcode_enditem_lido = OFF;
		MENS_WARNING = MENS_MODEL_CADAST_ERROR;
		return FALHA_MODELO_NAO_ENCONTRADO;
	}
	

	ProcessDrawEvents();
	return SEM_ERRO;
}


//
// Função: ColetaDados()
//
void ColetaDados(int Max_Test, int berco)
{
	long
		Size;
	int
		Arquivo_Coleta,
		cont,
		Mes,
		Dia,
		Ano,
		status;
	char
		*Data,
		*Hora,
		dia[4]="",
		mes[4]="",
		ano[4]="",
		*Buf;

	Data = DateStr();
	Hora = TimeStr();
	CopyString (dia, 0, Data, 3, 2);
	CopyString (mes, 0, Data, 0, 2);
	CopyString (ano, 0, Data, 8, 2);
	Buf = (char *)malloc(20000);
	GetSystemDate ( &Mes, &Dia, &Ano);// faz o nome do arquivo
	if(dados_berco[berco].status_produto == PRODUTO_APROVADO)
		sprintf(Buf,"%sHist_%d-%d-%d.txt",CAMINHO_APROVADOS, Dia,Mes,Ano);
	else
		sprintf(Buf,"%sHist_%d-%d-%d.txt",CAMINHO_REJEITOS, Dia,Mes,Ano);
	status = GetFileInfo(Buf , &Size);
	if (status == 1)
		Arquivo_Coleta  = OpenFile(Buf , VAL_WRITE_ONLY , VAL_APPEND , VAL_ASCII );
	else
		Arquivo_Coleta  = OpenFile(Buf , VAL_WRITE_ONLY , VAL_OPEN_AS_IS , VAL_ASCII );
	if(Arquivo_Coleta < 0)
	{
		MessagePopup ("Erro ao tentar coletar dados de Histórico",
					  "Falha ao tentar abrir arquivo de coleta de Histórico");
	}
	strcpy(Buf,"-----------------------------------------------------------------------------");
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	if(dados_berco[berco].status_produto == PRODUTO_APROVADO)
	{
		Fmt( Buf , "%s%s", dados_berco[berco].N_Serie_EndItem, "  - APROVADO");
	}
	else
	{
		Fmt( Buf , "%s%s", dados_berco[berco].N_Serie_EndItem, "  - REPROVADO");
	}
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	
	Fmt( Buf , "%s%i", "Berco = ",berco);
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	if(dados_berco[berco].retrabalho == ON)
	{
		strcpy(Buf, "RETRABALHO");
		status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	}
	for (cont = 1; cont <= Max_Test; cont++)
	{
		strcpy(Buf,Teste[berco][cont].Nome);
		Fmt(Buf , "%s%s" , Buf ,",");
		if(Teste[berco][cont].LimBaixo <= 999)
			Fmt(Buf , "%s%f[p3]\t" , Buf , Teste[berco][cont].LimBaixo);
		else
			Fmt(Buf , "%s%f[p1]\t" , Buf , Teste[berco][cont].LimBaixo);
		Fmt(Buf , "%s%s" , Buf ,",");
		if(Teste[berco][cont].Resultado <= 999)
			Fmt(Buf , "%s%f[p3]\t" , Buf , Teste[berco][cont].Resultado);
		else
			Fmt(Buf , "%s%f[p1]\t" , Buf , Teste[berco][cont].Resultado);
		Fmt(Buf , "%s%s" , Buf ,",");
		if(Teste[berco][cont].LimAlto <= 999)
			Fmt(Buf , "%s%f[p3]\t" , Buf , Teste[berco][cont].LimAlto);
		else
			Fmt(Buf , "%s%f[p1]\t" , Buf , Teste[berco][cont].LimAlto);
		
		Fmt(Buf , "%s%s" , Buf ,",");
		Fmt(Buf , "%s%s" , Buf , Teste[berco][cont].Unidade);
		Fmt(Buf , "%s%s" , Buf ,",");
		Fmt(Buf , "%s%s" , Buf , Teste[berco][cont].Condicao);
		Fmt(Buf , "%s%s\t" , Buf ,",");
		Fmt(Buf , "%s%f[p3]" , Buf , Teste[berco][cont].Tempo_teste);
		Fmt(Buf , "%s%s" , Buf ," s");
		status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	}
	Fmt(Buf , "%s%s" , "Versão SW de teste = ",VERSAO);
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	Fmt(Buf , "%s%f[p2]" , "Tempo de teste = ",tempo_total);
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	Data_e_Hora (Data, Dtimer, DmesI);
	Fmt( Buf, "%s%s - %s" , "Data = ", Data, Dtimer);
	status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
	status = CloseFile (Arquivo_Coleta);
	if(coletando_dados == CPK || coletando_dados == HISTOR_CPK)//
	{
		GetSystemDate ( &Mes, &Dia, &Ano);// faz o nome do arquivo
		if(dados_berco[berco].status_produto == PRODUTO_APROVADO)
			sprintf(Buf,"%sCPK_%d-%d-%d.txt",CAMINHO_CPK_APROV, Dia,Mes,Ano);
		else
			sprintf(Buf,"%sCPK_%d-%d-%d.txt",CAMINHO_REJEITOS, Dia,Mes,Ano);
		status = GetFileInfo(Buf , &Size);
		if (status == 1)
			Arquivo_Coleta  = OpenFile(Buf , VAL_WRITE_ONLY , VAL_APPEND , VAL_ASCII );
		else
			Arquivo_Coleta  = OpenFile(Buf , VAL_WRITE_ONLY , VAL_OPEN_AS_IS , VAL_ASCII );
		if(Arquivo_Coleta < 0)
		{
			MessagePopup ("Erro ao tentar coletar dados de CPK",
						  "Falha ao tentar abrir arquivo de coleta de CPK");
		}
		if(!status)//1º vez gravando o arquivo - cria cabeçalho
		{
			Fmt(Buf , "%s%s" , "Versão SW de teste = ",VERSAO);
			status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));


			strcpy(Buf,"Serial ,");
			for (cont = 1; cont <= Max_Test; cont++)
			{
				Fmt(Buf , "%s%s%s" , Buf ,Teste[berco][cont].Nome, ",");

			}
			status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));

			strcpy(Buf,"Lim Sup ,");
			for (cont = 1; cont <= Max_Test; cont++)
			{
				Fmt(Buf , "%s%f[p2]%s" , Buf ,Teste[berco][cont].LimAlto, ",");
			}
			status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));

			strcpy(Buf,"Lim Inf ,");
			for (cont = 1; cont <= Max_Test; cont++)
			{
				Fmt(Buf , "%s%f[p2]%s" , Buf ,Teste[berco][cont].LimBaixo,",");
			}
			status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));

		}
		strcpy(Buf,dados_berco[berco].N_Serie_EndItem);
		strcat(Buf, ",");
		for (cont = 1; cont <= Max_Test; cont++)
		{
			Fmt(Buf , "%s%f[p2]%s" , Buf , Teste[berco][cont].Resultado,",");
		}
		status = WriteLine(Arquivo_Coleta , Buf , StringLength(Buf));
		status = CloseFile (Arquivo_Coleta);
	}
	free (Buf);
}



//
// Função: MoveIn_Cim()
//
int MoveIn_Cim (int berco)
{
	int
		tent = 0;
	short
		time_out = 5;

	if (cim_conectado == OFF)
		return 1;

	char
		*errordesc;

	errordesc = (char *) CA_AllocMemory(500);
falha_conex1:
	rescim = CIMSockets__SMFmovein (cimsockets, NULL, sockID, time_out, stationID, dados_berco[berco].N_Serie_EndItem, &errordesc, &resultcim);
	if (resultcim < 0 || rescim <0)
	{
		if(tent == 0)
		{
			tent = 1;
			if(Reconect_CIM () == 0)
				goto falha_conex1;
		}
		MENS_WARNING = MENS_CIM_ERROR;
		Delay_thread(0.7);
		Fmt(mensagem, "%s%s%s", "Barcode", dados_berco[berco].N_Serie_EndItem, " de ENDITEM inválido no CIM ou erro de ROTA");
		COR_MENSAGENS= MENS_VERMELHO;
		Mensagem ( "",mensagem, errordesc, "",MENS_VERMELHO, berco);
		CA_FreeMemory(errordesc);
		Delay_thread(3);
		MENS_WARNING = MENS_OFF;
		return -1;
	}
	CA_FreeMemory(errordesc);
	dados_berco[berco].movein_feito = ON;
	return 1;
}

//
// Função: MoveOut_Build_Cim()
//
void MoveOut_Build_Cim(char *prefixo, double Res, int Rej, char* Test, int berco)
{
	int
		tent;
	char
		unit_result[3],
		group_id[6],
		version[6]="";
		//sTest[6]="";
	short
		timeout=3;

	//Fmt(sTest,"%i",Test);
	strcpy(version  , "V2.00");
	strcpy(group_id, prefixo);
	if(Rej == 1)
		strcpy(unit_result, "FA");
	else
		strcpy(unit_result, "PA");

	tent = 0;
falha_conex1:
	rescim = CIMSockets__SMFmoveout (cimsockets, NULL, sockID, timeout, stationID, dados_berco[berco].N_Serie_EndItem, unit_result, &resultcim);
	if (resultcim < 0 || rescim <0)
	{
		if(tent == 0)
		{
			tent = 1;
			if(Reconect_CIM () == 0)
				goto falha_conex1;
		}
		Mensagem( "Erro no Cim - Não fez moveout de ENDITEM", "CIMSockets__SMFmoveout", "Aperte Continue", "", MENS_VERMELHO, berco);
		return;
	}
	if(Rej == OFF)
	{
		strcpy(dados_berco[berco].N_Serie_EndItem_anterior, dados_berco[berco].N_Serie_EndItem);
	}
	else
	{
		rescim = CIMSockets__SMFenvtest (cimsockets, NULL, sockID, timeout,
										 stationID, dados_berco[berco].N_Serie_EndItem, group_id, version, Test, unit_result, Res, 1, &resultcim);
	}

	return;
}

//
// Função: PresetaTeste()
//
int PresetaTeste(int berco)
{
	char
		tmp[90];

	dados_berco[berco].status_produto 		= PRODUTO_TESTANDO;
	dados_berco[berco].tempo_inicial_teste = Timer();
	dados_berco[berco].rejeitado 			= OFF;
	dados_berco[berco].rejeita_montagem 	= OFF;
	dados_berco[berco].pos_teste			= Teste[berco][dados_berco[berco].num_teste].Numero; //pega eqval. a postest,vetor começa com zero(deve-se subtrair 1)
	strcpy(dados_berco[berco].mens_montagem_2,"");
	strcpy(dados_berco[berco].mens_montagem_3,"");
	strcpy(dados_berco[berco].mens_montagem_falha,"");
	strcpy(dados_berco[berco].MensagemFalha1,"");
	Fmt(tmp , "%s[w3]<%d" , dados_berco[berco].num_teste);
	
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_teste, 0, tmp);
	
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_nome, 0, Teste[berco][dados_berco[berco].num_teste].Nome);
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_status, 0, "...");
	InsertTextBoxLine (painel_auto,dados_berco[berco].crtlID_resultado , 0, "testando..");
	Fmt(tmp, "%f[p2]", Teste[berco][dados_berco[berco].num_teste].LimAlto);
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_lim_sup, 0, tmp);
	Fmt(tmp, "%f[p2]", Teste[berco][dados_berco[berco].num_teste].LimBaixo);
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_lim_inf, 0, tmp);
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_unidade, 0, Teste[berco][dados_berco[berco].num_teste].Unidade);
	InsertTextBoxLine (painel_auto, dados_berco[berco].crtlID_tempo, 0, "...");

	if (!status_emergencia)
		return RES_FALHA;

	return 0;
}

//
// Função: RetornaMovimentos()
//
int RetornaMovimentos(int testar_consistencia, char *mens_falha)
{
	int
		i,
		status;

	modo_thread = ESCRITA_E_LEITURA;
	retornar_movimentos = ON;
	all_motions_home	= OFF;
	Delay_thread(0.100);
	Mensagem( "Aguarde...", "Retornando para home position", "", "", MENS_CINZA, 0);

	if (HW_present == OFF) 
	{	
		
		for (i=1; i<=NUMERO_DE_BERCOS; i++)
			ResetTextBox (painel_auto, dados_berco[i].crtlID_mensagem , "");

		retornar_movimentos = OFF;
		
		return SEM_ERRO;
	
	}
	
	if(Inicializar_CircuitosSeguranca(testar_consistencia) < 0)
	{
		MessagePopup ("Erro ao inicializar circuitos de segurança", "Falha ao tentar inicializar Circuito de Emergência.");
		return FALHA;
	}	
	
	while( (all_motions_home==OFF || !status_emergencia) && !sair_programa )
	{

		// Recua Conector_Berco_1
		status = MoveConectorBerco1( OFF );
		if( status==FALHA_TIMEOUT )
		{
			strcpy(mens_falha, "Time Out - Conector_Berco_1");
			return FALHA_GRAVE;
		}
		if (VerificaExcecoesRetornaMovimentos(&status, mens_falha))
			return status;

		// Recua Conector_Berco_2
		status = MoveConectorBerco2( OFF );
		if( status==FALHA_TIMEOUT )
		{
			strcpy(mens_falha, "Time Out - Conector_Berco_2");
			return FALHA_GRAVE;
		}
		if (VerificaExcecoesRetornaMovimentos(&status, mens_falha))
			return status;

		Delay_thread(2);
		
		// Recua Clamp_Berco_1
		status = MoveClampBerco1( OFF );
		if( status==FALHA_TIMEOUT )
		{
			strcpy(mens_falha, "Time Out - Clamp_Berco_1");
			return FALHA_GRAVE;
		}
		if (VerificaExcecoesRetornaMovimentos(&status, mens_falha))
			return status;

		// Recua Clamp_Berco_2
		status = MoveClampBerco2( OFF );
		if( status==FALHA_TIMEOUT )
		{
			strcpy(mens_falha, "Time Out - Clamp_Berco_2");
			return FALHA_GRAVE;
		}
		if (VerificaExcecoesRetornaMovimentos(&status, mens_falha))
			return status;

		ApresentaImagemInstrucao();
	}
	for (i=1; i<=NUMERO_DE_BERCOS; i++)
		ResetTextBox (painel_auto, dados_berco[i].crtlID_mensagem , "");

	retornar_movimentos = OFF;

	return SEM_ERRO;
}


//
// Função: MensagensAuto()
//
void MensagensAuto(void)
{
	
	int
		berco;

	if(modo_manual || parar_mensagem_auto)
		return;

	for (berco=1; berco<=NUMERO_DE_BERCOS; berco++)
	{
		
		///SetCtrlAttribute (painel_auto, dados_berco[berco].crtlID_presenca, ATTR_CTRL_VAL, dados_berco[berco].status_debounc_presenca_produto);
		
		if(MENS_WARNING != MENS_OFF)
		{
			if(alarme_som != TOCOU_SOM)
				alarme_som = TOCAR_SOM;
			PrintMensWarning(alarme_som, berco);
			alarme_som = TOCOU_SOM;
			return;
		}
		alarme_som = SEM_SOM;
		if(dados_berco[berco].parar_mensagens_auto)
			return;

		//////////////////// Mens geral /////////////////////////
		if( !dados_berco[berco].modulo_em_teste ) 	   // nenhum berço em dados_berco[berco].num_teste
			SetMensAutoAllOFF(dados_berco[berco].mens_montagem_1, dados_berco[berco].mens_montagem_2, dados_berco[berco].mens_montagem_3, berco);
		else if( dados_berco[berco].modulo_em_teste ) // berço em dados_berco[berco].num_teste
			SetMensAuto_ON(dados_berco[berco].mens_montagem_1, berco);

		/////////////////// Mensagens de falha //////////////////
		if(strlen(dados_berco[berco].MensagemFalha1) > 0 || dados_berco[berco].rejeitado)
		{
			if(strlen(dados_berco[berco].MensagemFalha1)>0)
				strcpy(dados_berco[berco].mens_montagem_falha, dados_berco[berco].MensagemFalha1);
			Mensagem( dados_berco[berco].mens_montagem_1, dados_berco[berco].mens_montagem_2, dados_berco[berco].mens_montagem_3, dados_berco[berco].mens_montagem_falha, MENS_VERMELHO, berco);
		} else {
			Mensagem( dados_berco[berco].mens_montagem_1, dados_berco[berco].mens_montagem_2, dados_berco[berco].mens_montagem_3, dados_berco[berco].mens_montagem_falha, dados_berco[berco].cor_mensagens , berco);
		}
	}
}

//
// Função: ApresentaImagemInstrucao()
//
void ApresentaImagemInstrucao(void)
{
	int
		i;
	TipoNomeArquivo
		path;

	for (i=1; i<=NUMERO_DE_BERCOS; i++)
	{
		if ( dados_berco[i].quant_img_instrucao > 0 )
		{
			if( (Timer()-dados_berco[i].tempo_tela_img_instrucao)>TIME_OUT_FOTO )
			{
				dados_berco[i].index_img_instrucao++;
				if(dados_berco[i].index_img_instrucao > dados_berco[i].quant_img_instrucao - 1)
					dados_berco[i].index_img_instrucao = 0;

				Fmt(path,"%s%s",CAMINHO_TEMPLATES, dados_berco[i].imagem_instrucao[dados_berco[i].index_img_instrucao]);
				DisplayImageFile (painel_auto, dados_berco[i].crtlID_pic_instrucao, path);
				dados_berco[i].tempo_tela_img_instrucao = Timer();
			}
		}
	}
}

//
// Função: AdicionaImagemInstrucao()
//
void AdicionaImagemInstrucao(int ordem_apresentacao, char nome_imagem[], int berco)
{
	strcpy(dados_berco[berco].imagem_instrucao[ordem_apresentacao-1],nome_imagem);
	dados_berco[berco].quant_img_instrucao=ordem_apresentacao;
}

//
// Função: InicializaCIM()
//
int InicializaCIM(void)
{
	int
		file,
		i,
		status,
		tamanho;
	char
		cim_buffer[50],
		cim_label[50],
		tmp[90];
	short
		timeout = 5;

	Mensagem( "Aguarde...","Iniciando CIM e contagem produção...", "", "", MENS_CINZA, 0);

	/************** Inicia a contagem da produção **************/
	file = OpenFile( ARQ_FTT, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII );
	status = ReadLine( file, tmp,  5 );
	TotalTestados   = atoi(tmp);
	status = ReadLine( file, tmp,  5 );
	TotalAprovados  = atoi(tmp);
	status = ReadLine( file, tmp,  5 );
	TotalRejeitados = atoi(tmp);
	status = ReadLine( file, tmp,  5 );
	TotalFTT        = atof(tmp);
	CloseFile (file);

	//**********  Inicializa variaveis do CIM  **********
	strcpy(host,"");
	strcpy(service,"");
	strcpy(stationID,"");
	file = OpenFile ("..\\CIM\\Config_Cim.txt", VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if (file < 0)
	{
		MessagePopup ( " Erro abrindo arquivo CIM", "Falha ao abrir arquivo de configuração do CIM..." );
		return OFF;
	}
	for(i=0; i < 10; i++) //le até 10 linhas
	{
		if(ReadLine (file, cim_buffer, 29)<0)//fim do arquivo
			break;
		strcpy (cim_label, cim_buffer);
		tamanho = strlen(cim_label);
		if (!tamanho) continue; //continua no loop se string for vazia
		StringUpperCase (cim_label);
		if((strstr(cim_label,"FIM") != NULL || strstr(cim_label,"END") != NULL) && strlen(cim_label)<=4)
			break;

		if(strstr(cim_label, "MAQUINA=") != NULL)
		{
			CopyString (Num_Maquina, 0, cim_label, 8, 12);
			strcpy(stationID, Num_Maquina);
		}
		else if (strstr (cim_label, "HOST=") != NULL)
		{
			CopyBytes(host,0,cim_buffer,5,tamanho-5);
		}
		else if (strstr (cim_label, "SERVICE=")!= NULL)
		{
			CopyBytes(service,0,cim_buffer,8,tamanho-8);
		}
	}
	CloseFile (file);
	rescim = CIMSockets_New_SMF (NULL, 0, LOCALE_NEUTRAL, 0, &cimsockets);//"CIM Sockets - SMF", "Criando Object Handle";
	if(rescim < 0 || cimsockets < 0)
	{
		Mensagem( "","CIM Sockets - SMF", "Erro parametros do CIM - criação do socket", "", MENS_VERMELHO, 0);
		Delay(3);
		goto erro_cim;
	}
	rescim = CIMSockets__SMFopen_sock (cimsockets, NULL, host, service, timeout, &sockID);//CIM Sockets - SMF", Opening Socket
	if (rescim < 0 || sockID < 0)
	{
		Mensagem ( "","CIM Sockets - SMF", "Erro parametros do CIM - Erro abrindo socket", "", MENS_VERMELHO, 0);
		Delay(3);
		goto erro_cim;
	}
	rescim = CIMSockets__SMFsync_sock (cimsockets, NULL, sockID, stationID,
									   timeout, &timestamp);
	if (rescim < 0)
	{
		Mensagem( "","CIM Sockets - SMF", "Erro sincronizando conexão rede CIM", "", MENS_VERMELHO, 0);
		Delay(3);
		goto erro_cim;
	}
	if (timestamp < 0)
	{
		Mensagem( "","CIM Sockets - SMF", "Erro de conexão com a rede CIM - time stamp", "", MENS_VERMELHO, 0);
		Delay(3);
		goto erro_cim;
	}
	status = SetCtrlVal (painel_auto, AUTO_LED_CIM, ON);
	status = SetCtrlAttribute (painel_auto, AUTO_LED_CIM, ATTR_LABEL_TEXT,
							   "CIM Conectado");
	return ON;

erro_cim:

	status = SetCtrlVal (painel_auto, AUTO_LED_CIM, OFF);
	status = SetCtrlAttribute (painel_auto, AUTO_LED_CIM, ATTR_LABEL_TEXT,
							   "CIM Desconectado");
	return OFF;
}

//
// Função: Reconect_CIM()
//
int Reconect_CIM(void)
{
	int
		rescim;

	CIMSockets__SMFclose_sock (cimsockets, NULL, sockID, 2, NULL);
	Delay_thread(0.1);

	rescim = CIMSockets_New_SMF (NULL, 0, LOCALE_NEUTRAL, 0, &cimsockets);//"CIM Sockets - SMF","Criando Object Handle";
	if(rescim < 0 || cimsockets < 0)
	{
		return -1;
	}
	rescim = CIMSockets__SMFopen_sock (cimsockets, NULL, host, service, 3 , &sockID);//CIM Sockets - SMF", Opening Socket
	if (rescim < 0 || sockID < 0)
	{
		return -2;
	}
	rescim = CIMSockets__SMFsync_sock (cimsockets, NULL, sockID, stationID, 3 , &timestamp);
	if (rescim < 0)
	{
		return -3;
	}
	if (timestamp < 0)
	{
		return -4;
	}
	Delay_thread(0.1);

	return 0;
}

//
// Função: Zera()
//
void Zera(void)
{
	int
		file;
	char
		tmp[90];

	TotalRejeitados = 0;
	TotalAprovados = 0;
	TotalTestados = 0;
	SetCtrlVal (painel_auto, AUTO_TXT_TESTADOS, "0");
	SetCtrlVal (painel_auto, AUTO_TXT_APROVADOS, "0");
	SetCtrlVal (painel_auto, AUTO_TXT_REJEITADOS, "0");
	SetCtrlVal (painel_auto, AUTO_TXT_FTT, "0.0");
	//grava as estatisticas em arquivo
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
}

//
// Função: SolicitaAtualizarTabela()
//
// Descrição: verifica se o arquivo de solicitação de atualização de tabela esta presente
//
int SolicitaAtualizarTabela(void)
{
	int
		status = -1,
		arquivo = 0,
		tamanho = 0;
	char
		arq_nome[40] = {0};

	Fmt(arq_nome, "%s%s%s", PASTA_REDE_CTR, stationID, ".txt");
	arquivo = GetFileInfo (arq_nome, &tamanho);
	if(arquivo)
		status = remove (arq_nome);

	return status;
}

//
// Função: AtualizaFTT()
//
void AtualizaFTT(void)
{
	char
		tmp[90];

	//atualiza estatistica
	Fmt(tmp , "%f[p0]" , TotalTestados);
	SetCtrlAttribute (painel_auto, AUTO_TXT_TESTADOS, ATTR_CTRL_VAL,tmp);
	Fmt(tmp , "%f[p0]" , TotalRejeitados);
	SetCtrlAttribute (painel_auto, AUTO_TXT_REJEITADOS, ATTR_CTRL_VAL,tmp);
	Fmt(tmp , "%f[p0]" , TotalAprovados);
	SetCtrlAttribute (painel_auto, AUTO_TXT_APROVADOS, ATTR_CTRL_VAL,tmp);
	if(TotalTestados == 0)//evitar divisão por zero
		ftt = 0;
	else
		ftt = (TotalAprovados / TotalTestados) * 100.00;
	Fmt(tmp , "%f[p1]%s" , ftt , "%");
	SetCtrlAttribute (painel_auto, AUTO_TXT_FTT, ATTR_CTRL_VAL,tmp);
	//SetCtrlAttribute (painel_auto,AUTO_COLETA ,ATTR_CTRL_VAL ,coletando_dados);
	TotalTestados_ant = TotalTestados;
}

//
//
// Função: VerificaExcecoesRetornaMovimentos()
//
// Descrição: Esta função é utilizada para realizar validações básicas
//            durante retorna movimentos
//
// Parametros:
//
//   - resp: caso uma excecao seja identifcada, retorna o número da mesma.
//
//   - mens_falha: caso uma excecao seja identifcada, retorna a sua descrição.
//
// Retorno : Retorna o valor '0' caso não tenha ocorrido qualquer excecao.
//
int VerificaExcecoesRetornaMovimentos(int *resp, char * mens_falha)
{
	ApresentaImagemInstrucao();

	if( !status_emergencia )
	{
		strcpy(mens_falha,"Emergência Acionada.");
		*resp = EMERG_ACIONADA;
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
// Função: LoopPrincipal()
//
int LoopPrincipal(void)
{
double 
	tbc_1 = 0,
	tbc_2 = 0; 
double 
	timeout = 5,//5;
	estabilizar = 0.5,
	t;
int

	i,
	berco,
	status,
	status2,
	num_scanner;
static double
	tempo_nao_prioridade = 0;
	
//BD8
char 
	mens_falha[BDSUPPORT_TAM_MAX_DESC_ERROR]      = {0}; 

	
	if( HomePosition(mens_falha) < 0 )
	{
		MessagePopup( "Erro Home Position", mens_falha );
		return -1;
	}
	for (i = 1; i <= NUMERO_DE_BERCOS; i++)
		ResetTextBox (painel_auto, dados_berco[i].crtlID_mensagem , "\0");

	SetCtrlAttribute (painel_auto, AUTO_TXT_SERIE_1, ATTR_DIMMED, 0);
	SetCtrlAttribute (painel_auto, AUTO_TXT_MAQUINA, ATTR_CTRL_VAL, stationID);
	SetActiveCtrl( painel_auto, AUTO_TXT_SERIE_1 );
	status2 = CmtScheduleThreadPoolFunction (PoolHandle, Thread_CAN, &berco, &CAN_threadID[1]);
	////////////// inicia loop principal - eventos de UIR e relógio/////////////////
	SetSleepPolicy (MODO_SLEEP);
	do
	{
		ProcessSystemEvents ();
		
		if(Timer()-tempo_nao_prioridade > 0.2) //0.5
		{
			if(modo_manual)
				Atualiza_Manual();
			else
			{
				if(!status_emergencia)
				{
				    status=BDSupport_Emergencia_Acionada(mens_falha);	
					
					if( HomePosition(mens_falha) < 0 )
					{
						MessagePopup( "Erro Home Position", mens_falha );
						return -1;
					}
				}
				if(TotalTestados_ant != TotalTestados)
					AtualizaFTT();

				if (dados_berco[BERCO_1].status_debounc_presenca_produto == ON && dados_berco[BERCO_1].modulo_em_teste == OFF && dados_berco[BERCO_2].modulo_em_teste == OFF )//ao iniciar testes c/ 1 berço não pode mais acionar o outro
				{	
					tbc_1=Timer();
					num_scanner=dados_berco[BERCO_1].scanner_id;
					dados_scanner[num_scanner].leitor_scanner_ativado = OFF;//força ligar leitor
					while(dados_berco[BERCO_1].barcode_enditem_lido == OFF && Timer()-tbc_1 < TEMPO_DESL_BCR)
					{	
						Verifica_Barcodes(BERCO_1); 
						if(dados_berco[BERCO_2].barcode_enditem_lido == OFF && dados_berco[BERCO_2].status_debounc_presenca_produto == ON)
							break;
					}
					
					if ((Timer()-tbc_1 >TEMPO_DESL_BCR) || ( Timer()-t_BC[BERCO_1] >timeout_TBC))
					{
						MoveClampBerco1(OFF);
						if(dados_scanner[BERCO_1].scanner_habilitado)
							Desabilita_Scanner(SCANNER_1);
						
						///////////////////////////////////////////////////////////////////////////////////////////////
						Mensagem( " ", "-- Retire o Produto no berço de Testes 1 --", " ", "", MENS_AZUL, BERCO_1);
						ResetBarcode(OFF,  BERCO_1);
						HidePanel(painel_mensagens);
						ResetTextBox( painel_auto,AUTO_TXT_SERIE_1, "\0");
						dados_berco[BERCO_1].testar_produto = OFF;
						//dados_berco[BERCO_1].modulo_em_teste = OFF;
						dados_berco[BERCO_1].barcode_enditem_lido = OFF;
						strcpy(dados_berco[BERCO_1].prefixo_anterior,"");
						///////////////////////////////////////////////////////////////////////////////////////////////
						
						while(dados_berco[BERCO_1].status_debounc_presenca_produto == ON)
							Delay_thread(0.010);
						///////Delay_thread(1);
					}	
				}
				if (dados_berco[BERCO_2].status_debounc_presenca_produto == ON && dados_berco[BERCO_1].modulo_em_teste == OFF && dados_berco[BERCO_2].modulo_em_teste == OFF)//ao iniciar testes c/ 1 berço não pode mais acionar o outro
				{
					///Delay_thread(1);
					///MoveClampBerco2(ON);
					tbc_2=Timer();
					num_scanner=dados_berco[BERCO_2].scanner_id;
					dados_scanner[num_scanner].leitor_scanner_ativado = OFF;//força ligar leitor
					while(dados_berco[BERCO_2].barcode_enditem_lido == OFF && Timer()-tbc_2 <TEMPO_DESL_BCR)
					{	
						Verifica_Barcodes(BERCO_2);
						if(dados_berco[BERCO_1].barcode_enditem_lido == OFF && dados_berco[BERCO_1].status_debounc_presenca_produto == ON)
							break;
						//Delay_thread(.1); 
					}
					
					if ((Timer()-tbc_2 >TEMPO_DESL_BCR) ||( Timer()-t_BC[BERCO_2] >timeout_TBC))
					{
						MoveClampBerco2(OFF);
						if(dados_scanner[BERCO_2].scanner_habilitado)
							Desabilita_Scanner(SCANNER_2);
						///////////////////////////////////////////////////////////////////////////////////////////////
						Mensagem( " ", "-- Retire o Produto no berço de Testes 2 --", " ", "", MENS_AZUL, BERCO_2);
						ResetBarcode(OFF,  BERCO_2);
						HidePanel(painel_mensagens);
						ResetTextBox( painel_auto,AUTO_TXT_SERIE_2, "\0");
						dados_berco[BERCO_2].testar_produto = OFF;
						//dados_berco[BERCO_2].modulo_em_teste = OFF;
						dados_berco[BERCO_2].barcode_enditem_lido = OFF; 
						strcpy(dados_berco[BERCO_2].prefixo_anterior,"");
						////////////////////////////////////////////////////////////////////////////////////////////////
						while(dados_berco[BERCO_2].status_debounc_presenca_produto == ON)
							Delay_thread(0.010);
						//Delay_thread(1);
					}	 
				}
				
				ProntoParaTeste();
				MensagensAuto();
				ApresentaImagemInstrucao();
			}
			tempo_nao_prioridade=Timer();
		}
		
		
		for (i = 1; i <= NUMERO_DE_BERCOS; i++)
		{	
			//////////////////////////////////////////////////////////////////////
			if( dados_berco[i].testar_produto    == ON  && dados_berco[i].modulo_em_teste   == OFF && dados_berco[i].status_debounc_presenca_produto == ON)
			{
					t=Timer();
				    if (i == BERCO_1)
					{
						while(dados_berco[BERCO_1].status_debounc_presenca_produto && Timer()-t < estabilizar)
						{
							Delay_thread(0.01);
							if(dados_berco[BERCO_1].status_debounc_presenca_produto == OFF)
								break;
						}
						if(dados_berco[BERCO_1].status_debounc_presenca_produto == ON)
							MoveClampBerco1(ON); 
					}
					if (i == BERCO_2)
					{
						while(dados_berco[BERCO_2].status_debounc_presenca_produto && Timer()-t < estabilizar)
						{
							Delay_thread(0.01);
							if(dados_berco[BERCO_2].status_debounc_presenca_produto == OFF)
								break;
						}
						if(dados_berco[BERCO_2].status_debounc_presenca_produto == ON)
							MoveClampBerco2(ON);
					}
			}
			//////////////////////////////////////////////////////////////////////
			if (STATUS.Continua == ON) 
				 start_test = ON;

			if(dados_berco[BERCO_1].testar_produto == ON  && dados_berco[BERCO_2].testar_produto == ON  /*&& STATUS.Continua == OFF*/) 
				 start_test = ON;
				
			if( dados_berco[i].testar_produto    == ON  && dados_berco[i].modulo_em_teste   == OFF &&  
					dados_berco[i].status_debounc_presenca_produto == ON  &&  start_test == ON)
			{
					//start_test = OFF;
					// Inicia thread ciclo de testes
					berco = i;  
					dados_berco[berco].modulo_em_teste = ON;
					status=CmtScheduleThreadPoolFunction (PoolHandle, CicloAutomatico, &berco, &ciclo_threadID[i]);
					Delay_thread(0.3);  //<-- eq th
			}
			if(dados_berco[1].modulo_em_teste == ON && dados_berco[2].modulo_em_teste == ON)
					start_test = OFF;
			 
			if( dados_berco[i].modulo_em_teste   == OFF && 
				dados_berco[i].status_debounc_presenca_produto == OFF)  
			{
			    if (i == 1)
				{
						MoveClampBerco1(OFF);
						Desabilita_Scanner(SCANNER_1);
						/////////////////////////////////////////////////////
						ResetBarcode(OFF,  BERCO_1);
						///HidePanel(painel_mensagens);
						/////////////////////////////////////////////////////
						while(dados_berco[BERCO_1].status_debounc_presenca_produto == ON)
							Delay_thread(0.001);
						dados_berco[BERCO_1].testar_produto = OFF;
						//dados_berco[BERCO_1].modulo_em_teste = OFF;
						dados_berco[BERCO_1].barcode_enditem_lido = OFF; 
						strcpy(dados_berco[BERCO_1].prefixo_anterior,"");
						//Delay_thread(1);
				}	
					
				if (i == 2)
				{	
						MoveClampBerco2(OFF);
						Desabilita_Scanner(SCANNER_2);
						///////////////////////////////////////////////////////////////////////////////////////////////
						//Mensagem( " ", "-- Retire o Produto no berço de Testes 2 --", " ", "", MENS_AZUL, BERCO_2);
						ResetBarcode(OFF,  BERCO_2);
						///HidePanel(painel_mensagens);
						//ResetTextBox( painel_auto,AUTO_TXT_SERIE_2, "\0");
						////////////////////////////////////////////////////////////////////////////////////////////////
						while(dados_berco[BERCO_2].status_debounc_presenca_produto == ON)
							Delay_thread(0.001);
							dados_berco[BERCO_2].testar_produto = OFF;
							dados_berco[BERCO_2].modulo_em_teste = OFF;
							dados_berco[BERCO_2].barcode_enditem_lido = OFF; 
						    strcpy(dados_berco[BERCO_2].prefixo_anterior,"");
							//Delay_thread(1);
				}
			}
		}
	} 
	while(!sair_programa);

	//// Finaliza loop principal ////
	Finaliza_Loop_Principal();
	return 0;
}


//******************************** Função Foto_Display_Diag ******************************************************************
int Foto_Display_Diag(int modelo_display, int pattern)
{
int 
	status;
char 
	path[256],
	error_str[200];

	strcpy(path, DIR_TEMPLATES);
	switch(modelo_display)
	{
		case DISPLAY_SEGMENTADO:
			switch(pattern)
			{
				case PATTERN_LCD_ALL_OFF:
					strcat(path, "Disp_TFT_All_OFF.png");  //
					break;
				case PATTERN_LCD_ALL_ON:
					strcat(path, "Disp_Segm_All_ON.png");  //
					break;
				case PATTERN_LCD_3:
					strcat(path, "Disp_Segm_patt3.png");
					break;
				case PATTERN_LCD_4:
					strcat(path, "Disp_Segm_patt4.png");
					break;
				case PATTERN_LCD_EOL:
					strcat(path, "Disp_TFT_EOL.png");
					break;
			}
			break;
		case DISPLAY_TFT_MONO:
			switch(pattern)
			{
				case PATTERN_LCD_ALL_OFF:
					strcat(path, "Disp_TFT_All_OFF.png"); //
					break;
				case PATTERN_LCD_ALL_ON:
					strcat(path, "TFT_All_ON.png"); //
					break;
				case PATTERN_LCD_3:
					strcat(path, "TFT_Mono_Patt3.png");
					break;
				case PATTERN_LCD_4:
					strcat(path, "TFT_Mono_Patt4.png");
					break;
				case PATTERN_LCD_EOL:
					strcat(path, "Disp_TFT_EOL.png");
					break;
			}
			break;
		case DISPLAY_TFT_COLOR:
			switch(pattern)
			{
				case PATTERN_LCD_ALL_OFF:
					strcat(path, "Disp_TFT_All_OFF.png"); //
					break;
				case PATTERN_LCD_ALL_ON:
					strcat(path, "TFT_All_ON.png"); //
					break;
				case PATTERN_LCD_3:
					strcat(path, "TFT_Color_Patt3.png");
					break;
				case PATTERN_LCD_4:
					strcat(path, "TFT_Color_Patt3.png");
					break;
				case PATTERN_LCD_RED:
					strcat(path, "TFT_Color_red.png");
					break;
				case PATTERN_LCD_GREEN:
					strcat(path, "TFT_Color_green.png");
					break;
				case PATTERN_LCD_BLUE:
					strcat(path, "TFT_Color_blue.png");
					break;
				case PATTERN_LCD_GRAY_LEVEL:
					strcat(path, "TFT_Color_Gray_level.png");
					break;
				case PATTERN_LCD_COLOUR_BARS:
					strcat(path, "TFT_Color_ColourBars.png");
					break;
				case PATTERN_LCD_EOL:
					strcat(path, "Disp_TFT_EOL.png");
					break;
			}
			break;
	}
	status = DisplayImageFile (panel_CAN_diagnostico, TELA_DIAG_FOTO_DISPLAY , path);
	if(status < 0)
	{
		Fmt(error_str, "%s<%s%s", "Falhou ao tentar carregar foto do display. Verifique a existência do arquivo -> ", path);  
		MessagePopup ("Erro ao tentar carregar foto do display", error_str );
		return -1;
	}
	
return SEM_ERRO;
}


/********************************* Função ModelosCallback **************************************************************************/
int CVICALLBACK ModelosCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if (usar_printer == OFF)
				ReadChoicedIndexFile ();
			break;
		}
	return 0;
}


///////////////////////////////////////////////////////////////////////
//	ReadIndexFile													 //	
///////////////////////////////////////////////////////////////////////
int ReadIndexFile (void)
{

int 	

	i=0, 
	file, 
	nMaxItens,
	res,
	status;
char	
	choice[25], 
	item[25], 
	nome[80], 
	linha[300], 
	virgula[3],
	dado1[300],
	dado2[50],
	dado3[30],
	dado4[50],
	dado5[50],
	dado6[50]="",
	dado7[50]="",
	dado8[50]="",
	dado9[50]="",
	dado10[70]="",
	dado11[50]="",
	dado12[50]="";

	////////////////////////////////////////////////////////////////////
  	strcpy( nome, TABELA_MODELOS_LOCAL ) ; 
  	
	file = OpenFile ( nome, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if ( file < 0 ){
		MessagePopup( " ERRO ", "Erro na abertura do arquivo de modelos" ) ;
		return -1 ;
	}
	
	i = 0 ; 
	//status = ReadLine ( file, linha, 120 ) ;
	status = ReadLine ( file, linha, 120 ) ;
	
	while( ON )
	{
		status = ReadLine ( file, linha, 120 ) ;
		if( strcmp( linha, "FIM") == 0 || strcmp( linha, "END") == 0 || status <0) 
			break ;
	 	StringUpperCase (linha);    	
   		Scan(linha, "%s>%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]%c%s[t44]"
   		,dado1,virgula, dado2,virgula,dado3,virgula,dado4,virgula,dado5,virgula,dado6,virgula,dado7,virgula,dado8,virgula,dado9,virgula,dado10,virgula,dado11,virgula,dado12);
		Scan(dado1, "%s>%s", dado1);  //prefixo
   		Scan(dado2, "%s>%s", dado2);  //PN GM
   		Scan(dado3, "%s>%s", dado3);  //arquico CFG
   		Scan(dado4, "%s>%s", dado4);  //tabela testes
   		Scan(dado5, "%s>%s", dado5);  //tipo de amostra
   		Scan(dado6, "%s>%s", dado6);  //PN VIsteon 
   		Scan(dado7, "%s>%s", dado7);  //spare   
   		Scan(dado8, "%s>%s", dado8);  //Desc modelo
   		Scan(dado9, "%s>%s", dado9);  //Prefix EI
   		Scan(dado10, "%s>%s", dado10);//Display
		Scan(dado11, "%s>%s", dado11);//Aplique

		strcpy( index_alpha_code[i], 		dado1);
		strcpy( index_pn_custumer[i],		dado2) ;
		strcpy( index_tab_config[i], 		dado3) ;
		strcpy( index_tabela_testes[i], 	dado4) ;
		strcpy( index_master_sample[i], 	dado5) ;
		strcpy( index_pn_visteon[i], 		dado6) ;
		strcpy( index_descricao_modelo[i], 	dado8) ;
		strcpy( index_prefix_enditem[i], 	dado9) ;
		strcpy( index_display[i], 			dado10) ;
		strcpy( index_modelo_aplique[i], 	dado11) ;
		i++ ;	
	}
	
	CloseFile( file ) ;
	
	nMaxItens = i ;
	ReplaceListItem ( painel_auto, AUTO_MODELOS, 0, index_alpha_code[0], 0);

	for ( i=1; i <= nMaxItens;i++ )
		InsertListItem ( painel_auto, AUTO_MODELOS, -1, index_alpha_code[i], i );
	
	//////////////////////////////////////////////////////////////////
	file = OpenFile ( TAB_MODEL_SELECT, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII);

	if ( file < 0 ){
		MessagePopup( " ERRO ", "Erro na abertura do arquivo TAB_MODEL_SELECT" ) ;
		return -1 ;
	}
	
	status = ReadLine ( file, choice, 20 ) ;
	status = ReadLine ( file, item,   20 ) ;
													  
	CloseFile( file  ) ;
	
	modelo_atual_index = atoi(item) ;
	if(modelo_atual_index < 0 || modelo_atual_index > MAX_QUANT_MODELOS)
		modelo_atual_index =0;
	SetCtrlIndex ( painel_auto, AUTO_MODELOS, modelo_atual_index ) ;
	
	res = AtualizaDadosModelo();
	
	return res ;
}

///////////////////////////////////////////////////////////////////////
//	ReadChoicedIndexFile            								 //	
///////////////////////////////////////////////////////////////////////
int ReadChoicedIndexFile (void)
{

int  	
	file, 
	res,
	status;
char	
	itemLabel[20],  
	aux[5];

	
	//////////////////////////////////////////////////////////////
	GetCtrlIndex ( painel_auto, AUTO_MODELOS, &modelo_atual_index ) ;
	
	GetLabelFromIndex ( painel_auto, AUTO_MODELOS, modelo_atual_index, itemLabel );
	
	file = OpenFile ( TAB_MODEL_SELECT, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);
	if ( file < 0 ){
		MessagePopup( " ERRO ", "Erro na abertura do arquivo TAB_MODEL_SELECT" ) ;
		return -1 ;
	}
	
	status = WriteLine( file, itemLabel, strlen(itemLabel) ) ;
	Fmt( aux, "%d", modelo_atual_index ) ;
	status = WriteLine( file, aux, strlen(aux) ) ;
	
	CloseFile( file  ) ;
	res = AtualizaDadosModelo();
	
	return res;

}


/********************************* Função AtualizaDadosModelo **************************************************************************/
int AtualizaDadosModelo(void)
{
int 
	status;
	
	
	SetCtrlVal ( painel_auto, AUTO_PN_GM, 				index_pn_custumer[modelo_atual_index] ) ;
	SetCtrlVal ( painel_auto, AUTO_PN_VISTEON, 			index_pn_visteon[modelo_atual_index] ) ;
	SetCtrlVal ( painel_auto, AUTO_TABELA, 				index_tabela_testes[modelo_atual_index] ) ;
	//SetCtrlVal ( painel_auto, AUTO_APLIQUE, 			index_modelo_aplique[modelo_atual_index] ) ;
	SetCtrlVal ( painel_auto, AUTO_MODELO_DISPLAY, 		index_display[modelo_atual_index] ) ;
	SetCtrlVal ( painel_auto, AUTO_DESCRICAO_MODELO, 	index_descricao_modelo[modelo_atual_index] ) ;
	SetCtrlVal ( painel_auto, AUTO_AMOSTRA_TIPO,		index_master_sample[modelo_atual_index] ) ;
	
	strcpy(dados_berco[1].tab_testes , 	PASTA_TAB_LOCAIS) ;
	strcat(dados_berco[1].tab_testes , 	"\\TST\\") ;
	strcat(dados_berco[1].tab_testes , 	index_tabela_testes[modelo_atual_index]) ;
	strcpy(dados_berco[1].tab_CFG , 	PASTA_TAB_LOCAIS) ;
	strcat(dados_berco[1].tab_CFG , 	"\\CFG\\") ;
	strcat(dados_berco[1].tab_CFG, 		index_tab_config[modelo_atual_index]);	

	if(CarregaArq_CFG(1) != SEM_ERRO)
	{
		MessagePopup ( " ERRO AO CARREGAR CONFIGURAÇÕES DESTE MODELO..." , "Veja modelo selecionado") ;
		return -1 ;//erro nas cargas de CFG   
	}
	status = CarregaTabela(1); //carrega tab de testes
	if(status != SEM_ERRO){//erro na carga de tabela
		MessagePopup( "ERRO NA CARGA DAS TABELAS", "ERRO NA CARGA DA TABELA DE TESTES DO MODELO SELECIONADO"); 
		return -2 ;//erro nas cargas de tabela   
	}
return SUCESSO;		
}



int Atualiza_Tab_da_rede(void)
{
char 
	arq_tabs_rede[256], 
	cmd_str[300],
	tabela[200];
int
	atualizacao_tabs = -1;
	
			//------------ Atualiza tabelas local a partir do driver de rede ----------------------
			strcpy(arq_tabs_rede,  PASTA_TAB_REDE);
			
			SetBreakOnLibraryErrors (0);
			///Fmt(cmd_str,"%s<%s%s",arq_tabs_rede, "\\*.*"); 
			strcat(arq_tabs_rede,  TABELAS_REDE_VERSAO);
			Fmt(cmd_str,"%s<%s%s",arq_tabs_rede, "\\*.*"); 
			atualizacao_tabs = CopyFile (cmd_str, PASTA_TAB_LOCAIS);
			
			if(atualizacao_tabs == 0)
			{
				///strcat(arq_tabs_rede,  TABELAS_REDE_VERSAO);  
				Fmt(cmd_str,"%s<%s%s",arq_tabs_rede, "\\CFG\\*.*");
				Fmt(tabela, "%s<%s%s",PASTA_TAB_LOCAIS, "\\CFG");
	
				atualizacao_tabs = CopyFile (cmd_str, tabela);
				if(atualizacao_tabs == 0)
				{
					Fmt(cmd_str,"%s<%s%s",arq_tabs_rede, "\\TST\\*.*"); 
					Fmt(tabela, "%s<%s%s",PASTA_TAB_LOCAIS, "\\TST");
					atualizacao_tabs = CopyFile (cmd_str, tabela);
					if(atualizacao_tabs == 0)
						atualizacao_tabs = 1;
				}
			}
			SetBreakOnLibraryErrors (1);
			if(atualizacao_tabs != 1)
			{
				if(ConfirmPopup ("Falha na cópia de tabelas a partir da rede", 
					"Houve um falha na atualização das tabelas de testes e configurações a partir do servidor.\nNÃO é recomendável trabalhar com esta falha. Você deseja prosseguir?")==0)
				{
					return ABORTAR ;		
				}
				atualizacao_tabs = 0;
			}
return 0;
}

/********************** LeIndiceArquivo() *********************************************************/
int LeIndiceArquivo (void)
{
int 
	status,
	i=0, 
	k=0, 
	n=0, 
	file, 
	file1, 
	nMaxItens,
	res;
char	
	choice[25], 
	label[150], 
	item[25], 
	aux[5], 
	arq_modelos[180], 
	

	arq_tabs_rede[256],
	dir_tabs[180];

	
	nMaxItens = 2 ;
	ReplaceListItem ( painel_auto, AUTO_MASCARA, 0, id_model_byte_temp[i], 0);

	for ( i=1; i <= nMaxItens;i++ )
		InsertListItem ( painel_auto, AUTO_MASCARA, -1, id_prefix_enditem_temp[i], i );
	
	//////////////////////////////////////////////////////////////////
	file = OpenFile ( TAB_MODEL_SELECT, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII);

	if ( file < 0 ){
		MessagePopup( " ERRO ", "Erro na abertura do arquivo TAB_MODEL_SELECT" ) ;
		return -1 ;
	}
	
	status = ReadLine ( file, choice, 20 ) ;
	status = ReadLine ( file, item,   20 ) ;
	
	CloseFile( file  ) ;
	
	modelo_atual_index = atoi(item) ;
	if(modelo_atual_index < 0 || modelo_atual_index > MAX_QUANT_MODELOS)
		modelo_atual_index =0;
	SetCtrlIndex ( painel_auto, AUTO_MASCARA, modelo_atual_index ) ;
	return 0 ;
}

/********************** LeEscolheIndiceArquivo() *********************************************************/
int LeEscolheIndiceArquivo (void)
{

int 
	status,
	i=0, 
	file, 
	file1, 
	Num_max_itens, 
	nMaxItens,
	res;
char	
	itemLabel[20],  
	aux[5],
	nome[120]  ;
	
	//////////////////////////////////////////////////////////////
	GetCtrlIndex ( painel_auto, AUTO_MASCARA, &modelo_atual_index ) ;
	
	GetLabelFromIndex ( painel_auto, AUTO_MASCARA, modelo_atual_index, itemLabel ) ;
	Fmt( aux, "%d", modelo_atual_index ) ;
	status = WriteLine( file, aux, strlen(aux) ) ;
	
	CloseFile( file  ) ;
	
	return 0;

}
