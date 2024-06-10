#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/evalkey-fwd.h"

namespace openfhe
{

using EvalKeyImpl = lbcrypto::EvalKeyImpl<lbcrypto::DCRTPoly>;

class EvalKeyDCRTPoly final
{
    std::shared_ptr<EvalKeyImpl> m_evalKey;
public:
    EvalKeyDCRTPoly(std::shared_ptr<EvalKeyImpl>&& evalKey) noexcept;
    EvalKeyDCRTPoly(const EvalKeyDCRTPoly&) = delete;
    EvalKeyDCRTPoly(EvalKeyDCRTPoly&&) = delete;
    EvalKeyDCRTPoly& operator=(const EvalKeyDCRTPoly&) = delete;
    EvalKeyDCRTPoly& operator=(EvalKeyDCRTPoly&&) = delete;

    [[nodiscard]] const std::shared_ptr<EvalKeyImpl>& GetRef() const noexcept;
};

} // openfhe
