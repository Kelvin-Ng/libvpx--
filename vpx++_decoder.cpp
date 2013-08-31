#include "vpx++_decoder.h"

namespace vpx
{

Decoder::Decoder(vpx_codec_iface_t * iface, vpx_codec_flags_t flags)
{
	vpx_codec_err_t err;

	err = vpx_codec_dec_init(&codec, iface, NULL, flags);

	if (err)
	{
		throw(VpxException(err));
	}
}

Planes Decoder::Decode(Frame& encoded_frame, long deadline)
{
	vpx_codec_err_t err;

	err = vpx_codec_decode(&codec, &encoded_frame.front(),
				encoded_frame.size(), NULL, deadline);

	if (err)
	{
		throw(VpxException(err));
	}

	unsigned char * buf;
	int row_n, col_n;
	vpx_codec_iter_t iter = NULL;
	vpx_image_t * img;
	Planes decoded;
	Plane::iterator decoded_it;

	while ((img = vpx_codec_get_frame(&codec, &iter)))
	{
		for (int plane = 0; plane < 3; ++plane)
		{
			buf = img->planes[plane];
			decoded_it = decoded[plane].begin();

			if (plane)
			{
				// From sample code, don't know why
				row_n = (img->d_h + 1) / 2;
				col_n = (img->d_w + 1) / 2;
			}
			else
			{
				row_n = img->d_h;
				col_n = img->d_w;
			}

			for (int row = 0; row < row_n; ++row)
			{
				/*decoded[plane].insert(decoded_it, (char*)buf,
							(char*)buf + col_n);*/
				for (int i = 0; i < col_n; ++i)
				{
					decoded[plane].push_back(buf[i]);
				}

				buf += img->stride[plane];
				decoded_it += col_n;
			}

			decoded[plane].shrink_to_fit();
		}

		decoded.SetWidth(img->d_w);
		decoded.SetHeight(img->d_h);
	}

	return decoded;
}

}

