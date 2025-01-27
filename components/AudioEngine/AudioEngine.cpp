/**
 * Audio Engine for entire game
 * reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 * for buffer properties
 */
#include "AudioEngine.h"
#include <iostream>
#include <filesystem>
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

AudioEngine::AudioEngine()
{
    // Initialize OpenAL
    device = alcOpenDevice(nullptr);
    if (!device)
    {
        throw std::runtime_error("Failed to open OpenAL device");
    }

    context = alcCreateContext(device, nullptr);
    if (!context)
    {
        alcCloseDevice(device);
        throw std::runtime_error("Failed to create OpenAL context");
    }

    if (!alcMakeContextCurrent(context))
    {
        alcDestroyContext(context);
        alcCloseDevice(device);
        throw std::runtime_error("Failed to make OpenAL context current");
    }

    /*Initialize listeners, this should theoretically
    be the main character's position on the map */
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    float orientation[6] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, orientation);

    // Set up distance model for spatial audio
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    alListenerf(AL_GAIN, 1.0f);  // Global gain/volume
}

AudioEngine::~AudioEngine()
{
    cleanup();
}

void AudioEngine::cleanup()
{
    // Stop and delete all sources and buffers
    for (auto &[name, sound] : sounds)
    {
        alDeleteSources(1, &sound.source);
        alDeleteBuffers(1, &sound.buffer);
    }
    sounds.clear();

    if (context)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
    }

    if (device)
    {
        alcCloseDevice(device);
    }
}

std::unordered_map<std::string, SoundSource>& AudioEngine::getSounds() {
    return sounds;
}



bool AudioEngine::loadSound(const std::string &name, const std::string &filePath)
{
    if (!checkFileExists(filePath))
    {
        std::cerr << "Error: Sound file not found: " << filePath << std::endl;
        return false;
    }

    // Open and read the WAV file
    drwav wav;
    if (!drwav_init_file(&wav, filePath.c_str(), nullptr))
    {
        std::cerr << "Error: Failed to open WAV file" << std::endl;
        return false;
    }

    // Read the audio data
    std::vector<int16_t> buffer(wav.totalPCMFrameCount * wav.channels);
    drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, buffer.data());

    // Create OpenAL buffer
    SoundSource sound;
    alGenBuffers(1, &sound.buffer);
    alGenSources(1, &sound.source);

    // Figure out format (mono or stereo)
    ALenum format = (wav.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    // Upload audio data to OpenAL
    alBufferData(sound.buffer, format, buffer.data(),
                 buffer.size() * sizeof(int16_t), wav.sampleRate);

    if (!checkALError("alBufferData"))
    {
        drwav_uninit(&wav);
        return false;
    }

    // Set source properties
    alSource3f(sound.source, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(sound.source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcef(sound.source, AL_PITCH, 1.0f);
    alSourcef(sound.source, AL_GAIN, 1.0f);
    alSourcei(sound.source, AL_BUFFER, sound.buffer);

    // Set distance attenuation properties
    alSourcef(sound.source, AL_REFERENCE_DISTANCE, 1.0f);   // Distance where sound begins to attenuate
    alSourcef(sound.source, AL_MAX_DISTANCE, 1000.0f);      // Distance where attenuation stops
    alSourcef(sound.source, AL_ROLLOFF_FACTOR, 1.0f);       // How quickly sound attenuates

    sound.isPlaying = false;
    this->getSounds()[name] = sound;

    drwav_uninit(&wav);
    return checkALError("loadSound");
}

bool AudioEngine::isSoundPlaying(const std::string &name)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        ALint state;
        alGetSourcei(it->second.source, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }
    return false;
}

void AudioEngine::playSound(const std::string &name, bool loop)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        //AL_LOOPING i, iv turns looping on (AL_TRUE) or off (AL_FALSE)
        alSourcei(it->second.source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        alSourcePlay(it->second.source);
        it->second.isPlaying = true;
    }
}

void AudioEngine::stopSound(const std::string &name)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        alSourceStop(it->second.source);
        it->second.isPlaying = false;
    }
}

void AudioEngine::setListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioEngine::setListenerOrientation(float atX, float atY, float atZ,
                                         float upX, float upY, float upZ)
{
    float orientation[] = {atX, atY, atZ, upX, upY, upZ};
    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioEngine::setSoundPosition(const std::string &name, float x, float y, float z)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        alSource3f(it->second.source, AL_POSITION, x, y, z);
    }
}

void AudioEngine::setSoundVolume(const std::string &name, float volume)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        alSourcef(it->second.source, AL_GAIN, volume);
    }
}

void AudioEngine::setSoundPitch(const std::string &name, float pitch)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
    {
        alSourcef(it->second.source, AL_PITCH, pitch);
    }
}

bool AudioEngine::checkALError(const std::string &operation)
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        std::cerr << "OpenAL error during " << operation << ": " << error << std::endl;
        return false;
    }
    return true;
}

bool AudioEngine::checkFileExists(const std::string &filePath)
{
    bool exists = std::filesystem::exists(filePath);
    std::cout << "Checking path: " << std::filesystem::absolute(filePath) << std::endl;
    std::cout << "File " << (exists ? "exists" : "does not exist") << std::endl;
    return exists;
}

void AudioEngine::printSoundNames() const {
    std::cout << "Currently loaded sounds:" << std::endl;
    if (sounds.empty()) {
        std::cout << "  No sounds loaded" << std::endl;
        return;
    }

    for (const auto& [name, sound] : sounds) {
        std::cout << "  - " << name
                  << (sound.isPlaying ? " (playing)" : " (stopped)")
                  << std::endl;
    }
}