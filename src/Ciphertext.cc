#include "Ciphertext.h"

#include "openfhe/pke/ciphertext.h"

namespace openfhe
{

CiphertextDCRTPoly::CiphertextDCRTPoly(std::shared_ptr<CiphertextImpl>&& ciphertext) noexcept
    : m_ciphertext(std::move(ciphertext))
{ }
std::shared_ptr<CiphertextImpl> CiphertextDCRTPoly::GetInternal() const noexcept
{
    return m_ciphertext;
}
std::shared_ptr<CiphertextImpl>& CiphertextDCRTPoly::GetRef() noexcept
{
    return m_ciphertext;
}
const std::shared_ptr<CiphertextImpl>& CiphertextDCRTPoly::GetRef() const noexcept
{
    return m_ciphertext;
}

// Generator functions
std::unique_ptr<CiphertextDCRTPoly> DCRTPolyGenNullCiphertext()
{
    return std::make_unique<CiphertextDCRTPoly>();
}

} // openfhe
