#include "Ciphertext.h"

#include "openfhe/pke/ciphertext.h"

namespace openfhe
{

CiphertextDCRTPoly::CiphertextDCRTPoly(const std::shared_ptr<CiphertextImpl>& ciphertext)
    : m_ciphertext(ciphertext)
{ }
std::shared_ptr<CiphertextImpl> CiphertextDCRTPoly::GetInternal() const
{
    return m_ciphertext;
}
std::unique_ptr<CiphertextDCRTPoly> GenNullCiphertext()
{
    return std::make_unique<CiphertextDCRTPoly>();
}

} // openfhe
