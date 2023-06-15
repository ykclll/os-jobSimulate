#include "job.h"
//计算响应比，并返回当前响应比最大的job
int calculateRR(JOB job[], int currentTime2) {
    double maxRR = -1;//最高响应比
    int index2;
    for (int i = 0; i < quantity && job[i].reachTime <= currentTime2; i++) {
        if (job[i].visit != 1) {
            job[i].waitTime = currentTime2 - job[i].reachTime;
            job[i].RR = (double)job[i].waitTime / (double)job[i].needTime;
            if (job[i].RR > maxRR) {
                maxRR = job[i].RR;
                index2 = i;
            }
        }
    }

    if (maxRR == -1) {
        for (int i = 0; i < quantity; i++) {
            if (job[i].reachTime > currentTime2 && job[i].visit != 0) {
                job[i].RR = 0;
                maxRR = job[i].RR;
                index2 = i;
            }
        }
    }

    return index2;
}

void HRRN(JOB job[], int quantity) {
    int currentTime2 = job[0].reachTime;
    int roundTime2 = 0;//周转时间
    int index2;//当前响应比最大的job
    index2 = calculateRR(job, job[0].reachTime);

    printf("高响应比优先调度:\n");
    printf("------------------------------------------------------------------------\n");
    printf("作业编号\t到达时间\t开始时间\t等待时间\t周转时间\n");
    printf("------------------------------------------------------------------------\n");
    //按行输出作业信息
    for (int i = 0; i < quantity; i++) {
        if (job[index2].reachTime <= currentTime2) {    //若当前作业已在等待
            job[index2].startTime = currentTime2; //记录开始时间
            job[index2].waitTime = currentTime2 - job[index2].reachTime; //等待时间为当前时间减等待时间
            job[index2].runtime = job[index2].waitTime + job[index2].needTime;
            /*
                作业运行...
            */
            currentTime2 = currentTime2 + job[index2].needTime;    //更新当前时间
        } else {                                              //当前作业不在等待队列中
            job[index2].startTime = job[index2].reachTime;    //到达时间即为开始时间
            job[index2].waitTime = 0;
            currentTime2 = job[index2].startTime + job[index2].needTime;
            job[index2].runtime = job[index2].needTime;
        }

        printf("%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n", job[index2].id, job[index2].reachTime, job[index2].startTime, job[index2].waitTime, job[index2].runtime);
        wirtExcel(job, 1, index2);
        roundTime2 = roundTime2 + job[index2].waitTime+job[index2].needTime; //更新总周转时间
        job[index2].visit = 1;
        index2 = calculateRR(job, currentTime2); //更新当前响应比最大的job，准备下一轮循环
    }
    printf("------------------------------------------------------------------------\n");
    printf("总周转时间:%d\n", roundTime2);
    printf("平均周转时间:%.2lf\n\n", (double)roundTime2 / (double)quantity);
}
