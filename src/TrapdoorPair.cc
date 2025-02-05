#include "TrapdoorPair.h"

// #include "PrivateKey.h"
// #include "PublicKey.h"

namespace openfhe
{

RLWETrapdoorPairDRCTPoly::RLWETrapdoorPairDRCTPoly(RLWETrapdoorPair&& rlweTrapdoorPair) noexcept
    : m_trapdoorPair(std::move(rlweTrapdoorPair))
{ }
// std::unique_ptr<PrivateKeyDCRTPoly> KeyPairDCRTPoly::GetPrivateKey() const
// {
//     return std::make_unique<PrivateKeyDCRTPoly>(m_keyPair.secretKey);
// }
// std::unique_ptr<PublicKeyDCRTPoly> KeyPairDCRTPoly::GetPublicKey() const
// {
//     return std::make_unique<PublicKeyDCRTPoly>(m_keyPair.publicKey);
// }
// const KeyPair& KeyPairDCRTPoly::GetRef() const noexcept
// {
//     return m_keyPair;
// }

} // openfhe
