#include "stdafx.h"
#include "ShadeButtonST.h"
#include "GlobalObject.h"

//HANDLE
HANDLE g_hExit;			//�t�ΰh�XEvent
HANDLE g_hBreak;		//�t�ΰ���Event
HANDLE g_hAutoRun;		//�t��AutoRun Event
HANDLE g_hPause;		//�t�μȰ�Event
HANDLE g_hInitial;		//�t�Ϊ�l��

//�ܼ�
CString Project_Path;

//����
 LogServer *m_pLogServer;

 LogClient *LOG;

 CLanguageCtrl *LanguageCtrl;

 CSystemParams *SystemParams;

 CGetRecipe *ProcessRecipe;

 CStepProcess *StepProcess;

 //CStepProcess_PCB *StepProcess_PCB;

 //CStepProcess_Sticker *StepProcess_Sticker;

 CScenario *Scenario;

 CDynamic_Thread *Dynamic_Thread;

 CAutoThread *AutoTread;

 CSystemCodeCtrl *SystemCodeCtrl;

 CControlBase *ControlBase;

 CPerformanceLog *PerformanceLog;

//����
 CMessageBox *SystemMessageBox;

 COptionDlg *OptionDlg;

 COptionManualSelDlg *OptionManualSelDlg;

 CInputTestDlg *InputTestDlg;

 COutputTestDlg *OutputTestDlg;

 CUserAccountDlg *UserAccountDlg;

 CSystemParamsDlg *SystemParamsDlg;

 CRecipeSettingDlg *RecipeSettingDlg;

 CRecipeSettingCurrentDlg *RecipeSettingCurrentDlg;

 CRecipeListDlg *RecipeListDlg;

 CSystemStatusDlg *SystemStatusDlg;

 CMaintainPageDlg *MaintainPageDlg;

 CStepFuncDlg_PCB *StepFuncDlg;

 //CStepFuncDlg_Sticker *StepFuncDlg_Sticker;

 //CRobotStepFuncDlg *RobotStepFuncDlg;

 CSystemTraceDlg *SystemTraceDlg;

 CLogListDlg *LogListDlg;

 CPerformanceDlg *PerformanceDlg;

 CProduct_Data *Product_Data;
