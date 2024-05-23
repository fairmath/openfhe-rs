#include "Plaintext.h"

#include "openfhe/pke/encoding/plaintext.h"

#include "openfhe/src/lib.rs.h" // ComplexPair

namespace openfhe
{

Plaintext::Plaintext(const std::shared_ptr<PlaintextImpl>& plaintext)
    : m_plaintext(plaintext)
{ }
Plaintext& Plaintext::operator=(const std::shared_ptr<PlaintextImpl>& plaintext)
{
    m_plaintext = plaintext;
    return *this;
}
std::shared_ptr<PlaintextImpl> Plaintext::GetInternal() const
{
    return m_plaintext;
}
void Plaintext::SetLength(const size_t newSize) const
{
    m_plaintext->SetLength(newSize);
}
double Plaintext::GetLogPrecision() const
{
    return m_plaintext->GetLogPrecision();
}
rust::String Plaintext::GetString() const
{
    std::stringstream stream;
    stream << *m_plaintext;
    return rust::String(stream.str());
}
std::unique_ptr<std::vector<ComplexPair>> Plaintext::GetCopyOfCKKSPackedValue() const
{
    const std::vector<std::complex<double>>& v = m_plaintext->GetCKKSPackedValue();
    std::vector<ComplexPair> result;
    result.reserve(v.size());
    for (const std::complex<double>& elem : v)
    {
        result.push_back(ComplexPair{elem.real(), elem.imag()});
    }
    return std::make_unique<std::vector<ComplexPair>>(std::move(result));
}
std::unique_ptr<Plaintext> GenEmptyPlainText()
{
    return std::make_unique<Plaintext>();
}

} // openfhe
