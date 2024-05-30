#include "KeyPair.h"

#include "openfhe/pke/key/keypair.h"

#include "PublicKey.h"
#include "PrivateKey.h"

namespace openfhe
{

KeyPairDCRTPoly::KeyPairDCRTPoly(const KeyPair& keyPair)
    : m_publicKey(keyPair.publicKey)
    , m_privateKey(keyPair.secretKey)
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
