"""
rayleigh(w_0, lambda) computes the rayleigh length of a Gaussian beam given the waist size (w_0) and wavelength (lambda).
"""
function rayleigh(w_0, lambda)
    return (w_0^2)*pi/lambda
    end

"""
beamsize(w_0, z_0, z) computes the beam size of a Gaussian beam given the waist size(w_0), rayleigh length (z_0), and distance from the waist (z).
"""
function beam_size(w_0, z_0, z)
    return w_0*(1. + (z/z_0)^2)^.5
    end

"""
gouy(z_0,z) computes the gouy phase of a Gaussian beam given the rayleigh length (z_0) and position from the waist (z).
"""
function gouy(z_0, z)
    return atan(z,z_0)
    end

"""
beam_radius(z_0,z) computes the beam radius of a Gaussian beam given the rayleigh length (z_0) and position from the waist (z).
"""
function beam_radius(z_0, z)
    return z*(1. +(z_0/z)^2)
    end

"""
q_param(z,z_0) computes the q parameter of a Gaussian beam given the rayleigh length (z_0) and position from the waist (z).
"""
function q_param(z_0,z)
    return z + z_0*im
    end

"""
abcd_prop(M,q) applies an ABCD matrix to a given q parameter allowing for easy ABCD beam propogation
"""
function abcd_prop(M, q)
    return (M[1,1]*q + M[1,2])/(M[2,1]*q + M[2,2])
    end

"""
prop_mat(d) constructs a propogation matrix in free space for length (d)
"""
function prop_mat(d)
    return [1. d; 0 1.]
    end 

"""
refraction(n_1,n_2) constructs a refraction matrix between an interface going from index n_1 to a material with index n_2
"""
function refraction(n_1,n_2)
    return [1. 0; 0 n_1/n_2]
    end

"""
curved_refraction(n_1, n_2, R) constructs a matrix from media with index n_1 to media that is curved with a ROC (R) and with index n_2.
"""
function curved_refraction(n_1, n_2, R)
    return [1. 0; (n_1-n_2)/(R*n_2) n_1*n_2]
    end

#=
function reflection
    return [1. 0;0 1.]
    end
=#

"""
curved_mirror_horizontal(R,theta_aoi) constructs a matrix that propogates the horizontal mode of a Gaussian beam to be reflected from a curved mirror with radius of curvature (R) and an angle of incidence (theta_aoi)
"""
function curved_mirror_horizontal(R, theta_aoi)
    return [1. 0;  -2. /(R*cos(theta_aoi)) 1.]
    end

"""
curved_mirror_vertical(R, theta_aoi) constructs a matrix that propogates the vertical mode of a Gaussian beam to be reflected from a curved mirror with radius of curvature (R) and an angle of incidence (theta_aoi)
"""
function curved_mirror_vertical(R, theta_aoi)
    return [1. 0; -2. /(R/cos(theta_aoi)) 1.]
    end

"""
thin_lens(f) constructs a matrix that propogates a Gaussian beam through a thin lens with a focal length (f).
"""
function thin_lens(f)
    return [1. 0; 1. /f 1.]
    end

"""
thick_lens(n_outlens, n_lens, R_first, R_sec, d_lens) constructs a matrix that propogates a Gaussian beam through a thick lens with a index (n_lens), R_first being the radius of curvature of the entering side, R_sec being the radius of curvature of the exiting side, and d_lens being the thickness of the lens at the thickest point.
"""
function thick_lens(n_outlens, n_lens, R_first, R_sec, d_lens)
    first_inter = [1. 0 ; (n_lens-n_outlens)/(R_sec*n_outlens) n_lens/n_outlens]
    transfer = [1. t; 0 1]
    sec_inter = [1. 0;  (n_outlens-n_lens)/(R_first*n_lens) n_outlens/n_lens]
    return first_inter*transfer*sec_inter
    end

"""
complex_envelope(A_1, q, lamdbda, n, radius) defines the complex envelope of the Gaussian beam with complex amplitude A_1, a q parameter (q), wavelength (lambda), index n of the propogation media, and radius defining the radius from the center most point to draw the envelope
"""
function complex_envelope(A_1, q, lambda, n, radius)
    k = (2. *pi*n)/lambda
    rho_sq(x,y) = x^2 + y^2
    step_ = radius/80.
    RHO_SQ = [rho_sq(x,y) for x in -radius:step_:radius, y in -radius:step_:radius]
    return (A_1/q)*exp.((-im*k/(2. *q)).*RHO_SQ)
    end

"""
mod_sq(gauss_complex_field) defines the modulus squared of the complex envelope of the Gaussian that can help define the wavefront profile at a given (z) location.
"""
function mod_sq(gauss_complex_field)
    return abs.(real.(A_.*conj(A_)))
    end

