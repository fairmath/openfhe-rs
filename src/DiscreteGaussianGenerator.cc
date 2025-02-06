#include "DiscreteGaussianGenerator.h"

namespace openfhe {

DiscreteGaussianGeneratorDCRTPoly::DiscreteGaussianGeneratorDCRTPoly(
    const std::shared_ptr<DiscreteGaussianGeneratorImpl>& dgg) noexcept
    : m_dgg(dgg) {}

std::unique_ptr<DiscreteGaussianGeneratorDCRTPoly> GenDiscreteGaussianGenerator(double stddev) {
    auto dgg = std::make_shared<DiscreteGaussianGeneratorImpl>(stddev);
    return std::make_unique<DiscreteGaussianGeneratorDCRTPoly>(dgg);
}

} // namespace openfhe