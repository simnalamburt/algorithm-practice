use std::io;

fn main() {
  let default = 1000;
  print!("Bound? (default: {})\n> ", default);

  let line = io::stdin().read_line().ok().unwrap();
  let bound: uint = from_str(line.trim()).unwrap_or(default);

  // sigma(1000) = 1 + 2 + 3 + ... + 1000
  fn sigma(bound: uint) -> uint { return bound*(bound + 1)/2; }

  // sum(3) = sum of { x | 0 <= x < 1000, x % 3 == 0 }
  let sum = |mul: uint| -> uint { return mul*sigma((bound - 1)/mul); };

  println!("The answer is : {} + {} - {} = {}",
      sum(3), sum(5), sum(3*5), sum(3) + sum(5) - sum(3*5));
}
