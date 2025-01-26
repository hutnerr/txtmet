# TXTMET
This program is a command line utility to give metrics about a `.txt` file.
- Word count
- Character count (with and without whitespace)
- Sentence count
- Lines count

Compile using `gcc txtmet.c filemetrics.c -o txtmet`

```
Usage: ./txtmet <option(s)> <input_file>
Supported filetypes: .txt
Options:
  -w: count words (default)
  -c: count characters
  -s: count sentences
  -l: count lines
  -a: count all
```

**Examples**
- `./txtmet`               Will provide a help message
- `./txtmet test.txt`      Prints word metrics (default option)
- `./txtmet -w test.txt`   Prints word metrics 
- `./txtmet -a test.txt`   Prints all metrics
- `./txtmet -wl test.txt`  Prints word and line metrics
