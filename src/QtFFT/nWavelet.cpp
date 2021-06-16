#include "qtfft.h"

N::Wavelet:: Wavelet   (void               )
           : wavelet   (NULL               )
           , work      (NULL               )
           , direction (gsl_wavelet_forward)
{
}

N::Wavelet::~Wavelet (void)
{
  if (NotNull(wavelet)) ::gsl_wavelet_free          (wavelet) ;
  if (NotNull(work   )) ::gsl_wavelet_workspace_free(work   ) ;
  wavelet = NULL                                              ;
  work    = NULL                                              ;
}

bool N::Wavelet::allocate (const gsl_wavelet_type * T, size_t k)
{
  wavelet = ::gsl_wavelet_alloc(T,k) ;
  return NotNull(wavelet)            ;
}

bool N::Wavelet::workspace(size_t n)
{
  work = ::gsl_wavelet_workspace_alloc(n) ;
  return NotNull(work)                    ;
}

QString N::Wavelet::Name(void)
{
  if (IsNull(wavelet)) return ""              ;
  return QString(::gsl_wavelet_name(wavelet)) ;
}

int N::Wavelet::Transform(double * data,size_t stride,size_t n)
{
  return ::gsl_wavelet_transform(wavelet,data,stride,n,direction,work) ;
}

int N::Wavelet::TransformForward(double * data,size_t stride,size_t n)
{
  return ::gsl_wavelet_transform_forward(wavelet,data,stride,n,work) ;
}

int N::Wavelet::TransformInverse(double * data,size_t stride,size_t n)
{
  return ::gsl_wavelet_transform_inverse(wavelet,data,stride,n,work) ;
}

int N::Wavelet::Transform2d(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_transform(wavelet,data,tda,size1,size2,direction,work) ;
}

int N::Wavelet::Transform2dForward(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_transform_forward(wavelet,data,tda,size1,size2,work) ;
}

int N::Wavelet::Transform2dInverse(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_transform_inverse(wavelet,data,tda,size1,size2,work) ;
}

int N::Wavelet::TransformMatrix(gsl_matrix * m)
{
  return ::gsl_wavelet2d_transform_matrix(wavelet,m,direction,work) ;
}

int N::Wavelet::TransformMatrixForward(gsl_matrix * m)
{
  return ::gsl_wavelet2d_transform_matrix_forward(wavelet,m,work) ;
}

int N::Wavelet::TransformMatrixInverse(gsl_matrix * m)
{
  return ::gsl_wavelet2d_transform_matrix_inverse(wavelet,m,work) ;
}

int N::Wavelet::nsTransform(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_nstransform(wavelet,data,tda,size1,size2,direction,work) ;
}

int N::Wavelet::nsTransformForward(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_nstransform_forward(wavelet,data,tda,size1,size2,work) ;
}

int N::Wavelet::nsTransformInverse(double * data,size_t tda,size_t size1,size_t size2)
{
  return ::gsl_wavelet2d_nstransform_inverse(wavelet,data,tda,size1,size2,work) ;
}

int N::Wavelet::nsTransformMatrix(gsl_matrix * m)
{
  return ::gsl_wavelet2d_nstransform_matrix(wavelet,m,direction,work) ;
}

int N::Wavelet::nsTransformMatrixForward(gsl_matrix * m)
{
  return ::gsl_wavelet2d_nstransform_matrix_forward(wavelet,m,work) ;
}

int N::Wavelet::nsTransformMatrixInverse(gsl_matrix * m)
{
  return ::gsl_wavelet2d_nstransform_matrix_inverse(wavelet,m,work) ;
}
