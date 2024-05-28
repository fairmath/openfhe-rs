#pragma once

#include "openfhe/binfhe/lwe-privatekey-fwd.h"

namespace openfhe
{

using LWEPrivateKeyImpl = lbcrypto::LWEPrivateKeyImpl;

class LWEPrivateKey final
{
    std::shared_ptr<LWEPrivateKeyImpl> m_lwePrivateKey;
public:
    explicit LWEPrivateKey();
    explicit LWEPrivateKey(const std::shared_ptr<LWEPrivateKeyImpl>& lwePrivateKey);
    LWEPrivateKey(const LWEPrivateKey&) = delete;
    LWEPrivateKey(LWEPrivateKey&&) = delete;
    LWEPrivateKey& operator=(const LWEPrivateKey&) = delete;
    LWEPrivateKey& operator=(LWEPrivateKey&&) = delete;

    [[nodiscard]] std::shared_ptr<LWEPrivateKeyImpl> GetInternal() const;
};

} // openfhe
