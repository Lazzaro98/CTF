# AliceInCeptionland



We are given a .NET .exe file (uploaded here). 

We will be needing a:
 - .NET decompiler and debugger. I used JetBrains dotPeek but you can as well use .NET Reflector
 - Visual Studio C#


There are three stages of the challenge, each consisting of a task that requires from us to find the right input. So let's begin.

## The Chesire Cat
If we move Alice to the first question mark, we are starting the first challenge - The Cheshire Cat.  Looking at a decompiler, we see there is a class ChesireCat, and we easily find the encryption code there:

    string str = WhiteRabbit.Transform("41!ce1337");
    char[] array = WhiteRabbit.Transform(this.textBox1.Text).Reverse<char>().ToArray<char>();
    for (int index = 0; index < array.Length; ++index)
	array[index] ^= str[index % str.Length];
	if (!string.Join<char>("", ((IEnumerable<char>) array).Reverse<char>()).Equals("oI!&}IusoKs ?Ytr"))
            return;

We see here that after our input is XOR-ed with `str`, it needs to be equal to `oI!&}IusoKs ?Ytr`. The WhiteRabbit.Transform(string) just returns string that is passed as argument. So let's do some rev here, and write reversed function in C# :

    string str = "41!ce1337";
    char[] array = ("oI!&}IusoKs ?Ytr").Reverse<char>().ToArray<char>();
    for (int index = 0; index < array.Length; ++index)
	    array[index] ^= str[index % str.Length];
    for (int index = array.Length - 1; index >= 0; index--)
	    Console.Write(array[index]);
which gives us output `\xDE\xAD\xBE\xEF`, which is the solution for the first stage.

## The Catterpillar
After we killed the evil cat, we move the Alice to the next question mark and start the second stage. The same way as in stage one, we find the class and encryption. Considering every character is seperately encrypted, we can just avoid writing reverse function, and easily bruteforce it. (Could have been done in the 1st stage as well). 

    string str = "c4t3rp1114rz_s3cr3t1y_ru13_7h3_w0r1d";
    char[] array = ("\0R\u009C\u007F\u0016ndC\u0005î\u0093MíÃ×\u007F\u0093\u0090\u007FS}\u00AD\u0093)ÿÃ\f0\u0093g/\u0003\u0093+Ã¶\0Rt\u007F\u0016\u0087dC\aî\u0093píÃ8\u007F\u0093\u0093\u007FSz\u00AD\u0093ÇÿÃÓ0\u0093\u0086/\u0003q").Reverse<char>().ToArray<char>();
    for (int index = 0; index < array.Length; ++index)
    {
	    for (int i = 0; i < 128; i++)//try every printable ASCII value
	    {
		    byte num = rol((byte)((uint)(byte)((uint)(byte)((uint)rol((byte)i, (byte)114) + 222U) ^ (uint)Convert.ToByte(str[index % str.Length])) - (uint)sbyte.MaxValue), (byte)6);
		    if (array[index] == Convert.ToChar(num))//and check if that's the one we need.
				{
				    array[index] = Convert.ToChar((byte)i);
				    break;
				}
	    }
    }
    for (int index = array.Length - 1; index >= 0; index--)
	    Console.Write(array[index]); 
Executing the code, we bruteforced the solution for the 2nd stage, which is `\x4\xL\x1\xC\x3\x1\xS\xN\x0\xT\x4\xS\xL\x3\x3\xP\xS\x4\xV\x3\xH\x3\xR` 

##  Deep dream
In the third stage, we are again given encrpyted string, and using debugger we can see what Encode method looks like. ![Encode method](https://i.ibb.co/VQqwDKB/Screenshot-2021-08-23-041225.png)

Using the `Dream.<Encode>g__fm|3_3` function (fm33 in the code below), we can make a dictionary for all characters. We will do it only for characters that appear in our solution:

	string text = "3c3cf1df89fe832aefcc22fc82017cd57bef01df54235e21414122d78a9d88cfef3cf10c829ee32ae4ef01dfa1951cd51b7b22fc82433ef7ef418cdf8a9d802101ef64f9a495268fef18d52882324f217b1bd64b82017cd57bef01df255288f7593922712c958029e7efccdf081f8808a6efd5287595f821482822f6cb95f821cceff4695495268fefe72ad7821a67ae0060ad"; // given encrypted string
    byte[] array = new byte[]
    {
	    (byte)(xm & 255UL),
	    (byte)(xm >> 8 & 255UL),
	    (byte)(xm >> 16 & 255UL),
	    (byte)(xm >> 24 & 255UL),
	    (byte)(xm >> 32 & 255UL),
	    (byte)(xm >> 40 & 255UL),
	    (byte)(xm >> 48 & 255UL),
	    (byte)(xm >> 56 & 255UL)
    };
    string text2 = "";
    for (int i = 0; i < text.Length/2; i++)
	    text2 += Convert.ToChar((byte)(StringToByteArrayFastest("" + text[i * 2] + text[i*2 + 1])[0] ^ array[i % array.Length]));
    
    string dict = "";
    for (int i = 1; i < 256; i++) {
	string find = fm33((char)i)+"/";
    	if (text2.Contains(find)) {
    		dict += Convert.ToChar((byte)i) + " is encrypted with " + find + Environment.NewLine;
		}
    }
The code from above will give us encrypted data - `text2`, and dictionary - `dict`. All we need to do is to replace all the occurences of dict values in text2, and we will get the solution. ( The whole process could have been automated using String.Replace(), but considering it didn't work for extended ASCII for some reason, I decided to do it manually cause string was not that long ). 
`Sleeperio Sleeperio Disappeario Instanterio!`

After we completed all three stages, we get the flag: `corctf{4l1c3_15_1n_d33p_tr0ubl3_b3c4us3_1_d1d_n0t_s4v3_h3r!!:c}`
