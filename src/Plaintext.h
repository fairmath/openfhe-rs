#pragma once

#include "openfhe/core/utils/inttypes.h"
#include "openfhe/pke/encoding/plaintext-fwd.h"
#include "openfhe/pke/scheme/scheme-id.h"

#include "rust/cxx.h"

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
    Plaintext() = default;
    Plaintext(std::shared_ptr<PlaintextImpl>&& plaintext) noexcept;
    Plaintext(const Plaintext&) = delete;
    Plaintext(Plaintext&&) = delete;
    Plaintext& operator=(const Plaintext&) = delete;
    Plaintext& operator=(Plaintext&&) = delete;

    void SetLength(const size_t newSize) const;
    void SetLevel(const size_t l) const noexcept;
    [[nodiscard]] bool IsEncoded() const noexcept;
    [[nodiscard]] int64_t HighBound() const noexcept;
    [[nodiscard]] int64_t LowBound() const noexcept;
    [[nodiscard]] double GetLogPrecision() const;
    [[nodiscard]] rust::String GetString() const;
    [[nodiscard]] size_t GetLength() const noexcept;
    [[nodiscard]] size_t GetLevel() const noexcept;
    [[nodiscard]] double GetLogError() const;
    [[nodiscard]] size_t GetNoiseScaleDeg() const noexcept;
    [[nodiscard]] double GetScalingFactor() const noexcept;
    [[nodiscard]] SCHEME GetSchemeID() const noexcept;
    [[nodiscard]] uint32_t GetSlots() const noexcept;
    [[nodiscard]] bool Encode() const;
    [[nodiscard]] bool Decode() const;
    void SetFormat(const Format fmt) const;
    void SetIntVectorValue(const std::vector<int64_t>& val) const;
    void SetNoiseScaleDeg(const size_t nsd) const noexcept;
    void SetScalingFactor(const double sf) const noexcept;
    void SetSlots(const uint32_t s) const noexcept;
    void SetStringValue(const std::string& value) const;
    [[nodiscard]] std::unique_ptr<std::vector<ComplexPair>> GetCopyOfCKKSPackedValue() const;
    [[nodiscard]] const std::vector<int64_t>& GetPackedValue() const;
    [[nodiscard]] std::unique_ptr<std::vector<double>> GetRealPackedValue() const;
    [[nodiscard]] const std::vector<int64_t>& GetCoefPackedValue() const;
    [[nodiscard]] const std::string& GetStringValue() const;
    [[nodiscard]] const std::shared_ptr<PlaintextImpl>& GetRef() const noexcept;
    [[nodiscard]] std::shared_ptr<PlaintextImpl>& GetRef() noexcept;
};

// Generator functions
[[nodiscard]] std::unique_ptr<Plaintext> GenNullPlainText();

} // openfhe
