#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/core/lattice/trapdoor.h"

namespace openfhe
{

// class PrivateKeyDCRTPoly;
// class PublicKeyDCRTPoly;

using RLWETrapdoorPair = lbcrypto::RLWETrapdoorPair<lbcrypto::DCRTPoly>;
// using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
// using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;

class RLWETrapdoorPairDRCTPoly final
{
    RLWETrapdoorPair m_trapdoorPair;
public:
    RLWETrapdoorPairDRCTPoly(RLWETrapdoorPair&& rlweTrapdoorPair) noexcept;
    RLWETrapdoorPairDRCTPoly(const RLWETrapdoorPairDRCTPoly&) = delete;
    RLWETrapdoorPairDRCTPoly(RLWETrapdoorPairDRCTPoly&&) = delete;
    RLWETrapdoorPairDRCTPoly& operator=(const RLWETrapdoorPairDRCTPoly&) = delete;
    RLWETrapdoorPairDRCTPoly& operator=(RLWETrapdoorPairDRCTPoly&&) = delete;

    // [[nodiscard]] std::unique_ptr<Matrix<DCRTPoly>> GetMatrixR() const;
    // [[nodiscard]] std::unique_ptr<Matrix<DCRTPoly>> GetMatrixE() const;
};

} // openfhe
