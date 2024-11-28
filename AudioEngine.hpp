#pragma once

#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <string>
#include <unordered_map>
#include <vector>

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();
    static void printWorkingDirectory();
    static bool checkFileExists(const std::string &filePath);

    // Sound management
    bool loadSound(const std::string &name, const std::string &filePath);
    void playSound(const std::string &name, bool loop = false);
    void stopSound(const std::string &name);

    // 3D audio positioning
    void setListenerPosition(float x, float y, float z);
    void setListenerOrientation(float atX, float atY, float atZ,
                                float upX, float upY, float upZ);
    void setSoundPosition(const std::string &name, float x, float y, float z);

    // Sound properties
    void setSoundVolume(const std::string &name, float volume);
    void setSoundPitch(const std::string &name, float pitch);

private:
    ALCdevice *device;
    ALCcontext *context;

    struct SoundSource
    {
        ALuint source;
        ALuint buffer;
        bool isPlaying;
    };

    std::unordered_map<std::string, SoundSource> sounds;

    bool checkALError(const std::string &operation);
    void cleanup();
};