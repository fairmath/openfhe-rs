#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/core/lattice/trapdoor.h"
#include "Matrix.h"
#include "DCRTPoly.h"

namespace openfhe
{

class MatrixDCRTPoly;

using RLWETrapdoorPair = lbcrypto::RLWETrapdoorPair<lbcrypto::DCRTPoly>;

class RLWETrapdoorPairDRCTPoly final
{
    RLWETrapdoorPair m_trapdoorPair;
public:
    RLWETrapdoorPairDRCTPoly(RLWETrapdoorPair&& rlweTrapdoorPair) noexcept;
    RLWETrapdoorPairDRCTPoly(const RLWETrapdoorPairDRCTPoly&) = delete;
    RLWETrapdoorPairDRCTPoly(RLWETrapdoorPairDRCTPoly&&) = delete;
    RLWETrapdoorPairDRCTPoly& operator=(const RLWETrapdoorPairDRCTPoly&) = delete;
    RLWETrapdoorPairDRCTPoly& operator=(RLWETrapdoorPairDRCTPoly&&) = delete;

    [[nodiscard]] std::unique_ptr<MatrixDCRTPoly> GetMatrixR() const;
    [[nodiscard]] std::unique_ptr<MatrixDCRTPoly> GetMatrixE() const;

};

[[nodiscard]] std::unique_ptr<RLWETrapdoorPairDRCTPoly> DCRTPolyTrapdoorGen(
    const DCRTPolyParams& params,
    double stddev,
    int64_t base = 2,
    bool balanced = false);
} // openfhe
