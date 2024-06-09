#include "PublicKey.h"

#include "openfhe/pke/key/publickey.h"

namespace openfhe
{

PublicKeyDCRTPoly::PublicKeyDCRTPoly(const std::shared_ptr<PublicKeyImpl>& publicKey) noexcept
    : m_publicKey(publicKey)
{ }
std::shared_ptr<PublicKeyImpl> PublicKeyDCRTPoly::GetInternal() const noexcept
{
    return m_publicKey;
}
std::shared_ptr<PublicKeyImpl>& PublicKeyDCRTPoly::GetRef() noexcept
{
    return m_publicKey;
}
const std::shared_ptr<PublicKeyImpl>& PublicKeyDCRTPoly::GetRef() const noexcept
{
    return m_publicKey;
}

// Generator functions
std::unique_ptr<PublicKeyDCRTPoly> DCRTPolyGenNullPublicKey()
{
    return std::make_unique<PublicKeyDCRTPoly>();
}

} // openfhe
