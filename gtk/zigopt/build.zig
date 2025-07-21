const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "abcd_sim",
        .root_source_file = b.path("main.zig"),
        .target = target,
        .optimize = optimize,
    });

    exe.addCSourceFile(.{
        .file = b.path("abcd.c"),
        .flags = &.{"-std=c99"},
    });

    exe.linkLibC();
    b.installArtifact(exe); // ✅ Replaces exe.install()
    exe.addIncludePath(b.path("./include"));
 
    const run_cmd = b.addRunArtifact(exe);
    b.step("run", "Run the program").dependOn(&run_cmd.step); 
}
