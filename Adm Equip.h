//==============================================================================
//
// Title:		AdmEquip.h
// Purpose:		A short description of the interface.
//
//==============================================================================


#define	CAMINHO_VM_DEFAULT			"..\\VM\\INOUT\\"

//==============================================================================
// Types

struct Recurso {

	int capacidade;
	float *dados;
	int ultimo;
	int nItens; 

};

//==============================================================================
// Global Variables
int 	vm_mode;
char	caminho_vm[250];

//==============================================================================
// Global functions

// funções para compartilhamento de recursos
void   registraRecurso( struct Recurso *f, int quant_bercos );
int    solicitaRecurso(struct Recurso *f, int num_berco);
int    liberaRecurso( struct Recurso *f, int num_berco );
// funções para VM
int    VM_FlushInQ (int portNumber);
int    VM_OpenComConfig (int portNumber, char deviceName[], long baudRate, int parity, int dataBits, int stopBits, int inputQueueSize, int outputQueueSize);
int    VM_CloseCom (int portNumber);
int    VM_ComRd (int portNumber, char buffer[], size_t count);
int    VM_ComWrt (int portNumber, char buffer[], size_t count);
int    VM_GetInQLen (int portNumber);
int    VM_ComRdTerm(int portNo, char buf[], size_t   maxCnt, int termCh);
int    VM_SetComTime (int portNumber, double timeout_seconds);
