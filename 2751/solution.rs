//! rustfmt solution.rs
//! rustc solution.rs -O --edition=2018
//!
//! Reference:
//!   https://www.acmicpc.net/problem/2751

use mmap::read_input;
use parse::parse;
use std::io::prelude::*;
use std::io::{stdout, BufWriter};
use std::mem::uninitialized;

static mut TABLE: [bool; 2_000_001] = [false; 2_000_001];

fn main() {
    #[target_feature(enable = "avx2")]
    unsafe {
        for num in parse(read_input()).skip(1) {
            // -1_000_000 <= num <= 1_000_000
            TABLE[num as usize + 1_000_000] = true;
        }

        let stdout = stdout();
        let handle = stdout.lock();
        let mut writer = BufWriter::new(handle);

        let mut buffer: [u8; 8] = uninitialized();
        for (i, val) in TABLE.into_iter().enumerate() {
            if !val {
                continue;
            }
            let ret = itoa(&mut buffer, i as i32 - 1_000_000);

            writer.write_all(&buffer[ret..]).unwrap();
            writer.write_all(b"\n").unwrap();
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
    //! 항상 valid한 입력만이 들어온다고 가정함
    use std::iter::Iterator;

    pub struct FastParser<'a> {
        addr: &'a [u8],
        index: usize,
    }

    pub fn parse(addr: &[u8]) -> FastParser {
        FastParser { addr, index: 0 }
    }

    impl<'a> Iterator for FastParser<'a> {
        type Item = i32;

        fn next(&mut self) -> Option<Self::Item> {
            #[target_feature(enable = "avx2")]
            {
                let mut is_wip = false;
                let mut is_plus = true;
                let mut number = 0;

                if self.addr.len() <= self.index {
                    return None;
                }

                if self.addr[self.index] == b'-' {
                    is_plus = false;
                    self.index += 1;
                }

                while self.index < self.addr.len() {
                    match self.addr[self.index] {
                        ch @ b'0'..=b'9' => {
                            is_wip = true;
                            number = 10 * number + (ch - b'0') as i32;
                        }
                        _ => {
                            self.index += 1;
                            return Some(if is_plus { number } else { -number });
                        }
                    };

                    self.index += 1;
                }

                // 파싱중 EOF를 만남
                if is_wip {
                    return Some(if is_plus { number } else { -number });
                }

                None
            }
        }
    }
}

/// LUT, mod by 100
///
/// Reference:
///   https://github.com/miloyip/itoa-benchmark
///
/// NOTE: 카운팅소트만 아니었다면 10진법 대신 16진법을 써서 성능을 미세하게 올릴 수 있다.
fn itoa(buffer: &mut [u8; 8], val: i32) -> usize {
    #[rustfmt::skip]
    const TABLE: [&'static [u8; 2]; 100] = [
        b"00", b"01", b"02", b"03", b"04", b"05", b"06", b"07", b"08", b"09",
        b"10", b"11", b"12", b"13", b"14", b"15", b"16", b"17", b"18", b"19",
        b"20", b"21", b"22", b"23", b"24", b"25", b"26", b"27", b"28", b"29",
        b"30", b"31", b"32", b"33", b"34", b"35", b"36", b"37", b"38", b"39",
        b"40", b"41", b"42", b"43", b"44", b"45", b"46", b"47", b"48", b"49",
        b"50", b"51", b"52", b"53", b"54", b"55", b"56", b"57", b"58", b"59",
        b"60", b"61", b"62", b"63", b"64", b"65", b"66", b"67", b"68", b"69",
        b"70", b"71", b"72", b"73", b"74", b"75", b"76", b"77", b"78", b"79",
        b"80", b"81", b"82", b"83", b"84", b"85", b"86", b"87", b"88", b"89",
        b"90", b"91", b"92", b"93", b"94", b"95", b"96", b"97", b"98", b"99",
    ];

    if val < 0 {
        let ret = itoa(buffer, -val);
        buffer[ret - 1] = b'-';
        return ret - 1;
    }

    let mut p = buffer.len();
    let mut val = val as usize;

    while val >= 100 {
        let old = val;

        p -= 2;
        val /= 100;
        buffer[p] = TABLE[old - (val * 100)][0];
        buffer[p + 1] = TABLE[old - (val * 100)][1];
    }

    p -= 2;
    buffer[p] = TABLE[val][0];
    buffer[p + 1] = TABLE[val][1];

    p + if val < 10 { 1 } else { 0 }
}
