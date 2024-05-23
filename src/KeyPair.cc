#include "KeyPair.h"

#include "openfhe/pke/key/keypair.h"

namespace openfhe
{

KeyPairDCRTPoly::KeyPairDCRTPoly(const KeyPair& keyPair)
    : m_publicKey(keyPair.publicKey)
    , m_privateKey(keyPair.secretKey)
{ }
std::shared_ptr<PublicKeyImpl> KeyPairDCRTPoly::GetPublicKey() const
{
    return m_publicKey;
}
std::shared_ptr<PrivateKeyImpl> KeyPairDCRTPoly::GetPrivateKey() const
{
    return m_privateKey;
}

} // openfhe
