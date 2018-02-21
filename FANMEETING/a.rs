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
        let idol: Vec<_> = read_line().trim_right().chars().map(|e| e == 'F').collect();
        let fans: Vec<_> = read_line().trim_right().chars().map(|e| e == 'F').collect();

        let result = solve(idol, fans);
        println!("{}", result);
    }
}

fn solve(idol: Vec<bool>, fans: Vec<bool>) -> u32 {
    let end = fans.len() - idol.len() + 1;

    let mut count = 0;

    for iter in 0..end {
        let subfan = &fans[iter..iter + idol.len()];

        let mut result = true;
        for i in 0..idol.len() {
            if !(idol[i] || subfan[i]) {
                result = false;
                break
            }
        }

        if result {
            count += 1
        }

        // fn blank(count: usize) -> String {
        //     " ".repeat(count)
        // }
        // fn print_people(input: &[bool]) -> String {
        //     input.iter().map(|e| if *e { "F" } else { "M" }).collect()
        // }
        // let mut buffer = String::new();
        // for i in 0..idol.len() { buffer += if idol[i] || subfan[i] { "_" } else { "X" }; }
        // println!("{}{}", blank(iter), print_people(&idol));
        // println!("{}{}", blank(iter), print_people(subfan));
        // println!("{}{} {}", blank(iter), buffer, result);
        // println!();
    }

    count
}
