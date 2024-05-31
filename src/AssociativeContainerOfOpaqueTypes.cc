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
    std::map<uint32_t, std::shared_ptr<EvalKeyImpl>> indexToEvalKeyDCRTPolyMap)
    : m_indexToEvalKeyDCRTPolyMap(std::move(indexToEvalKeyDCRTPolyMap))
{ }
const std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>& MapFromIndexToEvalKey::GetInternal() const
{
    return m_indexToEvalKeyDCRTPolyMap;
}

} // openfhe
