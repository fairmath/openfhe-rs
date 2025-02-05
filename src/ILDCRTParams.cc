#include "ILDCRTParams.h"

namespace openfhe
{

ILDCRTParamsWrap::ILDCRTParamsWrap(
    const std::shared_ptr<ILDCRTParams>& params) noexcept
    : m_params(params)
{ }

const std::shared_ptr<ILDCRTParams>& ILDCRTParamsWrap::GetRef() const noexcept
{
    return m_params;
}

// Generator functions
std::unique_ptr<ILDCRTParamsWrap> GenILDCRTParamsByOrderSizeBits(
    uint32_t order, uint32_t size, uint32_t bits)
{
    return std::make_unique<ILDCRTParamsWrap>(
        std::make_shared<ILDCRTParams>(order, size, bits));
}

} // openfhe 