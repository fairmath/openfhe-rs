#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/privatekey-fwd.h"

namespace openfhe
{

using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;

class PrivateKeyDCRTPoly final
{
    std::shared_ptr<PrivateKeyImpl> m_privateKey;
public:
    explicit PrivateKeyDCRTPoly(const std::shared_ptr<PrivateKeyImpl>& privateKey);
    PrivateKeyDCRTPoly(const PrivateKeyDCRTPoly&) = delete;
    PrivateKeyDCRTPoly(PrivateKeyDCRTPoly&&) = delete;
    PrivateKeyDCRTPoly& operator=(const PrivateKeyDCRTPoly&) = delete;
    PrivateKeyDCRTPoly& operator=(PrivateKeyDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<PrivateKeyImpl> GetInternal() const;
};

} // openfhe
