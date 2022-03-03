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
            if (method_call.method_name().compare("init") == 0) {
            } else {
              result->NotImplemented();
            }
        }
    }
};

