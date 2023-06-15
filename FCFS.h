
#include"job.h"

void FCFS(JOB job[], int quantity)
{
    for(int i = 0;i<quantity;i++)
    {
        if(i==0)            //第一个进程
        {
            job[i].runtime = job[i].needTime;      //周转时间=服务时间   
            job[i].endtime = job[i].reachTime + job[i].needTime;
        }
        else if (job[i].reachTime>job[i-1].endtime)             //第i个进程到达系统，第i-1个系统运行完毕
        {
            job[i].runtime = job[i].needTime;
            job[i].endtime = job[i].reachTime + job[i].needTime;
        }
        else               //第i个进程到达系统，第i-1个系统未运行完毕
        {
            job[i].runtime = job[i].needTime + job[i-1].endtime - job[i].reachTime;     //周转时间=服务时间+前一个进程的结束时间-到达时间
            job[i].endtime = job[i].reachTime + job[i].runtime;   //结束时间=到达时间+周转时间
        }   
    }
    printf("FCFS运行结果:\n");
    int sum_runtime = 0;
    double averruntime;
    printf("--------------------------------------------------------\n");
    printf("作业编号\t到达时间\t开始时间\t周转时间\n");
    printf("--------------------------------------------------------\n");
    for(int i =0;i<quantity;i++)
    {
        printf("%-8d\t%-8d\t%-8d\t%-8d\n",job[i].id,job[i].reachTime,job[i].endtime-job[i].needTime,job[i].runtime);
        wirtExcel(job, 2, i);
        sum_runtime = sum_runtime +job[i].runtime;
    }
    averruntime = sum_runtime*1.0/quantity;
    printf("--------------------------------------------------------\n");
    printf("平均周转时间:%.2f\n",averruntime);
    printf("\n");
}