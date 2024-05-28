#include "PublicKey.h"

#include "openfhe/pke/key/publickey.h"

namespace openfhe
{

PublicKeyDCRTPoly::PublicKeyDCRTPoly()
    : m_publicKey(std::make_shared<PublicKeyImpl>())
{ }
PublicKeyDCRTPoly::PublicKeyDCRTPoly(const std::shared_ptr<PublicKeyImpl>& publicKey)
    : m_publicKey(publicKey)
{ }
std::shared_ptr<PublicKeyImpl> PublicKeyDCRTPoly::GetInternal() const
{
    return m_publicKey;
}
std::unique_ptr<PublicKeyDCRTPoly> GenDefaultConstructedPublicKey()
{
    return std::make_unique<PublicKeyDCRTPoly>();
}

} // openfhe
