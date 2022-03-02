///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#define LIBOMPX_DEFAULT_ENVIRONMENT LIBOMPX_ENVIRONMENT
#define LIBOMPX_DEFAULT_BACKEND LIBOMPX_BACKEND_NAME
#include "libompx/internal/sort.h"
#undef LIBOMPX_DEFAULT_ENVIRONMENT
#undef LIBOMPX_DEFAULT_BACKEND

void ompx::LIBOMPX_ENVIRONMENT::LIBOMPX_BACKEND_NAME::sort(uint32_t *Begin, uint32_t*End) {
  thrust::sort(thrust::LIBOMPX_ENVIRONMENT, Begin, End);
}

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------------===///
