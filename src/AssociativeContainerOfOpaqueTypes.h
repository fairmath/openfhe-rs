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

class UnorderedMapFromIndexToDCRTPoly final
{
    std::unordered_map<uint32_t, lbcrypto::DCRTPoly> m_indexToDCRTPolyUnorderedMap;
public:
    UnorderedMapFromIndexToDCRTPoly(
        std::unordered_map<uint32_t, lbcrypto::DCRTPoly>&& indexToDCRTPolyUnorderedMap) noexcept;
    [[nodiscard]] std::unordered_map<uint32_t, lbcrypto::DCRTPoly>& GetInternal() noexcept;
};

using EvalKeyImpl = lbcrypto::EvalKeyImpl<lbcrypto::DCRTPoly>;

class MapFromIndexToEvalKey final
{
    std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>
        m_sharedPtrToindexToEvalKeyDCRTPolyMap;
public:
    MapFromIndexToEvalKey(std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>&&
        indexToEvalKeyDCRTPolyMap) noexcept;
    [[nodiscard]] const std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>&
        GetInternalMap() const noexcept;
    [[nodiscard]] std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>
        GetInternal() const noexcept;
};

class MapFromStringToVectorOfEvalKeys final
{
    std::map<std::string, std::vector<std::shared_ptr<EvalKeyImpl>>> m_stringToVectorOfEvalKeysMap;
public:
    explicit MapFromStringToVectorOfEvalKeys(
        std::map<std::string, std::vector<std::shared_ptr<EvalKeyImpl>>>
        stringToVectorOfEvalKeysMap);
};

class MapFromStringToMapFromIndexToEvalKey final
{
    std::map<std::string, std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>>
        m_stringToMapFromIndexToEvalKeyMap;
public:
    explicit MapFromStringToMapFromIndexToEvalKey(
        std::map<std::string, std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>>
        stringToMapFromIndexToEvalKeyMap);
};

} // openfhe
