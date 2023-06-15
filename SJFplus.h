#include "job.h"

int getReachTask(JOB job[], int quantity, int currentTime) {
    int minReachTime = __INT_MAX__;
    int index = -1;
    for (int i = 0; i < quantity; i++) {
        if (job[i].reached != 1 && job[i].reachTime < minReachTime && job[i].reachTime >= currentTime) {
            job[i].reached = 1;          
            minReachTime = job[i].reachTime;
            index = i;
        }
    }
    return index;
}

int getNextTask(JOB job[], int quantity, int currentTime) {
    int minRemainTime = __INT_MAX__;
    int index = -1;
    for (int i = 0; i < quantity; i++) {
        if (job[i].reachTime <= currentTime && job[i].visit == 0) {
            job[i].reached = 1;
            if (job[i].remainNeedTime < minRemainTime) {
                minRemainTime = job[i].remainNeedTime;
                index = i;
            }
        }
    }
    return index;
}


void SJFplus(JOB job[], int quantity) {
    for (int i = 0; i < quantity; i++) {
        job[i].visit = 0;
    }
    int completed = 0;
    int currentTime = job[0].reachTime;
    int runIndex = -1;
    int reachIndex = -1;
    double roundTime = 0;
    printf("可抢占式的最短作业优先调度:\n");
    printf("--------------------------------------------------------\n");
    printf("作业编号\t到达时间\t开始时间\t周转时间\n");
    printf("--------------------------------------------------------\n");

    runIndex = getNextTask(job, quantity, currentTime);
    while (completed != quantity) {
        job[runIndex].startTime = currentTime;
        /*
            作业运行...
        */
        job[runIndex].reached = 1;
        reachIndex = getReachTask(job, quantity, currentTime);

        while(1) {
            if (reachIndex != -1) {
                job[runIndex].remainNeedTime = job[runIndex].remainNeedTime - (job[reachIndex].reachTime - job[runIndex].startTime);
                currentTime += (job[reachIndex].reachTime - job[runIndex].startTime);
            }
            if (job[runIndex].remainNeedTime > job[reachIndex].needTime && reachIndex != -1) {
                printf("%-8d\t%-8d\t%-8d\t\t(被挂起)\n", job[runIndex].id, job[runIndex].reachTime, job[runIndex].startTime);
                wirtExcel(job, 4, runIndex);
                runIndex = reachIndex;
            } else {
                reachIndex = getReachTask(job, quantity, currentTime);
                if (reachIndex != -1) {
                    continue;
                }
                currentTime += job[runIndex].remainNeedTime;
                job[runIndex].visit = 1;
                completed++;
                job[runIndex].runtime = currentTime - job[runIndex].reachTime;
                roundTime += job[runIndex].runtime;
                printf("%-8d\t%-8d\t%-8d\t%-8d\n", job[runIndex].id, job[runIndex].reachTime, job[runIndex].startTime, job[runIndex].runtime);
                wirtExcel(job, 4, runIndex);
                runIndex = getNextTask(job, quantity, currentTime);
                break;
            }
            break;
        }

    }
    printf("--------------------------------------------------------\n");
    printf("平均周转时间:%.2lf\n", roundTime/(double)quantity);
}