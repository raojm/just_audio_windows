#pragma comment(lib, "windowsapp")

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Audio.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Windows.Media.Playback.h>
#include <winrt/Windows.System.h>

using flutter::EncodableMap;
using flutter::EncodableValue;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Media;

// Looks for |key| in |map|, returning the associated value if it is present, or
// a nullptr if not.
//
// The variant types are mapped with Dart types in following ways:
// std::monostate       -> null
// bool                 -> bool
// int32_t              -> int
// int64_t              -> int
// double               -> double
// std::string          -> String
// std::vector<uint8_t> -> Uint8List
// std::vector<int32_t> -> Int32List
// std::vector<int64_t> -> Int64List
// std::vector<float>   -> Float32List
// std::vector<double>  -> Float64List
// EncodableList        -> List
// EncodableMap         -> Map
const EncodableValue* ValueOrNull(const EncodableMap& map, const char* key) {
  auto it = map.find(EncodableValue(key));
  if (it == map.end()) {
    return nullptr;
  }
  return &(it->second);
}

// Converts a std::string to std::wstring
auto TO_WIDESTRING = [](std::string string) -> std::wstring {
  if (string.empty()) {
    return std::wstring();
  }
  int32_t target_length =
      ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, string.data(),
                            static_cast<int32_t>(string.length()), nullptr, 0);
  if (target_length == 0) {
    return std::wstring();
  }
  std::wstring utf16_string;
  utf16_string.resize(target_length);
  int32_t converted_length =
      ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, string.data(),
                            static_cast<int32_t>(string.length()),
                            utf16_string.data(), target_length);
  if (converted_length == 0) {
    return std::wstring();
  }
  return utf16_string;
};

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

        std::cout << "com.ryanheise.just_audio.methods." + idx << std::endl;

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
              // const auto* audioSourceData = std::get_if<flutter::EncodableMap>(ValueOrNull(*args, "audioSource"));
              // const auto* initialPosition = std::get_if<int32_t>(ValueOrNull(*args, "initialPosition"));
              // const auto* initialIndex = std::get_if<int32_t>(ValueOrNull(*args, "initialIndex"));

              // const auto mediaSource = getMediaSource(*audioSourceData);

              // mediaPlayer.SetUriSource(mediaSource.Uri());

              result->Success(flutter::EncodableMap());
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

    Core::MediaSource AudioPlayer::getMediaSource(const flutter::EncodableMap &source) const& {
      // const std::string* id = std::get_if<std::string>(ValueOrNull(*source, "id"));
      const std::string* type = std::get_if<std::string>(ValueOrNull(source, "type"));
      if (type->compare("progressive") == 0) {
        const std::string* uri = std::get_if<std::string>(ValueOrNull(source, "type"));
        return Core::MediaSource::CreateFromUri(Uri(TO_WIDESTRING(*uri)));
      } else if (type->compare("dash") == 0) {
        throw "dash audiosource type is currently not supported";
      } else if (type->compare("hsl") == 0) {
        throw "hsl audiosource type is currently not supported";
      } else if (type->compare("silence") == 0) {
        throw "silence audiosource type is currently not supported";
      } else if (type->compare("concatenating") == 0) {
        throw "concatenating audiosource type is currently not supported";
      } else if (type->compare("clipping") == 0) {
        throw "clipping audiosource type is currently not supported";
      } else if (type->compare("looping") == 0) {
        throw "looping audiosource type is currently not supported";
      } else {
        throw std::invalid_argument( "Unknown AudioSource type: " + *type );
      }
    }

}; 

