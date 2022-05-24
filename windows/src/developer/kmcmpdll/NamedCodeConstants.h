#pragma once    // _S2
#ifndef _NAMEDCODECONSTANTS_H
#define _NAMEDCODECONSTANTS_H

#define MAX_ENAME	128
#define ALLOC_SIZE	256

#include "../../../../developer/kmcompx/include/kmcompx.h"
#include "../../../../developer/kmcompx/include/kmx_u16.h"

struct NCCENTRY_NEW
{
	char16_t name[MAX_ENAME+1];
	int code;
    KMX_DWORD storeIndex;
};
class NamedCodeConstants
{
private:
	NCCENTRY_NEW *entries_NEW;			// entries from &includecodes
	NCCENTRY_NEW *entries_file_NEW;		// entries from store(myconst) x
	int nEntries_NEW, nEntries_file_NEW;
	int chrindexes_NEW[128];		    // A-Z, 0-9, -, _; simple index
	
	int GetCode_IncludedCodes(const char16_t *codename);
	void AddCode_IncludedCodes(int n, const char16_t *p);
	KMX_BOOL IntLoadFile(const KMX_CHAR *filename);
public:
	NamedCodeConstants();
	~NamedCodeConstants();

	void reindex();
	void AddCode(int n, const char16_t *p, KMX_DWORD storeIndex);
	KMX_BOOL LoadFile(const char *filename);
	int GetCode(const char16_t *codename, KMX_DWORD *storeIndex);
};
#endif //_NAMEDCODECONSTANTS_H


//-----------------old ----------------------------------
/*
struct NCCENTRY
{
	wchar_t name[MAX_ENAME+1];
	int code;
    KMX_DWORD storeIndex;
};

class NamedCodeConstants
{
private:
	NCCENTRY *entries;			// entries from &includecodes
	NCCENTRY *entries_file;		// entries from store(myconst) x
	int nEntries, nEntries_file;
	int chrindexes[128];		// A-Z, 0-9, -, _; simple index

	int GetCode_IncludedCodes(const wchar_t *codename);
	void AddCode_IncludedCodes(int n, const wchar_t *p);
	KMX_BOOL IntLoadFile(const KMX_CHAR *filename);
public:
	NamedCodeConstants();
	~NamedCodeConstants();

	void reindex();
	void AddCode(int n, const wchar_t *p, KMX_DWORD storeIndex);
	KMX_BOOL LoadFile(const char *filename);
	int GetCode(const wchar_t *codename, KMX_DWORD *storeIndex);
};
*/
