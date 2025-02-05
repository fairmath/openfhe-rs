#include "TrapdoorPair.h"

namespace openfhe
{

RLWETrapdoorPairDRCTPoly::RLWETrapdoorPairDRCTPoly(RLWETrapdoorPair&& rlweTrapdoorPair) noexcept
    : m_trapdoorPair(std::move(rlweTrapdoorPair))
{ }
} // openfhe
