#pragma once

class NextPacket{

public:
    //! RAW video frame in YUV420 color system
	unsigned char * pucVideoBuffer;

    //! This variable is set on true if pucVideoBuffer holds last video frame, else false.
	bool bLastPacket;
	
	NextPacket(){
		pucVideoBuffer = 0;		
		bLastPacket = false;
	}
};