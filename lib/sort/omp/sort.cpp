///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#include "libompx/sort.h"

#include <algorithm>
//#include <omp.h>

#define LIBOMPX_ENVIRONMENT host
#include "sort.inc"
#define LIBOMPX_ENVIRONMENT device
#include "sort.inc"

void ompx::host::sort(uint32_t *Begin, uint32_t*End) {
  std::sort(Begin, End);
}

void ompx::device::sort(uint32_t *Begin, uint32_t*End) {
  #if defined(LIBOMPX_CUDA_THRUST)
    #if defined(LIBOMPX_ROCM_THRUST)
      #error "CUDA and ROCM thrust available but dynamic selection mechanism is not, abort!"
    #endif
    return ompx::device::cuda::sort(Begin, End);
  #elif defined(LIBOMPX_ROCM_THRUST)
    #if defined(LIBOMPX_CUDA_THRUST)
      #error "CUDA and ROCM thrust available but dynamic selection mechanism is not, abort!"
    #endif
    return ompx::device::rocm::sort(Begin, End);
  #else
      #error "Neither CUDA nor ROCM thrust available, no OpenMP default, abort!"
  #endif
}

void ompx::sort(uint32_t *Begin, uint32_t*End) {
#if 0
  uint32_t NumElements = End - Begin;
  uint32_t NumThreads = 256;
  uint32_t NumTeams = NumElements / NumThreads;
  #pragma omp target teams num_teams(NumTeams) thread_limit(NumThreads)
  {
    uint32_t ThreadId = omp_get_thread_num();
    uint32_t TeamId = omp_get_team_num();
    uint32_t TeamSize = omp_get_num_threads();
    uint32_t GlobalID = TeamId * TeamSize + ThreadId;
  }
#endif
}

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------------===///
