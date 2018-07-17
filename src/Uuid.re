/*---------------------------------------------------------------------------
   Copyright (c) 2008 Daniel C. B nzli. All rights reserved.
   Distributed under the ISC license, see terms at the end of the file.
   %%NAME%% %%VERSION%%
  ---------------------------------------------------------------------------*/
type t = string; /* 16 bytes long strings */

type version = [ | `V3(t, string) | `V4 | `V5(t, string)];

let nil = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";

let ns_dns = "k\167\184\016\157\173\017\209\128\180\000\192O\2120\200";

let ns_url = "k\167\184\017\157\173\017\209\128\180\000\192O\2120\200";

let ns_oid = "k\167\184\018\157\173\017\209\128\180\000\192O\2120\200";

let ns_X500 = "k\167\184\020\157\173\017\209\128\180\000\192O\2120\200";

let rand = (s, ()) => Random.State.bits(s); /* 30 random bits generator. */

let default_rand = rand(Random.State.make_self_init());

let md5 = Digest.string;

/* sha-1 digest. Based on pseudo-code of RFC 3174.
   Slow and ugly but does the job. */
let sha_1 = s => {
  let sha_1_pad = s => {
    let len = String.length(s);
    let blen = 8 * len;
    let rem = len mod 64;
    let mlen =
      if (rem > 55) {
        len + 128 - rem;
      } else {
        len + 64 - rem;
      };
    let m = Bytes.create(mlen);
    Bytes.blit_string(s, 0, m, 0, len);
    Bytes.fill(m, len, mlen - len, '\000');
    Bytes.set(m, len, '\128');
    if (Sys.word_size > 32) {
      Bytes.set(m, mlen - 8, Char.unsafe_chr(blen lsr 56 land 255));
      Bytes.set(m, mlen - 7, Char.unsafe_chr(blen lsr 48 land 255));
      Bytes.set(m, mlen - 6, Char.unsafe_chr(blen lsr 40 land 255));
      Bytes.set(m, mlen - 5, Char.unsafe_chr(blen lsr 32 land 255));
    };
    Bytes.set(m, mlen - 4, Char.unsafe_chr(blen lsr 24 land 255));
    Bytes.set(m, mlen - 3, Char.unsafe_chr(blen lsr 16 land 255));
    Bytes.set(m, mlen - 2, Char.unsafe_chr(blen lsr 8 land 255));
    Bytes.set(m, mlen - 1, Char.unsafe_chr(blen land 255));
    m;
  };
  /* Operations on int32 */
  let (&&&) = (land);
  let (lor) = Int32.logor;
  let (lxor) = Int32.logxor;
  let (land) = Int32.logand;
  let (++) = Int32.add;
  let lnot = Int32.lognot;
  let sr = Int32.shift_right;
  let sl = Int32.shift_left;
  let cls = (n, x) => sl(x, n) lor Int32.shift_right_logical(x, 32 - n);
  /* Start */
  let m = sha_1_pad(s);
  let w = Array.make(16, 0l);
  let h0 = ref(1732584193l);
  let h1 = ref(-271733879l);
  let h2 = ref(-1732584194l);
  let h3 = ref(271733878l);
  let h4 = ref(-1009589776l);
  let a = ref(0l);
  let b = ref(0l);
  let c = ref(0l);
  let d = ref(0l);
  let e = ref(0l);
  for (i in 0 to Bytes.length(m) / 64 - 1) {
    /* Fill w */
    /* For each block */
    let base = i * 64;
    for (j in 0 to 15) {
      let k = base + j * 4;
      w[j] =
        sl(Int32.of_int(Char.code @@ Bytes.get(m, k)), 24)
        lor sl(Int32.of_int(Char.code @@ Bytes.get(m, k + 1)), 16)
        lor sl(Int32.of_int(Char.code @@ Bytes.get(m, k + 2)), 8)
        lor Int32.of_int(Char.code @@ Bytes.get(m, k + 3));
    };
    /* Loop */
    a := h0^;
    b := h1^;
    c := h2^;
    d := h3^;
    e := h4^;
    for (t in 0 to 79) {
      let (f, k) =
        if (t <= 19) {
          (b^ land c^ lor (lnot(b^) land d^), 1518500249l);
        } else if (t <= 39) {
          (b^ lxor c^ lxor d^, 1859775393l);
        } else if (t <= 59) {
          (b^ land c^ lor (b^ land d^) lor (c^ land d^), (-1894007588l));
        } else {
          (b^ lxor c^ lxor d^, (-899497514l));
        };
      let s = t &&& 15;
      if (t >= 16) {
        w[s] = cls(1, w[s + 13 &&& 15] lxor w[s + 8 &&& 15] lxor w[s + 2 &&& 15] lxor w[s]);
      };
      let temp = (((cls(5, a^) ++ f) ++ e^) ++ w[s]) ++ k;
      e := d^;
      d := c^;
      c := cls(30, b^);
      b := a^;
      a := temp;
    };
    /* Update */
    h0 := h0^ ++ a^;
    h1 := h1^ ++ b^;
    h2 := h2^ ++ c^;
    h3 := h3^ ++ d^;
    h4 := h4^ ++ e^;
  };
  let h = Bytes.create(20);
  let i2s = (h, k, i) => {
    Bytes.set(h, k, Char.unsafe_chr(Int32.to_int(sr(i, 24)) &&& 255));
    Bytes.set(h, k + 1, Char.unsafe_chr(Int32.to_int(sr(i, 16)) &&& 255));
    Bytes.set(h, k + 2, Char.unsafe_chr(Int32.to_int(sr(i, 8)) &&& 255));
    Bytes.set(h, k + 3, Char.unsafe_chr(Int32.to_int(i) &&& 255));
  };
  i2s(h, 0, h0^);
  i2s(h, 4, h1^);
  i2s(h, 8, h2^);
  i2s(h, 12, h3^);
  i2s(h, 16, h4^);
  Bytes.unsafe_to_string(h);
};

let msg_uuid = (v, digest, ns, n) => {
  let u = Bytes.sub(Bytes.unsafe_of_string(digest(ns ++ n)), 0, 16);
  Bytes.set(u, 6) @@ Char.unsafe_chr(v lsl 4 lor (Char.code(Bytes.get(u, 6)) land 15));
  Bytes.set(u, 8) @@ Char.unsafe_chr(128 lor (Char.code(Bytes.get(u, 8)) land 63));
  Bytes.unsafe_to_string(u);
};

let v3 = (ns, n) => msg_uuid(3, md5, ns, n);

let v5 = (ns, n) => msg_uuid(5, sha_1, ns, n);

let v4_uuid = rand => {
  let r0 = rand();
  let r1 = rand();
  let r2 = rand();
  let r3 = rand();
  let r4 = rand();
  let u = Bytes.create(16);
  Bytes.set(u, 0) @@ Char.unsafe_chr(r0 land 255);
  Bytes.set(u, 1) @@ Char.unsafe_chr(r0 lsr 8 land 255);
  Bytes.set(u, 2) @@ Char.unsafe_chr(r0 lsr 16 land 255);
  Bytes.set(u, 3) @@ Char.unsafe_chr(r1 land 255);
  Bytes.set(u, 4) @@ Char.unsafe_chr(r1 lsr 8 land 255);
  Bytes.set(u, 5) @@ Char.unsafe_chr(r1 lsr 16 land 255);
  Bytes.set(u, 6) @@ Char.unsafe_chr(64 lor (r1 lsr 24 land 15));
  Bytes.set(u, 7) @@ Char.unsafe_chr(r2 land 255);
  Bytes.set(u, 8) @@ Char.unsafe_chr(128 lor (r2 lsr 24 land 63));
  Bytes.set(u, 9) @@ Char.unsafe_chr(r2 lsr 8 land 255);
  Bytes.set(u, 10) @@ Char.unsafe_chr(r2 lsr 16 land 255);
  Bytes.set(u, 11) @@ Char.unsafe_chr(r3 land 255);
  Bytes.set(u, 12) @@ Char.unsafe_chr(r3 lsr 8 land 255);
  Bytes.set(u, 13) @@ Char.unsafe_chr(r3 lsr 16 land 255);
  Bytes.set(u, 14) @@ Char.unsafe_chr(r4 land 255);
  Bytes.set(u, 15) @@ Char.unsafe_chr(r4 lsr 8 land 255);
  Bytes.unsafe_to_string(u);
};

let v4_gen = seed => {
  let rand = rand(seed);
  fun
  | () => v4_uuid(rand);
};

let v =
  fun
  | `V4 => v4_uuid(default_rand)
  | `V3(ns, n) => v3(ns, n)
  | `V5(ns, n) => v5(ns, n);

let create = v; /* deprecated */

let compare: (string, string) => int = Pervasives.compare;

let equal = (u, u') => compare(u, u') == 0;

let to_bytes = s => s;

let of_bytes = (~pos=0, s) => {
  let len = String.length(s);
  if (pos + 16 > len) {
    None;
  } else if (pos == 0 && len == 16) {
    Some(s);
  } else {
    Some(String.sub(s, pos, 16));
  };
};

let mixed_swaps = s => {
  let swap = (b, i, j) => {
    let t = Bytes.get(b, i);
    Bytes.set(b, i, Bytes.get(b, j));
    Bytes.set(b, j, t);
  };
  let b = Bytes.of_string(s);
  swap(b, 0, 3);
  swap(b, 1, 2);
  swap(b, 4, 5);
  swap(b, 6, 7);
  Bytes.unsafe_to_string(b);
};

let to_mixed_endian_bytes = s => mixed_swaps(s);

let of_mixed_endian_bytes = (~pos=?, s) =>
  switch (of_bytes(~pos?, s)) {
  | None => None
  | Some(s) => Some(mixed_swaps(s))
  };

let unsafe_of_bytes = u => u;

let unsafe_to_bytes = u => u;

let of_string = (~pos=0, s) => {
  let len = String.length(s);
  if (pos + 36 > len || s.[pos + 8] != '-' || s.[pos + 13] != '-' || s.[pos + 18] != '-' || s.[pos + 23] != '-') {
    None;
  } else {
    try (
      {
        let u = Bytes.create(16);
        let i = ref(0);
        let j = ref(pos);
        let ihex = c => {
          let i = Char.code(c);
          if (i < 48) {
            raise(Exit);
          } else if (i <= 57) {
            i - 48;
          } else if (i < 65) {
            raise(Exit);
          } else if (i <= 70) {
            i - 55;
          } else if (i < 97) {
            raise(Exit);
          } else if (i <= 102) {
            i - 87;
          } else {
            raise(Exit);
          };
        };
        let byte = (s, j) => Char.unsafe_chr(ihex(s.[j]) lsl 4 lor ihex(s.[j + 1]));
        while (i^ < 4) {
          Bytes.set(u, i^, byte(s, j^));
          j := j^ + 2;
          incr(i);
        };
        incr(j);
        while (i^ < 6) {
          Bytes.set(u, i^, byte(s, j^));
          j := j^ + 2;
          incr(i);
        };
        incr(j);
        while (i^ < 8) {
          Bytes.set(u, i^, byte(s, j^));
          j := j^ + 2;
          incr(i);
        };
        incr(j);
        while (i^ < 10) {
          Bytes.set(u, i^, byte(s, j^));
          j := j^ + 2;
          incr(i);
        };
        incr(j);
        while (i^ < 16) {
          Bytes.set(u, i^, byte(s, j^));
          j := j^ + 2;
          incr(i);
        };
        Some(Bytes.unsafe_to_string(u));
      }
    ) {
    | Exit => None
    };
  };
};

let to_string = (~upper=false, u) => {
  let hbase = if (upper) {55} else {87};
  let hex = (hbase, i) =>
    Char.unsafe_chr(
      if (i < 10) {
        48 + i;
      } else {
        hbase + i;
      },
    );
  let s = Bytes.of_string("XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX");
  let i = ref(0);
  let j = ref(0);
  let byte = (s, i, c) => {
    Bytes.set(s, i) @@ hex(hbase, c lsr 4);
    Bytes.set(s, i + 1) @@ hex(hbase, c land 15);
  };
  while (j^ < 4) {
    byte(s, i^, Char.code(u.[j^]));
    i := i^ + 2;
    incr(j);
  };
  incr(i);
  while (j^ < 6) {
    byte(s, i^, Char.code(u.[j^]));
    i := i^ + 2;
    incr(j);
  };
  incr(i);
  while (j^ < 8) {
    byte(s, i^, Char.code(u.[j^]));
    i := i^ + 2;
    incr(j);
  };
  incr(i);
  while (j^ < 10) {
    byte(s, i^, Char.code(u.[j^]));
    i := i^ + 2;
    incr(j);
  };
  incr(i);
  while (j^ < 16) {
    byte(s, i^, Char.code(u.[j^]));
    i := i^ + 2;
    incr(j);
  };
  Bytes.unsafe_to_string(s);
};

let pp = (ppf, u) => Format.pp_print_string(ppf, to_string(u));

let pp_string = (~upper=?, ppf, u) => Format.pp_print_string(ppf, to_string(~upper?, u));

let print = pp_string; /* deprecated */
/*---------------------------------------------------------------------------
   Copyright (c) 2008 Daniel C. B nzli
   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.
   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
  ---------------------------------------------------------------------------*/