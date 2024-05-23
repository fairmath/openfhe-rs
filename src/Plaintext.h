#pragma once

#include "openfhe/pke/encoding/plaintext-fwd.h"

#include "rust/cxx.h" // rust::String

namespace openfhe
{

using PlaintextImpl = lbcrypto::PlaintextImpl;
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
    [[nodiscard]] double GetLogPrecision() const;
    [[nodiscard]] rust::String GetString() const;
    [[nodiscard]] std::unique_ptr<std::vector<ComplexPair>> GetCopyOfCKKSPackedValue() const;
};
[[nodiscard]] std::unique_ptr<Plaintext> GenEmptyPlainText();

} // openfhe
