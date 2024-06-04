#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"

#include <memory>

namespace lbcrypto
{

template <class Element>
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
    explicit CryptoParametersBaseDCRTPoly(
        const std::shared_ptr<CryptoParametersBase>& cryptoParametersBase);
    CryptoParametersBaseDCRTPoly(const CryptoParametersBaseDCRTPoly&) = delete;
    CryptoParametersBaseDCRTPoly(CryptoParametersBaseDCRTPoly&&) = delete;
    CryptoParametersBaseDCRTPoly& operator=(const CryptoParametersBaseDCRTPoly&) = delete;
    CryptoParametersBaseDCRTPoly& operator=(CryptoParametersBaseDCRTPoly&&) = delete;
};

} // openfhe
