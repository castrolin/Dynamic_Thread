#ifndef __LOGFILE_
#define __LOGFILE_

class CLogFile
{
public:
	bool OpenFile(CString csFile);
	void CloseFile();
	long GetFileSize();
	bool CreateDirectory(CString csPath);
	bool DirectoryExist(CString csPath);
	bool FileExist(CString csFilename);
	void Write(CString csMsg);
	bool IsOpen() { return _m_bOpen; }

private:
	FILE *_m_pLogFile;
	bool _m_bOpen;
	CString	_m_Filename;
	CRITICAL_SECTION _m_CS;

public:
	CLogFile();
	~CLogFile();
};

#endif //__LOGFILE_
