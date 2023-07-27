#include "stdafx.h"
#include "Scenario.h"

// Adding the StepProcess function inside.
 

CScenario::CScenario()
{

	m_CloseThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	RBExecute = FALSE;
	RBAbnormal = FALSE;
	m_RBStatus = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_RBThread = AfxBeginThread(RBProc,  (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_RBThread->m_bAutoDelete = FALSE;
	m_RBThread->ResumeThread();

	CVExecute = FALSE;
	CVAbnormal = FALSE;
	m_CVStatus= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_CVThread = AfxBeginThread(CVProc,  (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_CVThread->m_bAutoDelete = FALSE;
	m_CVThread->ResumeThread();

	PCBExecute = FALSE;
	PCBAbnormal = FALSE;
	m_PCBStatus= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_PCBThread = AfxBeginThread(PCBProc,  (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_PCBThread->m_bAutoDelete = FALSE;
	m_PCBThread->ResumeThread();
}

CScenario::~CScenario()
{
	SetEvent(m_CloseThreadEvent);
}

UINT CScenario::RBProc(LPVOID Info)
{
	CScenario* this_obj = (CScenario*) Info;

	if(WaitForSingleObject(this_obj->m_CloseThreadEvent, 0) != WAIT_FAILED )
	{
		ResetEvent(this_obj->m_CloseThreadEvent); // The check

		this_obj->RobotStatus();		
	}

	return 0;
	
}

UINT CScenario::CVProc(LPVOID Info)
{
	CScenario* this_obj = (CScenario*) Info;

	if(WaitForSingleObject(this_obj->m_CloseThreadEvent, 0) != WAIT_FAILED )
	{
		ResetEvent(this_obj->m_CloseThreadEvent); 
		this_obj->CVStatus();	
	}

	return 0;

}

UINT CScenario::PCBProc(LPVOID Info)
{
	CScenario* this_obj = (CScenario*) Info;

	if(WaitForSingleObject(this_obj->m_CloseThreadEvent, 0) != WAIT_OBJECT_0 )
	{
		ResetEvent(this_obj->m_CloseThreadEvent);// The check

		this_obj->PCBStatus();

	}
	return 0;
}

void CScenario::RobotStatus()
{
	//BOOL bLoop = TRUE;

	//while(bLoop)
	//{
	//	try
	//	{
	//		if(WaitForSingleObject(m_RBStatus,0) == WAIT_OBJECT_0)
	//		{
	//			RBAbnormal = FALSE;
	//			::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_ROBOT, (WPARAM)Scenario->RBStep ,NULL);

	//			do 
	//			{
	//				Sleep(1000);
	//				TRACE("The Label machine has not provided label");
	//			} while (InputControl->GetInput(X016_TAPE_EMPTY) == true );


	//			StepProcess->Proc_Robot_Get_Tape(); //Get the label from machine

	//			if(InputControl->GetInput(InputControl->GetInput(X026_RB_VAC) == true))
	//			{
	//				StepProcess->Proc_Robot_Move_Port(PORT_TAPE_CCD);

	//				do 
	//				{
	//					Sleep(1000);
	//					TRACE("Panel is not exist!!");
	//				} while (InputControl->GetInput(X021_CV_EMPTY) == true); // If the cv hasn't load any panel;

	//				if(InputControl->GetInput(X021_CV_EMPTY) == false && Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE)
	//				{
	//					TRACE("RB Stick Sticker \n");	

	//					RBExecute = TRUE;

	//					m_dManual_Offset_X = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_X;
	//					m_dManual_Offset_Y = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_Y;
	//					m_dManual_Offset_T = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_T;

	//					//0 Deg
	//					if(SystemParams->GetSystemParamData()->bPuttingMode == 1)
	//					{
	//						m_dTotal_Offset_X = m_dManual_Offset_X + m_dPCB_Offset_X - m_dSticker_Offset_Y;
	//						m_dTotal_Offset_Y = m_dManual_Offset_Y + m_dPCB_Offset_Y + m_dSticker_Offset_X;
	//						m_dTotal_Offset_T = m_dManual_Offset_T - m_dPCB_Offset_T + m_dSticker_Offset_T;
	//					}
	//					else
	//					{
	//						m_dTotal_Offset_X = m_dManual_Offset_X + m_dPCB_Offset_X + m_dSticker_Offset_Y;
	//						m_dTotal_Offset_Y = m_dManual_Offset_Y + m_dPCB_Offset_Y - m_dSticker_Offset_X;
	//						m_dTotal_Offset_T = m_dManual_Offset_T - m_dPCB_Offset_T + m_dSticker_Offset_T;
	//					}

	//					StepProcess->Proc_Robot_Put_Tape(m_dTotal_Offset_X, m_dTotal_Offset_Y, m_dTotal_Offset_T);
	//					ResetEvent(m_RBStatus);

	//					Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_PROCESSING);
	//					Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_DONE);
	//				}

	//			}
	//			else
	//			{
	//				StepProcess->Proc_Robot_Move_Port(PORT_TAPE);
	//			}
	//			do 
	//			{
	//				if(InputControl->GetInput(X026_RB_VAC) == false && Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
	//				{
	//					StepProcess->Proc_Robot_Move_Port(PORT_TAPE);
	//					break;
	//				}
	//				else
	//					Sleep(1000);
	//			} while (InputControl->GetInput(X021_CV_EMPTY)==false);
	//			

	//		}
	//	}
	//	catch(SYSTEM_ERROR &ex)
	//	{
	//		
	//		ex.SetLocation("RB_Thread");

	//		ResetEvent(m_RBStatus);

	//		RBExecute = FALSE;


	//		LOG->Message_Error(Log_Main, ex.GetErrorMessage());

	//		SetSystemAlarm();
	//		RBAbnormal = TRUE;

	//		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
	//			bLoop = FALSE;

	//		Sleep(1);
	//		continue;
	//	}
	//}
	

}

void CScenario::CVStatus()
{
	//BOOL bLoop = TRUE;

	//while(bLoop)
	//{
	//	try
	//	{
	//		if(WaitForSingleObject(m_CVStatus,0) == WAIT_OBJECT_0)
	//		{
	//			CVAbnormal = FALSE;
	//			::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_CV, (WPARAM)Scenario->CVStep ,NULL);

	//			if(InputControl->GetInput(X021_CV_EMPTY) == true)
	//			{

	//				OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

	//				TRACE("CV Import \n");
	//				CVExecute = TRUE;

	//				bool bPanelEmpty = false;
	//				do
	//				{
	//					Sleep(1);
	//					bPanelEmpty = InputControl->GetInput(X021_CV_EMPTY);

	//				}while(bPanelEmpty == true && WaitForSingleObject(g_hAutoRun, 0) == WAIT_OBJECT_0);

	//				if(WaitForSingleObject(g_hAutoRun, 0) == WAIT_OBJECT_0)
	//				{
	//					Product_Data->SetProductExist(EXP_PRODUCT_EXIST);
	//					Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_IDLE);
	//				}

	//				Sleep(100);
	//			}
	//			else if(InputControl->GetInput(X021_CV_EMPTY) == false && Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
	//			{
	//				TRACE("CV Export \n");
	//				CVExecute = TRUE;
	//				OutputControl->SetOutput(Y021_REQ_CV_STOP, false);

	//				bool bPanelEmpty = false;

	//				do
	//				{
	//					Sleep(1);
	//					bPanelEmpty = InputControl->GetInput(X021_CV_EMPTY);

	//				}while(bPanelEmpty == false);



	//				Sleep(SystemParams->GetSystemParamData()->OUT_CV_Delay);

	//				Product_Data->SetProductExist(EXP_PRODUCT_EMPTY);
	//				Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_UNKNOWN);


	//				OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

	//				Sleep(100);
	//				
	//			}
	//			else
	//			{
	//				TRACE("CV Import \n");
	//				Product_Data->SetProductExist(EXP_PRODUCT_EXIST);
	//				Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_IDLE);
	//				ResetEvent(m_CVStatus);
	//			}

	//			ResetEvent(m_CVStatus);
	//		}
	//	}
	//	catch(SYSTEM_ERROR &ex)
	//	{
	//		ex.SetLocation("CV_Thread");

	//		ResetEvent(m_CVStatus);

	//		CVExecute = FALSE;


	//		LOG->Message_Error(Log_Main, ex.GetErrorMessage());

	//		SetSystemAlarm();
	//		CVAbnormal = TRUE;

	//		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
	//			bLoop = FALSE;

	//		Sleep(1);
	//		continue;
	//	}
	//}

}

void CScenario::PCBStatus()
{
	//BOOL bLoop = TRUE;
	//BOOL bRet;

	//while(bLoop)
	//{
	//	try
	//	{
	//		if(WaitForSingleObject(m_PCBStatus,0) == WAIT_OBJECT_0)
	//		{
	//			PCBAbnormal = FALSE;
	//			::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_PCB_PRESS, (WPARAM)Scenario->PCBStep ,NULL);

	//			if(!InputControl->GetInput(X021_CV_EMPTY) && Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE)
	//			{
	//				Sleep(500);

	//				TRACE("PCB Clamp \n");

	//				PCBExecute = TRUE;

	//				BOOL bPCB_Clamp = FALSE;
	//				do 
	//				{
	//					Sleep(500);
	//					bPCB_Clamp = StepProcess->Proc_PCB_Clamp(10000);
	//				} while (bPCB_Clamp == FALSE);


	//				bRet = FALSE;
	//				for(int x = 0; x < 3; x ++ )
	//				{
	//					bRet = StepProcess_PCB->Proc_CCD_Align(m_dPCB_Offset_X, m_dPCB_Offset_Y, m_dPCB_Offset_T);
	//					if(bRet == TRUE)
	//						break;
	//				}

	//				if(bRet == FALSE)
	//				{
	//					ULONG nRet = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
	//					throw SYSTEM_ERROR("PCB_CLAMP", _MODULE_ERROR_PROCESS, &nRet);	
	//				}
	//				ResetEvent(m_PCBStatus);
	//			}
	//			else if(!InputControl->GetInput(X021_CV_EMPTY) && Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
	//			{
	//				TRACE("PCB Release \n");

	//				PCBExecute = TRUE;
	//				StepProcess->Proc_PCB_Release(10000);

	//				Sleep(500);
	//				ResetEvent(m_PCBStatus);
	//			}
	//			else if (WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
	//			{
	//				ResetEvent(m_PCBStatus);
	//			}
	//			else
	//			{
	//				TRACE("Unexpected Error was occured");
	//				ULONG nRet = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
	//				throw SYSTEM_ERROR("PCB_CLAMP", _MODULE_ERROR_PROCESS, &nRet);
	//				ResetEvent(m_PCBStatus);

	//			}


	//		}
	//	}
	//	catch(SYSTEM_ERROR &ex)
	//	{
	//		ex.SetLocation("PCB_Thread");

	//		ResetEvent(m_PCBStatus);

	//		PCBExecute = FALSE;


	//		LOG->Message_Error(Log_Main, ex.GetErrorMessage());

	//		SetSystemAlarm();
	//		PCBAbnormal = TRUE;

	//		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
	//			bLoop = FALSE;

	//		Sleep(1);
	//		continue;
	//	}
	//}

}
/*

void CScenario::RobotStatus()
{
	BOOL b_Conti = TRUE;
	BOOL bRet = FALSE;
	RBStep = 0;
	DWORD nErrorCode = 0;

	while(b_Conti)
	{
		try
		{
			if(WaitForSingleObject(m_RBStatus, 0) == WAIT_OBJECT_0)
				{
					RBAbnormal = FALSE;
					::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_ROBOT, (WPARAM)Scenario->RBStep ,NULL);
					switch(RBStep)
					{
					case 1:

						TRACE("RB back to Safty Position \n");

						RBExecute = TRUE;
						StepProcess->Proc_Robot_Move_Port(PORT_TAPE);
						

						ResetEvent(m_RBStatus);
						break;
					case 10 :
						
						TRACE("RB Take Sticker \n");

						RBExecute = TRUE;
						StepProcess->Proc_Robot_Get_Tape();
						
						
						ResetEvent(m_RBStatus);

						break;
					case 20 :

						if(InputControl->GetInput(X026_RB_VAC) == true) 
						{
							TRACE("RB CCD Align \n");

							RBExecute = TRUE;

							bRet = FALSE;
							
							StepProcess->Proc_Robot_Move_Port(PORT_TAPE_CCD);

							for(int x = 0; x < 3; x ++ )
							{
								bRet = StepProcess_Sticker->Proc_CCD_Align(m_dSticker_Offset_X,m_dSticker_Offset_Y,m_dSticker_Offset_T);
								if(bRet == TRUE)
									break;
							}

							if(bRet == FALSE)
							{
								ULONG nRet = _ALARM_PROC_STEPPROCESS_TAPE_PATTERN_FIND_FAIL;
								throw SYSTEM_ERROR("RobotStatus RBStep = 20", _MODULE_ERROR_PROCESS, &nRet);	
							}
							
							ResetEvent(m_RBStatus);
						}
						else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
						{
							
							ResetEvent(m_RBStatus);
						}

						
						
						break;
					case 30 :
						if((Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE))
						{
							TRACE("RB PCB Align \n");

							RBExecute = TRUE;
							bRet = FALSE;

							for(int x = 0; x < 3; x ++ )
							{
								bRet = StepProcess_PCB->Proc_CCD_Align(m_dPCB_Offset_X, m_dPCB_Offset_Y, m_dPCB_Offset_T);
								if(bRet == TRUE)
									break;
							}

							if(bRet == FALSE)
							{
								ULONG nRet = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
								throw SYSTEM_ERROR("RobotStatus RBStep = 30", _MODULE_ERROR_PROCESS, &nRet);	
							}

							ResetEvent(m_RBStatus);
							
						}
						else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
						{
							ResetEvent(m_RBStatus);
						}
						
						ResetEvent(m_RBStatus);

						break;
					case 40 :

						if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE)
						{
							TRACE("RB Stick Sticker \n");	

							RBExecute = TRUE;

							m_dManual_Offset_X = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_X;
							m_dManual_Offset_Y = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_Y;
							m_dManual_Offset_T = ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_T;

							//0 Deg
							if(SystemParams->GetSystemParamData()->bPuttingMode == 1)
							{
								m_dTotal_Offset_X = m_dManual_Offset_X + m_dPCB_Offset_X - m_dSticker_Offset_Y;
								m_dTotal_Offset_Y = m_dManual_Offset_Y + m_dPCB_Offset_Y + m_dSticker_Offset_X;
								m_dTotal_Offset_T = m_dManual_Offset_T - m_dPCB_Offset_T + m_dSticker_Offset_T;
							}
							else
							{
								m_dTotal_Offset_X = m_dManual_Offset_X + m_dPCB_Offset_X + m_dSticker_Offset_Y;
								m_dTotal_Offset_Y = m_dManual_Offset_Y + m_dPCB_Offset_Y - m_dSticker_Offset_X;
								m_dTotal_Offset_T = m_dManual_Offset_T - m_dPCB_Offset_T + m_dSticker_Offset_T;
							}

							StepProcess->Proc_Robot_Put_Tape(m_dTotal_Offset_X, m_dTotal_Offset_Y, m_dTotal_Offset_T);
							ResetEvent(m_RBStatus);

							Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_PROCESSING);
							Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_DONE);

						}
						else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
						{
							ResetEvent(m_RBStatus);
						}

						ResetEvent(m_RBStatus);

						break;
					}
					RBExecute = FALSE;
					
			}
			if(WaitForSingleObject(g_hBreak,0)== WAIT_OBJECT_0 
				&&WaitForSingleObject(g_hPause,0)== WAIT_OBJECT_0)
			{
				RBExecute = FALSE;
				ResetEvent(m_RBStatus);
			}

		}
		catch(SYSTEM_ERROR &ex)
		{
			ex.SetLocation("RB_Thread");

			ResetEvent(m_RBStatus);

			RBExecute = FALSE;

			
			LOG->Message_Error(Log_Main, ex.GetErrorMessage());

			SetSystemAlarm();
			RBAbnormal = TRUE;

			if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
				b_Conti = FALSE;

			Sleep(1);
			continue;
		}
		
		
		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
			b_Conti = FALSE;

		Sleep(1);
	}
}

void CScenario::CVStatus()
{
	BOOL b_Conti = TRUE;
	CVStep = 0;
	DWORD nErrorCode = 0;


	while(b_Conti)
	{
		try
		{
			if(WaitForSingleObject(m_CVStatus, 0) == WAIT_OBJECT_0 )
			{
				CVAbnormal = FALSE;
				::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_CV, (WPARAM)Scenario->CVStep ,NULL);
				switch(CVStep)
				{
				case 10 :

					OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

					if(InputControl->GetInput(X021_CV_EMPTY) == true)
					{
						TRACE("CV Import \n");
						CVExecute = TRUE;

						bool bPanelEmpty = false;
						do
						{
							Sleep(1);
							bPanelEmpty = InputControl->GetInput(X021_CV_EMPTY);

						}while(bPanelEmpty == true && WaitForSingleObject(g_hAutoRun, 0) == WAIT_OBJECT_0);

						if(WaitForSingleObject(g_hAutoRun, 0) == WAIT_OBJECT_0)
						{
							Product_Data->SetProductExist(EXP_PRODUCT_EXIST);
							Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_IDLE);
						}
						
						Sleep(100);

						ResetEvent(m_CVStatus);
					}
					else
					{
						TRACE("CV Import \n");
						Product_Data->SetProductExist(EXP_PRODUCT_EXIST);
						Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_IDLE);
						ResetEvent(m_CVStatus);
					}
					
					
					break;
				case 20 :

					if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
					{
						TRACE("CV Export \n");
						CVExecute = TRUE;
						OutputControl->SetOutput(Y021_REQ_CV_STOP, false);

						bool bPanelEmpty = false;

						do
						{
							Sleep(1);
							bPanelEmpty = InputControl->GetInput(X021_CV_EMPTY);

						}while(bPanelEmpty == false);

						
				
						Sleep(SystemParams->GetSystemParamData()->OUT_CV_Delay);
		
						Product_Data->SetProductExist(EXP_PRODUCT_EMPTY);
						Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_UNKNOWN);

						
						OutputControl->SetOutput(Y021_REQ_CV_STOP, true);
						
						Sleep(100);

						ResetEvent(m_CVStatus);
					}
					else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
					{
						ResetEvent(m_CVStatus);
					}
					
					
					break;
				}
				CVExecute = FALSE;
			}
		}
		catch(SYSTEM_ERROR &ex)
		{
			ex.SetLocation("CV_Thread");
			ResetEvent(m_CVStatus);
			CVExecute = FALSE;
			LOG->Message_Error(Log_Main, ex.GetErrorMessage());
			SetSystemAlarm();
			CVAbnormal = TRUE;

			if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
				b_Conti = FALSE;

			Sleep(1);
			continue;
		}
		
		CVExecute = FALSE;
		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
			b_Conti = FALSE;
		Sleep(1);
	}
}

void CScenario::PCBStatus()
{
	BOOL b_Conti = TRUE;
	PCBStep = 0;
	DWORD nErrorCode = 0;

	while(b_Conti)
	{
		try
		{
			if(WaitForSingleObject(m_PCBStatus, 0) == WAIT_OBJECT_0 )
			{
				PCBAbnormal = FALSE;
				::SendMessage(SystemStatusDlg->GetSafeHwnd(),CWM_SYS_UPDATE_PRCESS_STATUS_PCB_PRESS, (WPARAM)Scenario->PCBStep ,NULL);
				switch(PCBStep)
				{
				case 10 :
					if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE)
					{
						Sleep(500);

						TRACE("PCB Clamp \n");

						PCBExecute = TRUE;
						StepProcess->Proc_PCB_Clamp(10000);
						ResetEvent(m_PCBStatus);
					}
					else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
					{
						ResetEvent(m_PCBStatus);
					}

					break;
				case 20 :
					if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
					{
						TRACE("PCB Release \n");

						PCBExecute = TRUE;
						StepProcess->Proc_PCB_Release(10000);

						Sleep(500);
						ResetEvent(m_PCBStatus);
					}
					else if(WaitForSingleObject(g_hAutoRun, 0) != WAIT_OBJECT_0)
					{
						ResetEvent(m_PCBStatus);
					}

					break;
				}
				PCBExecute = FALSE;
			}
			
			
		}
		catch(SYSTEM_ERROR &ex)
		{
			ex.SetLocation("PCB_Thread");
			ResetEvent(m_PCBStatus);
			PCBExecute = FALSE;
			LOG->Message_Error(Log_Main, ex.GetErrorMessage());
			SetSystemAlarm();
			PCBAbnormal = TRUE;

			if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
				b_Conti = FALSE;

			Sleep(1);
			continue;
		}
		
		PCBExecute = FALSE;
		if(WaitForSingleObject(m_CloseThreadEvent, 0) == WAIT_OBJECT_0)
			b_Conti = FALSE;

		Sleep(1);
	}
}
*/