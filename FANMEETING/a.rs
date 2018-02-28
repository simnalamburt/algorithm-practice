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
        let f = |e| if e == 'M' { 1 } else { 0 };
        let idol: Vec<_> = read_line().trim_right().chars().map(&f).collect();
        let fans: Vec<_> = read_line().trim_right().chars().map(&f).collect();
        let result = solve(idol, fans);
        println!("{}", result);
    }
}

fn solve(idol: Vec<u8>, fans: Vec<u8>) -> u32 {
    let end = fans.len() - idol.len() + 1;

    let mut count = 0;

    for iter in (0..end).rev() {
        let subfan = &fans[iter..iter + idol.len()];

        let mut is_all_zero = true;
        for i in 0..idol.len() {
            if idol[i] * subfan[i] == 1 {
                is_all_zero = false;
                break
            }
        }

        if is_all_zero {
            count += 1
        }

        let blank = |count| " ".repeat(count);
        let buffer: Vec<_> = (0..idol.len()).map(|i| idol[i] * subfan[i]).collect();
        eprintln!("\n\n1: 냄저, 0: 여자");
        eprintln!("{}", print_people(&fans));
        eprintln!("{}{}", blank(iter), print_people(subfan));
        eprintln!("{}{}", blank(iter), print_people(&idol));
        eprintln!();
        eprintln!("{}{} ({})", blank(iter), print_people(&buffer), if is_all_zero { "전부 0" } else { "1 있음" });
        fn print_people(input: &[u8]) -> String { input.iter().map(|&e| if e == 1 { '1' } else { '0' }).collect() }
    }

    count
}
