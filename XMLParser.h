#ifndef XML_PARSER_MODULE_H
#define XML_PARSER_MODULE_H

#include <DebugUtil.h>
#include <CharPointer.h>
#include <vuVec3.h>
#include <vuVec2.h>

class XMLParser
{

public:

	XMLParser(void);
	virtual ~XMLParser(void);
	virtual void ParseFile(const char* sFilename) = 0;
	static void ParseVec3(vuVec3<double>* pkVec, const char *sValString);
	static void ParseVec3(vuVec3<float>* pkVec, const char *sValString);
	static void ParseVec2(vuVec2<float>* pkVec, const char *sValString);

private:
	

};

#endif