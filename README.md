RasPi-Dashcam
Dash-mounted Camera using Raspberry Pi and Pi Cam
=============

INSTRUCTIONS:

Compile record.cpp with:
	$ make

Run with:
	$ make exec

================================================

DEPENDENCIES:

- "WiringPi" Library must be installed. (www.WiringPi.com)
- "g++-4.8" compiler is required when using Raspbian image.
		This is for use of C++11 threading functionality that is
		not yet implemented on the gcc (version 4.6.3) that is
		the default gcc on Raspbian image.

================================================

REVISION HISTORY:

v0.2.2 - 2/1/2015
		+ Organized project folder structure.
		* Discovered issues #003 and #004.

v0.2.1 - 1/31/2015
		* Fixed Issue #002: Multiple zero length output files.
		* (Hopefully) Fixed Issue #001: Video tearing.
		+ concatAll script now finds correct file to start with (zero
			length) on its own, instead of needing it to be passed in.

v0.2 - 10/26/2014
		* Re-implemented I/O using "istream.read" with a buffer instead of ".get" without
					Previously just grabbed characters one at a time with "get()" with no buffer.
					This is obviously slow. Had attempted to use "get" WITH a buffer, but ran
					into issues. Discovered that it was appending the null terminator to each
					segment, and then adding that to the output. "read" doesn't append the
					null. No mo problems! Now only uses 30% CPU rather than 100%!

		* Expanded Makefile functionality
		* Modified helper shell scripts to take parameters
		+ Added C++11 threading for opening files
		

v0.1 - 4/23/2014: "Woo it works!"
		+ Basic loop video recording implemented
		+ Includes helper shell scripts
		+ GPIO usage for testing for main or backup power



================================================
ISSUE LOG
================================================

[003] - File opening and closing is taking too long. CIN buffer is likely
	overflowing just as it was before implementing threading. Need to optimize
	threading, or use more than the two IO streams used now.

[004] - If not all NUMFILES number of video files have been created, concatAll
	fails to find the correct number to start with.


RESOLVED:

[001] - Fix tearing on video. Only seems to be caused by my program,
  	does not happen with direct output of same video. Seem to be losing
	just a few bytes every few seconds. Verified bytes in first h264 file
	are the same in both, but bytes in second output file differ.
	Trying different raspivid args to resolve, such as bitrate and
	framerate changes.
	RESOLUTION:
		Seems to have been solved along with Issue #002. Looks like lack of
		thread synchronization was probably causing the some of the output files
		to keep some old data when they weren't opening quick enough before
		the main thread attempted to write to it.

[002] - Multiple output files are being left empty, 0 bytes in size.
  	Might have to do with the loop conditions for the output to each
	file. Perhaps the "cin.gcount()" that I'm using is not updating as
	quickly as I need it to.
	Or may be that the thread opening the next file is not completing
	fast enough. Should keep synchronized instead of detaching.
	RESOLUTION:
		It was a thread synchronization issue. I was detaching the thread
		that opens up the next file stream for writing. Apparently this
		set up was not completing quick enough. Removing the detach and
		instead waiting with a join at the end of the loop seems to have
		resolved this.



================================================
TO DO
================================================

- Make NUMFILES and CHARS_PER_FILE to be generated based on time parameters
  	Such as "RecordTime = 20 minutes" (total between all files) and "VideoFileSize = 2 seconds"

- Add check at beginning to ensure MainPower is connected before starting.
  	Currently only listens for rising edge, not if pin is already held high.

- Decide on and revise method of error checking.
  1. Using "abort", "return 1", and "cerr" output.
  2. Exception throwing

- Revise README structure to use proper markdown formatting. I'm aware
  	that I'm not using it properly, just doing my own thing until I have
	time to research proper usage.

- Use locks on variables modified in other thread.
   Ideally shouldn't need it, but it's definitely unsafe to assume
	the other thread will finish in time. If it doesn't finish in
	time though, I have problems either way. Not using file locks,
	the output files could get messed up, but using locks, the recording
	thread will pause and wait for it, therefore not recording
	constantly as it should.

- Efficiencies to improve, w/ [Effect on efficiency]:
  1. [UNKNOWN] Shell piping into program
				Currently using pipe in bash to get feed into program.
				Using another method independent of the shell may be
				more efficient. I could be wrong on this, piping may
				not use the shell at all if it is just rerouting I/O
				and forgetting about it.
  2. [MINIMAL] Opening and closing so many files
				Not sure of a way around this. Need to open and close
				files for each x number of bytes in order to prevent curruption
				of older video with power loss. The shorter each file, the less
				lost video with corruption. Opening and closing files so
				often takes more CPU though.
		


