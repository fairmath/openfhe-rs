#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"

namespace lbcrypto
{

template <typename Element>
class CryptoParametersBase;

} // lbcrypto

namespace openfhe
{

using CryptoParametersBase = lbcrypto::CryptoParametersBase<lbcrypto::DCRTPoly>;

class CryptoParametersBaseDCRTPoly final
{
    std::shared_ptr<CryptoParametersBase> m_cryptoParametersBase;
public:
    CryptoParametersBaseDCRTPoly() = default;
    CryptoParametersBaseDCRTPoly(
        const std::shared_ptr<CryptoParametersBase>& cryptoParametersBase) noexcept;
    CryptoParametersBaseDCRTPoly(const CryptoParametersBaseDCRTPoly&) = delete;
    CryptoParametersBaseDCRTPoly(CryptoParametersBaseDCRTPoly&&) = delete;
    CryptoParametersBaseDCRTPoly& operator=(const CryptoParametersBaseDCRTPoly&) = delete;
    CryptoParametersBaseDCRTPoly& operator=(CryptoParametersBaseDCRTPoly&&) = delete;
};

} // openfhe
