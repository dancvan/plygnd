const std = @import("std");
const c = @cImport({
    @cInclude("abcd.h");
});

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    const R = 200.0; // mm, concave mirrors
    const L = 150.0;  // mm, cavity length < 2|R|

    const M_mirror = c.abcd_mirror(R);
    const M_space = c.abcd_free_space(L);

    // Round-trip matrix: M = M_mirror * M_space * M_mirror * M_space
    const M1 = c.abcd_multiply(M_space, M_mirror);
    const M2 = c.abcd_multiply(M_mirror, M1);
    const M_rt = c.abcd_multiply(M_space, M2);

    // Check stability
    if (c.abcd_is_stable(M_rt) == 0) {
        try stdout.print("Cavity is unstable!\n", .{});
        return;
    }

    // Calculate resonator q-parameter
    const q0 = c.abcd_resonator_q(M_rt);

    // Sample beam propagation through cavity
    const N = 100;
    var z_vals: [N]f64 = undefined;
    var q_vals: [N]c.cdouble= undefined;

    for (0..N) |i| {
        const z_pos = @as(f64, @floatFromInt(i)) * (L / @as(f64, N - 1));
        z_vals[i] = z_pos;

        // Propagate q(z) from initial q
        const Mz = c.abcd_free_space(z_pos);
        q_vals[i] = c.abcd_transform_q(Mz, q0);
    }

    // Export mode and elements
    try stdout.print("Exporting...\n", .{});
    _ = c.export_q_parameter("cavity_mode.txt", &z_vals, &q_vals, N);

    // Add mirror positions to marker file
    _ = c.export_element_markers("elements.txt");

    try stdout.print("Done.\n", .{});
}
