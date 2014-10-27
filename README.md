RasPi-Dashcam
  Dash-mounted camera using Raspberry Pi and Pi Cam
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

TO DO:

- Add check at beginning to ensure MainPower is connected before starting.
  	Currently only listens for rising edge, not if pin is already held high.

- Decide on and revise method of error checking.
  1. Using "abort", "return 1", and "cerr" output.
  2. Exception throwing

- Verify C++11 threads don't stay running as zombies when detached.
  	As far as I can tell they don't, but I'm not familiar enough with this
	new threading to be sure.

- Use locks on variables modified in other thread.
   Ideally shouldn't need it, but it's definitely unsafe to assume
	the other thread will finish in time. If it doesn't finish in
	time though, I have problems either way. Not using file locks,
	the output files could get messed up, but using locks, the recording
	thread will pause and wait for it, therefore not recording
	constantly as it should.

- Efficiencies to improve, w/ [Effect on efficiency]:
  1. [MODERATE] cin.get() for each byte instead of by blocks
				Getting in blocks would lower the number of loops
				required to take in feed. Was using just .get() because I
				ran into issues when grabbing multiple bytes at a time.
  2. [UNKNOWN] Shell piping into program
				Currently using pipe in bash to get feed into program.
				Using another method independent of the shell may be
				more efficient.
  3. [MINIMAL] Opening and closing so many files
				Not sure of a way around this. Need to open and close
				files for each x number of bytes in order to prevent curruption
				of older video with power loss. The shorter each file, the less
				lost video with corruption. Opening and closing files so
				often takes more CPU though.
		


