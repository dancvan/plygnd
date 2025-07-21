#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include "abcd.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

cdouble cdouble_add(cdouble a, cdouble b) {
    return (cdouble){a.re + b.re, a.im + b.im};
}

cdouble cdouble_sub(cdouble a, cdouble b) {
    return (cdouble){a.re - b.re, a.im - b.im};
}

cdouble cdouble_mul(cdouble a, cdouble b) {
    return (cdouble){
        a.re * b.re - a.im * b.im,
        a.re * b.im + a.im * b.re
    };
}

cdouble cdouble_div(cdouble a, cdouble b) {
    double denom = b.re * b.re + b.im * b.im;
    return (cdouble){
        (a.re * b.re + a.im * b.im) / denom,
        (a.im * b.re - a.re * b.im) / denom
    };
}

cdouble cdouble_inv(cdouble a) {
    double denom = a.re * a.re + a.im * a.im;
    return (cdouble){a.re / denom, -a.im / denom};
}

double cdouble_abs(cdouble a) {
    return sqrt(a.re * a.re + a.im * a.im);
}

// Multiply two ABCD matrices: result = m1 * m2
ABCDMatrix abcd_multiply(ABCDMatrix m1, ABCDMatrix m2) {
    ABCDMatrix result;
    result.A = m1.A * m2.A + m1.B * m2.C;
    result.B = m1.A * m2.B + m1.B * m2.D;
    result.C = m1.C * m2.A + m1.D * m2.C;
    result.D = m1.C * m2.B + m1.D * m2.D;
    return result;
}

// Apply ABCD matrix to ray
Ray abcd_apply(ABCDMatrix m, Ray r) {
    Ray result;
    result.x = m.A * r.x + m.B * r.theta;
    result.theta = m.C * r.x + m.D * r.theta;
    return result;
}

// Free space propagation over distance d
ABCDMatrix abcd_free_space(double d) {
    return (ABCDMatrix){1, d, 0, 1};
}

// Thin lens with focal length f
ABCDMatrix abcd_thin_lens(double f) {
    return (ABCDMatrix){1, 0, -1.0/f, 1};
}

// Interface between media of indices n1 and n2, with curvature radius R
ABCDMatrix abcd_interface(double n1, double n2, double R) {
    return (ABCDMatrix){1, 0, (n1 - n2) / (n2 * R), n1 / n2};
}

// Mirror with radius of curvature R
ABCDMatrix abcd_mirror(double R) {
    return (ABCDMatrix){1, 0, -2.0 / R, 1};
}

cdouble abcd_transform_q(ABCDMatrix m, cdouble q_in) {
    // Complex multiplication: A * q_in
    cdouble Aq;
    Aq.re = m.A * q_in.re;
    Aq.im = m.A * q_in.im;

    // Add B (a real number): Aq + B
    cdouble num;
    num.re = Aq.re + m.B;
    num.im = Aq.im;

    // Complex multiplication: C * q_in
    cdouble Cq;
    Cq.re = m.C * q_in.re;
    Cq.im = m.C * q_in.im;

    // Add D (a real number): Cq + D
    cdouble den;
    den.re = Cq.re + m.D;
    den.im = Cq.im;

    // Complex division: num / den
    double denom = den.re * den.re + den.im * den.im;
    cdouble result;
    result.re = (num.re * den.re + num.im * den.im) / denom;
    result.im = (num.im * den.re - num.re * den.im) / denom;

    return result;
}

void export_ray_trace(const char *filename, Ray *rays, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %lf %lf\n", i, rays[i].x, rays[i].theta);
    }

    fclose(fp);
}

void export_q_parameter(const char *filename, double z[], cdouble q[], int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        cdouble qinv = cdouble_inv(q[i]);

        double R = 1.0 / qinv.re;  // radius of curvature
        double w = sqrt(-1.0 / (M_PI * qinv.im));  // beam waist

        fprintf(fp, "%lf %lf %lf\n", z[i], R, w);
    }

    fclose(fp);
}

int abcd_is_stable(ABCDMatrix m) {
    double trace = m.A + m.D;
    return fabs(trace) < 2.0;
}

cdouble abcd_resonator_q(ABCDMatrix m) {
    // Implement q-parameter for resonator (using trace method)
    double A = m.A, B = m.B, C = m.C, D = m.D;
    double tr = A + D;
    double g = tr / 2.0;

    if (g * g >= 1.0) {
        // unstable, return NaN
        return (cdouble){NAN, NAN};
    }

    if (B == 0.0) {
	return (cdouble){NAN, NAN};
    }

    double im_part = sqrt((1.0 - g * g)) / B;
    cdouble q_inv = {0.0, im_part};
    return cdouble_inv(q_inv);

}

// ABCDMatrix make_cavity_with_lens() {
//     double R1 = 200.0;
//     double R2 = 200.0;
//     double f = 50.0;            // lens focal length
//     double L = 80.0;            // distance between lens and M2
//     double n_air = 1.0;
//     double n_glass = 1.5;
//     double t = 1.0;             // thickness of the glass substrate
// 
//     // Optical elements
//     ABCDMatrix M1 = abcd_mirror(R1);
//     ABCDMatrix int_air_to_glass = abcd_interface(n_air, n_glass, INFINITY); // planar
//     ABCDMatrix glass = abcd_free_space(t / n_glass);  // optical path length scaled
//     ABCDMatrix int_glass_to_air = abcd_interface(n_glass, n_air, INFINITY);
//     ABCDMatrix lens = abcd_thin_lens(f);
//     ABCDMatrix space = abcd_free_space(L);
//     ABCDMatrix M2 = abcd_mirror(R2);
// 
//     // Build half-cavity: M1 → substrate → lens → free space → M2
//     ABCDMatrix half_cavity = abcd_multiply(
//         M2,
//         abcd_multiply(
//             space,
//             abcd_multiply(
//                 lens,
//                 abcd_multiply(
//                     int_glass_to_air,
//                     abcd_multiply(glass, int_air_to_glass)
//                 )
//             )
//         )
//     );
// 
//     // Round trip: back through the same path and bounce off M1
//     ABCDMatrix round_trip = abcd_multiply(
//         M1,
//         abcd_multiply(
//             half_cavity,
//             half_cavity // back and forth
//         )
//     );
// 
//     return round_trip;
// }

void export_element_markers(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "0\tMirror (R = -200 mm)\n");
    fprintf(f, "150\tMirror (R = -200 mm)\n");

    fclose(f);
} 
