# Crypto Warm up
We are given the [encryption code](Warmup.py) and [output.txt](output.txt).

The script concatenates random string to the flag and then perform encryption algorithm using random prime number with `nbit` bits. However, we can get the generated random prime number (`p`) by looking at the output string length which is `19489`.

We are not given the source code of the function `is_valid`, but we can guess that it is about primitive roots. So, using the [primitive roots calculator](http://www.bluetulip.org/2014/programs/primitive.html), we can get all possible values of `s`.

Now, that we have `p` value and list of possible `s` values, we can bruteforce our way to the flag. (using [solution.py](solution.py))

`ASIS{_how_d3CrYpt_Th1S_h0m3_m4dE_anD_wEird_CrYp70_5yST3M?!!!!!!}`

~ Solution by [Dusan](https://github.com/duca9) and me.
