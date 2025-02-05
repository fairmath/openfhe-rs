#include "TrapdoorPair.h"
#include "Matrix.h"

namespace openfhe
{

RLWETrapdoorPairDRCTPoly::RLWETrapdoorPairDRCTPoly(RLWETrapdoorPair&& rlweTrapdoorPair) noexcept
    : m_trapdoorPair(std::move(rlweTrapdoorPair))
{ }
std::unique_ptr<MatrixDCRTPoly> RLWETrapdoorPairDRCTPoly::GetMatrixR() const
{
    return std::make_unique<MatrixDCRTPoly>(m_trapdoorPair.m_r);
}
std::unique_ptr<MatrixDCRTPoly> RLWETrapdoorPairDRCTPoly::GetMatrixE() const
{
    return std::make_unique<MatrixDCRTPoly>(m_trapdoorPair.m_e);
}
} // openfhe
