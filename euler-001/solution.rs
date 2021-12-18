use std::io::{self, Write};

fn main() -> Result<(), io::Error> {
    let default = 1000;
    print!("Bound? (default: {})\n> ", default);
    io::stdout().flush()?;

    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let bound: u64 = line.trim().parse().unwrap_or(default);

    // sum(3) = sum of { x | 0 <= x < 1000, x % 3 == 0 }
    let sum = |mul| mul * sigma((bound - 1) / mul);

    println!(
        "The answer is : {} + {} - {} = {}",
        sum(3),
        sum(5),
        sum(3 * 5),
        sum(3) + sum(5) - sum(3 * 5)
    );
    Ok(())
}

/// sigma(1000) = 1 + 2 + 3 + ... + 1000
fn sigma(bound: u64) -> u64 {
    return bound * (bound + 1) / 2;
}
