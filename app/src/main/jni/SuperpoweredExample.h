#ifndef Header_SuperpoweredExample
#define Header_SuperpoweredExample

#include <math.h>
#include <pthread.h>

#include "SuperpoweredExample.h"
#include "../../../../../../Superpowered/SuperpoweredAdvancedAudioPlayer.h"
#include "../../../../../../Superpowered/SuperpoweredFilter.h"
#include "../../../../../../Superpowered/SuperpoweredRoll.h"
#include "../../../../../../Superpowered/SuperpoweredFlanger.h"
#include "../../../../../../Superpowered/SuperpoweredAndroidAudioIO.h"
#include "../../../../../../Superpowered/SuperpoweredMixer.h"

#define NUM_BUFFERS 2
#define HEADROOM_DECIBEL 3.0f
static const float headroom = powf(10.0f, -HEADROOM_DECIBEL * 0.025);

class SuperpoweredExample {
public:

	SuperpoweredExample(const char *path, int *params);
	~SuperpoweredExample();

	bool process(short int *output, unsigned int numberOfSamples);
	void onPlayPause(bool play);
	void onCrossfader(int value, int stem);
	void onFxSelect(int value);
	void onFxOff();
	void onFxValue(int value);

private:
    SuperpoweredAndroidAudioIO *audioSystem;
    SuperpoweredAdvancedAudioPlayer *playerA, *playerB, *playerC, *playerD, *playerE, *playerF, *playerG;
    SuperpoweredStereoMixer *mixerA, *preMixer1, *preMixer2;
    float *stereoBuffer, *stereoBuffer2, *stereoBuffer3, *stereoBuffer4, *stereoBuffer5, *stereoBuffer6, *stereoBuffer7, *stemOneBuffer, *stemTwoBuffer;
    unsigned char activeFx;
    float crossValue, volM, volA, volB, vol1, vol2, vol3, vol4, vol5, vol6;
};

#endif
