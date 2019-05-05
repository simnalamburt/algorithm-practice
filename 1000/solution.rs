fn main() {
    let mut line = String::new();
    let stdin = std::io::stdin();
    stdin.read_line(&mut line);

    let result = line.trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>().unwrap())
        .sum::<i32>();

    println!("{}", result);
}
