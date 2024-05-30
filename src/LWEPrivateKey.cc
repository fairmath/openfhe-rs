#include "LWEPrivateKey.h"

#include "openfhe/binfhe/lwe-privatekey.h"

namespace openfhe
{

LWEPrivateKey::LWEPrivateKey()
    : m_lwePrivateKey(std::make_shared<LWEPrivateKeyImpl>())
{ }
LWEPrivateKey::LWEPrivateKey(const std::shared_ptr<LWEPrivateKeyImpl>& lwePrivateKey)
    : m_lwePrivateKey(lwePrivateKey)
{ }
std::shared_ptr<LWEPrivateKeyImpl> LWEPrivateKey::GetInternal() const
{
    return m_lwePrivateKey;
}

} // openfhe