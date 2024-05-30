#include "PrivateKey.h"

#include "openfhe/pke/key/privatekey.h"

namespace openfhe
{

PrivateKeyDCRTPoly::PrivateKeyDCRTPoly(const std::shared_ptr<PrivateKeyImpl>& privateKey)
    : m_privateKey(privateKey)
{ }
std::shared_ptr<PrivateKeyImpl> PrivateKeyDCRTPoly::GetInternal() const
{
    return m_privateKey;
}

} // openfhe
