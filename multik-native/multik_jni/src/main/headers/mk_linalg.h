/*
 * Copyright 2020-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license.
 */

#ifndef CPP_CPP_LINALG_H_
#define CPP_CPP_LINALG_H_

#include "cblas.h"
#include "lapacke.h"
#include "algorithm"

void eigen_values(double *A, int n) {
  const char Nchar = 'N';
  double *eigReal = new double[n];
  double *eigImag = new double[n];
  const int lwork = 5 * n;
  double *work = new double[lwork];
  int info;
  double *lv, *rv;
  const int one = 1;
// перезаписывает матрицу
//  dgeev(&Nchar, &Nchar, &n, A, &n, eigReal, eigImag, nullptr, &one, nullptr, &one, work, &lwork, &info);

  delete[] eigReal;
  delete[] eigImag;
  delete[] work;
}

float vector_dot(int n, float *X, int incx, float *Y, int incy) {
  return cblas_sdot(n, X, incx, Y, incy);
}

double vector_dot(int n, double *X, int incx, double *Y, int incy) {
  return cblas_ddot(n, X, incx, Y, incy);
}

openblas_complex_float vector_dot_complex(int n, float *X, int incx, float *Y, int incy) {
  return cblas_cdotc(n, X, incx, Y, incy);
}

openblas_complex_double vector_dot_complex(int n, double *X, int incx, double *Y, int incy) {
  return cblas_zdotc(n, X, incx, Y, incy);
}

int solve_linear_system(int n, int nrhs, float *A, int lda, float *b, int ldb) {
  int ipiv[n];

  return LAPACKE_sgesv(LAPACK_ROW_MAJOR, n, nrhs, A, lda, ipiv, b, ldb);
}

int solve_linear_system(int n, int nrhs, double *A, int lda, double *b, int ldb) {
  int ipiv[n];

  return LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, A, lda, ipiv, b, ldb);
}

int solve_linear_system_complex(int n, int nrhs, float *A, int lda, float *B, int ldb) {
  int ipiv[n];

  lapack_complex_float *a = (lapack_complex_float *)A;
  lapack_complex_float *b = (lapack_complex_float *)B;

  return LAPACKE_cgesv(LAPACK_ROW_MAJOR, n, nrhs, a, lda, ipiv, b, ldb);
}

int solve_linear_system_complex(int n, int nrhs, double *A, int lda, double *B, int ldb) {
  int ipiv[n];

  lapack_complex_double *a = (lapack_complex_double *)A;
  lapack_complex_double *b = (lapack_complex_double *)B;

  return LAPACKE_zgesv(LAPACK_ROW_MAJOR, n, nrhs, a, lda, ipiv, b, ldb);
}

int inverse_matrix(int n, float *A, int lda) {
  int ipiv[n];

  LAPACKE_sgetrf(LAPACK_ROW_MAJOR, n, n, A, lda, ipiv);

  return LAPACKE_sgetri(LAPACK_ROW_MAJOR, n, A, lda, ipiv);
}

int inverse_matrix(int n, double *A, int lda) {
  int ipiv[n];

  LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, A, lda, ipiv);

  return LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, A, lda, ipiv);
}

int inverse_matrix_complex(int n, float *A, int lda) {
  int ipiv[n];

  lapack_complex_float *a = (lapack_complex_float *)A;

  LAPACKE_cgetrf(LAPACK_ROW_MAJOR, n, n, a, lda, ipiv);

  return LAPACKE_cgetri(LAPACK_ROW_MAJOR, n, a, lda, ipiv);
}

int inverse_matrix_complex(int n, double *A, int lda) {
  int ipiv[n];

  lapack_complex_double *a = (lapack_complex_double *)A;

  LAPACKE_zgetrf(LAPACK_ROW_MAJOR, n, n, a, lda, ipiv);

  return LAPACKE_zgetri(LAPACK_ROW_MAJOR, n, a, lda, ipiv);
}

int qr_matrix(int m, int n, float *AQ, int lda, float *R) {
  int mn = std::min(m, n);
  float tau[mn];

  int info = LAPACKE_sgeqrf(LAPACK_ROW_MAJOR, m, n, AQ, lda, tau);
  if (info != 0)
	return info;

  for (size_t row = 0; row < mn; ++row) {
	size_t index = (n + 1) * row;
	memcpy(R + index, AQ + index, (n - row) * sizeof(float));
  }

  return LAPACKE_sorgqr(LAPACK_ROW_MAJOR, m, mn, mn, AQ, lda, tau);
}

int qr_matrix(int m, int n, double *AQ, int lda, double *R) {
  int mn = std::min(m, n);
  double tau[mn];

  int info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, m, n, AQ, lda, tau);
  if (info != 0)
	return info;

  for (size_t row = 0; row < mn; ++row) {
	size_t index = (n + 1) * row;
	memcpy(R + index, AQ + index, (n - row) * sizeof(double));
  }

  return LAPACKE_dorgqr(LAPACK_ROW_MAJOR, m, mn, mn, AQ, lda, tau);
}

int qr_matrix_complex(int m, int n, float *AQ, int lda, float *R) {
  int mn = std::min(m, n);
  lapack_complex_float tau[mn];
  lapack_complex_float *aq = (lapack_complex_float *)AQ;
  lapack_complex_float *r = (lapack_complex_float *)R;

  int info = LAPACKE_cgeqrf(LAPACK_ROW_MAJOR, m, n, aq, lda, tau);
  if (info != 0)
	return info;

  for (size_t row = 0; row < mn; ++row) {
	size_t index = (n + 1) * row;
	memcpy(r + index, aq + index, (n - row) * sizeof(lapack_complex_float));
  }

  return LAPACKE_cungqr(LAPACK_ROW_MAJOR, m, mn, mn, aq, lda, tau);
}

int qr_matrix_complex(int m, int n, double *AQ, int lda, double *R) {
  int mn = std::min(m, n);
  lapack_complex_double tau[mn];
  lapack_complex_double *aq = (lapack_complex_double *)AQ;
  lapack_complex_double *r = (lapack_complex_double *)R;

  int info = LAPACKE_zgeqrf(LAPACK_ROW_MAJOR, m, n, aq, lda, tau);
  if (info != 0)
	return info;

  for (size_t row = 0; row < mn; ++row) {
	size_t index = (n + 1) * row;
	memcpy(r + index, aq + index, (n - row) * sizeof(lapack_complex_double));
  }

  return LAPACKE_zungqr(LAPACK_ROW_MAJOR, m, mn, mn, aq, lda, tau);
}

int plu_matrix(int m, int n, float *A, int lda, int *IPIV) {
  return LAPACKE_sgetrf(LAPACK_ROW_MAJOR, m, n, A, lda, IPIV);
}

int plu_matrix(int m, int n, double *A, int lda, int *IPIV) {
  return LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, n, A, lda, IPIV);
}

int plu_matrix_complex(int m, int n, float *A, int lda, int *IPIV) {
  lapack_complex_float *a = (lapack_complex_float *)A;
  return LAPACKE_cgetrf(LAPACK_ROW_MAJOR, m, n, a, lda, IPIV);
}

int plu_matrix_complex(int m, int n, double *A, int lda, int *IPIV) {
  lapack_complex_double *a = (lapack_complex_double *)A;
  return LAPACKE_zgetrf(LAPACK_ROW_MAJOR, m, n, a, lda, IPIV);
}

void matrix_dot(bool trans_a, int offsetA, float *A, int lda, int m, int n, int k,
				bool trans_b, int offsetB, float *B, int ldb, float *C) {
  float alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;
  CBLAS_TRANSPOSE transB;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;
  (trans_b) ? transB = CblasTrans : transB = CblasNoTrans;

  cblas_sgemm(CblasRowMajor, transA, transB, m, n, k, alpha, A + offsetA, lda, B + offsetB, ldb, beta, C, n);
}

void matrix_dot(bool trans_a, int offsetA, double *A, int lda, int m, int n, int k,
				bool trans_b, int offsetB, double *B, int ldb, double *C) {
  double alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;
  CBLAS_TRANSPOSE transB;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;
  (trans_b) ? transB = CblasTrans : transB = CblasNoTrans;

  cblas_dgemm(CblasRowMajor, transA, transB, m, n, k, alpha, A + offsetA, lda, B + offsetB, ldb, beta, C, n);
}

void matrix_dot_complex(bool trans_a, int offsetA, float *A, int lda, int m, int n, int k,
						bool trans_b, int offsetB, float *B, int ldb, float *C) {
  float alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;
  CBLAS_TRANSPOSE transB;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;
  (trans_b) ? transB = CblasTrans : transB = CblasNoTrans;

  cblas_cgemm(CblasRowMajor, transA, transB, m, n, k, &alpha, A + offsetA, lda, B + offsetB, ldb, &beta, C, n);
}

void matrix_dot_complex(bool trans_a, int offsetA, double *A, int lda, int m, int n, int k,
						bool trans_b, int offsetB, double *B, int ldb, double *C) {
  double alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;
  CBLAS_TRANSPOSE transB;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;
  (trans_b) ? transB = CblasTrans : transB = CblasNoTrans;

  cblas_zgemm(CblasRowMajor, transA, transB, m, n, k, &alpha, A + offsetA, lda, B + offsetB, ldb, &beta, C, n);
}

void matrix_dot(bool trans_a, int offsetA, float *A, int lda, int m, int n, float *X, int incx, float *Y) {
  float alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;

  cblas_sgemv(CblasRowMajor, transA, m, n, alpha, A + offsetA, lda, X, incx, beta, Y, 1);
}

void matrix_dot(bool trans_a, int offsetA, double *A, int lda, int m, int n, double *X, int incx, double *Y) {
  double alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;

  cblas_dgemv(CblasRowMajor, transA, m, n, alpha, A + offsetA, lda, X, incx, beta, Y, 1);
}

void matrix_dot_complex(bool trans_a, int offsetA, float *A, int lda, int m, int n, float *X, int incx, float *Y) {
  float alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;

  cblas_cgemv(CblasRowMajor, transA, m, n, &alpha, A + offsetA, lda, X, incx, &beta, Y, 1);
}

void matrix_dot_complex(bool trans_a, int offsetA, double *A, int lda, int m, int n, double *X, int incx, double *Y) {
  double alpha = 1.0, beta = 0.0;
  CBLAS_TRANSPOSE transA;

  (trans_a) ? transA = CblasTrans : transA = CblasNoTrans;

  cblas_zgemv(CblasRowMajor, transA, m, n, &alpha, A + offsetA, lda, X, incx, &beta, Y, 1);
}

#endif //CPP_CPP_LINALG_H_