#include "KeyPair.h"

#include "PrivateKey.h"
#include "PublicKey.h"

namespace openfhe
{

KeyPairDCRTPoly::KeyPairDCRTPoly(KeyPair&& keyPair) noexcept
    : m_keyPair(std::move(keyPair))
{ }
std::unique_ptr<PrivateKeyDCRTPoly> KeyPairDCRTPoly::GetPrivateKey() const
{
    return std::make_unique<PrivateKeyDCRTPoly>(m_keyPair.secretKey);
}
std::unique_ptr<PublicKeyDCRTPoly> KeyPairDCRTPoly::GetPublicKey() const
{
    return std::make_unique<PublicKeyDCRTPoly>(m_keyPair.publicKey);
}
const KeyPair& KeyPairDCRTPoly::GetRef() const noexcept
{
    return m_keyPair;
}

} // openfhe
