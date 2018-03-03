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

        println!("{:?}", result);
    }
}

fn solve(digits: &[u8]) -> u32 {
    use std::collections::HashMap;
    use std::cell::UnsafeCell;

    let cache = UnsafeCell::new(HashMap::<Vec<u8>, u32>::new());

    struct Try<'a> { f: &'a Fn(&Try, &[u8]) -> u32 };
    let try = Try {

        f: &|try, digits| {
            let cache = unsafe { &mut *cache.get() };
            let key = digits.to_vec();

            if let Some(&value) = cache.get(&key) {
                return value;
            }

            let len = digits.len();
            let value = match len {
                0...2  => panic!("try() 함수 인자의 길이는 항상 3보다 커야합니다. (입력된 조각의 길이: {})", len),
                3 | 4 | 5 => eval(digits),
                _ => (3..std::cmp::min(len-2, 6))
                        .map(|i| (try.f)(try, &digits[..len - i]) + eval(&digits[len - i..]))
                        .min()
                        .unwrap()
            };

            cache.insert(key, value);
            value
        }

    };
    (try.f)(&try, digits)
}

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
            diffs[0] == (if i%2 == 1 { -1 } else { 1 } * diffs[i])
        });

        match is_alternative {
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
