#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"
#include "openfhe/pke/key/privatekey-fwd.h"

#include <vector>

// cxx currently does not support std::vector of opaque type

namespace openfhe
{

using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;

class VectorOfCiphertexts final
{
    std::vector<std::shared_ptr<CiphertextImpl>> m_ciphertexts;
public:
    explicit VectorOfCiphertexts(std::vector<std::shared_ptr<CiphertextImpl>> ciphertexts);
    [[nodiscard]] const std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal() const;
    [[nodiscard]] std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal();
};

using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;

class VectorOfPrivateKeys final
{
    std::vector<std::shared_ptr<PrivateKeyImpl>> m_privateKeys;
public:
    explicit VectorOfPrivateKeys(std::vector<std::shared_ptr<PrivateKeyImpl>> ciphertexts);
    [[nodiscard]] const std::vector<std::shared_ptr<PrivateKeyImpl>>& GetInternal() const;
};

} // openfhe
