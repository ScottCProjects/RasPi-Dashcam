// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void openFile( ofstream &f, string filename )
{
	f.open( filename, ios::out );
}

void closeFile( ofstream &f )
{
	f.close();
}

string filename( string prefix, int num )
{
	return prefix + string( itoa(num) ) + ".h264";
}

int main()
{
	int STRSIZE = 256;
	char str[STRSIZE];
	char c;
	
	cout << "Starting..." << endl;
	ofstream output[2];
	string fnamePrefix = "test";
	int numFiles = 4;
	int fileNum = 1;

	// Open up the first file
	openFile( output[0], filename(fnamePrefix, fileNum) );
	
	// Loop
	for( int i = 0, out = 0; i < 10; ++i )
	{
		// Set filename
		if( ++fileNum > 4 ) fileNum = 1;
		if( cin.good() )
			c = cin.get();
		while( cin.good() )
		{
			outfile.put(c);
			c = cin.get();
		}
	}

	outfile.close();
	
	cout << "Done." << endl;
	return 0;
}
