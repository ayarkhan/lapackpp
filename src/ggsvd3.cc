#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION_MAJOR >= 3 && LAPACK_VERSION_MINOR >= 6  // >= 3.6

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::JobU jobu, lapack::JobV jobv, lapack::JobQ jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    float* A, int64_t lda,
    float* B, int64_t ldb,
    float* ALPHA,
    float* BETA,
    float* U, int64_t ldu,
    float* V, int64_t ldv,
    float* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(p) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldq) > std::numeric_limits<blas_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = jobv2char( jobv );
    char jobq_ = jobq2char( jobq );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int p_ = (blas_int) p;
    blas_int k_ = (blas_int) *k;
    blas_int l_ = (blas_int) *l;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldv_ = (blas_int) ldv;
    blas_int ldq_ = (blas_int) ldq;
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_sggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< blas_int > iwork( (n) );

    LAPACK_sggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::JobU jobu, lapack::JobV jobv, lapack::JobQ jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    double* A, int64_t lda,
    double* B, int64_t ldb,
    double* ALPHA,
    double* BETA,
    double* U, int64_t ldu,
    double* V, int64_t ldv,
    double* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(p) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldq) > std::numeric_limits<blas_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = jobv2char( jobv );
    char jobq_ = jobq2char( jobq );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int p_ = (blas_int) p;
    blas_int k_ = (blas_int) *k;
    blas_int l_ = (blas_int) *l;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldv_ = (blas_int) ldv;
    blas_int ldq_ = (blas_int) ldq;
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_dggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< blas_int > iwork( (n) );

    LAPACK_dggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::JobU jobu, lapack::JobV jobv, lapack::JobQ jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb,
    float* ALPHA,
    float* BETA,
    std::complex<float>* U, int64_t ldu,
    std::complex<float>* V, int64_t ldv,
    std::complex<float>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(p) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldq) > std::numeric_limits<blas_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = jobv2char( jobv );
    char jobq_ = jobq2char( jobq );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int p_ = (blas_int) p;
    blas_int k_ = (blas_int) *k;
    blas_int l_ = (blas_int) *l;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldv_ = (blas_int) ldv;
    blas_int ldq_ = (blas_int) ldq;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_cggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( (2*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_cggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::JobU jobu, lapack::JobV jobv, lapack::JobQ jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb,
    double* ALPHA,
    double* BETA,
    std::complex<double>* U, int64_t ldu,
    std::complex<double>* V, int64_t ldv,
    std::complex<double>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(p) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldq) > std::numeric_limits<blas_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = jobv2char( jobv );
    char jobq_ = jobq2char( jobq );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int p_ = (blas_int) p;
    blas_int k_ = (blas_int) *k;
    blas_int l_ = (blas_int) *l;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldv_ = (blas_int) ldv;
    blas_int ldq_ = (blas_int) ldq;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_zggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( (2*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_zggsvd3( &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_, A, &lda_, B, &ldb_, ALPHA, BETA, U, &ldu_, V, &ldv_, Q, &ldq_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.6