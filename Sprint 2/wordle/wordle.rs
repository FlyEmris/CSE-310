extern crate rand;

use rand::seq::SliceRandom; // Import SliceRandom for random selection from a slice
use rand::thread_rng; // Import thread_rng to get a random number generator
use std::io; // Import io for input/output

fn main() {
    // Define word lists for each difficulty level
    let easy_words = vec!["cat", "dog", "bat", "hat", "rat"];
    let medium_words = vec!["apple", "grape", "peach"];
    let hard_words = vec!["pineapple", "strawberry", "blueberry"];

    // Prompt the user to choose a difficulty level
    println!("Choose a difficulty: Easy (1), Medium (2), Hard (3)");
    let mut difficulty = String::new();
    io::stdin().read_line(&mut difficulty).expect("Failed to read line");
    let difficulty: u32 = difficulty.trim().parse().expect("Please enter a number");

    // Select a word based on the chosen difficulty
    let word = match difficulty {
        1 => easy_words.choose(&mut thread_rng()).unwrap(), // Choose a random word from easy_words
        2 => medium_words.choose(&mut thread_rng()).unwrap(), // Choose a random word from medium_words
        3 => hard_words.choose(&mut thread_rng()).unwrap(), // Choose a random word from hard_words
        _ => {
            println!("Invalid difficulty");
            return; // Exit the program if an invalid difficulty is chosen
        }
    };

    // Initialize the guessed_word vector with underscores to represent unguessed letters
    let mut guessed_word: Vec<char> = vec!['_'; word.len()];
    let mut attempts = word.len() + 5; // Set the number of attempts (word length + 5)

    // Main game loop
    while attempts > 0 {
        // Display the current state of the guessed word and remaining attempts
        println!("Word: {}", guessed_word.iter().collect::<String>());
        println!("Attempts left: {}", attempts);

        // Prompt the user to enter a guess
        println!("Enter your guess (a single letter):");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("Failed to read line");
        let guess = guess.trim().chars().next().unwrap(); // Get the first character of the input

        // Check if the guessed letter is in the word
        let mut correct_guess = false;
        for (i, &letter) in word.chars().enumerate() {
            if letter == guess {
                guessed_word[i] = letter; // Update the guessed_word vector with the correct letter
                correct_guess = true;
            }
        }

        if !correct_guess {
            attempts -= 1; // Decrement attempts if the guess was incorrect
        }

        // Check if the user has guessed the entire word
        if !guessed_word.contains(&'_') {
            println!("Congratulations! You've guessed the word: {}", word);
            return; // Exit the game if the word is guessed
        }
    }

    // If the user runs out of attempts, display the correct word
    println!("Out of attempts! The word was: {}", word);
}
