#include "SuperpoweredExample.h"
#include "SuperpoweredSimple.h"
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>

static void playerEventCallbackA(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void *value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *playerA = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        playerA->setBpm(126.0f);
        playerA->setFirstBeatMs(353);
        playerA->setPosition(playerA->firstBeatMs, false, false);
    };
}

static void playerEventCallbackB(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void *value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *playerB = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        playerB->setBpm(126.0f);
        playerB->setFirstBeatMs(353);
        playerB->setPosition(playerB->firstBeatMs, false, false);
    };
}

static void playerEventCallbackC(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void *value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *playerB = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        playerB->setBpm(126.0f);
        playerB->setFirstBeatMs(353);
        playerB->setPosition(playerB->firstBeatMs, false, false);
    };
}

static bool audioProcessing(void *clientdata, short int *audioIO, int numberOfSamples, int samplerate) {
    return ((SuperpoweredExample *)clientdata)->process(audioIO, numberOfSamples);
}

SuperpoweredExample::SuperpoweredExample(const char *path, int *params) : activeFx(0), crossValue(0.0f), volB(0.0f), volA(1.0f * headroom) {

    vol2=0.0f;
    vol1=0.0f;
    volM=0.0f;
    vol3=0.0f;
    vol4=0.0f;
    vol5=0.0f;
    vol6=0.0f;

    unsigned int samplerate = params[4], buffersize = params[5];
    stereoBuffer = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer2 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer3 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer4 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer5 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer6 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stereoBuffer7 = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);

    stemOneBuffer = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);
    stemTwoBuffer = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);

    stemTwoBuffer = (float *)memalign(16, (buffersize + 16) * sizeof(float) * 2);

    mixerA = new SuperpoweredStereoMixer();
    preMixer1 = new SuperpoweredStereoMixer();
    preMixer2 = new SuperpoweredStereoMixer();

    playerA = new SuperpoweredAdvancedAudioPlayer(&playerA , playerEventCallbackA, samplerate, 0);
    playerA->open(path, params[0], params[1]);

    playerB = new SuperpoweredAdvancedAudioPlayer(&playerB , playerEventCallbackA, samplerate, 0);
    playerB->open(path, params[2], params[3]);

    playerC = new SuperpoweredAdvancedAudioPlayer(&playerC , playerEventCallbackA, samplerate, 0);
    playerC->open(path, params[6], params[7]);

    playerD = new SuperpoweredAdvancedAudioPlayer(&playerD , playerEventCallbackA, samplerate, 0);
    playerD->open(path, params[8], params[9]);

    playerE = new SuperpoweredAdvancedAudioPlayer(&playerE , playerEventCallbackA, samplerate, 0);
    playerE->open(path, params[10], params[11]);

    playerF = new SuperpoweredAdvancedAudioPlayer(&playerF , playerEventCallbackA, samplerate, 0);
    playerF->open(path, params[12], params[13]);

    playerG = new SuperpoweredAdvancedAudioPlayer(&playerG , playerEventCallbackA, samplerate, 0);
    playerG->open(path, params[14], params[15]);

    audioSystem = new SuperpoweredAndroidAudioIO(samplerate, buffersize, false, true, audioProcessing, this, 0);
}

SuperpoweredExample::~SuperpoweredExample() {
    delete playerA;
    delete playerB;
    delete playerC;
    delete playerD;
    delete playerE;
    delete playerF;
    delete playerG;
    delete audioSystem;
    free(stereoBuffer);
    free(stereoBuffer2);
    free(stereoBuffer3);
    free(stereoBuffer4);
    free(stereoBuffer5);
    free(stereoBuffer6);
    free(stereoBuffer7);

    free(stemOneBuffer);
    free(stemTwoBuffer);
}

void SuperpoweredExample::onPlayPause(bool play) {
    if (!play) {
        playerA->pause();
        playerB->pause();
        playerC->pause();
        playerD->pause();
        playerE->pause();
        playerF->pause();
        playerG->pause();
    } else {
        playerA->play(false);
        playerB->play(false);
        playerC->play(false);
        playerD->play(false);
        playerE->play(false);
        playerF->play(false);
        playerG->play(false);
    };
}

void SuperpoweredExample::onCrossfader(int value, int stem) {

    if (stem==1){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            volM = 0.0f;
        } else if (crossValue > 0.99f) {
            volM = 1.0f * headroom;
        } else { // constant power curve
            volM = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==2){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol1 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol1 = 1.0f * headroom;
        } else { // constant power curve
            vol1 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==3){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol2 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol2 = 1.0f * headroom;
        } else { // constant power curve
            vol2 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==4){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol3 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol3 = 1.0f * headroom;
        } else { // constant power curve
            vol3 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==5){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol4 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol4 = 1.0f * headroom;
        } else { // constant power curve
            vol4 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==6){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol5 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol5 = 1.0f * headroom;
        } else { // constant power curve
            vol5 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }

    if (stem==7){
        crossValue = float(value) * 0.01f;
        if (crossValue < 0.01f) {
            vol6 = 0.0f;
        } else if (crossValue > 0.99f) {
            vol6 = 1.0f * headroom;
        } else { // constant power curve
            vol6 = cosf(M_PI_2 * (1.0f - crossValue)) * headroom;
        };
    }


}

#define MINFREQ 60.0f
#define MAXFREQ 20000.0f

static inline float floatToFrequency(float value) {
    if (value > 0.97f) return MAXFREQ;
    if (value < 0.03f) return MINFREQ;
    value = powf(10.0f, (value + ((0.4f - fabsf(value - 0.4f)) * 0.3f)) * log10f(MAXFREQ - MINFREQ)) + MINFREQ;
    return value < MAXFREQ ? value : MAXFREQ;
}

bool SuperpoweredExample::process(short int *output, unsigned int numberOfSamples) {

    bool silence = !playerA->process(stereoBuffer, false, numberOfSamples, 1.0f, 0.0f, -1);

    if (!silence){
          playerB->process(stereoBuffer2, false, numberOfSamples, 1.0f, 0.0f, -1);
          playerC->process(stereoBuffer3, false, numberOfSamples, 1.0f, 0.0f, -1);
          playerD->process(stereoBuffer4, false, numberOfSamples, 1.0f, 0.0f, -1);
          playerE->process(stereoBuffer5, false, numberOfSamples, 1.0f, 0.0f, -1);
          playerF->process(stereoBuffer6, false, numberOfSamples, 1.0f, 0.0f, -1);
          playerG->process(stereoBuffer7, false, numberOfSamples, 1.0f, 0.0f, -1);
    }



    //ADDED CODE

    if (!silence) {

        //Pre-Mixers, coverts mono to 2 Stereo buffers
        float *mixerInputs1[4] = {stereoBuffer4, stereoBuffer5, stereoBuffer6, stereoBuffer7};
        float *mixerOutputs1[2] = {stereoBuffer4, NULL};
        float arrInVol1[8] = {vol3, vol3, vol4, vol4, vol5, vol5, vol6, vol6};
        float arrOutVol1[2] = {1.0f, 1.0f};
        float mixerOutputMeter1[2] = {0.0f, 0.0f};

        preMixer1->process(mixerInputs1, mixerOutputs1, arrInVol1, arrOutVol1, NULL, mixerOutputMeter1, numberOfSamples);

/*



        float *mixerInputs2[4] = {stereoBuffer3, stemOneBuffer, NULL, NULL};
        float *mixerOutputs2[2] = {stemTwoBuffer, NULL};
        float arrInVol2[8] = {vol2, vol2, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        float arrOutVol2[2] = {1.0f, 1.0f};
        float mixerOutputMeter2[2] = {0.0f, 0.0f};

        preMixer2->process(mixerInputs2, mixerOutputs2, arrInVol2, arrOutVol2, NULL, mixerOutputMeter2, numberOfSamples);




        */

        //Master mixer
        float *mixerInputsM[4] = {stereoBuffer, stereoBuffer2, stereoBuffer3, stereoBuffer4};
        float *mixerOutputsM[2] = {stereoBuffer, NULL};
        float arrInVolM[8] = {volM, volM, vol1, vol1, vol2, vol2, 1.0f, 1.0f};
        float arrOutVolM[2] = {1.0f, 1.0f};
        float mixerOutputMeterM[2] = {0.0f, 0.0f};

        mixerA->process(mixerInputsM, mixerOutputsM, arrInVolM, arrOutVolM, NULL, mixerOutputMeterM,
                        numberOfSamples);

    }

    //


    // The stereoBuffer is ready now, let's put the finished audio into the requested buffers.
    if (!silence) SuperpoweredFloatToShortInt(stereoBuffer, output, numberOfSamples);
    return !silence;
}

extern "C" {
JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_SuperpoweredExample(JNIEnv *javaEnvironment, jobject self, jstring apkPath, jlongArray offsetAndLength);
JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_onPlayPause(JNIEnv *javaEnvironment, jobject self, jboolean play);
JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_onCrossfader(JNIEnv *javaEnvironment, jobject self, jint value, jint stem);
}

static SuperpoweredExample *example = NULL;

// Android is not passing more than 2 custom parameters, so we had to pack file offsets and lengths into an array.
JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_SuperpoweredExample(JNIEnv *javaEnvironment, jobject self, jstring apkPath, jlongArray params) {
    // Convert the input jlong array to a regular int array.
    jlong *longParams = javaEnvironment->GetLongArrayElements(params, JNI_FALSE);
    int arr[16];
    for (int n = 0; n < 16; n++) arr[n] = longParams[n];
    javaEnvironment->ReleaseLongArrayElements(params, longParams, JNI_ABORT);

    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    example = new SuperpoweredExample(path, arr);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);

}

JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_onPlayPause(JNIEnv *javaEnvironment, jobject self, jboolean play) {
    example->onPlayPause(play);
}

JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_onCrossfader(JNIEnv *javaEnvironment, jobject self, jint value, jint stem) {
    example->onCrossfader(value, stem);
}
