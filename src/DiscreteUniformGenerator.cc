#include "DiscreteUniformGenerator.h"

namespace openfhe {

std::unique_ptr<DiscreteUniformGeneratorDCRTPoly> DCRTPolyGenNullDiscreteUniformGenerator() {
    return std::make_unique<DiscreteUniformGeneratorDCRTPoly>();
}

} // openfhe 
