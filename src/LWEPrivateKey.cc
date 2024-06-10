#include "LWEPrivateKey.h"

#include "openfhe/binfhe/lwe-privatekey.h"

namespace openfhe
{

LWEPrivateKey::LWEPrivateKey(std::shared_ptr<LWEPrivateKeyImpl>&& lwePrivateKey) noexcept
    : m_lwePrivateKey(std::move(lwePrivateKey))
{ }
const std::shared_ptr<LWEPrivateKeyImpl>& LWEPrivateKey::GetRef() const noexcept
{
    return m_lwePrivateKey;
}

} // openfhe
