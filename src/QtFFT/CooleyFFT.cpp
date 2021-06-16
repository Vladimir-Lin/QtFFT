#include "qtfft.h"

N::CooleyFFT:: CooleyFFT   (void)
             : AbstractFFT (    )
{
}

N::CooleyFFT::~CooleyFFT(void)
{
}

int N::CooleyFFT::type(void) const
{
  return 1 ;
}

bool N::CooleyFFT::isSupported(Cpp::ValueTypes T,int dimension) const
{
  switch (T)                        {
    case Cpp::Float   : return true ;
    case Cpp::Double  : return true ;
    case Cpp::LDouble : return true ;
  }                                 ;
  return false                      ;
}

int N::CooleyFFT::AllocateSource(CUIDs elements,QByteArray & Source)
{
  return Source.size() ;
}

int N::CooleyFFT::AllocateTarget(CUIDs elements,QByteArray & Target)
{
  return Target.size() ;
}

bool N::CooleyFFT::  Prepare   (
        CUIDs        elements  ,
        VarArgs    & Paraments ,
        QByteArray & Source    ,
        QByteArray & Target    )
{
  return false ;
}

void N::CooleyFFT::Execution(void)
{
}
