fn main() {
    use std::io::{self, BufRead};

    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut read_line = || {
        let mut buffer = String::new();
        handle.read_line(&mut buffer).unwrap();
        buffer
    };

    let count = read_line().trim_right().parse().unwrap();
    for _ in 0..count {
        let count = read_line().trim_right().parse().unwrap();
        let numbers: Vec<i32> = read_line().trim_right().splitn(count, ' ').map(|str| str.parse().unwrap()).collect();

        println!("{}", solve(&numbers));
    }
}

fn solve(numbers: &[i32]) -> i32 {
    try(numbers, 0, 0)
}

fn try(numbers: &[i32], me: i32, enemy: i32) -> i32 {
    match numbers.len() {
        0 => me - enemy,
        1 => -try(&[], enemy, me + numbers[0]),
        _ => ,
    }
}
