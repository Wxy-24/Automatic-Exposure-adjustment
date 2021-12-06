#include "test_case.h"
#include <chrono>
#include<time.h>
#include "face_utils.h"
#include <algorithm>

#define DEBUG_TIME 1
#define DEBUG 0

extern float fFunCoefGrayExp[28][3];
int iExpTable[2701][256];// = { 0 };
int iCountTable[2701][256] = {0};

int testGenTable()
{


    int iDistance[4] = {40, 60, 80, 100};
    int iGrayExpDelta[3][53][3] = {0};
    
    int iNumLines = sizeof(fFunCoefGrayExp) / sizeof(fFunCoefGrayExp[0]);
    printf("lines: %d\n", iNumLines);
    for(int i=0; i<iNumLines; i++)

    {
        CameraType cameraType = Seeker07B;
        int iGrayTarget = 100;
        int iExpTarget = getFunResultGrayExp(i, iGrayTarget, cameraType);
        printf("target exp i=%d, exp=%d\n", i, iExpTarget);

        for(int iGray=0; iGray<256; iGray++)
        {
            int iExp = getFunResultGrayExp(i, iGray, cameraType);
            if(iExpTable[iExp][iGray]!=0)
            {
                iExpTable[iExp][iGray] = std::min(iExpTarget, iExpTable[iExp][iGray]);
            }
            else
            {
                iExpTable[iExp][iGray] = iExpTarget;
            }
            //printf(" line:%d (gray:%d  exp:%d) \n", i, iGray, iExp);
        }
        printf("\n------------------------------\n");
    }



    // interpolatation
	printf("3\n");
    tableInterplote(iExpTable);
	printf("4\n");

#define SPECKLE_TABLE 0
#if SPECKLE_TABLE
    {
        FILE* fp1 = fopen("table1_speckle.csv", "w");
        if(NULL != fp1)
        {
            for(int i=0; i<2701; i+=10)
            {
                for(int j=0; j<256; j++)
                {
                    fprintf(fp1, "%d,", iExpTable[i][j]);
                }
                fprintf(fp1, "\n");
            }

            for (int j = 0; j < 256; j++)
            {
                fprintf(fp1, "%d,", j);
            }
                fprintf(fp1, "\n");
            fclose(fp1);
        }
    }
#else
    {
        FILE *fp1 = fopen("table1.csv", "w");
        if(NULL != fp1)
        {
            for(int i=0; i<2701; i+=10)
            {
                for(int j=0; j<256; j++)
                {
                    fprintf(fp1, "%d,", iExpTable[i][j]);
                }
                fprintf(fp1, "\n");
            }

            for (int j = 0; j < 256; j++)
            {
                fprintf(fp1, "%d,", j);
            }
                fprintf(fp1, "\n");
            fclose(fp1);
        }
    }
#endif
#if SPECKLE_TABLE
    {
        FILE* fp1 = fopen("zngx_face_ae_speckle_table.h", "w");
        if(NULL != fp1)
        {
            fprintf(fp1, "#ifndef __FACE_AE_SPECKLE_TABLE_H__\n");
            fprintf(fp1, "#define __FACE_AE_SPECKLE_TABLE_H__\n");
            fprintf(fp1, "int16_t iExpSpeckleTable[271][256] = {\n");
            for(int i=0; i<2700; i+=10)
            {
                for(int j=0; j<256; j++)
                {
                    fprintf(fp1, "%d,", iExpTable[i][j]);
                }
                fprintf(fp1, "\n");
            }
            for (int j = 0; j < 255; j++)
            {
                fprintf(fp1, "%d,", iExpTable[2700][j]);
            }
            fprintf(fp1, "%d\n", iExpTable[2700][255]);
            fprintf(fp1, "};\n#endif \/\/__FACE_AE_SPECKLE_TABLE_H__\n");
            fclose(fp1);
        }
    }
#else
    {
        FILE* fp1 = fopen("face_ae_table.h", "w");
        if(NULL != fp1)
        {
            fprintf(fp1, "#ifndef __FACE_AE_TABLE_H__\n");
            fprintf(fp1, "#define __FACE_AE_TABLE_H__\n");
            fprintf(fp1, "int16_t iExpTable[271][256] = {\n");
            for(int i=0; i<2700; i+=10)
            {
                for(int j=0; j<256; j++)
                {
                    fprintf(fp1, "%d,", iExpTable[i][j]);
                }
                fprintf(fp1, "\n");
            }
            for (int j = 0; j < 255; j++)
            {
                fprintf(fp1, "%d,", iExpTable[2700][j]);
            }
            fprintf(fp1, "%d\n", iExpTable[2700][255]);
            fprintf(fp1, "};\n#endif \/\/__FACE_AE_TABLE_H__\n");
            fclose(fp1);
        }
    }
#endif
	return 0;
}
