! gfortran solution.f95 -O2 -Wall -Wextra -Wpedantic -Werror -fmax-array-constructor=2097152
program main
  implicit none
  integer :: a, b
  read (*,*) a, b
  write (*, '(i0)') a + b
end program main
