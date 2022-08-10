package main

import (
	"fmt"
	"strings"
	"github.com/manifoldco/promptui"
)

var latin = [5][6]string{
	{"a", "b", "c", "d", "e", "f"},
	{"g", "h", "i", "j", "k", "l"},
	{"m", "n", "o", "p", "q", "r"},
	{"s", "t", "u", "v", "w", "x"},
	{"y", "z", "!", "?", ":", " "},
}

var galactic = [5][6]string{	
	{"ᔑ", "ʖ", "ᓵ", "↸", "Ŀ", "⎓"},
	{"ㅓ", "〒", "╎", "፧", "ꖌ", "ꖎ"},
	{"ᒲ", "リ", "フ", "¡", "ᑑ", "።"},
	{"ነ", "ﬧ", "⚍", "⍊", "∴", "/"},
	{"॥", "Λ", "ʗ", "˨", "ᚴ", "ᚌ"},
}
var userText string
var userKey string

func indexOf(letter string, choice int) (int, int) {
	for i:=0; i<5; i++ {
		for a:=0; a<6; a++ {
			if choice == 0 {
				if latin[i][a] == letter {
					return i, a;
				}
			} else {
				if galactic[i][a] == letter {
					return i, a;
				}
			}
		}
	}
	return 0, 0;
}

func reverse(text []string) []string {
	for i, a:= 0, len(text)-1; i<a; i, a = i+1, a-1 {
		text[i], text[a] = text[a], text[i];
	}
	return text;
}

func stringToKey(key []string) int {
	var keyInt int
	for i:=0; i<len(key); i++ {
		textRow, textColumn := indexOf(key[i], 0)
		keyInt += textRow + textColumn
	}
	fmt.Println(keyInt)
	return keyInt
}

func encrypt(text []string, key int) string {
	for i:=0; i<len(text); i++ {
		row, col := indexOf(text[i], 0);
		text[i] = galactic[row][(col+key)%6]
    }
    return strings.Join(text, "");
}

func decrypt(text []string, key int) string {
	for i:=0; i<len(text); i++ {
		row, col := indexOf(text[i], 1);
		text[i] = latin[row][(col+(key-2))%6]
    }
    return strings.Join(text, "");
}

func main() {
	prompt := promptui.Select{
		Label: "What to do",
		Items: []string{"Encrypt", "Decrypt"},
	}
	_, result, err := prompt.Run()
	if err != nil {
		fmt.Printf("Prompt failed: %v\n", err)
		return
	}

	fmt.Println("Enter the text")
	fmt.Scanln(&userText)
	fmt.Println("Enter key (only text): ")
	fmt.Scanln(&userKey)
	key := stringToKey(strings.Split(userKey, ""));
	text := strings.Split(userText, "");
	fmt.Printf("Original text: %v \n", text);
	reversedText := reverse(text);
	fmt.Printf("Reversed text: %v \n", reversedText);
	if result == "Encrypt" {
		fmt.Printf("Encrypted text: %v \n", encrypt(reversedText, key));
	} else {
		fmt.Printf("Decrypted text: %v \n", decrypt(reversedText, key));
	}
}