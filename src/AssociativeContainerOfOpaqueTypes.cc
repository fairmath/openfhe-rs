#include "AssociativeContainerOfOpaqueTypes.h"

namespace openfhe
{

UnorderedMapFromIndexToDCRTPoly::UnorderedMapFromIndexToDCRTPoly(
    std::unordered_map<uint32_t, lbcrypto::DCRTPoly>&& indexToDCRTPolyUnorderedMap) noexcept
    : m_indexToDCRTPolyUnorderedMap(std::move(indexToDCRTPolyUnorderedMap))
{ }
std::unordered_map<uint32_t, lbcrypto::DCRTPoly>&
    UnorderedMapFromIndexToDCRTPoly::GetInternal() noexcept
{
    return m_indexToDCRTPolyUnorderedMap;
}

MapFromIndexToEvalKey::MapFromIndexToEvalKey(
    std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>&&
    sharedPtrToindexToEvalKeyDCRTPolyMap) noexcept
    : m_sharedPtrToindexToEvalKeyDCRTPolyMap(std::move(sharedPtrToindexToEvalKeyDCRTPolyMap))
{ }
const std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>&
    MapFromIndexToEvalKey::GetInternalMap() const noexcept
{
    return *m_sharedPtrToindexToEvalKeyDCRTPolyMap;
}
std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>
    MapFromIndexToEvalKey::GetInternal() const noexcept
{
    return m_sharedPtrToindexToEvalKeyDCRTPolyMap;
}

MapFromStringToVectorOfEvalKeys::MapFromStringToVectorOfEvalKeys(
    std::map<std::string, std::vector<std::shared_ptr<EvalKeyImpl>>> stringToVectorOfEvalKeysMap)
    : m_stringToVectorOfEvalKeysMap(std::move(stringToVectorOfEvalKeysMap))
{ }

MapFromStringToMapFromIndexToEvalKey::MapFromStringToMapFromIndexToEvalKey(
    std::map<std::string, std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>>
    stringToMapFromIndexToEvalKeyMap)
    : m_stringToMapFromIndexToEvalKeyMap(std::move(stringToMapFromIndexToEvalKeyMap))
{ }

} // openfhe
