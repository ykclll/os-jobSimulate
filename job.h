#ifndef job_h
#define job_h
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define MAXJOB 50

int quantity = 0; //作业总数


//PCB
typedef struct JOB 
{
    int id;//作业ID
    int reachTime;//到达时间
    int needTime;//作业长度，即需要运行的时间
    double RR;//响应比
    int waitTime;//等待时间
    int startTime;//开始时间
    int visit;          //作业是否被访问(完成)
    int endtime;        //作业结束时间
    int runtime;        //作业周转时间
    int remainNeedTime; //剩余作业长度
    int reached;        //是否到达
}JOB;


//作业初始化
void init(JOB *job) {
    for (int i = 0; i < MAXJOB; i++) {
        job[i].id = -1;
        job[i].reachTime = 0;
        job[i].needTime = 0;
        job[i].RR = -1;
        job[i].waitTime = 0; 
        job[i].startTime = 0;
        job[i].visit = 0;
        job[i].endtime = 0;
        job[i].runtime = 0;
        job[i].remainNeedTime = 0;
        job[i].reached = 0;
    }
}


//按作业到达时间排序
void sort_reachTime(JOB *job) {
    for(int i = 0;i<quantity-1;i++) {
        for(int j = 0;j<quantity-i-1;j++) {
            if(job[j].reachTime>job[j+1].reachTime) {
                JOB temp = job[j];
                job[j] = job[j+1];
                job[j+1] = temp;           
            }
        }
    }
}

//读取作业信息并输出
void readJOBdata(JOB *job) {
    char filename[20];
    printf("请输入测试文件名:\n");
    scanf("%s", filename);
    FILE* file;
    file = fopen(filename, "rw");
    if (file != NULL) {
    int i = 0;
        while (!feof(file)) {
            fscanf(file, "%d %d %d\n", &(job[i].id), &(job[i].reachTime), &(job[i].needTime));
            job[i].remainNeedTime = job[i].needTime;
            quantity++;
            i++;
        }
    } else {
        printf("打开文件失败,请检查输入文件名");
        exit(0);
    }
}


//展示初始作业序列
void showJobs(JOB job[]) {
    printf("初始作业序列:\n");
    printf("-------------------------------------\n");
    printf("作业编号\t到达时间\t作业长度\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < quantity; i++) {
        printf("%-8d\t%-8d\t%-8d\n", job[i].id, job[i].reachTime, job[i].needTime);
    }
    printf("-------------------------------------\n\n");
}

//将输出结果导出到Excel中
void wirtExcel(JOB job[], int choice, int index) {
    FILE *fp = NULL;
    static int a = 0, b = 0, c = 0, d = 0;
    fp = fopen("output.csv", "a");
    if (choice == 1) {
        if (a == 0) {
            fprintf(fp, "\nHRRN\njobID,reachTime,startTime,waitTime,roundTime\n");
            a++;
        }
        fprintf(fp, "%d,%d,%d,%d,%d\n", job[index].id, job[index].reachTime, job[index].startTime, job[index].waitTime, job[index].runtime);
    } else if (choice == 2) {
        if (b == 0) {
            fprintf(fp, "\nFCFS\njobID,reachTime,startTime,roundTime\n");
            b++;
        }
        fprintf(fp, "%d,%d,%d,%d\n",job[index].id,job[index].reachTime,job[index].endtime-job[index].needTime,job[index].runtime);
    } else if (choice == 3) {
        if (c == 0) {
            fprintf(fp, "\nSJF\njobID,reachTime,runTime,startTime,roundTime\n");
            c++;
        }
        fprintf(fp, "%d,%d,%d,%d,%d\n",
            job[index].id, job[index].reachTime, job[index].needTime, job[index].endtime, job[index].runtime);
    } else if (choice == 4) {
        if (d == 0) {
            fprintf(fp, "\nPSJF\njobID,reachTime,startTime,roundTime\n");
            d++;
        }
        fprintf(fp, "%d,%d,%d,%d\n", job[index].id, job[index].reachTime, job[index].startTime, job[index].runtime);
    }
    fclose(fp);
}

#endif