def solve(i,u):
 p=I[i];
 if u<p:return i
 k=solve(solve(i+1,p),u);print(p);return k
import sys;I=[*map(int,sys.stdin),9**9];sys.setrecursionlimit(10050);solve(0,9**8)
