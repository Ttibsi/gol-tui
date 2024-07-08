const std = @import("std");

const source_files = [_][]const u8{
    "src/main.cpp",
    "src/game.cpp",
};

pub fn build(b: *std.Build) void {
    const dep = b.dependency("rawterm", .{});

    const exe = b.addExecutable(.{
        .name = "gol-tui",
        .target = b.host,
    });
    exe.linkLibCpp();

    exe.linkLibrary(dep.artifact("rawterm"));
    exe.root_module.addIncludePath(dep.path(""));
    exe.addIncludePath(b.path("include/"));

    exe.addCSourceFiles(.{ 
        .files = &source_files,
        .flags = &.{
            "-std=c++20",
            "-Wall", 
            "-Wextra" 
        }
    });

    // first str = zon name, second str = name in addStaticLib
    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_exe.step);
}
