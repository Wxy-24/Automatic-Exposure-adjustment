#include "face_utils.h"
#include "face_formula.h"
#include <stdio.h>
#include <algorithm>



int tableIntpMax1(int iExpTable[2701][256])
{
	int pre_i = 0;
	for (int iGray = 1; iGray < 30; iGray++)
	{
		int maxcount = 0;
		for (int i = 1; i < 600; i++)
		{
			int iExpFromTable = iExpTable[i][iGray];
			if (iExpFromTable == 2700)
			{
				maxcount += 1;
				pre_i = i;
				continue;
			}
		}
		if (maxcount == 0) 
		{   
			printf("col No. %d no max, pre_i = %d",iGray,pre_i);
			iExpTable[pre_i + 4][iGray] = 2700;
		}
	}
	return 0;
}


int tableIntpMax2(int iExpTable[2701][256])
{
	for (int iGray = 0; iGray < 90; iGray++)
	{
		for (int i = 1; i < 2700; i++)
		{
			int iExpFromTable = iExpTable[i][iGray];
			if (iExpFromTable == 2700)
			{
				for (int k = i + 1; k < 2701; k++){iExpTable[k][iGray] = 2700;}
			}
		}

	}
	return 0;
}



int tableCalLastRow2(int iExpTable[2701][256])
{
	int iExpStart = 0;
	int iExpEnd = 0;
	int iIdxStart = 0;
	int iIdxEnd = 0;
	int iIdxFirstNoneZero = 0;
	int iExpFisrtNoneZero = 0;
	bool bFindFisrtNoneZero = false;
	bool bFindPairNoneZero = false;

	for (int iGray = 1; iGray < 255; iGray++)
	{
		int iExpFromTable = iExpTable[2700][iGray];
		int iExpFirst = iExpTable[2700][0];

		// find the first non-zero value and its position
		if (iExpFromTable != 0 && !bFindFisrtNoneZero)
		{
			iExpEnd = iExpTable[2700][iGray];
			iIdxEnd = iGray;
			iExpFisrtNoneZero = iExpFromTable;
			iIdxFirstNoneZero = iGray;
			bFindFisrtNoneZero = true;

			for (int i = 0; i<iIdxEnd; i++)
			{
				iExpTable[2700][i] = 2700;
			}
			printf("3:   %d %d\n", iIdxEnd, iExpEnd);
		}

		// find the second changing point
		if (iExpFromTable != iExpTable[2700][iIdxEnd] && bFindFisrtNoneZero)
		{
			iExpStart = iExpEnd;
			iExpEnd = iExpTable[2700][iGray];
			iIdxStart = iIdxEnd;
			iIdxEnd = iGray;
			bFindPairNoneZero = true;
		}

		// interpolatation
		if (bFindFisrtNoneZero && bFindPairNoneZero)
		{
			printf("2:  iExpStart:%d  iExpEnd:%d  iIdxStar:%d  iIdxEnd:%d\n", iExpStart, iExpEnd, iIdxStart, iIdxEnd);
			//printf("iExpFromTable: %d exp:%d\n", i, iExpFromTable);
			int iGap = iExpEnd - iExpStart;
			int iNum = iIdxEnd - iIdxStart;
			float fIntervals = 1.0 * iGap / (iNum + 1);
			for (int j = 1; j < iNum; j++)
			{
				int iExpTmp = iExpStart + j * fIntervals;
				iExpTmp = iExpTmp / 10 * 10;
				iExpTmp = std::min(iExpTmp, 2700);
				iExpTmp = std::max(0, iExpTmp);
				iExpTable[2700][iIdxStart + j] = iExpTmp;
				//printf("%d %d %d\n", iIdxStart + j, iGray, iExpTmp);
			}
			bFindPairNoneZero = false;
		}
	}


	iExpStart = iExpTable[2700][iIdxEnd];
	iExpEnd = iExpTable[2700][255];
	iIdxStart = iIdxEnd;
	iIdxEnd = 255;
	int iGap = iExpEnd - iExpStart;
	int iNum = iIdxEnd - iIdxStart;
	float fIntervals = 1.0 * iGap / (iNum + 1);
	for (int j = 1; j < iNum; j++)
	{
		int iExpTmp = iExpStart + j * fIntervals;
		iExpTmp = iExpTmp / 10 * 10;
		iExpTmp = std::min(iExpTmp, 2700);
		iExpTmp = std::max(0, iExpTmp);
		//iExpTable[2700][iIdxStart + j] = iExpTmp;
		//printf("%d %d %d\n", iIdxStart + j, iGray, iExpTmp);
	}

	return 0;
}

int tableCalEachCol(int iExpTable[2701][256])
{
	for (int iGray = 0; iGray < 256; iGray++)
	{
		int iExpStart = 0;   
		int iExpEnd = 0;
		int iIdxStart = 0;
		int iIdxEnd = 0;
		int iIdxFirst = 0;   
		int iExpFisrt = 0;   
		bool bFindFisrtNoneZero = false;
		bool bFindPairNoneZero = false;
		for (int i = 0; i<2701; i++)
		{
			int iExpFromTable = iExpTable[i][iGray];

			if (iExpFromTable != 0 && !bFindFisrtNoneZero)
			{
				printf("3\n");
				iExpEnd = iExpFromTable;
				iIdxEnd = i;
				iExpFisrt = iExpFromTable;
				iIdxFirst = i;
				bFindFisrtNoneZero = true;
			}

			if (iExpFromTable != 0 && bFindFisrtNoneZero)
			{
				iExpStart = iExpEnd;
				iExpEnd = iExpFromTable;
				iIdxStart = iIdxEnd;
				iIdxEnd = i;
				bFindPairNoneZero = true;
			}

			if (bFindFisrtNoneZero && bFindPairNoneZero)
			{
				//printf("2:  iExpStart:%d  iExpEnd:%d  iIdxStar:%d  iIdxEnd:%d\n", iExpStart, iExpEnd, iIdxStart, iIdxEnd);
				//printf("iExpFromTable: %d exp:%d\n", i, iExpFromTable);
				int iGap = iExpEnd - iExpStart;
				int iNum = iIdxEnd - iIdxStart;
				float fIntervals = 1.0 * iGap / (iNum + 1);
				for (int j = 1; j<iNum; j++)
				{
					int iExpTmp = iExpStart + j*fIntervals;
					iExpTmp = iExpTmp / 10 * 10;
					iExpTmp = std::min(iExpTmp, 2700);
					iExpTmp = std::max(0, iExpTmp);
					iExpTable[iIdxStart + j][iGray] = iExpTmp;
					//printf("%d %d %d\n", iIdxStart + j, iGray, iExpTmp);
				}
				bFindPairNoneZero = false;
			}

		}

		// for the last row
		if (iIdxFirst != 0)
		{
			iExpStart = 0;
			iExpEnd = iExpFisrt;
			iIdxStart = 0;
			iIdxEnd = iIdxFirst;
			printf("begin part :  iExpStart:%d  iExpEnd:%d  iIdxStar:%d  iIdxEnd:%d\n", iExpStart, iExpEnd, iIdxStart, iIdxEnd);

			int iGap = iExpEnd - iExpStart;
			int iNum = iIdxEnd - iIdxStart;
			float fIntervals = 1.0 * iGap / (iNum + 1);
			for (int j = 1; j < iNum; j++)
			{
				int iExpTmp = iExpStart + j * fIntervals;
				iExpTmp = iExpTmp / 10 * 10;
				iExpTmp = std::min(iExpTmp, 2700);
				iExpTmp = std::max(0, iExpTmp);
				iExpTable[iIdxStart + j][iGray] = iExpTmp;
				// printf("%d %d %d\n", iIdxStart + j, iGray, iExpTmp);
			}
		}


		if (iIdxFirst != 0)
		{
			iExpStart = 0;
			iExpEnd = iExpFisrt;
			iIdxStart = 0;
			iIdxEnd = iIdxFirst;
			printf("begin part :  iExpStart:%d  iExpEnd:%d  iIdxStar:%d  iIdxEnd:%d\n", iExpStart, iExpEnd, iIdxStart, iIdxEnd);

			int iGap = iExpEnd - iExpStart;
			int iNum = iIdxEnd - iIdxStart;
			float fIntervals = 1.0 * iGap / (iNum + 1);
			for (int j = 1; j < iNum; j++)
			{
				int iExpTmp = iExpStart + j * fIntervals;
				iExpTmp = iExpTmp / 10 * 10;
				iExpTmp = std::min(iExpTmp, 2700);
				iExpTmp = std::max(0, iExpTmp);
				iExpTable[iIdxStart + j][iGray] = iExpTmp;
				// printf("%d %d %d\n", iIdxStart + j, iGray, iExpTmp);
			}
		}
	}
	return 0;
}

int getFunResultGrayExp(int iIdxLine, int iGray, CameraType cameraType)  
{
    if(Seeker == cameraType)
    {
        int iExp = fFunCoefGrayExp[iIdxLine][0]*iGray*iGray + fFunCoefGrayExp[iIdxLine][1] *iGray + fFunCoefGrayExp[iIdxLine][2];
        iExp = iExp / 10 * 10;
        iExp = iExp > 2700 ? 2700 : iExp;
        iExp = iExp < 0 ? 0 : iExp;
        return iExp;
    }
    else if(Sunmi == cameraType)
    {
        int iExp = fFunCoefGrayExpSunmi[iIdxLine][0]*iGray*iGray + fFunCoefGrayExpSunmi[iIdxLine][1]*iGray +fFunCoefGrayExpSunmi[iIdxLine][2];
        iExp = iExp / 10 * 10;
        iExp = iExp > 2700 ? 2700 : iExp;
        iExp = iExp < 0 ? 0 : iExp;
        return iExp;
    }
}

int getFunResultExpGray(int iIdxLine, int iExp, CameraType cameraType)
{
    if(Seeker07B == cameraType)
    {
        int iGray = fFunCoefExpGray[iIdxLine][0]*iExp*iExp + fFunCoefExpGray[iIdxLine][1] *iExp + fFunCoefExpGray[iIdxLine][2];
        return iGray;
    } 
    else if(Sunmi == cameraType)
    {
        int iGray = fFunCoefExpGraySunmi[iIdxLine][0]*iExp + fFunCoefExpGraySunmi[iIdxLine][1];
        return iGray;
    }
}


// interpolatation
int tableInterplote(int iExpTable[2701][256])
{
	tableIntpMax1(iExpTable);
    tableCalLastRow2(iExpTable);
    tableCalEachCol(iExpTable);
	tableIntpMax2(iExpTable);
    return 0;
}

int readExpTable(char* filePath, int iExpTable[2701][256])
{
    FILE* fp = fopen(filePath, "r");
    if(NULL != fp)
    {
        for(int i=0; i<271; i++)
        {
            int iExp = 0;
            for(int j=0; j<255; j++)
            {
                fscanf(fp, "%d,", &iExp);
                iExpTable[i][j] = iExp;
            }
            fscanf(fp, "%d,\n", &iExp);
            iExpTable[i][255] = iExp;
        }
        fclose(fp);
    }
    else
    {
        printf("%s is not exist\n", filePath);
        return -1;
    }
    return 0;
}