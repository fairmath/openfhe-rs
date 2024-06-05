#include "DCRTPoly.h"

namespace openfhe
{

DCRTPoly::DCRTPoly(lbcrypto::DCRTPoly&& poly) noexcept
    : m_poly(std::move(poly))
{ }

DCRTPolyParams::DCRTPolyParams(const std::shared_ptr<lbcrypto::DCRTPoly::Params>& params)
    : m_params(params)
{ }
std::shared_ptr<lbcrypto::DCRTPoly::Params> DCRTPolyParams::GetInternal() const
{
    return m_params;
}

// Generator functions
std::unique_ptr<DCRTPolyParams> GenNullDCRTPolyParams()
{
    return std::make_unique<DCRTPolyParams>();
}

} // openfhe
