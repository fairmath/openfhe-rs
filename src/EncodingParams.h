#pragma once

#include <memory>

namespace lbcrypto
{

class EncodingParamsImpl;

} // lbcrypto

namespace openfhe
{

using EncodingParamsImpl = lbcrypto::EncodingParamsImpl;

class EncodingParams final
{
    std::shared_ptr<EncodingParamsImpl> m_encodingParams;
public:
    EncodingParams(const std::shared_ptr<EncodingParamsImpl>& encodingParams) noexcept;
    EncodingParams(const EncodingParams&) = delete;
    EncodingParams(EncodingParams&&) = delete;
    EncodingParams& operator=(const EncodingParams&) = delete;
    EncodingParams& operator=(EncodingParams&&) = delete;

    [[nodiscard]] const std::shared_ptr<EncodingParamsImpl>& GetRef() const noexcept;
};

} // openfhe
