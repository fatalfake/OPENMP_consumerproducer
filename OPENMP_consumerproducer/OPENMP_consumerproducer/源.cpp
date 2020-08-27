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
	//�źŵ�
	int empty = 5;//�����еĿ��пռ��С
	int full = 0;//��������ʹ�ÿռ�Ĵ�С

	int nthreads;
	int tid, i, tip;
	int first;
	omp_lock_t lockP;
	//��ǰ�����ߵ���Ŀ
	int numberOfProductor = 0;
	//��ʼ����
	omp_init_lock(&lockP);
	//�߳�����ĿΪ4
	omp_set_num_threads(4);
	first = 1;
	queue<string> d;
	//omp_in_parallel();
	//omp_set_dynamic(20);

	printf("����˵����\n");
	printf("ż���߳���Ϊ�����ߣ������߳���Ϊ�����ߡ������߶�ȡ����ͬһĿ¼���ļ���Ϊ�̶߳�Ӧtid���ı��ĵ������ı����У������ߴӶ����а��ı��ֳɵ��ʡ�\n");
	printf("��������������� 5...\n");
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
			printf("�߳������� %d\n", nthreads);
			printf("�߳� %d ��������...\n", tid);
			tip = tid % 2;
		}
		//ż���߳�Ϊ������
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
						printf("�߳� %d ������ \n", tid);
						printf("�����߲���������Ϊ��");
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
			//printf("�߳� %d�˳���\n", tid);
#pragma omp critical
			{
				numberOfProductor++;
			}
			//omp_unset_lock(&lockP);  			
		}
		else//�����߳�Ϊ������
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
						printf("�߳� %d ������\n", tid);
						char sentences[255];
						string str;
						if (!d.empty()) {
							str = d.front();
							d.pop();
						}
						str.copy(sentences, str.length(), 0);
						sentences[str.length() + 1] = '\0';
						char *tokenPtr = strtok(sentences, " ");
						printf("�����߷ִʽ����\n");
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


