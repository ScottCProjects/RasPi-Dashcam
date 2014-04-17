// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int STRSIZE = 256;
	char str[STRSIZE];
	unsigned char c;

	ofstream outfile;
	outfile.open("testOut.h264", ios::out /*| ios::binary*/);
	while( cin.good() )
	{
		cin.get(str, STRSIZE);
		if( cin.good() )
			//cout.put(c);
			outfile.write(str, STRSIZE-1);
	}

	outfile.close();

	return 0;
}
