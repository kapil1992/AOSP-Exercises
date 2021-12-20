#pragma once

#include "NextPacket.h"

class FFmpegPlayerBase {

public:
	/**
	* Default constructor.
	*/
	FFmpegPlayerBase();

	/**
	* Default destructor.
	*/
	~FFmpegPlayerBase();

	/**
	* @brief Use this function to setup playback.
	* 
	* @param pcMoviePath path to video file
	*
	* @return true if setup pass with no error, else return false
	*/
	bool setup(const char * pcMoviePath);

	/**
	* @brief Use this function to get next video frame.
	* 
	* @return packet which hold pointer to video frame buffer (YUV420) 
	* and variable which indicate is this last video frame or not.
	*/
	NextPacket getNextFrame();
	
	/**
	* @brief Use this function to restart video stream.
	*/
	void restartStream();

	/**
	* @brief Use this function to get video width.
	* 
	* @return video frame width
	*/
	unsigned short getWidth();

	/**
	* @brief Use this function to get video height.
	* 
	* @return video frame height
	*/
	unsigned short getHeight();

	/**
	* @brief Use this function check does video stream exist in input file.
	* 
	* @return true if video stream exist in input file, else return false
	*/
	bool isVideoPresent();

	/**
	* @brief Use this function to get video stream duration.
	* 
	* @return this value is in ms.
	*/
	unsigned long getDuration();
	
	/**
	* @brief Use this function to get video frame rate.
	* 
	* @return this value is in frame per second.
	*/
	double getFrameRate();
};