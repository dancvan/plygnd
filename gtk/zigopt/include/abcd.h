#ifndef ABCD_H
#define ABCD_H

#include <complex.h>

typedef struct {
    double A, B, C, D;
} ABCDMatrix;

typedef struct {
    double x;      // Ray height
    double theta;  // Ray angle
} Ray;

typedef struct {
    double re; 
    double im; 
} cdouble;

// Matrix operations
ABCDMatrix abcd_multiply(ABCDMatrix m1, ABCDMatrix m2);
Ray abcd_apply(ABCDMatrix m, Ray r);

// Optical elements
ABCDMatrix abcd_free_space(double d);
ABCDMatrix abcd_thin_lens(double f);
ABCDMatrix abcd_interface(double n1, double n2, double R);
ABCDMatrix abcd_mirror(double R);

// Gaussian beam qparameter transformation
cdouble abcd_transform_q(ABCDMatrix m, cdouble q_in);

// Export functions

void export_ray_trace(const char *filename, Ray *rays, int count);
void export_q_parameter(const char *filename, double z[], cdouble q[], int count);

// Resonator analysis

int abcd_is_stable(ABCDMatrix m);
cdouble abcd_resonator_q(ABCDMatrix m);

// Optional: Export element markers for plotting

void export_element_markers(const char *filename);

#endif
