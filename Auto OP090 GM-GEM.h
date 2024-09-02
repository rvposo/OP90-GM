/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  AFERIR                           1
#define  AFERIR_TXT_MENSAGEM              2       /* control type: textBox, callback function: (none) */
#define  AFERIR_CMD_FINALIZAR             3       /* control type: command, callback function: VOLTA_AFERIR */
#define  AFERIR_CDM_START_APERTADEIRA     4       /* control type: command, callback function: Start_Apertadeira_AFERIR */
#define  AFERIR_LED_NOTOK                 5       /* control type: LED, callback function: (none) */
#define  AFERIR_LED_READY                 6       /* control type: LED, callback function: (none) */
#define  AFERIR_LED_OK                    7       /* control type: LED, callback function: (none) */
#define  AFERIR_DEC_APERTADEIRA           8       /* control type: deco, callback function: (none) */
#define  AFERIR_TXT_MENS_APERTADEIRA      9       /* control type: textMsg, callback function: (none) */
#define  AFERIR_TEXTMSG_12                10      /* control type: textMsg, callback function: (none) */

#define  AUTO                             2
#define  AUTO_TXT_TESTE_2                 2       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_TESTE                   3       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_SERIE_2                 4       /* control type: textBox, callback function: LeNSerie */
#define  AUTO_TXT_SERIE_1                 5       /* control type: textBox, callback function: LeNSerie */
#define  AUTO_TXT_MENSAGEM                6       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_MENSAGEM_2              7       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_NOME_2                  8       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_UNIDADE_2               9       /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_STATUS_2                10      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_TEMPO_2                 11      /* control type: textBox, callback function: (none) */
#define  AUTO_LIM_INF_2                   12      /* control type: textBox, callback function: (none) */
#define  AUTO_LIM_SUP_2                   13      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_RESULTADO               14      /* control type: textBox, callback function: (none) */
#define  AUTO_PICTURE                     15      /* control type: picture, callback function: CallBack_TEXT */
#define  AUTO_TXT_NOME                    16      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_UNIDADE                 17      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_STATUS                  18      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_TEMPO                   19      /* control type: textBox, callback function: (none) */
#define  AUTO_LIM_INF                     20      /* control type: textBox, callback function: (none) */
#define  AUTO_LIM_SUP                     21      /* control type: textBox, callback function: (none) */
#define  AUTO_TXT_RESULTADO_2             22      /* control type: textBox, callback function: (none) */
#define  AUTO_TEXTMSG_29                  23      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_48                  24      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_47                  25      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_30                  26      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_46                  27      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_31                  28      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_36                  29      /* control type: textMsg, callback function: (none) */
#define  AUTO_BOTAOZERA                   30      /* control type: command, callback function: ZeraProducao */
#define  AUTO_TEXTMSG_4                   31      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_10                  32      /* control type: textMsg, callback function: (none) */
#define  AUTO_SERIAL_ENDITEM_1            33      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_11                  34      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_12                  35      /* control type: textMsg, callback function: (none) */
#define  AUTO_TXT_MAQUINA                 36      /* control type: textMsg, callback function: (none) */
#define  AUTO_PICTURE_2                   37      /* control type: picture, callback function: CallBack_TEXT */
#define  AUTO_AMOSTRA_TIPO                38      /* control type: textMsg, callback function: (none) */
#define  AUTO_PN_GM                       39      /* control type: textMsg, callback function: (none) */
#define  AUTO_MODELO_DISPLAY              40      /* control type: textMsg, callback function: (none) */
#define  AUTO_PN_VISTEON                  41      /* control type: textMsg, callback function: (none) */
#define  AUTO_DESCRICAO_MODELO            42      /* control type: textMsg, callback function: (none) */
#define  AUTO_TABELA                      43      /* control type: textMsg, callback function: (none) */
#define  AUTO_SERIAL_ENDITEM_2            44      /* control type: textMsg, callback function: (none) */
#define  AUTO_MODELOS                     45      /* control type: ring, callback function: ModelosCallback */
#define  AUTO_DECORATION_6                46      /* control type: deco, callback function: (none) */
#define  AUTO_DECORATION_5                47      /* control type: deco, callback function: (none) */
#define  AUTO_TEXTMSG                     48      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEMPO_TOTAL_2               49      /* control type: numeric, callback function: (none) */
#define  AUTO_TEMPO_TOTAL                 50      /* control type: numeric, callback function: (none) */
#define  AUTO_TXT_TESTADOS                51      /* control type: textMsg, callback function: (none) */
#define  AUTO_TXT_REJEITADOS              52      /* control type: textMsg, callback function: (none) */
#define  AUTO_TXT_FTT                     53      /* control type: textMsg, callback function: (none) */
#define  AUTO_TXT_APROVADOS               54      /* control type: textMsg, callback function: (none) */
#define  AUTO_MSG_NOME                    55      /* control type: textMsg, callback function: (none) */
#define  AUTO_LED_CIM                     56      /* control type: LED, callback function: (none) */
#define  AUTO_MENS_FALHA_2                57      /* control type: string, callback function: (none) */
#define  AUTO_MENS_FALHA                  58      /* control type: string, callback function: (none) */
#define  AUTO_PRESENCA_2                  59      /* control type: LED, callback function: (none) */
#define  AUTO_PRESENCA                    60      /* control type: LED, callback function: (none) */
#define  AUTO_PIC_INSTRUCAO_2             61      /* control type: picture, callback function: CallBack_TEXT */
#define  AUTO_PIC_INSTRUCAO               62      /* control type: picture, callback function: CallBack_TEXT */
#define  AUTO_BIMANUAL_REMOTO             63      /* control type: command, callback function: BimanualRemoto */
#define  AUTO_TEXTMSG_37                  64      /* control type: textMsg, callback function: (none) */
#define  AUTO_REJ_REMOTO                  65      /* control type: command, callback function: RejRemoto */
#define  AUTO_CONT_REMOTO                 66      /* control type: command, callback function: ContRemoto */
#define  AUTO_TEXTMSG_38                  67      /* control type: textMsg, callback function: (none) */
#define  AUTO_TXT_VERSAO                  68      /* control type: textMsg, callback function: (none) */
#define  AUTO_VERSAO_TABS                 69      /* control type: textMsg, callback function: (none) */
#define  AUTO_LED_MSAMPLE_1               70      /* control type: LED, callback function: (none) */
#define  AUTO_LED_NEGSAMPLE_1             71      /* control type: LED, callback function: (none) */
#define  AUTO_TEXTMSG_2                   72      /* control type: textMsg, callback function: (none) */
#define  AUTO_BUT_REJEiTA_2               73      /* control type: command, callback function: Rej_v_2 */
#define  AUTO_TEXTMSG_44                  74      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_42                  75      /* control type: textMsg, callback function: (none) */
#define  AUTO_BUT_REJEiTA_1               76      /* control type: command, callback function: Rej_v_1 */
#define  AUTO_TEXTMSG_28                  77      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_33                  78      /* control type: textMsg, callback function: (none) */
#define  AUTO_TEXTMSG_45                  79      /* control type: textMsg, callback function: (none) */
#define  AUTO_RETRABALHO_2                80      /* control type: LED, callback function: (none) */
#define  AUTO_RETRABALHO_1                81      /* control type: LED, callback function: (none) */
#define  AUTO_S_BC_1                      82      /* control type: command, callback function: Send_BC_1 */
#define  AUTO_S_BC_2                      83      /* control type: command, callback function: Send_BC_2 */
#define  AUTO_PP_2                        84      /* control type: radioButton, callback function: Prod_2 */
#define  AUTO_PP_1                        85      /* control type: radioButton, callback function: Prod_1 */
#define  AUTO_LED_BI                      86      /* control type: LED, callback function: (none) */
#define  AUTO_LED_REJ                     87      /* control type: LED, callback function: (none) */
#define  AUTO_LED_CONT                    88      /* control type: LED, callback function: (none) */
#define  AUTO_LED_LC                      89      /* control type: LED, callback function: (none) */
#define  AUTO_LED_TRD                     90      /* control type: LED, callback function: (none) */
#define  AUTO_MASCARA                     91      /* control type: ring, callback function: MascaraCallback */

#define  LOGO_BAR                         3
#define  LOGO_BAR_PICTURE                 2       /* control type: picture, callback function: CallBack_TEXT */
#define  LOGO_BAR_VERSAO_2                3       /* control type: textMsg, callback function: (none) */
#define  LOGO_BAR_VERSAO                  4       /* control type: textMsg, callback function: (none) */
#define  LOGO_BAR_TEXTMSG_5               5       /* control type: textMsg, callback function: (none) */
#define  LOGO_BAR_TEXTMSG_3               6       /* control type: textMsg, callback function: (none) */
#define  LOGO_BAR_COMMANDBUTTON           7       /* control type: command, callback function: ESC_BAR */

#define  REJ_PARAF                        4
#define  REJ_PARAF_FOTO_REJ_PARAF         2       /* control type: picture, callback function: (none) */


     /* Control Arrays: */

#define  A_AMOSTRA                        1
#define  A_DESCRICAO_MODELO               2
#define  A_PN_VISTEON                     3
#define  A_SERIAL_ENDITEM                 4
#define  A_TABELA                         5
#define  ARRAYLIMINF                      6
#define  ARRAYLIMSUP                      7
#define  ARRAYMENSAGEM                    8
#define  ARRAYMENSFALHA                   9
#define  ARRAYNOME                        10
#define  ARRAYPICINSTRUCAO                11
#define  ARRAYPRESENCA                    12
#define  ARRAYRESULTADO                   13
#define  ARRAYSTATUS                      14
#define  ARRAYTEMPO                       15
#define  ARRAYTESTE                       16
#define  ARRAYUNIDADE                     17
#define  CTRLARRAY                        18

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_MANUAL             3       /* callback function: Manual_Bar */
#define  MENUBAR_MENU1_SEPARATOR          4
#define  MENUBAR_MENU1_SAIR_PROG          5       /* callback function: Quit_Bar */
#define  MENUBAR_MENU2                    6
#define  MENUBAR_MENU2_ITEM1_2            7       /* callback function: ColetaDados_Bar */
#define  MENUBAR_MENU2_ITEM1              8       /* callback function: Version_Bar */


     /* Callback Prototypes: */

int  CVICALLBACK BimanualRemoto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallBack_TEXT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ColetaDados_Bar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ContRemoto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ESC_BAR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LeNSerie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Manual_Bar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK MascaraCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelosCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Prod_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Prod_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Quit_Bar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Rej_v_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rej_v_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RejRemoto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Send_BC_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Send_BC_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start_Apertadeira_AFERIR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Version_Bar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK VOLTA_AFERIR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeraProducao(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
