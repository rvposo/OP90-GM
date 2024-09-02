#include "cvixml.h"    

#include <NIDAQmx.h>
#include <utility.h>
#include <ansi_c.h>
#include <analysis.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include <stdio.h>  
#include "toolbox.h"
#include "Main OP090 GM-GEM.h"
#include "DAQ_MX.h"

int status = 0, 
	sampsPerChan_daq = 100, 
	tamanho = 8000, //8 canais * 1000 Samples
	tamanho_real,
	acao_digital;
double 	
	time_out = 3,
	leituras[10000],
	leituras_2[20000];
int EscDigital6009(char *canal_string, uInt32 valor_escrever, int tipo_escrita);
static float64 
	resultingSampClkRate;

//************************* Função  Init_NI_daq_6210 ************************************************************************
int Init_NI_daq_6210 (int berco)
{
	status = DAQmxCreateTask("",&analog_INP_handler_6210[berco]); 	
	status = DAQmxCreateTask("",&analog_OUT_handler_6210[berco]); 	
	status = DAQmxCreateAIVoltageChan(analog_INP_handler_6210[berco], canal_AD_DAQ_6210_string[berco],"",DAQmx_Val_Diff, -10, 10, DAQmx_Val_Volts,NULL);
	status = DAQmxCreateAOVoltageChan(analog_OUT_handler_6210[berco], canal_DA_DAQ_6210_string[berco],"", MIN_TENSAO_DA, MAX_TENSAO_DA, DAQmx_Val_Volts,NULL);
	return 0;
}

//************************* Função  Stop_NI_daq_6210 ************************************************************************
int Stop_NI_daq_6210 (int berco)
{
	DAQmxStopTask(analog_INP_handler_6210[berco]);
	DAQmxStopTask(analog_OUT_handler_6210[berco]);
	DAQmxClearTask(analog_INP_handler_6210[berco]);
	DAQmxClearTask(analog_OUT_handler_6210[berco]);
	return 0;
}

//************************* Função  Init_NI_4461 ************************************************************************
int Init_NI_4461 (void)
{
char 
	ambos_canais[512];
int32 		
	sampsPerChan_OUT=0, 
	sampsPerChan_IN=0;

	//////////////////////////////////////////////////
	sampsPerChan_IN 	=  SAMP_PER_CHANN_IN;
	sampsPerChan_OUT 	=  SAMP_PER_CHANN_OUT;
	SetBreakOnLibraryErrors (0);
	Stop_NI_4461();
	Delay(0.1);
	//////////////////////////////////////////////////////
	strcpy(ambos_canais,canal_DA_4461_0_string);
	strcat(ambos_canais, ":");
	strcat(ambos_canais, "ao1");
	///strcat(ambos_canais, canal_DA_4461_1_string);
	status = DAQmxCreateTask("",&entrada_4461_handler_0); 	
	status = DAQmxCreateTask("",&entrada_4461_handler_1); 
	
	status = DAQmxCreateTask("",&saida_4461_handler_0);
	status = DAQmxCreateTask("",&saida_4461_handler_1); 
	status = DAQmxCreateTask("",&saida_4461_handler_ambos); 	
	
	status = DAQmxCreateAIVoltageChan(entrada_4461_handler_0,canal_AD_4461_0_string,"",DAQmx_Val_Diff, -10, 10, DAQmx_Val_Volts,NULL);
	status = DAQmxCreateAIVoltageChan(entrada_4461_handler_1,canal_AD_4461_1_string,"",DAQmx_Val_Diff, -10, 10, DAQmx_Val_Volts,NULL); 
	
	
	status = DAQmxCreateAOVoltageChan(saida_4461_handler_0,canal_DA_4461_0_string,"", MIN_TENSAO_DA4461, MAX_TENSAO_DA4461, DAQmx_Val_Volts,NULL);
	status = DAQmxCreateAOVoltageChan(saida_4461_handler_1,canal_DA_4461_1_string,"", MIN_TENSAO_DA4461, MAX_TENSAO_DA4461, DAQmx_Val_Volts,NULL);
	status = DAQmxCreateAOVoltageChan(saida_4461_handler_ambos,ambos_canais,"", MIN_TENSAO_DA4461, MAX_TENSAO_DA4461, DAQmx_Val_Volts,NULL); 
	
	//////////////////////////////////////////////////////////
	status = DAQmxCfgSampClkTiming(saida_4461_handler_0,"",SAMPLE_RATE_4461,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan_OUT);
	status = DAQmxCfgSampClkTiming(saida_4461_handler_1,"",SAMPLE_RATE_4461,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan_OUT);
	//status = DAQmxCfgSampClkTiming(saida_4461_handler_ambos,"",resultingSampClkRate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan_OUT);
	
	status = DAQmxCfgSampClkTiming(entrada_4461_handler_0,"",SAMPLE_RATE_4461,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,sampsPerChan_IN);
	status = DAQmxCfgSampClkTiming(entrada_4461_handler_1,"",SAMPLE_RATE_4461,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,sampsPerChan_IN);
	
	return 0;
}

//************************* Função  Stop_NI_4461 ************************************************************************
int Stop_NI_4461 (void)
{
	DAQmxStopTask(entrada_4461_handler_0);
	DAQmxStopTask(saida_4461_handler_0);
	DAQmxClearTask(entrada_4461_handler_0);
	DAQmxClearTask(saida_4461_handler_0);
	
	DAQmxStopTask(entrada_4461_handler_1);
	DAQmxStopTask(saida_4461_handler_1);
	DAQmxClearTask(entrada_4461_handler_1);
	DAQmxClearTask(saida_4461_handler_1);
	
	DAQmxStopTask(saida_4461_handler_ambos);
	DAQmxClearTask(saida_4461_handler_ambos);
	/////////////////////////////////////////
	return 0;
}

//************************* Função  SetSampleClockRate ************************************************************************
int SetSampleClockRate(TaskHandle taskHandle, float64 desiredFreq, int32 sampsPerBuff, float64 cyclesPerBuff, float64 *desiredSampClkRate, float64 *sampsPerCycle, float64 *resultingSampClkRate, float64 *resultingFreq)
{
int	error=0;
	
	*sampsPerCycle = sampsPerBuff / cyclesPerBuff;
	*desiredSampClkRate = desiredFreq * sampsPerBuff / cyclesPerBuff;
	status = DAQmxSetTimingAttribute(taskHandle,DAQmx_SampClk_Rate,*desiredSampClkRate);  
	status = DAQmxGetTimingAttribute(taskHandle,DAQmx_SampClk_Rate,resultingSampClkRate);
	*resultingFreq = *resultingSampClkRate / *sampsPerCycle;
	return status;
}

//************************* Função  Ler_4461 ************************************************************************
/*
int Ler_4461(int ler_thd, int canal, double *Level, double *Freq_Peak, double *Distortion)
{
int 
	filter_design,
	filter_type,
	filter_order=1,
	err,
	log, 
	numRead,
	task_done;
double 
	ripple=2,
	attentuation=4;
IIRFilterPtr 
	filter_information;
WindowConst 
	WinConst;
float64	
	*gData=NULL;
static int  
	canal_anterior;
uInt32		
	gNumChannels=1,
	sampsPerChanHI=0,
	sampsPerChanLO=0;
TaskHandle  
	entradas_4461_handler;
double 
	df, 
	auto_power_spectrum[100048],
	harm_amp[QTDADE_HARMONICAS], 
	harm_freq[QTDADE_HARMONICAS], 
	resultingFrequency, 
	desiredSampClkRate,
	thd,
	thd_noise,
	sampsPerCycle=0,
	Power_Peak,
	read_freq=0,
	v_DC_rms,
	v_AC_rms,
	dB_correct,
	fator=1,
	t;
	
	/////////////////////////////////////////////
	if(canal == ESQUERDO)
	{
		entradas_4461_handler = entrada_4461_handler_0;
	}
	else
	{
		entradas_4461_handler = entrada_4461_handler_1;
	}
	sampsPerChanHI =  SAMP_PER_CHANN_IN;
	if( (gData=(float64*)malloc(sampsPerChanHI*gNumChannels*sizeof(float64)))==NULL ) 
	{
		goto error;
	}
	status = DAQmxReadAnalogF64(entradas_4461_handler,sampsPerChanHI,0.5 ,DAQmx_Val_GroupByScanNumber,gData,sampsPerChanHI*gNumChannels,&numRead,NULL);
	if(numRead !=  sampsPerChanHI)
	{
		goto error;
	}
	else if(numRead == 0)
	{
		status = FALHA;
		goto error;
	}
	//////////// filtros ///////
	if(filtro_audio==1)
		Ch_BPF (gData,sampsPerChanHI ,resultingSampClkRate ,20 ,20000 , 0.1, 5, gData); //BPF  20 Hz to  20 KHz 
	else if(filtro_audio==2)
		Ch_BPF (gData,sampsPerChanHI ,resultingSampClkRate , 20 ,10000 , 0.1, 5, gData);//BPF  20 Hz to  10 KHz
	else if(filtro_audio==3 )
		Ch_BPF (gData,sampsPerChanHI ,resultingSampClkRate ,400 ,20000 , 0.1, 5, gData); //BPF 400 Hz to 20 KHz
	else if(filtro_audio==4)   
	{
	    filter_information = AllocIIRFilterPtr (BANDPASS, filter_order);    
		err = InvCh_CascadeCoef (resultingSampClkRate, 900,
                                 8000, attentuation,
                                 filter_information);
		err = IIRCascadeFiltering (gData, sampsPerChanHI, filter_information,
                               gData);
	   
		////////////////////////////////////////////////
    	FreeIIRFilterPtr(filter_information);
	}
	else if(filtro_audio==5)
	{
	
	   Ch_LPF (gData,sampsPerChanHI ,resultingSampClkRate ,20000 , 0.1, 5, gData);//LPF 20 KHz  
	
	}
	else if(filtro_audio==6 )
		Ch_BPF (gData,sampsPerChanHI ,resultingSampClkRate ,400 ,5000 , 0.1, 5, gData); //BPF 400 Hz to 5 KHz
	else if(filtro_audio==7 )
		Ch_BPF (gData,sampsPerChanHI ,resultingSampClkRate ,300 ,20000 , 0.1, 5, gData); //BPF 300 Hz to 20 KHz
	/////////////////////
	ACDCEstimator (gData,sampsPerChanHI , &v_AC_rms, &v_DC_rms);
	ScaledWindow (gData, sampsPerChanHI, 6, &WinConst);
	status = AutoPowerSpectrum (gData, sampsPerChanHI, 1.0/resultingSampClkRate,auto_power_spectrum , &df);
	*Level= v_AC_rms;
	ultimo_nivel_audio_lido = v_AC_rms;
	if(v_AC_rms > 0.01)
	{
		//ScaledWindow (gData, sampsPerChanHI, 0, &WinConst);
		//status = AutoPowerSpectrum (gData, sampsPerChanHI, 1.0/resultingSampClkRate,auto_power_spectrum , &df);
		status = PowerFrequencyEstimate (auto_power_spectrum, sampsPerChanHI/2, -1, WinConst, df, 7, &read_freq, &Power_Peak);
		*Freq_Peak=read_freq;
		if(ler_thd)
		{
			status = HarmonicAnalyzer (auto_power_spectrum, sampsPerChanHI/2, -1, QTDADE_HARMONICAS, 
				0, resultingSampClkRate, 
				read_freq,
				harm_amp,harm_freq ,&thd , &thd_noise);
				*Distortion=thd;
		}
		else
		 	*Distortion=999;
		//Delay(0.05);
		Delay(0.001);
	}
	else
	{
		*Freq_Peak=-999;
		*Distortion=-999;
	}
	if(filtro_audio==4)
	{
		//if((read_freq>20 && read_freq<=4000)|| *Freq_Peak==-999)
		//{
			dB_correct=-3;
			fator=0.707;
		//}
		/*if(read_freq<=31.5)
		{
			dB_correct=-29.9;
			fator=0.03198895;
		}
		else if(read_freq>31.5 && read_freq<=63)
		{
			dB_correct=-23.9;
			fator=0.063826348;
		}
		else if(read_freq>63 && read_freq<=100)
		{
			dB_correct=-19.8;
			fator=0.063826348;
		}
		else if(read_freq>100 && read_freq<=200)
		{
			dB_correct=-13.8;
			fator=0.20417379;
		}
		else if(read_freq>200 && read_freq<=400)
		{
			dB_correct=-7.8;
			fator=0.40738027;
		}
		else if(read_freq>400 && read_freq<=800)
		{
			dB_correct=-1.9;
			fator=0.8035261221;
		}
		else if(read_freq>800 && read_freq<=900)
		{
			dB_correct=-1.8;
			fator=0.8128305161;
		}
		else if(read_freq>900 && read_freq<=2000)
		{
			dB_correct=0;
			fator=1;
		}
		else if(read_freq>2000 && read_freq<=3150)
		{
			dB_correct=5.6;
			fator=1.9054607179;
		}
		else if(read_freq>3150 && read_freq<=4000)
		{
			dB_correct=9.0;
			fator=2.8183829;
		}*/
		
		/*
		*Level= v_AC_rms=v_AC_rms*fator;
		
	//}
	
		
	
error:	
	//if( gData ) {
		free(gData);
		gData = NULL;
	//}

	return status;
}
*/
//************************* Função  Saida_4461 ************************************************************************
/*
int Saida_4461(int canal, double frequencia, double amplitude)
{
double 
	desiredSampClkRate, 
	sampsPerCycle, 
	resultingFrequency,
     phase=0.0;
float64     
	*data=NULL;
int32 		
	written,
	sampsPerBuffer,
	sampsPerChanLO=0,
	sampsPerChan_OUT=0, 
	sampsPerChan_IN=0;
int         
	log;
	
	
	
	while (AA_busy==ON)
	   Delay_thread(.1);
	
	AA_busy = ON;
	   Delay_thread(.01);
	
	

	if(amplitude < 0.001 || amplitude > 8)//1mVolt até 8V saida
	{
		freq_anterior=0;
		AA_busy = OFF;
		Delay_thread(.01);
		return -555;
	}		
	if(frequencia < FREQ_MIN_MONITORAR || frequencia > FREQ_MAX_MONITORAR)
	{
		freq_anterior=0;
		AA_busy = OFF;
		Delay_thread(.01);
		return -777;
	}		
	sampsPerChan_IN 	=  SAMP_PER_CHANN_IN;
	sampsPerChan_OUT 	=  SAMP_PER_CHANN_OUT;
			
	if(freq_anterior != frequencia || amplitude != amplitude_anterior || canal_anterior != canal)//reajusta o rate de acordo com a frequencia a ser gerada e monitorada 
	{
		freq_anterior = frequencia;
		amplitude_anterior = amplitude;
		sampsPerBuffer=(SAMPLE_RATE_4461/frequencia)*CICLO_POR_BUFFER;
		switch(canal)
		{
			case ESQUERDO:
				SetBreakOnLibraryErrors (0);
				DAQmxStopTask(saida_4461_handler_1);
				DAQmxClearTask(saida_4461_handler_1);
				SetBreakOnLibraryErrors (1);
				status = DAQmxCreateTask("",&saida_4461_handler_0);
				status = DAQmxCreateAOVoltageChan(saida_4461_handler_0,canal_DA_4461_0_string,"", MIN_TENSAO_DA4461, MAX_TENSAO_DA4461, DAQmx_Val_Volts,NULL);
				status = SetSampleClockRate(saida_4461_handler_0,freq_anterior,sampsPerBuffer,CICLO_POR_BUFFER,&desiredSampClkRate,&sampsPerCycle,&resultingSampClkRate,&resultingFrequency);
				rate_anterior = resultingSampClkRate;
				status = DAQmxCfgSampClkTiming(saida_4461_handler_0,"",resultingSampClkRate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan_OUT);
				if( (data=malloc(sampsPerBuffer*sizeof(float64)))==NULL ) 
					goto error;
				GenSineWave(sampsPerBuffer,amplitude,1/sampsPerCycle,&phase,data);
				status = DAQmxWriteAnalogF64(saida_4461_handler_0,sampsPerBuffer,0,10.0,DAQmx_Val_GroupByChannel,data,&written,NULL);
				status = DAQmxStartTask(saida_4461_handler_0);
				canal_anterior=ESQUERDO;
				break;
			case DIREITO:
				SetBreakOnLibraryErrors (0);
				DAQmxStopTask(saida_4461_handler_0);
				DAQmxClearTask(saida_4461_handler_0);
				SetBreakOnLibraryErrors (1);
				status = DAQmxCreateTask("",&saida_4461_handler_1); 
				status = DAQmxCreateAOVoltageChan(saida_4461_handler_1,canal_DA_4461_1_string,"", MIN_TENSAO_DA4461, MAX_TENSAO_DA4461, DAQmx_Val_Volts,NULL);
				status = SetSampleClockRate(saida_4461_handler_1,freq_anterior,sampsPerBuffer,CICLO_POR_BUFFER,&desiredSampClkRate,&sampsPerCycle,&resultingSampClkRate,&resultingFrequency);
				rate_anterior = resultingSampClkRate;
				status = DAQmxCfgSampClkTiming(saida_4461_handler_1,"",resultingSampClkRate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan_OUT);
				if( (data=malloc(sampsPerBuffer*sizeof(float64)))==NULL ) 
					goto error;
				GenSineWave(sampsPerBuffer,amplitude,1/sampsPerCycle,&phase,data);
				status = DAQmxWriteAnalogF64(saida_4461_handler_1,sampsPerBuffer,0,10.0,DAQmx_Val_GroupByChannel,data,&written,NULL);
				status = DAQmxStartTask(saida_4461_handler_1);
				canal_anterior=DIREITO;
				break;
			case AMBOS:
				canal_anterior=AMBOS;
				break;
		}
	
	}		
error:
	if( data ) 
	{
		free(data);
		data = NULL;
	}
	
	AA_busy = OFF;
	Delay_thread(.01);
	
return status;
}
*/
//************************* Função  GenSineWave ************************************************************************
void GenSineWave(int numElements, double amplitude, double frequency, double *phase, double sineWave[])
{
	int i=0;

	for(;i<numElements;++i)
		sineWave[i] = sqrt(2)*amplitude*sin(PI/180.0*(*phase+360.0*frequency*i));
	*phase = fmod(*phase+frequency*360.0*numElements,360.0);
}
//************************* Função  CenterInRange ************************************************************************
void CenterInRange(const double inputArray[], int numElements, double upper, double lower, double outputArray[])
{
	int i=0;
	double	shift=(upper+lower)/2.0;
	
	for(;i<numElements;++i)
		outputArray[i] = inputArray[i] + shift;
}
//************************* Função  VmedioSEnd2canais ************************************************************************
double VmedioSEnd2canais (int canalA, int canalB, int berco)
{
double resA, resB, res;

	resA = 2*Vmedio_NIdaq_6210_1ch(canalA, -5, 5, TERMIN_CONF_SING_ENDED, berco);  //CANAL A  = sinal +
	resB = 2*Vmedio_NIdaq_6210_1ch(canalB, -5, 5, TERMIN_CONF_SING_ENDED, berco); //CANAL B = sinal -
	res  = resA - resB;
return res;
}
//************************* Função  Vmedio_NIdaq_6210_1ch ************************************************************************
double Vmedio_NIdaq_6210_1ch (int canal, double lim_min, double lim_max, int terminal_conf, int berco)
{
char canal_nome[100];
double valor;

		SetBreakOnLibraryErrors (0);
		///DAQmxStopTask(analog_INP_handler_6210[berco]);
		///DAQmxClearTask(analog_INP_handler_6210[berco]);
		switch(canal)
		{
			case 0:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai0");
				strcpy(canal_nome,"canal_0");
				break;
			case 1:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai1");
				strcpy(canal_nome,"canal_1");
				break;
			case 2:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai2");
				strcpy(canal_nome,"canal_2");
				break;
			case 3:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai3");
				strcpy(canal_nome,"canal_3");
				break;
			case 4:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai4");
				strcpy(canal_nome,"canal_4");
				break;
			case 5:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai5");
				strcpy(canal_nome,"canal_5");
				break;
			case 6:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai6");
				strcpy(canal_nome,"canal_6");
				break;
			case 7:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai7");
				strcpy(canal_nome,"canal_7");
				break;
			case 8:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai8");
				strcpy(canal_nome,"canal_8");
				break;
			case 9:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai9");
				strcpy(canal_nome,"canal_9");
				break;
			case 10:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai10");
				strcpy(canal_nome,"canal_10");
				break;	
			case 11:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai11");
				strcpy(canal_nome,"canal_11");
				break;	
			case 12:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai12");
				strcpy(canal_nome,"canal_12");
				break;	
			case 13:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai13");
				strcpy(canal_nome,"canal_13");
				break;	
			case 14:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai14");
				strcpy(canal_nome,"canal_14");
				break;		
			case 15:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai15");
				strcpy(canal_nome,"canal_15");
				break;			
				
		
		}
		status = DAQmxCreateTask("",&analog_INP_handler_6210[berco]);
		if (status  != 0)
			status = 0;
			
			
		if(terminal_conf == TERMIN_CONF_SING_ENDED)
			status = DAQmxCreateAIVoltageChan(analog_INP_handler_6210[berco],canal_AD_DAQ_6210_string[berco], canal_nome, DAQmx_Val_RSE,lim_min,lim_max,DAQmx_Val_Volts,NULL);
		else
			status = DAQmxCreateAIVoltageChan(analog_INP_handler_6210[berco],canal_AD_DAQ_6210_string[berco], canal_nome, DAQmx_Val_Diff,lim_min,lim_max,DAQmx_Val_Volts,NULL);
		
		if (status  != 0)
			status = 0;
	
		
		DAQmxReadAnalogF64 (analog_INP_handler_6210[berco], sampsPerChan_daq, time_out, DAQmx_Val_GroupByChannel, leituras, sampsPerChan_daq,
                &tamanho_real, NULL);
    	Mean (leituras, sampsPerChan_daq, &valor);
		DAQmxStopTask(analog_INP_handler_6210[berco]);
		DAQmxClearTask(analog_INP_handler_6210[berco]);
		SetBreakOnLibraryErrors (1);
		
	return valor;
}

//************************* Função  Vmedio_RapidoNIdaq_6210_1ch ************************************************************************
double Vmedio_RapidoNIdaq_6210_1ch (int canal, double lim_min, double lim_max, int terminal_conf, int berco)
{
char 
	canal_nome[100];
double 
	valor;
int 
	divisor=10;

	DAQmxReadAnalogF64 (analog_INP_handler_6210[berco], sampsPerChan_daq/divisor, time_out, DAQmx_Val_GroupByChannel, leituras, sampsPerChan_daq/divisor,
                &tamanho_real, NULL);
    Mean (leituras, sampsPerChan_daq/divisor, &valor);

	return valor;
}

//************************* Função  Vmedio_NIdaq_6210_8ch ************************************************************************
int Vmedio_NIdaq_6210_8ch (double lim_min, double lim_max, double *canal0, double *canal1,double *canal2,double *canal3
	,double *canal4, double *canal5, double *canal6, double *canal7, int berco)
{
char 
	canal_nome[100];
double 
	valor;

		SetBreakOnLibraryErrors (0);
		DAQmxStopTask(analog_INP_handler_6210[berco]);
		DAQmxClearTask(analog_INP_handler_6210[berco]);
		Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai0:7");
		strcpy(canal_nome,"canal_todos");
		status = DAQmxCreateTask("",&analog_INP_handler_6210[berco]); 	
		status = DAQmxCreateAIVoltageChan(analog_INP_handler_6210[berco],canal_AD_DAQ_6210_string[berco], canal_nome, DAQmx_Val_Diff,lim_min,lim_max,DAQmx_Val_Volts,NULL);
		//DAQmxReadAnalogF64 (analog_INP_handler_6210[berco], sampsPerChan, time_out, DAQmx_Val_GroupByChannel, leituras, tamanho,
        //        &tamanho_real, NULL);
		DAQmxReadAnalogF64 (analog_INP_handler_6210[berco], sampsPerChan_daq, time_out, DAQmx_Val_GroupByChannel, leituras, tamanho,
                &tamanho_real, NULL);
    	Mean (leituras, sampsPerChan_daq, &valor);
		*canal0 = valor;
		Subset1D (leituras, tamanho, sampsPerChan_daq, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal1 = valor;

		Subset1D (leituras, tamanho, sampsPerChan_daq*2, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal2 = valor;

		Subset1D (leituras, tamanho, sampsPerChan_daq*3, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal3 = valor;
		
		Subset1D (leituras, tamanho, sampsPerChan_daq*4, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal4 = valor;
		
		Subset1D (leituras, tamanho, sampsPerChan_daq*5, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal5 = valor;
		
		Subset1D (leituras, tamanho, sampsPerChan_daq*6, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal6 = valor;
		
		Subset1D (leituras, tamanho, sampsPerChan_daq*7, sampsPerChan_daq, leituras_2);
    	Mean (leituras_2, sampsPerChan_daq, &valor);
		*canal7 = valor;
		
		DAQmxStopTask(analog_INP_handler_6210[berco]);
		DAQmxClearTask(analog_INP_handler_6210[berco]);

	return 0;
}


//************************************ Atualiza_DA_DAQ6009 *************************************************				
int Atualiza_DA_DAQ6009 (double tensao_ch0, double tensao_ch1, int berco)
{
int32 samples_escrita_per_channel= 1;
bool32 auto_start = 1, data_layout = DAQmx_Val_GroupByChannel;
float64 time_out_escrita = 1,//1 segundo
		tensao[2];

	tensao[0] = tensao_ch0;
	tensao[1] = tensao_ch1;
	DAQmxWriteAnalogF64 (analog_OUT_handler_6210[berco], samples_escrita_per_channel, auto_start, time_out_escrita,
             data_layout, tensao, &tamanho_real, NULL);			   
	return 0;
}


//************************************ EscDigital6009_Byte *************************************************				
int EscDigital6009_Byte(int porta, uInt32 valor_escrever, int berco)
{
int32 samples_escrita_per_channel= 1;
bool32 auto_start = 1, data_layout = DAQmx_Val_GroupByChannel;
float64 time_out_escrita = 1;//1 segundo 
int32	escrito; 
uInt8 valor_bit;
char dig_string_6210[100];
	
	if(porta == 0)
			Fmt(dig_string_6210, "%s<%s%s",DAQ_6210_string[berco],"/port0");
	else
			Fmt(dig_string_6210, "%s<%s%s",DAQ_6210_string[berco],"/port1");
	
	status = DAQmxCreateTask("",&digital_port_handler_6210[berco]); 	
	status = DAQmxCreateDOChan(digital_port_handler_6210[berco], dig_string_6210,"", DAQmx_Val_ChanForAllLines);
	status = DAQmxWriteDigitalU32(digital_port_handler_6210[berco], samples_escrita_per_channel,
		auto_start, time_out_escrita, data_layout, &valor_escrever, &escrito, NULL);
	DAQmxStopTask(digital_port_handler_6210[berco]);
	DAQmxClearTask(digital_port_handler_6210[berco]);
	return 0;
}

//************************************ EscDigital6009_Bit *************************************************				
int EscDigital6009_Bit(int porta, int linha, uInt32 valor_escrever, int berco)
{
int32 
	samples_escrita_per_channel= 1;
bool32 
	auto_start = 1, 
	data_layout = DAQmx_Val_GroupByChannel;
float64 
	time_out_escrita = 1;//1 segundo 
int32	
	escrito; 
uInt8 
	valor_bit;
	
	if(porta == 0)
	{
		switch(linha)
		{
			case 0:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line0");
				break;
			case 1:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line1");
				break;
			case 2:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line2");
				break;
			case 3:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line3");
				break;
			case 4:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line4");
				break;
			case 5:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line5");
				break;
			case 6:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line6");
				break;
			case 7:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port0/line7");
				break;
		}
	}
	else
	{
		switch(linha)
		{
			case 0:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port1/line0");
				break;
			case 1:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port1/line1");
				break;
			case 2:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port1/line2");
				break;
			case 3:
				Fmt(canal_dig_string_6210[berco], "%s<%s%s",DAQ_6210_string[berco],"/port1/line3");
				break;
		}
	}
	
	status = DAQmxCreateTask("",&digital_port_handler_6210[berco]); 	
	valor_bit = valor_escrever;
	status = DAQmxCreateDOChan(digital_port_handler_6210[berco], canal_dig_string_6210[berco],"", DAQmx_Val_ChanForAllLines);
	status = DAQmxWriteDigitalLines(digital_port_handler_6210[berco], samples_escrita_per_channel,
		auto_start, time_out_escrita, data_layout, &valor_bit, &escrito, NULL);
	DAQmxStopTask(digital_port_handler_6210[berco]);
	DAQmxClearTask(digital_port_handler_6210[berco]);
	return 0;
}


//************************************double *FormaOnda_NIdaq_6210_1ch *************************************************				
int FormaOnda_NIdaq_6210_1ch (double lim_min, double lim_max, int canal, int leit_por_seg, int num_leit, double *leituras, int berco)
{
double desiredSampClkRate, sampsPerCycle, resultingFrequency;
int         status ;
double      phase=0.0;
char canal_nome[100]="";
uInt64	sampsPerChanHI_IN=0;
int32 		written,
			sampsPerBuffer,
			sampsPerChanHI_OUT=0,
			sampsPerChanLO=0;

 TaskHandle entradas_analogicas_forma_onda;
 
		time_out = 10.00 ;

		SetBreakOnLibraryErrors (0);

	
		switch(canal)
		{
			case 0:
				Fmt( canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai0:1");
				strcpy(canal_nome,"canal_0");
				break;
			case 1:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai1");
				strcpy(canal_nome,"canal_1");
				break;
			case 2:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai2");
				strcpy(canal_nome,"canal_2");
				break;
			case 3:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai3");
				strcpy(canal_nome,"canal_3");
				break;
			case 4:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai4");
				strcpy(canal_nome,"canal_4");
				break;
			case 5:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai5");
				strcpy(canal_nome,"canal_5");
				break;
			case 6:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai6");
				strcpy(canal_nome,"canal_6");
				break;
			case 7:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai7");
				strcpy(canal_nome,"canal_7");
				break;
			case 8:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai8");
				strcpy(canal_nome,"canal_8");
				break;
			case 9:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai9");
				strcpy(canal_nome,"canal_9");
				break;
			case 10:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai10");
				strcpy(canal_nome,"canal_10");
				break;
			case 11:
				Fmt(canal_AD_DAQ_6210_string[berco], "%s<%s%s",DAQ_6210_string[berco],"/ai11");
				strcpy(canal_nome,"canal_11");
				break;
				
		}
		status = DAQmxCreateTask("",&entradas_analogicas_forma_onda);
		if (status !=0)
			goto error;
		
		sampsPerChanHI_IN 	=  SAMP_PER_CHANN_IN;
		sampsPerChanHI_OUT 	=  SAMP_PER_CHANN_OUT;
			
		status = DAQmxCreateAIVoltageChan(entradas_analogicas_forma_onda, canal_AD_DAQ_6210_string[berco], canal_nome, DAQmx_Val_RSE,lim_min,lim_max,DAQmx_Val_Volts,NULL);
		if (status !=0)
			goto error;
		

		sampsPerBuffer=(SAMPLE_RATE_PADRAO/FREQUENCIA_PADRAO)*CICLO_POR_BUFFER;
		status = SetSampleClockRate(entradas_analogicas_forma_onda,FREQUENCIA_PADRAO,sampsPerBuffer,CICLO_POR_BUFFER,&desiredSampClkRate,&sampsPerCycle,&resultingSampClkRate,&resultingFrequency);
		if (status !=0)
			goto error;
		
		
		status = DAQmxCfgSampClkTiming(entradas_analogicas_forma_onda,"",resultingSampClkRate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChanHI_IN);
		if (status !=0)
			goto error;
		
		Delay_thread(.1);
		DAQmxReadAnalogF64 (entradas_analogicas_forma_onda, num_leit, time_out, DAQmx_Val_GroupByChannel, 
				leituras, num_leit, &tamanho_real, NULL);
	
		DAQmxStopTask(entradas_analogicas_forma_onda);
		DAQmxClearTask(entradas_analogicas_forma_onda);
		
	
		SetBreakOnLibraryErrors (1);
		return 0;	
		
error:	
	  
		DAQmxStopTask(entradas_analogicas_forma_onda);
		DAQmxClearTask(entradas_analogicas_forma_onda);
		
return -1;

}
//************************************int FormaOnda_daq6009_4ch *************************************************				
int FormaOnda_daq6009_4ch (double lim_min, double lim_max, int leit_por_seg,
	int num_leit, double *canal0, double *canal1, double *canal2,double *canal3, int berco) 
{
char 
	canal_nome[100];

		/////////////////////////////////////
		strcpy(canal_AD_DAQ_6210_string[berco], "Dev1/ai0:3");
		strcpy(canal_nome,"canal_todos");
		status = DAQmxCreateTask("",&analog_INP_handler_6210[berco]); 	
		status = DAQmxCreateAIVoltageChan(analog_INP_handler_6210[berco],canal_AD_DAQ_6210_string[berco], canal_nome, DAQmx_Val_Diff,lim_min,lim_max,DAQmx_Val_Volts,NULL);
		DAQmxReadAnalogF64 (analog_INP_handler_6210[berco], leit_por_seg, time_out, DAQmx_Val_GroupByChannel, leituras, num_leit,
                &tamanho_real, NULL);
return 0;
}

//************************************int LerDigital6009_Bit *************************************************				
int LerDigital6009_Bit (int porta,int *bits_lidos, int berco)
{
int	
	bit_escrever,
	tamanho = 100;
uInt8  
	bits_digitais[100];
int32 
	samples_escrita_per_channel= 1, 
	samples_per_channel_read, 
	bytesPerSamp;
float64 
	time_out_escrita = 1;//1 segundo

	///////////////////////////////////////////////////////////////
	status = DAQmxCreateTask("",&digital_port_handler_6210[berco]); 	
	if(porta == 0)
	{
		status = DAQmxCreateDIChan(digital_port_handler_6210[berco] , "Dev1/port0/line0:7", "",DAQmx_Val_ChanForAllLines);
	}
	else
	{
		status = DAQmxCreateDIChan(digital_port_handler_6210[berco] , "Dev1/port1/line0:3", "",DAQmx_Val_ChanForAllLines);
	}
	status = DAQmxReadDigitalLines(digital_port_handler_6210[berco], samples_escrita_per_channel,
		time_out_escrita,DAQmx_Val_GroupByChannel,bits_digitais,tamanho ,&samples_per_channel_read,&bytesPerSamp,NULL);
	if(porta == 0)
	{
			bits_lidos[0] = bits_digitais[0];
			bits_lidos[1] = bits_digitais[1];
			bits_lidos[2] = bits_digitais[2];
			bits_lidos[3] = bits_digitais[3];
			bits_lidos[4] = bits_digitais[4];
			bits_lidos[5] = bits_digitais[5];
			bits_lidos[6] = bits_digitais[6];
			bits_lidos[7] = bits_digitais[7];
	}
	else
	{
			bits_lidos[0] = bits_digitais[0];
			bits_lidos[1] = bits_digitais[1];
			bits_lidos[2] = bits_digitais[2];
			bits_lidos[3] = -1;
			bits_lidos[4] = -1;
			bits_lidos[5] = -1;
			bits_lidos[6] = -1;
			bits_lidos[7] = -1;
	}
	DAQmxStopTask(digital_port_handler_6210[berco]);
	DAQmxClearTask(digital_port_handler_6210[berco]);
 return 0;
}
