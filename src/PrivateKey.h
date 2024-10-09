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
    PrivateKeyDCRTPoly() = default;
    PrivateKeyDCRTPoly(const std::shared_ptr<PrivateKeyImpl>& privateKey) noexcept;
    PrivateKeyDCRTPoly(const PrivateKeyDCRTPoly&) = delete;
    PrivateKeyDCRTPoly(PrivateKeyDCRTPoly&&) = delete;
    PrivateKeyDCRTPoly& operator=(const PrivateKeyDCRTPoly&) = delete;
    PrivateKeyDCRTPoly& operator=(PrivateKeyDCRTPoly&&) = delete;

    [[nodiscard]] const std::shared_ptr<PrivateKeyImpl>& GetRef() const noexcept;
    [[nodiscard]] std::shared_ptr<PrivateKeyImpl>& GetRef() noexcept;
};

[[nodiscard]] std::unique_ptr<PrivateKeyDCRTPoly> DCRTPolyGenNullPrivateKey();

} // openfhe
