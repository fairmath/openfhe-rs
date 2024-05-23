#pragma once

#include "openfhe/pke/scheme/gen-cryptocontext-params.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns-params.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns-params.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns-params.h"

namespace openfhe
{

using SCHEME = lbcrypto::SCHEME;
using SecretKeyDist = lbcrypto::SecretKeyDist;
using ProxyReEncryptionMode = lbcrypto::ProxyReEncryptionMode;
using MultipartyMode = lbcrypto::MultipartyMode;
using ExecutionMode = lbcrypto::ExecutionMode;
using DecryptionNoiseMode = lbcrypto::DecryptionNoiseMode;
using KeySwitchTechnique = lbcrypto::KeySwitchTechnique;
using ScalingTechnique = lbcrypto::ScalingTechnique;
using SecurityLevel = lbcrypto::SecurityLevel;
using EncryptionTechnique = lbcrypto::EncryptionTechnique;
using MultiplicationTechnique = lbcrypto::MultiplicationTechnique;
using COMPRESSION_LEVEL = lbcrypto::COMPRESSION_LEVEL;

using Params = lbcrypto::Params;
using ParamsBFVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBFVRNS>;
using ParamsBGVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS>;
using ParamsCKKSRNS = lbcrypto::CCParams<lbcrypto::CryptoContextCKKSRNS>;

[[nodiscard]] std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme);
[[nodiscard]] std::unique_ptr<Params> GetParamsByVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS();
[[nodiscard]] std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS();
[[nodiscard]] std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS();
[[nodiscard]] std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(
    const std::vector<std::string>& vals);

} // openfhe
