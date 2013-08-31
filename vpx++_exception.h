#include <vpx/vpx_codec.h>

#include <exception>

namespace vpx
{

class VpxException : public std::exception
{
public:
	VpxException(vpx_codec_err_t err) noexcept
	{
		this->err = err;
	}

	const char * what() const noexcept
	{
		return vpx_codec_err_to_string(err);
	}

private:
	vpx_codec_err_t err;
};

}

