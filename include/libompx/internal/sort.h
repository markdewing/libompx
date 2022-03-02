///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#include <stdint.h>

#if defined(LIBOMPX_DEFAULT_ENVIRONMENT) and !defined(LIBOMPX_ENVIRONMENT)
#define LIBOMPX_ENVIRONMENT LIBOMPX_DEFAULT_ENVIRONMENT
#endif
#if defined(LIBOMPX_DEFAULT_BACKEND) and !defined(LIBOMPX_BACKEND)
#define LIBOMPX_BACKEND LIBOMPX_DEFAULT_BACKEND
#endif

namespace ompx {

#ifdef LIBOMPX_ENVIRONMENT
namespace LIBOMPX_ENVIRONMENT {
#endif

#ifdef LIBOMPX_BACKEND
namespace LIBOMPX_BACKEND {
#endif

void sort(uint32_t *Begin, uint32_t *End);

#ifdef LIBOMPX_BACKEND
}
#ifdef LIBOMPX_DEFAULT_BACKEND
using LIBOMPX_DEFAULT_BACKEND::sort;
#endif
#endif

#ifdef LIBOMPX_ENVIRONMENT
}
#ifdef LIBOMPX_DEFAULT_ENVIRONMENT
using LIBOMPX_DEFAULT_ENVIRONMENT::sort;
#endif
#endif

}

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------------===///
