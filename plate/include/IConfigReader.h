#pragma once

#include "base0/platform.h"
#include <string>

class IConfigReader
{
public:
    IConfigReader(void){};
    virtual ~IConfigReader(void){};
    virtual void Dump()=0;

    virtual int GetValueByName(const char *apAppName, const char * apKeyName, INT64 &aiValue, const INT64 aiDefVal) = 0;

    virtual int GetValueByName(const char *apAppName, const char * apKeyName, int &aiValue, const int aiDefVal) = 0;

    virtual int GetValueByName(const char *apAppName, const char * apKeyName, WORD &aiValue, const WORD aiDefVal) = 0;

    virtual int GetValueByName(const char *apAppName, const char * apKeyName, float &afValue, const float afDefVal) = 0;

    virtual int GetValueByName(const char *apAppName, const char * apKeyName, std::string &aoVal, const char *apszDefVal) = 0;
};
