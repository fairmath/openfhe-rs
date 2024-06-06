#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"

namespace lbcrypto
{

template <typename Element>
class SchemeBase;

} // lbcrypto

namespace openfhe
{

using SchemeBase = lbcrypto::SchemeBase<lbcrypto::DCRTPoly>;

class SchemeBaseDCRTPoly final
{
    std::shared_ptr<SchemeBase> m_schemeBase;
public:
    SchemeBaseDCRTPoly() = default;
    SchemeBaseDCRTPoly(const std::shared_ptr<SchemeBase>& schemeBase) noexcept;
    SchemeBaseDCRTPoly(const SchemeBaseDCRTPoly&) = delete;
    SchemeBaseDCRTPoly(SchemeBaseDCRTPoly&&) = delete;
    SchemeBaseDCRTPoly& operator=(const SchemeBaseDCRTPoly&) = delete;
    SchemeBaseDCRTPoly& operator=(SchemeBaseDCRTPoly&&) = delete;
};

} // openfhe
