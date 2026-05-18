fn main() {
    let input = include_str!("input.txt");
    match process(input) {
        Some(v) => println!("{}", v),
        None => println!("Error in input"),
    }
}

fn process(input: &str) -> Option<i32> {
    let moves = match parse(input) {
        Ok(v) => v,
        Err(e) => {
            println!("Error {}", e);
            return None;
        }
    };

    let mut dial = 50;
    let mut counter = 0;

    for t in moves {
        dial += t;
        dial = dial.rem_euclid(100);

        if dial == 0 {
            counter += 1;
        }

    }

    return Some(counter)
}

fn parse(input: &str) -> Result<Vec<i32>, String> {
    input.lines().map(|line| {
        if let Some(amount) = line.strip_prefix("L") {
            match amount.parse::<i32>() {
                Ok(n) => Ok(-n),
                Err(e) => Err(e.to_string()),
            }
        }
        else if let Some(amount) = line.strip_prefix("R") {
            match amount.parse::<i32>() {
                Ok(n) => Ok(n),
                Err(e) => Err(e.to_string()),
            }
        }
        else {
            panic!();
        }
    }).collect()
}

#[cfg(test)]
mod tests {
    use crate::process;

    #[test]
    fn test_process() {
        let input = "L68
L30
R48
L5
R60
L55
L1
L99
R14
L82";

        assert_eq!(Some(3), process(input))
    }
}