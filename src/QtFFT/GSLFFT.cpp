#include "qtfft.h"

N::GSLFFT:: GSLFFT      (void)
          : AbstractFFT (    )
{
}

N::GSLFFT::~GSLFFT(void)
{
}

int N::GSLFFT::type(void) const
{
  return 3 ;
}

bool N::GSLFFT::isSupported(Cpp::ValueTypes T,int dimension) const
{
  switch (T)                         {
    case Cpp::Float   : return true  ;
    case Cpp::Double  : return true  ;
    case Cpp::LDouble : return false ;
  }                                  ;
  return false                       ;
}

int N::GSLFFT::AllocateSource(CUIDs elements,QByteArray & Source)
{
  return Source.size() ;
}

int N::GSLFFT::AllocateTarget(CUIDs elements,QByteArray & Target)
{
  return Target.size() ;
}

bool N::GSLFFT::     Prepare   (
        CUIDs        elements  ,
        VarArgs    & Paraments ,
        QByteArray & Source    ,
        QByteArray & Target    )
{
  return false ;
}

void N::GSLFFT::Execution(void)
{
}
