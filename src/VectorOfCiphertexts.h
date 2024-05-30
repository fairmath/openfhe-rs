#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"

#include <vector>

namespace openfhe
{

using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;

class VectorOfCiphertexts final
{
    std::vector<std::shared_ptr<CiphertextImpl>> m_ciphertexts;
public:
    VectorOfCiphertexts(std::vector<std::shared_ptr<CiphertextImpl>> ciphertexts);
    [[nodiscard]] const std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal() const;
    [[nodiscard]] std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal();
};

} // openfhe
