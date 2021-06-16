#include "qtfft.h"

N::AccelerateFFT:: AccelerateFFT (void)
                 : AbstractFFT   (    )
{
}

N::AccelerateFFT::~AccelerateFFT(void)
{
}

int N::AccelerateFFT::type(void) const
{
  return 5 ;
}

bool N::AccelerateFFT::isSupported(Cpp::ValueTypes T,int dimension) const
{
  #if defined(Q_OS_IOS)
  switch (T)                        {
    case Cpp::Float   : return true ;
    case Cpp::Double  : return true ;
    case Cpp::LDouble : return true ;
  }                                 ;
  #endif
  return false                      ;
}

int N::AccelerateFFT::AllocateSource(CUIDs elements,QByteArray & Source)
{
  return Source.size() ;
}

int N::AccelerateFFT::AllocateTarget(CUIDs elements,QByteArray & Target)
{
  return Target.size() ;
}

bool N::AccelerateFFT:: Prepare   (
        CUIDs           elements  ,
        VarArgs       & Paraments ,
        QByteArray    & Source    ,
        QByteArray    & Target    )
{
  return false ;
}

void N::AccelerateFFT::Execution(void)
{
}
