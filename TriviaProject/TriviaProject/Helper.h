#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>


class Helper
{
public:
	/*
	* This function takes the client socket and 
	* a message and send it to him
	*/
	static void sendData(SOCKET sc, std::string message);
	
	/*
	* This function takes a client socket bytes num
	* and returns the respons of the client
	*/
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	
	/*
	* This function takes a number and padds zeros 
	* into it
	*/
	static std::string getPaddedNumber(int num, int digits);
};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif

