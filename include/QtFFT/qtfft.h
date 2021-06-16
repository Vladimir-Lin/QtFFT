/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 * QtFFT acts as an interface between Qt and FFT libraries.                 *
 * Please keep QtFFT as simple as possible.                                 *
 *                                                                          *
 * Qt Version   : 5.4.1                                                     *
 * CIOS Version : 1.6.0                                                     *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_FFT_H
#define QT_FFT_H

#include <QtCore>
#include <QtNetwork>
#include <QtSql>
#ifndef QT_STATIC
#include <QtScript>
#endif

#include <Essentials>

#ifdef QT_QTGMP_LIB
#include <QtGMP>
#endif

#ifdef QT_QTGSL_LIB
#include <QtGSL>
#endif

#ifdef QT_QTCUDA_LIB
#include <QtCUDA>
#endif

extern "C" {

#include <gsl/gsl_wavelet.h>
#include <gsl/gsl_wavelet2d.h>
#include <gsl/gsl_fft.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_fft_complex_float.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_halfcomplex_float.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_real_float.h>
#include <QtFFT/fftw3.h>

}

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTFFT_LIB)
#      define Q_FFT_EXPORT Q_DECL_EXPORT
#    else
#      define Q_FFT_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_FFT_EXPORT
#endif

namespace N
{

class Q_FFT_EXPORT Wavelet        ;
class Q_FFT_EXPORT Hankel         ;
class Q_FFT_EXPORT AbstractFFT    ;
class Q_FFT_EXPORT CooleyFFT      ;
class Q_FFT_EXPORT KissFFT        ;
class Q_FFT_EXPORT GSLFFT         ;
class Q_FFT_EXPORT FFTW           ;
class Q_FFT_EXPORT AccelerateFFT  ;


class Q_FFT_EXPORT Wavelet
{
  public:

    gsl_wavelet           * wavelet   ;
    gsl_wavelet_workspace * work      ;
    gsl_wavelet_direction   direction ;

    explicit Wavelet             (void) ;
    virtual ~Wavelet             (void) ;

    bool    allocate             (const gsl_wavelet_type * T,size_t k) ;
    bool    workspace            (size_t n) ;
    QString Name                 (void) ;

    int Transform                (double * data,size_t stride,size_t n) ;
    int TransformForward         (double * data,size_t stride,size_t n) ;
    int TransformInverse         (double * data,size_t stride,size_t n) ;
    int Transform2d              (double * data,size_t tda,size_t size1,size_t size2) ;
    int Transform2dForward       (double * data,size_t tda,size_t size1,size_t size2) ;
    int Transform2dInverse       (double * data,size_t tda,size_t size1,size_t size2) ;
    int TransformMatrix          (gsl_matrix * m) ;
    int TransformMatrixForward   (gsl_matrix * m) ;
    int TransformMatrixInverse   (gsl_matrix * m) ;
    int nsTransform              (double * data,size_t tda,size_t size1,size_t size2) ;
    int nsTransformForward       (double * data,size_t tda,size_t size1,size_t size2) ;
    int nsTransformInverse       (double * data,size_t tda,size_t size1,size_t size2) ;
    int nsTransformMatrix        (gsl_matrix * m) ;
    int nsTransformMatrixForward (gsl_matrix * m) ;
    int nsTransformMatrixInverse (gsl_matrix * m) ;

  protected:

  private:

};

class Q_FFT_EXPORT Hankel
{
  public:

    gsl_dht * hankel ;

    explicit Hankel   (void) ;
    explicit Hankel   (int size) ;
    explicit Hankel   (int size,double nu, double xmax) ;
             Hankel   (const Hankel & hankel) ;
    virtual ~Hankel   (void) ;

    bool   Allocate   (int size) ;
    bool   New        (int size,double nu, double xmax) ;
    int    Initialize (double nu,double xmax) ;
    int    Apply      (double * In,double * Out) ;
    double x          (int n) ;
    double k          (int n) ;

  protected:

  private:

};

class Q_FFT_EXPORT AbstractFFT
{
  public:

    typedef enum         {
      fftForward  = 0    ,
      fftBackward = 1    }
      TransformDirection ;

    TransformDirection direction  ;
    Cpp::ValueTypes    vType      ;
    int                sourceType ; // 0 - Undecided , 1 - Real , 2 - Complex
    int                targetType ; // 0 - Undecided , 1 - Real , 2 - Complex
    int                dimension  ;

    explicit AbstractFFT        (void);
    virtual ~AbstractFFT        (void);

    virtual int  type           (void) const = 0 ;
    virtual bool isSupported    (Cpp::ValueTypes type,int dimension) const = 0 ;
    virtual int  AllocateSource (CUIDs elements,QByteArray & Source) = 0 ;
    virtual int  AllocateTarget (CUIDs elements,QByteArray & Target) = 0 ;
    virtual bool Prepare        (CUIDs        elements        ,
                                 VarArgs    & Paraments       ,
                                 QByteArray & Source          ,
                                 QByteArray & Target    ) = 0 ;
    virtual void Execution      (void) = 0 ;

  protected:

  private:

};

class Q_FFT_EXPORT CooleyFFT : public AbstractFFT
{
  public:

    explicit CooleyFFT          (void) ;
    virtual ~CooleyFFT          (void) ;

    virtual int  type           (void) const ;
    virtual bool isSupported    (Cpp::ValueTypes T,int dimension) const ;
    virtual int  AllocateSource (CUIDs elements,QByteArray & Source) ;
    virtual int  AllocateTarget (CUIDs elements,QByteArray & Target) ;
    virtual bool Prepare        (CUIDs        elements  ,
                                 VarArgs    & Paraments ,
                                 QByteArray & Source    ,
                                 QByteArray & Target  ) ;
    virtual void Execution      (void) ;

  protected:

  private:

};

class Q_FFT_EXPORT KissFFT : public AbstractFFT
{
  public:

    explicit KissFFT            (void) ;
    virtual ~KissFFT            (void) ;

    virtual int  type           (void) const ;
    virtual bool isSupported    (Cpp::ValueTypes T,int dimension) const ;
    virtual int  AllocateSource (CUIDs elements,QByteArray & Source) ;
    virtual int  AllocateTarget (CUIDs elements,QByteArray & Target) ;
    virtual bool Prepare        (CUIDs        elements  ,
                                 VarArgs    & Paraments ,
                                 QByteArray & Source    ,
                                 QByteArray & Target  ) ;
    virtual void Execution      (void) ;

  protected:

  private:

};

class Q_FFT_EXPORT GSLFFT : public AbstractFFT
{
  public:

    explicit GSLFFT             (void) ;
    virtual ~GSLFFT             (void) ;

    virtual int  type           (void) const ;
    virtual bool isSupported    (Cpp::ValueTypes T,int dimension) const ;
    virtual int  AllocateSource (CUIDs elements,QByteArray & Source) ;
    virtual int  AllocateTarget (CUIDs elements,QByteArray & Target) ;
    virtual bool Prepare        (CUIDs        elements  ,
                                 VarArgs    & Paraments ,
                                 QByteArray & Source    ,
                                 QByteArray & Target  ) ;
    virtual void Execution      (void) ;

  protected:

  private:

};

class Q_FFT_EXPORT FFTW : public AbstractFFT
{
  public:

    explicit       FFTW           (void) ;
    virtual       ~FFTW           (void) ;

    virtual int    type           (void) const ;
    virtual bool   isSupported    (Cpp::ValueTypes T,int dimension) const ;
    virtual int    AllocateSource (CUIDs elements,QByteArray & Source) ;
    virtual int    AllocateTarget (CUIDs elements,QByteArray & Target) ;
    virtual bool   Prepare        (CUIDs        elements  ,
                                   VarArgs    & Paraments ,
                                   QByteArray & Source    ,
                                   QByteArray & Target  ) ;
    virtual void   Execution      (void) ;

    void           Cleanup        (void);

    fftw_complex * array          (int size);
    fftw_complex * fromByteArray  (int & size,QByteArray & Array);
    QByteArray     toByteArray    (fftw_complex * complex,int size);
    void           Execute        (const fftw_plan plan);
    void           Destroy        (fftw_plan plan);

    fftw_plan      Frequency      (int N,double * data,fftw_complex * dout,unsigned int flags = FFTW_MEASURE) ;
    void           Retrieve       (int component,int index,int length,double * data,fftw_complex * dout) ;

    void           Execute        (const fftwf_plan plan);
    void           Destroy        (fftwf_plan plan);

    #ifndef DISABLE_FFTW_LDOUBLE
    void           Execute        (const fftwl_plan plan);
    void           Destroy        (fftwl_plan plan);
    #endif

  protected:

    fftw_plan  fftplan  ;
    fftwf_plan fftfplan ;
    #ifndef DISABLE_FFTW_LDOUBLE
    fftwl_plan fftlplan ;
    #endif

  private:

    int fftSize                   (int fft,int length) ;
    int fftSize                   (int fft,CUIDs elements) ;

};

class Q_FFT_EXPORT AccelerateFFT : public AbstractFFT
{ // Apple iPhone OS Accelerate Framework
  public:

    explicit     AccelerateFFT  (void) ;
    virtual     ~AccelerateFFT  (void) ;

    virtual int  type           (void) const ;
    virtual bool isSupported    (Cpp::ValueTypes T,int dimension) const ;
    virtual int  AllocateSource (CUIDs elements,QByteArray & Source) ;
    virtual int  AllocateTarget (CUIDs elements,QByteArray & Target) ;
    virtual bool Prepare        (CUIDs        elements  ,
                                 VarArgs    & Paraments ,
                                 QByteArray & Source    ,
                                 QByteArray & Target  ) ;
    virtual void Execution      (void) ;

  protected:

  private:

};

}

QT_END_NAMESPACE

Q_DECLARE_METATYPE(N::Wavelet)
Q_DECLARE_METATYPE(N::Hankel)
Q_DECLARE_METATYPE(N::CooleyFFT)
Q_DECLARE_METATYPE(N::KissFFT)
Q_DECLARE_METATYPE(N::GSLFFT)
Q_DECLARE_METATYPE(N::FFTW)
Q_DECLARE_METATYPE(N::AccelerateFFT)

Q_DECLARE_INTERFACE(N::AbstractFFT  , "com.neutrino.math.fft" )

#endif
