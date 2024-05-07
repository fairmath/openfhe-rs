#include "openfhe_rs_dev/src/main.rs.h"

namespace openfhe_rs_dev
{
std::unique_ptr<VectorOfComplexNumbers> GenVectorOfComplexNumbers(const std::vector<ComplexPair>& vals)
{
    std::vector<std::complex<double>> result;
    result.reserve(vals.size());
    for (const ComplexPair& p : vals)
    {
        result.emplace_back(p.re, p.im);
    }
    return std::make_unique<VectorOfComplexNumbers>(std::move(result));
}
std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme)
{
    return std::make_unique<Params>(scheme);
}
std::unique_ptr<Params> GetParamsByVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<Params>(vals);
}
std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS()
{
    return std::make_unique<ParamsBFVRNS>();
}
std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsBFVRNS>(vals);
}
std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS()
{
    return std::make_unique<ParamsBGVRNS>();
}
std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsBGVRNS>(vals);
}
std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS()
{
    return std::make_unique<ParamsCKKSRNS>();
}
std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsCKKSRNS>(vals);
}
std::unique_ptr<Plaintext> GenEmptyPlainText()
{
    return std::make_unique<Plaintext>();
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(const ParamsBFVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(const ParamsBGVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(const ParamsCKKSRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
} // openfhe_rs_dev

