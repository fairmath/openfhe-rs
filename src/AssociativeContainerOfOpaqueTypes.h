#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/key/evalkey-fwd.h"

#include "EvalKey.h"

#include <cstdint>
#include <map>
#include <unordered_map>

// cxx currently does not support std::unordered_map and std::map

namespace openfhe
{

using DCRTPoly = lbcrypto::DCRTPoly;

class UnorderedMapFromIndexToDCRTPoly final
{
    std::unordered_map<uint32_t, DCRTPoly> m_indexToDCRTPolyUnorderedMap;
public:
    explicit UnorderedMapFromIndexToDCRTPoly(
        std::unordered_map<uint32_t, DCRTPoly> indexToDCRTPolyUnorderedMap);
    [[nodiscard]] std::unordered_map<uint32_t, DCRTPoly>& GetInternal();
};

using EvalKeyImpl = lbcrypto::EvalKeyImpl<lbcrypto::DCRTPoly>;

class MapFromIndexToEvalKey final
{
    std::map<uint32_t, std::shared_ptr<EvalKeyImpl>> m_indexToEvalKeyDCRTPolyMap;
public:
    explicit MapFromIndexToEvalKey(std::map<uint32_t,
        std::shared_ptr<EvalKeyImpl>> indexToEvalKeyDCRTPolyMap);
    [[nodiscard]] const std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>& GetInternal() const;
};

} // openfhe
