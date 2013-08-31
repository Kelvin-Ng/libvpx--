#ifndef CPPVPX_DECODER_H
#define CPPVPX_DECODER_H

#define VPX_CODEC_DISABLE_COMPAT 1

#include "vpx++.h"
#include <vpx/vpx_decoder.h>

namespace vpx
{

class Decoder
{
public:
	Decoder(vpx_codec_iface_t * iface, vpx_codec_flags_t flags = 0);

	Planes Decode(Frame& encoded_frame, long deadline);

private:
	vpx_codec_iface_t * iface;
	vpx_codec_ctx_t codec;
};

}

#endif

