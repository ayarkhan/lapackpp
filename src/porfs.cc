#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup posv_computational
int64_t porfs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    float const* A, int64_t lda,
    float const* AF, int64_t ldaf,
    float const* B, int64_t ldb,
    float* X, int64_t ldx,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_sporfs( &uplo_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, B, &ldb_, X, &ldx_, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup posv_computational
int64_t porfs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    double const* A, int64_t lda,
    double const* AF, int64_t ldaf,
    double const* B, int64_t ldb,
    double* X, int64_t ldx,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_dporfs( &uplo_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, B, &ldb_, X, &ldx_, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup posv_computational
int64_t porfs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<float> const* A, int64_t lda,
    std::complex<float> const* AF, int64_t ldaf,
    std::complex<float> const* B, int64_t ldb,
    std::complex<float>* X, int64_t ldx,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (2*n) );
    std::vector< float > rwork( (n) );

    LAPACK_cporfs( &uplo_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, B, &ldb_, X, &ldx_, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Improves the computed solution to a system of linear
/// equations when the coefficient matrix is Hermitian positive definite,
/// and provides error bounds and backward error estimates for the
/// solution.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] uplo
///     - lapack::Uplo::Upper: Upper triangle of A is stored;
///     - lapack::Uplo::Lower: Lower triangle of A is stored.
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrices B and X. nrhs >= 0.
///
/// @param[in] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     The Hermitian matrix A.
///     \n
///     If uplo = Upper, the leading n-by-n
///     upper triangular part of A contains the upper triangular part
///     of the matrix A, and the strictly lower triangular part of A
///     is not referenced.
///     \n
///     If uplo = Lower, the leading n-by-n lower
///     triangular part of A contains the lower triangular part of
///     the matrix A, and the strictly upper triangular part of A is
///     not referenced.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[in] AF
///     The n-by-n matrix AF, stored in an ldaf-by-n array.
///     The triangular factor U or L from the Cholesky factorization
///     \f$ A = U^H U \f$ or \f$ A = L L^H \f$, as computed by `lapack::potrf`.
///
/// @param[in] ldaf
///     The leading dimension of the array AF. ldaf >= max(1,n).
///
/// @param[in] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     The right hand side matrix B.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @param[in,out] X
///     The n-by-nrhs matrix X, stored in an ldx-by-nrhs array.
///     On entry, the solution matrix X, as computed by `lapack::potrs`.
///     On exit, the improved solution matrix X.
///
/// @param[in] ldx
///     The leading dimension of the array X. ldx >= max(1,n).
///
/// @param[out] ferr
///     The vector ferr of length nrhs.
///     The estimated forward error bound for each solution vector
///     X(j) (the j-th column of the solution matrix X).
///     If XTRUE is the true solution corresponding to X(j), ferr(j)
///     is an estimated upper bound for the magnitude of the largest
///     element in (X(j) - XTRUE) divided by the magnitude of the
///     largest element in X(j). The estimate is as reliable as
///     the estimate for RCOND, and is almost always a slight
///     overestimate of the true error.
///
/// @param[out] berr
///     The vector berr of length nrhs.
///     The componentwise relative backward error of each solution
///     vector X(j) (i.e., the smallest relative change in
///     any element of A or B that makes X(j) an exact solution).
///
/// @retval = 0: successful exit
///
/// @ingroup posv_computational
int64_t porfs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<double> const* A, int64_t lda,
    std::complex<double> const* AF, int64_t ldaf,
    std::complex<double> const* B, int64_t ldb,
    std::complex<double>* X, int64_t ldx,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (2*n) );
    std::vector< double > rwork( (n) );

    LAPACK_zporfs( &uplo_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, B, &ldb_, X, &ldx_, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
