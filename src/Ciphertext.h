#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"

namespace openfhe
{

using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;

class CiphertextDCRTPoly final
{
    std::shared_ptr<CiphertextImpl> m_ciphertext;
public:
    CiphertextDCRTPoly() = default;
    CiphertextDCRTPoly(std::shared_ptr<CiphertextImpl>&& ciphertext) noexcept;
    CiphertextDCRTPoly(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly(CiphertextDCRTPoly&&) = delete;
    CiphertextDCRTPoly& operator=(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly& operator=(CiphertextDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<CiphertextImpl> GetInternal() const noexcept;
    [[nodiscard]] std::shared_ptr<CiphertextImpl>& GetRef() noexcept;
    [[nodiscard]] const std::shared_ptr<CiphertextImpl>& GetRef() const noexcept;
};

// Generator functions
[[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> GenNullCiphertext();

} // openfhe
