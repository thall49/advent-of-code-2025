use anyhow::{Result, Context};

fn main() {
    let input = include_str!("input.txt");
    match process(input) {
        Ok(v) => println!("{}", v),
        Err(e) => println!("Error in input: {}", e),
    }
}

fn process(input: &str) -> Result<u64> {
    let mut sum: u64 = 0;

    for range in input.split(",") {
        let total = parse(range)?;
        sum += total;
    }

    Ok(sum)
}

fn parse(input: &str) -> Result<u64> {
    let dash = input.find("-").with_context(|| format!("Unable to find dash in {}", input))?;

    let lower = &input[..dash].to_string();
    let upper = input[(dash + 1)..].parse::<u64>()?;

    let len = (lower.len() + 1) / 2;

    let mut check: u64 = 0;
    while check < upper {
        
    }


    

    Ok(0)
}

#[cfg(test)]
mod tests {
    use crate::process;
    use anyhow::Result;

    #[test]
    fn test_process() -> Result<()> {
        let input = "1-22,95-115,998-1012,1188511880-1188511890,222220-222224,
1698522-1698528,446443-446449,38593856-38593862,565653-565659,
824824821-824824827,2121212118-2121212124";

        assert_eq!(1227775554u64, process(input)?);
        Ok(())
    }
}