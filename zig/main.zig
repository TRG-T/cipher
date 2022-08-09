const std = @import("std");
const Allocator = std.mem.Allocator;
const print = @import("std").debug.print;

const LATIN = [5][6]u8{
    [_]u8{'a', 'b', 'c', 'd', 'e', 'f'},
    [_]u8{'g', 'h', 'i', 'j', 'k', 'l'},
    [_]u8{'m', 'n', 'o', 'p', 'q', 'r'},
    [_]u8{'s', 't', 'u', 'v', 'w', 'x'},
    [_]u8{'y', 'z', '!', '?', ':', ' '},
};

const GALACTIC = [5][6]u16{
    [_]u16{'ᔑ', 'ʖ', 'ᓵ', '↸', 'Ŀ', '⎓'},
    [_]u16{'ㅓ', '〒', '╎', '፧', 'ꖌ', 'ꖎ'},
    [_]u16{'ᒲ', 'リ', 'フ', '¡', 'ᑑ', '።'},
    [_]u16{'ነ', 'ﬧ', '⚍', '⍊', '∴', '/'},
    [_]u16{'॥', 'Λ', 'ʗ', '˨', 'ᚴ', 'ᚌ'},
};


pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    var allocator = arena.allocator();

    var max_len: u32 = 255;
    var user_text = try allocator.alloc(u8, max_len);

    print("Enter text to be encrypted: ", .{});
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

    print("Enter key (1 ascii char): ", .{});
    var user_key = try stdin.readByte();

    var final_text = try allocator.alloc(u16, current_size);
    var text = user_text[0..current_size];
    std.mem.reverse(u8, text);

    print("{s}\n", .{text});

    encrypt(&text, &final_text, user_key);
    for (final_text) | char | {
        print("{u}", .{char});
    }
}

fn encrypt(text: *[]u8, final_text: *[]u16, key: u16) void {
    var coords: [2]usize = undefined;
    var i: u32 = 0;
    while (i < text.len) : (i+=1) {
        coords = index_of(text.*[i]);
        final_text.*[i] = GALACTIC[coords[0]][(coords[1] + key) % 6];
    }
}

fn index_of(letter: u8) [2]usize {
    for (LATIN) | row, i | {
        for (row) | cell , j | {
            if (cell == letter) {
                return [2]usize {i, j};
            }
        }
    }
    return [2]usize {0,0};
}
