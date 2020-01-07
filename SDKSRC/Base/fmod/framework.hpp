
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#include <iostream>

#include <chrono>
#include <thread>


FMOD_RESULT result;

FMOD::System* fmodsystem = nullptr;
FMOD::ChannelGroup* channelGroup = nullptr;
FMOD_CREATESOUNDEXINFO exinfo;
bool soundIsReady = false;

// Create the sound.
FMOD::Sound* sound[16] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
FMOD::Channel* channel[16] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

bool succeededOrWarn(const std::string& message, FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cerr << message << ": " << result << " " << FMOD_ErrorString(result) << std::endl;
        return false;
    }
    return true;
}

FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
    FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
    void* commandData1, void* commandData2)
{
    std::cout << "Callback called for " << controlType << std::endl;
    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK nonblockcallback(FMOD_SOUND* sound, FMOD_RESULT result)
{
    FMOD::Sound* snd = (FMOD::Sound*)sound;

    printf("Sound loaded! (%d) %s\n", result, FMOD_ErrorString(result));

    soundIsReady = true;
    
    return FMOD_OK;
}

void FMOD_Deinit() {
    for (int i = 0; i < 16; i++) {
        if (sound[i]!=nullptr)
            sound[i]->release();
    }

    channelGroup->release();
    fmodsystem->release();
}

int FMOD_Init()
{
    // Create the main system object.
    result = FMOD::System_Create(&fmodsystem);
    if (!succeededOrWarn("FMOD: Failed to create system object", result))
        return 1;

    // Initialize FMOD.
    result = fmodsystem->init(512, FMOD_INIT_NORMAL, nullptr);
    if (!succeededOrWarn("FMOD: Failed to initialise system object", result))
        return 1;

    // Create the channel group.

    result = fmodsystem->createChannelGroup("inGameSoundEffects", &channelGroup);
    if (!succeededOrWarn("FMOD: Failed to create in-game sound effects channel group", result))
        return 1;

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.nonblockcallback = nonblockcallback;

    return 0;
}

int FMOD_Play(int SOUNDNUMBER) {
    // Play the sound.
    if (sound[SOUNDNUMBER]!=nullptr) 
    result = fmodsystem->playSound(sound[SOUNDNUMBER], nullptr, false, &channel[SOUNDNUMBER]);


    // Assign the channel to the group.
    result = channel[SOUNDNUMBER]->setChannelGroup(channelGroup);
    if (!succeededOrWarn("FMOD: Failed to set channel group on", result))
        return 1;

    // Set a callback on the channel.
    // This works.
    channel[SOUNDNUMBER]->setCallback(&channelGroupCallback);
    if (!succeededOrWarn("FMOD: Failed to set callback for sound", result))
        return 1;

    return SOUNDNUMBER;
}

int FMOD_Set(int SOUNDNUMBER, char* sndfile)
{
    //https://documentation.help/FMOD-API/nonblocking.html
    fmodsystem->createSound(sndfile, FMOD_NONBLOCKING, &exinfo, &sound[SOUNDNUMBER]);
    if (!succeededOrWarn("FMOD: Failed to create stream", result))
        return 1;
        
    if (!succeededOrWarn("FMOD: Failed to play sound", result))
        return 1;
    
    

    //bool isPlaying = false;
    //do {
    //    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //    channel[SOUNDNUMBER]->isPlaying(&isPlaying);

    //    
    //} while (isPlaying);


    // Clean up.
    
    return 0;
}