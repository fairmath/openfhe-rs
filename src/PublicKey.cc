#include "PublicKey.h"

#include "openfhe/pke/key/publickey.h"

namespace openfhe
{

PublicKeyDCRTPoly::PublicKeyDCRTPoly()
    : m_publicKey(std::make_shared<PublicKeyImpl>())
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
