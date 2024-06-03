#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"
#include "openfhe/pke/key/evalkey-fwd.h"
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

class VectorOfDCRTPolys final
{
    std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> m_elements;
public:
    explicit VectorOfDCRTPolys(const std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> elements);
    [[nodiscard]] std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> GetInternal() const;
};

using EvalKeyImpl = lbcrypto::EvalKeyImpl<lbcrypto::DCRTPoly>;

class VectorOfEvalKeys final
{
    std::vector<std::shared_ptr<EvalKeyImpl>> m_evalKeys;
public:
    explicit VectorOfEvalKeys(std::vector<std::shared_ptr<EvalKeyImpl>> evalKeys);
    [[nodiscard]] const std::vector<std::shared_ptr<EvalKeyImpl>>& GetInternal() const;
};

} // openfhe
