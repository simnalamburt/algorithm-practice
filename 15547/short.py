import zlib,base64
a,b=map(int,input().split())
print(' '.join(zlib.decompress(base64.b85decode('c$`I&U2fwr420k3EQar}Xdk!5UV)Yvmw<j;NzD0o<TwdnK(I;8d_($gZJJ?6_l#ImZRj>2S;vA<OV==Tc!NYctOqMQG}&13S&Ihzx^*Nrd4FAml%eR(?t`C(=A*V1f3&C+L^*6@_sz<Aj@tO(ZbK9|36`u|U-9iJ$?L<@@1=Tr2s+iYU~h7_C`41cX^AU7yvb&h+{zQs2eep5Cy~;UKt;whyVzzj5bI~b4^^7B`A*y7B~WNVG%95TZzOpP?0tJ@_RFdn>!fJHxzv;_kR=l3*Ck(J#dlZaS?$<tqoZf4B|Dpxqs=wq?&<I$jQiM+aHNzU?9vtgnrPQDX7tRHa7WW&JnxS<wUB&hJH@|ekfV0jHmB|3+(DMT2rNFYuJ{rS98RDA04bMC?2LGgk4qiHxVwcbPU*eMR{_y&dBY;rjU|RX^HBy8P@~oLKN+~^Km')).decode().split()[a-1:b]))
