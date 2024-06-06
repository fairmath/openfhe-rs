#include "DecryptResult.h"

namespace openfhe
{

DecryptResult::DecryptResult(lbcrypto::DecryptResult&& decryptResult) noexcept
    : m_decryptResult(std::move(decryptResult))
{ }

} // openfhe
