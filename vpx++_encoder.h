#ifndef CPPVPX_ENCODER_H
#define CPPVPX_ENCODER_H

#define VPX_CODEC_DISABLE_COMPAT 1

#include "vpx++.h"

#include <vpx/vpx_encoder.h>

namespace vpx
{

class Encoder
{
public:
	Encoder(vpx_codec_iface_t * iface, long width, long height,
			vpx_codec_flags_t flags = 0,
			vpx_img_fmt_t fmt = VPX_IMG_FMT_I420);

	~Encoder();

	void SetConfig(const vpx_codec_enc_cfg_t cfg);

	vpx_codec_enc_cfg_t GetConfig();

	Frame Encode(Planes planes, unsigned long deadline,
				vpx_enc_frame_flags_t flags = 0);

private:
	vpx_codec_iface_t * iface;
	vpx_codec_ctx_t codec;
	vpx_codec_enc_cfg_t cfg;
	vpx_image_t raw_frame;
	unsigned frame_cnt;
};

}

#endif

