#include "AudioClip.h"
#include "AudioEngine.h"
#include "AudioStream.h"
#include "../Resources.h"

namespace ZXEngine
{
	AudioClip::AudioClip(AudioStream* stream)
	{
		mAudioStream = stream;
		mAudioEngine = AudioEngine::GetInstance();
		mAudioEngine->mAudioClips.push_back(this);
	}

	AudioClip::~AudioClip()
	{
		if (mSound != nullptr)
		{
			mSound->stop();
			mSound->drop();
		}
		mAudioEngine->mAudioClips.erase(std::remove(mAudioEngine->mAudioClips.begin(), mAudioEngine->mAudioClips.end(), this), mAudioEngine->mAudioClips.end());
	}

	void AudioClip::Play2D(bool loop)
	{
		if (mSound != nullptr)
		{
			mSound->stop();
			mSound->drop();
		}
		mSound = mAudioEngine->mEngine->play2D(mAudioStream->mSoundSource, loop, false, true);
		mSound->setVolume(mVolume);
		mIs3D = false;
	}

	void AudioClip::Play3D(const Vector3& position, bool loop)
	{
		if (mSound != nullptr)
		{
			mSound->stop();
			mSound->drop();
		}
		mSound = mAudioEngine->mEngine->play3D(mAudioStream->mSoundSource, irrklang::vec3df(position.x, position.y, position.z), loop, false, true);
		mSound->setVolume(mVolume);
		mSound->setMinDistance(mMinDistance);
		mSound->setMaxDistance(mMaxDistance);
		mIs3D = true;
	}

	void AudioClip::Stop()
	{
		if (mSound == nullptr || mSound->isFinished())
			return;
		
		mSound->stop();
		mSound->drop();
		mSound = nullptr;
	}

	void AudioClip::SetPause(bool pause)
	{
		if (mSound == nullptr || mSound->isFinished())
			return;

		mSound->setIsPaused(pause);
	}

	void AudioClip::SetLoop(bool loop)
	{
		if (mSound == nullptr || mSound->isFinished())
			return;

		mSound->setIsLooped(loop);
	}

	void AudioClip::SetVolume(float volume)
	{
		mVolume = volume;

		if (mSound == nullptr || mSound->isFinished())
			return;

		mSound->setVolume(volume);
	}

	void AudioClip::SetPosition(const Vector3& position)
	{
		if (mSound == nullptr || mSound->isFinished())
			return;

		mSound->setPosition(irrklang::vec3df(position.x, position.y, position.z));
	}

	bool AudioClip::GetIs3D()
	{
		return mIs3D;
	}

	float AudioClip::GetLength()
	{
		return mAudioStream->mLength;
	}

	uint32_t AudioClip::GetLengthMS()
	{
		return mAudioStream->mLenthMS;
	}

	void AudioClip::SetMinDistance(float distance)
	{
		mMinDistance = distance;

		if (mSound)
			mSound->setMinDistance(distance);
	}

	float AudioClip::GetMinDistance()
	{
		return mMinDistance;
	}

	void AudioClip::SetMaxDistance(float distance)
	{
		mMaxDistance = distance;

		if (mSound)
			mSound->setMaxDistance(distance);
	}

	float AudioClip::GetMaxDistance()
	{
		return mMaxDistance;
	}
}