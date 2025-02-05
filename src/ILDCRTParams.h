#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/core/lattice/hal/default/ildcrtparams.h"
#include "openfhe/core/math/math-hal.h"

namespace openfhe
{

using ILDCRTParams = lbcrypto::ILDCRTParams<lbcrypto::BigInteger>;

class ILDCRTParamsWrap final
{
    std::shared_ptr<ILDCRTParams> m_params;
public:
    ILDCRTParamsWrap() = default;
    ILDCRTParamsWrap(const std::shared_ptr<ILDCRTParams>& params) noexcept;
    ILDCRTParamsWrap(const ILDCRTParamsWrap&) = delete;
    ILDCRTParamsWrap(ILDCRTParamsWrap&&) = delete;
    ILDCRTParamsWrap& operator=(const ILDCRTParamsWrap&) = delete;
    ILDCRTParamsWrap& operator=(ILDCRTParamsWrap&&) = delete;

    [[nodiscard]] const std::shared_ptr<ILDCRTParams>& GetRef() const noexcept;
};

// Generator functions
[[nodiscard]] std::unique_ptr<ILDCRTParamsWrap> GenILDCRTParamsByOrderSizeBits(
    uint32_t order, uint32_t size, uint32_t bits);

} // openfhe 