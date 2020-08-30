#ifndef EYE_LIB_EYERAVBITSTREAMFILTER_HPP
#define EYE_LIB_EYERAVBITSTREAMFILTER_HPP

#include "YaoAV.h"

namespace Eyer {

    class EyerAVBitstreamFilterPrivate;

    enum EyerAVBitstreamFilterType
    {
        h264_mp4toannexb = 1,
        hevc_mp4toannexb = 2
    };

    class EyerAVBitstreamFilter {
    public:
        EyerAVBitstreamFilter(EyerAVBitstreamFilterType type, YaoAVStream & stream);
        ~EyerAVBitstreamFilter();

        int SendPacket(YaoAVPacket * packet);
        int ReceivePacket(YaoAVPacket * packet);

        static int QueryAllBitstreamFilter();
    private:
        EyerAVBitstreamFilterPrivate * piml = nullptr;
    };
}

#endif //EYE_LIB_EYERAVBITSTREAMFILTER_HPP
