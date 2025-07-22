const std = @import("std");
const c = @cImport({
    @cInclude("abcd.h");
});

const stdin = std.io.getStdIn().reader();
const stdout = std.io.getStdOut().writer();

const Element = enum {
    Mirror,
    Lens,
    FreeSpace,
};

const ElementInstance = struct {
    kind: Element,
    value: f64, // Radius (mirror), Focal length (lens), Length (space)
};

const max_elements = 10;
var elements: [max_elements]ElementInstance = undefined;
var element_count: usize = 0;

fn readFloat(reader: anytype) !f64 {
    var buffer: [100]u8 = undefined;
    const line = try reader.readUntilDelimiterOrEof(&buffer, '\n');
    return try std.fmt.parseFloat(f64, line.?);
}

fn readInt(reader: anytype) !u8 {
    var buffer: [100]u8 = undefined;
    const line = try reader.readUntilDelimiterOrEof(&buffer, '\n');
    return try std.fmt.parseInt(u8, line.?, 10); // parse from base-10 string
}

fn prompt(msg: []const u8) !f64 {
    try stdout.print("{s}", .{msg});
    return try readFloat(stdin);
}

fn add_element(kind: Element, value: f64) void {
    if (element_count < max_elements) {
        elements[element_count] = .{ .kind = kind, .value = value };
        element_count += 1;
    }
}

fn export_elements_to_json() !void {
    const file = try std.fs.cwd().createFile("elements.json", .{ .truncate = true });
    defer file.close();
    const writer = file.writer();

    var json_stream = std.json.writeStream(writer, .{});
    try json_stream.beginArray();
    for (elements[0..element_count]) |e| {
        try json_stream.write(e);
    }
    try json_stream.endArray();
}

fn import_elements_from_json() !void {
    const allocator = std.heap.page_allocator;
    const file = try std.fs.cwd().openFile("elements.json", .{});
    defer file.close();

    const stat = try file.stat();
    const file_size = stat.size;

    const buffer = try allocator.alloc(u8, file_size);
    defer allocator.free(buffer);

    _ = try file.readAll(buffer);

    const parsed = try std.json.parseFromSlice([]ElementInstance, allocator, buffer, .{});
    defer parsed.deinit();

    const imported = parsed.value;
    if (imported.len > max_elements) return error.TooManyElements;

    for (imported, 0..) |elem, i| {
        elements[i] = elem;
    }
    element_count = imported.len;
}

pub fn main() !void {
    while (true) {
        try stdout.print("\nFabry–Pérot Cavity Builder\n", .{});
        try stdout.print("1. Add Mirror\n2. Add Lens\n3. Add Free Space\n4. Analyze\n5. Exit\n6. Export to JSON\n7. Import from JSON\n> ", .{});

        const choice = try readInt(stdin);
        switch (choice) {
            1 => {
                const R = try prompt("Enter mirror radius (mm): ");
                add_element(.Mirror, R);
            },
            2 => {
                const f = try prompt("Enter lens focal length (mm): ");
                add_element(.Lens, f);
            },
            3 => {
                const d = try prompt("Enter free space distance (mm): ");
                add_element(.FreeSpace, d);
            },
            4 => {
                var m = c.ABCDMatrix{ .A = 1, .B = 0, .C = 0, .D = 1 };
                for (elements[0..element_count]) |e| {
                    const next = switch (e.kind) {
                        .Mirror => c.abcd_mirror(e.value),
                        .Lens => c.abcd_thin_lens(e.value),
                        .FreeSpace => c.abcd_free_space(e.value),
                    };
                    m = c.abcd_multiply(next, m);
                }

                const stable = c.abcd_is_stable(m);
                const g = (m.A + m.D) / 2.0;

                try stdout.print("\nRound-trip matrix: [ {d:.3}, {d:.3}; {d:.3}, {d:.3} ]\n", .{ m.A, m.B, m.C, m.D });
                try stdout.print("Cavity is {s} (g = {d:.3})\n", .{ if (stable != 0) "STABLE" else "UNSTABLE", g});
            },
            5 => return,
            6 => {
                try export_elements_to_json();
                try stdout.print("Exported to elements.json\n", .{});
            },
            7 => {
                try import_elements_from_json();
                try stdout.print("Imported from elements.json\n", .{});
            },
            else => try stdout.print("Invalid choice.\n", .{}),
        }
    }
}
