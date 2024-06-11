#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/keypair.h"

namespace openfhe
{

class PrivateKeyDCRTPoly;
class PublicKeyDCRTPoly;

using KeyPair = lbcrypto::KeyPair<lbcrypto::DCRTPoly>;
using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;

class KeyPairDCRTPoly final
{
    KeyPair m_keyPair;
public:
    KeyPairDCRTPoly(KeyPair&& keyPair) noexcept;
    KeyPairDCRTPoly(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly(KeyPairDCRTPoly&&) = delete;
    KeyPairDCRTPoly& operator=(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly& operator=(KeyPairDCRTPoly&&) = delete;

    [[nodiscard]] std::unique_ptr<PrivateKeyDCRTPoly> GetPrivateKey() const;
    [[nodiscard]] std::unique_ptr<PublicKeyDCRTPoly> GetPublicKey() const;

    [[nodiscard]] const KeyPair& GetRef() const noexcept;
};

} // openfhe
