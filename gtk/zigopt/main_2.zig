const std = @import("std");
const c = @cImport({
    @cInclude("abcd.h");
});

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    const ray = c.Ray{ .x = 1.0, .theta = 0.1 };
    const lens = c.abcd_thin_lens(50.0);
    const out = c.abcd_apply(lens, ray);

    try stdout.print("Output ray: x = {}, theta = {}\n", .{ out.x, out.theta });
}
