const std = @import("std");
const print = std.debug.print;

const LATIN = [5][6]u8{
    .{'a', 'b', 'c', 'd', 'e', 'f'},
    .{'g', 'h', 'i', 'j', 'k', 'l'},
    .{'m', 'n', 'o', 'p', 'q', 'r'},
    .{'s', 't', 'u', 'v', 'w', 'x'},
    .{'y', 'z', '!', '?', ':', ' '},
};

const GALACTIC = [5][6]u21{
    .{'ᔑ', 'ʖ', 'ᓵ', '↸', 'Ŀ', '⎓'},
    .{'ㅓ', '〒', '╎', '፧', 'ꖌ', 'ꖎ'},
    .{'ᒲ', 'リ', 'フ', '¡', 'ᑑ', '።'},
    .{'ነ', 'ﬧ', '⚍', '⍊', '∴', '/'},
    .{'॥', 'Λ', 'ʗ', '˨', 'ᚴ', 'ᚌ'},
};


pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    var user_text = std.ArrayList(u21).init(allocator);
    defer user_text.deinit();

    print("Enter text to be encrypted: ", .{});
    var byte = try stdin.readByte();
    while (byte != 0 and byte != '\n'): (byte = try stdin.readByte()) {
        try user_text.append(byte);
    }

    print("Enter key (0-255): ", .{});
    var user_key = try stdin.readByte();

    var text = user_text.items;
    std.mem.reverse(u21, text);

    for (text) |char| {
        print("{u}", .{char});
    }
    print("\n", .{});

    encrypt(text, user_key);
    for (text) |char| {
        print("{u}", .{char});
    }
}

fn encrypt(text: []u21, key: u8) void {
    var coords: [2]usize = undefined;
    var i: u32 = 0;
    while (i < text.len) : (i+=1) {
        coords = index_of(text[i]);
        text[i] = GALACTIC[coords[0]][(coords[1] + key) % 6];
    }
}

fn index_of(letter: u21) [2]usize {
    for (LATIN) | row, i | {
        for (row) | cell , j | {
            if (cell == letter) {
                return .{i, j};
            }
        }
    }
    return .{0,0};
}
