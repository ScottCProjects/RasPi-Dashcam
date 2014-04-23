// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <fstream>
#include <wiringPi.h>

using namespace std;

int main()
{
	wiringPiSetup();
	int STRSIZE = 256;
	char str[STRSIZE];
	char c;
	
	cout << "Starting..." << endl;
	ofstream outfile;
	outfile.open("testOut.h264", ios::out /*| ios::binary*/);
	if( cin.good() )
		c = cin.get();
	while( cin.good() )
	{
		outfile.put(c);
		c = cin.get();
	}

	outfile.close();
	
	cout << "Done." << endl;
	return 0;
}
