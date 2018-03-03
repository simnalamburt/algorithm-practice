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

static mut BUFFER: [u32; 9997] = [0; 9997];

fn solve(digits: &[u8]) -> u32 {
    use std::cmp::min;
    use std::u32::MAX as uninitialized;

    // 캐시 리셋
    unsafe { BUFFER = [uninitialized; 9997] }
    let get_cache = |index: usize| unsafe { &mut BUFFER[index - 3] };

    struct Try<'a> { f: &'a Fn(&Try, usize) -> u32 };
    let try = Try {

        f: &|try, index| {
            // 캐시에 값이 있는지 먼저 확인
            let value = *get_cache(index);
            if value != uninitialized {
                return value;
            }

            // 캐시에 값이 없으면 계산 수행
            let value = match index {
                0...2  => panic!("try() 함수의 인자 index는 항상 3 이상이어야 합니다. (현재 index: {})", index),
                3 | 4 | 5 => eval(&digits[..index]),
                _ => (3..min(index-2, 6))
                        .map(|i| (try.f)(try, index - i) + eval(&digits[index - i..index]))
                        .min()
                        .unwrap()
            };

            // 캐시 업데이트
            *get_cache(index) = value;
            value
        }

    };
    (try.f)(&try, digits.len())
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
