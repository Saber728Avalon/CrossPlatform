#include "CPMemory.h"
#include <map>

#if defined(_USE_CP_MEMORY)




std::map<void *, CPMemInfo>& GetDetectMap()
{
	static std::map<void *, CPMemInfo> g_DetectMemMap;
	return g_DetectMemMap;
}

void DumpCPMemInfo()
{
   std::map<void *, CPMemInfo> &memMap = GetDetectMap();
	for (auto iter = memMap.begin(); iter != memMap.end(); iter++)
	{
		printf("0x%x, %d, line:%s\n", iter->first, iter->second.nSize, iter->second.strInfo.c_str());
	}
}

#endif