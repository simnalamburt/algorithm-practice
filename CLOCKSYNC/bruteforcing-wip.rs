use std::io::{self, BufRead};

type State = [u32; 16];
const zero_state: State = [0u32; 16];

const switch: [State; 10] = [
    [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1],
    [1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0],
    [1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1],
    [0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
];

fn main() {
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    let mut count = String::new();
    handle.read_line(&mut count).unwrap();

    let count: u8 = count.trim().parse().unwrap();
    for _ in 0..count {
        let mut line = String::new();
        handle.read_line(&mut line).unwrap();

        let input: Vec<_> = line.trim().split(' ').map(|str| {
            let oclock: u32 = str.parse().unwrap();
            (oclock / 3) % 4
        }).collect();

        let mut clock = zero_state;
        for i in 0..clock.len() {
            clock[i] = input[i];
        }

        // TODO
        let result = solve(clock);

        if result == std::u32::MAX {
            println!("-1");
        } else {
            println!("{}", result);
        }
    }
}

fn add(lhs: State, rhs: State) -> State {
    let mut result: State = [0u32; 16];
    for i in 0..result.len() {
        result[i] = lhs[i] + rhs[i];
    }
    result
}

fn rec(state: State, click: [u8; 10], iter: u32) -> Option<u8> {
    if iter == 10 {
        return if state == zero_state {
            // 시계가 모두 12시를 가리킬 경우, 전체 시도 횟수 반환
            Some(click.iter().fold(0, |acc, &x| acc + x))
        } else {
            None
        }
    }

    for i in 0..4 {
    }

    // TODO
    return None;
}

fn solve(input: State) -> u32 {
    let mut min = std::u32::MAX;

    // for a0 in 0..4 {
    //     let b0 = fma(input, switch[0], a0);
    //     for a1 in 0..4 {
    //         let b1 = fma(b0, switch[1], a1);
    //         for a2 in 0..4 {
    //             let b2 = fma(b1, switch[2], a2);
    //             for a3 in 0..4 {
    //                 let b3 = fma(b2, switch[3], a3);
    //                 for a4 in 0..4 {
    //                     let b4 = fma(b3, switch[4], a4);
    //                     for a5 in 0..4 {
    //                         let b5 = fma(b4, switch[5], a5);
    //                         for a6 in 0..4 {
    //                             let b6 = fma(b5, switch[6], a6);
    //                             for a7 in 0..4 {
    //                                 let b7 = fma(b6, switch[7], a7);
    //                                 for a8 in 0..4 {
    //                                     let b8 = fma(b7, switch[8], a8);
    //                                     for a9 in 0..4 {
    //                                         let mut b9 = fma(b8, switch[9], a9);

    //                                         for i in 0..b9.len() {
    //                                             b9[i] %= 4;
    //                                         }

    //                                         if b9 != [
    //                                             3, 3, 3, 3,
    //                                             3, 3, 3, 3,
    //                                             3, 3, 3, 3,
    //                                             3, 3, 3, 3u32
    //                                         ] {
    //                                             continue;
    //                                         }

    //                                         let sum = a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
    //                                         if min > sum { min = sum; }
    //                                     }
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    min
}
