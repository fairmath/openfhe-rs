#include "PublicKey.h"

#include "openfhe/pke/key/publickey.h"

namespace openfhe
{

PublicKeyDCRTPoly::PublicKeyDCRTPoly(const std::shared_ptr<PublicKeyImpl>& publicKey)
    : m_publicKey(publicKey)
{ }
std::shared_ptr<PublicKeyImpl> PublicKeyDCRTPoly::GetInternal() const
{
    return m_publicKey;
}
std::unique_ptr<PublicKeyDCRTPoly> GenNullPublicKey()
{
    return std::make_unique<PublicKeyDCRTPoly>();
}

} // openfhe
