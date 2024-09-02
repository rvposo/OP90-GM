#include <windows.h>
#include <rs232.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <userint.h>
#include "SenhaParametros.h"

#include "cvixml.h"
#include "Main OP090 GM-GEM.h"
#include "Auto OP090 GM-GEM.h"
#include "Manual OP090 GM-GEM.h"

#include "CAN GM-GEM.h"

//
// Função: ESC_BAR() 
//
int CVICALLBACK ESC_BAR (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(painel_logo);
			break;
	}
	return 0;
}

//
// Função: LeNSerie1() 
//
int CVICALLBACK LeNSerie1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char
		aux[50];

	switch (event)
	{
		case EVENT_COMMIT:
			
			if( !sair_programa )
			{
				GetCtrlVal (panel, control, aux);
				if(strlen(aux) > 1)
					dados_scanner[SCANNER_1].leu_serial_scanner_manual = ON; //Seta flag leu com o leitor manual
			}	
			break;
			
	}
	return 0;
}

//
// Função: LeNSerie2() 
//
int CVICALLBACK LeNSerie2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char
		aux[50];

	switch (event)
	{
		case EVENT_COMMIT:
			
			if( !sair_programa )
			{
				GetCtrlVal (panel, control, aux);
				if(strlen(aux) > 1)
					dados_scanner[SCANNER_2].leu_serial_scanner_manual = ON; //Seta flag leu com o leitor manual
			}	
			break;
			
	}
	return 0;
}

//
// Função: Manual_Bar() 
//
void CVICALLBACK Manual_Bar (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	if(em_debug == OFF)
		if (ValidarAcesso("Tela Manual")!=0)
			return;
	
	///////////////////////////////////////////////
	///berco_manual = 1;
	///atualizar_mens_can[berco_manual] = ON;
	///////////////////////////////////////////////
	
	modo_manual = ON;
	
	DisplayPanel (painel_manual);

	modo_thread=ESCRITA_E_LEITURA;
	HidePanel (painel_auto);
}

//
// Função: Version_Bar() 
//
void CVICALLBACK Version_Bar (int menuBar, int menuItem, void *callbackData,
		int panel)
{
 	SetCtrlVal (painel_logo,LOGO_BAR_VERSAO , VERSAO); 
	InstallPopup( painel_logo );
}

//
// Função: ZeraProducao() 
//
int CVICALLBACK ZeraProducao (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Zera();
			SetActiveCtrl (painel_auto, AUTO_TXT_SERIE_1);
			SetActiveCtrl (painel_auto, AUTO_TXT_SERIE_2);  
			break;
		}
	return 0;
}

//
// Função: RejeitaMontagemBerco1() 
//
int CVICALLBACK  RejeitaMontagemBerco1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch (event){
		case EVENT_COMMIT:
			dados_berco[BERCO_1].rejeita_montagem = ON;
			break;
	}
	return 0;
}

//
// Função: RejeitaMontagemBerco2() 
//
int CVICALLBACK  RejeitaMontagemBerco2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch (event){
		case EVENT_COMMIT:
			dados_berco[BERCO_2].rejeita_montagem = ON;
			break;
	}
	return 0;
}

//
// Função: Quit_Bar() 
//
void CVICALLBACK Quit_Bar (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	sair_programa = ON;
	QuitUserInterface (EXIT_PROGRAM);

}

//
// Função: CallBack_TEXT() 
//
int CVICALLBACK CallBack_TEXT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	return 0;
}

//
// Função: ColetaDados_Bar() 
//
void CVICALLBACK ColetaDados_Bar (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	GetMenuBarAttribute( menuBar, MENUBAR_MENU2_ITEM1_2, ATTR_CHECKED, &coletando_dados );
	coletando_dados ^= 1;
	SetMenuBarAttribute( menuBar, MENUBAR_MENU2_ITEM1_2, ATTR_CHECKED, coletando_dados );
}


//
// Função: Manual_Fim() 
//
int CVICALLBACK Manual_Fim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel(painel_manual);
			DisplayPanel (painel_auto);
			SetCtrlAttribute (painel_auto, AUTO_TXT_SERIE_1 , ATTR_DIMMED, 0);
			SetActiveCtrl (painel_auto, AUTO_TXT_SERIE_1);
			SetCtrlAttribute (painel_manual, MANUAL_RESETAEMERG , ATTR_CTRL_VAL, OFF);
			SAIDA.Reseta_emerg = OFF;
			modo_manual=OFF;
		
			break;
		}
	return 0;
}

//
// Função: Manual_ThreadSistema() 
//
int CVICALLBACK Manual_ThreadSistema (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		valor;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &valor);
			switch(valor)
			{
				case 0:
					modo_thread=PARAR_ESC_LEIT;
					break;
				case 1:
					modo_thread=LEITURA_APENAS;
					break;
				case 2:
					modo_thread=ESCRITA_E_LEITURA;
					break;
				case 3:
					modo_thread=ESCRITA_APENAS;
					break;
			}
			break;
	}
	return 0;
}

////////////////////////////////////////////////
//       Acoes Segurança/Botoeiras
////////////////////////////////////////////////

//
// Função: Manual_Habilita_emerg() 
//
int CVICALLBACK Manual_Habilita_emerg (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Habilita_emerg = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_Reseta_emerg() 
//
int CVICALLBACK Manual_Reseta_emerg (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Reseta_emerg = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_ResetarEmergencia() 
//
int CVICALLBACK Manual_ResetarEmergencia (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			ResetarEmergencia(OFF);
			break;
		}
	return 0;
}

//
// Função: Manual_TravaPorta() 
//
int CVICALLBACK Manual_TravaPorta (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			Trava(acao);
			break;
	}
	return 0;
}

//
// Função: Manual_ContatoraVibracao() 
//
int CVICALLBACK Manual_ContatoraVibracao (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.ContatoraVibracao = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_Battery_1() 
//
int CVICALLBACK Manual_Battery_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Battery_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_Crank_Run_1() 
//
int CVICALLBACK Manual_Crank_Run_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Crank_Run_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_DIC_SWINPUT_Dig_1() 
//
int CVICALLBACK Manual_DIC_SWINPUT_Dig_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.DIC_SWINPUT_Dig_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_ServiceEngineSoon_1() 
//
int CVICALLBACK Manual_ServiceEngineSoon_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.ServiceEngineSoon_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_VccDireto_Shunt_1() 
//
int CVICALLBACK Manual_VccDireto_Shunt_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.VccDireto_Shunt_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_HabilitaFonte_1() 
//
int CVICALLBACK Manual_HabilitaFonte_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.HabilitaFonte_1 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_PS_Inp_select1() 
//
int CVICALLBACK Manual_PS_Inp_select1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.PS_Inp_select1 = acao;
			break;
	}
	return 0;
}




//
// Função: Manual_Battery_2() 
//
int CVICALLBACK Manual_Battery_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Battery_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_Crank_Run_2() 
//
int CVICALLBACK Manual_Crank_Run_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.Crank_Run_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_DIC_SWINPUT_Dig_2() 
//
int CVICALLBACK Manual_DIC_SWINPUT_Dig_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.DIC_SWINPUT_Dig_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_ServiceEngineSoon_2() 
//
int CVICALLBACK Manual_ServiceEngineSoon_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.ServiceEngineSoon_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_VccDireto_Shunt_2() 
//
int CVICALLBACK Manual_VccDireto_Shunt_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.VccDireto_Shunt_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_HabilitaFonte_2() 
//
int CVICALLBACK Manual_HabilitaFonte_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.HabilitaFonte_2 = acao;
			break;
	}
	return 0;
}

//
// Função: Manual_PS_Inp_select2() 
//
int CVICALLBACK Manual_PS_Inp_select2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &acao);
			SAIDA.PS_Inp_select2 = acao;
			break;
	}
	return 0;
}


/////////////////////////////////////////////
//       Movimentos Manuais Atuadores
/////////////////////////////////////////////

//
// Função: Manual_ClampBerco1() 
//
// Descrição: Executa o movimento manual do Clamp_Berco_1.
//
int CVICALLBACK Manual_ClampBerco1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			MoveClampBerco1(acao);
	}
	return 0;
}

//
// Função: Manual_ClampBerco2() 
//
// Descrição: Executa o movimento manual do Clamp_Berco_2.
//
int CVICALLBACK Manual_ClampBerco2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			MoveClampBerco2(acao);
	}
	return 0;
}

//
// Função: Manual_ConectorBerco1() 
//
// Descrição: Executa o movimento manual do Conector_Berco_1.
//
int CVICALLBACK Manual_ConectorBerco1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			MoveConectorBerco1(acao);
	}
	return 0;
}

//
// Função: Manual_ConectorBerco2() 
//
// Descrição: Executa o movimento manual do Conector_Berco_2.
//
int CVICALLBACK Manual_ConectorBerco2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			MoveConectorBerco2(acao);
	}
	return 0;
}

//
// Função: Manual_Combitac() 
//
// Descrição: Executa o movimento manual do Combitac.
//
int CVICALLBACK Manual_Combitac (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			MoveCombitac(acao);
	}
	return 0;
}

int CVICALLBACK LigaCluster1 (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			TravaLigaCluster1(ON);
			LigarProduto1();
			break;
	}
	return 0;
}

int CVICALLBACK LigaCluster2 (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			TravaLigaCluster2(ON);
			LigarProduto2();
			break;
	}
	return 0;
}

int CVICALLBACK DesligaCluster1 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;
		
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			DesligarProduto1();
			TravaLigaCluster1(OFF);
			break;
	}
	return 0;
}

int CVICALLBACK DesligaCluster2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int
		acao   = 0;
		
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &acao);
			DesligarProduto2();
			TravaLigaCluster2(OFF);
			break;
	}
	return 0;
}







//**********************************Função LeNSerie ***********************************************************************
int CVICALLBACK LeNSerie (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int n,
	berco =1;
	switch (event)
	{
		case EVENT_COMMIT:
		//	if (!modulo_em_teste)
			{
				n = LeBarcode(0,berco);
			}
		//	else
				ResetTextBox (panel, control , "");
				
			break;
	}
	return 0;
}
//*********************************************************************************************************

int CVICALLBACK RejeitaProduto1 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK RejeitaProduto2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Vdut_1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{

int valor=0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &valor);
			switch (valor)
			{
				case 0:
					Set_Vdut(VOLTS_0, 1);
				break;
				case 1:
					Set_Vdut(VOLTS_12_6, 1);
				break;
				case 2:
					Set_Vdut(VOLTS_13_5, 1);	
				break;
				case 3:
					Set_Vdut(VOLTS_15, 1);		
				break;
			}
		break;
	}
	
	return 0;
}

int CVICALLBACK Vdut_2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
int valor = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			 GetCtrlVal(panel, control, &valor);
			switch (valor)
			{
				case 0:
					Set_Vdut(VOLTS_0, 2);
				break;
				case 1:
					Set_Vdut(VOLTS_12_6, 2);
				break;
				case 2:
					Set_Vdut(VOLTS_13_5, 2);	
				break;
				case 3:
					Set_Vdut(VOLTS_15, 2);		
				break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Set_DIC_SW_adj_1 (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
int valor = 0; 

	switch (event)
	{
		case EVENT_COMMIT:
		 GetCtrlVal(panel, control, &valor); 
			switch (valor)
			{
				case 1:
					DIC_SW_adj(R_604, 1);
				break;
				case 2:
					DIC_SW_adj(R_1624,1);	
				break;
				case 3:
					DIC_SW_adj(R_3534, 1);
				break;
				
			}
			break;
	}
	return 0;
}

int CVICALLBACK Set_DIC_SW_adj_2 (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
int valor = 0;   

	switch (event)
	{
		case EVENT_COMMIT:
		 GetCtrlVal(panel, control, &valor); 
			switch (valor)
			{
				case 1:
					DIC_SW_adj(R_604, 2);
				break;
				case 2:
					DIC_SW_adj(R_1624,2);	
				break;
				case 3:
					DIC_SW_adj(R_3534, 2);
				break;
				
			}
			break;
	}
	return 0;
}

int CVICALLBACK Rej_v_1 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			dados_berco[BERCO_1].rejeita_montagem = ON;
			Delay_thread(.1);
			break;
	}
	return 0;
}

int CVICALLBACK Rej_v_2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			dados_berco[BERCO_2].rejeita_montagem = ON;
			Delay_thread(.1);  
			break;
	}
	return 0;
}


///
int CVICALLBACK RejRemoto (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
								   
	switch (event)
		{
		case EVENT_COMMIT:
			rej_remoto = ON;
			Delay_thread(1);
			rej_remoto = OFF;
			break;
		}
return 0; 
}
/*******************ContRemoto() **************************/
int CVICALLBACK ContRemoto (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
								   
	switch (event)
		{
		case EVENT_COMMIT:
			cont_remoto = ON;
			Delay_thread(1);
			cont_remoto = OFF;
			break;
		}
return 0; 
}
/*******************BimanualRemoto() **************************/
int CVICALLBACK BimanualRemoto (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
								   
	switch (event)
		{
		case EVENT_COMMIT:
			bimanual_remoto = ON;
			Delay_thread(1);
			bimanual_remoto = OFF; 
			break;
		}
return 0; 
}

int CVICALLBACK ModeloCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 
			break;
	}
	return 0;
}

int CVICALLBACK MascaraCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LeEscolheIndiceArquivo ();

			break;
	}
	return 0;
}
