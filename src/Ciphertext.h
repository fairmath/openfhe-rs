#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"

#include "SerialMode.h" // SerialMode

namespace openfhe
{

using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;

class CiphertextDCRTPoly final
{
    std::shared_ptr<CiphertextImpl> m_ciphertext;
public:
    friend bool SerializeCiphertextToFile(const std::string& ciphertextLocation,
        const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
    friend bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation,
        CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);

    CiphertextDCRTPoly() = default;
    explicit CiphertextDCRTPoly(const std::shared_ptr<CiphertextImpl>& ciphertext);
    CiphertextDCRTPoly(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly(CiphertextDCRTPoly&&) = delete;
    CiphertextDCRTPoly& operator=(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly& operator=(CiphertextDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<CiphertextImpl> GetInternal() const;
};
[[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> GenNullCiphertext();

} // openfhe
