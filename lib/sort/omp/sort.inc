///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#include "libompx/internal/sort.h"

#if defined(LIBOMPX_CUDA_THRUST)
#define LIBOMPX_BACKEND cuda
#include "libompx/internal/sort.h"
#undef LIBOMPX_BACKEND
#endif

#if defined(LIBOMPX_ROCM_THRUST)
#define LIBOMPX_BACKEND rocm
#include "libompx/internal/sort.h"
#undef LIBOMPX_BACKEND
#endif

#undef LIBOMPX_ENVIRONMENT
