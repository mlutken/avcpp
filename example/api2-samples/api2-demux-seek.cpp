#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <functional>

#include "av.h"
#include "av_ffmpeg.h"
#include "av_codec.h"
#include "av_packet.h"
#include "av_videorescaler.h"
#include "av_audioresampler.h"
#include "av_utils.h"

// API2
#include "av_format.h"
#include "av_formatcontext.h"
#include "av_codec.h"
#include "av_codeccontext.h"

using namespace std;
using namespace av;

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    av::init();
    av::setFFmpegLoggingLevel(AV_LOG_DEBUG);

    string uri {argv[1]};

    error_code ec;

    FormatContext ictx;

    ictx.openInput(uri);
    ictx.findStreamInfo();

    clog << "Seekable: " << ictx.seekable() << endl;

    {
        // Seek to the 200 seconds
        ictx.seek({200, {1,1}});
        auto pkt = ictx.readPacket();
        clog << "Seek 0: [" << pkt.streamIndex() << "] pts=" << pkt.pts() << " / " << pkt.pts().seconds() << endl;
    }


    {
        // Seek to the 0 seconds
        ictx.seek({0, {1,1}});
        auto pkt = ictx.readPacket();
        clog << "Seek 0: [" << pkt.streamIndex() << "] pts=" << pkt.pts() << " / " << pkt.pts().seconds() << endl;
    }


    {
        // Seek to the 200 seconds and read to the end
        ictx.seek({200, {1,1}});
        clog << "Seek 2:\n";
        while (true) {
            auto pkt = ictx.readPacket(ec);
            if (!pkt)
                break;
            clog << "    [" << pkt.streamIndex() << "] pts=" << pkt.pts() << " / " << pkt.pts().seconds() << endl;
        }
    }

    {
        // Seek the the begin and read 100 packets
        ictx.seek({0, {1,1}});
        clog << "Seek 3:\n";
        size_t count = 100;
        while (count --> 0) {
            auto pkt = ictx.readPacket(ec);
            if (!pkt)
                break;
            clog << "    [" << pkt.streamIndex() << "] pts=" << pkt.pts() << " / " << pkt.pts().seconds() << endl;
        }
    }

}
