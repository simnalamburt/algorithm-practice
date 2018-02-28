/*
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
        let digits: Vec<u8> = read_line().trim_right().chars().map(|e| e.to_digit(10).unwrap() as u8).collect();
        let result = solve(digits);

        println!("{:?}", result);
    }
}

fn solve(digits: Vec<u8>) -> u32 {
    println!("{:?}", digits);

    42
}
*/

fn eval(digits: &[u8]) -> u32 {
    let len = digits.len();

    // 조각 길이 검사
    if len < 3 || 5 < len {
        panic!("조각의 길이는 항상 3 이상 5 이하여야 합니다. (입력된 조각의 길이: {})", len)
    }

    let diffs: Vec<_> = (1..len).map(|i| digits[i-1] as i8 - digits[i] as i8).collect();

    // 단조증감여부 체크
    let is_monotonic = diffs[1..].into_iter().all(|&e| diffs[0] == e);
    if is_monotonic {
        match diffs[0] {
            0 => 1,
            1 | -1 => 2,
            _ => 5,
        }
    } else {
        let is_alternative = (1..diffs.len()).all(|i| {
            diffs[0] == if i%2 == 1 { -1 } else { 1 } * diffs[i]
        });

        match is_alternative {
            true => 4,
            false => 10
        }
    }
}

fn main() {
    println!("{}", eval(&[3, 3, 3]));
    println!("{}", eval(&[5, 5, 5, 5]));

    println!("{}", eval(&[2, 3, 4, 5, 6]));
    println!("{}", eval(&[3, 2, 1, 0]));

    println!("{}", eval(&[3, 2, 3]));
    println!("{}", eval(&[5, 4, 5, 4, 5]));

    println!("{}", eval(&[1, 4, 7]));
    println!("{}", eval(&[8, 6, 4, 2]));

    println!("{}", eval(&[1, 7, 9, 1, 2]));
    println!("{}", eval(&[3, 3, 1]));
}
