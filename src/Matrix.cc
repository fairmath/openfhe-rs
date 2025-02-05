#include "Matrix.h"

namespace openfhe
{

MatrixDCRTPoly::MatrixDCRTPoly(Matrix&& matrix) noexcept
    : m_matrix(std::move(matrix))
{ }

} // openfhe 