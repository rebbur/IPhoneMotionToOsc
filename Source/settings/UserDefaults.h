#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class UserDefaults
{
public:
    static bool storeString(const String& key, const String& value);
    static bool loadString(const String& key, String& value);
    
    static bool storeLong(const String& key, const long value);
    static bool loadLong(const String& key, long& value);
    
};
