#include "PrivateKey.h"

#include "openfhe/pke/key/privatekey.h"

namespace openfhe
{

PrivateKeyDCRTPoly::PrivateKeyDCRTPoly(const std::shared_ptr<PrivateKeyImpl>& privateKey) noexcept
    : m_privateKey(privateKey)
{ }
std::shared_ptr<PrivateKeyImpl> PrivateKeyDCRTPoly::GetInternal() const noexcept
{
    return m_privateKey;
}

} // openfhe
