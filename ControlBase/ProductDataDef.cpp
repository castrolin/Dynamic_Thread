#include "stdafx.h"
#include "ProductDataDef.h"



CProduct_Data::CProduct_Data(CString ProductName)
{

	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	m_Project_Path.Format("%s%s", tcDriver, tcDir);

	m_ProductName = ProductName;
	m_FileName = m_Project_Path + "\\CtrlPrms\\ProductData\\" + m_ProductName + ".ini";

	

	m_Exist = EXP_PRODUCT_EMPTY;
	m_Status = EXP_PRODUCT_STATUS_UNKNOWN;
}

CProduct_Data::~CProduct_Data()
{

}

BOOL CProduct_Data::DataRestore()
{
	m_Exist = PRODUCT_EXIST_STATUS(GetPrivateProfileInt(m_ProductName, "Exist", EXP_PRODUCT_EMPTY, m_FileName));
	m_Status = PRODUCT_PRODUCT_STATUS(GetPrivateProfileInt(m_ProductName, "Status", EXP_PRODUCT_STATUS_UNKNOWN, m_FileName));

	return TRUE;
}

void CProduct_Data::DataClear()
{
	m_Exist = EXP_PRODUCT_EMPTY;
	m_Status = EXP_PRODUCT_STATUS_IDLE;
}

void CProduct_Data::SetProductExist( PRODUCT_EXIST_STATUS Exist )
{
	m_Exist = Exist;
	WritePrivateProfileString(m_ProductName, "Exist", FormatString("%d", m_Exist), m_FileName);
	
}

void CProduct_Data::SetProductProcStatus( PRODUCT_PRODUCT_STATUS Status )
{
	m_Status = Status;
	WritePrivateProfileString(m_ProductName, "Status", FormatString("%d", m_Status), m_FileName);
}

PRODUCT_EXIST_STATUS CProduct_Data::GetProductExist()
{
	return m_Exist;
}

PRODUCT_PRODUCT_STATUS CProduct_Data::GetProductProcStatus()
{
	return m_Status;
}



