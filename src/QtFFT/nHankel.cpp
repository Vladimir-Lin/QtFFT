#include "qtfft.h"

N::Hankel:: Hankel (void)
          : hankel (NULL)
{
}

N::Hankel:: Hankel (int size)
          : hankel (NULL    )
{
  hankel = ::gsl_dht_alloc((size_t)size) ;
}

N::Hankel:: Hankel (int size,double nu,double xmax)
{
  hankel = ::gsl_dht_new ((size_t)size,nu,xmax) ;
}

N::Hankel:: Hankel (const Hankel & h)
          : hankel (NULL            )
{
  hankel = ::gsl_dht_alloc((size_t)h.hankel->size) ;
}

N::Hankel::~Hankel (void)
{
  if (NotNull(hankel)) ::gsl_dht_free(hankel) ;
  hankel = NULL                               ;
}

bool N::Hankel::Allocate(int size)
{
  hankel = ::gsl_dht_alloc((size_t)size) ;
  return NotNull(hankel)                 ;
}

bool N::Hankel::New(int size,double nu,double xmax)
{
  hankel = ::gsl_dht_new ((size_t)size,nu,xmax) ;
  return NotNull(hankel)                        ;
}

int N::Hankel::Initialize(double nu,double xmax)
{
  return ::gsl_dht_init(hankel,nu,xmax) ;
}

int N::Hankel::Apply(double * In,double * Out)
{
  return ::gsl_dht_apply(hankel,In,Out) ;
}

double N::Hankel::x(int n)
{
  return ::gsl_dht_x_sample(hankel,n) ;
}

double N::Hankel::k(int n)
{
  return ::gsl_dht_k_sample(hankel,n) ;
}
