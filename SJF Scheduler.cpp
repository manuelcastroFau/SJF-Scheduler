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
	void setArrivalTime(int y);
	void readyQueuePop();
	int getTotalProcess();
	int reponseTime;
	int TurnaroundTime;
	int workTime;


private:
	queue<int> cpuBurst;
	queue<int> IO;
	queue<int> readyQueue;
	int arrivalTime;
	bool isCPUburst;
	int totalProcess;
	


};

Process::Process()
{
	arrivalTime = 0;
	isCPUburst = true;
	reponseTime = 0;

}
Process::Process(int x[], int len)
{
	arrivalTime = 0;
	isCPUburst = true;
	//int len = int(sizeof(x)) / sizeof(x[0]);
	//cout << len << endl;
	//cout << "Process started" << endl ;
	for (size_t i = 0; i < len; i++)
	{
		if (i%2==0)
		{
			cpuBurst.push(x[i]);
			//cout << "CPU: " << x[i]<<"\t";
			totalProcess++;
		}
		else
		{
			IO.push(x[i]);
			//cout << "I/O: " << x[i] << "\t";
		}
	}
	//cout <<"Process readed"<< endl<<endl;
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
	// || !cpuBurst.empty() && !IO.empty()
	int count = 0;
	while (readyQueue.empty() && count<2 )
	{
		//cout << "happen  ->";
		if (isCPUburst && !cpuBurst.empty())
		{
			readyQueue.push(cpuBurst.front());
			workTime = workTime + cpuBurst.front();
			cpuBurst.pop();
			isCPUburst = false;
			
		}
		else
		{
			if (!IO.empty())
			{
				arrivalTime = arrivalTime + IO.front();
				workTime = workTime + IO.front();
				IO.pop();
				isCPUburst = true;
			}
			
		}
		
		if (!readyQueue.empty())
		{
			//cout << readyQueue.front() << "\n";
		}
		count++;
	}
}

int Process::getArrivaltime()
{
	return arrivalTime;
}

void Process::setArrivalTime(int y)
{
	arrivalTime = y;
}

void Process::readyQueuePop()
{
	readyQueue.pop();
}

int Process::getTotalProcess()
{
	return totalProcess;
}

class SJFsched
{
public:
	SJFsched();
	SJFsched(Process [], int s);
	~SJFsched();
	void cpu();
	int cpuTotalWork;

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
	int totalProcess = 0;

	cout << "this is Start time " << actualTime << endl;
	///
	//get totatl process from all process array
	for (size_t i = 0; i < size; i++)
	{
		totalProcess += p[i].getTotalProcess()+1;
	}
	cout << "total process " << totalProcess << endl;

	
	for (size_t j = 0; j <= totalProcess; j++)
	{
		cout << "*****This is actual time " << actualTime << endl;
		cout << "LIST OF THE PROCESS ON THE READY QUEUE\n";
		cout << "Proccess\t"<< "Burst\t"<< "ArrivalTime\n";
		


		////////////////////////
		//select short Job in  the ready queue of process
		for (size_t i = 0; i < size; i++)
		{
			if (p[i].getReadyQueueP() != 0 && p[i].getArrivaltime()<=actualTime)
			{
				int currentproccessJob = p[i].getReadyQueueP();
				if (actualTime >= p[i].getArrivaltime())
				{
					if (shortJob > currentproccessJob)
					{

						shortJob = currentproccessJob;
						processNumber = i;
					}
					if (shortJob == currentproccessJob)
					{
						if (p[processNumber].getArrivaltime() > p[i].getArrivaltime())
						{
							processNumber = i;
						}

					}

				}
				cout << "Process P" << i + 1 << "\t" << currentproccessJob << " \t" << p[i].getArrivaltime() << endl;
				
			}
			else
			{
				if (p[i].getReadyQueueP()!=0)
				{
					cout << "Process P" << i + 1 << "\t" << p[i].getReadyQueueP() << "\t" <<"(" << p[i].getArrivaltime() << ") - I/O Queue\n" << endl;
				}

				
			}
			if (p[i].getReadyQueueP()==0)
			{
				p[1].TurnaroundTime = 896;
				if (p[i].TurnaroundTime == 0)
				{
					p[i].TurnaroundTime = actualTime;
				}
			}
			
		}

		
		
		
		if (shortJob== 999999999)
		{
			int firstArrivaalProcess = 99999;
			for (size_t i = 0; i < size; i++)
			{
				if (p[i].getReadyQueueP()!=0)
				{
					if (firstArrivaalProcess > p[i].getArrivaltime()) {
						firstArrivaalProcess = p[i].getArrivaltime();
						cout << "New Arrival Time is " << actualTime << endl;
					}
				}
			}
			actualTime = firstArrivaalProcess;

		}



		if (processNumber != -1 && p[processNumber].getReadyQueueP() != 0 && shortJob!= 999999999)
		{
			if (p[processNumber].reponseTime == 0 && processNumber!=7)
			{
				p[processNumber].reponseTime = actualTime;
			}

			cout << "Next Process on the CPU: " << "P" << processNumber + 1 << " -> " << shortJob << " burst" << endl;
			//p[processNumber].setArrivalTime(p[processNumber].getArrivaltime() + p[processNumber].getReadyQueueP());

			//actualTime = actualTime  +p[processNumber].getArrivaltime();
			
			cpuTotalWork = cpuTotalWork+ p[processNumber].getReadyQueueP();
			actualTime = actualTime + p[processNumber].getReadyQueueP();
			p[processNumber].setArrivalTime(actualTime);
			cout << "===========================================\n";
			cout << "Process Number: " << processNumber + 1 <<endl<< "\t Cpu: " << shortJob << endl;
			cout << "Actual Time after process p" << processNumber+1 <<" = "<< actualTime << endl;
			cout << "===========================================\n";
			
			//cout << "now arrival time will be " << p[processNumber].getArrivaltime() << endl;
			p[processNumber].readyQueuePop();
			//p[processNumber].setArrivalTime(actualTime+)

			p[processNumber].moveToReadyQueue();

			shortJob = 999999999;

		}
		else {

			//actualTime=+10;
			//int firstArrivaalProcess = 99999999999999;

			//for (size_t i = 0; i < size; i++)
			//{
			//	if (p[i].getReadyQueueP()!=0)
			//	{
			//		if (firstArrivaalProcess > p[i].getArrivaltime()) {
			//			firstArrivaalProcess = p[i].getArrivaltime();
			//		}
			//	}
			//}
		}
		//shortJob = 999999999;

		




		//////////////////////////

	}



	
	cout << "\nSJF Simulation Results\n";
	cout << "Process    " << "Reponse Time   " << "Wait time\t" << "TunrAround Time" << endl;
	int totaRT=0,totalTT=0, totalwt=0;
	for (size_t i = 0; i < size; i++)
	{
		totaRT += p[i].reponseTime;
		int temp = p[i].TurnaroundTime - p[i].workTime;
		totalwt += temp;
		totalTT += p[i].TurnaroundTime;
		cout << "P" << i+1 << "\t\t" << p[i].reponseTime <<"\t\t"<< temp <<"\t\t" << p[i].TurnaroundTime << endl;

	}
	cout << "------------------------------------------------------------------\n";
	cout << "Average" << "\t\t" << totaRT/9 << "\t\t" << totalwt/9 << "\t\t" << totalTT/9 << endl;
	
	cout << "Total  CPU  work " << cpuTotalWork << endl;
	cout << "Total  CPU % work " << cpuTotalWork/double(actualTime)*100  << endl;

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


  /*int p1data[] = { 7, 22, 6, 19};
  int p2data[] = { 14, 48, 15, 44 };
  int p3data[] = { 8, 43, 7, 41};
  int p4data[] = { 13, 37, 4, 41 };
  int p5data[] = { 6, 34, 7, 21};
  int p6data[] = { 9, 32, 4, 28 };
  int p7data[] = { 14, 46, 17, 41 };
  int p8data[] = { 4, 64, 5, 53};
  int p9data[] = { 13, 37, 8, 41 };*/


  Process p1(p1data, 17);
  Process p2(p2data, 17);
  Process p3(p3data, 17);
  Process p4(p4data, 17);
  Process p5(p5data, 19);
  Process p6(p6data, 17);
  Process p7(p7data, 15);
  Process p8(p8data, 19);
  Process p9(p9data, 17);

 /* Process p1(p1data, 4);
  Process p2(p2data, 4);
  Process p3(p3data, 4);
  Process p4(p4data, 4);
  Process p5(p5data, 4);
  Process p6(p6data, 4);
  Process p7(p7data, 4);
  Process p8(p8data, 4);
  Process p9(p9data, 4);*/

  Process p[] = { p1,p2,p3,p4,p5,p6,p7,p8,p9 };

  //p1.moveToReadyQueue();

  SJFsched sjf(p,9);
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
