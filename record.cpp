// Scott Camarena
// scprojects.wordpress.com
//
// 
//============================================================

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <wiringPi.h>

using namespace std;

#define NUMFILES 20 // Arg specified in Makefile overwrites this default
#define CHARS_PER_FILE 500000
#define NUMSTREAMS 2
#define AMP_PIN 0

#define CIN_BUFFER_SIZE 500

void openFile( ofstream &f, string filename )
{
	cout << "Opening: " << filename << endl;
	f.close();
	f.open( filename, ios::out );
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


void setupNextFileStream( int &fileNum, int &streamNum, ofstream *output, string &fnamePrefix )
{
		// Set fileNum for next file
		if( ++fileNum > NUMFILES ) fileNum = 1;
		cout << "FileNum: " << fileNum << "\nOutStream: " << streamNum << endl;
		// Open next file
		openFile( output[1 - streamNum], filename(fnamePrefix, fileNum) );
		return;
}

int main( int argc, char** argv )
{
	cout << "Starting..." << endl;
	// Setup everything
	if(wiringPiSetup() < 0)
	{
		cerr << "ERROR: WIRINGPISETUP, ITS BROKE!" << endl;
		return 1;
	}
	// Setup interrupt
	if( wiringPiISR( AMP_PIN, INT_EDGE_RISING, &powerLoss ) < 0 )
	{
		cerr << "ERROR: ISR CREATION BROKEN." << endl;
		return 1;
	}
	
	// Set up variables
	char c;
	ofstream output[2];
	int fileNum = 1;
	int streamNum = 0;
	int numFiles = NUMFILES;
	string fnamePrefix;

	char cStr[CIN_BUFFER_SIZE];

	// Take in and verify inputs
	if( argc < 2 ) // At least prefix provided
	{
		cerr << "ERROR: Invalid arguments.\n\tMust provide prefix for recording filenames." << endl;
		return 1;
	}
	fnamePrefix = argv[1];

	if( argc >= 3 ) // If 3rd arg provided, is a valid integer
	{
		int numToVerify = atoi(argv[2]); // Will return 0 if invalid
		if( numToVerify == 0 )
		{
			cerr << "ERROR: Invalid numFiles argument."
					<< "\n\tPlease provide integer value." << endl;
			return 1;
		}
		numFiles = numToVerify;
	}

	// Open up the first file
	openFile( output[streamNum], filename(fnamePrefix, fileNum) );
	
	// Loop for each file output
	while( cin.good() && mainPower )
	{
		// Get next file ready and open the stream
		//		in a new thread
		std::thread doSetup( setupNextFileStream,
				std::ref(fileNum), std::ref(streamNum),
				std::ref(output), std::ref(fnamePrefix) );
		// Detach thread and forget about it
		doSetup.detach();

		// Loop for number of characters in one file
		cin.read(cStr, CIN_BUFFER_SIZE);
		for( int i = cin.gcount(); i < CHARS_PER_FILE && cin.good();
				i += cin.gcount() )
		{
			output[streamNum].write(cStr, cin.gcount());
			cin.read(cStr, CIN_BUFFER_SIZE);
		}

		// Set streamNum for next iteration
		streamNum = 1 - streamNum;
	}

	// Tell me which condition failed
	if( !cin.good() )
		cout << "cin failed." << endl;
	if( !mainPower )
		cout << "Lost main power." << endl;
	
	// Close the output streams
	output[0].close();
	output[1].close();
	
	cout << "Done." << endl;
	return 0;
}







