#include "EvalKey.h"

#include "openfhe/pke/key/evalkey.h"

namespace openfhe
{

EvalKeyDCRTPoly::EvalKeyDCRTPoly(std::shared_ptr<EvalKeyImpl>&& evalKey) noexcept
    : m_evalKey(std::move(evalKey))
{ }
const std::shared_ptr<EvalKeyImpl>& EvalKeyDCRTPoly::GetRef() const noexcept
{
    return m_evalKey;
}

} // openfhe
