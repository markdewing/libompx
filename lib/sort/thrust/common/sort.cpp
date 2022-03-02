///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#include <thrust/sort.h>

#define LIBOMPX_ENVIRONMENT device
#include "sort.inc"
#undef LIBOMPX_ENVIRONMENT

#define LIBOMPX_ENVIRONMENT host
#include "sort.inc"
#undef LIBOMPX_ENVIRONMENT

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------------===///
