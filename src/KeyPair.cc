#include "KeyPair.h"

#include "openfhe/pke/key/keypair.h"

#include "PublicKey.h"
#include "PrivateKey.h"

namespace openfhe
{

KeyPairDCRTPoly::KeyPairDCRTPoly(KeyPair&& keyPair) noexcept
    : m_publicKey(std::move(keyPair.publicKey))
    , m_privateKey(std::move(keyPair.secretKey))
{ }
std::unique_ptr<PublicKeyDCRTPoly> KeyPairDCRTPoly::GetPublicKey() const
{
    return std::make_unique<PublicKeyDCRTPoly>(m_publicKey);
}
std::unique_ptr<PrivateKeyDCRTPoly> KeyPairDCRTPoly::GetPrivateKey() const
{
    return std::make_unique<PrivateKeyDCRTPoly>(m_privateKey);
}

} // openfhe
