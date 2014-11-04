#include <iostream>
#include <istream>
#include <fstream>
#include "Timer.h"
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;

void cp1(string input, string output)
{
	ifstream is(input.c_str());
	ofstream out(output.c_str());
	while(is.good())
	{
		char c = is.get();
		if(is.good())
			out.put(c);
	}
	is.close();
	out.close();
}

void cp2(string input, string output)
{
	ifstream is(input.c_str(),std::ifstream::binary);
	ofstream out(output.c_str(),std::ofstream::binary);
	char * buffer = new char [BUFSIZ];
	while(is.good())
	{
		is.read(buffer,1);
		if(is.good())
			out.write(buffer,1);
	}
	is.close();
	out.close();
	delete[] buffer;
}

void cp3(string input, string output)
{
	ifstream is(input.c_str(),std::ifstream::binary);
	ofstream out(output.c_str(),std::ofstream::binary);
	char * buffer = new char [BUFSIZ];
	while(is.good())
	{
		is.read(buffer,BUFSIZ);
		out.write(buffer,BUFSIZ);
	}
	is.close();
	out.close();
	delete[] buffer;
}

inline bool exists(const string& name)
{
	ifstream f(name.c_str());
	if(f.good())
	{
		f.close();
		return true;
	}
	else
	{
		f.close();
		return false;
	}
}

int main(int argc, char *argv[])
{
	string in = argv[1];
	string out = argv[2];

	//Check if input exists, else exit
	if(!exists(in))
	{
		cout << "Error: Input file does not exist." << endl;
		exit(0);
	}

	//Check if output file does not exist, and create if necessary
	if(!exists(out))
	{
		ofstream outfile(out.c_str());
	}

	if(argc == 3)
	{
		cp3(in,out);		
	}
	if(argc == 4)
	{
	//CP1
	Timer t1;
	double eTime1;
	t1.start();
	cp1(in, out);
	cout << "Method 1:" << endl;
	t1.elapsedWallclockTime(eTime1);
	cout << "Wallclock: " << eTime1 << endl;
	t1.elapsedUserTime(eTime1);
	cout << "User Time: " << eTime1 << endl;
	t1.elapsedSystemTime(eTime1);
 	cout << "System Time: " << eTime1 << endl << endl;
	remove(out.c_str());

	//CP2
	Timer t2;
	double eTime2;
	t2.start();
	cp2(in, out);
	cout << "Method 2:" << endl;
	t2.elapsedWallclockTime(eTime2);
	cout << "Wallclock: " << eTime2 << endl;
	t2.elapsedUserTime(eTime2);
	cout << "User Time: " << eTime2 << endl;
	t2.elapsedSystemTime(eTime2);
 	cout << "System Time: " << eTime2 << endl << endl;
	remove(out.c_str());

	//CP3
	Timer t3;
	double eTime3;
	t3.start();
	cp3(in, out);
	cout << "Method 3:" << endl;
	t3.elapsedWallclockTime(eTime3);
	cout << "Wallclock: " << eTime3 << endl;
	t3.elapsedUserTime(eTime3);
	cout << "User Time: " << eTime3 << endl;
	t3.elapsedSystemTime(eTime3);
 	cout << "System Time: " << eTime3 << endl << endl;
	}
	else
	{
		cout << "Error: Incorrect number of arguments." << endl;
	}

	return 0;
}
