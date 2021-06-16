#include "qtfft.h"

N::FFTW:: FFTW        (void)
        : AbstractFFT (    )
{
}

N::FFTW::~FFTW(void)
{
}

int N::FFTW::type(void) const
{
  return 4 ;
}

bool N::FFTW::isSupported(Cpp::ValueTypes T,int dimension) const
{
  switch (T)                        {
    case Cpp::Float   : return true ;
    case Cpp::Double  : return true ;
    #ifndef DISABLE_FFTW_LDOUBLE
    case Cpp::LDouble : return true ;
    #endif
  }                                 ;
  return false                      ;
}

int N::FFTW::fftSize(int fft,int length)
{
  int s = Cpp::SizeOf(vType) ;
  switch (fft)               {
    case  0: s  = 0 ; break  ;
    case  1:          break  ;
    case  2: s += s ; break  ;
    default: s  = 0 ; break  ;
  }                          ;
  s *= length                ;
  return s                   ;
}

int N::FFTW::fftSize(int fft,CUIDs elements)
{
  int s = Cpp::SizeOf(vType)           ;
  switch (fft)                         {
    case  0: s  = 0 ; break            ;
    case  1:          break            ;
    case  2: s += s ; break            ;
    default: s  = 0 ; break            ;
  }                                    ;
  for (int i=0;i<elements.count();i++) {
    s *= elements[i]                   ;
  }                                    ;
  return s                             ;
}

int N::FFTW::AllocateSource(CUIDs elements,QByteArray & Source)
{
  if (dimension<=0               ) return Source.size() ;
  if (dimension!=elements.count()) return Source.size() ;
  int ffts = fftSize(sourceType,elements)               ;
  int osiz = Source.size()                              ;
  Source.resize(ffts+osiz)                              ;
  return Source.size()                                  ;
}

int N::FFTW::AllocateTarget(CUIDs elements,QByteArray & Target)
{
  if (dimension<=0               ) return Target.size() ;
  if (dimension!=elements.count()) return Target.size() ;
  int ffts = fftSize(targetType,elements)               ;
  int osiz = Target.size()                              ;
  Target.resize(ffts+osiz)                              ;
  return Target.size()                                  ;
}

bool N::FFTW::       Prepare   (
        CUIDs        elements  ,
        VarArgs    & Paraments ,
        QByteArray & Source    ,
        QByteArray & Target    )
{
  return false ;
}

void N::FFTW::Execution(void)
{
  switch (vType)                   {
    case Cpp::Float                :
      ::fftwf_execute ( fftfplan ) ;
    break                          ;
    case Cpp::Double               :
      ::fftw_execute  ( fftplan  ) ;
    break                          ;
    #ifndef DISABLE_FFTW_LDOUBLE
    case Cpp::LDouble              :
      ::fftwl_execute ( fftlplan ) ;
    break                          ;
    #endif
  }                                ;
}

void N::FFTW::Cleanup(void)
{
  ::fftw_cleanup  ( ) ;
  ::fftwf_cleanup ( ) ;
  #ifndef DISABLE_FFTW_LDOUBLE
  ::fftwl_cleanup ( ) ;
  #endif
}

fftw_complex * N::FFTW::array(int size)
{
  if (size<=0) return NULL;
  return new fftw_complex[size];
}

fftw_complex * N::FFTW::fromByteArray (int & size,QByteArray & Array)
{
  if (Array.size()<=0) {
    size = 0;
    return NULL;
  }
  char * d = Array.data();
  memcpy(&size,d,sizeof(int));
  return (fftw_complex *)(d+sizeof(int));
}

QByteArray N::FFTW::toByteArray(fftw_complex * complex,int size)
{
  QByteArray F;
  int S = sizeof(int);
  int C = (sizeof(fftw_complex) * size);
  S += C;
  F.resize(S);
  char * d = F.data();
  memcpy(d,&size,sizeof(int));
  d += sizeof(int);
  memcpy(d,complex,C);
  return F;
}

void N::FFTW::Execute(const fftw_plan plan)
{
  ::fftw_execute (plan);
}

void N::FFTW::Destroy(fftw_plan plan)
{
  ::fftw_destroy_plan (plan);
}

fftw_plan N::FFTW::Frequency(int N,double * data,fftw_complex * dout,unsigned int flags)
{
  return ::fftw_plan_dft_r2c_1d(N,data,dout,flags)  ;
}

void N::FFTW::Retrieve(int component,int index,int length,double * data,fftw_complex * dout)
{
  for (int i=0;i<length;i++,index++) {
    data[index] = dout[index][component] ;
  };
}

void N::FFTW::Execute(const fftwf_plan plan)
{
  ::fftwf_execute (plan);
}

void N::FFTW::Destroy(fftwf_plan plan)
{
  ::fftwf_destroy_plan (plan);
}

#ifndef DISABLE_FFTW_LDOUBLE

void N::FFTW::Execute(const fftwl_plan plan)
{
  ::fftwl_execute (plan);
}

void N::FFTW::Destroy(fftwl_plan plan)
{
  ::fftwl_destroy_plan (plan);
}

#endif
