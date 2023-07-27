
#include "stdafx.h"
#include "GetRecipe.h"
#include <sys/stat.h>

CGetRecipe::CGetRecipe(const CString &RecipePATH)
{
	CDiskObject DiskObject;

	m_RecipeFolderPath = RecipePATH + "Recipe\\";

	if(DiskObject.DirectoryExists(m_RecipeFolderPath) == FALSE)
		DiskObject.CreateDirectoryA(m_RecipeFolderPath);
}

CGetRecipe::~CGetRecipe(void)
{

}

bool CGetRecipe::FileExist(CString filename)
{
	if(::GetFileAttributes(filename) == 0xFFFFFFFF) // 若找不到
	{	
		return false;
	}
	else
		return true;
}

bool CGetRecipe::LoadRecipe(LPCTSTR FileName)
{

	CString Machine_ParamFileName;
	Machine_ParamFileName.Format("%sCtrlPrms\\MachineSetting.ini", Project_Path);

	char str[64] ;

	CString filename ;

	std::vector<CString> RecipeList;

	GetSystemRecipeFileList(RecipeList);

	CGetRecipe::RECIPE_INDEX_INFO info ;


	for(UINT x = 0; x < RecipeList.size(); x ++)
	{
		CGetRecipe::GetRecipeIndexInfo(RecipeList.at(x), info);

		if(info.csFileName == FileName)
		{
			filename.Format(m_RecipeFolderPath + RecipeList.at(x));
			CString MainKey, SubKey;

			GetPrivateProfileString("Recipe","Recipe Name", "" , str , 64 , filename) ;
			Recipe_Data.st_RecipeInfo.csRecipeName.Format("%s" , str);

			Recipe_Data.st_RecipeInfo.csFileName = info.csFileName;

			GetPrivateProfileString("Recipe","Recipe Comment", "" , str , 64 , filename) ;
			Recipe_Data.st_RecipeInfo.csComment.Format("%s" , str);

			GetPrivateProfileString("Recipe","Access Time", "" , str , 64 , filename) ;
			Recipe_Data.st_RecipeInfo.csAccessTime.Format("%s" , str);

			GetPrivateProfileString("Recipe","Recipe ID", "" , str , 64 , filename) ;
			Recipe_Data.st_RecipeInfo.nRcipeID = atoi(str);

			//RecipeData
			Recipe_Data.st_RecipeData.nThreshold = GetPrivateProfileInt("RecipeData","nThreshold", 0, filename) ;
			Recipe_Data.st_RecipeData.nBlur = GetPrivateProfileInt("RecipeData","nBlur", 0, filename) ;

			Recipe_Data.st_RecipeData.nOrgPosPixel_LX = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_LX", 0, filename) ;
			Recipe_Data.st_RecipeData.nOrgPosPixel_LY = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_LY", 0, filename) ;

			Recipe_Data.st_RecipeData.nOrgPosPixel_RX = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_RX", 0, filename) ;
			Recipe_Data.st_RecipeData.nOrgPosPixel_RY = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_RY", 0, filename) ;


			Recipe_Data.st_RecipeData.nThreshold_Sticker = GetPrivateProfileInt("RecipeData","nThreshold_Sticker", 0, filename) ;
			Recipe_Data.st_RecipeData.nBlur_Sticker = GetPrivateProfileInt("RecipeData","nBlur_Sticker", 0, filename) ;

			Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_Sticker_LX", 0, filename) ;
			Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_Sticker_LY", 0, filename) ;

			Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_Sticker_RX", 0, filename) ;
			Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY = GetPrivateProfileDouble("RecipeData","nOrgPosPixel_Sticker_RY", 0, filename) ;


			Recipe_Data.st_RecipeData.Offset_mm_X = GetPrivateProfileDouble("SystemParam", "Offset_mm_X", 0.0, filename);
			Recipe_Data.st_RecipeData.Offset_mm_Y = GetPrivateProfileDouble("SystemParam", "Offset_mm_Y", 0.0, filename);
			Recipe_Data.st_RecipeData.Offset_mm_T = GetPrivateProfileDouble("SystemParam", "Offset_mm_T", 0.0, filename);
			return true;
		}


	}

	return false;
}

bool CGetRecipe::SaveRecipe()
{

	CString Machine_ParamFileName;
	Machine_ParamFileName.Format("%sCtrlPrms\\MachineSetting.ini", Project_Path);

	CString filename, csCheck, szData ;

	csCheck = FormatString("Work%03d", Recipe_Data.st_RecipeInfo.nRcipeID);
	csCheck.Trim();

	if(csCheck.IsEmpty())
		return false;


	//重新拼湊檔名,考慮傳入名字沒有附檔名.rcp
	if( -1 == csCheck.Find(".rcp"))
	{
		csCheck += ".rcp" ;
	}
	filename.Format("%s%s", m_RecipeFolderPath, csCheck);

	CString MainKey, SubKey;

	szData = Recipe_Data.st_RecipeInfo.csRecipeName; 
	if (!WritePrivateProfileString("Recipe","Recipe Name" , szData , filename ))
	{
		return false;
	}

	szData = Recipe_Data.st_RecipeInfo.csComment;
	if (!WritePrivateProfileString("Recipe","Recipe Comment" , szData , filename ))
	{
		return false;
	}

	szData = Recipe_Data.st_RecipeInfo.csAccessTime;
	if (!WritePrivateProfileString("Recipe","Access Time" , szData , filename ))
	{
		return false;
	}

	szData = FormatString("%d", (int)Recipe_Data.st_RecipeInfo.nRcipeID);
	if (!WritePrivateProfileString("Recipe","Recipe ID" , szData , filename ))
	{
		return false;
	}

	WritePrivateProfileString("RecipeData","nThreshold" , FormatString("%d", Recipe_Data.st_RecipeData.nThreshold) , filename );
	WritePrivateProfileString("RecipeData","nBlur" , FormatString("%d", Recipe_Data.st_RecipeData.nBlur) , filename );

	WritePrivateProfileString("RecipeData","nOrgPosPixel_LX" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_LX) , filename );
	WritePrivateProfileString("RecipeData","nOrgPosPixel_LY" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_LY) , filename );

	WritePrivateProfileString("RecipeData","nOrgPosPixel_RX" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_RX) , filename );
	WritePrivateProfileString("RecipeData","nOrgPosPixel_RY" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_RY) , filename );


	WritePrivateProfileString("RecipeData","nThreshold_Sticker" , FormatString("%d", Recipe_Data.st_RecipeData.nThreshold_Sticker) , filename );
	WritePrivateProfileString("RecipeData","nBlur_Sticker" , FormatString("%d", Recipe_Data.st_RecipeData.nBlur_Sticker) , filename );

	WritePrivateProfileString("RecipeData","nOrgPosPixel_Sticker_LX" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX) , filename );
	WritePrivateProfileString("RecipeData","nOrgPosPixel_Sticker_LY" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY) , filename );

	WritePrivateProfileString("RecipeData","nOrgPosPixel_Sticker_RX" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX) , filename );
	WritePrivateProfileString("RecipeData","nOrgPosPixel_Sticker_RY" , FormatString("%f", Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY) , filename );


	::WritePrivateProfileString("SystemParam", "Offset_mm_X", FormatString("%.3lf", Recipe_Data.st_RecipeData.Offset_mm_X), filename);
	::WritePrivateProfileString("SystemParam", "Offset_mm_Y", FormatString("%.3lf", Recipe_Data.st_RecipeData.Offset_mm_Y), filename);
	::WritePrivateProfileString("SystemParam", "Offset_mm_T", FormatString("%.3lf", Recipe_Data.st_RecipeData.Offset_mm_T), filename);

	return true;
}

int CGetRecipe::GetTotalRecipeName( CStringList &cList_TotalRecipe )
{
	CFileFind finder;
	int num=0;

	cList_TotalRecipe.RemoveAll();

	CString csFind = m_RecipeFolderPath ;
	csFind += _T("\\*.rcp");

	BOOL bWorking = finder.FindFile(csFind);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (!finder.IsDirectory() && !finder.IsDots())
		{
			cList_TotalRecipe.AddTail(finder.GetFileName());
			num++;
		}
	}

	finder.Close();

	return num;

}

CString CGetRecipe::GetRecipeName()
{
	return Recipe_Data.st_RecipeInfo.csRecipeName;
}

CString CGetRecipe::GetRecipeFileName()
{
	return Recipe_Data.st_RecipeInfo.csFileName;
}

bool CGetRecipe::GetRecipeIndexInfo( const LPCTSTR recipename, CGetRecipe::RECIPE_INDEX_INFO &recipe_index_info)
{
	char str[64] ;
	CString msg , filename , csCheck , szData ;
	memset(str , 0x0 , 64);

	csCheck.Format("%s" , recipename );
	csCheck.Trim();

	if(csCheck.IsEmpty())
	{
		return false;
	}

	//重新拼湊檔名,考慮傳入名字沒有附檔名.rcp
	if( -1 == csCheck.Find(".rcp"))
	{
		csCheck += ".rcp" ;
	}

	filename = m_RecipeFolderPath +"\\"+ csCheck ;

	if( !FileExist(filename) )
	{	
		return false;
	}

	GetPrivateProfileString("Recipe","Recipe Name", "" , str , 64 , filename) ;
	recipe_index_info.csRecipeName.Format("%s" , str);

	recipe_index_info.csFileName = csCheck;

	GetPrivateProfileString("Recipe","Recipe Comment", "" , str , 64 , filename) ;
	recipe_index_info.csComment.Format("%s" , str);

	GetPrivateProfileString("Recipe","Access Time", "" , str , 64 , filename) ;
	recipe_index_info.csAccessTime.Format("%s" , str);

	GetPrivateProfileString("Recipe","Recipe ID", "" , str , 64 , filename) ;
	recipe_index_info.nRcipeID =atoi(str);

	return (true);
}

bool CGetRecipe::ReloadRecipe()
{
	RECIPE_DATA NewData;
	Recipe_Data.st_RecipeData = NewData;

	if(LoadRecipe(Recipe_Data.st_RecipeInfo.csFileName) == false)
		return false;

	return true;
}
