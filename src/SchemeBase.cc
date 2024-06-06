#include "SchemeBase.h"

#include "openfhe/pke/schemebase/base-scheme.h"

namespace openfhe
{

SchemeBaseDCRTPoly::SchemeBaseDCRTPoly(const std::shared_ptr<SchemeBase>& schemeBase) noexcept
    : m_schemeBase(schemeBase)
{ }

} // openfhe
