// rustfmt solution.rs && rustc solution.rs -O --edition=2018
//
// Reference:
//   https://www.acmicpc.net/problem/2751
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
