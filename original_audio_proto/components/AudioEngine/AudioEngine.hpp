/**
 * Audio Engine for entire game
 * reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 * for buffer properties
 *
 * working dir for sound files should be the parent Audio folder
 */
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

struct SoundSource
{
    ALuint source;
    ALuint buffer;
    bool isPlaying;
};

class AudioEngine
{
private:
    ALCdevice *device;
    ALCcontext *context;

    /**
     * Map of all sounds currently active
     *
     * can pull a file by it's name via:
     * auto it = sounds.find(name);
        if (it != sounds.end()) {
            // code code code!!!
        }
     */
    std::unordered_map<std::string, SoundSource> sounds;
    bool checkALError(const std::string &operation);
    void cleanup();
public:
    AudioEngine();
    ~AudioEngine();
    static bool checkFileExists(const std::string &filePath);
    bool isSoundPlaying(const std::string &name);
    bool loadSound(const std::string &name, const std::string &filePath);
    void playSound(const std::string &name, bool loop = false);
    void stopSound(const std::string &name);

    /**
     * @param x
     * @param y
     * @param z
     * @return none
     * set listener for player
     * theoretically everything in this game should revolve around the player
     * so should always be set to 0,0,0
     */
    void setListenerPosition(float x, float y, float z);

    /**
     * set listener orientation
     * look at page 11 in the book
     *
     * @param atX
     * @param atY
     * @param atZ
     * @param upX
     * @param upY
     * @param upZ
     */
    void setListenerOrientation(float atX, float atY, float atZ,
                                float upX, float upY, float upZ);

    /**
     * set sound position
     * @param name name of sound (unique)
     * @param x
     * @param y
     * @param z
     */
    void setSoundPosition(const std::string &name, float x, float y, float z);

    /**
     * Set sound volume
     * @param name name of sound (unique)
     * @param volume
     */
    void setSoundVolume(const std::string &name, float volume);
    /**
     * set pitch of audio
     * @param name name of sound (unique)
     * @param pitch Range: [0.5-2.0] Default: 1.0
     *
     */
    void setSoundPitch(const std::string &name, float pitch);
    /**
     * get a reference to the original sound map
     * @return
     */
    std::unordered_map<std::string, SoundSource>& getSounds();

    /**
     * print names of all sounds in the unordered_map
     */
    void printSoundNames() const;
};