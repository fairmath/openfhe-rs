#pragma once

#include "openfhe/core/math/discreteuniformgenerator.h"
#include "DCRTPoly.h"

namespace openfhe {

using DiscreteUniformGeneratorImpl = lbcrypto::DiscreteUniformGeneratorImpl<lbcrypto::DCRTPoly>;

class DiscreteUniformGeneratorDCRTPoly final {
    std::shared_ptr<DiscreteUniformGeneratorImpl> m_dug;
public:
    DiscreteUniformGeneratorDCRTPoly() = default;
    DiscreteUniformGeneratorDCRTPoly(const DiscreteUniformGeneratorDCRTPoly&) = delete;
    DiscreteUniformGeneratorDCRTPoly(DiscreteUniformGeneratorDCRTPoly&&) = delete;
    DiscreteUniformGeneratorDCRTPoly& operator=(const DiscreteUniformGeneratorDCRTPoly&) = delete;
    DiscreteUniformGeneratorDCRTPoly& operator=(DiscreteUniformGeneratorDCRTPoly&&) = delete;
};

// Generator functions
std::unique_ptr<DiscreteUniformGeneratorDCRTPoly> GenNullDiscreteUniformGenerator();

} // openfhe 