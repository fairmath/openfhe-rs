#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"

namespace openfhe
{

class DCRTPoly final
{
    lbcrypto::DCRTPoly m_poly;
public:
    explicit DCRTPoly(lbcrypto::DCRTPoly&& poly) noexcept;
    DCRTPoly(const DCRTPoly&) = delete;
    DCRTPoly(DCRTPoly&&) = delete;
    DCRTPoly& operator=(const DCRTPoly&) = delete;
    DCRTPoly& operator=(DCRTPoly&&) = delete;
};

class DCRTPolyParams final
{
    std::shared_ptr<lbcrypto::DCRTPoly::Params> m_params;
public:
    DCRTPolyParams() = default;
    explicit DCRTPolyParams(const std::shared_ptr<lbcrypto::DCRTPoly::Params>& params);
    DCRTPolyParams(const DCRTPolyParams&) = delete;
    DCRTPolyParams(DCRTPolyParams&&) = delete;
    DCRTPolyParams& operator=(const DCRTPolyParams&) = delete;
    DCRTPolyParams& operator=(DCRTPolyParams&&) = delete;

    [[nodiscard]] std::shared_ptr<lbcrypto::DCRTPoly::Params> GetInternal() const;
};

// Generator functions
[[nodiscard]] std::unique_ptr<DCRTPolyParams> GenNullDCRTPolyParams();

} // openfhe
