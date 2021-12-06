#ifndef __FACE_UTILS_H__
#define __FACE_UTILS_H__
// 室内工位 40-100cm
// exp = 0.035   *gray*gray + 3.074 *gray + 122.8
// exp = 0.06704 *gray*gray + 8.984 *gray + 33.82
// exp = 0.2206  *gray*gray + 10.88 *gray + 47.24
// exp = 0.2293  *gray*gray + 25.82 *gray - 171.4

// 室外阴天  40-100cm          
// exp = 0.009947*gray*gray + 2.81 *gray + 78.58
// exp = 0.02636 *gray*gray + 0.381*gray + 155.3
// exp = 0.05887 *gray*gray - 3.227*gray + 258.7 
// exp = 0.03582 *gray*gray + 2.974*gray + 107.1
//-------------------------------------------
//室内工位
//exp = 0.035   gray*gray + 3.074 *gray + 122.8
//exp = 0.06704 gray*gray + 8.984 *gray + 33.82
//exp = 0.2206  gray*gray + 10.88 *gray + 47.24
//exp = 0.2293  gray*gray + 25.82 *gray - 171.4
//窗边顺光
//exp = 0.02962 gray*gray + 2.719 *gray + 104.1
//exp = 0.05965 gray*gray + 6.394 *gray + 96.24
//exp = 0.04479 gray*gray + 24.52 *gray - 259.6
//exp = 0.1615  gray*gray + 19.47 *gray - 67.06
//窗边逆光
//exp = 0.03744 * gray *gray + 1.47  *gray + 187.3
//exp = 0.047   * gray *gray + 10.03 *gray + 6.251
//exp = 0.07425 * gray *gray + 17.95 *gray - 125
//exp = 0.138   * gray *gray + 18.96 *gray - 109.7
//室外阴天
//exp = 0.009947 *gray*gray + 2.81  *gray + 78.58
//exp = 0.02636  *gray*gray + 0.381 *gray + 155.3
//exp = 0.05887  *gray*gray - 3.227 *gray + 258.7
//exp = 0.03582  *gray*gray + 2.974 *gray + 107.1
//室外顺光
//exp = 0.009022 *gray + 1.956  * gray + 2.129
//exp = 0.03259  *gray - 5.313  * gray + 328.6
//exp = 0.02094  *gray - 0.5423 * gray + 66.87
//exp = 0.01682  *gray - 0.6413 * gray + 148.3
//室外逆光
//exp = 0.03038  *gray*gray - 3.721  *gray + 317.8
//exp = 0.02078  *gray*gray - 0.833  *gray + 188.3
//exp = 0.005511 *gray*gray + 3.29   *gray - 20.9
//exp = 0.009337 *gray*gray + 2.883  *gray + 34.63
//室外侧光
//exp = 0.001403  *gray*gray + 6.034  *gray - 88.17
//exp = 0.0248    *gray*gray - 0.7344 *gray + 104.2
//exp = 0.01787   *gray*gray + 0.5792 *gray + 67.91
//exp = -0.005424 *gray*gray + 8.085  *gray - 256.1

//gray = -5.94e-05  * exp *exp + 0.268  *exp - 12.03
//gray = -5.293e-05 * exp *exp + 0.2288 *exp - 0.9559
//gray = -2.692e-05 * exp *exp + 0.1483 *exp + 17.88
//gray = -2.58e-05  * exp *exp + 0.1494 *exp - 0.3308

//#include <opencv2/opencv.hpp>

enum CameraType{
    Seeker=0,
    Sunmi=1
};

int getFunResultGrayExp(int iIdxLine, int iGray, CameraType cameraType=Seeker);

int getFunResultExpGray(int iIdxLine, int iExp, CameraType cameraType=Seeker); 

int getFunResultExpGray(int iIdxLine, int iExp);

int tableInterplote(int iExpTable[2701][256]);

int readExpTable(char* filePath, int iExpTable[2701][256]);

//int image2Mem(cv::Mat src, char* fileName);
//
//int image2Mem640x384(cv::Mat src, char* fileName);
#endif // __FACE_UTILS_H__