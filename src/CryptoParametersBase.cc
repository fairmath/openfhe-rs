#include "CryptoParametersBase.h"

#include "openfhe/pke/schemebase/base-cryptoparameters.h"

namespace openfhe
{

CryptoParametersBaseDCRTPoly::CryptoParametersBaseDCRTPoly(
    const std::shared_ptr<CryptoParametersBase>& cryptoParametersBase)
    : m_cryptoParametersBase(cryptoParametersBase)
{ }

} // openfhe
