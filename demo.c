/*
Demo cac giai thuat lap lich cho CPU
*/
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------
//HAM TIM PHAN TU NHO NHAT CUA MANG
int Min(int tmp[],int n){
	int nhonhat =tmp[0];
	for(int i = 1; i < n ; i++)
		if (tmp[i] < nhonhat)
			nhonhat = tmp[i];
	return nhonhat;
}

//Ham tinh tong cac phan tu trong mang 1 chieu
int Sum(int tmp[],int n){
	int tong = tmp[0];
	for( int i =1;i<n;i++)
		tong +=tmp[i];
		return tong;
}

//Ham sap xep mang tmp1 giam dan, cac mang khac duoc keo theo
void SXGiam(int tmp1[],int tmp2[],int tmp3[],int tmp4[],int n){
    int i,j;
    for (i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if (tmp1[i]< tmp1[j])
            {
                int tmp=tmp1[i];
                tmp1[i]=tmp1[j];
                tmp1[j]=tmp;
                
                tmp=tmp2[i];
                tmp2[i]=tmp2[j];
                tmp2[j]=tmp;
                
                tmp=tmp3[i];
                tmp3[i]=tmp3[j];
                tmp3[j]=tmp;
                
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
            if (tmp1[i]> tmp1[j])
            {
                int tmp=tmp1[i];
                tmp1[i]=tmp1[j];
                tmp1[j]=tmp;
                
                tmp=tmp2[i];
                tmp2[i]=tmp2[j];
                tmp2[j]=tmp;
                
                tmp=tmp3[i];
                tmp3[i]=tmp3[j];
                tmp3[j]=tmp;
                
                tmp=tmp4[i];
                tmp4[i]=tmp4[j];
                tmp4[j]=tmp;
            }
}

// Ham ve bieu do Gantt don gian
void veGanttDonGian(int tt[], int tgth[], int tgc[], int n) {
    printf("Bieu do Gantt:\n");
    printf("|");
    for(int i = 0; i < n; i++) {
        printf(" P%d |", tt[i]);
    }
    printf("\n");
    
    printf("0");
    for(int i = 0; i < n; i++) {
        printf("    %d", tgc[i] + tgth[i]);
    }
    printf("\n\n");
}

// Ham tinh thoi gian cho trung binh
float tinhTGCTrungBinh(int tgc[], int n) {
    return (float)Sum(tgc, n) / n;
}

// Ham in ket qua thong ke
void inThongKe(int tt[], int tgc[], int tgth[], int n) {
    printf("Thong ke ket qua:\n");
    printf("Tien trinh | TG Cho | TG Thuc hien | TG Luu lai\n");
    printf("-------------------------------------------\n");
    
    for(int i = 0; i < n; i++) {
        int tgll = tgc[i] + tgth[i];
        printf("    P%-7d| %-7d| %-13d| %-8d\n", tt[i], tgc[i], tgth[i], tgll);
    }
    
    printf("\nThoi gian cho trung binh: %.2f\n", tinhTGCTrungBinh(tgc, n));
    printf("============================================\n\n");
}

// Giai thuat FCFS (First Come First Served)
void FCFS(int tt[], int tdv[], int dut[], int tgth[], int n) {
    printf("=== GIAI THUAT FCFS (First Come First Served) ===\n");
    
    int tgc[100];
    tgc[0] = 0;
    
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth[i - 1];
    
    veGanttDonGian(tt, tgth, tgc, n);
    inThongKe(tt, tgc, tgth, n);
}

// Giai thuat Priority (Do uu tien cao nhat truoc)
void Priority(int tt[], int tdv[], int dut[], int tgth[], int n) {
    printf("=== GIAI THUAT PRIORITY (Do uu tien) ===\n");
    
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
    
    int tgc[100];
    tgc[0] = 0;
    
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth_temp[i - 1];
    
    printf("Thu tu thuc hien theo do uu tien (cao -> thap):\n");
    for(int i = 0; i < n; i++) {
        printf("P%d (uu tien: %d, thoi gian: %d) ", tt_temp[i], dut_temp[i], tgth_temp[i]);
    }
    printf("\n\n");
    
    veGanttDonGian(tt_temp, tgth_temp, tgc, n);
    inThongKe(tt_temp, tgc, tgth_temp, n);
}

// Giai thuat SJF (Shortest Job First)
void SJF(int tt[], int tdv[], int dut[], int tgth[], int n) {
    printf("=== GIAI THUAT SJF (Shortest Job First) ===\n");
    
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
    
    int tgc[100];
    tgc[0] = 0;
    
    for(int i = 1; i < n; i++)
        tgc[i] = tgc[i - 1] + tgth_temp[i - 1];
    
    printf("Thu tu thuc hien theo thoi gian (ngan -> dai):\n");
    for(int i = 0; i < n; i++) {
        printf("P%d (thoi gian: %d) ", tt_temp[i], tgth_temp[i]);
    }
    printf("\n\n");
    
    veGanttDonGian(tt_temp, tgth_temp, tgc, n);
    inThongKe(tt_temp, tgc, tgth_temp, n);
}

int main()
{
    int n = 4; // so luong tien trinh
    int tt[4] = {1, 2, 3, 4}; // chi so tien trinh
    int tdv[4] = {0, 1, 2, 3}; // thoi diem vao ready list
    int dut[4] = {4, 2, 1, 3}; // do uu tien cua tien trinh (cao hon = uu tien hon)
    int tgth[4] = {13, 8, 21, 16}; // thoi gian thuc hien
    
    printf("======= CAC GIAI THUAT LAP LICH CHO CPU =======\n\n");
    printf("Du lieu dau vao:\n");
    printf("Tien trinh: ");
    for(int i = 0; i < n; i++) printf("P%d ", tt[i]);
    printf("\nThoi gian thuc hien: ");
    for(int i = 0; i < n; i++) printf("%d ", tgth[i]);
    printf("\nDo uu tien: ");
    for(int i = 0; i < n; i++) printf("%d ", dut[i]);
    printf("\n\n");
    
    // Giai thuat FCFS
    FCFS(tt, tdv, dut, tgth, n);
    
    // Giai thuat Priority
    Priority(tt, tdv, dut, tgth, n);
    
    // Giai thuat SJF
    SJF(tt, tdv, dut, tgth, n);
    
    return 0;
}