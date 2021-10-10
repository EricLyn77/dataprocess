#pragma once
#if _MSC_VER>1000
#endif

#ifndef _XCFILESTREAM_H_
#define _XCFILESTERAM_H_

#include<string>
#include<list>
#include<vector>

using namespace std;
#include<windows.h>

#define XC_ERR_NONE 0
#define XC_ERR_INVALID_FILE_NAME (-1)

class CXCFileStream
{
public:
	CXCFileStream(void);
	~CXCFileStream(void);

	const int ReadCsvData(LPCTSTR IpszFilename, vector<list<string>>&vISrt);
	const int WriteCsvData(LPCTSTR IpaszFilename, const vector<list<string>>&vISrt);

private:
	const bool IsCsvFile(LPCTSTR IpszFilename);

};

#endif


