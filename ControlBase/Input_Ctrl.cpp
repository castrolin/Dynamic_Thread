
#include "stdafx.h"
#include "Input_Ctrl.h"

CInputControl::CInputControl()
{
	m_ADO = new CADODatabase();
}

CInputControl::~CInputControl()
{
	
}

//bool CInputControl::Initial_Info_Advantech_DAQ_Input(CIO_CentraCtrl_DAQ *IO_Ctrl)
//{
//	try
//	{
//		CString csDBName,  sz;
//		std::vector< CString > m_Infos1, m_Infos2;
//
//		csDBName.Format("%s\\CtrlPrms\\%s", Project_Path, "ContrelSystem.mdb");
//
//		for(UINT x = 0; x < m_Input_Advantech_DAQ_Array.size(); x ++)
//		{
//			delete m_Input_Advantech_DAQ_Array.at(x);
//		}
//
//		m_Input_Advantech_DAQ_Array.clear();
//
//		m_Infos1.clear();
//
//
//		if( m_ADO->GetDataArray_Column("Input_Advantech_DAQ", "BitName", m_Infos1, csDBName ) == false ) //"Input_Advantech_PCIE1730"
//			return false ;
//
//		for(UINT i=0; i<m_Infos1.size(); i++)
//		{	
//			CDigital_Input_Advantech_DAQ *Input = NULL;
//			Input = new CDigital_Input_Advantech_DAQ();
//
//			m_Infos2.clear();
//
//			if( m_ADO->GetDataArray_Row("Input_Advantech_DAQ", "BitName", m_Infos1.at(i), m_Infos2, csDBName ) != false )
//			{
//
//				
//				INPUT_INFO_ADVANTECH_DAQ InputInfoData;
//				InputInfoData.bDummy		= IO_Ctrl->CheckDummy();
//				InputInfoData.sBitName		= m_Infos2.at(0);
//				InputInfoData.sCardName		= m_Infos2.at(1);
//				InputInfoData.nBitIndex		= atoi(m_Infos2.at(2));
//				InputInfoData.nPortID       = atoi(m_Infos2.at(3));
//				InputInfoData.nCardID		= atoi(m_Infos2.at(4));
//
//
//				InputInfoData.m_PanelInfo = IO_Ctrl->CreateInstanceCtrl_Input(InputInfoData.sCardName, FormatString("%d", InputInfoData.nCardID));
//
//				if(InputInfoData.m_PanelInfo == NULL && InputInfoData.bDummy == FALSE)
//				{
//					UINT nRet = _ALARM_PROC_ADVANTECH_DAQ_NOT_FOUND;
//					throw(SYSTEM_ERROR("CreateInstanceCtrl_Input",_MODULE_ERROR_ADVANTECH_DAQ, &nRet));
//					return false;
//				}
//
//				
//				if( Input->InitialCtrlInfo(InputInfoData) == false )
//				{
//					return false ;
//				}
//
//				m_Input_Advantech_DAQ_Array.push_back(Input);
//			}
//
//		}
//	}
//	catch(SYSTEM_ERROR &e)
//	{
//		e.SetLocation("Initial_Info_Advantech_DAQ_Input");
//		throw e;
//		return false;
//	}
//	catch(...)
//	{
//		UINT nRet = _ALARM_PROC_ADVANTECH_DAQ_DATABASE_FAIL;
//		throw(SYSTEM_ERROR("Initial_Info_Advantech_DAQ_Input",_MODULE_ERROR_ADVANTECH_DAQ, &nRet));
//		return false;
//	}
//	
//	
//	return true;
//}

bool CInputControl::Initial_All_Input()
{

	m_Input_Array.clear();

	//m_Input_Array.insert(m_Input_Array.end(), m_Input_Advantech_DAQ_Array.begin(), m_Input_Advantech_DAQ_Array.end());

	return true;
}

bool CInputControl::GetInput( UINT nIndex ,bool bWait, DWORD nTimeout )
{	
	try
	{
		//if(nIndex == X20_CHAMBER_DOOR_Z_UP)
		//	return true;

		DWORD nEndTime = GetTickCount() + nTimeout;
		if(nIndex >= m_Input_Array.size())
			return false;
	
		if (bWait)
		{
			do 
			{
				Delay(100);
			} 
			while ( GetTickCount() <= nEndTime);//false jump
		}

		return m_Input_Array.at(nIndex)->GetValue();
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetInput");
		throw;
		return false;
	}

	return true;

}