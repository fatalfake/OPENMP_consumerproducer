#define _CRT_SECURE_NO_WARNINGS 


#include <omp.h>
#include <stdio.h>
#include <windows.h> 
#include <conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream> 
#include <queue>
#include  <direct.h> 
using namespace std;
#define Nr  5
int main() {

	//string *d=new string[Nr];
	/*for(int i=0;i<Nr;i++)
	{
		d[i]="";
	}*/
	//信号灯
	int empty = 5;//队列中的空闲空间大小
	int full = 0;//队列中已使用空间的大小

	int nthreads;
	int tid, i, tip;
	int first;
	omp_lock_t lockP;
	//当前生产者的数目
	int numberOfProductor = 0;
	//初始化锁
	omp_init_lock(&lockP);
	//线程总数目为4
	omp_set_num_threads(4);
	first = 1;
	queue<string> d;
	//omp_in_parallel();
	//omp_set_dynamic(20);

	printf("程序说明：\n");
	printf("偶数线程作为生产者，奇数线程作为消费者。生产者读取程序同一目录下文件名为线程对应tid的文本文档并将文本入列，消费者从队列中把文本分成单词。\n");
	printf("程序将在五秒后启动 5...\n");
	Sleep(1000);
	printf("4...\n");
	Sleep(1000);
	printf("3...\n");
	Sleep(1000);
	printf("2...\n");
	Sleep(1000);
	printf("1...\n");
	Sleep(1000);
#pragma omp parallel  shared(d,empty,full,numberOfProductor) private(tid,i,tip) firstprivate(first) 
	{
		if (first == 1)
		{
			tid = omp_get_thread_num();
			first = 0;
			nthreads = omp_get_num_threads();
			printf("线程数量： %d\n", nthreads);
			printf("线程 %d 正在启动...\n", tid);
			tip = tid % 2;
		}
		//偶数线程为生产者
		if (tip == 0)
		{   // producator
			//omp_set_lock(&lockP);
			stringstream strStream;
			strStream << tid;
			string fileName;
			string directPath;
			char   buffer[MAX_PATH];
			_getcwd(buffer, MAX_PATH);
			directPath = buffer;
			fileName = directPath + "\\" + strStream.str() + ".txt";
			//fileName=strStream.str()+".txt";
			ifstream fin(fileName);
			while (!fin.eof())
			{
				if (empty > 0)
				{


#pragma omp critical
					{
						printf("线程 %d 生产者 \n", tid);
						printf("生产者产生的数据为：");
						string str;
						getline(fin, str);
						d.push(str);
						cout << str << "\n";
						empty--;
						full++;
					}
				}
				else
				{
					Sleep(1000);
				}
			}
			//printf("线程 %d退出！\n", tid);
#pragma omp critical
			{
				numberOfProductor++;
			}
			//omp_unset_lock(&lockP);  			
		}
		else//奇数线程为消费者
		{
			//omp_set_lock(&lockP);
				  // consumator
			while (true)
			{
				if (numberOfProductor == 2 && d.empty())
				{
					break;
				}
				if (full > 0 && !d.empty())
				{
#pragma omp critical
					{
						printf("线程 %d 消费者\n", tid);
						char sentences[255];
						string str;
						if (!d.empty()) {
							str = d.front();
							d.pop();
						}
						str.copy(sentences, str.length(), 0);
						sentences[str.length() + 1] = '\0';
						char *tokenPtr = strtok(sentences, " ");
						printf("消费者分词结果：\n");
						while (tokenPtr != NULL)
						{
							cout << tokenPtr << '\t' << '\n';
							tokenPtr = strtok(NULL, " ");
						}
						full--;
						empty++;
					}


				}
				else
				{
					Sleep(100);
				}
			}

		}
		//omp_unset_lock(&lockP);  
		   //}
	}


	char end = _getch();
}


