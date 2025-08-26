/*
cai dat cac giai thuat lap lich cho CPU
Input:
	-n : So luong tien trinh
	-tt[n]: Chi so cua tien trinh
	-tdv [n]: Thoi diem vao Ready_List
	-dut[n] : Do uu tien cua tien trinh
	-tgth[n]: Thoi gian thuc hien
Output:
	- Bieu do Gantt
	-Thoi gian cho trung binh cua cac tien trinh
	-Thoi gian luu lai trong he thong cua moi tien trinh
*/
//********************************************************************//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//------------------------------------------------------------------

//------------------------------------------------------------------

//------------------------------------------------------------------
void Vekt(int kt, int sl) {
    for (int i = 0; i < sl; i++) {
        printf("%c",kt);  
    }
}
//------------------------------------------------------------------
//HAM TIM PHAN TU NHO NHAT CUA MANG
int Min(int tmp[],int n){
	int nhonhat =tmp[0]; //chot phan tu dau tien
	for(int i = 1; i < n ; i++)
		if (tmp[i] < nhonhat)//neu cac phan tu sau nho hon phan tu dau
			nhonhat = tmp[i];//doi cho
	return nhonhat;
}
//------------------------------------------------------------------
// Ham di chuyen con tro toi vi tri (x, y) - Linux version
void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}
//------------------------------------------------------------------
//Ham tinh tong cac phan tu trong mang 1 chieu
int Sum(int tmp[],int n){
	int tong = tmp[0];//gan tong = phan tu dau tien
	for( int i =1;i<n;i++)// duyet tu phan tu thu 2
		tong +=tmp[i];
		return tong;
}
//------------------------------------------------------------------
//Ham sap xep mang tmp1 giam dan, cac mang khac duoc keo theo
void SXGiam(int tmp1[],int tmp2[],int tmp3[],int tmp4[],int n){
    int i,j;
    for (i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if (tmp1[i]< tmp1[j]) // neu phan tu sau lon hon phan tu truoc thi doi cho
            {
                // doi cho tmp1
                int tmp=tmp1[i];
                tmp1[i]=tmp1[j];
                tmp1[j]=tmp;
                
                //cac mang keo theo tmp2
                tmp=tmp2[i];
                tmp2[i]=tmp2[j];
                tmp2[j]=tmp;
                
                //tmp3
                tmp=tmp3[i];
                tmp3[i]=tmp3[j];
                tmp3[j]=tmp;
                
                //tmp4
                tmp=tmp4[i];
                tmp4[i]=tmp4[j];
                tmp4[j]=tmp;
            }
}

//Ham sap xep mang tmp1 tang dan, cac mang khac duoc keo theo
void SXTang(int tmp1[],int tmp2[],int tmp3[],int tmp4[],int n){
    int i,j;
    for (i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if (tmp1[i]> tmp1[j]) // neu phan tu truoc lon hon phan tu sau thi doi cho
            {
                // doi cho tmp1
                int tmp=tmp1[i];
                tmp1[i]=tmp1[j];
                tmp1[j]=tmp;
                
                //cac mang keo theo tmp2
                tmp=tmp2[i];
                tmp2[i]=tmp2[j];
                tmp2[j]=tmp;
                
                //tmp3
                tmp=tmp3[i];
                tmp3[i]=tmp3[j];
                tmp3[j]=tmp;
                
                //tmp4
                tmp=tmp4[i];
                tmp4[i]=tmp4[j];
                tmp4[j]=tmp;
            }
}
//------------------------------------------------------------------
// Ham ve bieu do Gantt chung cho tat ca cac giai thuat
void veGantt(int tt[], int tgth[], int tgc[], int n, int startRow) {
    gotoXY(5, startRow);
    printf("Tien Trinh:");
    gotoXY(2, startRow + 2);
    printf("Thoi gian cho:");
    gotoXY(18, startRow + 1);
    Vekt(124, 1); // ky tu dau tien cua gantt "|"
    
    int demvach = 0; // dem vach "-" da ve
    
    // duyet qua tat ca cac tien trinh
    for(int i = 0; i < n; i++) {
        // tinh ti le de ve gantt
        int sovach = tgth[i] / Min(tgth, n); // tinh so vach "-"
        if(tgth[i] % Min(tgth, n) >= Min(tgth, n) / 2)
            sovach++;
        
        // nhay len hang tren de viet tien trinh
        gotoXY(18 + demvach + i, startRow);
        printf("P%d", tt[i]);
        gotoXY(19 + demvach + i, startRow + 1);
        Vekt(45, sovach * 3); // ve bang dau "-"
        if(i != n - 1) // neu chua phai tien trinh cuoi cung 
            Vekt(124, 1); // ve diem chuyen giao "|"
        else
            Vekt(124, 1); // Ket thuc GANTT
        gotoXY(18 + demvach + i, startRow + 2);
        printf("%d", tgc[i]);
        demvach += sovach * 3;
    }
    // nhay den cuoi gantt de viet tong thoi gian
    gotoXY(18 + demvach + n, startRow + 2);
    printf("%d", Sum(tgth, n));
}
//------------------------------------------------------------------
// Ham tinh thoi gian cho trung binh
float tinhTGCTrungBinh(int tgc[], int n) {
    return (float)Sum(tgc, n) / n;
}
//------------------------------------------------------------------
// Ham tinh thoi gian luu lai trong he thong
void tinhTGLuuLai(int tgc[], int tgth[], int tgll[], int n) {
    for(int i = 0; i < n; i++) {
        tgll[i] = tgc[i] + tgth[i];
    }
}
//------------------------------------------------------------------
// Ham in ket qua thong ke
void inThongKe(int tt[], int tgc[], int tgth[], int n, int startRow) {
    int tgll[100];
    tinhTGLuuLai(tgc, tgth, tgll, n);
    
    gotoXY(5, startRow + 4);
    printf("Thong ke ket qua:");
    gotoXY(5, startRow + 5);
    printf("Tien trinh | TG Cho | TG Thuc hien | TG Luu lai");
    gotoXY(5, startRow + 6);
    Vekt(45, 45);
    
    for(int i = 0; i < n; i++) {
        gotoXY(5, startRow + 7 + i);
        printf("    P%-7d| %-7d| %-13d| %-8d", tt[i], tgc[i], tgth[i], tgll[i]);
    }
    
    gotoXY(5, startRow + 8 + n);
    printf("Thoi gian cho trung binh: %.2f", tinhTGCTrungBinh(tgc, n));
}
//------------------------------------------------------------------
// Giai thuat FCFS (First Come First Served)
void FCFS(int tt[], int tdv[], int dut[], int tgth[], int n, int startRow) {
    int tgc[100]; // mang chua thoi gian cho cua tien trinh
    tgc[0] = 0; // thoi gian cho cua tien trinh dau tien = 0
    
    // thoi gian cho tt sau = T/G cho cua tt truoc + thoi gian thuc hien cua tien trinh
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth[i - 1];
    
    printf("1. Giai thuat FCFS");
    veGantt(tt, tgth, tgc, n, startRow);
    inThongKe(tt, tgc, tgth, n, startRow);
}
//------------------------------------------------------------------
// Giai thuat Priority (Do uu tien cao nhat truoc)
void Priority(int tt[], int tdv[], int dut[], int tgth[], int n, int startRow) {
    // Tao ban sao cac mang de sap xep
    int tt_temp[100], tdv_temp[100], dut_temp[100], tgth_temp[100];
    for(int i = 0; i < n; i++) {
        tt_temp[i] = tt[i];
        tdv_temp[i] = tdv[i];
        dut_temp[i] = dut[i];
        tgth_temp[i] = tgth[i];
    }
    
    // Sap xep theo do uu tien giam dan (uu tien cao nhat truoc)
    SXGiam(dut_temp, tt_temp, tdv_temp, tgth_temp, n);
    
    int tgc[100]; // mang chua thoi gian cho cua tien trinh
    tgc[0] = 0; // thoi gian cho cua tien trinh dau tien = 0
    
    // thoi gian cho tt sau = T/G cho cua tt truoc + thoi gian thuc hien cua tien trinh
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth_temp[i - 1];
    
    printf("2. Giai thuat Priority (Do uu tien)");
    veGantt(tt_temp, tgth_temp, tgc, n, startRow);
    inThongKe(tt_temp, tgc, tgth_temp, n, startRow);
}
//------------------------------------------------------------------
// Giai thuat SJF (Shortest Job First)
void SJF(int tt[], int tdv[], int dut[], int tgth[], int n, int startRow) {
    // Tao ban sao cac mang de sap xep
    int tt_temp[100], tdv_temp[100], dut_temp[100], tgth_temp[100];
    for(int i = 0; i < n; i++) {
        tt_temp[i] = tt[i];
        tdv_temp[i] = tdv[i];
        dut_temp[i] = dut[i];
        tgth_temp[i] = tgth[i];
    }
    
    // Sap xep theo thoi gian thuc hien tang dan (ngan nhat truoc)
    SXTang(tgth_temp, tt_temp, tdv_temp, dut_temp, n);
    
    int tgc[100]; // mang chua thoi gian cho cua tien trinh
    tgc[0] = 0; // thoi gian cho cua tien trinh dau tien = 0
    
    // thoi gian cho tt sau = T/G cho cua tt truoc + thoi gian thuc hien cua tien trinh
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth_temp[i - 1];
    
    printf("3. Giai thuat SJF (Shortest Job First)");
    veGantt(tt_temp, tgth_temp, tgc, n, startRow);
    inThongKe(tt_temp, tgc, tgth_temp, n, startRow);
}
//------------------------------------------------------------------
int main()
{
	int i,j; //cac bien chay trong chuong trinh
	int n=4; // so luong tien trinh
	int tt[4]={1,2,3,4};//chi so tien trinh
	int tdv[4]={0,1,2,3};//thoi diem vao ready list
	int dut[4]={4,2,1,3};//do uu tien cua tien trinh (cao hon = uu tien hon)
	int tgth[4]={13,8,21,16};//thoi gian thuc hien
	
	system("clear"); // Xoa man hinh (Linux)
	printf("\t\t\t\t\tCAC GIAI THUAT LAP LICH CHO CPU\n\n");
	
	// Giai thuat FCFS
	FCFS(tt, tdv, dut, tgth, n, 3);
	
	gotoXY(0, 20);
	printf("Nhan phim Enter de tiep tuc...");
	getchar();
	system("clear");
	
	printf("\t\t\t\t\tCAC GIAI THUAT LAP LICH CHO CPU\n\n");
	
	// Giai thuat Priority
	Priority(tt, tdv, dut, tgth, n, 3);
	
	gotoXY(0, 20);
	printf("Nhan phim Enter de tiep tuc...");
	getchar();
	system("clear");
	
	printf("\t\t\t\t\tCAC GIAI THUAT LAP LICH CHO CPU\n\n");
	
	// Giai thuat SJF
	SJF(tt, tdv, dut, tgth, n, 3);
	
	gotoXY(0, 20);
	printf("Nhan phim Enter de ket thuc...");
	getchar();
	
	return 0;
}
//------------------------------------------------------------------