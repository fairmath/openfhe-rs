#pragma once

#include "openfhe/core/math/discretegaussiangenerator.h"
#include "openfhe/core/math/discretegaussiangenerator-impl.h"
#include "DCRTPoly.h"


namespace openfhe
{

using DiscreteGaussianGeneratorImpl = lbcrypto::DiscreteGaussianGeneratorImpl<lbcrypto::DCRTPoly>;

class DiscreteGaussianGeneratorDCRTPoly final
{
    std::shared_ptr<DiscreteGaussianGeneratorImpl> m_dgg;
public:
    DiscreteGaussianGeneratorDCRTPoly() = default;
    DiscreteGaussianGeneratorDCRTPoly(const std::shared_ptr<DiscreteGaussianGeneratorImpl>& params) noexcept;
    DiscreteGaussianGeneratorDCRTPoly(const DiscreteGaussianGeneratorDCRTPoly&) = delete;
    DiscreteGaussianGeneratorDCRTPoly(DiscreteGaussianGeneratorDCRTPoly&&) = delete;
    DiscreteGaussianGeneratorDCRTPoly& operator=(const DiscreteGaussianGeneratorDCRTPoly&) = delete;
    DiscreteGaussianGeneratorDCRTPoly& operator=(DiscreteGaussianGeneratorDCRTPoly&&) = delete;
};

// Generator functions
[[nodiscard]] std::unique_ptr<DiscreteGaussianGeneratorDCRTPoly> GenDiscreteGaussianGenerator(double stddev);

} // openfhe 