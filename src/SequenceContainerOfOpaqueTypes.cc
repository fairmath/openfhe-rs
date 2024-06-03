#include "SequenceContainerOfOpaqueTypes.h"

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

VectorOfPrivateKeys::VectorOfPrivateKeys(std::vector<std::shared_ptr<PrivateKeyImpl>> privateKeys)
    : m_privateKeys(std::move(privateKeys))
{ }
const std::vector<std::shared_ptr<PrivateKeyImpl>>& VectorOfPrivateKeys::GetInternal() const
{
    return m_privateKeys;
}

VectorOfDCRTPoly::VectorOfDCRTPoly(const std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> elements)
    : m_elements(elements)
{ }
std::shared_ptr<std::vector<lbcrypto::DCRTPoly>> VectorOfDCRTPoly::GetInternal() const
{
    return m_elements;
}

} // openfhe
