#ifndef MyHeadFile_H

#include <iostream> 
#include <stdio.h>  


#define MyHeadFile_H

#define PAI 3.1415926535898
#define Rad (PAI/180.0)                   // �Ƕ�ת���ȵ�ϵ��
#define Deg (180.0/PAI)                   // ����ת�Ƕȵ�ϵ��
#define C_Light 299792458.0               // ���� m/s

#define R_WGS84  6378137.0                // WGS84����ĳ����� m 
#define F_WGS84  1.0/298.257223563        // WGS84����ı���
#define Omega_WGS 7.2921151467e-5         // WGS84�������ת���ٶ� rad/s
#define GM_WGS   398600.5e+9              // WGS84���������������GM m3/s2

#define R_CGS2K  6378137.0                // CGCS2000����ĳ����� m
#define F_CGS2K  1.0/298.257222101        // CGCS2000����ı���
#define Omega_BDS 7.2921150e-5            // CGCS2000�������ת���ٶ� rad/s
#define GM_BDS   398600.4418e+9           // CGCS2000���������������GM m3/s2

// GPS�����źŵ�һЩ����
#define  FG1_GPS  1575.42E6               // L1�ź�Ƶ�� 
#define  FG2_GPS  1227.60E6               // L2�ź�Ƶ��
#define  WL1_GPS  (C_Light/FG1_GPS)       // L1�źŲ���
#define  WL2_GPS  (C_Light/FG2_GPS)       // L2�źŲ���

// BDS�����źŵ�һЩ����
#define  FG1_BDS  1561.098E6              // B1�źŵ�Ƶ�� 
#define  FG3_BDS  1268.520E6              // B3�źŵ�Ƶ�� 
#define  WL1_BDS  (C_Light/FG1_BDS)       // B1�źŲ���
#define  WL3_BDS  (C_Light/FG3_BDS)       // B3�źŲ���


#define MAXCHANNUM 36                     // ÿһ��Ԫ���ܹ۲⵽�����������
#define MAXGPSNUM  32                     // GPSϵͳ�����������
#define MAXBDSNUM 63                      // BDSϵͳ�����������
#define MAXRAWLEN 50000                   // �ļ������ڶ�ȡ�ĵ�������ֽ���

#define POLYCRC32 0xEDB88320u             // У�������ɺ�������
#define MAXBUFF 10000                     // ���뺯��������buff����󳤶�
#define OEM7HLEN 28                       // ����ͷ���ֽ���
#define OEM7SYNC1 0xAA                    // ����ͷ�ı�ʶ1
#define OEM7SYNC2 0x44                    // ����ͷ�ı�ʶ2
#define OEM7SYNC3 0x12                    // ����ͷ�ı�ʶ3
#define ID_RANGE 43                       // �۲�ֵ���͵�message��ID
#define ID_GPSEPH 7                       // GPS�㲥�������͵�message��ID
#define ID_BDSEPH 1696                    // BDS�㲥�������͵�message��ID
#define ID_POS 42                         // NovAtel���ջ���λ������͵�message��ID

#define U1(p) (*((unsigned char *)(p)))   // ��ָ��pָ����ڴ��е�ֵ��Ϊ�޷����ַ�����
#define I1(p) (*((char *)(p)))            // ��ָ��pָ����ڴ��е�ֵ��Ϊ�ַ�����

// ��������ϵͳ���� 
enum GNSSSys { UNKS = 0, GPS, BDS};

// ͨ��ʱ�䶨��
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

// GPSʱ���壨��+���������ʽ��
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

// �������ն���
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

// GPS+BDS�㲥����
struct GPSEPHREC
{
    unsigned short PRN;
    GNSSSys     Sys;
    // TOC����ȫ���������Ӳ��ʱ������������ӵĲο�ʱ�䣩 TOE����ȫ���ڹ����ϵ�ʱ������������Ĳο�ʱ�䣩
    GPSTIME  	TOC, TOE; // s
    short		SVHealth; // 0-���� 1-������
    double		ClkBias, ClkDrift, ClkDriftRate; // �Ӳ� s  ���� s/s  ��Ư s/s2
    unsigned int	IODE, IODC;//������������ �����ӵ���������
    double      TGD1, TGD2;// �㲥����������ʱ��Ⱥ�ӳ�
    double		SqrtA, e, M0, OMEGA, i0, omega, OMEGADot, iDot, DeltaN;
    double		Crs, Cuc, Cus, Cic, Cis, Crc;// �㶯��
    double		SVAccuracy;

    GPSEPHREC() {
        PRN = SVHealth = 0;
        Sys = UNKS;
        ClkBias = ClkDrift = ClkDriftRate = IODE = IODC = TGD1 = TGD2 = 0.0;
        SqrtA = e = M0 = OMEGA = i0 = omega = OMEGADot = iDot = DeltaN = 0.0;
        Crs = Cuc = Cus = Cic = Cis = Crc = SVAccuracy = 0.0;
    }
};

// ÿ�����ǵĹ۲����ݶ��� 
struct SATOBS
{
    short    Prn;
    GNSSSys  System;
    // GPS��L1-0��L2-1   BDS��B1I-0, B3I-1
    double   p[2], l[2], d[2]; // α�ࡢ��λΪm,������Ϊm/s
    double   cn0[2], LockTime[2]; // ����ȣ�����ʱ��
    unsigned char half[2];
    bool     Valid; // ��Ч��

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

// ÿ����Ԫ�Ķ�λ����ṹ�嶨�� 
// ͬʱҲ���ڱ���NovAtel���ջ���λ�������ʱ���õ�ʱ�䡢λ�ú�ʹ����������
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

// MW��GF��Ϲ۲�ֵ���ݵĶ���(���ڴֲ�̽��)
struct MWGF
{
    short Prn;//���Ǻ�
    GNSSSys Sys;
    double MW, GF, PIF;
    //ƽ������
    int n;

    MWGF()
    {
        Prn = n = 0;
        Sys = UNKS;
        MW = GF = PIF = 0.0;
    }
};

// ÿ������λ�á��ٶȺ��Ӳ�ȵ��м������ 
struct SATMIDRES
{
    double SatPos[3], SatVel[3];
    double SatClkOft, SatClkSft;
    double Elevation, Azimuth; // �߶Ƚǣ���λ��
    double TropCorr; // �������ӳٸ���
    /*
    GPS��tgd��׼��L1��L2��ɵ��޵������Ϲ۲�ֵ
    BDS��tgd��׼��B3
    */
    double Tgd1, Tgd2; // Ӳ���ӳ�
    bool Valid;  // false=û���������������� true-��������

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

// ÿ����Ԫ�Ĺ۲����ݶ��� 
struct EPOCHOBS
{
    GPSTIME    Time;
    short      SatNum;
    SATOBS     SatObs[MAXCHANNUM]; // ���ǵĹ۲�����
    SATMIDRES  SatPVT[MAXCHANNUM]; // ����λ�õȼ�����������������SatObs��ͬ
    MWGF       ComObs[MAXCHANNUM]; // ��ǰ��Ԫ����Ϲ۲�ֵ������������SatObs��ͬ
    EPOCHOBS()
    {
        SatNum = 0;
    }
};

// ͨ��ʱ,GPSʱ�ͼ�������֮����໥ת������
void CommonTimeToMJDTime(const COMMONTIME* CT, MJDTIME* MJDT);
void MJDTimeToCommonTime(const MJDTIME* MJDT, COMMONTIME* CT);
void GPSTimeToMJDTime(const GPSTIME* GT, MJDTIME* MJDT);
void MJDTimeToGPSTime(const MJDTIME* MJDT, GPSTIME* GT);
void CommonTimeToGPSTime(const COMMONTIME* CT, GPSTIME* GT);
void GPSTimeToCommonTime(const GPSTIME* GT, COMMONTIME* CT);
// ������GPSʱ֮��Ĳ�ֵ
double GetDiffTime(const GPSTIME* GT2, const GPSTIME* GT1); 


// �ռ�ֱ�����ꡢ���������໥ת������
void XYZToBLH(const double xyz[3], double blh[3], const double R, const double F);
void BLHToXYZ(const double BLH[3], double XYZ[3], const double R, const double F);
// ��վ��ƽ����ת��������㺯��
void BLHToENUMat(const double Blh[], double Mat[]); 
// ���Ǹ߶ȽǷ�λ�Ǽ��㺯��
void CompSatElAz(int i,const double Xr[], const double Xs[], double* Elev, double* Azim); 
// ��λ�����㺯��
void Comp_dEnu(int type, const double X0[], const double Xr[], double dENU[]);


// �������
double VectDot(int m, int n, const double A[], const double B[]);
// �������
bool CrossDot(int m, int n, const double A[], const double B[], double C[]);
// �������
bool MatrixAddition(int m, int n, const double M1[], const double M2[], double M3[]);
//�������
bool MatrixSubtraction(int m, int n, const double M1[], const double M2[], double M3[]);
// �������
bool MatrixMultiply(int m1, int n1, int m2, int n2, const double M1[], const double M2[], double M3[]);
// ����ת��
bool MatrixTranspose(int m, int n, const double M1[], double MT[]);
// ��������
int MatrixInv(int n, double a[], double b[]);
// �����ع�
void deleteRowAndColumn(int m, int n, int m1, int n1, double M[]);// ɾ��ָ����һ�к�һ��
void deleteRow(int rows, int rowToDelete, double vector[]);// ɾ��ָ����һ��


// NovAtel OEM7���ݽ��뺯��
int DecodeNovOem7Dat(unsigned char Buff[], int& Len, EPOCHOBS* obs, GPSEPHREC geph[], GPSEPHREC beph[], POSRES* pres);
int decode_rangeb_oem7(unsigned char* buff, EPOCHOBS* obs);// ��ȡ�۲�ֵ��Ϣ
int decode_gpsephem(unsigned char* buff, GPSEPHREC* eph);// ��ȡGPS�㲥������Ϣ
int decode_bdsephem(unsigned char* buff, GPSEPHREC* eph);// ��ȡBDS�㲥������Ϣ
int decode_psrpos(unsigned char* buff, POSRES* pos);// ��ȡ���ջ���λ�����Ϣ
unsigned int crc32(const unsigned char* buff, int len);// У�������ɺ���

// ���븨��ת������
unsigned short U2(unsigned char* p);
unsigned int U4(unsigned char* p);
int U8(unsigned char* p);
float R4(unsigned char* p);
double R8(unsigned char* p);

// ��������λ�á��ٶȺ��Ӳ���м���
bool CompGPSSatPVT(const int Prn, const GPSTIME* t, const GPSEPHREC* Eph, SATMIDRES* Mid);// �������ʱ�̵�GPS����PVT
bool CompBDSSatPVT(const int Prn, const GPSTIME* t, const GPSEPHREC* Eph, SATMIDRES* Mid);// �������ʱ�̵�BDS����PVT
void ComputeGPSSatOrbitAtSignalTrans(EPOCHOBS* Epk, GPSEPHREC* GPSEph, GPSEPHREC* BDSEph, double RcvPos[3]);// �����źŷ���ʱ�̶�Ӧ���ǵ�PVT
double hopfield(double H, double E);// �������ӳٸ�������

// �ֲ�̽��
void DetectOutlier(EPOCHOBS* obs);

// SPP
bool SPP(EPOCHOBS* Epoch, GPSEPHREC* GPSEph, GPSEPHREC* BDSEph, POSRES* Res);
// SPV
void SPV(EPOCHOBS* Epoch, POSRES* Res);

// ����������
void OutputResult(const POSRES* pres, const POSRES* res, double enu[]);

#endif
