#include "qtfft.h"

N::AbstractFFT:: AbstractFFT (void       )
               : direction   (fftForward )
               , vType       (Cpp::Double)
               , sourceType  (0          )
               , targetType  (0          )
               , dimension   (0          )
{
}

N::AbstractFFT::~AbstractFFT(void)
{
}
