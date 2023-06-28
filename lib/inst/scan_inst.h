
// Explicit instantiations for scan functions
template void ompx_inclusive_scan_n(int *, size_t, int *);
template void ompx_inclusive_scan_n(unsigned int *, size_t, unsigned int *);
template void ompx_inclusive_scan_n(float *, size_t, float *);
template void ompx_inclusive_scan_n(double *, size_t, double *);
