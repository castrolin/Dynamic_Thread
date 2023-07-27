#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

struct UP_STREAM_SIGNAL
{
	BYTE SendReady;
	BYTE Sending;
	BYTE Transfer;
	BYTE ControlSpare[29];

	UP_STREAM_SIGNAL()
	{
		memset(this, 0, sizeof(UP_STREAM_SIGNAL));
	}
};


struct DOWN_STREAM_SIGNAL
{
	BYTE RcvReady;
	BYTE Receving;
	BYTE Transfer;
	BYTE TFTStopReq;
	BYTE CFStopReq;
	BYTE DelayReqLevel_1;
	BYTE DelayReqLevel_2;
	BYTE DelayReqLevel_3;
	BYTE ControlSpare[24];

	DOWN_STREAM_SIGNAL()
	{
		memset(this, 0, sizeof(DOWN_STREAM_SIGNAL));
	}
};

#pragma pack(pop)	