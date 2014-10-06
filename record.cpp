// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <wiringPi.h>

using namespace std;

#define NUMFILES 20
#define CHARS_PER_FILE 1000000
//#define NUMSTREAMS 2
#define AMP_PIN 0

void openFile( ofstream *f, string filename )
{
	cout << "Opening: " << filename << endl;
	(*f).close();
	(*f).open( filename, ios::out );
}

void closeFile( ofstream &f )
{
	f.close();
}

// Generate filename
string filename( string prefix, int num )
{
	return prefix + string( std::to_string(static_cast<long long>(num)) ) + ".h264";
}

volatile bool mainPower = true;
void powerLoss()
{
	mainPower = false;
}

int main()
{
	cout << "Starting..." << endl;
	// Setup everything
	if(wiringPiSetup() < 0)
	{
		cout << "ISSUES: WIRINGPISETUP, ITS BROKE!" << endl;
		return 1;
	}
	// Setup interrupt
	if( wiringPiISR( AMP_PIN, INT_EDGE_RISING, &powerLoss ) < 0 )
	{
		cout << "ISR CREATION BROKEN." << endl;
		return 1;
	}

	char c;
	ofstream output[2];
	string fnamePrefix = "test";
	int numFiles = 4;
	int fileNum = 1;
	int streamNum = 0;

	// Open up the first file
	openFile( &output[streamNum], filename(fnamePrefix, fileNum) );
	
	// Loop for each file output
	while( cin.good() && mainPower )
	{
		// Set fileNum for next file
		if( ++fileNum > NUMFILES ) fileNum = 1;
		cout << "FileNum: " << fileNum << "\nOutStream: " << streamNum << endl;
		// Open next file
		//thread t( openFile, &output[1 - streamNum], filename(fnamePrefix, fileNum) );
		openFile( &output[1 - streamNum], filename(fnamePrefix, fileNum) );

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

	output[0].close();
	output[1].close();
	
	cout << "Done." << endl;
	return 0;
}







