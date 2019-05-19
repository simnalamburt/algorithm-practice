//! rustfmt solution.rs
//! rustc solution.rs -O --edition=2018
//!
//! Reference:
//!   https://www.acmicpc.net/problem/2751

use mmap::read_input;
use parse::parse;
use std::io::prelude::*;
use std::io::{stdout, BufWriter};

fn main() {
    #[target_feature(enable = "avx2")]
    unsafe {
        let mut iter = parse(read_input());
        let count = iter.next().unwrap() as usize;
        let mut numbers = vec![0; count];
        for (i, num) in iter.enumerate() {
            numbers[i] = num;
        }

        numbers.sort_unstable();

        let stdout = stdout();
        let handle = stdout.lock();
        let mut writer = BufWriter::new(handle);

        for num in numbers {
            writer.write(num.to_string().as_bytes()).unwrap();
            writer.write(b"\n").unwrap();
        }
    }
}

mod mmap {
    use std::ffi::c_void as void;
    use std::mem::uninitialized;
    use std::process::exit;
    use std::ptr::null_mut;
    use std::slice::from_raw_parts;

    const STDIN_FILENO: i32 = 0;
    const PROT_READ: i32 = 1;
    const MAP_PRIVATE: i32 = 1;
    const MAP_FAILED: *mut void = std::usize::MAX as *mut _;

    // Linux x86-64, glibc 8.3.0
    #[repr(C)]
    struct stat {
        st_dev: u64,
        st_ino: u64,
        st_nlink: u64,
        st_mode: u32,
        st_uid: u32,
        st_gid: u32,
        __pad0: u32,
        st_rdev: u64,
        st_size: i64,
        st_blksize: i64,
        st_blocks: i64,
        st_atime: i64,
        st_atime_nsec: i64,
        st_mtime: i64,
        st_mtime_nsec: i64,
        st_ctime: i64,
        st_ctime_nsec: i64,
        __unused: [i64; 3],
    }
    extern "C" {
        fn fstat(fildes: i32, buf: *mut stat) -> i32;
        fn mmap(
            addr: *mut void,
            len: usize,
            prot: i32,
            flags: i32,
            fd: i32,
            offset: i64,
        ) -> *mut void;
    }

    #[target_feature(enable = "avx2")]
    pub unsafe fn read_input<'a>() -> &'a [u8] {
        // Linux x86-64, glibc 8.3.0
        debug_assert!(std::mem::size_of::<stat>() == 144);

        // stdin 길이 측정
        let mut stat: stat = uninitialized();
        let ret = fstat(STDIN_FILENO, &mut stat);
        if ret != 0 {
            exit(1);
        }
        let file_size = stat.st_size as usize;

        // stdin mmap 수행
        let addr = mmap(
            null_mut(),
            file_size,
            PROT_READ,
            MAP_PRIVATE,
            STDIN_FILENO,
            0,
        );
        if addr == MAP_FAILED {
            exit(1);
        }

        from_raw_parts(addr as *mut u8, file_size)
    }
}

mod parse {
    use std::iter::Iterator;
    use std::process::exit;

    pub struct FastParser<'a> {
        addr: &'a [u8],
        index: usize,
    }

    pub fn parse(addr: &[u8]) -> FastParser {
        FastParser { addr, index: 0 }
    }

    #[derive(Copy, Clone)]
    enum State {
        ExpectSignDigitBlank,
        ExpectDigit,
        ExpectDigitBlank,
    }
    #[derive(Copy, Clone)]
    enum Kind {
        Sign,
        Digit,
        Blank,
    }
    #[derive(Copy, Clone)]
    enum Sign {
        Plus,
        Minus,
    }

    impl<'a> Iterator for FastParser<'a> {
        type Item = i32;

        fn next(&mut self) -> Option<Self::Item> {
            #[target_feature(enable = "avx2")]
            {
                let mut state = State::ExpectSignDigitBlank;
                let mut sign = Sign::Plus;

                let mut number = 0;

                while self.index < self.addr.len() {
                    let ch = self.addr[self.index];

                    let kind = match ch {
                        b'-' => Kind::Sign,
                        b'0'..=b'9' => Kind::Digit,
                        b' ' | b'\n' => Kind::Blank,
                        _ => exit(1),
                    };

                    let mut read_digit = || number = 10 * number + (ch - b'0') as i32;

                    match (state, kind) {
                        (State::ExpectSignDigitBlank, Kind::Sign) => {
                            state = State::ExpectDigit;
                            sign = Sign::Minus;
                        }
                        (State::ExpectSignDigitBlank, Kind::Digit) => {
                            state = State::ExpectDigitBlank;
                            read_digit();
                        }
                        (State::ExpectSignDigitBlank, Kind::Blank) => {
                            // no-op
                        }
                        (State::ExpectDigit, Kind::Digit) => {
                            state = State::ExpectDigitBlank;
                            read_digit();
                        }
                        (State::ExpectDigitBlank, Kind::Digit) => {
                            read_digit();
                        }
                        (State::ExpectDigitBlank, Kind::Blank) => {
                            // 파싱 종료
                            self.index += 1;
                            return Some(if let Sign::Plus = sign { number } else { -number });
                        }
                        _ => exit(1),
                    }

                    self.index += 1;
                }

                // 파싱중 EOF를 만남
                if let State::ExpectDigitBlank = state {
                    return Some(if let Sign::Plus = sign { number } else { -number });
                }

                None
            }
        }
    }
}
