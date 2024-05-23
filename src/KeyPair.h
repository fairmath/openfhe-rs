#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/privatekey-fwd.h"
#include "openfhe/pke/key/publickey-fwd.h"

namespace lbcrypto
{

template <class Element>
class KeyPair;

} // lbcrypto

namespace openfhe
{

using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;
using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
using KeyPair = lbcrypto::KeyPair<lbcrypto::DCRTPoly>;

class KeyPairDCRTPoly final
{
    std::shared_ptr<PublicKeyImpl> m_publicKey;
    std::shared_ptr<PrivateKeyImpl> m_privateKey;
public:
    explicit KeyPairDCRTPoly(const KeyPair& keyPair);
    KeyPairDCRTPoly(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly(KeyPairDCRTPoly&&) = delete;
    KeyPairDCRTPoly& operator=(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly& operator=(KeyPairDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<PublicKeyImpl> GetPublicKey() const;
    [[nodiscard]] std::shared_ptr<PrivateKeyImpl> GetPrivateKey() const;
};

} // openfhe