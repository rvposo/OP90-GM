//==============================================================================
//
// Title:		CyberXML.h
// Purpose:		A short description of the interface.
//
// Created on:	29/08/2018 at 12:23:57 by Alexandre.
// Copyright:	Microsoft. All Rights Reserved.
//
//==============================================================================

#ifndef __CyberXML_H__
#define __CyberXML_H__

#ifdef __cplusplus
    extern "C" {
#endif
		
#define hrChk(f) if (error = (f), FAILED (error)) goto Error; else

//==============================================================================
// Include files

#include "cvixml.h"
#include "cvidef.h"
#include <ansi_c.h>
#include <msxml6.h>

//==============================================================================
// Constants
#define SAVE_CHECK_ONLINE	0
#define SAVE_CHECK_LOCAL	1
#define TABULAR_OFF			0
#define TABULAR_ON			1
//==============================================================================
// Types
////////// usado para verificação local /////////
typedef struct {
	char
		 ecuid[35],
		 serial[35],
		 mkm1[50],
		 mkm2[50],
		 mkm3[50],
		 mkm4[70],
		 mkm5[50],
		 ukm1[50],
		 ukm2[50],
		 ukm3[50],
		 ukm4[70],
		 ukm5[50];
	int
		totalRecords,
		validRecords,
		invalidRecords,
		mkValid,
		ukValid;
		 
}DADOS_ECU_XML;
///////// usado para arquivo de resposta ////////
typedef struct {
	char
		 totalRecords[30],
		 validRecords[30],
		 ecuid[50];   // ecu serial
	int
		 mkValid, // true or false
		 ukValid; // true or false
		 
}DADOS_RESULT_XML;

//==============================================================================
// External variables

//==============================================================================
// Global functions

int GetXMLRecord (char *path, char *pathxsd, DADOS_ECU_XML *dados_res);
int GetResultXMLRecord (char *path, char *pathxsd, DADOS_ECU_XML *dados_res);
int SaveEcuRecord (char *path, int tabular, int local, DADOS_ECU_XML dados_cfg_cyber);
CVIXMLElement GetEcuRecord(CVIXMLElement parent, DADOS_ECU_XML *dados_cfg_cyber);
int GetElementValue(CVIXMLElement element, DADOS_ECU_XML *dados_cfg_cyber);
int GetAttrValue(CVIXMLElement element, char *AttrName, char *Result);
int validateXMLFile(char *sFName, char *sError);
int CarregaArqLiveKey(char * tab_live_key, DADOS_ECU_XML *dados_ecu_local, char * ecuid);
int CarregaECUIDArqLiveKey(char * tab_live_key, DADOS_ECU_XML * dados_ecu_local, char * n_serie);

#ifdef __cplusplus
    }
#endif

#endif  /* endif __CyberXML_H__ */
