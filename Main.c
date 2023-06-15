 #include "FCFS.h"
#include "SJF.h"
#include "HRRN.h"
#include "SJFplus.h"
#include "job.h"

int main() {
    JOB job[MAXJOB];
    JOB job2[MAXJOB];
    JOB job3[MAXJOB];
    JOB job4[MAXJOB];
    init(job);
    init(job2);
    init(job3);
    init(job4);
    readJOBdata(job);
    for (int i = 0; i < 4; i++) {
        job2[i].id = job[i].id;
        job2[i].reachTime = job[i].reachTime;
        job2[i].needTime = job[i].needTime;
        job2[i].remainNeedTime = job[i].needTime;
        job3[i].id = job[i].id;
        job3[i].reachTime = job[i].reachTime;
        job3[i].needTime = job[i].needTime;
        job3[i].remainNeedTime = job[i].needTime;
        job4[i].id = job[i].id;
        job4[i].reachTime = job[i].reachTime;
        job4[i].needTime = job[i].needTime;
        job4[i].remainNeedTime = job[i].needTime;
    }
    showJobs(job);
    sort_reachTime(job);
    sort_reachTime(job2);
    sort_reachTime(job3);
    sort_reachTime(job4);
    FCFS(job, quantity);
    SJF(job2, quantity);
    SJFplus(job3, quantity);
    HRRN(job4, quantity);
    return 0;
}