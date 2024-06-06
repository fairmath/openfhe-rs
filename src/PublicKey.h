#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/publickey-fwd.h"

#include "SerialMode.h"

namespace openfhe
{

using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;

class PublicKeyDCRTPoly final
{
    std::shared_ptr<PublicKeyImpl> m_publicKey;
public:
    friend bool SerializePublicKeyToFile(const std::string& publicKeyLocation,
        const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
    friend bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation,
        PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);

    PublicKeyDCRTPoly() = default;
    PublicKeyDCRTPoly(const std::shared_ptr<PublicKeyImpl>& publicKey) noexcept;
    PublicKeyDCRTPoly(const PublicKeyDCRTPoly&) = delete;
    PublicKeyDCRTPoly(PublicKeyDCRTPoly&&) = delete;
    PublicKeyDCRTPoly& operator=(const PublicKeyDCRTPoly&) = delete;
    PublicKeyDCRTPoly& operator=(PublicKeyDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<PublicKeyImpl> GetInternal() const noexcept;
};

// Generator functions
[[nodiscard]] std::unique_ptr<PublicKeyDCRTPoly> GenNullPublicKey();

} // openfhe
