#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"

#include <vector>
#include <omp.h>

// -----------------------------------------------------------------------------
// simple overloaded wrappers around LAPACKE
static lapack_int LAPACKE_sytrs(
    char uplo, lapack_int n, lapack_int nrhs, float* A, lapack_int lda, lapack_int* ipiv, float* B, lapack_int ldb )
{
    return LAPACKE_ssytrs( LAPACK_COL_MAJOR, uplo, n, nrhs, A, lda, ipiv, B, ldb );
}

static lapack_int LAPACKE_sytrs(
    char uplo, lapack_int n, lapack_int nrhs, double* A, lapack_int lda, lapack_int* ipiv, double* B, lapack_int ldb )
{
    return LAPACKE_dsytrs( LAPACK_COL_MAJOR, uplo, n, nrhs, A, lda, ipiv, B, ldb );
}

static lapack_int LAPACKE_sytrs(
    char uplo, lapack_int n, lapack_int nrhs, std::complex<float>* A, lapack_int lda, lapack_int* ipiv, std::complex<float>* B, lapack_int ldb )
{
    return LAPACKE_csytrs( LAPACK_COL_MAJOR, uplo, n, nrhs, A, lda, ipiv, B, ldb );
}

static lapack_int LAPACKE_sytrs(
    char uplo, lapack_int n, lapack_int nrhs, std::complex<double>* A, lapack_int lda, lapack_int* ipiv, std::complex<double>* B, lapack_int ldb )
{
    return LAPACKE_zsytrs( LAPACK_COL_MAJOR, uplo, n, nrhs, A, lda, ipiv, B, ldb );
}

// -----------------------------------------------------------------------------

static lapack_int LAPACKE_sytrf(
    char uplo, lapack_int n, float* A, lapack_int lda, lapack_int* ipiv )
{
    return LAPACKE_ssytrf( LAPACK_COL_MAJOR, uplo, n, A, lda, ipiv );
}

static lapack_int LAPACKE_sytrf(
    char uplo, lapack_int n, double* A, lapack_int lda, lapack_int* ipiv )
{
    return LAPACKE_dsytrf( LAPACK_COL_MAJOR, uplo, n, A, lda, ipiv );
}

static lapack_int LAPACKE_sytrf(
    char uplo, lapack_int n, std::complex<float>* A, lapack_int lda, lapack_int* ipiv )
{
    return LAPACKE_csytrf( LAPACK_COL_MAJOR, uplo, n, A, lda, ipiv );
}

static lapack_int LAPACKE_sytrf(
    char uplo, lapack_int n, std::complex<double>* A, lapack_int lda, lapack_int* ipiv )
{
    return LAPACKE_zsytrf( LAPACK_COL_MAJOR, uplo, n, A, lda, ipiv );
}

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_sytrs_work( Params& params, bool run )
{
    using namespace blas;
    typedef typename traits< scalar_t >::real_t real_t;
    typedef long long lld;

    // get & mark input values
    lapack::Uplo uplo = params.uplo.value();
    int64_t n = params.dim.n();
    int64_t nrhs = params.nrhs.value();
    int64_t align = params.align.value();

    // mark non-standard output values
    params.ref_time.value();
    // params.ref_gflops.value();
    // params.gflops.value();

    if (! run)
        return;

    // ---------- setup
    int64_t lda = roundup( max( 1, n ), align );
    int64_t ldb = roundup( max( 1, n ), align );
    size_t size_A = (size_t) lda * n;
    size_t size_ipiv = (size_t) (n);
    size_t size_B = (size_t) ldb * nrhs;

    std::vector< scalar_t > A_tst( size_A );
    std::vector< scalar_t > A_ref( size_A );
    std::vector< int64_t > ipiv_tst( size_ipiv );
    std::vector< lapack_int > ipiv_ref( size_ipiv );
    std::vector< scalar_t > B_tst( size_B );
    std::vector< scalar_t > B_ref( size_B );

    int64_t idist = 1;
    int64_t iseed[4] = { 0, 1, 2, 3 };
    lapack::larnv( idist, iseed, A_tst.size(), &A_tst[0] );
    A_ref = A_tst;
    lapack::larnv( idist, iseed, B_tst.size(), &B_tst[0] );
    B_ref = B_tst;

    // ---------- factor before test
    int64_t info = lapack::sytrf( uplo, n, &A_tst[0], lda, &ipiv_tst[0] );
    if (info != 0) {
        fprintf( stderr, "lapack::sytrf returned error %lld\n", (lld) info );
    }

    // ---------- run test
    libtest::flush_cache( params.cache.value() );
    double time = omp_get_wtime();
    int64_t info_tst = lapack::sytrs( uplo, n, nrhs, &A_tst[0], lda, &ipiv_tst[0], &B_tst[0], ldb );
    time = omp_get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::sytrs returned error %lld\n", (lld) info_tst );
    }

    params.time.value() = time;
    // double gflop = lapack::Gflop< scalar_t >::sytrs( n, nrhs );
    // params.gflops.value() = gflop / time;

    if (params.ref.value() == 'y' || params.check.value() == 'y') {
        // ---------- factor
        int64_t info = LAPACKE_sytrf( uplo2char(uplo), n, &A_ref[0], lda, &ipiv_ref[0] );
        if (info != 0) {
            fprintf( stderr, "LAPACKE_sytrf returned error %lld\n", (lld) info );
        }
        // ---------- run reference
        libtest::flush_cache( params.cache.value() );
        time = omp_get_wtime();
        int64_t info_ref = LAPACKE_sytrs( uplo2char(uplo), n, nrhs, &A_ref[0], lda, &ipiv_ref[0], &B_ref[0], ldb );
        time = omp_get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_sytrs returned error %lld\n", (lld) info_ref );
        }

        params.ref_time.value() = time;
        // params.ref_gflops.value() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( B_tst, B_ref );
        params.error.value() = error;
        params.okay.value() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_sytrs( Params& params, bool run )
{
    switch (params.datatype.value()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_sytrs_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_sytrs_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_sytrs_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_sytrs_work< std::complex<double> >( params, run );
            break;
    }
}