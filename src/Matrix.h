#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/core/math/matrix.h"

namespace openfhe
{

using Matrix = lbcrypto::Matrix<lbcrypto::DCRTPoly>;

class MatrixDCRTPoly final
{
    Matrix m_matrix;
public:
    MatrixDCRTPoly(const Matrix& matrix);
    MatrixDCRTPoly(const MatrixDCRTPoly&) = delete;
    MatrixDCRTPoly(MatrixDCRTPoly&&) = delete;
    MatrixDCRTPoly& operator=(const MatrixDCRTPoly&) = delete;
    MatrixDCRTPoly& operator=(MatrixDCRTPoly&&) = delete;
};
} // openfhe