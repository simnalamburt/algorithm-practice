// fpc solution.pas -O2 -Coti -vwnh

function popcount(bitset: Int64): Int64;
begin
  popcount := 0;
  while bitset <> 0 do begin
    popcount += 1;
    bitset := bitset and (bitset - 1);
  end;
end;

var
  N, M, i, sum, j, bitset_guitars, bitset_songs, songs_max, guitars_min, count_guitars, count_songs: Int64;
  DATA: Array[0..9] of Int64;
  sink: Char;
  buffer: String;
begin
  // Handle input
  readln(N, M);

  for i := 0 to N-1 do begin
    read(sink);
    while sink <> ' ' do begin
      read(sink);
    end;
    readln(buffer);

    sum := 0;
    for j := 0 to M-1 do begin
      if buffer[j+1] = 'Y' then begin
        sum += Int64(1) shl j;
      end;
    end;

    DATA[i] := sum;
  end;

  // Brute-force
  songs_max := 0;
  guitars_min := -1;
  for bitset_guitars := 0 to (1<<N) - 1 do begin
    bitset_songs := 0;

    for i := 0 to N-1 do begin
      if (bitset_guitars and (1 << i)) <> 0 then begin
        bitset_songs := bitset_songs or DATA[i];
      end;
    end;

    count_guitars := popcount(bitset_guitars);
    count_songs := popcount(bitset_songs);

    if count_songs > songs_max then begin
      songs_max := count_songs;
      guitars_min := count_guitars;
    end else if (count_songs = songs_max) and (count_guitars < guitars_min) then begin
      guitars_min := count_guitars;
    end
  end;

  writeln(guitars_min);
end.
