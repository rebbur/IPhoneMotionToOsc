#include "UserDefaults.h"

#import <Foundation/Foundation.h>

bool UserDefaults::storeString(const String& key, const String& value)
{
    NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];
    
    NSString* value_ns = [NSString stringWithUTF8String: value.toUTF8()];
    NSString* key_ns = [NSString stringWithUTF8String: key.toUTF8()];
    
    [userDefaults setObject:value_ns forKey:key_ns];
    [userDefaults synchronize];
    
    return true;
}

bool UserDefaults::loadString(const String& key, String& value)
{
    NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];

    NSString* key_ns = [NSString stringWithUTF8String: key.toUTF8()];
    NSString* value_ns = [userDefaults objectForKey:key_ns];

    if (value_ns == nil)
        return false;
    
    value = String([value_ns UTF8String]);
    return true;
}


bool UserDefaults::storeLong(const String& key, const long value)
{
    NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];
    
    NSInteger value_ns = value;
    NSString* key_ns = [NSString stringWithUTF8String: key.toUTF8()];
    
    [userDefaults setInteger:value_ns forKey:key_ns];
    [userDefaults synchronize];
    
    return true;
}

bool UserDefaults::loadLong(const String& key, long& value)
{
    NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];
    
    NSString* key_ns = [NSString stringWithUTF8String: key.toUTF8()];
    NSInteger value_ns = [userDefaults integerForKey:key_ns];
    
    value = value_ns;
    return true;
}
