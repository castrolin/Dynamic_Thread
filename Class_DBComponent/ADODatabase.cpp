#include "StdAfx.h"
#include ".\adodatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CADODatabase::CADODatabase(void)
{
	// ADO initial
	CoInitialize(NULL);
	m_pConnection = NULL;
	m_pConnection.CreateInstance(__uuidof(Connection));
}

CADODatabase::~CADODatabase(void)
{
	CloseDB();
	m_pConnection.Release();
	m_pConnection = NULL;
	::CoUninitialize();
}

bool CADODatabase::OpenDB(CString csDBName)
{
	CString m_cstrConnection;
	m_cstrConnection.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='%s'",csDBName);

	if(IsOpen())
		CloseDB();

	VERIFY(!m_cstrConnection.IsEmpty());

	HRESULT hr = S_OK;

	try
	{
		hr = m_pConnection->Open(_bstr_t(m_cstrConnection), _bstr_t(""), _bstr_t(""), adModeUnknown);
		return hr == S_OK;
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}
}

void CADODatabase::CloseDB()
{
	if(IsOpen())
		m_pConnection->Close();
}

BOOL CADODatabase::IsOpen()
{
	if(m_pConnection )
	{
		return m_pConnection->GetState() != adStateClosed;
	}
	else
	{
		return FALSE;
	}
}

bool CADODatabase::GetDataArray_Column(CString csTabName, CString csColumnName, std::vector< CString > &mInfos, CString csDBName)
{
	CString cstrSQL;

	if(!OpenDB(csDBName))								// Ū���}�l
	{
		return false;
	}

	cstrSQL.Format("SELECT %s FROM %s", csColumnName, csTabName);

	LoadOneColumn(cstrSQL, mInfos, 0);

	CloseDB();											// ����Ū��
	return true ;
}


bool CADODatabase::LoadOneColumn(CString cstrSQL, std::vector< CString > &mADOInfos, int iIndex)
{
	_variant_t var;

	_RecordsetPtr	m_pRecordset;

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// �bADO�ާ@����ĳ�y�y���n�`��try...catch()�Ӯ�����~�H���A�]�������ɷ|�g�`�X�{�@�ǷN�Q���쪺���~
	try
	{
		m_pRecordset->Open(cstrSQL.GetBuffer(0),// �d��DemoTable���Ҧ��r�q
			m_pConnection.GetInterfacePtr(),		// ����w���w��IDispatch���w
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	while(!m_pRecordset->EndOfFile)
	{
		var = m_pRecordset->GetCollect(_variant_t((long)iIndex));
		if(var.vt != VT_NULL)
			mADOInfos.push_back((LPCSTR)_bstr_t(var));

		m_pRecordset->MoveNext();
	}

	m_pRecordset->Close();
	return true;
}

bool CADODatabase::GetDataArray_Row(CString csTabName, CString csColumnName, CString csRowName, std::vector< CString > &mInfos,IN CString csDBName)
{
	//!����d�߻y�y
	CString cstrSQL, cstrCondition ;

	if(!OpenDB(csDBName))								// Ū���}�l
		return false;

	cstrCondition.Format("WHERE %s = '%s'" , csColumnName, csRowName ) ;
	cstrSQL = "SELECT * FROM " + csTabName + " " + cstrCondition;

	LoadOneRow(cstrSQL, mInfos);

	CloseDB();											// ����Ū��

	return true ;
}

bool CADODatabase::LoadOneRow(CString cstrSQL, std::vector< CString > &mADOInfos)
{
	int iIndex = 0 ;
	_variant_t var;
	_RecordsetPtr	m_pRecordset;

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// �bADO�ާ@����ĳ�y�y���n�`��try...catch()�Ӯ�����~�H���A�]�������ɷ|�g�`�X�{�@�ǷN�Q���쪺���~
	try
	{
		m_pRecordset->Open(cstrSQL.GetBuffer(0),// �d��DemoTable���Ҧ��r�q
			m_pConnection.GetInterfacePtr(),		// ����w���w��IDispatch���w
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false ;
	}

	while(!m_pRecordset->EndOfFile)
	{
		long lFieldsCount = GetFieldsCount(m_pRecordset);
		while( iIndex < lFieldsCount  )
		{
			var = m_pRecordset->GetCollect(_variant_t((long)iIndex));
			if(var.vt != VT_NULL)
				mADOInfos.push_back((LPCSTR)_bstr_t(var));
			else
				return false ;

			iIndex ++ ;
		}

		m_pRecordset->MoveNext();
	}

	m_pRecordset->Close();
	return true;
}

long CADODatabase::GetFieldsCount(_RecordsetPtr m_pRS)
{
	Fields* m_field ;

	ASSERT(m_pRS != NULL);
	try
	{
		m_field = GetFields(m_pRS) ;
		if( m_field != NULL )
			return m_field->Count;
		else
			return -1;
	}
	catch(_com_error e)
	{
		return -1;
	} 
}

Fields* CADODatabase::GetFields(_RecordsetPtr m_pRS)
{
	ASSERT(m_pRS != NULL);
	FieldsPtr pFields = NULL ;
	try
	{
		if (SUCCEEDED(m_pRS->get_Fields(&pFields)))
		{
			return pFields;
		}
	}
	catch (_com_error e)
	{
		return NULL;
	} 
	return NULL;
}