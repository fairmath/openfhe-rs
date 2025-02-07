#include "Trapdoor.h"
#include "openfhe/core/lattice/trapdoor.h"

namespace openfhe
{

std::unique_ptr<TrapdoorOutput> DCRTPolyTrapdoorGen(
    const ILDCRTParams& params,
    double stddev,
    int64_t base,
    bool balanced)
{

    std::shared_ptr<ILDCRTParams> params_ptr = std::make_shared<ILDCRTParams>(params);

    auto result = lbcrypto::RLWETrapdoorUtility<lbcrypto::DCRTPoly>::TrapdoorGen(
        params_ptr,
        stddev,
        base,
        balanced
    );

    return std::make_unique<TrapdoorOutput>(TrapdoorOutput{
        std::move(result.first),
        std::move(result.second)
    });
}

} // openfhe 