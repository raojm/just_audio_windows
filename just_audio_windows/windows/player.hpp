#pragma comment(lib, "windowsapp")

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <winrt/Windows.Media.Audio.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Windows.Media.Playback.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Media;

class AudioPlayer
{
private:
    /* data */
public:
    std::string id;
    Playback::MediaPlayer mediaPlayer;
    AudioPlayer::AudioPlayer(std::string idx, flutter::BinaryMessenger* messenger) {
        id = idx;
        mediaPlayer = Playback::MediaPlayer();

        auto channel =
          std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            messenger, "com.ryanheise.just_audio.methods." + idx,
            &flutter::StandardMethodCodec::GetInstance());

        channel->SetMethodCallHandler(
          [player = this](const auto &call, auto result) {
            player->HandleMethodCall(call, std::move(result));
          });
    }
    AudioPlayer::~AudioPlayer() {
        // mediaPlayer.Close();
    }

    void AudioPlayer::HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
        const auto* args =std::get_if<flutter::EncodableMap>(method_call.arguments());
        if (args) {
            if (method_call.method_name().compare("load") == 0) {
            } else if (method_call.method_name().compare("play") == 0) {
              mediaPlayer.Play();
              result->Success();
            } else if (method_call.method_name().compare("pause") == 0) {
              mediaPlayer.Pause();
              result->Success();
            } else if (method_call.method_name().compare("setVolume") == 0) {
              const auto* volume = std::get_if<double>(ValueOrNull(*args, "volume"));
              if (!volume) {
                return result->Error("volume_error", "volume argument missing");
              }
              float volumeFloat = (float) *volume;
              mediaPlayer.Volume(volumeFloat);
              result->Success();
            } else if (method_call.method_name().compare("setSpeed") == 0) {
              const auto* speed = std::get_if<double>(ValueOrNull(*args, "speed"));
              if (!speed) {
                return result->Error("speed_error", "speed argument missing");
              }
              float speedFloat = (float) *speed;
              mediaPlayer.PlaybackRate(speedFloat);
              result->Success();
            } else if (method_call.method_name().compare("setPitch") == 0) {
              const auto* pitch = std::get_if<double>(ValueOrNull(*args, "pitch"));
              if (!pitch) {
                return result->Error("pitch_error", "pitch argument missing");
              }
              float pitchFloat = (float) *pitch;
              mediaPlayer.AudioBalance(pitchFloat);
              result->Success();
            } else if (method_call.method_name().compare("setSkipSilence") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setLoopMode") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setShuffleMode") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setShuffleOrder") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setAutomaticallyWaitsToMinimizeStalling") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setCanUseNetworkResourcesForLiveStreamingWhilePaused") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setPreferredPeakBitRate") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("seek") == 0) {
              const auto* position = std::get_if<int32_t>(ValueOrNull(*args, "position"));
              if (position) {
                mediaPlayer.Position(TimeSpan(std::chrono::milliseconds(*position)));
              }
              result->Success();
            } else if (method_call.method_name().compare("concatenatingInsertAll") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("concatenatingRemoveRange") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("concatenatingMove") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("setAndroidAudioAttributes") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("audioEffectSetEnabled") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("androidLoudnessEnhancerSetTargetGain") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("androidEqualizerGetParameters") == 0) {
              result->Success();
            } else if (method_call.method_name().compare("androidEqualizerBandSetGain") == 0) {
              result->Success();
            } else {
              result->NotImplemented();
            }
        }
    }
};

