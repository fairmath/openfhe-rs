#pragma once

#include "openfhe/binfhe/lwe-ciphertext-fwd.h"
#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/ciphertext-fwd.h"
#include "openfhe/pke/key/evalkey-fwd.h"
#include "openfhe/pke/key/privatekey-fwd.h"

// cxx currently does not support std::vector of opaque type

namespace openfhe
{

using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;

class VectorOfCiphertexts final
{
    std::vector<std::shared_ptr<CiphertextImpl>> m_ciphertexts;
public:
    VectorOfCiphertexts(std::vector<std::shared_ptr<CiphertextImpl>>&& ciphertexts) noexcept;
    [[nodiscard]] const std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal() const noexcept;
    [[nodiscard]] std::vector<std::shared_ptr<CiphertextImpl>>& GetInternal() noexcept;
};

class VectorOfVectorOfCiphertexts final
{
    std::vector<std::vector<std::shared_ptr<CiphertextImpl>>> m_ciphertexts;
public:
    VectorOfVectorOfCiphertexts(
        std::vector<std::vector<std::shared_ptr<CiphertextImpl>>>&& ciphertexts) noexcept;
    [[nodiscard]] std::vector<std::vector<std::shared_ptr<CiphertextImpl>>>&
        GetInternal() noexcept;
};

using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;

class VectorOfPrivateKeys final
{
    std::vector<std::shared_ptr<PrivateKeyImpl>> m_privateKeys;
public:
    VectorOfPrivateKeys(std::vector<std::shared_ptr<PrivateKeyImpl>>&& ciphertexts) noexcept;
    [[nodiscard]] const std::vector<std::shared_ptr<PrivateKeyImpl>>& GetInternal() const noexcept;
};

class VectorOfDCRTPolys final
{
    std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> m_elements;
public:
    VectorOfDCRTPolys(std::shared_ptr<std::vector<lbcrypto::DCRTPoly>>&& elements) noexcept;
    [[nodiscard]] std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> GetInternal() const noexcept;
};

using EvalKeyImpl = lbcrypto::EvalKeyImpl<lbcrypto::DCRTPoly>;

class VectorOfEvalKeys final
{
    std::vector<std::shared_ptr<EvalKeyImpl>> m_evalKeys;
public:
    VectorOfEvalKeys(std::vector<std::shared_ptr<EvalKeyImpl>> evalKeys);
    [[nodiscard]] const std::vector<std::shared_ptr<EvalKeyImpl>>& GetInternal() const noexcept;
};

using LWECiphertextImpl = lbcrypto::LWECiphertextImpl;

class VectorOfLWECiphertexts final
{
    std::vector<std::shared_ptr<LWECiphertextImpl>> m_lweCiphertexts;
public:
    VectorOfLWECiphertexts(
        std::vector<std::shared_ptr<LWECiphertextImpl>>&& lweCiphertexts) noexcept;
    [[nodiscard]] std::vector<std::shared_ptr<LWECiphertextImpl>>& GetInternal() noexcept;
};

} // openfhe
