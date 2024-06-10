#include "EncodingParams.h"

#include "openfhe/pke/encoding/encodingparams.h"

namespace openfhe
{

EncodingParams::EncodingParams(const std::shared_ptr<EncodingParamsImpl>& encodingParams) noexcept
    : m_encodingParams(encodingParams)
{ }
const std::shared_ptr<EncodingParamsImpl>& EncodingParams::GetRef() const noexcept
{
    return m_encodingParams;
}

} // openfhe
