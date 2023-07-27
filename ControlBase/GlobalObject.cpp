#include "stdafx.h"
#include "ShadeButtonST.h"
#include "GlobalObject.h"

//HANDLE
HANDLE g_hExit;			//╰参癶Event
HANDLE g_hBreak;		//╰参氨ゎEvent
HANDLE g_hAutoRun;		//╰参AutoRun Event
HANDLE g_hPause;		//╰参既氨Event
HANDLE g_hInitial;		//╰参﹍て

//跑计
CString Project_Path;

//じン
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

//跌怠
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
