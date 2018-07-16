#!/bin/bash
refmt --print=binary tests/src/native/IndexNative.re | ./lang_ppx.exe /dev/stdin /tmp/lang-ppx.out.tmp
refmt --print-width=140 --parse=binary --print=re /tmp/lang-ppx.out.tmp > tests/src/native/IndexNativeCpsed.re