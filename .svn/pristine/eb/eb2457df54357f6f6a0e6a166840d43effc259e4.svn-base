#include "Diag GM-Gem.h"
#include <windows.h> 
#include "toolbox.h"
#include <formatio.h>
#include <ansi_c.h>
#include <rs232.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Diag GM-Gem.h"  

#include "cvixml.h"    
#include "Main OP090 GM-GEM.h"  //<---   

#include "CAN GM-Gem.h" 
#include "Manual OP090 GM-GEM.h"  //<---
#include "Auto OP090 GM-GEM.h"  
#include <userint.h>    
#include <NIDAQmx.h> 
#include "DAQ_MX.h" 

long  IDAutomation_Code128b(char *DataToEncode, char *output, long iSize);   

int 
	berco_manual,	
	panel_info_description,
	panel_MTC_description;
char 
	*word_to_str;
//**************************************** TimerManual *******************************************************************
 int CVICALLBACK TimerManual (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

double 
	res;

	
int canal = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute (painel_manual, MANUAL_POWER_MODE , 	ATTR_CTRL_VAL, SysPwrMd[berco_manual].cData[6]);//atualiza info de IGN
			///SetCtrlAttribute (painel_manual, MANUAL_SEND_MENS_CAN, 	ATTR_CTRL_VAL, atualizar_mens_can[berco_manual]);
			canal = 0;
			res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1);
			res = res * 1000;
			SetCtrlVal(painel_manual,MANUAL_G_I,res);
			
			canal = 8;
			res = Vmedio_NIdaq_6210_1ch(canal, -5, 5, TERMIN_CONF_SING_ENDED, 1);
			res = res * 1000;
			SetCtrlVal(painel_manual,MANUAL_G_I_2,res);
		
			break;
	}
	
return 0;
}

//**************************************** Timer_2 *******************************************************************
int CVICALLBACK Timer_2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
				if(ponteiro_logs_can == NULL)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SALVAR_LOG_CAN, ATTR_DIMMED, ON);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SALVAR_LOG_CAN, ATTR_DIMMED, OFF);
				if(modo_diagnostico[berco_manual] == MANTER_DIAG)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_ENTER_DIAG, ATTR_CTRL_VAL, ON);
				else
				{
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_ENTER_DIAG, 	ATTR_CTRL_VAL, OFF);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, 		ATTR_CTRL_VAL, OFF);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_VISTEON,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_CUSTOMER,  ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
				}
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INDEX_ATUAL, 	ATTR_CTRL_VAL, atual_index_live_key[berco_manual]);
				break;
	}
	return 0;
}


/******************************* StartDiag_Customer() ********************************************/
int CVICALLBACK StartDiag_Customer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
double 
	timeout=2,
	t=0;
	
		/////////////////////////////
		switch (event)
		{
		case EVENT_COMMIT:
		
			if(InicializaCAN(can_defin[berco_manual].nome,  can_defin[berco_manual].canal, berco_manual) < 0)
			{
				MessagePopup ("Erro ao tentar resetar CAN",
							  "Houve um erro ao tentar reinicializar o módulo CAN");
				return -1;
			} 
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_VISTEON,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_CUSTOMER,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			qual_diag_atual[berco_manual] 	= NOT_DIAG;
			modo_diagnostico[berco_manual] 	= ENTRAR_DIAG_CUSTOMER;
			t=Timer();
			while(modo_diagnostico[berco_manual] != MANTER_DIAG && Timer()-t<timeout)
				Delay_thread(0.01);
			if(modo_diagnostico[berco_manual] == MANTER_DIAG)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_CUSTOMER,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				qual_diag_atual[berco_manual] = EM_DIAG_CUSTOMER;
			}
			break;
		}
	return 0;
}

			
			
/******************************* StartDiag_Visteon() ********************************************/
int CVICALLBACK StartDiag_Visteon (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
double 
	timeout=2,
	t=0;

		switch (event)
		{
		case EVENT_COMMIT:
		
			
			if(InicializaCAN(can_defin[berco_manual].nome,  can_defin[berco_manual].canal, berco_manual) < 0)
			{
				MessagePopup ("Erro ao tentar resetar CAN",
							  "Houve um erro ao tentar reinicializar o módulo CAN");
				return -1;
			} 
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_VISTEON,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_CUSTOMER,  ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			qual_diag_atual[berco_manual] 	= NOT_DIAG;
			modo_diagnostico[berco_manual] 	= ENTRAR_DIAG_VISTEON;
			t=Timer();
			while(modo_diagnostico[berco_manual] != MANTER_DIAG && Timer()-t<timeout)
				Delay_thread(0.01);
			ResetManual_Controls(OFF, berco_manual);
			if(modo_diagnostico[berco_manual] == MANTER_DIAG)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_VISTEON,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			atual_counts_velo[berco_manual] = 0;
			atual_counts_taco[berco_manual] = 0;
			break;
		}
	return 0;
}


//****************************** ResetManual_Controls() ***************************************************************************
void ResetManual_Controls(int ecu_reset, int berco)
{
		Inicializa_LedsSaidas(berco);
	/*	DIAG_TELLTALES.tt_airbag 			= VAL_TT_AIRBAG_OFF;
		DIAG_TELLTALES.tt_park_brake 		= VAL_TT_PARKBRAKE_OFF;
		DIAG_TELLTALES.tt_abs 				= VAL_TT_ABS_OFF;
		DIAG_TELLTALES.tt_battery			= VAL_TT_BATTERY_OFF;
		DIAG_TELLTALES.tt_se_parkbrake		= VAL_TT_SE_PARKBREAK_OFF;
		DIAG_TELLTALES.tt_coolant_temp 		= VAL_TT_COOLANT_TEMP_OFF;
		DIAG_TELLTALES.tt_cruise_engaged	= VAL_TT_CRUISE_ENGAGED_OFF;
		DIAG_TELLTALES.tt_cruise_on			= VAL_TT_CRUISEON_OFF;
		DIAG_TELLTALES.tt_front_fog 		= VAL_TT_FRONT_FOG_OFF;
		DIAG_TELLTALES.tt_fuel_level_low	= VAL_TT_FUEL_LV_LOW_OFF;					 
		DIAG_TELLTALES.tt_high_beam 		= VAL_TT_HIGH_BEAM_OFF;					 
		DIAG_TELLTALES.tt_light_on 			= VAL_TT_LIGHTON_OFF;					 
		DIAG_TELLTALES.tt_oil_pressure 		= VAL_TT_OIL_PRESSURE_OFF;
		DIAG_TELLTALES.tt_rear_fog 			= VAL_TT_REAR_FOG_OFF;
		DIAG_TELLTALES.tt_seat_belt 		= VAL_TT_SEATBELT_OFF;
		DIAG_TELLTALES.tt_security 			= VAL_TT_SECURITY_OFF;
		DIAG_TELLTALES.tt_serv_eng_soon		= VAL_TT_SERV_ENG_SOON_OFF;
		DIAG_TELLTALES.tt_tire_press_low	= VAL_TT_TIRE_PRESS_LOW_OFF;
		DIAG_TELLTALES.tt_turn_left 		= VAL_TT_TURN_LEFT_OFF;
		DIAG_TELLTALES.tt_turn_right 		= VAL_TT_TURN_RIGHT_OFF;
		DIAG_TELLTALES.tt_esc_off 			= VAL_TT_ESCOFF_OFF;
		DIAG_TELLTALES.tt_esc_service		= VAL_TT_ESC_SERVICE_OFF;
		DIAG_TELLTALES.tt_parking_brake		= VAL_TT_PARKING_BRAKE_OFF;
		DIAG_TELLTALES.tt_press_clutch		= VAL_TT_PRESS_CLUTCH_OFF;
		DIAG_TELLTALES.tt_passeng_seatbelt	= VAL_TT_PASSEN_SEATBELT_OFF;
		DIAG_TELLTALES.tt_traction_cntrl_off= VAL_TT_TRACTION_CONTRL_OFF;
		DIAG_TELLTALES.tt_service_vehi_soon	= VAL_TT_SERV_VEH_SOON_OFF;
		DIAG_TELLTALES.tt_eps				= VAL_TT_EPS_OFF;
		DIAG_TELLTALES.tt_park_assist		= VAL_TT_PARK_ASSIST_OFF;
		DIAG_TELLTALES.tt_glow_plug			= VAL_TT_GLOWPLUG_OFF;
		DIAG_TELLTALES.tt_kmh				= VAL_TT_KMH_OFF;
		DIAG_TELLTALES.tt_mph				= VAL_TT_MPH_OFF;
		DIAG_TELLTALES.tt_pedestrian		= VAL_TT_PEDESTRIAN_OFF;
		DIAG_TELLTALES.tt_lane_kepper_green	= VAL_TT_LANE_KEEP_GREEN_OFF;
		DIAG_TELLTALES.tt_lane_kepper_amber	= VAL_TT_LANE_KEEP_AMBER_OFF;
		DIAG_TELLTALES.tt_track_lead_green	= VAL_TT_TRACK_LEAD_GREEN_OFF;
		DIAG_TELLTALES.tt_track_lead_amber	= VAL_TT_TRACK_LEAD_AMBER_OFF;
		DIAG_TELLTALES.tt_auto_hold_white	= VAL_TT_AUTOHOLD_WHITE_OFF;
		DIAG_TELLTALES.tt_auto_hold_green	= VAL_TT_AUTOHOLD_GREEN_OFF;
		DIAG_OUTPUT.out_fca					= 0;
		DIAG_OUTPUT.out_fca_dn				= 0;
		DIAG_OUTPUT.out_passiv_start_run	= 0;
		DIAG_OUTPUT.out_passiv_start_acc	= 0;
	*/
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERVICO_STATUS, 		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_AIRBAG,			ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_BRAKE, 			ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_ABS, 			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LALTERNADOR, 		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SE_PBRAKE,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HI_TEMP,				ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ENGAGED,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ON,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FRONT_FOG,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LOW_FUEL,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HIGH_BEAM,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LIGHT_ON,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_OIL_PRESSURE,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_REAR_FOG,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT,			ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_ENG_SOON,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TYRE_PRESSURE,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LEFT_TURN,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_RIGHT_TURN,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_OFF,				ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_SERVICE,			ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_BRAKE,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUTCH,				ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASS_SEATBELT,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACTION_CONTROL,	ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_VEH_SOON,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_EPS,					ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARK_ASSIST,			ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GLOW,				ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_KMH,					ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MPH,					ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PEDESTRIAN,			ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_GREEN,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_AMBER,		ATTR_CTRL_VAL ,	OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_GREEN,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_AMBER,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_WHITE,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_GREEN,		ATTR_CTRL_VAL , OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_GAUGE_BACKLIGHT,ATTR_CTRL_VAL , PWM_ILUM_DEFAULT);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_POINT_BACKLIGHT,ATTR_CTRL_VAL , PWM_ILUM_DEFAULT);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_LCD_BACKLIGHT,  ATTR_CTRL_VAL , PWM_ILUM_DEFAULT);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_ILLUM_TELLTALE, ATTR_CTRL_VAL , 100);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_TACO_CUSTOMER,  ATTR_CTRL_VAL , 0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIAG_VELO_CUSTOMER,  ATTR_CTRL_VAL , 0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_COUNTS,				ATTR_CTRL_VAL , 0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGES,				ATTR_CTRL_VAL , 255); //default all
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SPEED,				ATTR_CTRL_VAL , 2);   //default all
		//-------------------------------------------------------	 
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK,  		ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK,  		ATTR_CTRL_VAL ,OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIC_SWITCH,  	ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIC_SWITCH,  	ATTR_CTRL_VAL ,OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START,  	ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START,  	ATTR_CTRL_VAL ,OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT,  	ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT,  	ATTR_CTRL_VAL ,OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG, ATTR_OFF_TEXT 		,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION, ATTR_OFF_TEXT 	,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS, ATTR_CTRL_VAL , OFF);
				
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PN_STATUS, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PN_STATUS, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS, ATTR_OFF_TEXT 			,"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS, ATTR_CTRL_VAL , OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_OFF_TEXT ,			"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_CTRL_VAL ,OFF);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM,  ATTR_OFF_TEXT ,	"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM,  ATTR_CTRL_VAL ,OFF);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY,  	ATTR_OFF_TEXT ,	"---");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY,  	ATTR_CTRL_VAL ,OFF);
			
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_ECU_ID, ATTR_OFF_TEXT ,"---");
		SetCtrlAttribute(panel_CAN_diagnostico,  TELA_DIAG_READ_ECU_ID, ATTR_CTRL_VAL, OFF);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  	ATTR_OFF_TEXT ,"--");
		SetCtrlAttribute(panel_CAN_diagnostico,  TELA_DIAG_FLIP_TACO, 	ATTR_CTRL_VAL, OFF);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  	ATTR_OFF_TEXT ,"--");
		SetCtrlAttribute(panel_CAN_diagnostico,  TELA_DIAG_FLIP_VELO, 	ATTR_CTRL_VAL, OFF);
						   
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  	ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN, ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER, ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE, ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,   	ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  ATTR_OFF_COLOR ,VAL_WHITE);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  	ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN, ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER, ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE, ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,   	ATTR_CTRL_VAL ,OFF);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  ATTR_CTRL_VAL ,OFF);
													  
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE, 	ATTR_OFF_COLOR,	VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE, 	ATTR_ON_COLOR,	VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE,  	ATTR_CTRL_VAL ,	ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVE_ABSOLUTO, 	ATTR_CTRL_VAL ,	ON);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_OUT,			ATTR_CTRL_VAL ,	0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_DN_OUT, 		ATTR_CTRL_VAL ,	0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_RUN_OUT,	ATTR_CTRL_VAL , 0);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_ACC_OUT,	ATTR_CTRL_VAL , 0);
	
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SLEEP_MODE,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_POINTER_PLAC_MODE,	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MEC,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_PN,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MTC,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUSTER_INFO,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LER_NVM,  			ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GRAVAR_NVM,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WHATCH_DOG_TEST, 	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_MASTER_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RET_POINT_STOP,   	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVER,  				ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
																   
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DOWNLOAD_NVM,  	 	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA,  	ATTR_FRAME_COLOR ,	VAL_WHITE);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 			ATTR_DIMMED, ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGE_TABLE_ITEM, 	ATTR_DIMMED, ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, 	ATTR_DIMMED, ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE, 		ATTR_DIMMED, ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,  	ATTR_DIMMED ,ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  		ATTR_DIMMED ,ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  			ATTR_DIMMED ,ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  			ATTR_DIMMED ,ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_TACO,  			ATTR_DIMMED ,ON);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_VELO,  			ATTR_DIMMED ,ON);
		if(!ecu_reset)
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ECU_RESET, 		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
	
		if(!ecu_reset)
			Foto_Display_Diag(DISPLAY_SEGMENTADO, PATTERN_LCD_EOL);
		else
			DeleteImage(panel_CAN_diagnostico, TELA_DIAG_FOTO_DISPLAY);
	
		/*
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_0,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_1,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_2,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_3,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_4,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_5,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_6,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_7,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_8,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_9,  		ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_10,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_11,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_12,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_13,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_14,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_15,  	ATTR_CTRL_VAL , 0x00);
		*/
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_TACO,  	ATTR_CTRL_VAL , 0x00);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_VELO,  	ATTR_CTRL_VAL , 0x00);
		
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, ATTR_CTRL_VAL , "");
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGE_TABLE_ITEM, ATTR_CTRL_VAL , -1);
		if(!ecu_reset)
		{
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_VISTEON,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STARTDIAG_CUSTOMER,  ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
		}
}
			
//****************************** FimDiag() ***************************************************************************
int CVICALLBACK FimDiag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			modo_diagnostico[berco_manual] = NOT_DIAG;
			qual_diag_atual[berco_manual]  = NOT_DIAG;
			Delay_thread(0.01);
			ResetManual_Controls(OFF, berco_manual);
			DeleteImage(panel_CAN_diagnostico, TELA_DIAG_FOTO_DISPLAY);
			break;
		}
		
		return 0;
}

/********************** Clear_Comm_CAN() **************************************************************/
int CVICALLBACK Clear_Comm_CAN (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ResetTextBox (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, "");
			if(monitorar_comm_CAN == ON)
			{
				if(ponteiro_logs_can != NULL)
					strcpy(ponteiro_logs_can,"");
			}
			break;
	}
	return 0;
}

/*************************** Mostrar_Comm_CAN() ******************************************************************/
int CVICALLBACK Mostrar_Comm_CAN (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlAttribute (panel_CAN_diagnostico, control, ATTR_CTRL_VAL, &monitorar_comm_CAN);
			if(monitorar_comm_CAN == ON)
			{
				tempo_inicial_log_CAN = Timer();
				if(ponteiro_logs_can == NULL)
				{
					ponteiro_logs_can = (char *)malloc(MAX_TAM_ARQ_LOG_CAN);
					Fmt(ponteiro_logs_can, "%s<%s%i\n", "Comunicação CAN cluster GM-Gem - Berço Num=", berco_manual);
					strcat(ponteiro_logs_can, "Data(MM-DD-YYYY)=");
					strcat(ponteiro_logs_can, DateStr ());
					strcat(ponteiro_logs_can, " - Hora=");
					strcat(ponteiro_logs_can, TimeStr ());
					strcat(ponteiro_logs_can, "\n");
				}
			}
			break;
	}
	return 0;
}

/*************************** Filtrar_not_diag_CAN() ******************************************************************/
int CVICALLBACK Filtrar_not_diag_CAN (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlAttribute (panel_CAN_diagnostico, control, ATTR_CTRL_VAL, &filtrar_mens_n_diag_CAN);
			break;
	}
return 0;
}
  
/*************************** SalvarLogsCAN() ******************************************************************/
int CVICALLBACK SalvarLogsCAN (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
char 
	nome_arquivo[500];
int
	file_handle,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
	        if (FileSelectPopupEx (PATH_LOG_CAN, "GM-Gem CAN_Log.txt", "*.txt",
								   "Nome do arquivo", VAL_SAVE_BUTTON, 0, 1,
								   nome_arquivo) > 0)
	        {
				file_handle = OpenFile (nome_arquivo, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
				if(file_handle < 0)
				{
					MessagePopup ("Erro ao tentar abrir arquivo",
								  "Houve um erro ao tentar ABRIR arquivo para coleta de dados da comunicação CAN");
					return -1;
				}
				status  = WriteFile (file_handle, ponteiro_logs_can, strlen(ponteiro_logs_can));
				Delay_thread(0.3);
				CloseFile (file_handle);
				if(status < 0)
				{
					MessagePopup ("Erro ao tentar gravar arquivo",
								  "Houve um erro ao tentar GRAVAR arquivo para coleta de dados da comunicação CAN");
					return -1;
				}
				
	        }
			
			break;
	}
return 0;
}
//***************************** Configurar_Monitorar_CAN ***********************************************************
int CVICALLBACK Configurar_Monitorar_CAN (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlAttribute (panel_CAN_diagnostico, control, ATTR_CTRL_VAL, &tipo_monitoramento_CAN);

			break;
	}
	return 0;
}

//***************************** Tela_Diagnostico *******************************************************************
int CVICALLBACK Tela_Diagnostico (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel(panel_CAN_diagnostico);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 			ATTR_DIMMED, ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 			ATTR_DIMMED, ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGE_TABLE_ITEM, 	ATTR_DIMMED, ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, 	ATTR_DIMMED, ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE, 		ATTR_DIMMED, ON);
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SET_MAN_BERCO, &berco_manual);   
	        modo_diagnostico[berco_manual] 		= SAIR_DIAG;
			atualizar_mens_can[berco_manual] 	= ON;
			filtrar_mens_n_diag_CAN				= ON;
			if(ponteiro_logs_can != NULL)
				free(ponteiro_logs_can);
			ponteiro_logs_can					= NULL;
			monitorar_comm_CAN					= OFF;
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_IMP_COMM_CAN, ATTR_CTRL_VAL, OFF);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INDEX_MANUAL, ATTR_CTRL_VAL, manual_index_live_key);
			//////////////////////////////////////////////////////////////////////////////////////
			
			tamanho_nvm[berco_manual] = TAMANHO_NVM; //comando não está respondendo corretamente

			break;
		}
	return 0;
}

//*********************************************************************************************************
int CVICALLBACK Liga_CAN_manual (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &atualizar_mens_can[berco_manual]);
			SetCtrlAttribute (panel,MANUAL_ERROS_CAN , ATTR_DIMMED, !atualizar_mens_can[berco_manual]);
			break;
		}
	return 0;
}

//*********************************************************************************************************
int CVICALLBACK ReinicializaCan (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			
			atualizar_mens_can[berco_manual]= OFF;
			Delay_thread(1);
			InicializaCAN(can_defin[berco_manual].nome,can_defin[berco_manual].canal, berco_manual);
			atualizar_mens_can[berco_manual]	= ON;
			if(ponteiro_logs_can != NULL)
				free(ponteiro_logs_can);	
			ponteiro_logs_can = NULL;
			Delay_thread(0.1);
			break;
		}
	return 0;
}

//*********************************** TacoGauge() **********************************************************************
int CVICALLBACK TacoGauge (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	rpm;
	
	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlVal (painel_manual, MANUAL_TACOGAUGE, &rpm);
			rpm = rpm * 1000;
			SetaMensTaco(rpm, berco_manual);	
			break;
		}
	return 0;
}

//*********************************** VeloGauge() **********************************************************************
int CVICALLBACK VeloGauge (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int velo;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &velo);
			SetaMensVelo(velo, berco_manual);
			break;
		}
	return 0;
}


//*********************************** Live_CruiseEngaged() ****************************************************
int CVICALLBACK Live_CruiseEngaged (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_CRUISE_ENGAGED, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 33, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_CRUISE_ENGAGED, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_CruiseON() *********************************************************
int CVICALLBACK Live_CruiseON (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
int acao=0;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_CRUISE_ON, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 33, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_CRUISE_ON, !acao);
			break;
	}
	return 0;
}

//*********************************** Live_FrontFog() ***********************************************************
int CVICALLBACK Live_FrontFog (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_FRONT_FOG, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 21, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_FRONT_FOG, !acao);

			break;
		}
	return 0;
}

//*********************************** Live_hi_beam() ***********************************************************
int CVICALLBACK Live_hi_beam (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_HIGH_BEAM, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 13, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_HIGH_BEAM, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_rear_fog() ***********************************************************
int CVICALLBACK Live_rear_fog (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_REAR_FOG, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 20, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_LED_REAR_FOG, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_light_on() ***********************************************************
int CVICALLBACK Live_light_on (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIGHT_ON, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 23, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_LIGHT_ON, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_left_turn() ***********************************************************
int CVICALLBACK Live_left_turn (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_LEFT_TURN, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 25, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_LED_LEFT_TURN, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_right_turn() ***********************************************************
int CVICALLBACK Live_right_turn (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_RIGHT_TURN, &acao);
			set_cam_bit(&Exterior_Lighting_HS[berco_manual], Exterior_Lighting_HS[berco_manual].dwID, 27, !acao);	  
			SetCtrlVal (painel_manual, MANUAL_LED_RIGHT_TURN, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_hi_temp() ***********************************************************
int CVICALLBACK Live_hi_temp (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_HI_TEMP, &acao);
			//set_cam_bit(&MMI_ECM_CANHS_RNr_01,0x66A,20,!acao);   //WarningWaterTemp
			SetCtrlVal (painel_manual, MANUAL_HI_TEMP, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_oil() ***********************************************************
int CVICALLBACK Live_oil (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_OIL_PRESSURE, &acao);
			//AcendeLampadaNormalMode(OIL_PRESSURE,acao);
			SetCtrlVal (painel_manual, MANUAL_OIL_PRESSURE, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_Battery() ***********************************************************
int CVICALLBACK Live_Battery (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LALTERNADOR, &acao);
			//set_cam_bit(&MMI_ECM_CANHS_R_02, 0x5DF, 04,!acao); 
			SetCtrlVal (painel_manual, MANUAL_LALTERNADOR, !acao);
			break;
	}
	return 0;
}

//*********************************** Live_brake() ***********************************************************
int CVICALLBACK Live_brake (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
int acao=0; 

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_BRAKE, &acao);
			//set_cam_bit(&MMI_ECM_CANHS_R_02,0x5DF,11,!acao); 
			SetCtrlVal (painel_manual, MANUAL_LED_BRAKE, !acao);
			break;
	}
	return 0;
}

//*********************************** Live_ABS() ***********************************************************
int CVICALLBACK Live_ABS (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_ABS, &acao);
			//AcendeLampadaNormalMode(ABS,!acao);
			SetCtrlVal (painel_manual, MANUAL_LED_ABS, !acao);
			break;  
	
		}
	return 0;
}

//*********************************** Live_airbag() ***********************************************************
int CVICALLBACK Live_airbag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_AIRBAG, &acao);
			set_cam_bit(&Airbag_Indications_19A_M[berco_manual], Airbag_Indications_19A_M[berco_manual].dwID, 56,!acao); 
			set_cam_bit(&Airbag_Indications_198_M[berco_manual], Airbag_Indications_198_M[berco_manual].dwID, 0,!acao); 
			SetCtrlVal (painel_manual, MANUAL_LED_AIRBAG, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_tyre_pressure() ***********************************************************
int CVICALLBACK Live_tyre_pressure (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int acao=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_TYRE_PRESSURE, &acao);
			//set_cam_bit(&MMI_BCM_CANHS_R_01,0x673,10,!acao); 
			SetCtrlVal (painel_manual, MANUAL_TYRE_PRESSURE, !acao);
			break;
	}
	return 0;
}

//*********************************** Live_EPS() ***********************************************************
int CVICALLBACK Live_EPS (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int acao;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_EPS, &acao);
			//AcendeLampadaNormalMode(LED_ESC_OFF,!acao);
			SetCtrlVal (painel_manual, MANUAL_EPS, !acao);
			break;
		}
	return 0;
}

//*********************************** Live_low_fuel() ***********************************************************
int CVICALLBACK Live_low_fuel (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LED_LOW_FUEL, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LED_LOW_FUEL, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_tracklead_green() ***********************************************************
int CVICALLBACK Live_tracklead_green (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_TRACKLEAD_GREEN, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_TRACKLEAD_GREEN, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_tracklead_amber() ***********************************************************
int CVICALLBACK Live_tracklead_amber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_TRACKLEAD_AMBER, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_TRACKLEAD_AMBER, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_autohold_green() ***********************************************************
int CVICALLBACK Live_autohold_green (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_AUTOHOLD_GREEN, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_AUTOHOLD_GREEN, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_autohold_white() ***********************************************************
int CVICALLBACK Live_autohold_white (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_AUTOHOLD_WHITE, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_AUTOHOLD_WHITE, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_line_keeper_amber() ***********************************************************
int CVICALLBACK Live_line_keeper_amber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_LINE_K_AMBER, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_LINE_K_AMBER, !acao);
			break;   
		}	  
	return 0;
}

//*********************************** Live_line_keeper_green() ***********************************************************
int CVICALLBACK Live_line_keeper_green (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_LINE_K_GREEN, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_LINE_K_GREEN, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_pedestrian() ***********************************************************
int CVICALLBACK Live_pedestrian (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_PEDESTRIAN, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_PEDESTRIAN, !acao);
			break;   
		}	  
	return 0;
}

//*********************************** Live_mph() ***********************************************************
int CVICALLBACK Live_mph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_MPH, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_MPH, !acao);
			break;   
		}	  
	return 0;
}

//*********************************** Live_kmh() ***********************************************************
int CVICALLBACK Live_kmh (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_KMH, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_KMH, !acao);
			break;   
		}	  
	return 0;
}
//*********************************** Live_park_asist() ***********************************************************
int CVICALLBACK Live_park_asist (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_PARK_ASSIST, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_PARK_ASSIST, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_service_vehicle_soon() ***********************************************************
int CVICALLBACK Live_service_vehicle_soon (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_SERV_VEH_SOON, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_SERV_VEH_SOON, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_traction_control() ***********************************************************
int CVICALLBACK Live_traction_control (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_TRACTION_CONTROL, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_TRACTION_CONTROL, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_passeng_seatbelt() ***********************************************************
int CVICALLBACK Live_passeng_seatbelt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_PASS_SEATBELT, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_PASS_SEATBELT, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_clutch_to_start() ***********************************************************
int CVICALLBACK Live_clutch_to_start (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_CLUTCH, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_CLUTCH, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_security() ***********************************************************
int CVICALLBACK Live_security (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_SECURITY, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_SECURITY, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_Esc_Service() ***********************************************************
int CVICALLBACK Live_Esc_Service (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_ESC_SERVICE, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_ESC_SERVICE, !acao);
			break;   
		}	  
	return 0;
}		 
  
//*********************************** Live_Esc_Off() ***********************************************************
int CVICALLBACK Live_Esc_Off (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_LIVE_ESC_OFF, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_LIVE_ESC_OFF, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_glow_plug() ***********************************************************
int CVICALLBACK Live_glow_plug (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_GLOW, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_GLOW, !acao);
			break;   
		}	  
	return 0;
}	

//*********************************** Live_service_engine_soon() ***********************************************************
int CVICALLBACK Live_service_engine_soon (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_SERV_ENG_SOON, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_SERV_ENG_SOON, !acao);
			break;   
		}	  
	return 0;
}		 

//*********************************** Live_Parking_brake() ***********************************************************
int CVICALLBACK Live_Parking_brake (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_PARKING_BRAKE, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_PARKING_BRAKE, !acao);
			break;   
		}	  
	return 0;
}


//*********************************** Live_ServiceEletricParkBrake() ***********************************************************
int CVICALLBACK Live_ServiceEletricParkBrake (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_SE_PBRAKE, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_SE_PBRAKE, !acao);
			break;   
		}	  
	return 0;
}		 


//*********************************** Live_SeatBelt() ***********************************************************
int CVICALLBACK Live_SeatBelt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

int acao=0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (painel_manual, MANUAL_SEAT_BELT, &acao);
			
			SetCtrlVal (painel_manual, MANUAL_SEAT_BELT, !acao);
			break;   
		}	  
	return 0;
}		 


int CVICALLBACK BotTemp (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

int CVICALLBACK AllLeds (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &valor);
			if(valor)
			{
			}
			else
			{
			}
			break;
		}
	return 0;
}
 
int CVICALLBACK All_LedsIll (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &valor);
			if(valor)
			{
			}
			else
			{
			}
			break;
		}
	return 0;
}



int CVICALLBACK VerErros_CAN (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
double res = 0;
char res_str[10];

	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel,MANUAL_ERROS_CAN , ATTR_DIMMED, ON);
			SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"...." );
			//res = DiagLinha_CAN(0);//hscan
			Fmt(res_str, "%s<%i",(int)res);
			if(res==CANBUSOFF)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"BUSOFF" );
			else if(res==CANBITWARNING)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"WARNING" );
			else if(res==CANNOTOPENDED)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"CLOSED" );
			else if(res==CANBITDLLRXFULL)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"RXFULL" );
			else if(res==CANBITTX)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"TXERR" );
			else if(res==CANRXOFF)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"RXOFF" );
			else if(res==CANNOTOPENDED)
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,"CLOSED" );
				
			else
				SetCtrlVal (panel,MANUAL_HSCAN_ERR ,res_str );

			break;
		}
	return 0;
}

//**************************** Diag_ecu_reset() ********************************************************************
int CVICALLBACK Diag_ecu_reset (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status;
	
	switch (event)
		{
		case EVENT_COMMIT:
			status = ECU_reset_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ECU_RESET,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				ResetManual_Controls(ON, berco_manual);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ECU_RESET,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	return 0;
}

//**************************** Diag_corrigir_checksum() ********************************************************************
int CVICALLBACK Diag_corrigir_checksum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int
	status;
	
	switch (event)
		{
		case EVENT_COMMIT:
			status = CorrigirChecksum_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CORRIGIR_CHKSUM,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CORRIGIR_CHKSUM,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	return 0;
}

//**************************** Diag_watch_dog_test() ********************************************************************
int CVICALLBACK Diag_watch_dog_test (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status;
	
	switch (event)
		{
		case EVENT_COMMIT:
			status = Whatch_dog_test_Diag(berco_manual);
			if(status == SUCESSO)
			{
				ResetManual_Controls(OFF, berco_manual);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WHATCH_DOG_TEST,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WHATCH_DOG_TEST,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	return 0;
}


//**************************** Diag_cluster_info() ********************************************************************
int CVICALLBACK Diag_cluster_info (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[100],
	tmp_str[100];
	
	switch (event)
		{
		case EVENT_COMMIT:
			
			status = Ler_Registro_status(CLUSTER_INFO, &valor, berco_manual);
			if(status == SUCESSO)
			{
				if(valor < 0x1000)
					Fmt(valor_str, "%s<0%x", valor);
				else
					Fmt(valor_str, "%s<%x", valor);
				StringUpperCase (valor_str);
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM, ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM,  	ATTR_ON_TEXT ,	valor_str);
				Fmt(tmp_str , "%s<%x",  add_table_speed[berco_manual]); 
				StringUpperCase (tmp_str);
				Fmt(valor_str , "%s<%s%s", "Endereço Table=0x", tmp_str); 
				SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 1, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
				Fmt(tmp_str , "%s<%x",  add_table_taco[berco_manual]); 
				StringUpperCase (tmp_str);
				Fmt(valor_str , "%s<%s%s", "Endereço Table=0x", tmp_str); 
				SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 13, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				status = Ler_dados_tabelas_calibracao(OFF, berco_manual);
				if(status == SUCESSO)
				{
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUSTER_INFO,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
					SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CLUSTER_INFO, ON);
					SetCtrlAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 		ATTR_DIMMED, OFF);
					SetCtrlAttribute(panel_CAN_diagnostico, TELA_DIAG_GAUGE_TABLE_ITEM, ATTR_DIMMED, OFF);
					SetCtrlAttribute(panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, ATTR_DIMMED, OFF);
					SetCtrlAttribute(panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE, 	ATTR_DIMMED, OFF);
				}	
				else
				{
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUSTER_INFO,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
				}
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUSTER_INFO,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			
			break;
		}
	return 0;
}
//**************************** Diag_cluster_info_description() ********************************************************************
int CVICALLBACK Diag_cluster_info_description (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
		{
		case EVENT_COMMIT:
			panel_info_description = LoadPanel (0, "Diag GM-Gem.uir", PANEL_INFO);
			DisplayPanel (panel_info_description);
			break;
		}
	return 0;
}
int CVICALLBACK DiagMode1 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			berco_manual = 1;
			DisplayPanel (panel_CAN_diagnostico); 
			break;
	}
	return 0;
}
/*******************Dimming() **************************/
int CVICALLBACK Dimming (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, control, &valor);
			Exterior_Lighting_HS[berco_manual].cData[5] = valor;
			Exterior_Lighting_HS[berco_manual].cData[4] = valor;
			break;
		}
return 0; 
}



 
//**************************** Diag_MTC_description() ********************************************************************
int CVICALLBACK Diag_MTC_description (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
		{
		case EVENT_COMMIT:
			panel_MTC_description = LoadPanel (0, "Diag GM-Gem.uir", PANEL_MTC);
			DisplayPanel (panel_MTC_description);
			break;
		}
	return 0;
}
 
//**************************** CloseClusterInfoDescription() ********************************************************************
int CVICALLBACK CloseClusterInfoDescription (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
		{
		case EVENT_COMMIT:
			DiscardPanel (panel_info_description);
			break;
		}
	return 0;
}

//**************************** Close_MTC_Description() ********************************************************************
int CVICALLBACK Close_MTC_Description (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
		{
		case EVENT_COMMIT:
			DiscardPanel (panel_MTC_description);
			break;
		}
	return 0;
}
//**************************** Fim_Tela_Diag **************************************************************************
int CVICALLBACK Fim_Tela_Diag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch (event)
		{
		case EVENT_COMMIT:
			ResetManual_Controls(OFF, berco_manual);
			DeleteImage(panel_CAN_diagnostico, TELA_DIAG_FOTO_DISPLAY);
			monitorar_comm_CAN = OFF;
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_IMP_COMM_CAN, ATTR_CTRL_VAL, OFF);
			if(dados_berco[berco_manual].modulo_em_teste == OFF)
				modo_diagnostico[berco_manual] = SAIR_DIAG;
			
			HidePanel(panel_CAN_diagnostico);
			Delay_thread(0.5);
			
			ResetTextBox (panel_CAN_diagnostico, TELA_DIAG_RESP_CAN, "");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_0,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_1,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_2,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_3,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_4,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_5,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_6,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_7,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_8,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_9,  		ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_10,  	ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_11,  	ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_12,  	ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_13,  	ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_14,  	ATTR_CTRL_VAL , 0x00);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_15,  	ATTR_CTRL_VAL , 0x00);
			
			
			if(ponteiro_logs_can != NULL)
				free(ponteiro_logs_can);
			ponteiro_logs_can = NULL;
			
			break;
		}
	return 0;
}

//**************************** Diag_rear_fog **************************************************************************
int CVICALLBACK Diag_rear_fog (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_REAR_FOG, &valor);
			status = Acende_lampada_cluster_DIAG(REAR_FOG, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_REAR_FOG, !valor);
			break;
	}
	return 0;
}



//**************************** Diag_SeatBelt **************************************************************************
int CVICALLBACK Diag_SeatBelt (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT, &valor);
			status = Acende_lampada_cluster_DIAG(DRIVER_SEAT_BELT, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT, !valor);
			break;
	}
	return 0;
}

	
	
/*********************** Diag_left_turn() *************************************/
int CVICALLBACK Diag_left_turn (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_LEFT_TURN, &valor);
			status =Acende_lampada_cluster_DIAG(TURN_LEFT, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_LEFT_TURN, !valor);
			break;
	}
	return 0;
}

/*********************** Diag_right_turn() *************************************/
int CVICALLBACK Diag_right_turn (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_RIGHT_TURN, &valor);
			status = Acende_lampada_cluster_DIAG(TURN_RIGHT, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_RIGHT_TURN, !valor);
 			break;
	}
	return 0;
}

   
/*********************** Diag_Esc_Off() *************************************/
int CVICALLBACK Diag_Esc_Off (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_ESC_OFF, &valor);
			status = Acende_lampada_cluster_DIAG(ESC_OFF, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ESC_OFF, !valor);
 			break;
	}
	return 0;
}
	
  
/*********************** Diag_Esc_Service() *************************************/
int CVICALLBACK Diag_Esc_Service (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_ESC_SERVICE, &valor);
			status = Acende_lampada_cluster_DIAG(ESC_SERVICE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ESC_SERVICE, !valor);
 			break;
	}
	return 0;
}

	 
		 
/*********************** Diag_Parking_brake() *************************************/
int CVICALLBACK Diag_Parking_brake (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_PARKING_BRAKE, &valor);
			status = Acende_lampada_cluster_DIAG(PARKING_BRAKE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PARKING_BRAKE, !valor);
 			break;
	}
	return 0;
}
/*********************** Diag_clutch_to_start() *************************************/
int CVICALLBACK Diag_clutch_to_start (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_CLUTCH, &valor);
			status = Acende_lampada_cluster_DIAG(PRESS_CLUTCH_START, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CLUTCH, !valor);
 			break;
	}
	return 0;
}


/*********************** Diag_passeng_seatbelt() *************************************/
int CVICALLBACK Diag_passeng_seatbelt (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_PASS_SEATBELT, &valor);
			status = Acende_lampada_cluster_DIAG(PASSENGER_SEAT_BELT, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PASS_SEATBELT, !valor);
 			break;
	}
	return 0;
}
	 
/*********************** Diag_traction_control() *************************************/
int CVICALLBACK Diag_traction_control (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TRACTION_CONTROL, &valor);
			status = Acende_lampada_cluster_DIAG(TRACTION_CONTROL_OFF, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TRACTION_CONTROL, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_service_vehicle_soon() *************************************/
int CVICALLBACK Diag_service_vehicle_soon (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SERV_VEH_SOON, &valor);
			status = Acende_lampada_cluster_DIAG(SERVIVE_VEHICLE_SOON, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SERV_VEH_SOON, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_park_asist() *************************************/
int CVICALLBACK Diag_park_asist (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_PARK_ASSIST, &valor);
			status = Acende_lampada_cluster_DIAG(PARK_ASSIST, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PARK_ASSIST, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_glow_plug() *************************************/
int CVICALLBACK Diag_glow_plug (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_GLOW, &valor);
			status = Acende_lampada_cluster_DIAG(GLOW_PLUG, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_GLOW, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_kmh() *************************************/
int CVICALLBACK Diag_kmh (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_KMH, &valor);
			status = Acende_lampada_cluster_DIAG(KMH, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_KMH, !valor);
 			break;
	}
	return 0;
}
/*********************** Diag_mph() *************************************/
int CVICALLBACK Diag_mph (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MPH, &valor);
			status = Acende_lampada_cluster_DIAG(MPH, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MPH, !valor);
 			break;
	}
	return 0;
}

   
/*********************** Diag_pedestrian() *************************************/
int CVICALLBACK Diag_pedestrian (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_PEDESTRIAN, &valor);
			status = Acende_lampada_cluster_DIAG(PEDESTRIAN, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PEDESTRIAN, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_line_keeper_green() *************************************/
int CVICALLBACK Diag_line_keeper_green (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LINE_K_GREEN, &valor);
			status = Acende_lampada_cluster_DIAG(LANE_KEEPER_GREEN, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LINE_K_GREEN, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_line_keeper_amber() *************************************/
int CVICALLBACK Diag_line_keeper_amber (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LINE_K_AMBER, &valor);
			status = Acende_lampada_cluster_DIAG(LANE_KEEPER_AMBER, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LINE_K_AMBER, !valor);
 			break;
	}
	return 0;
}
			 
	  
	   
	   
/*********************** Diag_tracklead_green() *************************************/
int CVICALLBACK Diag_tracklead_green (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_GREEN, &valor);
			status = Acende_lampada_cluster_DIAG(TRACKING_LEAD_GREEN, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_GREEN, !valor);
 			break;
	}
	return 0;
}
/*********************** Diag_tracklead_amber() *************************************/
int CVICALLBACK Diag_tracklead_amber (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_AMBER, &valor);
			status = Acende_lampada_cluster_DIAG(TRACKING_LEAD_AMBER, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_AMBER, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_autohold_white() *************************************/
int CVICALLBACK Diag_autohold_white (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_WHITE, &valor);
			status = Acende_lampada_cluster_DIAG(AUTOHOLD_WHITE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_WHITE, !valor);
 			break;
	}
	return 0;
}
/*********************** Diag_autohold_green() *************************************/
int CVICALLBACK Diag_autohold_green (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_GREEN, &valor);
			status = Acende_lampada_cluster_DIAG(AUTOHOLD_GREEN, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_GREEN, !valor);
 			break;
	}
	return 0;
}

	
/*********************** Diag_hi_temp() *************************************/
int CVICALLBACK Diag_hi_temp (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_HI_TEMP, &valor);
			status = Acende_lampada_cluster_DIAG(COOLANT_TEMP, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_HI_TEMP, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_CruiseEngaged() *************************************/
int CVICALLBACK Diag_CruiseEngaged (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ENGAGED, &valor);
			status = Acende_lampada_cluster_DIAG(CRUISE_ENGAGED, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CRUISE_ENGAGED, !valor);
 			break;
	}
	return 0;
}


/*********************** Diag_CruiseON() *************************************/
int CVICALLBACK Diag_CruiseON (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ON, &valor);
			status = Acende_lampada_cluster_DIAG(CRUISE_ON, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CRUISE_ON, !valor);
 			break;
	}
	return 0;
}

 
/*********************** Diag_FrontFog() *************************************/
int CVICALLBACK Diag_FrontFog (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_FRONT_FOG, &valor);
			status = Acende_lampada_cluster_DIAG(FRONT_FOG, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_FRONT_FOG, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_oil() *************************************/
int CVICALLBACK Diag_oil (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_OIL_PRESSURE, &valor);
			status = Acende_lampada_cluster_DIAG(OIL_PRESSURE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_OIL_PRESSURE, !valor);
			break;
	}
	return 0;
}

/********************************* Diag_Battery() *******************************************************/
int CVICALLBACK Diag_Battery (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LALTERNADOR, &valor);
			status = Acende_lampada_cluster_DIAG(BATTERY, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LALTERNADOR, !valor);
 			break;
	}
	return 0;
}

/*********************** Diag_ServiceEletricParkBrake() ***************************************************/
int CVICALLBACK Diag_ServiceEletricParkBrake (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SE_PBRAKE, &valor);
			status = Acende_lampada_cluster_DIAG(SERVICE_ELETRIC_PARK_BRAKE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SE_PBRAKE, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_brake() *******************************************************/
int CVICALLBACK Diag_brake (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_BRAKE, &valor);
			status = Acende_lampada_cluster_DIAG(PARK_BRAKE, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_BRAKE, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_hi_beam() *******************************************************/
int CVICALLBACK Diag_hi_beam (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_HIGH_BEAM, &valor);
			status = Acende_lampada_cluster_DIAG(HI_BEAM, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_HIGH_BEAM, !valor);
 			break;
	}
	return 0;
}


/********************************* Diag_light_on() *******************************************************/
int CVICALLBACK Diag_light_on (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LIGHT_ON, &valor);
			status = Acende_lampada_cluster_DIAG(LIGHTS_ON, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LIGHT_ON, !valor);
 			break;
	}
	return 0;
}

	
   
/********************************* Diag_gauge_backlight() *******************************************************/
int CVICALLBACK Diag_gauge_backlight (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = Ilumination_PWM_DIAG(GAUGE_BACKLIGHT, valor, berco_manual);
 			break;
	}
	return 0;
}

/********************************* Diag_lcd_backlight() *******************************************************/
int CVICALLBACK Diag_lcd_backlight (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = Ilumination_PWM_DIAG(LCD_BACKLIGHT, valor, berco_manual);
 			break;
	}
	return 0;
}
/********************************* Diag_pointers_backlight() *******************************************************/
int CVICALLBACK Diag_pointers_backlight (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = Ilumination_PWM_DIAG(POINTER_BACKLIGHT, valor, berco_manual);
 			break;
	}
	return 0;
}
/********************************* Diag_tt_illumination() *******************************************************/
int CVICALLBACK Diag_tt_illumination(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = Ilumination_PWM_DIAG(TELLTALES_ILL, valor, berco_manual);
 			break;
	}
	return 0;
}


/********************************* Diag_run_crank() *******************************************************/
int CVICALLBACK Diag_run_crank(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK,  ATTR_OFF_TEXT ,"OFF");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK, OFF);
			status = Ler_DI_status(RUN_CRANK, &valor, berco_manual);
			if(valor == ON)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_RUN_CRANK, ON);
 			break;
	}
	return 0;
}

 
/********************************* Diag_dic_switch() *******************************************************/
int CVICALLBACK Diag_dic_switch(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIC_SWITCH,  ATTR_OFF_TEXT ,"OFF");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_DIC_SWITCH, OFF);
			status = Ler_DI_status(DIC_SWITCH, &valor, berco_manual);
			if(valor == ON)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_DIC_SWITCH, ON);
 			break;
	}
	return 0;
}

 
/********************************* Diag_dic_analog() *******************************************************/
int CVICALLBACK Diag_dic_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIC_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_DIC_ANALOG, OFF);
			status = Ler_Analog_status(DIC_ANALOG, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_DIC_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DIC_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_passive_start() *******************************************************/
int CVICALLBACK Diag_passive_start(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START, OFF);
			status = Ler_Analog_status(PASSIVE_START, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASSIVE_START,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_read_FCA_out() *******************************************************/
int CVICALLBACK Diag_read_FCA_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT, OFF);
			status = Ler_Analog_status(FCA_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_read_FCA_DN_out() *******************************************************/
int CVICALLBACK Diag_read_FCA_DN_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT, OFF);
			status = Ler_Analog_status(FCA_DN_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_FCA_DN_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

	
/********************************* Diag_read_passive_start_run_out() *******************************************************/
int CVICALLBACK Diag_read_passive_start_run_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT, OFF);
			status = Ler_Analog_status(PASSIV_START_RUN_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_RUN_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}
	
/********************************* Diag_read_passive_start_IS1_out() *******************************************************/
int CVICALLBACK Diag_read_passive_start_IS1_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT, OFF);
			status = Ler_Analog_status(PASSIV_START_IS1_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS1_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}
/********************************* Diag_read_passive_start_acc_out() *******************************************************/
int CVICALLBACK Diag_read_passive_start_acc_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT, OFF);
			status = Ler_Analog_status(PASSIV_START_ACC_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_ACC_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}
	
/********************************* Diag_read_passive_start_IS2_out() *******************************************************/
int CVICALLBACK Diag_read_passive_start_IS2_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT, OFF);
			status = Ler_Analog_status(PASSIV_START_IS2_OUT, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_PASS_ST_IS2_OUT,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_write_FCA_out() *******************************************************/
int CVICALLBACK Diag_write_FCA_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_OUT, &valor);
			status = Esc_Digital_Output(FCA_OUT, valor, berco_manual);
			if(status != SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_OUT, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_write_FCA_DN_out() *******************************************************/
int CVICALLBACK Diag_write_FCA_DN_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_DN_OUT, &valor);
			status = Esc_Digital_Output(FCA_DN_OUT, valor, berco_manual);
			if(status != SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_WRITE_FCA_DN_OUT, !valor);
 			break;
	}
	return 0;
}

/****************************** Diag_write_passive_start_run_out() ***************************************************/
int CVICALLBACK Diag_write_passive_start_run_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)										
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_RUN_OUT, &valor);
			status = Esc_Digital_Output(PASSIV_START_RUN_OUT, valor, berco_manual);
			if(status != SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_RUN_OUT, !valor);
 			break;
	}
	return 0;
}

/****************************** Diag_write_passive_start_acc_out() ***************************************************/
int CVICALLBACK Diag_write_passive_start_acc_out(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)										
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_ACC_OUT, &valor);
			status = Esc_Digital_Output(PASSIV_START_ACC_OUT, valor, berco_manual);
			if(status != SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_WRITE_PASS_ST_ACC_OUT, !valor);
 			break;
	}
	return 0;
}



/********************************* Diag_battery_voltage() *******************************************************/
int CVICALLBACK Diag_battery_voltage(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE, OFF);
			status = Ler_Analog_status(BATTERY_VOLTAGE, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BATTERY_VOLTAGE,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}
		
/********************************* Diag_pcb_temperature() *******************************************************/
int CVICALLBACK Diag_pcb_temperature(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE, OFF);
			status = Ler_Analog_status(PCB_TEMPERATURE_NTC, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PCB_TEMPERATURE,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}


/********************************* Diag_monitor_5v() *******************************************************/
int CVICALLBACK Diag_monitor_5v(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V, OFF);
			status = Ler_Analog_status(MONITOR_5V, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MONITOR_5V,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_low_fuel_analog() *******************************************************/
int CVICALLBACK Diag_low_fuel_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG, OFF);
			status = Ler_Analog_status(LOW_FUEL_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LOW_FUEL_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_tire_press_analog() *******************************************************/
int CVICALLBACK Diag_tire_press_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG, OFF);
			status = Ler_Analog_status(TIRE_PRESS_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TIRE_PRESS_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_esc_analog() *******************************************************/
int CVICALLBACK Diag_esc_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG, OFF);
			status = Ler_Analog_status(ESC_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_abs_analog() *******************************************************/
int CVICALLBACK Diag_abs_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG, OFF);
			status = Ler_Analog_status(ABS_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ABS_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

	
		 
/********************************* Diag_parking_analog() *******************************************************/
int CVICALLBACK Diag_parking_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG, OFF);
			status = Ler_Analog_status(PARKING_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_brake_analog() *******************************************************/
int CVICALLBACK Diag_brake_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG, OFF);
			status = Ler_Analog_status(BRAKE_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BRAKE_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_airbag_analog() *******************************************************/
int CVICALLBACK Diag_airbag_analog(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG, OFF);
			status = Ler_Analog_status(AIRBAG_AD, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AIRBAG_ANALOG,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

	
/********************************* Diag_Live_key_status() *******************************************************/
int CVICALLBACK Diag_Live_key_status(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY, OFF);
			status = LerStatus_LiveKey(berco_manual);
			if(status == ON)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY, ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY,  ATTR_ON_TEXT ,"ON");
			}
			else
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY, OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_STATUS_LIVE_KEY,  ATTR_OFF_TEXT ,"OFF");
			}
 			break;
	}
	return 0;
}
	
/********************************* Diag_crystal_verification() *******************************************************/
int CVICALLBACK Diag_crystal_verification(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION, OFF);
			status = Ler_Registro_status(CRYSTAL_VERIF, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRYSTAL_VERIFICATION,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_MEC_status() *******************************************************/
int CVICALLBACK Diag_MEC_status(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS, OFF);
			status = Ler_Registro_status(MEC_STATUS, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS, ON);
				Fmt(valor_str, "%s<0x%x", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MEC_STATUS,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}


/********************************* Diag_PN_status() *******************************************************/
int CVICALLBACK Diag_PN_status(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PN_STATUS,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PN_STATUS, OFF);
			status = Ler_Registro_status(PN_STATUS, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_PN_STATUS, ON);
				Fmt(valor_str, "%s<%i", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PN_STATUS,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_MTC_status() *******************************************************/
int CVICALLBACK Diag_MTC_status(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS, OFF);
			status = Ler_Registro_status(MTC_STATUS, &valor, berco_manual);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_CTRL_VAL , OFF);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_OFF_TEXT ,"OK");
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_0,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[0][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_1,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[1][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_2,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[2][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_3,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[3][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_4,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[4][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_5,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[5][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_6,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[6][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_7,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[7][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_8,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[8][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_9,  		ATTR_CTRL_VAL , bytes_resp_CAN_diag[9][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_10,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[10][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_11,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[11][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_12,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[12][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_13,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[13][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_14,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[14][berco_manual]);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_15,  	ATTR_CTRL_VAL , bytes_resp_CAN_diag[15][berco_manual]);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MTC_STATUS,  ATTR_OFF_TEXT ,"ERROR");
			}
 			break;
	}
	return 0;
}

    
/********************************* Diag_sw_version() *******************************************************/
int CVICALLBACK Diag_sw_version(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM, OFF);
			status = Ler_Registro_status(SW_STATUS, &valor, berco_manual);
			if(status == SUCESSO)
			{
			
				sprintf(valor_str, "%06x", valor);
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM, ON);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SW_VERSION_INFORM,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_base_status() *******************************************************/
int CVICALLBACK Diag_base_status(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS,  ATTR_OFF_TEXT ,"---");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS, OFF);
			status = Ler_Registro_status(BASE_STATUS, &valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS, ON);
				Fmt(valor_str, "%s<%i", valor);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_BASE_STATUS,  ATTR_ON_TEXT ,valor_str);
			}
 			break;
	}
	return 0;
}

  

/********************************* Diag_enable_gauge() *******************************************************/
int CVICALLBACK Diag_enable_gauge(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE, &valor);
			status = Enable_gauge_Diag(valor, berco_manual);
			if(status == SUCESSO)
			{
				if(valor)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE, ATTR_ON_COLOR,		VAL_GREEN);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE, ATTR_OFF_COLOR,	VAL_GREEN);
			}
			else
			{
				if(valor)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE,  ATTR_ON_COLOR ,	VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ENABLE_GAUGE,  ATTR_OFF_COLOR ,	VAL_RED);
			}
 			break;
	}
	return 0;
}
   
/********************************* Diag_SleepMode() *******************************************************/
int CVICALLBACK Diag_SleepMode(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			status = EnterSleepMode_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SLEEP_MODE,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_PointerReturnStopPosition() *******************************************************/
int CVICALLBACK Diag_PointerReturnStopPosition(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,	ATTR_DIMMED ,	ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,			ATTR_DIMMED ,	ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,			ATTR_DIMMED ,	ON);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,			ATTR_DIMMED ,	ON);
			status = ReturnPointersStop_Diag(berco_manual, OFF);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RET_POINT_STOP,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,ATTR_DIMMED ,	OFF);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RET_POINT_STOP,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
 			break;
	}
	return 0;
}
		 
 
/********************************* Diag_Init_Flip_Detect() *******************************************************/
int CVICALLBACK Diag_Init_Flip_Detect(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			status = Flip_Detect_Diag(GAUGES_ALL, ON, OFF, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INIT_FLIP_DETECT,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  	ATTR_DIMMED ,	OFF);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_Flip_Detect() *******************************************************/
int CVICALLBACK Diag_Flip_Detect(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	gauges;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGES,		 ATTR_CTRL_VAL, &gauges);
			Delay_thread(0.100);
			
			status = Flip_Detect_Diag(gauges, OFF, OFF, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT, ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				if(gauges == GAUGE_TACOMETRO || gauges == GAUGES_ALL) 
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  	ATTR_DIMMED ,	OFF);
				if(gauges == GAUGE_VELOCIMETRO || gauges == GAUGES_ALL) 
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  	ATTR_DIMMED ,	OFF);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_DETECT,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_flip_taco() *******************************************************/
int CVICALLBACK Diag_flip_taco(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  ATTR_OFF_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  ATTR_OFF_TEXT ,"--");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO, OFF);
			status = Flip_Detect_Diag(GAUGE_TACOMETRO, OFF, ON, berco_manual);
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO, ON);
			if(status == SUCESSO)
			{
				Fmt(valor_str, "%s<%i", dados_rotor_offset[berco_manual].taco_flip_value);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  	ATTR_ON_TEXT ,	valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  	ATTR_ON_COLOR,	VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_TACO,  	ATTR_DIMMED ,	OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_TACO,  	ATTR_CTRL_VAL,	dados_rotor_offset[berco_manual].taco_rotor_value);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_TACO,  ATTR_ON_COLOR ,VAL_RED);
			}
			Delay_thread(0.010);
 			break;
	}
	return 0;
}

/********************************* Diag_flip_velo() *******************************************************/
int CVICALLBACK Diag_flip_velo(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50];

	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  ATTR_OFF_COLOR ,VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  ATTR_OFF_TEXT ,"--");
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO, OFF);
			status = Flip_Detect_Diag(GAUGE_VELOCIMETRO, OFF, ON, berco_manual);
			SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO, ON);
			if(status == SUCESSO)
			{
				Fmt(valor_str, "%s<%i", dados_rotor_offset[berco_manual].velo_flip_value);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  	ATTR_ON_TEXT ,	valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  	ATTR_ON_COLOR,	VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_VELO,  	ATTR_DIMMED ,	OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_RO_VELO,  	ATTR_CTRL_VAL,	dados_rotor_offset[berco_manual].velo_rotor_value);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FLIP_VELO,  ATTR_ON_COLOR ,VAL_RED);
			}
			Delay_thread(0.010);
 			break;
	}
	return 0;
}

/********************************* Diag_PointerPlacementMode() *******************************************************/
int CVICALLBACK Diag_PointerPlacementMode(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			status = EnterPointerPlacMode_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_POINTER_PLAC_MODE,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
 			break;
	}
	return 0;
}
		 
/********************************* Diag_programar_MEC() *******************************************************/
int CVICALLBACK Diag_programar_MEC(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MEC,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			status = Programar_MEC_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MEC,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MEC,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
 			break;
	}
	return 0;
}



/********************************* Diag_programar_PN() *******************************************************/
int CVICALLBACK Diag_programar_PN(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

unsigned long
	valor=0;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_PN,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_CUSTOMER_PN, &valor);
			
			status = Programar_PN_Diag(valor, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_PN,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_PN,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
 			break;
	}
	return 0;
}
/********************************* Diag_programar_MTC() *******************************************************/
int CVICALLBACK Diag_programar_MTC(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

unsigned char
	valor=0;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MTC,  		ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_0, &valor);
			envio_can[berco_manual].dados_can[0] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_1, &valor);
			envio_can[berco_manual].dados_can[1] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_2, &valor);
			envio_can[berco_manual].dados_can[2] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_3, &valor);
			envio_can[berco_manual].dados_can[3] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_4, &valor);
			envio_can[berco_manual].dados_can[4] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_5, &valor);
			envio_can[berco_manual].dados_can[5] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_6, &valor);
			envio_can[berco_manual].dados_can[6] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_7, &valor);
			envio_can[berco_manual].dados_can[7] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_8, &valor);
			envio_can[berco_manual].dados_can[8] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_9, &valor);
			envio_can[berco_manual].dados_can[9] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_10, &valor);
			envio_can[berco_manual].dados_can[10] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_11, &valor);
			envio_can[berco_manual].dados_can[11] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_12, &valor);
			envio_can[berco_manual].dados_can[12] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_13, &valor);
			envio_can[berco_manual].dados_can[13] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_14, &valor);
			envio_can[berco_manual].dados_can[14] = valor;
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MTC_15, &valor);
			envio_can[berco_manual].dados_can[15] = valor;
			
			status = Programar_MTC_Diag(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MTC,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PROGRAMAR_MTC,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
 			break;
	}
	return 0;
}

/********************************* Diag_Padrao_display() *******************************************************/
int CVICALLBACK Diag_Padrao_display(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	model;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_MODELO_DISPLAY, &model);
			if(model < 1 || model > 3)
			{
				MessagePopup ("Erro ao acionar padrão de display",
							  "Modelo de display não definido. Selecione um modelo");
				return -1;
			}
			switch(model)
			{
				case 1:
					modelo_display[berco_manual] = DISPLAY_SEGMENTADO;
					break;
				case 2:
					modelo_display[berco_manual] = DISPLAY_TFT_MONO;
					break;
				case 3:
					modelo_display[berco_manual] = DISPLAY_TFT_COLOR;
					break;
			}
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_NUM_PADRAO, &valor);
			if(modelo_display[berco_manual] == DISPLAY_SEGMENTADO && valor > 3)
			{
				MessagePopup ("Erro ao acionar padrão de display",
							  "O padrão de display selecionado só está disponível para modelos com TFT.\nPara modelo SEGMENTADO só padrões AllOff e AllOn");
				return -1;
			}
			if(modelo_display[berco_manual] != DISPLAY_TFT_COLOR && valor > 3)
			{
				MessagePopup ("Erro ao acionar padrão de display",
							  "O padrão de display selecionado só está disponível para modelo de display TFT Colorido");
				return -1;
			}
			Foto_Display_Diag(modelo_display[berco_manual], valor);
			////////////////////////////////////////////////////		
			if(	Display_pattern_CAN (valor, berco_manual) < 0)
				return -1;
		
			break;
	  }   
return 0;
}			

/********************************* Diag_security() *******************************************************/
int CVICALLBACK Diag_security (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SECURITY, &valor);
			status = Acende_lampada_cluster_DIAG(SECURITY, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SECURITY, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_ABS() *******************************************************/
int CVICALLBACK Diag_ABS (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_ABS, &valor);
			status = Acende_lampada_cluster_DIAG(ABS, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_ABS, !valor);
			break;
	}
	return 0;
}

/********************************* Diag_airbag() *******************************************************/
int CVICALLBACK Diag_airbag (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_AIRBAG, &valor);
			status = Acende_lampada_cluster_DIAG(AIRBAG, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_AIRBAG, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_service_engine_soon() *******************************************************/
int CVICALLBACK Diag_service_engine_soon (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_SERV_ENG_SOON, &valor);
			status = Acende_lampada_cluster_DIAG(SERVICE_ENGINE_SOON, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_SERV_ENG_SOON, !valor);
 			break;
	}
	return 0;
}

/********************************* Diag_tyre_pressure() *******************************************************/
int CVICALLBACK Diag_tyre_pressure (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TYRE_PRESSURE, &valor);
			status = Acende_lampada_cluster_DIAG(TIRE_PRESSURE_LOW, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_TYRE_PRESSURE, !valor);
			break;
	}
	return 0;
}

/********************************* Diag_EPS() *******************************************************/
int CVICALLBACK Diag_EPS (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;  	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_EPS, &valor);
			status = Acende_lampada_cluster_DIAG(EPS, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_EPS, !valor);
			break;
	}
	return 0;
}

/********************************* Diag_low_fuel() *******************************************************/
int CVICALLBACK Diag_low_fuel (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_LED_LOW_FUEL, &valor);
			status = Acende_lampada_cluster_DIAG(FUEL_LEVEL_LOW, !valor, berco_manual);
			if(status == SUCESSO)
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_LED_LOW_FUEL, !valor);
			break;
	}
	return 0;
}


/********************************* Telltales_all_red() *******************************************************/
int CVICALLBACK Telltales_all_red (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, valor, berco_manual);
			if(status == SUCESSO)
			{
					MostraGroupLeds_Status(ALL_TELLTALES_RED, valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  	ATTR_OFF_COLOR,VAL_RED);
			}
			break;
	}
	return 0;
}

/********************************* Telltales_all_green() *******************************************************/
int CVICALLBACK Telltales_all_green (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, valor, berco_manual);
			if(status == SUCESSO)
			{
					MostraGroupLeds_Status(ALL_TELLTALES_GREEN, valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}

/********************************* Telltales_all_amber() *******************************************************/
int CVICALLBACK Telltales_all_amber (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, valor, berco_manual);
			if(status == SUCESSO)
			{
					MostraGroupLeds_Status(ALL_TELLTALES_AMBER, valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}

/********************************* Telltales_all_white() *******************************************************/
int CVICALLBACK Telltales_all_white (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, valor, berco_manual);
			if(status == SUCESSO)
			{
				MostraGroupLeds_Status(ALL_TELLTALES_WHITE, valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}

/********************************* Telltales_all_blue() *******************************************************/
int CVICALLBACK Telltales_all_blue (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE, valor, berco_manual);
			if(status == SUCESSO)
			{
				MostraGroupLeds_Status(ALL_TELLTALES_BLUE, valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}

/********************************* Telltales_all() *******************************************************/
int CVICALLBACK Telltales_all (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL, &valor);
			status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_RED, valor, berco_manual);
			if(status == SUCESSO)
				status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_GREEN, valor, berco_manual);
			if(status == SUCESSO)
				status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_AMBER, valor, berco_manual);
			if(status == SUCESSO)
				status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_WHITE, valor, berco_manual);
			if(status == SUCESSO)
				status = Acende_lampada_cluster_DIAG(ALL_TELLTALES_BLUE,  valor, berco_manual);
			if(status == SUCESSO)
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,  	ATTR_ON_COLOR ,VAL_GREEN);
				MostraGroupLeds_Status(ALL_TELLTALES_RED,   valor);
				MostraGroupLeds_Status(ALL_TELLTALES_GREEN, valor);
				MostraGroupLeds_Status(ALL_TELLTALES_AMBER, valor);
				MostraGroupLeds_Status(ALL_TELLTALES_WHITE, valor);
				MostraGroupLeds_Status(ALL_TELLTALES_BLUE,  valor);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}


/********************************* Telltales_display_customer() *******************************************************/
int CVICALLBACK Telltales_display_customer (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int
	valor,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST, &valor);
			status = LedsDisplay_Customer_DIAG(valor, berco_manual);
			if(status == SUCESSO)
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  	ATTR_ON_COLOR ,VAL_GREEN);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  	ATTR_OFF_COLOR ,VAL_GREEN);
			}
			else
			{
				if(valor == ON)
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  	ATTR_ON_COLOR ,VAL_RED);
				else
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLT_DISPLAY_CUST,  	ATTR_OFF_COLOR ,VAL_RED);
			}
			
			break;
	}
	return 0;
}

/********************************* Diag_tacometro_customer() *******************************************************/
int CVICALLBACK Diag_tacometro_customer (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
		//case EVENT_KEYPRESS:
			if(event == EVENT_KEYPRESS)
			{
				if(GetKeyPressEventVirtualKey (eventData2) != VAL_ENTER_VKEY)
					return 0;
			}
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = SetTacometroCustomer_DIAG(valor,berco_manual);
			break;
	}
	return 0;
}

/********************************* Diag_mover_gauges_eol_visteon() *******************************************************/
int CVICALLBACK Diag_mover_gauges_eol_visteon (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int counts,
	gauges,
	status,
	val_absoluto,
	torque,
	speed;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVER,  	ATTR_CMD_BUTTON_COLOR ,VAL_WHITE);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVE_ABSOLUTO, 	ATTR_CTRL_VAL, &val_absoluto);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TORQUE, 			ATTR_CTRL_VAL, &torque);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SPEED, 			ATTR_CTRL_VAL, &speed);//cuidado - Speed menor que 166 para movimento absoluto os ponteiros não funcionam
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_COUNTS,			ATTR_CTRL_VAL, &counts);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGES,			ATTR_CTRL_VAL, &gauges);
			if(gauges == GAUGES_ALL)
			{
				status = SetGauge_eol_visteon_DIAG(counts, GAUGE_TACOMETRO, 	val_absoluto, torque, speed, OFF, berco_manual);
				status = SetGauge_eol_visteon_DIAG(counts, GAUGE_VELOCIMETRO, 	val_absoluto, torque, speed, ON, berco_manual);
			}
			else
			{
				status = SetGauge_eol_visteon_DIAG(counts, gauges, 	val_absoluto, torque, speed, ON, berco_manual);
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVER,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MOVER,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
	}
	return 0;
}


/********************************* Diag_velocimetro_customer() *******************************************************/
int CVICALLBACK Diag_velocimetro_customer (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
int valor=0,
	status;

	switch (event)
	{
		case EVENT_COMMIT:
		//case EVENT_KEYPRESS:
			if(event == EVENT_KEYPRESS)
			{
				if(GetKeyPressEventVirtualKey (eventData2) != VAL_ENTER_VKEY)
					return 0;
			}
			GetCtrlVal (panel_CAN_diagnostico, control, &valor);
			status = SetVelocimetroCustomer_DIAG(valor, berco_manual);
			break;
	}
	return 0;
}

/*************************** LeNVM_Diag() ******************************************************************/
int CVICALLBACK LeNVM_Diag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50];
unsigned char
	quantos_bytes;
unsigned long
	end_inicial;

	switch (event)
		{
		case EVENT_COMMIT:
			
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ADD_INICIAL, 		ATTR_CTRL_VAL, 			&end_inicial);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_QUANTOS_BYTES, 		ATTR_CTRL_VAL, 			&quantos_bytes);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LER_NVM,  			ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_1,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_2,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_3,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_4,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_5,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_6,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_7,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_8,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_9,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_10,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_11,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_12,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_13,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_14,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_15,  			ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_16,  			ATTR_CTRL_VAL ,	"");
			
			status = Ler_BytesNVM_Diag(end_inicial, quantos_bytes, ON, berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LER_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				if(bytes_resp_CAN_diag[0][berco_manual] < 0x10)
					Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[0][berco_manual]);
				else
					Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[0][berco_manual]);
				StringUpperCase (valor_str);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_1,  	ATTR_CTRL_VAL ,	valor_str);
				if(quantos_bytes > 1)
				{
					if(bytes_resp_CAN_diag[1][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[1][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[1][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_2,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 2)
				{
					if(bytes_resp_CAN_diag[2][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[2][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[2][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_3,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 3)
				{
					if(bytes_resp_CAN_diag[3][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[3][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[3][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_4,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 4)
				{
					if(bytes_resp_CAN_diag[4][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[4][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[4][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_5,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 5)
				{
					if(bytes_resp_CAN_diag[5][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[5][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[5][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_6,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 6)
				{
					if(bytes_resp_CAN_diag[6][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[6][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[6][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_7,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 7)
				{
					if(bytes_resp_CAN_diag[7][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[7][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[7][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_8,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 8)
				{
					if(bytes_resp_CAN_diag[8][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[8][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[8][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_9,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 9)
				{
					if(bytes_resp_CAN_diag[9][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[9][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[9][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_10,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 10)
				{
					if(bytes_resp_CAN_diag[10][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[10][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[10][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_11,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 11)
				{
					if(bytes_resp_CAN_diag[11][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[11][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[11][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_12,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 12)
				{
					if(bytes_resp_CAN_diag[12][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[12][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[12][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_13,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 13)
				{
					if(bytes_resp_CAN_diag[13][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[13][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[13][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_14,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 14)
				{
					if(bytes_resp_CAN_diag[14][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[14][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[14][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_15,  	ATTR_CTRL_VAL ,	valor_str);
				}
				if(quantos_bytes > 15)
				{
					if(bytes_resp_CAN_diag[15][berco_manual] < 0x10)
						Fmt(valor_str, "%s<0%x", bytes_resp_CAN_diag[15][berco_manual]);
					else
						Fmt(valor_str, "%s<%x", bytes_resp_CAN_diag[15][berco_manual]);
					StringUpperCase (valor_str);
					SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_16,  	ATTR_CTRL_VAL ,	valor_str);
				}
				
				
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LER_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
return 0;
}


/*************************** Diag_clear_bytes_NVM() ******************************************************************/
int CVICALLBACK Diag_clear_bytes_NVM (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_1,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_2,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_3,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_4,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_5,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_6,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_7,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_8,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_9,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_10,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_11,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_12,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_13,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_14,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_15,  		ATTR_CTRL_VAL ,	"");
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_16,  		ATTR_CTRL_VAL ,	"");
			break;
		}
return 0;
}


/*************************** Diag_Download_NVM() ******************************************************************/
int CVICALLBACK Diag_Download_NVM (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;
char
	valor_str[50];
unsigned int
	dado_word;

	switch (event)
		{
		case EVENT_COMMIT:
			
			tamanho_nvm[berco_manual] = TAMANHO_NVM; //comando p/ ler via DIAG não está respondendo corretamente
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DOWNLOAD_NVM,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			if(ConfirmPopup ("Confirmar download da NVM",
						  "Você confirma que deseja fazer o download de toda a NVM do cluster?") != 1)
				return -1;
			status = Ler_toda_NVM(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DOWNLOAD_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DOWNLOAD_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	
return 0;
}


/*************************** Diag_Write_live_key_alternativo() ******************************************************************/
int CVICALLBACK Diag_Write_live_key_alternativo (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status = RES_FALHA,
	item;
char
	valor_str[50];

	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA,  	ATTR_FRAME_COLOR ,	VAL_WHITE);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA, 	ATTR_CTRL_VAL, 		&item);
			switch(item)
			{
				case 0xFF:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de MASTER Key",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do MASTER KEY(One Shot)?") == 1)
							status = Gravar_Master_Key(berco_manual);
					break;
				case 1:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de UNLOCK Key",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do UNLOCK KEY(One Shot)?") == 1)
							status = Gravar_Unlock_Key(berco_manual);
					break;
				case 2:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 2",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 2?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY2, berco_manual);
					break;
				case 3:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 3",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 3?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY3, berco_manual);
					break;
				case 4:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 4",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 4?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY4, berco_manual);
					break;
				case 5:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 5",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 5?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY5, berco_manual);
					break;
				case 6:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 6",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 6?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY6, berco_manual);
					break;
				case 7:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 7",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 7?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY7, berco_manual);
					break;
				case 8:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 8",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 8?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY8, berco_manual);
					break;
				case 9:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 9",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 9?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY9, berco_manual);
					break;
				case 10:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 10",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 10?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY10, berco_manual);
					break;
				case 11:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 11",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 11?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY11, berco_manual);
					break;
				case 12:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 12",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 12?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY12, berco_manual);
					break;
				case 13:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 13",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 13?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY13, berco_manual);
					break;
				case 14:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 14",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 14?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY14, berco_manual);
					break;
				case 15:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 15",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 15?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY15, berco_manual);
					break;
				case 16:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 16",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 16?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY16, berco_manual);
					break;
				case 17:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 17",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 17?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY17, berco_manual);
					break;
				case 18:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 18",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 18?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY18, berco_manual);
					break;
				case 19:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 19",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 19?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY19, berco_manual);
					break;
				case 20:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Key 20",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do GENERAL KEY 20?") == 1)
							status = Gravar_General_Key(WRITE_GENERAL_KEY20, berco_manual);
					break;
				case 21:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL do ECU-ID",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL do ECU-ID?") == 1)
							status = Gravar_ECU_ID(berco_manual);
					break;
				case 22:
					if(ConfirmPopup ("Confirmar GRAVAÇÃO INDIVIDUAL de general Keys",
								  "Você confirma que deseja fazer a gravação INDIVIDUAL de GENERAL KEYS de 2 a 20?") == 1)
							status = GravaSequencia_general_keys(berco_manual);
					break;
				default:
					break;
			}
			if(status == RES_FALHA)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA,  	 ATTR_FRAME_COLOR ,	VAL_WHITE);
			else if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA,  	 ATTR_FRAME_COLOR ,	VAL_GREEN);
				status = LerIndexar_arq_index_LiveKey(ON, berco_manual);
			}
			else
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ALTERNATIVA,  	 ATTR_FRAME_COLOR ,	VAL_RED);
			break;
		}
	
return 0;
}

/*************************** Diag_Write_Master_Key() ******************************************************************/
int CVICALLBACK Diag_Write_Master_Key (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;
char
	valor_str[50];

	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_MASTER_KEY,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			if(ConfirmPopup ("Confirmar GRAVAÇÃO de MASTER Key",
						  "Você confirma que deseja fazer a gravação do MASTER KEY(One Shot)?") != 1)
				return -1;
			status = LerIndexar_arq_index_LiveKey(ON, berco_manual);
			
			status = Gravar_Master_Key(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_MASTER_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	ATTR_DIMMED ,OFF);
			}
			else
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_MASTER_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			break;
		}
	
return 0;
}

/*************************** Diag_Write_Unlock_Key() ******************************************************************/
int CVICALLBACK Diag_Write_Unlock_Key (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;
char
	valor_str[50];

	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			if(ConfirmPopup ("Confirmar GRAVAÇÃO de UNLOCK Key",
						  "Você confirma que deseja fazer a gravação do UNLOCK KEY(One Shot)?") != 1)
				return -1;

			status = LerIndexar_arq_index_LiveKey(ON, berco_manual);
			
			status = Gravar_Unlock_Key(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_UNLOCK_KEY,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	
return 0;
}

/*************************** Diag_Write_ECU_ID() ******************************************************************/
int CVICALLBACK Diag_Write_ECU_ID (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;
char
	valor_str[50];

	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			if(ConfirmPopup ("Confirmar GRAVAÇÃO de ECU-ID",
						  "Você confirma que deseja fazer a gravação do ECU-ID?") != 1)
				return -1;
			status = LerIndexar_arq_index_LiveKey(ON, berco_manual);

			status = Gravar_ECU_ID(berco_manual);
			if(status == SUCESSO)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			else
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_ECU_ID,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			break;
		}
	
return 0;
}

 	 
/********************************* Diag_ler_ECU_ID() *******************************************************/
int CVICALLBACK Diag_ler_ECU_ID(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_ECU_ID,  ATTR_OFF_TEXT ,"---");
			SetCtrlAttribute(panel_CAN_diagnostico,  TELA_DIAG_READ_ECU_ID,  ATTR_CTRL_VAL, OFF);
			status = Ler_ECU_ID(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlVal(panel_CAN_diagnostico, TELA_DIAG_READ_ECU_ID, ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_READ_ECU_ID,  ATTR_ON_TEXT ,dados_live_key[berco_manual].ecu_id_lido);
			}
 			break;
	}
	return 0;
}

/*************************** Index_manual_livekey() ******************************************************************/
int CVICALLBACK Index_manual_livekey (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_INDEX_MANUAL, ATTR_CTRL_VAL, &manual_index_live_key);
			status = LeDados_ASC_LiveKey( manual_index_live_key, berco_manual);
			break;
		}
	
return 0;
}

 /*************************** Diag_Write_General_Keys() ******************************************************************/
int CVICALLBACK Diag_Write_General_Keys (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50],
	tmp[100];

	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			if(ConfirmPopup ("Confirmar GRAVAÇÃO de general Keys",
						  "Você confirma que deseja fazer a gravação do GENERAL KEYS de 2 a 20?") != 1)
				return -1;
			status = LerIndexar_arq_index_LiveKey(ON, berco_manual);
			
			status = GravaSequencia_general_keys(berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_WRITE_GENERAL_KEYS,  ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	
return 0;
}


/*************************** Diag_Update_table() ******************************************************************/
int CVICALLBACK Diag_Update_table (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status,
	item;
char
	valor_str[50];
unsigned int
	dado_word;

	switch (event)
		{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE,  	 ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GAUGE_TABLE_ITEM, ATTR_CTRL_VAL, &item);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, ATTR_CTRL_VAL ,valor_str);
			status = Fmt(&dado_word, "%x<%s", valor_str);
			if(status < 1)
			{
				MessagePopup ("Erro setup para UPDATE de dados nas tabelas de calibração",
							  "Erro setup para UPDATE de dados nas tabelas de calibração. Valor do dado é inválido");
				return -1;
			}
			status = Fmt(valor_str, "%s<%x", dado_word); //mostrar ao usuario o valor após leitura do dado pelo CVI
			StringUpperCase (valor_str);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TABLE_ITEM_VALUE, ATTR_CTRL_VAL ,valor_str);
			if(item < 0 || item > 35)
			{
				MessagePopup ("Erro setup para UPDATE de dados nas tabelas de calibração",
							  "Erro setup para UPDATE de dados nas tabelas de calibração. Item da tabela não definido");
				return -1;
			}
			
			status = Esc_Table_DataWord(item, dado_word ,berco_manual);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_UPDATE_TABLE,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
	
return 0;
}

/*************************** Diag_gravar_bytes_NVM() ******************************************************************/
int CVICALLBACK Diag_gravar_bytes_NVM (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50];
unsigned char
	quantos_bytes;
unsigned long
	end_inicial;
unsigned int
	dado_byte;

	switch (event)
		{
		case EVENT_COMMIT:
			
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ADD_INICIAL, 		ATTR_CTRL_VAL, 			&end_inicial);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_QUANTOS_BYTES, 		ATTR_CTRL_VAL, 			&quantos_bytes);
			SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GRAVAR_NVM,  		ATTR_CMD_BUTTON_COLOR ,	VAL_WHITE);
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_1,  			ATTR_CTRL_VAL ,	valor_str);
			ResetaBytesEnvio_CAN(berco_manual);
			//////////////////////////////////////////////////
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[0] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 2)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_2,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_2,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[1] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 3)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_3,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_3,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[2] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 4)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_4,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_4,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[3] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 5)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_5,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_5,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[4] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 6)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_6,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_6,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[5] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 7)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_7,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_7,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[6] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 8)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_8,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_8,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[7] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 9)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_9,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_9,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[8] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 10)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_10,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_10,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[9] = dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 11)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_11,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_11,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[10]= dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 12)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_12,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_12,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[11]= dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 13)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_13,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_13,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[12]= dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 14)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_14,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_14,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[13]= dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 15)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_15,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_15,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[14]= dado_byte;
			//////////////////////////////////////////////////
			if(quantos_bytes < 16)
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_16,  		ATTR_CTRL_VAL ,	"");
			GetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_DADO_16,  			ATTR_CTRL_VAL ,	valor_str);
			status = Fmt(&dado_byte, "%x<%s", valor_str);
			if(status > 0)
				envio_can[berco_manual].dados_can[15]= dado_byte;
			
			status = Gravar_BytesNVM_Diag(end_inicial, quantos_bytes, berco_manual, OFF);
			if(status == SUCESSO)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GRAVAR_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_GREEN);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GRAVAR_NVM,  	ATTR_CMD_BUTTON_COLOR ,VAL_RED);
			}
			break;
		}
return 0;
}


/******************************** Power_mode() ******************************************************************/
int CVICALLBACK Power_mode (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int item;

	switch (event)
	{
		case EVENT_COMMIT:

			
			//GetCtrlVal (panel, MANUAL_POWER_MODE , &item);
		
			switch(item)
			{
				case 0:
				   SysPwrMd[berco_manual].cData[6] = 0x00;
				break;
				
				case 1:
				   SysPwrMd[berco_manual].cData[6] = 0x01;
				break;
				
				case 2:
				   SysPwrMd[berco_manual].cData[6] = 0x02;
				break;
				
				case 3:
				   SysPwrMd[berco_manual].cData[6] = 0x02;
				break;		
			}
			
	
			break;
	}
	return 0;
}


/******************************** Get_manual_num_berco() ******************************************************************/
int CVICALLBACK Get_manual_num_berco_diag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor = 0;

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, TELA_DIAG_SET_MAN_BERCO, &valor); 
			switch (valor)
			{
				case 1:
				    berco_manual = 1;
					
				break;
				case 2:
				    berco_manual = 2;
							
				break;
			}
			Delay_thread(.1);
			break;
		}
	return 0;
}


/******************************** Get_manual_num_berco() ******************************************************************/
int CVICALLBACK Get_manual_num_berco (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int valor = 0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, MANUAL_SET_MAN_BERCO, &valor); 
			switch (valor)
			{
				case 1:
				    berco_manual = 1;
				   	atualizar_mens_can[1] = ON;
					atualizar_mens_can[2] = OFF;  					
				break;
				case 2:
				    berco_manual = 2;
					atualizar_mens_can[1] = OFF;
					atualizar_mens_can[2] = ON;  					
				break;
			}
			Delay_thread(.1);
			break;
		}
	return 0;
}
//********************************** Função Quit ***********************************************************************
int CVICALLBACK Quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			////////////////////////
			
			atualizar_mens_can[berco_manual]=OFF; 
			Delay_thread(1);
			
			///////////////////////
		
			sair_programa = ON;
			QuitUserInterface (0);
			break;
	}
	return 0;
}

//********************************** Função Ler_dados_tabelas_calibracao() ***********************************************************************
int Ler_dados_tabelas_calibracao(int delay_command, int berco)
{
unsigned int
	data_val_inp,
	data_val_out;
char
	valor_str[100],
	valor_wr1[100],
	valor_wr2[100];
int 
	status;

	////////////////////////////////////////// Velo table ////////////////////////////////////////////
	status = Ler_Table_DataWord(VELO_CAN_MIN, &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_MAX, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_min =  data_val_inp;
		dados_tab_cal[berco].velo_can_max =  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_min));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_can_max));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN Min=0x", valor_wr1, "CAN Máx=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 2, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_0, 	&data_val_inp,  delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_0, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_0 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_0 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_0));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_0));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-0=0x", valor_wr1, "Counts-0=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 3, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_1, 	&data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_1, &data_val_out,delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_1 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_1 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_1));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_1));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-1=0x", valor_wr1, "Counts-1=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 4, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_2, 	&data_val_inp, delay_command,berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_2, &data_val_out, delay_command,berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_2 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_2 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_2));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_2));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-2=0x", valor_wr1, "Counts-2=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 5, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_3, 	&data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_3, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_3 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_3 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_3));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_3));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-3=0x", valor_wr1, "Counts-3=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 6, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_4, 	&data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_4, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_4 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_4 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_4));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_4));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-4=0x", valor_wr1, "Counts-4=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 7, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_5, 	&data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_5, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_5 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_5 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_5));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_5));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-5=0x", valor_wr1, "Counts-5=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 8, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_6, 	&data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_6, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_6 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_6 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_6));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_6));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-6=0x", valor_wr1, "Counts-6=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 9, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_CAN_POINT_7, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_COUNTS_POINT_7, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].velo_can_pt_7 		=  data_val_inp;
		dados_tab_cal[berco].velo_counts_pt_7 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].velo_can_pt_7));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].velo_counts_pt_7));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-7=0x", valor_wr1, "Counts-7=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 10, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	if(status == SUCESSO)
		status = Ler_Table_DataWord(VELO_ROTOR_OFFSET, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_rotor_offset[berco].velo_rotor_value 	=  data_val_out;
		if(modo_manual)
		{	
			if(dados_rotor_offset[berco].velo_rotor_value < 0x10)
				Fmt(valor_wr1, "%s<0%x", dados_rotor_offset[berco].velo_rotor_value);
			else
				Fmt(valor_wr1, "%s<%x",  dados_rotor_offset[berco].velo_rotor_value);
			StringUpperCase (valor_wr1);
			Fmt(valor_str, "%s<%s%s", "Rotor Offset=0x",valor_wr1);
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 11, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	
	/***************************************** Taco table ******************************************************/
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_MIN, &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_MAX, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_min =  data_val_inp;
		dados_tab_cal[berco].taco_can_max =  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_min));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_can_max));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN Min=0x", valor_wr1, "CAN Máx=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 14, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_0, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_0, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_0 		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_0 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_0));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_0));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-0=0x", valor_wr1, "Counts-0=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 15, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_1, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_1, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_1 		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_1 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_1));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_1));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-1=0x", valor_wr1, "Counts-1=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 16, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_2, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_2, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_2		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_2 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_2));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_2));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-2=0x", valor_wr1, "Counts-2=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 17, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_3, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_3, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_3		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_3 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_3));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_3));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-3=0x", valor_wr1, "Counts-3=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 18, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_4,  	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_4, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_4		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_4 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_4));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_4));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-4=0x", valor_wr1, "Counts-4=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 19, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_5, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_5, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_5		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_5 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_5));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_5));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-5=0x", valor_wr1, "Counts-5=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 20, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_6, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_6, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_6		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_6 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_6));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_6));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-6=0x", valor_wr1, "Counts-6=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 21, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_CAN_POINT_7, 	 &data_val_inp, delay_command, berco);
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_COUNTS_POINT_7, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_tab_cal[berco].taco_can_pt_7		=  data_val_inp;
		dados_tab_cal[berco].taco_counts_pt_7 	=  data_val_out;
		if(modo_manual)
		{	
			strcpy(valor_wr1, Word_to_string(dados_tab_cal[berco].taco_can_pt_7));
			strcpy(valor_wr2, Word_to_string(dados_tab_cal[berco].taco_counts_pt_7));
			StringUpperCase (valor_wr1);
			StringUpperCase (valor_wr2);
			Fmt(valor_str , "%s<%s%s / %s%s", "CAN-7=0x", valor_wr1, "Counts-7=0x", valor_wr2); 
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 22, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	if(status == SUCESSO)
		status = Ler_Table_DataWord(TACO_ROTOR_OFFSET, &data_val_out, delay_command, berco);
	if(status == SUCESSO)
	{
		dados_rotor_offset[berco].taco_rotor_value 	=  data_val_out;
		if(modo_manual)
		{	
			if(dados_rotor_offset[berco].taco_rotor_value < 0x10)
				Fmt(valor_wr1, "%s<0%x", dados_rotor_offset[berco].taco_rotor_value);
			else
				Fmt(valor_wr1, "%s<%x",  dados_rotor_offset[berco].taco_rotor_value);
			StringUpperCase (valor_wr1);
			Fmt(valor_str, "%s<%s%s", "Rotor Offset=0x",valor_wr1);
			SetTreeCellAttribute(panel_CAN_diagnostico, TELA_DIAG_CALIBRACAO, 23, VAL_ALL_OBJECTS, ATTR_LABEL_TEXT,  valor_str);
		}
	}
	
return status;
}

//********************************** Função Word_to_string() ***********************************************************************
char *Word_to_string(unsigned int valor)
{
size_t 
	tamanho;
int 
	i;

	free(word_to_str);
	word_to_str = (char *)malloc(100);
	Fmt(word_to_str, "%s<%x", valor);
	for(i=1; i<4; i++)
	{
		tamanho = strlen(word_to_str);
		if(tamanho < 4)
			AddStringPrefix(&word_to_str, "0", 1);
	}
	return word_to_str;
}


/********************************* MostraGroupLeds_Status() *******************************************************/
void MostraGroupLeds_Status(TELLTALES_GM_GEM telltales, int valor)
{
	if(valor == OFF)
	{
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,  		ATTR_OFF_COLOR ,VAL_WHITE);
		SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL,  		ATTR_CTRL_VAL  ,OFF);
	}
	switch(telltales)
	{
		case ALL_TELLTALES_RED:
			if(valor == ON)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  		ATTR_ON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_AIRBAG,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LALTERNADOR,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HI_TEMP,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_BRAKE,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_OIL_PRESSURE,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_BRAKE,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASS_SEATBELT,  			ATTR_CTRL_VAL ,ON);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  		ATTR_OFF_COLOR ,VAL_WHITE);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_RED,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_AIRBAG,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LALTERNADOR,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HI_TEMP,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_BRAKE,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_OIL_PRESSURE,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SEAT_BELT,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARKING_BRAKE,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PASS_SEATBELT,  			ATTR_CTRL_VAL ,OFF);
			}
			break;
		case ALL_TELLTALES_GREEN:
			if(valor == ON)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_ON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ENGAGED,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FRONT_FOG,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LIGHT_ON,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LEFT_TURN,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_RIGHT_TURN,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_GREEN,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_GREEN,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_GREEN,  			ATTR_CTRL_VAL ,ON);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_OFF_COLOR ,VAL_WHITE);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_GREEN,  	ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CRUISE_ENGAGED,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_FRONT_FOG,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LIGHT_ON,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LEFT_TURN,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_RIGHT_TURN,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_GREEN,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_GREEN,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_GREEN,  			ATTR_CTRL_VAL ,OFF);
			}
			break;
		case ALL_TELLTALES_AMBER:
			if(valor == ON)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_ON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_ABS,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SE_PBRAKE,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_REAR_FOG,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SECURITY,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_ENG_SOON,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TYRE_PRESSURE,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_SERVICE,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUTCH,  				ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACTION_CONTROL,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_VEH_SOON,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_EPS,  					ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARK_ASSIST,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GLOW,  					ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PEDESTRIAN,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_AMBER,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_AMBER,  		ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LOW_FUEL,  			ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_OFF,  				ATTR_CTRL_VAL ,ON);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_OFF_COLOR ,VAL_WHITE);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_AMBER,  	ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_ABS,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SE_PBRAKE,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_REAR_FOG,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SECURITY,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_ENG_SOON,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TYRE_PRESSURE,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_SERVICE,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_CLUTCH,  				ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACTION_CONTROL,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_SERV_VEH_SOON,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_EPS,  					ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PARK_ASSIST,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_GLOW,  					ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_PEDESTRIAN,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LINE_K_AMBER,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TRACKLEAD_AMBER,  		ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_LED_LOW_FUEL,  			ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_ESC_OFF,  				ATTR_CTRL_VAL ,OFF);
			}
			break;
		case ALL_TELLTALES_WHITE:
			if(valor == ON)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_ON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_KMH,  					ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MPH,  					ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_WHITE,  		ATTR_CTRL_VAL ,ON);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_OFF_COLOR ,VAL_WHITE);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_WHITE,  	ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_KMH,  					ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_MPH,  					ATTR_CTRL_VAL ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_AUTOHOLD_WHITE,  		ATTR_CTRL_VAL ,OFF);
			}
			break;
		case ALL_TELLTALES_BLUE:
			if(valor == ON)
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_ON_COLOR ,VAL_GREEN);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_CTRL_VAL ,ON);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HIGH_BEAM,  				ATTR_CTRL_VAL ,ON);
			}
			else
			{
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_OFF_COLOR ,VAL_WHITE);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_TELLTALES_ALL_BLUE,  	ATTR_CTRL_VAL  ,OFF);
				SetCtrlAttribute (panel_CAN_diagnostico, TELA_DIAG_HIGH_BEAM,  				ATTR_CTRL_VAL  ,OFF);
			}
			break;
		default:
			break;
	}
}



			   

/********************************* Teste_CMD() *******************************************************/
int CVICALLBACK Teste_CMD(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int 
	status;
char
	valor_str[50];
unsigned char
	 valor;
double 
	t,
	timeout;

	switch (event)
	{
		case EVENT_COMMIT:
		//GetCtrlVal (panel_CAN_diagnostico, TELA_DIAG_TESTE, &valor);
		
		t = Timer();
		/*servico_diagnostico[berco_manual] = TELLTALE_DIAG_CUSTOMER;
		while(servico_diagnostico[berco_manual] == TELLTALE_DIAG_CUSTOMER && Timer()-t <=timeout)
				Delay_thread(0.001);
		if(status_comunic_CAN[berco_manual] < 0 || Resp_diagnostico_RX[0][berco_manual].dwID != ID_CAN_DIAG_RX || 
		   Resp_diagnostico_RX[0][berco_manual].cData[0] != 0x05 || Resp_diagnostico_RX[0][berco_manual].cData[1] != 0x6F || 
		   Resp_diagnostico_RX[0][berco_manual].cData[2] != 0xF0)
		{
			return Indica_comm_CAN_Not_OK();
		}*/
	
		Indica_comm_CAN_OK(berco_manual);
			
 			break;
	}
	return 0;
}
   

int CVICALLBACK Prod_1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,control,&my_prod_1);
			break;
	}
	return 0;
}

int CVICALLBACK Prod_2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,control,&my_prod_2); 
			break;
	}
	return 0;
}

int CVICALLBACK Send_BC_1 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
char aux[100]={0};	
	
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlVal(panel, AUTO_TXT_SERIE_1,"SJY02A00001");
			
			Delay_thread(.3);
			
			GetCtrlVal (panel, AUTO_TXT_SERIE_1, aux);
			
			if(strlen(aux) > 1)
				///leu_serial_scanner_manual[1] = ON; //Seta flag leu com o leitor manual
				dados_scanner[SCANNER_1].leu_serial_scanner_manual=ON;
			
			break;
	}
	return 0;
}



int CVICALLBACK Send_BC_2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
char aux[100]={0};	
	
	switch (event)
	{
		case EVENT_COMMIT:
											
			SetCtrlVal(panel, AUTO_TXT_SERIE_2,"SJY02A00002"); 
			
			Delay_thread(.3);
			
			GetCtrlVal (panel, AUTO_TXT_SERIE_2, aux);
			if(strlen(aux) > 1)
				///leu_serial_scanner_manual[2] = ON; //Seta flag leu com o leitor manual
				   dados_scanner[SCANNER_2].leu_serial_scanner_manual=ON;
			
			break;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//18/06/2019
int CVICALLBACK Read_VPPS (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
char cluster_VPPS [30] ={0};

	switch (event)
	{
		case EVENT_COMMIT:
			F_read_VPPS(berco_manual, &cluster_VPPS[0]);
			SetCtrlVal(panel,TELA_DIAG_VPPS_DUNS, cluster_VPPS);
			break;
	}
	return 0;
}

int CVICALLBACK Write_VPPS (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
char cluster_VPPS [30] ={0};

	switch (event)
	{
		case EVENT_COMMIT:
			PromptPopup ("Entre com VPPS", "14 caracteres no máximo", cluster_VPPS, VPPS_LENGHT); 
			F_write_VPPS(berco_manual, &cluster_VPPS[0]);
			break;
	}
	return 0;
}

int CVICALLBACK Read_DUNS (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
char cluster_DUNS [30] ={0};

	switch (event)
	{
		case EVENT_COMMIT:
			F_read_DUNS(berco_manual, &cluster_DUNS[0]);
			SetCtrlVal(panel,TELA_DIAG_VPPS_DUNS, cluster_DUNS);
			break;
	}
	return 0;
}

int CVICALLBACK Write_DUNS (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
char 
	cluster_DUNS [30] ={0}; 

	switch (event)
	{
		case EVENT_COMMIT:
			PromptPopup ("Entre com DUNS", "9 caracteres no máximo", cluster_DUNS, DUNS_LENGHT); 
			F_write_DUNS(berco_manual, &cluster_DUNS[0]);
			break;
	}
	return 0;
}
