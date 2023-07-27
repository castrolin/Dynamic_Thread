#pragma once

#include <Gdiplus.h>

#include "GlobalDefine.h"

#include "CommonFunc.h"

#include "LogSystemImport.h"

#include "PLC_Data_Structure.h"



//�Ҳձ��


//�Ҳյ�����



//�D�{�����
#include "GetRecipe.h"
#include "SystemParams.h"
#include "SystemCodeCtrl.h"
#include "SystemControlBase.h"
#include "PerformanceLog.h"

//�y�{��
#include "StepProcess.h"
#include "Scenario.h"
#include "AutoThread.h"
#include "Dynamic_Thread.h"

//�D�{��������
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
//OpenCV ����Include



//HANDLE
extern HANDLE g_hExit;		//�t�ΰh�XEvent
extern HANDLE g_hBreak;		//�t�ΰ���Event
extern HANDLE g_hAutoRun;	//�t��AutoRun Event
extern HANDLE g_hPause;		//�t�μȰ�Event
extern HANDLE g_hInitial;	//�t�Ϊ�l��

//�ܼ�
extern CString Project_Path;

//����
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
//����
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
