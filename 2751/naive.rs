use std::io::prelude::*;
use std::io::stdin;

fn main() {
    let stdin = stdin();
    let mut iter = stdin.lock().lines();

    let count = iter.next().unwrap().unwrap().parse().unwrap();
    let mut numbers: Vec<i32> = Vec::with_capacity(count);

    for line in iter {
        numbers.push(line.unwrap().parse().unwrap());
    }

    numbers.sort();

    for num in numbers {
        println!("{}", num);
    }
}
