#include "vpx++_encoder.h"
#include <cstring>

#include <iostream>

using std::cout;
using std::endl;

namespace vpx
{

Encoder::Encoder(vpx_codec_iface_t * iface, long width, long height, 
			vpx_codec_flags_t flags, vpx_img_fmt_t fmt)
{
	frame_cnt = 0;

	vpx_codec_err_t err;

	err = vpx_codec_enc_config_default(iface, &cfg, 0);

	if (err)
	{
		throw(VpxException(err));
	}

	// Set bitrate according to the width and height
	cfg.rc_target_bitrate = width * height * cfg.rc_target_bitrate
					/ cfg.g_w / cfg.g_h;
	// Set width and height
	cfg.g_w = width;
	cfg.g_h = height;

	if (!vpx_img_alloc(&raw_frame, fmt, width, height, 1))
	{
		throw("Failed to allocate raw frame");
	}

	// Initialize codec
	err = vpx_codec_enc_init(&codec, iface, &cfg, flags);

	if (err)
	{
		throw(VpxException(err));
	}
}

Encoder::~Encoder()
{
	vpx_img_free(&raw_frame);

	vpx_codec_err_t err = vpx_codec_destroy(&codec);

	if (err)
	{
		throw(VpxException(err));
	}
}

void Encoder::SetConfig(const vpx_codec_enc_cfg_t cfg)
{
	this->cfg = cfg;

	vpx_codec_enc_config_set(&codec, &(this->cfg));
}

vpx_codec_enc_cfg_t Encoder::GetConfig()
{
	return cfg;
}

Frame Encoder::Encode(Planes planes,	unsigned long deadline,
				vpx_enc_frame_flags_t flags)
{
	raw_frame.planes[VPX_PLANE_Y] = &(planes[0].front());
	raw_frame.planes[VPX_PLANE_U] = &(planes[1].front());
	raw_frame.planes[VPX_PLANE_V] = &(planes[2].front());

	vpx_codec_encode(&codec, &raw_frame, frame_cnt, 1, flags, deadline);

	vpx_codec_iter_t iter = NULL;
	const vpx_codec_cx_pkt_t * pkt;

	Frame encoded_frame;
	encoded_frame.SetWidth(cfg.g_w);
	encoded_frame.SetHeight(cfg.g_h);

	while ((pkt = vpx_codec_get_cx_data(&codec, &iter)) != NULL)
	{
		if (pkt->kind == VPX_CODEC_CX_FRAME_PKT)
		{
			encoded_frame.resize(pkt->data.frame.sz);

			std::copy((char*)pkt->data.frame.buf,
				(char*)pkt->data.frame.buf + pkt->data.frame.sz,
				encoded_frame.begin());

			++frame_cnt;
			
			break;
		}
	}

	return encoded_frame;
}

}

