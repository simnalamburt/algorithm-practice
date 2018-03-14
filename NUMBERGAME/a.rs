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
        let numbers: Vec<i16> = read_line().trim_right().splitn(count, ' ').map(|str| str.parse().unwrap()).collect();

        println!("{}", solve(&numbers));
    }
}

fn solve(numbers: &[i16]) -> i32 {
    eprintln!("{:?}", numbers);

    42
}
