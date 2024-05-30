#include "VectorOfCiphertexts.h"

namespace openfhe
{

VectorOfCiphertexts::VectorOfCiphertexts(std::vector<std::shared_ptr<CiphertextImpl>> ciphertexts)
    : m_ciphertexts(std::move(ciphertexts))
{ }
const std::vector<std::shared_ptr<CiphertextImpl>>& VectorOfCiphertexts::GetInternal() const
{
    return m_ciphertexts;
}
std::vector<std::shared_ptr<CiphertextImpl>>& VectorOfCiphertexts::GetInternal()
{
    return m_ciphertexts;
}

} // openfhe
