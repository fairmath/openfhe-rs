#include "EncodingParams.h"

#include "openfhe/pke/encoding/encodingparams.h"

namespace openfhe
{

EncodingParams::EncodingParams(const std::shared_ptr<EncodingParamsImpl>& encodingParams)
    : m_encodingParams(encodingParams)
{ }

} // openfhe
