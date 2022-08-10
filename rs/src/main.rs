use console::Term;
use dialoguer::{theme::ColorfulTheme, Select};
use std::io;

const LATIN: [[char; 6]; 5] = [
    ['a', 'b', 'c', 'd', 'e', 'f'],
    ['g', 'h', 'i', 'j', 'k', 'l'],
    ['m', 'n', 'o', 'p', 'q', 'r'],
    ['s', 't', 'u', 'v', 'w', 'x'],
    ['y', 'z', '!', '?', ':', ' '],
];

const GALACTIC: [[char; 6]; 5] = [
    ['ᔑ', 'ʖ', 'ᓵ', '↸', 'Ŀ', '⎓'],
    ['ㅓ', '〒', '╎', '፧', 'ꖌ', 'ꖎ'],
    ['ᒲ', 'リ', 'フ', '¡', 'ᑑ', '።'],
    ['ነ', 'ﬧ', '⚍', '⍊', '∴', '/'],
    ['॥', 'Λ', 'ʗ', '˨', 'ᚴ', 'ᚌ'],
];

fn main() -> std::io::Result<()> {
    let selection = Select::with_theme(&ColorfulTheme::default())
        .item("Encrypt")
        .item("Decrypt")
        .default(0)
        .interact_on(&Term::stderr())?;

    println!("Enter the text");
    let mut user_text = String::new();
    io::stdin()
        .read_line(&mut user_text)
        .expect("Failed to read input");
    let text = user_text.trim();

    println!("Enter the key (text or number)");
    let mut user_key = String::new();
    io::stdin()
        .read_line(&mut user_key)
        .expect("Failed to read input");
    let key = string_to_key(user_key.trim());

    match selection {
        0 => {
            let encrypted_text = encrypt(text, key);
            println!("Encrypted text: {}", encrypted_text);
        }
        1 => {
            let decrypted_text = decrypt(text, key);
            println!("Decrypted text: {}", decrypted_text);
        }
        _ => {
            println!("Something went wrong");
            println!("Something went wrong")
        }
    }
    Ok(())
}

fn index_of(letter: char, choice: usize) -> (usize, usize) {
    [LATIN, GALACTIC]
        .get(choice)
        .and_then(|map| {
            map.iter().enumerate().find_map(|(row, row_slice)| {
                let col = row_slice.iter().position(|&s| s == letter)?;
                Some((row, col))
            })
        })
        .unwrap_or((0, 0))
}

fn string_to_key(text: &str) -> usize {
    let mut key = 0;
    for c in text.chars() {
        match c.is_alphabetic() {
            true => {
                let (row, col) = index_of(c, 0);
                key += row + col;
            }
            false => {
                key += c.to_digit(10).unwrap_or(0) as usize
            }
        }
    }
    println!("Key is: {}", key);
    key
}

fn encrypt(text: &str, key: usize) -> String {
    text.chars()
        .rev()
        .map(|letter| {
            let (row, col) = index_of(letter, 0);
            GALACTIC[row][(col + key) % 6]
        })
        .collect()
}

fn decrypt(text: &str, key: usize) -> String {
    text.chars()
        .rev()
        .map(|letter| {
            let (row, col) = index_of(letter, 1);
            LATIN[row][(col + (key-2)) % 6]
        })
        .collect()
}
