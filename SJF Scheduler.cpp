// SJF Scheduler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>



using namespace std;

class Process
{
public:
	Process();
	Process(int x[], int);
	~Process();
	int getReadyQueueP();
	void moveToReadyQueue();
	int getArrivaltime();
	void readyQueuePop();



private:
	queue<int> cpuBurst;
	queue<int> IO;
	queue<int> readyQueue;
	int arrivalTime;
	bool isCPUburst;


};

Process::Process()
{
	arrivalTime = 0;
	isCPUburst = true;

}
Process::Process(int x[], int len)
{
	arrivalTime = 0;
	isCPUburst = true;
	//int len = int(sizeof(x)) / sizeof(x[0]);
	//cout << len << endl;
	cout << "Process started" << endl ;
	for (size_t i = 0; i < len; i++)
	{
		if (i%2==0)
		{
			cpuBurst.push(x[i]);
			cout << "CPU: " << x[i]<<"\t";
		}
		else
		{
			IO.push(x[i]);
			cout << "I/O: " << x[i] << "\t";
		}
	}
	cout <<"Process readed"<< endl<<endl;
	moveToReadyQueue();

}

Process::~Process()
{
}

int Process::getReadyQueueP()
{
	//to delete teh 4 later
	//readyQueue.push(4);
	if (!readyQueue.empty())
	{
		return readyQueue.front();
	}
	return 0;
	
}

void Process::moveToReadyQueue()
{
	while (readyQueue.empty())
	{
		cout << "happen  ->";
		if (isCPUburst)
		{
			readyQueue.push(cpuBurst.front());
			isCPUburst = false;
			
		}
		else
		{
			arrivalTime = arrivalTime + IO.front();
			IO.pop();
		}
		
		cout<<readyQueue.front()<< "\n";
	}
}

int Process::getArrivaltime()
{
	return arrivalTime;
}

void Process::readyQueuePop()
{
	readyQueue.pop();
}

class SJFsched
{
public:
	SJFsched();
	SJFsched(Process [], int s);
	~SJFsched();
	void cpu();

private:
	Process *p;
	int size;
	int actualTime;

};

SJFsched::SJFsched()
{
	p=0;
	size = 0;
	actualTime = 0;
}

SJFsched::SJFsched( Process x[] , int s)
{
	p = x;
	size = s;
}

SJFsched::~SJFsched()
{

}

void SJFsched::cpu()
{
	int shortJob = 999999999;
	int processNumber = -1;
	for (size_t i = 0; i < size; i++)
	{
		int currentproccessJob =p[i].getReadyQueueP();
		if (shortJob>currentproccessJob && actualTime >= p[i].getArrivaltime())
		{
			shortJob = currentproccessJob;
			processNumber = i;
		}
	}

	if (processNumber!=-1)
	{
		actualTime = +p[processNumber].getReadyQueueP();
		cout << "====================\n";
		cout << "Process Number: " << processNumber << "\t Cpu: " << shortJob<<endl;
		cout << "Actual Time: " << actualTime << endl;
		cout << "====================\n";
		
		p[processNumber].readyQueuePop();

		

	}


}



int main()
{
   cout << "Hello World!\n";
  int p1data[] = { 7, 22, 6, 19, 12, 44, 8, 21, 10, 37, 5, 24, 6, 44, 7 , 43, 8 };
  int p2data[] = { 14, 48, 15, 44, 17, 42, 22, 37, 19, 76, 14, 41, 16, 31, 17, 43, 18 };
  int p3data[] = { 8, 43, 7, 41, 6, 45, 8, 21, 9, 35, 14, 18, 5, 26, 3, 31, 6 };
  int p4data[] = { 13, 37, 4, 41, 5, 35, 12, 41, 8, 55, 15, 34, 6, 73, 5, 77, 3 };
  int p5data[] = { 6, 34, 7, 21, 5, 44, 6, 32, 7, 28, 3, 48, 11, 44, 6, 33, 3, 28, 4 };
  int p6data[] = { 9, 32, 4, 28, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 };
  int p7data[] = { 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 };
  int p8data[] = { 4, 64, 5, 53, 6, 44, 4, 73, 6, 87, 5, 66, 8, 25, 6, 33, 9, 41, 7 };
  int p9data[] = { 13, 37, 8, 41, 7, 27, 12, 29, 5, 27, 6, 18, 3, 33, 4, 62, 6 };


  Process p1(p1data, 17);
  Process p2(p2data, 17);
  Process p3(p3data, 17);
  Process p4(p4data, 17);
  Process p5(p5data, 17);
  Process p6(p6data, 17);
  Process p7(p7data, 15);
  Process p8(p8data, 19);
  Process p9(p9data, 17);

  Process p[] = { p1,p2,p3,p4,p5,p6,p7,p8,p9 };

  //p1.moveToReadyQueue();

  SJFsched sjf(p,8);
  sjf.cpu();
  


}
   
   



   //cout<<p1.getReadyQueueP();

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
