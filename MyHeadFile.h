#ifndef MyHeadFile_H

#include <iostream> 
#include <stdio.h>  


#define MyHeadFile_H

#define PAI 3.1415926535898
#define Rad (PAI/180.0)                   // 角度转弧度的系数
#define Deg (180.0/PAI)                   // 弧度转角度的系数
#define C_Light 299792458.0               // 光速 m/s

#define R_WGS84  6378137.0                // WGS84椭球的长半轴 m 
#define F_WGS84  1.0/298.257223563        // WGS84椭球的扁率
#define Omega_WGS 7.2921151467e-5         // WGS84椭球的自转角速度 rad/s
#define GM_WGS   398600.5e+9              // WGS84椭球地心引力常数GM m3/s2

#define R_CGS2K  6378137.0                // CGCS2000椭球的长半轴 m
#define F_CGS2K  1.0/298.257222101        // CGCS2000椭球的扁率
#define Omega_BDS 7.2921150e-5            // CGCS2000椭球的自转角速度 rad/s
#define GM_BDS   398600.4418e+9           // CGCS2000椭球地心引力常数GM m3/s2

// GPS卫星信号的一些常量
#define  FG1_GPS  1575.42E6               // L1信号频率 
#define  FG2_GPS  1227.60E6               // L2信号频率
#define  WL1_GPS  (C_Light/FG1_GPS)       // L1信号波长
#define  WL2_GPS  (C_Light/FG2_GPS)       // L2信号波长

// BDS卫星信号的一些常量
#define  FG1_BDS  1561.098E6              // B1信号的频率 
#define  FG3_BDS  1268.520E6              // B3信号的频率 
#define  WL1_BDS  (C_Light/FG1_BDS)       // B1信号波长
#define  WL3_BDS  (C_Light/FG3_BDS)       // B3信号波长


#define MAXCHANNUM 36                     // 每一历元所能观测到的最大卫星数
#define MAXGPSNUM  32                     // GPS系统的最大卫星数
#define MAXBDSNUM 63                      // BDS系统的最大卫星数
#define MAXRAWLEN 50000                   // 文件或网口读取的单次最大字节数

#define POLYCRC32 0xEDB88320u             // 校验码生成函数所用
#define MAXBUFF 10000                     // 解码函数中所用buff的最大长度
#define OEM7HLEN 28                       // 数据头的字节数
#define OEM7SYNC1 0xAA                    // 数据头的标识1
#define OEM7SYNC2 0x44                    // 数据头的标识2
#define OEM7SYNC3 0x12                    // 数据头的标识3
#define ID_RANGE 43                       // 观测值类型的message的ID
#define ID_GPSEPH 7                       // GPS广播星历类型的message的ID
#define ID_BDSEPH 1696                    // BDS广播星历类型的message的ID
#define ID_POS 42                         // NovAtel接收机定位结果类型的message的ID

#define U1(p) (*((unsigned char *)(p)))   // 将指针p指向的内存中的值作为无符号字符返回
#define I1(p) (*((char *)(p)))            // 将指针p指向的内存中的值作为字符返回

// 导航卫星系统定义 
enum GNSSSys { UNKS = 0, GPS, BDS};

// 通用时间定义
struct COMMONTIME   
{
    short Year;
    unsigned short Month;
    unsigned short Day;
    unsigned short Hour;
    unsigned short Minute;
    double         Second;

    COMMONTIME()
    {
        Year = 0;
        Month = 0;
        Day = 0;
        Hour = 0;
        Minute = 0;
        Second = 0.0;
    }
};

// GPS时定义（周+周内秒的形式）
struct GPSTIME
{
    unsigned short Week;
    double         SecOfWeek;

    GPSTIME()
    {
        Week = 0;
        SecOfWeek = 0.0;
    }
};

// 简化儒略日定义
struct MJDTIME             
{
    int Days;
    double FracDay;

    MJDTIME()
    {
        Days = 0;
        FracDay = 0.0;
    }
};

// GPS+BDS广播星历
struct GPSEPHREC
{
    unsigned short PRN;
    GNSSSys     Sys;
    // TOC是完全用于卫星钟差的时间参数（卫星钟的参考时间） TOE是完全用于轨道拟合的时间参数（星历的参考时间）
    GPSTIME  	TOC, TOE; // s
    short		SVHealth; // 0-健康 1-不健康
    double		ClkBias, ClkDrift, ClkDriftRate; // 钟差 s  钟速 s/s  钟漂 s/s2
    unsigned int	IODE, IODC;//星历数据龄期 卫星钟的数据龄期
    double      TGD1, TGD2;// 广播星历播发的时间群延迟
    double		SqrtA, e, M0, OMEGA, i0, omega, OMEGADot, iDot, DeltaN;
    double		Crs, Cuc, Cus, Cic, Cis, Crc;// 摄动项
    double		SVAccuracy;

    GPSEPHREC() {
        PRN = SVHealth = 0;
        Sys = UNKS;
        ClkBias = ClkDrift = ClkDriftRate = IODE = IODC = TGD1 = TGD2 = 0.0;
        SqrtA = e = M0 = OMEGA = i0 = omega = OMEGADot = iDot = DeltaN = 0.0;
        Crs = Cuc = Cus = Cic = Cis = Crc = SVAccuracy = 0.0;
    }
};

// 每颗卫星的观测数据定义 
struct SATOBS
{
    short    Prn;
    GNSSSys  System;
    // GPS：L1-0，L2-1   BDS：B1I-0, B3I-1
    double   p[2], l[2], d[2]; // 伪距、相位为m,多普勒为m/s
    double   cn0[2], LockTime[2]; // 载噪比，跟踪时间
    unsigned char half[2];
    bool     Valid; // 有效性

    SATOBS()
    {
        Prn = 0;
        System = UNKS;
        p[0] = p[1] = l[0] = l[1] = d[0] = d[1] = 0.0;
        cn0[0] = cn0[1] = 0.0;
        LockTime[0] = LockTime[1] = 0.0;
        half[0] = half[1] = 0;
        Valid = false;
    }
};

// 每个历元的定位结果结构体定义 
// 同时也用于保存NovAtel接收机定位结果（此时仅用到时间、位置和使用卫星数）
struct POSRES
{
    GPSTIME Time;
    double Pos[3], Vel[3];
    double PDOP, SigmaPos, SigmaVel;
    int SatNum;

    POSRES()
    {
        Time.Week = 0;
        Time.SecOfWeek = 0.0;
        for (int i = 0; i < 3; i++) Pos[i] = 0.0,Vel[i] = 0.0;
        PDOP = SigmaPos = SigmaVel = 0.0;
        SatNum = 0;
    }

};

// MW和GF组合观测值数据的定义(用于粗差探测)
struct MWGF
{
    short Prn;//卫星号
    GNSSSys Sys;
    double MW, GF, PIF;
    //平滑计数
    int n;

    MWGF()
    {
        Prn = n = 0;
        Sys = UNKS;
        MW = GF = PIF = 0.0;
    }
};

// 每颗卫星位置、速度和钟差等的中间计算结果 
struct SATMIDRES
{
    double SatPos[3], SatVel[3];
    double SatClkOft, SatClkSft;
    double Elevation, Azimuth; // 高度角，方位角
    double TropCorr; // 对流层延迟改正
    /*
    GPS的tgd基准是L1、L2组成的无电离层组合观测值
    BDS的tgd基准是B3
    */
    double Tgd1, Tgd2; // 硬件延迟
    bool Valid;  // false=没有星历或星历过期 true-星历可用

    SATMIDRES()
    {
        SatPos[0] = SatPos[1] = SatPos[2] = 0.0;
        SatVel[0] = SatVel[1] = SatVel[2] = 0.0;
        Elevation = PAI / 2.0;
        Azimuth = 0.0;
        SatClkOft = SatClkSft = 0.0;
        Tgd1 = Tgd2 = TropCorr = 0.0;
        Valid = false;
    }
};

// 每个历元的观测数据定义 
struct EPOCHOBS
{
    GPSTIME    Time;
    short      SatNum;
    SATOBS     SatObs[MAXCHANNUM]; // 卫星的观测数据
    SATMIDRES  SatPVT[MAXCHANNUM]; // 卫星位置等计算结果，数组索引与SatObs相同
    MWGF       ComObs[MAXCHANNUM]; // 当前历元的组合观测值，数组索引与SatObs相同
    EPOCHOBS()
    {
        SatNum = 0;
    }
};

// 通用时,GPS时和简化儒略日之间的相互转换函数
void CommonTimeToMJDTime(const COMMONTIME* CT, MJDTIME* MJDT);
void MJDTimeToCommonTime(const MJDTIME* MJDT, COMMONTIME* CT);
void GPSTimeToMJDTime(const GPSTIME* GT, MJDTIME* MJDT);
void MJDTimeToGPSTime(const MJDTIME* MJDT, GPSTIME* GT);
void CommonTimeToGPSTime(const COMMONTIME* CT, GPSTIME* GT);
void GPSTimeToCommonTime(const GPSTIME* GT, COMMONTIME* CT);
// 求两个GPS时之间的差值
double GetDiffTime(const GPSTIME* GT2, const GPSTIME* GT1); 


// 空间直角坐标、大地坐标的相互转换函数
void XYZToBLH(const double xyz[3], double blh[3], const double R, const double F);
void BLHToXYZ(const double BLH[3], double XYZ[3], const double R, const double F);
// 测站地平坐标转换矩阵计算函数
void BLHToENUMat(const double Blh[], double Mat[]); 
// 卫星高度角方位角计算函数
void CompSatElAz(int i,const double Xr[], const double Xs[], double* Elev, double* Azim); 
// 定位误差计算函数
void Comp_dEnu(int type, const double X0[], const double Xr[], double dENU[]);


// 向量点积
double VectDot(int m, int n, const double A[], const double B[]);
// 向量叉乘
bool CrossDot(int m, int n, const double A[], const double B[], double C[]);
// 矩阵相加
bool MatrixAddition(int m, int n, const double M1[], const double M2[], double M3[]);
//矩阵减法
bool MatrixSubtraction(int m, int n, const double M1[], const double M2[], double M3[]);
// 矩阵相乘
bool MatrixMultiply(int m1, int n1, int m2, int n2, const double M1[], const double M2[], double M3[]);
// 矩阵转置
bool MatrixTranspose(int m, int n, const double M1[], double MT[]);
// 矩阵求逆
int MatrixInv(int n, double a[], double b[]);
// 矩阵重构
void deleteRowAndColumn(int m, int n, int m1, int n1, double M[]);// 删除指定的一行和一列
void deleteRow(int rows, int rowToDelete, double vector[]);// 删除指定的一行


// NovAtel OEM7数据解码函数
int DecodeNovOem7Dat(unsigned char Buff[], int& Len, EPOCHOBS* obs, GPSEPHREC geph[], GPSEPHREC beph[], POSRES* pres);
int decode_rangeb_oem7(unsigned char* buff, EPOCHOBS* obs);// 读取观测值消息
int decode_gpsephem(unsigned char* buff, GPSEPHREC* eph);// 读取GPS广播星历消息
int decode_bdsephem(unsigned char* buff, GPSEPHREC* eph);// 读取BDS广播星历消息
int decode_psrpos(unsigned char* buff, POSRES* pos);// 读取接收机定位结果消息
unsigned int crc32(const unsigned char* buff, int len);// 校验码生成函数

// 解码辅助转换函数
unsigned short U2(unsigned char* p);
unsigned int U4(unsigned char* p);
int U8(unsigned char* p);
float R4(unsigned char* p);
double R8(unsigned char* p);

// 计算卫星位置、速度和钟差等中间结果
bool CompGPSSatPVT(const int Prn, const GPSTIME* t, const GPSEPHREC* Eph, SATMIDRES* Mid);// 计算给定时刻的GPS卫星PVT
bool CompBDSSatPVT(const int Prn, const GPSTIME* t, const GPSEPHREC* Eph, SATMIDRES* Mid);// 计算给定时刻的BDS卫星PVT
void ComputeGPSSatOrbitAtSignalTrans(EPOCHOBS* Epk, GPSEPHREC* GPSEph, GPSEPHREC* BDSEph, double RcvPos[3]);// 计算信号发射时刻对应卫星的PVT
double hopfield(double H, double E);// 对流层延迟改正函数

// 粗差探测
void DetectOutlier(EPOCHOBS* obs);

// SPP
bool SPP(EPOCHOBS* Epoch, GPSEPHREC* GPSEph, GPSEPHREC* BDSEph, POSRES* Res);
// SPV
void SPV(EPOCHOBS* Epoch, POSRES* Res);

// 结果输出函数
void OutputResult(const POSRES* pres, const POSRES* res, double enu[]);

#endif
