#include "Trapdoor.h"
#include "DCRTPoly.h"
#include "openfhe/core/lattice/trapdoor.h"
#include "openfhe/core/lattice/dgsampling.h"

namespace openfhe
{

std::unique_ptr<TrapdoorOutput> DCRTPolyTrapdoorGen(
    const ILDCRTParams& params,
    int64_t base,
    bool balanced)
{

    std::shared_ptr<ILDCRTParams> params_ptr = std::make_shared<ILDCRTParams>(params);

    auto result = lbcrypto::RLWETrapdoorUtility<lbcrypto::DCRTPoly>::TrapdoorGen(
        params_ptr,
        lbcrypto::SIGMA,
        base,
        balanced
    );

    return std::make_unique<TrapdoorOutput>(TrapdoorOutput{
        std::move(result.first),
        std::move(result.second)
    });
}

void DCRTPolyGaussSamp(size_t n, size_t k, base)
{
    DCRTPolyImpl::DggType dgg(lbcrypto::SIGMA);

    double c = (base + 1) * lbcrypto::SIGMA;
    double s = lbcrypto::SPECTRAL_BOUND(n, k, base);
    DCRTPolyImpl::DggType dggLargeSigma(sqrt(s * s - c * c));
}

// [x] n
// [x] k
// [ ] trapPair.first
// [ ] trapPair.second
// [ ] u
// [x] dgg 
// [x] dggLargeSigma
// [x] base

} // openfhe 