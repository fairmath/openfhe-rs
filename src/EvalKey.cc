#include "EvalKey.h"

#include "openfhe/pke/key/evalkey.h"

namespace openfhe
{

EvalKeyDCRTPoly::EvalKeyDCRTPoly(const std::shared_ptr<EvalKeyImpl>& evalKey)
    : m_evalKey(evalKey)
{ }
std::shared_ptr<EvalKeyImpl> EvalKeyDCRTPoly::GetInternal() const
{
    return m_evalKey;
}

} // openfhe
