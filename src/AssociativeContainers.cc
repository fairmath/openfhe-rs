#include "AssociativeContainers.h"

namespace openfhe
{

MapFromIndexToEvalKey::MapFromIndexToEvalKey(
    std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>&&
    sharedPtrToindexToEvalKeyDCRTPolyMap) noexcept
    : m_sharedPtrToindexToEvalKeyDCRTPolyMap(std::move(sharedPtrToindexToEvalKeyDCRTPolyMap))
{ }
const std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>&
    MapFromIndexToEvalKey::GetRef() const noexcept
{
    return m_sharedPtrToindexToEvalKeyDCRTPolyMap;
}

MapFromStringToMapFromIndexToEvalKey::MapFromStringToMapFromIndexToEvalKey(
    std::map<std::string, std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>>
    stringToMapFromIndexToEvalKeyMap)
    : m_stringToMapFromIndexToEvalKeyMap(std::move(stringToMapFromIndexToEvalKeyMap))
{ }
MapFromStringToVectorOfEvalKeys::MapFromStringToVectorOfEvalKeys(
    std::map<std::string, std::vector<std::shared_ptr<EvalKeyImpl>>> stringToVectorOfEvalKeysMap)
    : m_stringToVectorOfEvalKeysMap(std::move(stringToVectorOfEvalKeysMap))
{ }

SetOfUints::SetOfUints(std::set<uint32_t>&& uintsSet) noexcept
    : m_uintsSet(std::move(uintsSet))
{ }
const std::set<uint32_t>& SetOfUints::GetRef() const noexcept
{
    return m_uintsSet;
}

UnorderedMapFromIndexToDCRTPoly::UnorderedMapFromIndexToDCRTPoly(
    std::unordered_map<uint32_t, lbcrypto::DCRTPoly>&& indexToDCRTPolyUnorderedMap) noexcept
    : m_indexToDCRTPolyUnorderedMap(std::move(indexToDCRTPolyUnorderedMap))
{ }
std::unordered_map<uint32_t, lbcrypto::DCRTPoly>&
    UnorderedMapFromIndexToDCRTPoly::GetRef() noexcept
{
    return m_indexToDCRTPolyUnorderedMap;
}

} // openfhe
