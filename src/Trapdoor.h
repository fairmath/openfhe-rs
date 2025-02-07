#pragma once
#include "Params.h"
#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/core/math/matrix.h"
#include "openfhe/core/lattice/trapdoor.h"

namespace openfhe
{

using Matrix = lbcrypto::Matrix<lbcrypto::DCRTPoly>;   
using RLWETrapdoorPair = lbcrypto::RLWETrapdoorPair<lbcrypto::DCRTPoly>;

struct TrapdoorOutput
{
    Matrix m;
    RLWETrapdoorPair tp;
};


// Generator functions
[[nodiscard]] std::unique_ptr<TrapdoorOutput> DCRTPolyTrapdoorGen(
    const ILDCRTParams& params,
    double stddev,
    int64_t base,
    bool balanced);
} // openfhe