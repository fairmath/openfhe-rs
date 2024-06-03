#include "AssociativeContainerOfOpaqueTypes.h"

namespace openfhe
{

UnorderedMapFromIndexToDCRTPoly::UnorderedMapFromIndexToDCRTPoly(
    std::unordered_map<uint32_t, DCRTPoly> indexToDCRTPolyUnorderedMap)
    : m_indexToDCRTPolyUnorderedMap(std::move(indexToDCRTPolyUnorderedMap))
{ }
std::unordered_map<uint32_t, DCRTPoly>& UnorderedMapFromIndexToDCRTPoly::GetInternal()
{
    return m_indexToDCRTPolyUnorderedMap;
}

MapFromIndexToEvalKey::MapFromIndexToEvalKey(
    const std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>
    sharedPtrToindexToEvalKeyDCRTPolyMap)
    : m_sharedPtrToindexToEvalKeyDCRTPolyMap(sharedPtrToindexToEvalKeyDCRTPolyMap)
{ }
const std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>&
    MapFromIndexToEvalKey::GetInternalMap() const
{
    return *m_sharedPtrToindexToEvalKeyDCRTPolyMap;
}
std::shared_ptr<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>
    MapFromIndexToEvalKey::GetInternal() const
{
    return m_sharedPtrToindexToEvalKeyDCRTPolyMap;
}

} // openfhe
