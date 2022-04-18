#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#define LARGE 48800
#define DISK 80000
#define NUM_HOLE 625


using namespace std;

int main(int argc, char const *argv[])
{
	string name;
	string chch = "";
	char buf[10];
	char content[1024] = {0};
	//string content1 = content;
    struct timeval start, end;
   	gettimeofday(&start,0);


	for (int i = 0; i < NUM_HOLE * 2; ++i)
	{
		sprintf (buf, "%d", i);
		name = chch + argv[1] + "/" + buf + "agefile.txt";
		ofstream agefile;
		agefile.open(name.c_str());
		for (int j = 0; j < DISK/NUM_HOLE/2; ++j)
		{
			agefile.write(content, sizeof(content));
		}
		agefile.close();
	}

	for (int i = 0; i < NUM_HOLE * 2; i = i+2)
	{
		sprintf (buf, "%d", i);
		name =  chch + argv[1] + "/" + buf + "agefile.txt";
		unlink(name.c_str()); 
	}


	ofstream file;
	string laname;
	laname =  chch + argv[1] + "/largefile.txt";
	file.open(laname.c_str());

	for (int i = 0; i < LARGE; ++i)
	{
		file.write(content, sizeof(content));
	}
	file.close();

	for (int i = 1; i < NUM_HOLE*2; i=i+2)
	{
		sprintf (buf, "%d", i);
		name =  chch + argv[1] + "/" + buf + "agefile.txt";
		unlink(name.c_str()); 
	}

	name = "filefrag -v " + laname;
	system("sync");
    system(name.c_str());
    gettimeofday(&end ,0);
    printf("Elapsed time in : %lf seconds\n", end.tv_sec - start.tv_sec + ( end.tv_usec - start.tv_usec)/1000000.0  ) ; 


}


