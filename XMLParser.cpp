#include <XMLParser.h>
#include <tinyxml2.h>
#include <DebugUtil.h>

XMLParser::XMLParser(void)
{

}

XMLParser::~XMLParser(void)
{

}

void XMLParser::ParseVec3(vuVec3<double>* pkVec, const char *sValString)
{
	ASSERT(pkVec)
	ASSERT(sValString)

	char sCopy[256];

	strcpy(sCopy, sValString);

	char* sToken = strtok(sCopy, ",");
	(*pkVec)[0] = atof(sToken);
	sToken = strtok(NULL, ",");
	(*pkVec)[1] = atof(sToken);
	sToken = strtok(NULL, ",");
	(*pkVec)[2] = atof(sToken);
}

void XMLParser::ParseVec3(vuVec3<float>* pkVec, const char *sValString)
{
	ASSERT(pkVec)
	ASSERT(sValString)

	char sCopy[256];

	strcpy(sCopy, sValString);

	char* sToken = strtok(sCopy, ",");
	(*pkVec)[0] = (float) atof(sToken);
	sToken = strtok(NULL, ",");
	(*pkVec)[1] = (float) atof(sToken);
	sToken = strtok(NULL, ",");
	(*pkVec)[2] = (float) atof(sToken);
}

void XMLParser::ParseVec2(vuVec2<float> *pkVec, const char *sValString)
{
	ASSERT(pkVec)
	ASSERT(sValString)

	char sCopy[256];

	strcpy(sCopy, sValString);

	char* sToken = strtok(sCopy, ",");
	(*pkVec)[0] = (float) atof(sToken);
	sToken = strtok(NULL, ",");
	(*pkVec)[1] = (float) atof(sToken);
}