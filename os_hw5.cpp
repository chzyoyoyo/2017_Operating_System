#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
//#include <list>


using namespace std;




int main(int argc, char const *argv[])
{
	/* code */
	FILE *file = fopen("trace.txt", "r");
	unsigned int cpuad;
	vector<unsigned int> cpuvec;

	list<unsigned int> frames;
 //    list<unsigned int>::iterator deiter;

    map<unsigned int, list<unsigned int>::iterator> cpumap;


	while(fscanf(file, " %*c %X,%*d", &cpuad) != EOF)
    {
    	cpuad /= 4096;
    	cpuvec.push_back(cpuad);

    }


    for (int i = 0; i < 8; ++i)
    {
    	/* code */
    	unsigned int hitcount = 0;
    	unsigned int misscount = 0;
    	int framesize = 32;
    	int cpuflag;

    	if (i < 4)
    	{
    		cpuflag = 0;
    		if (i == 0)
    		{
    			printf("%s---\n", "FIFO");
    			printf("size\tmiss\thit\t\tpage fault ratio\n");
    		}

	    	for (int num = 0; num <= i; ++num)
	    	{
	    		framesize *= 2;
	    	}
    	}
    	else 
    	{
    		cpuflag = 1;
    		if (i == 4)
    		{
    			printf("%s---\n", "LRU");
    			printf("size\tmiss\thit\t\tpage fault ratio\n");
    		}
	    	for (int num = 4; num <= i; ++num)
	    	{
	    		framesize *= 2;
	    	}
    	}
    	for (int now = 0; now < cpuvec.size(); now++)
    	{
    		
    		map<unsigned int, list<unsigned int>::iterator>::iterator iter;
    		
    		iter = cpumap.find(cpuvec[now]);
    		if(iter != cpumap.end())
    		{
    			if (cpuflag == 1)
    			{   			
					frames.erase(iter -> second);
					frames.push_back(cpuvec[now]);
					cpumap.erase(iter);
					cpumap.insert(pair<unsigned int, list<unsigned int>::iterator>(cpuvec[now], --frames.end()));
    			}

    			hitcount++;
    		}

    		else
    		{
    			if (frames.size() >= framesize)
    			{
    				
    				cpumap.erase(frames.front());
    				frames.pop_front();

    			}

    			frames.push_back(cpuvec[now]);

    			cpumap.insert(pair<unsigned int, list<unsigned int>::iterator>(cpuvec[now], --frames.end()));
    			misscount++;

    		}
    	}

    	cpumap.clear();
    	frames.clear();



    	printf("%d\t%d\t%d\t%.9f\n", framesize, misscount, hitcount, misscount/(double)(misscount+hitcount));
    }
}




