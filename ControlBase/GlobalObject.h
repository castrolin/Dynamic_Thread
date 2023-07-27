#pragma once

#include <Gdiplus.h>

#include "GlobalDefine.h"

#include "CommonFunc.h"

#include "LogSystemImport.h"

#include "PLC_Data_Structure.h"



//模組控制項


//模組視窗項



//主程式控制項
#include "GetRecipe.h"
#include "SystemParams.h"
#include "SystemCodeCtrl.h"
#include "SystemControlBase.h"
#include "PerformanceLog.h"

//流程類
#include "StepProcess.h"
#include "Scenario.h"
#include "AutoThread.h"
#include "Dynamic_Thread.h"

//主程式視窗項
#include "MessageBox.h"
#include "MessageBoxCRC.h"
#include "MessageBoxYC.h"
#include "RecipeSettingDlg.h"
#include "RecipeSettingCurrentDlg.h"
#include "RecipeListDlg.h"
#include "OptionDlg.h"
#include "OptionManualSelDlg.h"
#include "SystemStatusDlg.h"
#include "SystemParams_Dlg.h"
#include "UserAccountDlg.h"
#include "MaintainPageDlg.h"
#include "StepFuncDlg_PCB.h"
//#include "StepFuncDlg_Sticker.h"
//#include "RobotStepFuncDlg.h"
#include "InputTestDlg.h"
#include "OutputTestDlg.h"
#include "SystemTraceDlg.h"
#include "LogListDlg.h"
#include "PerformanceDlg.h"
//OpenCV 相關Include



//HANDLE
extern HANDLE g_hExit;		//系統退出Event
extern HANDLE g_hBreak;		//系統停止Event
extern HANDLE g_hAutoRun;	//系統AutoRun Event
extern HANDLE g_hPause;		//系統暫停Event
extern HANDLE g_hInitial;	//系統初始化

//變數
extern CString Project_Path;

//元件
extern LogServer *m_pLogServer;

extern LogClient *LOG;

extern CLanguageCtrl *LanguageCtrl;

extern CSystemParams *SystemParams;

extern CGetRecipe *ProcessRecipe;

extern CStepProcess *StepProcess;

extern CDynamic_Thread *Dynamic_Thread;

extern CScenario *Scenario;

extern CAutoThread *AutoTread;

extern CSystemCodeCtrl *SystemCodeCtrl;

extern CControlBase *ControlBase;

extern CPerformanceLog *PerformanceLog;
//視窗
extern CMessageBox *SystemMessageBox;

extern COptionDlg *OptionDlg;

extern COptionManualSelDlg *OptionManualSelDlg;

extern CInputTestDlg *InputTestDlg;

extern COutputTestDlg *OutputTestDlg;

extern CUserAccountDlg *UserAccountDlg;

extern CSystemParamsDlg *SystemParamsDlg;

extern CRecipeSettingDlg *RecipeSettingDlg;

extern CRecipeSettingCurrentDlg *RecipeSettingCurrentDlg;

extern CRecipeListDlg *RecipeListDlg;

extern CSystemStatusDlg *SystemStatusDlg;

extern CMaintainPageDlg *MaintainPageDlg;

extern CStepFuncDlg_PCB *StepFuncDlg;

//extern CStepFuncDlg_Sticker *StepFuncDlg_Sticker;

//extern CRobotStepFuncDlg *RobotStepFuncDlg;

extern CSystemTraceDlg *SystemTraceDlg;

extern CLogListDlg *LogListDlg;

extern CPerformanceDlg *PerformanceDlg;

extern CProduct_Data *Product_Data;
