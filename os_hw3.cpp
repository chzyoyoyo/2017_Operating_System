#include <iostream>
#include <fstream>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/time.h>


using namespace std;

int *numMT = NULL; 
int *numST = NULL;
int lebound[15];
int ribound[15];
sem_t sem[15];

void* pthread(void* p)
{
	int tid = *((int*)&p);
	int parentid = (tid-1)/2;
	int pivot;
	int runidx;


	if(tid >= 0 && tid < 7)
	{
		if(tid != 0)
		{
			sem_wait(&sem[parentid]);
		}
		pivot = lebound[tid];
		runidx = pivot + 1;

		while(runidx < ribound[tid] + 1)
		{

			if(numMT[pivot] > numMT[runidx])
			{
				int temp;

				temp = numMT[runidx];
				for (int i = runidx - pivot; i > 0; i--)
				{
					/* code */
					numMT[pivot+i] = numMT[pivot+i-1];
				}
				numMT[pivot] = temp;
				pivot++;
				runidx++; 
			}

			else if (numMT[pivot] <= numMT[runidx])
			{
				runidx++;
			}

		}

		lebound[tid*2+1] = lebound[tid];
		ribound[tid*2+1] = pivot;
		lebound[2*tid+2] = pivot+1;
		ribound[2*tid+2] = ribound[tid];

	}

	else if (tid > 6 && tid < 15)
	{
		/* code */
		sem_wait(&sem[parentid]);

		for (int i = lebound[tid]; i < ribound[tid]; ++i)
		{
			/* code */
			for (int j = i+1; j < ribound[tid]+1 ; ++j)
			{
				/* code */
				if(numMT[i] > numMT[j])
				{
					int temp;
					temp = numMT[j];
					numMT[j] = numMT[i];
					numMT[i] = temp;
				}
			}
		}
	}
	sem_post(&sem[tid]);
	sem_post(&sem[tid]);
    pthread_exit((void*)0);


}

int main()
{
	char argv[200];
	int large;
	struct timeval start;
	struct timeval end;
	long sec;
	long usec;

	cin >> argv;

	ifstream fin;
	fin.open(argv);
	fin >> large;


	numMT = new int[large];
	numST = new int[large];

	for (int i = 0; i < large; ++i)
	{
		/* code */
		fin >> numST[i];
		numMT[i] = numST[i];

	}

	lebound[0] = 0;
	ribound[0] = large - 1;

	for (int i = 0; i < 15; ++i)
	{
		sem_init(&sem[i], 0, 0);
	}

	pthread_t thread[15];
    gettimeofday(&start, 0);
    for (int i = 0; i < 15; ++i)
    {
        pthread_create(&thread[i], NULL, pthread, (void*)(intptr_t)i);
    }

    for(int i=7; i<15; i++)
    {
        sem_wait(&sem[i]);
    }
	gettimeofday(&end, 0);

	sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;

    cout << "Elapsed time of MT sorting: " << (float)sec+(usec/1000000.0) << " sec\n";
    
    ofstream fout;
    fout.open("output1.txt");

	for(int i=0; i<large; i++)
	{
        fout << numMT[i] << " ";
	}

    fout.close();
	gettimeofday(&start, 0);

	for (int i = 0; i < large - 1; ++i)
	{
		/* code */
		for (int j = i+1; j < large; ++j)
		{
			/* code */
			if(numST[i] > numST[j])
			{
				int temp;
				temp = numST[j];
				numST[j] = numST[i];
				numST[i] = temp;
			}
		}
	}
	//cout << numST[9] << endl;
	gettimeofday(&end, 0);
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    cout << "Elapsed time of ST sorting: " << (float)sec+(usec/1000000.0) << " sec\n";
	ofstream foutST;
	foutST.open("output2.txt");
	for(int i=0; i<large; ++i)
        foutST << numST[i] << " ";

    fin.close();
    foutST.close();
    delete [] numMT;
    delete [] numST;
}





