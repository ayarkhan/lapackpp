#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    float* A, int64_t lda,
    float* S,
    float* U, int64_t ldu,
    float* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_sgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_sgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    double* A, int64_t lda,
    double* S,
    double* U, int64_t ldu,
    double* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_dgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_dgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    std::complex<float>* A, int64_t lda,
    float* S,
    std::complex<float>* U, int64_t ldu,
    std::complex<float>* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1] = { 0 };
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_cgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    if (lrwork_ == 0) {
        // if query doesn't work, this is from documentation
        blas_int mx = max( m, n );
        blas_int mn = min( m, n );
        if (jobz == lapack::Job::NoVec) {
            lrwork_ = 7*mn;  // LAPACK > 3.6 needs only 5*mn
        }
        else {
            lrwork_ = max( 5*mn*mn + 5*mn, 2*mx*mn + 2*mn*mn + mn );
        }
        lrwork_ = max( 1, lrwork_ );
    }

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( lrwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_cgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    std::complex<double>* A, int64_t lda,
    double* S,
    std::complex<double>* U, int64_t ldu,
    std::complex<double>* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1] = { 0 };
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_zgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    if (lrwork_ == 0) {
        // if query doesn't work, this is from documentation
        blas_int mx = max( m, n );
        blas_int mn = min( m, n );
        if (jobz == lapack::Job::NoVec) {
            lrwork_ = 7*mn;  // LAPACK > 3.6 needs only 5*mn
        }
        else {
            lrwork_ = max( 5*mn*mn + 5*mn, 2*mx*mn + 2*mn*mn + mn );
        }
        lrwork_ = max( 1, lrwork_ );
    }

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( lrwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_zgesdd( &jobz_, &m_, &n_, A, &lda_, S, U, &ldu_, VT, &ldvt_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack