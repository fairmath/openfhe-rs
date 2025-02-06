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

RLWETrapdoorResultDRCTPoly::RLWETrapdoorResultDRCTPoly(Matrix&& uniformMatrix, RLWETrapdoorPair&& trapdoorPair) noexcept
    : m_uniformMatrix(std::move(uniformMatrix))
    , m_trapdoorPair(std::move(trapdoorPair))
{ }

std::unique_ptr<MatrixDCRTPoly> RLWETrapdoorResultDRCTPoly::GetUniformMatrix() const
{
    return std::make_unique<MatrixDCRTPoly>(m_uniformMatrix);
}

std::unique_ptr<RLWETrapdoorPairDRCTPoly> RLWETrapdoorResultDRCTPoly::GetTrapdoorPair() const
{
    return std::make_unique<RLWETrapdoorPairDRCTPoly>(RLWETrapdoorPair(m_trapdoorPair));
}

std::unique_ptr<RLWETrapdoorResultDRCTPoly> DCRTPolyTrapdoorGen(
    const ILDCRTParamsWrap& params,
    double stddev,
    int64_t base,
    bool balanced)
{
    auto result = lbcrypto::RLWETrapdoorUtility<lbcrypto::DCRTPoly>::TrapdoorGen(
        params.GetRef(),
        stddev,
        base,
        balanced
    );
    return std::make_unique<RLWETrapdoorResultDRCTPoly>(
        std::move(result.first),
        std::move(result.second)
    );
}

} // openfhe