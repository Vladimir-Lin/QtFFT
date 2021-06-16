#include "qtfft.h"

N::KissFFT:: KissFFT     (void)
           : AbstractFFT (    )
{
}

N::KissFFT::~KissFFT(void)
{
}

int N::KissFFT::type(void) const
{
  return 2 ;
}

bool N::KissFFT::isSupported(Cpp::ValueTypes T,int dimension) const
{
  switch (T)                        {
    case Cpp::Float   : return true ;
    case Cpp::Double  : return true ;
    case Cpp::LDouble : return true ;
  }                                 ;
  return false                      ;
}

int N::KissFFT::AllocateSource(CUIDs elements,QByteArray & Source)
{
  return Source.size() ;
}

int N::KissFFT::AllocateTarget(CUIDs elements,QByteArray & Target)
{
  return Target.size() ;
}

bool N::KissFFT::    Prepare   (
        CUIDs        elements  ,
        VarArgs    & Paraments ,
        QByteArray & Source    ,
        QByteArray & Target    )
{
  return false ;
}

void N::KissFFT::Execution(void)
{
}
