#include "NetworkUtils.h"

IPAddress NetworkUtils::getCurrentIPAddress()
{
	Array<IPAddress> ipAdresses;
	IPAddress::findAllAddresses (ipAdresses);
	//return first non local ipaddress
	for (int i=0; i<ipAdresses.size(); ++i)
	{
		if (ipAdresses[i] != IPAddress::local())
			return ipAdresses[i];
	}
	return IPAddress();
}
