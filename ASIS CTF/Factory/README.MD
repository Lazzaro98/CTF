
# Factory

We are given a [pdf file](factory.pdf).

Using *binwalk*, we can extract all the hidden files. (`binwalk --dd='.*' factory.pdf`)

Now, checking the files' strings, we can see that there is a text inside `4C` file. The file type is BT, but what we can do in order to get flag is to just use strings with the right regex.

`strings 4C | grep "([a-zA-Z0-9]*)" `

This will highlight the text and also the flag: `ASIS{_PDF_1N_PDF_iZ_A_T4sK_fOR_fOreEnSic5_L0v3RS}`
