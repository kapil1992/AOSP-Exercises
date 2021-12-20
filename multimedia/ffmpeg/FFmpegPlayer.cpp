/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_NDEBUG 0
#define LOG_TAG "FFmpegPlayer"
 
#include <utils/Log.h>

#include "FFmpegPlayer.h"
#include "SoftwareRenderer.h"
#include "AwesomePlayer.h"
#include "FFmpegPlayerBase.h"

#include <media/Metadata.h>
#include <media/stagefright/MediaExtractor.h>
#include <gui/ISurfaceTexture.h>
#include <gui/SurfaceTextureClient.h>
#include <media/stagefright/MetaData.h>
#include <media/Metadata.h>
#include <media/stagefright/MediaExtractor.h>
#include <hardware/gralloc.h>

namespace android {

//! Maximum buffer size for one video frame in YUV420 colour system
#define __MAX_BUFFER_SIZE__		1920 * 1080 * 2

//! Buffer for one video frame
unsigned char pucBuffer[__MAX_BUFFER_SIZE__];

//! Surface which will be used for video frame rendering in surface flinger
sp<ANativeWindow> mySurfaceTexture;

//! Instance of ffmpeg wrapper
FFmpegPlayerBase * ffmpegPlayerBase;

//! Thread which will be used decoding and rendering video frames
void * decodingThread(void * param);

//! Frame counter
unsigned int uiFrameCounter;

//! Helper variables to get know when playback in running and when is paused.
bool bPlaying, bPause;

FFmpegPlayer::FFmpegPlayer(): mPlayer(new AwesomePlayer) {
    ALOGV("[FFmpegPlayer constructor]");
	
	bPlaying = false;
	bPause = false;
	uiFrameCounter = 0;

	ffmpegPlayerBase = new FFmpegPlayerBase();

    mPlayer->setListener(this);
}

FFmpegPlayer::~FFmpegPlayer() {
    ALOGV("[~FFmpegPlayer]");
    reset();

    if(ffmpegPlayerBase != NULL){
		delete ffmpegPlayerBase;
		ffmpegPlayerBase = NULL;
	}

    delete mPlayer;
    mPlayer = NULL;
}

status_t FFmpegPlayer::initCheck() {
    ALOGV("[initCheck]");
    return OK;
}

status_t FFmpegPlayer::setUID(uid_t uid) {
    ALOGV("[setUID] [%u]\n", uid);
    mPlayer->setUID(uid);
    return OK;
}

status_t FFmpegPlayer::setDataSource(
        const char *url, const KeyedVector<String8, String8> *headers) {
    ALOGE("[setDataSource][this function shouldn't be called in current example]");
	return OK;
}

// Warning: The filedescriptor passed into this method will only be valid until
// the method returns, if you want to keep it, dup it!
status_t FFmpegPlayer::setDataSource(int fd, int64_t offset, int64_t length) {
    ALOGV("[setDataSource][redirect to ffmpeg setup]");
    
    char path[512] = { 0 };
    char* realPath = NULL;

    sprintf(path, "/proc/%d/fd/%d", getpid(), fd);

    if (path[0] != '\0') {
        printf("fd path is %s\n", path);
        realPath = realpath(path, NULL);
        if (realPath != NULL) {
            ALOGI("get full path from fd %s\n", realPath);
        }
    }
    
    //! TODO, call setup function here and check return value.
    if (!ffmpegPlayerBase->setup(realPath)) 
	ALOGE("Failed to do FFMpeg setup\n");
    
    free(realPath);    
	return OK;
}

status_t FFmpegPlayer::setDataSource(const sp<IStreamSource> &source) {
    ALOGE("[setDataSource][this function shouldn't be called in current example]");
    return OK;
}

status_t FFmpegPlayer::setVideoSurfaceTexture(
        const sp<ISurfaceTexture> &surfaceTexture) {
    ALOGV("[setVideoSurfaceTexture]");
    // TODO, create and save new SurfaceTextureClient
    mySurfaceTexture = new SurfaceTextureClient(surfaceTexture);
    mPlayer->setSurfaceTexture(surfaceTexture);
    return OK;
}

status_t FFmpegPlayer::prepare() {
    ALOGV("[prepare]");
    //! We are using here prepare function from Awesome Player.
    //! This can be bypassed in future.
    return mPlayer->prepare();
}

status_t FFmpegPlayer::prepareAsync() {
    ALOGV("[prepareAsync]");
    //! We are using here prepare function from Awesome Player.
    //! This can be bypassed in future by just calling callback function.
    return mPlayer->prepareAsync();
}

status_t FFmpegPlayer::start() {
    ALOGV("[start]");
	if(bPause == false){
		uiFrameCounter = 0;
		bPlaying = true;
		
		//! Create and start thread
                ALOGD("Starting Decoding thread\n");
		pthread_t decodingThread_thread; 
		pthread_create(&decodingThread_thread, 0, decodingThread, 0);
	}
	bPause = false;
   	return OK;
}

status_t FFmpegPlayer::stop() {
    ALOGV("[stop]");
    //! TODO, stop playback
    bPlaying = false;
	return OK;
}

status_t FFmpegPlayer::pause() {
    ALOGV("[pause]");
	//! TODO, pause playback
    bPause = true;
    bPlaying = false;
    return OK;
}

bool FFmpegPlayer::isPlaying() {
    ALOGV("[isPlaying]");
    return bPlaying && !bPause;	
}

status_t FFmpegPlayer::seekTo(int msec) {
	msec = msec * 1000;
    ALOGV("[seekTo][%.2f msec]", msec);
	return OK;
}

status_t FFmpegPlayer::getCurrentPosition(int *msec) {
	*msec = uiFrameCounter / ffmpegPlayerBase->getFrameRate() * 1000;
	ALOGV("[getCurrentPosition][%d]", *msec);
    return OK;
}

status_t FFmpegPlayer::getDuration(int *msec) {    
    *msec = ffmpegPlayerBase->getDuration();
    ALOGV("[getDuration][%d msec]", *msec);
    return OK;
}

status_t FFmpegPlayer::reset() {
    ALOGV("[reset]");
	ffmpegPlayerBase->restartStream();
    return OK;
}

status_t FFmpegPlayer::setLooping(int loop) {
    ALOGV("[setLooping]");
    //! This is probably dead code and can be bypassed in future.
    return mPlayer->setLooping(loop);
}

player_type FFmpegPlayer::playerType() {
    ALOGV("[playerType]");
    return FFMPEG_PLAYER;
}

status_t FFmpegPlayer::invoke(const Parcel &request, Parcel *reply) {
    ALOGV("[invoke]");
	return OK;
}

void FFmpegPlayer::setAudioSink(const sp<AudioSink> &audioSink) {
    ALOGV("[setAudioSink]");
    MediaPlayerInterface::setAudioSink(audioSink);
    mPlayer->setAudioSink(audioSink);    
}

status_t FFmpegPlayer::setParameter(int key, const Parcel &request) {
    ALOGV("[setParameter][key=%d)", key);
	return OK;
}

status_t FFmpegPlayer::getParameter(int key, Parcel *reply) {
    ALOGV("[getParameter]");
	return OK;
}

status_t FFmpegPlayer::getMetadata(
        const media::Metadata::Filter& ids, Parcel *records) {
    ALOGD("[getMetadata]");
    using media::Metadata;

    uint32_t flags = mPlayer->flags();

    Metadata metadata(records);

    metadata.appendBool(
            Metadata::kPauseAvailable,
            flags & MediaExtractor::CAN_PAUSE);

    metadata.appendBool(
            Metadata::kSeekBackwardAvailable,
            flags & MediaExtractor::CAN_SEEK_BACKWARD);

    metadata.appendBool(
            Metadata::kSeekForwardAvailable,
            flags & MediaExtractor::CAN_SEEK_FORWARD);

    metadata.appendBool(
            Metadata::kSeekAvailable,
            flags & MediaExtractor::CAN_SEEK);

    return OK;
}

status_t FFmpegPlayer::dump(int fd, const Vector<String16> &args) const {
    ALOGV("[dump]");
	return OK;
}

//! TODO, implement here decoding thread
void * decodingThread(void * param){
       unsigned int uiHeight = ffmpegPlayerBase->getHeight(); 
       unsigned int uiWidth  = ffmpegPlayerBase->getWidth(); 
 
       ALOGV("[decodingThread][width %d]", uiWidth); 
       ALOGV("[decodingThread][height %d]", uiHeight); 
 
       sp<MetaData> meta = new MetaData; 
       meta->setInt32(kKeyWidth, uiWidth); 
       meta->setInt32(kKeyHeight, uiHeight); 
       meta->setInt32(kKeyColorFormat, OMX_COLOR_FormatYUV420Planar); 
       SoftwareRenderer sr(mySurfaceTexture, meta); 
 
       NextPacket packet; 
  
       while(bPlaying) { 
            if(bPause == true){ 
               usleep(500 * 1000); 
               continue; 
            } 
            packet = ffmpegPlayerBase->getNextFrame(); 
            if(packet.bLastPacket == true){ 
               bPlaying = false; 
               break; 
            } 
            if(pucBuffer == NULL || packet.pucVideoBuffer == NULL){ 
               ALOGE("[decodingThread][no memory]"); 
               continue; 
            } 
            uiFrameCounter ++; 
            memcpy(pucBuffer, packet.pucVideoBuffer, uiWidth * uiHeight * 1.5); 
            sr.render(pucBuffer, uiWidth * uiHeight * 1.5, NULL); 
       } 
 
       pthread_exit(0); 
       return NULL;	
}

}  // namespace android
