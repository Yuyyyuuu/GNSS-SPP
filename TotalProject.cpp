#include"MyHeadFile.h"
#include"sockets.h"


int main()
{
    int mode;//默认0为事后，1为实时
    printf("Please enter a value for mode(0-Post-processing 1-Real-time processing): ");
    scanf("%d", &mode);
    printf("You entered: %d\n", mode);

    EPOCHOBS obs;
    GPSEPHREC geph[MAXGPSNUM];
    GPSEPHREC beph[MAXBDSNUM];
    POSRES pres;
    POSRES res;
    double enu[3] = { 0,0,0 };// 定位误差
    int flag = 0;//是否进行定位的标志

    if (mode == 0)
    {
        unsigned char Buff[MAXRAWLEN];
        FILE* file;
        if (fopen_s(&file, "202010261820.oem719", "rb") != 0)
        {
            printf("无法打开文件！\n");
            return 0;
        }
        int len = 0;
        while (!feof(file))
        {
            int obtain_byte = fread(Buff + len, 1, MAXRAWLEN - len, file);
            if (obtain_byte < MAXRAWLEN - len) break;
            len = obtain_byte + len;
            flag = DecodeNovOem7Dat(Buff, len, &obs, geph, beph, &pres);

            if (flag == 1)
            {
                // 粗差探测并计算可用数据的组合观测值
                DetectOutlier(&obs);
                int f = SPP(&obs, geph, beph, &res);
                if (f) SPV(&obs, &res);
                OutputResult(&pres, &res,enu);             
            }
        }
        fclose(file);
    }
    else if (mode == 1)
    {
        unsigned char Buff[MAXRAWLEN];
        unsigned char buff[MAXRAWLEN];
        SOCKET NetGps;
        if (OpenSocket(NetGps, "47.114.134.129", 7190) == false)
        {
            printf("This ip & port was not opened.\n");
            return 0;
        }
        int lenR = 0;
        int lenD = 0;// Buff的长度（字节数）
        // 测站pos结果文件
        FILE* file1 = fopen("D:\\卫星导航算法课程\\result.txt", "w");
        if (file1 == NULL)
        {
            printf("无法打开文件。\n");
            return 1;
        }
        fprintf(file1, " E(m)  N(m)  U(m)  Vx(m/s)  Vy(m/s)  Vz(m/s)  PDOP\n");
        while (true)
        {
            Sleep(980);
            if ((lenR = recv(NetGps, (char*)buff, MAXRAWLEN, 0)) > 0)
            {
                memcpy(Buff + lenD, buff, lenR);
                lenD = lenR + lenD;
                memset(buff, 0, MAXRAWLEN);
                flag = DecodeNovOem7Dat(Buff, lenD, &obs, geph, beph, &pres);
                if (flag == 1)
                {
                    // 粗差探测并计算可用数据的组合观测值
                    DetectOutlier(&obs);
                    int f = SPP(&obs, geph, beph, &res);
                    if (f) SPV(&obs, &res);
                    OutputResult(&pres, &res, enu);
                    fprintf(file1, "%5.3f %5.3f %5.3f %6.3f %6.3f %6.3f %6.4f\n", enu[0], enu[1], enu[2], res.Vel[0], res.Vel[1], res.Vel[2], res.PDOP);
                }
            }
        }
        fclose(file1);
    }
     system("pause");
}


