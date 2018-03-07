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
        let digits: Vec<_> = read_line().trim_right().chars().map(|e| e.to_digit(10).unwrap() as u8).collect();
        let result = solve(&digits);

        println!("{}", result);
    }
}

mod cache {
    use std::u32::MAX as BLANK;

    pub struct Cache([u32; 9998]);
    pub struct Entry<'cache>(&'cache u32);

    impl Cache {
        pub fn new() -> Self {
            Cache([BLANK; 9998])
        }

        pub fn read(&self, key: usize) -> Entry {
            Entry(&self.0[key - 3])
        }
    }

    impl<'cache> Entry<'cache> {
        pub fn or<F: FnOnce() -> u32>(&self, func: F) -> u32 {
            let addr = self.0;
            let value = *addr;

            match value {
                BLANK => {
                    let ptr = addr as *const u32 as *mut u32;

                    let value = func();
                    unsafe { *ptr = value }
                    value
                }
                _ => value
            }
        }
    }
}

fn solve(digits: &[u8]) -> u32 {
    use std::cmp::min;
    use cache::Cache;

    let cache = Cache::new();

    struct Try<'a> { f: &'a Fn(&Try, usize) -> u32 };
    let try = Try {

        f: &|try, index| {
            cache.read(index).or(|| {
                match index {
                    0...2  => panic!("try() 함수의 인자 index는 항상 3 이상이어야 합니다. (현재 index: {})", index),
                    3 | 4 | 5 => eval(&digits[..index]),
                    _ => (3..min(index-2, 6))
                            .map(|i| (try.f)(try, index - i) + eval(&digits[index - i..index]))
                            .min()
                            .unwrap()
                }
            })
        }

    };
    (try.f)(&try, digits.len())
}

fn eval(digits: &[u8]) -> u32 {
    fn sub(a: u8, b: u8) -> i8 { a as i8 - b as i8 }

    let len = digits.len();
    let diff = sub(digits[1], digits[0]);

    if (2..len).all(|i| sub(digits[i], digits[i-1]) == diff) {
        // 숫자가 모노토닉하게 변화하는 경우
        match diff {
            0 => 1,
            1 | -1 => 2,
            _ => 5,
        }
    } else {
        // 모노토닉하지 않은경우
        match (2..len).all(|i| digits[i] == digits[i%2]) {
            true => 4,
            false => 10
        }
    }
}

#[test]
fn test_eval() {
    assert_eq!(1, eval(&[3, 3, 3]));
    assert_eq!(1, eval(&[5, 5, 5, 5]));

    assert_eq!(2, eval(&[2, 3, 4, 5, 6]));
    assert_eq!(2, eval(&[3, 2, 1, 0]));

    assert_eq!(4, eval(&[3, 2, 3]));
    assert_eq!(4, eval(&[5, 4, 5, 4, 5]));

    assert_eq!(5, eval(&[1, 4, 7]));
    assert_eq!(5, eval(&[8, 6, 4, 2]));

    assert_eq!(10, eval(&[1, 7, 9, 1, 2]));
    assert_eq!(10, eval(&[3, 3, 1]));
}

#[test]
fn test_solve() {
    assert_eq!(4, solve(&[1, 2, 3, 4, 1, 2, 3, 4]));
    assert_eq!(2, solve(&[1, 1, 1, 1, 1, 2, 2, 2]));
    assert_eq!(5, solve(&[1, 2, 1, 2, 2, 2, 2, 2]));
    assert_eq!(2, solve(&[2, 2, 2, 2, 2, 2, 2, 2]));
    assert_eq!(14, solve(&[1, 2, 6, 7, 3, 9, 3, 9]));
}
