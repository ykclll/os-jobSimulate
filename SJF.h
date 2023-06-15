#include"job.h"
#include"stdio.h"
void SJF(JOB job[], int quantity) {
    int i;
    int b = 0;
    int temp;
    int min;
	double pjzztime=0.0;
    for (i = 0; i < quantity - 1; i++) { //按作业到达系统时间进行排序，最早到达的排在最前面 
        if (job[i].reachTime > job[i + 1].reachTime) {   //把到达时间早的赋值到min
            min = job[i].reachTime;
            job[i].reachTime = job[i + 1].reachTime;
            job[i + 1].reachTime = min;

            //把到达时间早的赋值到min
            min = job[i].needTime;
            job[i].needTime = job[i + 1].needTime;
            job[i + 1].needTime = min;

            temp = job[i].id;
            job[i].id = job[i + 1].id;
            job[i + 1].id = temp;//在temp数组中排序
        }
    }
    job[0].endtime = job[0].reachTime + job[0].needTime;//结束时间=到达时间+服务时间
    job[0].runtime = job[0].needTime;//周转时间=服务时间

    for (i = 1; i < quantity; i++) {
        if (job[i].reachTime > job[0].endtime);  //作业到达系统时，第0个作业还在运行
        else b = b + 1;        //用b统计需等待作业0运行的作业个数
    }

    for (i = 1; i <= b - 1; i++) {
        if (job[i].needTime > job[i + 1].needTime) {
            min = job[i].reachTime;
            job[i].reachTime = job[i + 1].reachTime;
            job[i + 1].reachTime = min;

            min = job[i].needTime;
            job[i].needTime = job[i + 1].needTime;
            job[i + 1].needTime = min;

            temp = job[i].id;		//将第二个参数的值复制给第一个参数，返回第一个参数
            job[i].id = job[i + 1].id;
            job[i + 1].id = temp;
        }                 //按最短运行时间排序
    }

    for (i = 1; i < quantity; i++) {
        if (job[i].reachTime > job[i - 1].endtime) {     //第i个进程到达系统时，第i-1个进程已运行完毕
            job[i].endtime = job[i].reachTime + job[i].needTime;
            job[i].runtime = job[i].needTime;
        }
        else {
            job[i].endtime = job[i - 1].endtime + job[i].needTime;
            job[i].runtime = job[i].endtime - job[i].reachTime;
        }
    }

    printf("最短作业优先:\n");
    printf("------------------------------------------------------------------------\n");
	printf("作业编号\t到达时间\t运行时间\t完成时间\t周转时间\n");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < quantity; i++)
    {
		pjzztime+=job[i].runtime;
        printf("%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n",
            job[i].id, job[i].reachTime, job[i].needTime, job[i].endtime, job[i].runtime);
        wirtExcel(job, 3, i, 0);
    }
	pjzztime=pjzztime*1.0/quantity;
    printf("------------------------------------------------------------------------\n");
	printf("平均周转时间:%.2f\n\n",pjzztime);
    wirtExcel(job, 5, 0, pjzztime);
}
