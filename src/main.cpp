#ifdef _UNICODE
#undef _UNICODE
#endif
#ifdef UNICODE
#undef UNICODE
#endif
#include <clipp.h>
#include <bass/bass.h>
#include <stdcpp.h>
#include <colored_cout.h>

using namespace clipp;

string filename;
int volume = 1;
bool help = false, debug_out = false;
#pragma region // license
constexpr auto license = "BSD 3-Clause License\n\
\n\
Copyright (c) 2021, sjc0910\n\
All rights reserved.\n\
\n\
Redistribution and use in source and binary forms, with or without\n\
modification, are permitted provided that the following conditions are met:\n\
\n\
1. Redistributions of source code must retain the above copyright notice, this\n\
   list of conditions and the following disclaimer.\n\
\n\
2. Redistributions in binary form must reproduce the above copyright notice,\n\
   this list of conditions and the following disclaimer in the documentation\n\
   and/or other materials provided with the distribution.\n\
\n\
3. Neither the name of the copyright holder nor the names of its\n\
   contributors may be used to endorse or promote products derived from\n\
   this software without specific prior written permission.\n\
\n\
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"\n\
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n\
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n\
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE\n\
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n\
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR\n\
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER\n\
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,\n\
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n\
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\
";
#pragma endregion // license

group args = (
    (command("help") % "get help messages" >> help,
    option("license") % "print license" >> []{
        cout << license << flush;
        exit(0);
    }) | (
        command("play") % "play sound",
        value("file", filename) % "sound file",
        (option("--volume", "-v", "--vol") & value("volume", volume) % "set sound volume (default: 1)")|(option("-m", "--mute").set(volume, 0) % "mute (the same as \"--volume 0\")"),
        option("--debug", "--dbg", "-d") % "print debug message" >> debug_out
    )
);

template<class ...Args>
void debug_msg(Args... args) {
    if (!debug_out) return;
    time_t t = time(nullptr);
    tm *time = new tm();
    localtime_s(time, &t);
    clog << clr::yellow << "[DEBUG " << setfill('0') << setw(2) << time->tm_hour << ':' << setw(2) << time->tm_min << ':' << setw(2) << time->tm_sec << setfill(' ') << "] ";
    if (sizeof...(args) == 0) cout << "Debug Message" << endl;
    (clog << ... << args) << endl << clr::reset;
    delete time;
}

string sec2str(unsigned long long sec) {
    unsigned int h = 0, m = 0;
    if (sec >= 60) m = sec / 60, sec %= 60;
    if (m >= 60) h = m / 60, m %= 60;
    stringstream buf;
    buf << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' << setw(2) << sec << setfill(' ');
    return buf.str();
}

int main(int argc, char **argv) {
    if (!parse(argc, argv, args)) {
        cout << clr::red << "Unable to resolve arguments." << endl;
        cout << clr::green << "Type \"conplay help\" for help." << flush;
    }
    else if (help) {
        cout << make_man_page(args, "conplay").prepend_section("DESCRIPTION", "\tPlay sound in console.").append_section("LICENSE", string("\tBSD-3-Clause\n\tFor further information, please type \"") + "conplay" + " help license\".");
        cout << flush;
    }
    else {
        debug_msg("Detecting file...");
        if (!directory_entry(path(filename)).exists()) {
            cerr << clr::red << "File not found: " << filename;
            goto _exit;
        }
        debug_msg("Initializing bass library...");
        if (!BASS_Init((volume == 0 ? 0 : -1), 44100, 0, nullptr, nullptr)) {
            cerr << clr::red << "Unable to initialize library!"; goto _exit;
        }
        debug_msg("Setting volume...");
        BASS_SetVolume(volume * 1. / 100);
        debug_msg("Opening file...");
        HSTREAM stream = BASS_StreamCreateFile(false, filename.c_str(), 0, 0, BASS_SAMPLE_FLOAT);
        debug_msg("Created stream successfully with value ", stream);
        unsigned int sec = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE));
        debug_msg("Playing channel...");
        BASS_ChannelPlay(stream, false);
        while (BASS_ChannelIsActive(stream)) {
            static unsigned int i = 0;
            cout << sec2str(i++) << '/' << sec2str(sec) << '\r';
            this_thread::sleep_for(seconds(1));
        }
        cout << sec2str(sec) << '/' << sec2str(sec) << endl;
        cout << "Finished!" << flush;
        if (debug_out) cout << endl;
        debug_msg("Freeing stream...");
        BASS_ChannelFree(stream);
        debug_msg("Freeing library...");
        if (!BASS_Free()) {
            cerr << clr::red << "Unable to free library!"; goto _exit;
        }
    }
_exit:
    cout << clr::reset;
    return 0;
}