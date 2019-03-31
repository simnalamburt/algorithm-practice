package main
import(
."fmt"
."bytes"
s"strings"
f"compress/flate"
."encoding/ascii85"
."io/ioutil"
)
func main(){B:=make([]byte,360)
Decode(B,[]byte("7$:9)j#RU%pN77hGA-VQ^1ke+BSg^BO=5fI3WHmTPH51N,-/GPrZB-#1-I_aBZ&a@T['g8%!=2=OTqg@`J`piDA\"K!)p/?Y'M%0rl0h*'#/eoJ9F1jr3GcYN/!H^UPV!n7dIS<p@Mg.!`4/[,-8*$l-X3A?_+X5[p!b*D9ju\"YoT2]'`c>Rk/&'JGPJarpb?tNVV8Ki>2EY)E.1WW+gHc%/m<?B\"CGiQ\\T*mK`5]f;W'%p.14T-/MVgITO8XXi\"MJj_pO4L*tA/3'HWF)loHSYFpF_n@gf'Fp$R[f^(`VZTYA=FGNI-l[j@H&I)j;!0(fNI6\"n#V;TBcN9VO!i4LL^)Tor9\"'J_isIY43P0e::h.7^04V9+YKkW`uEZpQYY61Gf;Us77[hk&DYuPQ1\"chb479F2R[$;rX?WRK*k)5Z2P+2!<<'!"),true)
S,_:=ReadAll(f.NewReader(NewReader(B)))
var a,b int
Scanf("%d%d",&a,&b)
Println(s.Join(s.Split(string(S),"\n")[a-1:b]," "))}
