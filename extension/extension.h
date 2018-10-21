#ifndef _INCLUDE_BEN_EXT_H_
	#define _INCLUDE_BEN_EXT_H_
#include "smsdk_ext.h"
#include "CDetour/detours.h"

class CTauntExtension : public SDKExtension
{
	public:
		virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
		virtual void SDK_OnUnload();
};

#endif
