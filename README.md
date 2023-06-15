### 介绍
C语言模拟实现作业调度算法，包括先来先服务(FCFS)、最短作业优先(SJF)、高响应比优先(HRRN)、最短剩余时间优先(SRTF)

### 输出格式
每种算法打印一张表，按调度顺序排序，并且打印:
- 作业编号
- 到达时间
- 开始时间
- 周转时间  

并在表后输出*平均周转时间*   
同时在当前目录下生成一个csv文件，可用Excel打开  
### 使用说明  
运行Main.c文件，根据提示输入txt文件名，系统可自动计算  
txt文件格式: 每行代表一个作业，分别读入作业编号、到达时间、作业长度
### 任务分工
job.h:ykc wx    (done)  
HRRN.h:ykc     (done)  
FCFS.h:wx (done)  
SJF.h:qjt (done)  
Main.c:ykc (done)  
SJPplus.h:ykc qjt wx (done)
