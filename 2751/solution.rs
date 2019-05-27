use libc::{input, print};
use parse::parse;
use std::ptr::copy_nonoverlapping;

const ITOA_LUT: &'static [u8; 200] = b"\
    0001020304050607080910111213141516171819\
    2021222324252627282930313233343536373839\
    4041424344454647484950515253545556575859\
    6061626364656667686970717273747576777879\
    8081828384858687888990919293949596979899\
";
static mut TABLE: [bool; 2_000_001] = [false; 2_000_001];
static mut OUTPUT_BUFFER: [u8; 7_888_904] = [0u8; 7_888_904];

fn main() {
    unsafe {
        //
        // stdin mmap 수행 및 오토마타로 stdin 파싱
        //
        let mut iter = parse(input());
        let count = iter.next().unwrap() as usize;
        for num in iter.take(count) {
            // -1_000_000 <= num <= 1_000_000
            *TABLE.get_unchecked_mut(num as usize + 1_000_000) = true;
        }

        //
        // 출력할 내용을 OUTPUT_BUFFER에 기록
        //
        let mut idx = 0;
        macro_rules! assign {
            ($dst_idx:expr, $value:expr) => {
                *OUTPUT_BUFFER.get_unchecked_mut(idx + $dst_idx) = $value;
            };
        }
        macro_rules! memcpy {
            ($dst_idx:expr, $src_idx:expr) => {
                copy_nonoverlapping(
                    ITOA_LUT.get_unchecked($src_idx * 2),
                    OUTPUT_BUFFER.get_unchecked_mut(idx + $dst_idx),
                    2,
                );
            };
        }

        // -1_000_000
        if TABLE[0] {
            OUTPUT_BUFFER[0] = b'-';
            OUTPUT_BUFFER[1] = b'1';
            OUTPUT_BUFFER[2] = b'0';
            OUTPUT_BUFFER[3] = b'0';
            OUTPUT_BUFFER[4] = b'0';
            OUTPUT_BUFFER[5] = b'0';
            OUTPUT_BUFFER[6] = b'0';
            OUTPUT_BUFFER[7] = b'0';
            OUTPUT_BUFFER[8] = b'\n';
            idx += 9;
        }
        // -999_999 .. -99_999
        for i in (1..900_001).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            memcpy!(1, num / 10000);
            memcpy!(3, (num / 100) % 100);
            memcpy!(5, num % 100);
            assign!(7, b'\n');
            idx += 8;
        }
        // -99_999 .. -9_999
        for i in (900_001..990_001).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            assign!(1, (num / 10000) as u8 + b'0');
            memcpy!(2, (num / 100) % 100);
            memcpy!(4, num % 100);
            assign!(6, b'\n');
            idx += 7;
        }
        // -9_999 .. -999
        for i in (990_001..999_001).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            memcpy!(1, num / 100);
            memcpy!(3, num % 100);
            assign!(5, b'\n');
            idx += 6;
        }
        // -999 .. -99
        for i in (999_001..999_901).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            assign!(1, (num / 100) as u8 + b'0');
            memcpy!(2, num % 100);
            assign!(4, b'\n');
            idx += 5;
        }
        // -99 .. -9
        for i in (999_901..999_991).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            memcpy!(1, num);
            assign!(3, b'\n');
            idx += 4;
        }
        // -9 .. 0
        for i in (999_991..1_000_000).filter(|i| TABLE[*i]) {
            let num = 1000000 - i;

            assign!(0, b'-');
            assign!(1, num as u8 + b'0');
            assign!(2, b'\n');
            idx += 3;
        }
        // 0 .. 10
        for i in (1_000_000..1_000_010).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            assign!(0, num as u8 + b'0');
            assign!(1, b'\n');
            idx += 2;
        }
        // 10 .. 100
        for i in (1_000_010..1_000_100).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            memcpy!(0, num);
            assign!(2, b'\n');
            idx += 3;
        }
        // 100 .. 1_000
        for i in (1_000_100..1_001_000).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            assign!(0, (num / 100) as u8 + b'0');
            memcpy!(1, num % 100);
            assign!(3, b'\n');
            idx += 4;
        }
        // 1_000 .. 10_000
        for i in (1_001_000..1_010_000).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            memcpy!(0, num / 100);
            memcpy!(2, num % 100);
            assign!(4, b'\n');
            idx += 5;
        }
        // 10_000 .. 100_000
        for i in (1_010_000..1_100_000).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            assign!(0, (num / 10000) as u8 + b'0');
            memcpy!(1, (num / 100) % 100);
            memcpy!(3, num % 100);
            assign!(5, b'\n');
            idx += 6;
        }
        // 100_000 .. 1_000_000
        for i in (1_100_000..2_000_000).filter(|i| TABLE[*i]) {
            let num = i - 1000000;

            memcpy!(0, num / 10000);
            memcpy!(2, (num / 100) % 100);
            memcpy!(4, num % 100);
            assign!(6, b'\n');
            idx += 7;
        }
        // 1_000_000
        if TABLE[2_000_000] {
            assign!(0, b'1');
            assign!(1, b'0');
            assign!(2, b'0');
            assign!(3, b'0');
            assign!(4, b'0');
            assign!(5, b'0');
            assign!(6, b'0');
            // NOTE: 맨 마지막 줄에 LF 없어도 정답으로 인정됨
            idx += 7;
        }

        //
        // 출력
        //
        print(&OUTPUT_BUFFER[..idx]);
    };
}

mod libc {
    use std::ffi::c_void;
    use std::mem::uninitialized;
    use std::process::exit;
    use std::ptr::null_mut;
    use std::slice::from_raw_parts;

    const STDIN_FILENO: i32 = 0;
    const STDOUT_FILENO: i32 = 1;
    const PROT_READ: i32 = 1;
    const MAP_PRIVATE: i32 = 1;
    const MAP_FAILED: *mut c_void = std::usize::MAX as *mut _;

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
            addr: *mut c_void,
            len: usize,
            prot: i32,
            flags: i32,
            fd: i32,
            offset: i64,
        ) -> *mut c_void;
        fn write(fd: i32, buf: *const c_void, count: usize) -> isize;
    }

    pub unsafe fn input<'a>() -> &'a [u8] {
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

    pub unsafe fn print(buf: &[u8]) {
        write(STDOUT_FILENO, buf.as_ptr() as *const c_void, buf.len());
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
            let mut is_plus = true;
            let mut number = 0;

            // NOTE: 입력이 스펙대로만 들어온다면 self.addr[self.index]에 접근하기 전에
            // 바운더리 체크를 먼저 할 필요가 없음
            if *unsafe { self.addr.get_unchecked(self.index) } == b'-' {
                is_plus = false;
                self.index += 1;
            }

            let len = self.addr.len();
            while self.index < len {
                let ch = *unsafe { self.addr.get_unchecked(self.index) };
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
