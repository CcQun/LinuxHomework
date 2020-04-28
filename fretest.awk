#!/usr/bin/awk -f
{f[$1]++} END {m = 0;c = f[m];for (i in f) {if(f[i]>f[m]) m = i;c=f[m]};print m,c}
