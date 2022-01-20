//! ```
//! rustfmt run.rs && clippy-driver run.rs && rustc -O run.rs
//!
//! xz -dc targets.xz | ./run > result
//! ```
//!
//! ###### Reference
//! - https://en.wikipedia.org/wiki/Set_cover_problem

use crate::itertools::combinations;
use std::io::{self, BufRead};
use std::time::Instant;

const TARGET_LENGTH: usize = 11;
const TARGET_COUNT: usize = 3;
const BITSET_FULL: u32 = 0b11111111111111111111111111;

fn main() -> io::Result<()> {
    let mut words = Vec::new();

    {
        for line in io::stdin().lock().lines() {
            let word = line?;
            if word.len() != TARGET_LENGTH {
                continue;
            }

            let mut bitset = 0;
            for c in word.chars() {
                if let 'a'..='z' = c {
                    bitset |= 1u32 << (c as u8 - b'a');
                }
            }

            words.push((word, bitset));
        }
    }

    let num_words = words.len();
    let num_combinations = (0..TARGET_COUNT).fold(1, |acc, i| acc * (num_words - i) / (i + 1));

    eprintln!("number of words with 11 letters: {num_words}");
    eprintln!("number of possible combinations: {num_combinations}");

    let begin = Instant::now();

    for (i, combination) in combinations(&words, TARGET_COUNT).enumerate() {
        if i % 10_000_000 == 0 && i > 0 {
            let percent = i as f64 * 100.0 / num_combinations as f64;
            let elapsed = begin.elapsed();
            let remaining = (num_combinations - i) as f64 / i as f64 * elapsed.as_secs_f64();
            if remaining > 3600.0 {
                eprintln!(
                    "{i:10} ({percent:.3}%, {:.1} hours remaining)",
                    remaining / 3600.0
                );
            } else if remaining > 60.0 {
                eprintln!(
                    "{i:10} ({percent:.3}%, {:.1} minutes remaining)",
                    remaining / 60.0
                );
            } else {
                eprintln!("{i:10} ({percent:.3}%, {:.1} seconds remaining)", remaining);
            }
        }
        let result = combination
            .iter()
            .map(|(_, bitset)| *bitset)
            .fold(0, |acc, bitset| acc | bitset);
        if result == BITSET_FULL {
            println!(
                "{:?}",
                combination.iter().map(|(word, _)| word).collect::<Vec<_>>()
            );
        }
    }

    Ok(())
}

mod itertools {
    use std::iter::Iterator;

    enum State {
        Initial,
        Combining(Vec<usize>),
        Finished,
    }

    pub struct Combinations<'items, T> {
        items: &'items [T],
        k: usize,
        state: State,
    }

    pub fn combinations<T>(items: &[T], k: usize) -> Combinations<'_, T> {
        let state = if items.len() >= k {
            State::Initial
        } else {
            State::Finished
        };
        Combinations { items, k, state }
    }

    #[test]
    fn test_combinations() {
        assert_eq!(
            combinations(&vec![1, 2, 3, 4], 2).collect::<Vec<_>>(),
            vec![[&1, &2], [&1, &3], [&1, &4], [&2, &3], [&2, &4], [&3, &4]]
        );
        assert_eq!(
            combinations(&vec![1, 2, 3], 3).collect::<Vec<_>>(),
            vec![[&1, &2, &3]]
        );
        assert_eq!(combinations(&vec![1, 2, 3], 4).collect::<Vec<_>>().len(), 0);
    }

    impl<'items, T> Iterator for Combinations<'items, T> {
        type Item = Vec<&'items T>;

        fn next(&mut self) -> Option<Self::Item> {
            // Implemented as a Moore state machine.
            let n = self.items.len();
            let k = self.k;

            // Update the state.
            match self.state {
                State::Initial => {
                    self.state = State::Combining((0..k).collect());
                }
                State::Combining(ref indices) if indices[0] == n - k => {
                    self.state = State::Finished;
                }
                State::Combining(ref mut indices) => {
                    let mut i = k - 1;
                    while indices[i] == n - k + i {
                        i -= 1;
                    }
                    let new = indices[i] + 1;
                    for j in i..k {
                        indices[j] = new + j - i;
                    }
                }
                State::Finished => {}
            }

            // Yield the current combination.
            match &self.state {
                State::Initial => unreachable!(),
                State::Combining(indices) => {
                    Some((0..k).map(|i| &self.items[indices[i]]).collect())
                }
                State::Finished => None,
            }
        }
    }
}
