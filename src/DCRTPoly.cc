#include "DCRTPoly.h"

namespace openfhe
{

DCRTPoly::DCRTPoly(lbcrypto::DCRTPoly&& poly) noexcept
    : m_poly(std::move(poly))
{ }

DCRTPolyParams::DCRTPolyParams(const std::shared_ptr<lbcrypto::DCRTPoly::Params>& params) noexcept
    : m_params(params)
{ }
const std::shared_ptr<lbcrypto::DCRTPoly::Params>& DCRTPolyParams::GetRef() const noexcept
{
    return m_params;
}

// Generator functions
std::unique_ptr<DCRTPolyParams> DCRTPolyGenNullParams()
{
    return std::make_unique<DCRTPolyParams>();
}
std::unique_ptr<DCRTPolyParams> DCRTPolyGenParamsByOrderSizeBits(
    const uint32_t order, const uint32_t size, const uint32_t bits)
{
    return std::make_unique<DCRTPolyParams>(
        std::make_shared<lbcrypto::ILDCRTParams<lbcrypto::BigInteger>>(order, size, bits));
}
} // openfhe
