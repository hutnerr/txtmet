use std::env;

const MAX_ARGS: usize = 7;

const USAGE: &str = "Usage: ./txtmet <option(s)> <input_file>
Options:
  -w: count words (default)
  -c: count characters
  -s: count sentences
  -l: count lines
  -a: count all";

const NEWLINE: char = '\n';
const SPACE: char = ' ';
const TAB: char = '\t';

struct FlagOptions
{
    words: bool,
    chars: bool,
    sentences: bool,
    lines: bool,
}

struct TextData
{
    words: usize,
    chars: usize,
    charsws: usize,
    sentences: usize,
    lines: usize,
}

fn main()
{
    let args: Vec<String> = env::args().collect();

    if args.len() == 1 || args.len() > MAX_ARGS
    {
        log_error("Please provide arguments...");
    }

    let filename = match args.last()
    {
        Some(f) => f.clone(),
        None => {
            log_error("Please provide a file...");
            return;
        }
    };

    let options: FlagOptions = if args.len() == 2
    {
        // 2 args likely means just a filename, no flags. use default
        FlagOptions
        {
            words: true,
            chars: false,
            sentences: false,
            lines: false,
        }
    }
    else
    {
        match parse_cla(args)
        {
            Some(o) => o,
            None => {
                log_error("Invalid flag...");
                return;
            }
        }
    };

    let text = match std::fs::read_to_string(filename)
    {
        Ok(t) => t,
        Err(e) => {
            log_error(e.to_string().as_str());
            return;
        }
    };

    let data: TextData = get_data(text);
    if options.words     { println!("{:<15} {:>8}", "Words", data.words); }
    if options.chars     {
        println!("{:<15} {:>8}", "Chars (no WS)", data.chars);
        println!("{:<15} {:>8}", "Chars (WS)", data.charsws);
    }
    if options.sentences { println!("{:<15} {:>8}", "Sentences", data.sentences); }
    if options.lines     { println!("{:<15} {:>8}", "Lines", data.lines); }
}

fn parse_cla(args: Vec<String>) -> Option<FlagOptions>
{
    let mut options: FlagOptions = FlagOptions
    {
        words: false,
        chars: false,
        sentences: false,
        lines: false
    };

    for arg in &args[1..args.len() - 1]
    {
        if !arg.starts_with('-') { return None; }

        for ch in arg[1..].chars()
        {
            match ch
            {
                'w' => options.words = true,
                'c' => options.chars = true,
                's' => options.sentences = true,
                'l' => options.lines = true,
                'a' => {
                    options.words = true;
                    options.chars = true;
                    options.sentences = true;
                    options.lines = true;
                },
                _ => return None
            }
        }
    }
    Some(options)
}

fn get_data(filetext: String) -> TextData
{
    let mut data: TextData = TextData
    {
        words: 0,
        chars: 0,
        charsws: 0,
        sentences: 0,
        lines: 0,
    };

    let mut in_word = false;

    for c in filetext.chars()
    {
        data.charsws += 1;
        match c
        {
            NEWLINE => {
                data.lines += 1;
                if in_word {
                    data.words += 1;
                    in_word = false;
                }
            }
            SPACE | TAB => {
                if in_word {
                    data.words += 1;
                    in_word = false;
                }
            }
            '.' | '?' | '!' => {
                data.sentences += 1;
                data.chars += 1;
                in_word = true;
            },
            _ => {
                data.chars += 1;
                in_word = true;
            }
        }
    }

    // we likely have at least 1 line even if no newline
    if !filetext.is_empty() && !filetext.ends_with('\n') { data.lines += 1; }
    if in_word { data.words += 1; }

    data
}

fn log_error(s: &str)
{
    eprintln!("[ERROR] {}\n", s);
    eprintln!("{}", USAGE);
}
