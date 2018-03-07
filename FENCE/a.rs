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
        let heights: Vec<u32> = read_line().trim_right().splitn(count, ' ').map(|str| str.parse().unwrap()).collect();

        println!("{}", solve(&heights));
    }
}

fn solve(_heights: &[u32]) -> u32 {
    let buffer = [0; 2**16 - 1];


    let mut a = 20000;
    let mut bits = Vec::new();
    while a > 0 {
        bits.push(a & 1 == 1);
        a >>= 1;
    }
    print!("{} = 0b", a);
    bits.into_iter().rev().for_each(|b| print!("{}", if b { 1 } else { 0 }));
    println!();





    //let len = heights.len();

    //for i in 0..len {
    //    print!("{} ", heights[i])
    //}
    //let mut i = 0;
    //while i < len {
    //    i += 2;
    //}

    //println!();



    // TODO: Remove
    std::process::exit(0);

    // match heights.len() {
    //     0 => panic!("solve()의 인자로 비어있는 슬라이스가 입력되면 안됩니다."),
    //     1 => return heights[0],
    //     _ => ()
    // }
}
