#ifndef CHAR_POINTER_MODULE_H
#define CHAR_POINTER_MODULE_H

#include <cstring>
#include <cstdlib>
#include <DebugUtil.h>

class CharPointer
{   

public:
	CharPointer(const char* strName)
    {
		ASSERT(strName)

		mStr = _strdup(strName);
	}

    CharPointer( const CharPointer &that ) : mStr( 0 )
    {
		*this = that ;
	}

    CharPointer & operator = ( const CharPointer& that )
	{
		if	(this != &that)
		{
			if(mStr)
			{
				free(mStr);
			}
            
			mStr = _strdup(that.mStr);
		}
        
		return *this ;
	}

	~CharPointer()
	{
		if(mStr)
        {
			free(mStr);
        }
		
		mStr = 0 ;
	}

    const char* GetChar()								{ return mStr; }
    bool operator == (const CharPointer& that) const	{ return ! strcmp(mStr, that.mStr); }
    bool operator == (const char* sName) const			{ return ! strcmp(mStr, sName); }
	bool operator < (const CharPointer& that) const		{ return (strcmp(mStr, that.mStr) < 0); }
	bool operator < (const char* sName) const			{ return (strcmp (mStr, sName) < 0); }
    bool operator != (const CharPointer& that) const	{ return ! operator==(that); }
    bool operator != (const char* sName) const			{ return ! operator==(sName); }
	char& operator [] (unsigned int index) const		{ return mStr[index]; }

    private:

    char* mStr; 
};
#endif