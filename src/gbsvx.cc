#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gbsv
int64_t gbsvx(
    lapack::Factored fact, lapack::Op trans, int64_t n, int64_t kl, int64_t ku, int64_t nrhs,
    float* AB, int64_t ldab,
    float* AFB, int64_t ldafb,
    int64_t* ipiv,
    lapack::Equed* equed,
    float* R,
    float* C,
    float* B, int64_t ldb,
    float* X, int64_t ldx,
    float* rcond,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kl) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ku) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldafb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char trans_ = op2char( trans );
    char equed_ = equed2char( *equed );
    blas_int n_ = (blas_int) n;
    blas_int kl_ = (blas_int) kl;
    blas_int ku_ = (blas_int) ku;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldafb_ = (blas_int) ldafb;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_sgbsvx( &fact_, &trans_, &n_, &kl_, &ku_, &nrhs_, AB, &ldab_,
                   AFB, &ldafb_, ipiv_ptr, &equed_, R, C, B, &ldb_, X, &ldx_,
                   rcond, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *equed = char2equed( equed_ );
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gbsv
int64_t gbsvx(
    lapack::Factored fact, lapack::Op trans, int64_t n, int64_t kl, int64_t ku, int64_t nrhs,
    double* AB, int64_t ldab,
    double* AFB, int64_t ldafb,
    int64_t* ipiv,
    lapack::Equed* equed,
    double* R,
    double* C,
    double* B, int64_t ldb,
    double* X, int64_t ldx,
    double* rcond,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kl) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ku) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldafb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char trans_ = op2char( trans );
    char equed_ = equed2char( *equed );
    blas_int n_ = (blas_int) n;
    blas_int kl_ = (blas_int) kl;
    blas_int ku_ = (blas_int) ku;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldafb_ = (blas_int) ldafb;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_dgbsvx( &fact_, &trans_, &n_, &kl_, &ku_, &nrhs_, AB, &ldab_,
                   AFB, &ldafb_, ipiv_ptr, &equed_, R, C, B, &ldb_, X, &ldx_,
                   rcond, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *equed = char2equed( equed_ );
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gbsv
int64_t gbsvx(
    lapack::Factored fact, lapack::Op trans, int64_t n, int64_t kl, int64_t ku, int64_t nrhs,
    std::complex<float>* AB, int64_t ldab,
    std::complex<float>* AFB, int64_t ldafb,
    int64_t* ipiv,
    lapack::Equed* equed,
    float* R,
    float* C,
    std::complex<float>* B, int64_t ldb,
    std::complex<float>* X, int64_t ldx,
    float* rcond,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kl) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ku) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldafb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char trans_ = op2char( trans );
    char equed_ = equed2char( *equed );
    blas_int n_ = (blas_int) n;
    blas_int kl_ = (blas_int) kl;
    blas_int ku_ = (blas_int) ku;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldafb_ = (blas_int) ldafb;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (2*n) );
    std::vector< float > rwork( (n) );

    LAPACK_cgbsvx( &fact_, &trans_, &n_, &kl_, &ku_, &nrhs_, AB, &ldab_,
                   AFB, &ldafb_, ipiv_ptr, &equed_, R, C, B, &ldb_, X, &ldx_,
                   rcond, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *equed = char2equed( equed_ );
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// Uses the LU factorization to compute the solution to a
/// system of linear equations
///     \f$ A   X = B, \f$
///     \f$ A^T X = B, \f$ or
///     \f$ A^H X = B, \f$
/// where A is a band matrix of order n with kl subdiagonals and ku
/// superdiagonals, and X and B are n-by-nrhs matrices.
///
/// Error bounds on the solution and a condition estimate are also
/// provided.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] fact
///     Whether or not the factored form of the matrix A is
///     supplied on entry, and if not, whether the matrix A should be
///     equilibrated before it is factored.
///     - lapack::Factored::Factored:
///         On entry, AFB and ipiv contain the factored form of A.
///         If equed != None, the matrix A has been
///         equilibrated with scaling factors given by R and C.
///         AB, AFB, and ipiv are not modified.
///
///     - lapack::Factored::NotFactored:
///         The matrix A will be copied to AFB and factored.
///
///     - lapack::Factored::Equilibrate:
///         The matrix A will be equilibrated if necessary, then
///         copied to AFB and factored.
///
/// @param[in] trans
///     The form of the system of equations:
///     - lapack::Op::NoTrans:   \f$ A   X = B \f$ (No transpose)
///     - lapack::Op::Trans:     \f$ A^T X = B \f$ (Transpose)
///     - lapack::Op::ConjTrans: \f$ A^H X = B \f$ (Conjugate transpose)
///
/// @param[in] n
///     The number of linear equations, i.e., the order of the
///     matrix A. n >= 0.
///
/// @param[in] kl
///     The number of subdiagonals within the band of A. kl >= 0.
///
/// @param[in] ku
///     The number of superdiagonals within the band of A. ku >= 0.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrices B and X. nrhs >= 0.
///
/// @param[in,out] AB
///     The kl+ku+1-by-n matrix AB, stored in an ldab-by-n array.
///     On entry, the matrix A in band storage, in rows 1 to kl+ku+1.
///     The j-th column of A is stored in the j-th column of the
///     array AB as follows:
///     \n
///     AB(ku+1+i-j,j) = A(i,j) for max(1,j-ku) <= i <= min(n,j+kl)
///     \n
///     - If fact = Factored and equed != None,
///     then A must have been equilibrated by the scaling
///     factors in R and/or C.
///
///     - AB is not modified if fact = Factored or NotFactored,
///     or if fact = Equilibrate and equed = None on exit.
///
///     - On exit, if equed != None, A is scaled as follows:
///       - equed = Row:  \f$ A := \text{diag}(R) \; A \f$
///       - equed = Col:  \f$ A := A \; \text{diag}(C) \f$
///       - equed = Both: \f$ A := \text{diag}(R) \; A \; \text{diag}(C). \f$
///
/// @param[in] ldab
///     The leading dimension of the array AB. ldab >= kl+ku+1.
///
/// @param[in,out] AFB
///     The 2*kl+ku+1-by-n matrix AFB, stored in an ldafb-by-n array.
///     - If fact = Factored, then AFB is an input argument and on entry
///     contains details of the LU factorization of the band matrix
///     A, as computed by `lapack::gbtrf`. U is stored as an upper triangular
///     band matrix with kl+ku superdiagonals in rows 1 to kl+ku+1,
///     and the multipliers used during the factorization are stored
///     in rows kl+ku+2 to 2*kl+ku+1.
///
///     - If equed != None, then AFB is
///     the factored form of the equilibrated matrix A.
///
///     - If fact = NotFactored, then AFB is an output argument and on exit
///     returns details of the LU factorization of A.
///
///     - If fact = Equilibrate, then AFB is an output argument and on exit
///     returns details of the LU factorization of the equilibrated
///     matrix A (see the description of AB for the form of the
///     equilibrated matrix).
///
/// @param[in] ldafb
///     The leading dimension of the array AFB. ldafb >= 2*kl+ku+1.
///
/// @param[in,out] ipiv
///     The vector ipiv of length n.
///     - If fact = Factored, then ipiv is an input argument and on entry
///     contains the pivot indices from the factorization \f$ A = P L U \f$
///     as computed by `lapack::gbtrf`; row i of the matrix was interchanged
///     with row ipiv(i).
///
///     - If fact = NotFactored, then ipiv is an output argument and on exit
///     contains the pivot indices from the factorization \f$ A = P L U \f$
///     of the original matrix A.
///
///     - If fact = Equilibrate, then ipiv is an output argument and on exit
///     contains the pivot indices from the factorization \f$ A = P L U \f$
///     of the equilibrated matrix A.
///
/// @param[in,out] equed
///     The form of equilibration that was done:
///     - lapack::Equed::None:
///         No equilibration (always true if fact = NotFactored).
///     - lapack::Equed::Row:
///         Row equilibration, i.e., A has been premultiplied by diag(R).
///     - lapack::Equed::Col:
///         Column equilibration, i.e., A has been postmultiplied by diag(C).
///     - lapack::Equed::Both:
///         Both row and column equilibration, i.e.,
///         A has been replaced by \f$ \text{diag}(R) \; A \; \text{diag}(C). \f$
///     \n
///     equed is an input argument if fact = Factored; otherwise, it is an
///     output argument.
///
/// @param[in,out] R
///     The vector R of length n.
///     The row scale factors for A.
///     - If equed = Row or Both, A is multiplied on the left by diag(R);
///     - if equed = None or Col, R is not accessed.
///
///     - If fact = Factored, R is an input argument;
///     - otherwise, R is an output argument.
///
///     - If fact = Factored and equed = Row or Both,
///     each element of R must be positive.
///
/// @param[in,out] C
///     The vector C of length n.
///     The column scale factors for A.
///     - If equed = Col or Both, A is multiplied on the right by diag(C);
///     - if equed = None or Row, C is not accessed.
///
///     - If fact = Factored, C is an input argument;
///     - otherwise, C is an output argument.
///
///     - If fact = Factored and equed = Col or Both,
///     each element of C must be positive.
///
/// @param[in,out] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     On entry, the right hand side matrix B.
///     On exit,
///     - if equed = None, B is not modified;
///     - if trans = NoTrans and equed = Row or Both, B is overwritten by
///     \f$ \text{diag}(R) \; B; \f$
///     - if trans = Trans or ConjTrans and equed = Col or Both, B is
///     overwritten by \f$ \text{diag}(C) \; B. \f$
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @param[out] X
///     The n-by-nrhs matrix X, stored in an ldx-by-nrhs array.
///     If successful or return value = n+1, the n-by-nrhs solution matrix X
///     to the original system of equations. Note that A and B are
///     modified on exit if equed != None, and the solution to the
///     equilibrated system is \f$ \text{diag}(C)^{-1} X \f$ if trans = NoTrans and
///     equed = Col or Both, or \f$ \text{diag}(R)^{-1} X \f$ if trans = Trans or ConjTrans
///     and equed = Row or Both.
///
/// @param[in] ldx
///     The leading dimension of the array X. ldx >= max(1,n).
///
/// @param[out] rcond
///     The estimate of the reciprocal condition number of the matrix
///     A after equilibration (if done). If rcond is less than the
///     machine precision (in particular, if rcond = 0), the matrix
///     is singular to working precision. This condition is
///     indicated by a return code of return value > 0.
///
/// @param[out] ferr
///     The vector ferr of length nrhs.
///     The estimated forward error bound for each solution vector
///     X(j) (the j-th column of the solution matrix X).
///     If XTRUE is the true solution corresponding to X(j), ferr(j)
///     is an estimated upper bound for the magnitude of the largest
///     element in (X(j) - XTRUE) divided by the magnitude of the
///     largest element in X(j). The estimate is as reliable as
///     the estimate for rcond, and is almost always a slight
///     overestimate of the true error.
///
/// @param[out] berr
///     The vector berr of length nrhs.
///     The componentwise relative backward error of each solution
///     vector X(j) (i.e., the smallest relative change in
///     any element of A or B that makes X(j) an exact solution).
///
/// @retval = 0: successful exit
/// @retval > 0 and <= n: if return value = i, then U(i,i) is exactly zero.
///     The factorization has
///     been completed, but the factor U is exactly
///     singular, so the solution and error bounds
///     could not be computed. rcond = 0 is returned.
/// @retval = n+1: U is nonsingular, but rcond is less than machine
///     precision, meaning that the matrix is singular
///     to working precision. Nevertheless, the
///     solution and error bounds are computed because
///     there are a number of situations where the
///     computed solution can be more accurate than the
///     value of rcond would suggest.
///
/// @ingroup gbsv
int64_t gbsvx(
    lapack::Factored fact, lapack::Op trans, int64_t n, int64_t kl, int64_t ku, int64_t nrhs,
    std::complex<double>* AB, int64_t ldab,
    std::complex<double>* AFB, int64_t ldafb,
    int64_t* ipiv,
    lapack::Equed* equed,
    double* R,
    double* C,
    std::complex<double>* B, int64_t ldb,
    std::complex<double>* X, int64_t ldx,
    double* rcond,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kl) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ku) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldafb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char trans_ = op2char( trans );
    char equed_ = equed2char( *equed );
    blas_int n_ = (blas_int) n;
    blas_int kl_ = (blas_int) kl;
    blas_int ku_ = (blas_int) ku;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldafb_ = (blas_int) ldafb;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (2*n) );
    std::vector< double > rwork( (n) );

    LAPACK_zgbsvx( &fact_, &trans_, &n_, &kl_, &ku_, &nrhs_, AB, &ldab_,
                   AFB, &ldafb_, ipiv_ptr, &equed_, R, C, B, &ldb_, X, &ldx_,
                   rcond, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *equed = char2equed( equed_ );
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

}  // namespace lapack