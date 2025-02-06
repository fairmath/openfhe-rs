#include "DiscreteUniformGenerator.h"

namespace openfhe {

std::unique_ptr<DiscreteUniformGeneratorDCRTPoly> GenNullDiscreteUniformGenerator() {
    return std::make_unique<DiscreteUniformGeneratorDCRTPoly>();
}

} // openfhe 
