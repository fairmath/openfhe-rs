#include "Params.h"

namespace openfhe
{

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
std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(
    const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsCKKSRNS>(vals);
}

} // openfhe
