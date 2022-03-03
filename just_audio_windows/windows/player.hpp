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
    AudioPlayer::AudioPlayer(std::string x) {
        id = x;
        mediaPlayer = Playback::MediaPlayer();
    }
    // ~player();
};

