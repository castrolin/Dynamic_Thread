#pragma once
#include <vector>
#include "DiskObject.h"
#include "ProductDataDef.h"

class CGetRecipe
{
public:



	struct RECIPE_INDEX_INFO
	{
		//[Recipe]

		UINT nRcipeID;
		CString csRecipeName ;
		CString csFileName ;
		CString csComment;		
		CString csAccessTime;

		RECIPE_INDEX_INFO()
		{
			nRcipeID = 0;
			csRecipeName.Empty();
			csFileName.Empty();
			csComment.Empty() ;		
			csAccessTime.Empty();	
		}

	};

	struct RECIPE_DATA
	{

		int nThreshold;
		int nBlur;
		double nOrgPosPixel_LX;
		double nOrgPosPixel_LY;

		double nOrgPosPixel_RX;
		double nOrgPosPixel_RY;


		int nThreshold_Sticker;
		int nBlur_Sticker;
		double nOrgPosPixel_Sticker_LX;
		double nOrgPosPixel_Sticker_LY;

		double nOrgPosPixel_Sticker_RX;
		double nOrgPosPixel_Sticker_RY;


		double Offset_mm_X;
		double Offset_mm_Y;
		double Offset_mm_T;


		RECIPE_DATA()
		{
			nThreshold = 0;
			nBlur = 0;
			nOrgPosPixel_LX = 0;
			nOrgPosPixel_LY = 0;

			nOrgPosPixel_RX = 0;
			nOrgPosPixel_RY = 0;


			nThreshold_Sticker = 0;
			nBlur_Sticker = 0;
			nOrgPosPixel_Sticker_LX = 0;
			nOrgPosPixel_Sticker_LY = 0;

			nOrgPosPixel_Sticker_RX = 0;
			nOrgPosPixel_Sticker_RY = 0;
		}
	};

	struct RECIPE_STRUCT
	{
		RECIPE_INDEX_INFO	st_RecipeInfo;
		RECIPE_DATA st_RecipeData;

	};

protected:
	CString m_RecipeFolderPath ;

public:
	RECIPE_STRUCT Recipe_Data;
	bool FileExist(CString filename);
	bool ReloadRecipe();
	bool LoadRecipe(LPCTSTR FileName);
	bool SaveRecipe();
	int  GetTotalRecipeName( CStringList &cList_TotalRecipe );
	CString GetRecipeName();
	CString GetRecipeFileName();
	bool GetRecipeIndexInfo( const LPCTSTR recipename , CGetRecipe::RECIPE_INDEX_INFO &recipe_index_info);

public:
	CGetRecipe(const CString &RecipePATH);
	~CGetRecipe(void);
};

