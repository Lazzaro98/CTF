# babyrev
We are given binary (uploaded here), which when we run, asks us for input. So, our task is to figure out the expected input which is also the flag. 

### Analyzing the binary
Looking at the decompiled code from ghidra, we see:

[![babyrev_ghidra_1](https://i.ibb.co/N2KtHqG/babyrev1.jpg "babyrev_ghidra_1")](https://i.ibb.co/N2KtHqG/babyrev1.jpg "babyrev_ghidra_1")

First 7 characters of our input have to be `corctf{`, our input needs to end with `}`, and it needs to be 0x1c long, which is 28 in decimal.  If we pass that test, then the program tests the input excluding first 7 characters:

![baby_rev_2](https://i.ibb.co/bvg1CXt/rev-baby-2.jpg "baby_rev_2")

The while loop repeats itself for every character from the input. It calculates `rot_number = rot_number * 4` . If that's not the prime number, it increments until it becomes prime. When we finally have prime number, we rotate the input's character for rot_number (rot_n simply rotates character for given number of spots in alphabet). After this is done, the string that was created this way is compared to `check`, which was previously `memfrob`-ed. 


## Solution
Okay, so let's start reversing it. First we take the values of `check`, and do the opposite of memfrob(XOR42) - which is just XORing every byte with 42. 

    int check[] = {0x5f, 0x40, 0x5a, 0x15, 0x75, 0x45, 0x62, 0x53, 0x75, 0x46, 0x52, 0x43, 0x5f, 0x75, 0x50, 0x52, 0x75, 0x5f, 0x5c, 0x4f};
    for(int i=0;i<sizeof(check)/sizeof(check[0]);i++)
        check[i]^=42;
After that, we do exactly the same thing as they did while encrypting - find the first prime number coming after `counter*4`, and `Inverse_rot_n` our char for that number. **Inverse_rot_n(index)** is the same as **rot_n(26 - index % 26)**. ( I just copied the same `rot_n` and `is_prime` functions as ghidra decompiled. )



    int counter = 0x1c-7;
    while(counter-->=0) {
        int rot_number = counter*4;
        while(!is_prime(rot_number))rot_number+=1;
        check[counter] = rot_n((char)check[counter], 26-(rot_number%26));
    }
All we need to do now is to print `check` together with excluded first 7 characters - `corctf{` and `}`. 


    cout<<"corctf{";
    for(int i=0;i<sizeof(check)/sizeof(check[0]);i++)
        cout<<(char)check[i];
    cout<<"}";

`corctf{see?_rEv_aint_so_bad}`
