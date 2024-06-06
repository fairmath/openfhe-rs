#pragma once

#include "openfhe/binfhe/lwe-privatekey-fwd.h"

namespace openfhe
{

using LWEPrivateKeyImpl = lbcrypto::LWEPrivateKeyImpl;

class LWEPrivateKey final
{
    std::shared_ptr<LWEPrivateKeyImpl> m_lwePrivateKey;
public:
    LWEPrivateKey(std::shared_ptr<LWEPrivateKeyImpl>&& lwePrivateKey) noexcept;
    LWEPrivateKey(const LWEPrivateKey&) = delete;
    LWEPrivateKey(LWEPrivateKey&&) = delete;
    LWEPrivateKey& operator=(const LWEPrivateKey&) = delete;
    LWEPrivateKey& operator=(LWEPrivateKey&&) = delete;

    [[nodiscard]] std::shared_ptr<LWEPrivateKeyImpl> GetInternal() const noexcept;
};

} // openfhe
