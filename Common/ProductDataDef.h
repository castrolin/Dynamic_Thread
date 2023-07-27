#pragma once

//CST_NUM

#define _CST_NUM_INCH_4	25
#define _CST_NUM_INCH_6	12
#define _CST_NUM_PDMS	6

#define _PRODUCT_PROCESSING_COLOR		RGB(255, 200, 15)
#define _PRODUCT_PROCESS_SUCCESS_COLOR	RGB(0, 255, 0)
#define _PRODUCT_PROCESS_FAIL_COLOR		RGB(255, 0, 0)
#define _PRODUCT_PROCESS_EXIST_COLOR	RGB(0, 0, 255)
#define _PRODUCT_PROCESS_EMPTY_COLOR		RGB(255, 255, 255)
#define _PRODUCT_PROCESS_IDLE_COLOR			RGB(150, 150, 150)
#define _PRODUCT_PROCESS_UNKNOWN_COLOR		RGB(255, 0, 0)

enum PRODUCT_PRODUCT_STATUS
{
	EXP_PRODUCT_STATUS_UNKNOWN,
	EXP_PRODUCT_STATUS_IDLE,
	EXP_PRODUCT_STATUS_PROCESSING,
	EXP_PRODUCT_STATUS_DONE

};

enum PRODUCT_EXIST_STATUS
{
	EXP_PRODUCT_EMPTY,
	EXP_PRODUCT_EXIST,
	
};

class AFX_EXT_CLASS CProduct_Data
{
public:

	CProduct_Data(CString ProductName);
	~CProduct_Data();

private:
	CString m_ProductName;
	CString m_FileName;
	CString m_Project_Path;

	PRODUCT_PRODUCT_STATUS m_Status;
	PRODUCT_EXIST_STATUS m_Exist;
	

public:

	BOOL DataRestore();
	void DataClear();

	void SetProductExist(PRODUCT_EXIST_STATUS Exist);
	void SetProductProcStatus(PRODUCT_PRODUCT_STATUS Status);

	PRODUCT_EXIST_STATUS GetProductExist();
	PRODUCT_PRODUCT_STATUS GetProductProcStatus();

};