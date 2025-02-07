#include "DCRTPoly.h"
#include "openfhe/src/lib.rs.h"

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

std::unique_ptr<DCRTPolyImpl> DCRTPolyGenFromDug(const ILDCRTParams& params)
{   
    std::shared_ptr<ILDCRTParams> params_ptr = std::make_shared<ILDCRTParams>(params);
    typename DCRTPolyImpl::DugType dug;
    return std::make_unique<DCRTPolyImpl>(dug, params_ptr, Format::COEFFICIENT);
}

} // openfhe
