#pragma once
#include ".\ADODEF.h"
#include <vector>

class AFX_EXT_CLASS CADODatabase
{
private:
	_ConnectionPtr m_pConnection;

	bool LoadOneColumn(CString cstrSQL, std::vector< CString > &mADOInfos, int iIndex=0);
	bool LoadOneRow(CString cstrSQL, std::vector< CString > &mADOInfos) ;

	long GetFieldsCount(_RecordsetPtr m_pRS);
	Fields* GetFields(_RecordsetPtr m_pRS);

public:
	CADODatabase(void);
	virtual ~CADODatabase(void);

	bool OpenDB(CString csDBName);						//�}�Ҩt�Τ����Ʈw
	void CloseDB();											//�����t�Τ����Ʈw
	BOOL IsOpen();

	bool GetDataArray_Column(CString csTabName, CString csColumnName, std::vector< CString > &mInfos, CString csDBName);
	bool GetDataArray_Row(CString csTabName, CString csColumnName, CString csRowName, std::vector< CString > &mInfos,IN CString csDBName);

};