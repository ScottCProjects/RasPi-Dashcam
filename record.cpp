// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

#define NUMFILES 4
#define CHARS_PER_FILE 150
//#define NUMSTREAMS 2

void openFile( ofstream &f, string filename )
{
	cout << "Opening: " << filename << endl;
	f.open( filename, ios::out );
}

void closeFile( ofstream &f )
{
	f.close();
}

// Generate filename
string filename( string prefix, int num )
{
	return prefix + string( itoa(num) ) + ".h264";
}

int main()
{
	cout << "Starting..." << endl;
	// Setup everything
	char c;
	ofstream output[NUMSTREAMS];
	string fnamePrefix = "test";
	int numFiles = 4;
	int fileNum = 1;
	int streamNum = 0;

	// Open up the first file
	openFile( output[streamNum], filename(fnamePrefix, fileNum) );
	
	// Loop for each file output
	for( int iteration = 0; iteration < 10; ++iteration )
	{
		// Set fileNum for next file
		if( ++fileNum > NUMFILES ) fileNum = 1;
cout << "FileNum: " << fileNum << "\nOutStream: " << streamNum << endl;
		// Open next file
		openFile( output[1 - streamNum], filename(fnamePrefix, fileNum) );

		// Loop for number of characters in one file
		if( cin.good() )
			c = cin.get();
		for( int i = 0; i < CHARS_PER_FILE && cin.good(); ++i )
		{
			output[streamNum].put(c);
			c = cin.get();
		}

		// Set streamNum for next iteration
		streamNum = 1 - streamNum;
	}

	outfile.close();
	
	cout << "Done." << endl;
	return 0;
}
