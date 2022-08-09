const std = @import("std");
const Allocator = std.mem.Allocator;
const print = @import("std").debug.print;

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    var allocator = arena.allocator();

    var max_len: u32 = 255;
    var user_text = try allocator.alloc(u8, max_len);

    print("Enter text to be encrypted\n", .{});
    var byte = try stdin.readByte();
    var current_size: u32 = 0;
    while (byte != 0 and byte != '\n') {
        user_text[current_size] = byte;
        current_size += 1;
        if (current_size == max_len) {
            var x = try allocator.realloc(user_text, current_size*2);
            max_len = current_size*2;
            _ = x;
        }
        byte = try stdin.readByte();
    }

    var text = user_text[0..current_size];
    std.mem.reverse(u8, text);

    print("{s}", .{text});
}
