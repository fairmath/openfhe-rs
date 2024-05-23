#pragma once

#include "openfhe/core/utils/inttypes.h" // Format
#include "openfhe/pke/encoding/plaintext-fwd.h"
#include "openfhe/pke/scheme/scheme-id.h"

#include "rust/cxx.h" // rust::String

namespace openfhe
{

using PlaintextImpl = lbcrypto::PlaintextImpl;
using SCHEME = lbcrypto::SCHEME;
using Format = ::Format;
struct ComplexPair;

class Plaintext final
{
    std::shared_ptr<PlaintextImpl> m_plaintext;
public:
    explicit Plaintext() = default;
    explicit Plaintext(const std::shared_ptr<PlaintextImpl>& plaintext);
    Plaintext(const Plaintext&) = delete;
    Plaintext(Plaintext&&) = delete;
    Plaintext& operator=(const Plaintext&) = delete;
    Plaintext& operator=(Plaintext&&) = delete;
    Plaintext& operator=(const std::shared_ptr<PlaintextImpl>& plaintext);

    [[nodiscard]] std::shared_ptr<PlaintextImpl> GetInternal() const;
    void SetLength(const size_t newSize) const;
    void SetLevel(const size_t l) const;
    [[nodiscard]] bool IsEncoded() const;
    [[nodiscard]] int64_t HighBound() const;
    [[nodiscard]] int64_t LowBound() const;
    [[nodiscard]] double GetLogPrecision() const;
    [[nodiscard]] rust::String GetString() const;
    [[nodiscard]] size_t GetLength() const;
    [[nodiscard]] size_t GetLevel() const;
    [[nodiscard]] double GetLogError() const;
    [[nodiscard]] size_t GetNoiseScaleDeg() const;
    [[nodiscard]] double GetScalingFactor() const;
    [[nodiscard]] SCHEME GetSchemeID() const;
    [[nodiscard]] uint32_t GetSlots() const;
    [[nodiscard]] bool Encode() const;
    [[nodiscard]] bool Decode() const;
    void SetFormat(const Format fmt) const;
    void SetIntVectorValue(const std::vector<int64_t>& val) const;
    void SetNoiseScaleDeg(const size_t nsd) const;
    void SetScalingFactor(const double sf) const;
    void SetSlots(const uint32_t s) const;

    [[nodiscard]] std::unique_ptr<std::vector<ComplexPair>> GetCopyOfCKKSPackedValue() const;
    [[nodiscard]] std::unique_ptr<std::vector<int64_t>> GetCopyOfPackedValue() const;
    [[nodiscard]] std::unique_ptr<std::vector<double>> GetCopyOfRealPackedValue() const;
    [[nodiscard]] std::unique_ptr<std::vector<int64_t>> GetCopyOfCoefPackedValue() const;
};
[[nodiscard]] std::unique_ptr<Plaintext> GenEmptyPlainText();

} // openfhe
