#include "PrivateKey.h"

#include "openfhe/pke/key/privatekey.h"

namespace openfhe
{

PrivateKeyDCRTPoly::PrivateKeyDCRTPoly(const std::shared_ptr<PrivateKeyImpl>& privateKey) noexcept
    : m_privateKey(privateKey)
{ }
const std::shared_ptr<PrivateKeyImpl>& PrivateKeyDCRTPoly::GetRef() const noexcept
{
    return m_privateKey;
}
std::shared_ptr<PrivateKeyImpl>& PrivateKeyDCRTPoly::GetRef() noexcept
{
    return m_privateKey;
}

std::unique_ptr<PrivateKeyDCRTPoly> DCRTPolyGenNullPrivateKey()
{
    return std::make_unique<PrivateKeyDCRTPoly>();

} // openfhe
