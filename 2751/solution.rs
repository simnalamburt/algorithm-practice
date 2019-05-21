//! rustfmt solution.rs
//! rustc solution.rs -O --edition=2018
//!
//! Reference:
//!   https://www.acmicpc.net/problem/2751

use mmap::read_input;
use parse::parse;
use std::io::prelude::*;
use std::io::stdout;
use std::mem::uninitialized;
use std::ptr::copy_nonoverlapping;

static mut TABLE: [bool; 2_000_001] = [false; 2_000_001];
static mut OUTPUT_BUFFER: [u8; 7_888_904] = [0u8; 7_888_904];

fn main() {
    #[target_feature(enable = "avx2")]
    unsafe {
        //
        // stdin mmap 수행 및 오토마타로 stdin 파싱
        //
        let mut iter = parse(read_input());
        let count = iter.next().unwrap() as usize;
        for num in iter.take(count) {
            // -1_000_000 <= num <= 1_000_000
            TABLE[num as usize + 1_000_000] = true;
        }

        //
        // 출력할 내용을 OUTPUT_BUFFER에 기록
        //
        let mut idx = 0;
        let mut buffer: [u8; 8] = uninitialized();

        for i in -1_000_000..0 {
            if !TABLE.get_unchecked(i as usize + 1_000_000) {
                continue;
            }

            let offset = itoa(&mut buffer, -i as u32);
            let len = 8 - offset;

            OUTPUT_BUFFER[idx] = b'-';
            idx += 1;
            copy_nonoverlapping(&buffer[offset], &mut OUTPUT_BUFFER[idx], len);
            idx += len;
            OUTPUT_BUFFER[idx] = b'\n';
            idx += 1;
        }
        for i in 0..1_000_001 {
            if !TABLE[i as usize + 1_000_000] {
                continue;
            }

            let offset = itoa(&mut buffer, i);
            let len = 8 - offset;

            copy_nonoverlapping(&buffer[offset], &mut OUTPUT_BUFFER[idx], len);
            idx += len;
            OUTPUT_BUFFER[idx] = b'\n';
            idx += 1;
        }

        // 출력
        stdout().write_all(&OUTPUT_BUFFER[0..idx]).unwrap();
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
    //! 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른 atoi를 만들 수
    //! 있다.
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
                let mut is_plus = true;
                let mut number = 0;

                // NOTE: 입력이 스펙대로만 들어온다면 self.addr[self.index]에 접근하기 전에
                // 바운더리 체크를 먼저 할 필요가 없음

                if self.addr[self.index] == b'-' {
                    is_plus = false;
                    self.index += 1;
                }

                let len = self.addr.len();
                while self.index < len {
                    let ch = self.addr[self.index];
                    if ch < b'0' || b'9' < ch {
                        break;
                    }
                    number = 10 * number + (ch - b'0') as i32;
                    self.index += 1;
                }

                self.index += 1;
                return Some(if is_plus { number } else { -number });
            }
        }
    }
}

/// LUT, mod by 100. 0 <= val <= 1_000_000 일때에만 정상적으로 동작함.
///
/// Reference:
///   https://github.com/miloyip/itoa-benchmark
///
/// NOTE: 카운팅소트만 아니었다면 10진법 대신 16진법을 써서 성능을 미세하게 올릴 수 있다.
fn itoa(buffer: &mut [u8; 8], mut val: u32) -> usize {
    debug_assert!(val <= 1_000_000);

    #[rustfmt::skip]
    const TABLE: &'static [u8; 200] = b"\
        0001020304050607080910111213141516171819\
        2021222324252627282930313233343536373839\
        4041424344454647484950515253545556575859\
        6061626364656667686970717273747576777879\
        8081828384858687888990919293949596979899\
    ";

    let mut p = buffer.len();
    while val >= 100 {
        p -= 2;
        let rem: u32 = val % 100;
        val /= 100;
        unsafe { copy_nonoverlapping(TABLE.get_unchecked(rem as usize * 2), buffer.get_unchecked_mut(p), 2) }
    }
    p -= 2;
    unsafe { copy_nonoverlapping(TABLE.get_unchecked(val as usize * 2), buffer.get_unchecked_mut(p), 2) }

    p + if val < 10 { 1 } else { 0 }
}
