//==============================================================================
//
// Title:		CyberXML.c
// Purpose:		A short description of the implementation.
//
// Created on:	11/08/2018 at 15:44:57 by Alexandre.
// Copyright:	MS Tecnologia. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "msxml.h"
#include "CyberXML.h"
#include <formatio.h>


//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

#define hrChk(f) if (error = (f), FAILED (error)) goto Error; else


/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetXMLRecord (char *path, char *pathxsd, DADOS_ECU_XML *dados_ecu_local)
{

	int sucess = 0;
	HRESULT         error = S_OK;

	CVIXMLDocument   doc = 0;
	CVIXMLElement    rootElem = 0;
	CVIXMLElement    record = 0;
	// validação pela ferramenta da GM
	// Valida arquivo
	//status = XMLValidate(path, pathxsd, &errMsg);
	//if(status == -1) return -2;
	
	// Inicializa valores
	strcpy(dados_ecu_local->ecuid, "");
	strcpy(dados_ecu_local->serial, "");
	strcpy(dados_ecu_local->mkm1, "");
	strcpy(dados_ecu_local->mkm2, "");
	strcpy(dados_ecu_local->mkm3, "");
	strcpy(dados_ecu_local->mkm4, "");
	strcpy(dados_ecu_local->mkm5, "");
	strcpy(dados_ecu_local->ukm1, "");
	strcpy(dados_ecu_local->ukm2, "");
	strcpy(dados_ecu_local->ukm3, "");
	strcpy(dados_ecu_local->ukm4, "");
	strcpy(dados_ecu_local->ukm5, "");
	

	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);
	hrChk (CVIXMLLoadDocument (path, &doc));
	hrChk (CVIXMLGetRootElement (doc, &rootElem));
	hrChk (CVIXMLGetChildElementByTag(rootElem, "ecuRecord", &record));

	hrChk(GetEcuRecord(record, dados_ecu_local));


Error:
	CVIXMLDiscardElement (record);
	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);
	
	if (FAILED (error)) 
		return error;

	return sucess;
}
/*le o arquivo de resultado do teste local*/
int GetResultXMLRecord (char *path, char *pathxsd, DADOS_ECU_XML *dados_res)
{

	int sucess = 0;
	HRESULT         error = S_OK;

	CVIXMLDocument   doc = 0;
	CVIXMLElement    rootElem = 0;
	CVIXMLElement    record = 0;
	// validação pela ferramenta da GM
	// Valida arquivo
	//status = XMLValidate(path, pathxsd, &errMsg);
	//if(status == -1) return -2;
	
	// Inicializa valores
	dados_res->totalRecords = 0;
	dados_res->validRecords = 0;
	dados_res->invalidRecords = 0;
	strcpy(dados_res->ecuid, "");
	dados_res->mkValid = 0;
	dados_res->ukValid = 0;
	

	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);
	hrChk (CVIXMLLoadDocument (path, &doc));
	hrChk (CVIXMLGetRootElement (doc, &rootElem));

	hrChk (CVIXMLGetChildElementByTag(rootElem, "VerificationSummary", &record));
	hrChk(GetEcuRecord(rootElem, dados_res));
	hrChk (CVIXMLGetChildElementByTag(rootElem, "VerificationResult", &record));
	hrChk(GetEcuRecord(record, dados_res));


Error:
	CVIXMLDiscardElement (record);
	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);
	
	if (FAILED (error)) 
		return error;

	return sucess;
}


int GetElementValue(CVIXMLElement element, DADOS_ECU_XML *dados_ecu_local)
{

	char            
		value[200],
		tag[100];
	
	HRESULT         error = S_OK;


	hrChk(CVIXMLGetElementTag(element,tag));
	hrChk(CVIXMLGetElementValue(element,value));

	if (strcmp(tag,"ecuid")==0)
	{
		strcpy(dados_ecu_local->ecuid, value);
	}
	else if (strcmp(tag,"serialNo")==0)
	{
		strcpy(dados_ecu_local->serial, value);
	}
	else if (strcmp(tag,"mkm1") == 0)
	{
		strcpy(dados_ecu_local->mkm1, value);
	}
	else if (strcmp(tag,"mkm2") == 0)
	{
		strcpy(dados_ecu_local->mkm2, value);
	}
	else if (strcmp(tag,"mkm3") == 0)
	{
		strcpy(dados_ecu_local->mkm3, value);
	}
	else if (strcmp(tag,"mkm4") == 0)
	{
		strcpy(dados_ecu_local->mkm4, value);
	}
	else if (strcmp(tag,"mkm5") == 0)
	{
		strcpy(dados_ecu_local->mkm5, value);
	}
	else if (strcmp(tag,"ukm1") == 0)
	{
		strcpy(dados_ecu_local->ukm1, value);
	}
	else if (strcmp(tag,"ukm2") == 0)
	{
		strcpy(dados_ecu_local->ukm2, value);
	}
	else if (strcmp(tag,"ukm3") == 0)
	{
		strcpy(dados_ecu_local->ukm3, value);
	}
	else if (strcmp(tag,"ukm4") == 0)
	{
		strcpy(dados_ecu_local->ukm4, value);
	}
	else if (strcmp(tag,"ukm5") == 0)
	{
		strcpy(dados_ecu_local->ukm5, value);
	}
	else if (strcmp(tag,"MkValid") == 0)
	{
		if (strcmp(value, "true")==0)
			dados_ecu_local->mkValid=1;
		else if(strcmp(value, "false")==0)
			dados_ecu_local->mkValid=0;
	}
	else if (strcmp(tag,"UkValid") == 0)
	{
		if (strcmp(value, "true")==0)
			dados_ecu_local->ukValid=1;
		else if(strcmp(value, "false")==0)
			dados_ecu_local->ukValid=0;
	}
	else if (strcmp(tag,"totalRecords") == 0)
	{
		dados_ecu_local->totalRecords=atoi(value);
	}
	else if (strcmp(tag,"validRecords") == 0)
	{
		dados_ecu_local->validRecords=atoi(value);
	}
	else if (strcmp(tag,"invalidRecords") == 0)
	{
		dados_ecu_local->invalidRecords=atoi(value);
	}
	
return 0;

Error:

	return error;

}
/* obtem todos os elementos que estão dentro do parent */
CVIXMLElement GetEcuRecord(CVIXMLElement parent, DADOS_ECU_XML *dados_ecu_local)
{

	int 			i, numElements ;
	CVIXMLElement	element = 0;
	HRESULT         error = S_OK;
	

	hrChk(CVIXMLGetNumChildElements(parent,&numElements));
	

	for (i = 0; i < numElements; ++i)

	{
		hrChk(CVIXMLGetChildElementByIndex(parent, i, &element));
		hrChk(GetElementValue(element, dados_ecu_local)); 
	}


	return 0;

Error:
	return error;

}

static CAObjHandle LoadXMLDocument(const char *path)
{
	VBOOL success;
	CAObjHandle doc;
	VARIANT vtPath;

	MSXML2_NewDOMDocument40IXMLDOMDocument2(0, 0, LOCALE_NEUTRAL, 0, &doc);
	MSXML2_IXMLDOMDocument2Setasync(doc, 0, VFALSE);
	MSXML2_IXMLDOMDocument2SetvalidateOnParse(doc, 0, VFALSE);
	MSXML2_IXMLDOMDocument2SetresolveExternals(doc, 0, VFALSE);
	MSXML2_IXMLDOMDocument2SetpreserveWhiteSpace(doc, 0, VTRUE);
	CA_VariantSetCString(&vtPath, path);
	MSXML2_IXMLDOMDocument2load(doc, 0, vtPath, &success);
	//assert(success == VTRUE);
	CA_VariantClear(&vtPath);
	return doc;
}

/*--------------------------------------------------------------------------------------
   Salva arquivos para verificação
   tabular - formata os arquivos;
   local - se 1 grava para verificação local, se 0 grava para verificação on line
---------------------------------------------------------------------------------------*/
int SaveEcuRecord (char *path, int tabular, int local, DADOS_ECU_XML dados_ecu)
{

	int i, numElements ;
	int 
		apagar = 0,
		arq_existe,
		tamanho = 0;
		
	CVIXMLElement element = 0;
	char            *value = NULL;
	char			newValue[200]="";
	HRESULT         error = S_OK;
				
	//static
	CVIXMLDocument   doc = 0;
	CVIXMLElement    rootElem = 0;
	CVIXMLElement    record = 0;
	
	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);
	arq_existe = GetFileInfo (path, &tamanho);
	if(arq_existe == 1)
		hrChk (CVIXMLLoadDocument (path, &doc));
	else
		hrChk (CVIXMLNewDocument ("ecuRecordList", &doc));

	hrChk (CVIXMLGetRootElement (doc, &rootElem));
	hrChk (CVIXMLGetChildElementByTag(rootElem, "ecuRecord", &record));

	//
	// Remove o ecuRecord antigo, se for novo arquivo
	//
	if(apagar)
	{
		hrChk(CVIXMLGetNumChildElements(rootElem,&numElements));
		for (i = 0; i < numElements; ++i)
		{
			hrChk (CVIXMLGetChildElementByIndex(rootElem, i, &element));
				hrChk (CVIXMLRemoveElement(element));
		}
	}
	// Cria tag ecuRecord
	hrChk(CVIXMLNewElement(rootElem,-1,"ecuRecord", &record));

	// Cria tag ecuid
	hrChk(CVIXMLNewElement(record, -1,"ecuid", &element));
	Fmt(newValue,"%s",dados_ecu.ecuid);
	hrChk(CVIXMLSetElementValue (element, newValue));

	hrChk(CVIXMLNewElement(record,-1,"SerialNo", &element));
	Fmt(newValue,"%s",dados_ecu.serial);
	hrChk(CVIXMLSetElementValue (element, newValue));
	if(local)
	{
		hrChk(CVIXMLNewElement(record,-1,"mkm1", &element));
		Fmt(newValue,"%s",dados_ecu.mkm1);
		hrChk(CVIXMLSetElementValue (element, newValue));

		hrChk(CVIXMLNewElement(record,-1,"mkm2", &element));
		Fmt(newValue,"%s",dados_ecu.mkm2);
		hrChk(CVIXMLSetElementValue (element, newValue));

		hrChk(CVIXMLNewElement(record,-1,"mkm3", &element));
		Fmt(newValue,"%s",dados_ecu.mkm3);
		hrChk(CVIXMLSetElementValue (element, newValue));
	}
	hrChk(CVIXMLNewElement(record,-1,"mkm4", &element));
	Fmt(newValue,"%s",dados_ecu.mkm4);
	hrChk(CVIXMLSetElementValue (element, newValue));

	hrChk(CVIXMLNewElement(record,-1,"mkm5", &element));
	Fmt(newValue,"%s",dados_ecu.mkm5);
	hrChk(CVIXMLSetElementValue (element, newValue));

	if(local)
	{
		hrChk(CVIXMLNewElement(record,-1,"ukm1", &element));
		Fmt(newValue,"%s",dados_ecu.ukm1);
		hrChk(CVIXMLSetElementValue (element, newValue));

		hrChk(CVIXMLNewElement(record,-1,"ukm2", &element));
		Fmt(newValue,"%s",dados_ecu.ukm2);
		hrChk(CVIXMLSetElementValue (element, newValue));

		hrChk(CVIXMLNewElement(record,-1,"ukm3", &element));
		Fmt(newValue,"%s",dados_ecu.ukm3);
		hrChk(CVIXMLSetElementValue (element, newValue));
	}
	hrChk(CVIXMLNewElement(record,-1,"ukm4", &element));
	Fmt(newValue,"%s",dados_ecu.ukm4);
	hrChk(CVIXMLSetElementValue (element, newValue));

	hrChk(CVIXMLNewElement(record,-1,"ukm5", &element));
	Fmt(newValue,"%s",dados_ecu.ukm5);
	hrChk(CVIXMLSetElementValue (element, newValue));

	hrChk(CVIXMLSaveDocument (doc, tabular, path));
	
	CVIXMLDiscardElement (rootElem);
	CVIXMLDiscardDocument (doc);


Error:
	free (value);
	if (element)
		CVIXMLDiscardElement (element);
	if (record)
		CVIXMLDiscardElement (record);

	if (FAILED (error)) 
		return error;

	return 0;
}
/*--------------------------------------------------------------------------------------------
       Le arquivo de live key lidos durante a gravação dos parametros M1, M2, M3
       le os dados M4 e M5 se o ecuid for o mesmo do parametro de entrada
---------------------------------------------------------------------------------------------*/
int CarregaArqLiveKey(char * tab_live_key, DADOS_ECU_XML * dados_ecu_local, char * ecu_id)
{
int 
	i=0,
	arquivo=0,
	ecu_lido_confere = 0,
	serial_lido = 0,
	ukm4_lido_1 = 0,
	ukm4_lido_2 = 0,
	mkm4_lido_1 = 0,
	mkm4_lido_2 = 0,
	ukm5_lido   = 0,
	mkm5_lido   = 0,
	tamanho; 
char  
	linha_da_tabela[200]="", 
	resposta[100], 
	aux[250]; 

	////////////////////////////////////////////////////////////////////
			   
	arquivo = OpenFile( tab_live_key, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII ) ;
	if (arquivo < 0)
	{
		MessagePopup ("Erro ao abrir arquivo",
					  "Arquivo de live key não encontrado.");
	    return -1;
	}
	for(i=0; i < 10000 ; i++) //le até 10000 linhas
	{
    
		if(ReadLine (arquivo, linha_da_tabela, 80)<0)//fim do arquivo
		   break;
		strcpy (resposta, linha_da_tabela);
		tamanho = strlen(resposta);
		if (!tamanho) continue; //continua no loop se string for vazia
		//StringUpperCase (resposta);
	    if(strcmp(resposta, "FIM") == 0)
    		break;
    		
		else if(strstr (resposta, "ECU_ID="))
		{
			CopyString (aux, 0, resposta, strlen("ECU_ID="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			if(strcmp(aux, ecu_id) == 0)
			{
				strcpy(dados_ecu_local->ecuid, aux);
				ecu_lido_confere = 1;
			}
			else
			{
				ecu_lido_confere = 0;
			}
		}
		else if(strstr (resposta, "SERIAL=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("SERIAL="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->serial, aux);
			serial_lido = 1;
		}
		else if(strstr (resposta, "Master_M4_1=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M4_1="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->mkm4, aux);
			mkm4_lido_1 = 1;
		}
		else if(strstr (resposta, "Master_M4_2=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M4_2="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcat(dados_ecu_local->mkm4, aux);
			mkm4_lido_2 = 1;
		}
		else if(strstr (resposta, "Master_M5=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M5="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->mkm5, aux);
			mkm5_lido = 1;
		}
		else if(strstr (resposta, "Unlock_M4_1=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M4_1="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->ukm4, aux);
			ukm4_lido_1 = 1;
		}
		else if(strstr (resposta, "Unlock_M4_2=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M4_2="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcat(dados_ecu_local->ukm4, aux);
			ukm4_lido_2 = 1;
		}
		else if(strstr (resposta, "Unlock_M5=") && ecu_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M5="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->ukm5, aux);
			ukm5_lido = 1;
		}
		if(mkm5_lido && ukm5_lido && mkm4_lido_1 && mkm4_lido_2 && ukm4_lido_1 && ukm4_lido_2)
			break;
	}
	CloseFile (arquivo);

	
return ecu_lido_confere;	
}
/*--------------------------------------------------------------------------------------------
       Le arquivo de live key lidos durante a gravação dos parametros M1, M2, M3
       le o dado ecuid para o numero de serie de entrada
---------------------------------------------------------------------------------------------*/
int CarregaECUIDArqLiveKey(char * tab_live_key, DADOS_ECU_XML * dados_ecu_local, char * n_serie)
{
int 
	i=0,
	arquivo=0,
	serial_lido_confere = 0,
	ecu_id_lido = 0,
	ukm4_lido_1 = 0,
	ukm4_lido_2 = 0,
	mkm4_lido_1 = 0,
	mkm4_lido_2 = 0,
	ukm5_lido   = 0,
	mkm5_lido   = 0,
	tamanho; 
char  
	linha_da_tabela[200]="", 
	resposta[100], 
	aux[250]; 

	////////////////////////////////////////////////////////////////////
			   
	arquivo = OpenFile( tab_live_key, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII ) ;
	if (arquivo < 0)
	{
		MessagePopup ("Erro ao abrir arquivo",
					  "Arquivo de live key não encontrado.");
	    return -1;
	}
	for(i=0; i < 10000 ; i++) //le até 10000 linhas
	{
    
		if(ReadLine (arquivo, linha_da_tabela, 80)<0)//fim do arquivo
		   break;
		strcpy (resposta, linha_da_tabela);
		tamanho = strlen(resposta);
		if (!tamanho) continue; //continua no loop se string for vazia
		//StringUpperCase (resposta);
	    if(strcmp(resposta, "FIM") == 0)
    		break;
    		
		else if(strstr (resposta, "SERIAL="))
		{
			CopyString (aux, 0, resposta, strlen("SERIAL="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			if(strcmp(aux, n_serie) == 0)
			{
				strcpy(dados_ecu_local->serial, aux);
				serial_lido_confere = 1;
			}
			else
			{
				serial_lido_confere = 0;
			}
		}
		else if(strstr (resposta, "ECU_ID=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("ECU_ID="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->ecuid, aux);
			ecu_id_lido = 1;
		}
		else if(strstr (resposta, "Master_M4_1=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M4_1="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->mkm4, aux);
			mkm4_lido_1 = 1;
		}
		else if(strstr (resposta, "Master_M4_2=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M4_2="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcat(dados_ecu_local->mkm4, aux);
			mkm4_lido_2 = 1;
		}
		else if(strstr (resposta, "Master_M5=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Master_M5="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->mkm5, aux);
			mkm5_lido = 1;
		}
		else if(strstr (resposta, "Unlock_M4_1=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M4_1="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->ukm4, aux);
			ukm4_lido_1 = 1;
		}
		else if(strstr (resposta, "Unlock_M4_2=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M4_2="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcat(dados_ecu_local->ukm4, aux);
			ukm4_lido_2 = 1;
		}
		else if(strstr (resposta, "Unlock_M5=") && serial_lido_confere)
		{
			CopyString (aux, 0, resposta, strlen("Unlock_M5="), -1);
 	   		Scan(aux, "%s>%s", aux);//elimina tab ou espaco apos a string
			strcpy(dados_ecu_local->ukm5, aux);
			ukm5_lido = 1;
		}
		if(ecu_id_lido && mkm5_lido && ukm5_lido && mkm4_lido_1 && mkm4_lido_2 && ukm4_lido_1 && ukm4_lido_2)
			break;
	}
	CloseFile (arquivo);

	
return serial_lido_confere;	
}

