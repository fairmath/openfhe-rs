#include "Matrix.h"

namespace openfhe
{

MatrixDCRTPoly::MatrixDCRTPoly(const Matrix& matrix)
    : m_matrix(matrix)
{ }

size_t MatrixDCRTPoly::GetRows() const noexcept
{
    return m_matrix.GetRows();
}

size_t MatrixDCRTPoly::GetCols() const noexcept
{
    return m_matrix.GetCols();
}

} // openfhe 