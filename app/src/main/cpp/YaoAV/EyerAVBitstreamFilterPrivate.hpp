
#ifndef EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
#define EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVBitstreamFilterPrivate {
    public:
        AVBSFContext * ctx = nullptr;
    };
}

#endif //EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
