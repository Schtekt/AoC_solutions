pub fn part1(input: &String) -> Result<String, Box<dyn std::error::Error>> {
    let mut left = Vec::<i32>::new();
    let mut right = Vec::<i32>::new();

    for line in input.lines() {
        let mut parts = line.split_whitespace();

        left.push(parts.next().unwrap().parse::<i32>()?);

        right.push(parts.next().unwrap().parse::<i32>()?);
    }

    left.sort();
    right.sort();

    if left.len() != right.len() {
        return Err(Box::new(std::fmt::Error));
    }

    let mut sum = 0;
    for i in 0..left.len() {
        sum += (left[i] - right[i]).abs();
    }

    return Ok(sum.to_string());
}

pub fn part2(input: &String) -> Result<String, Box<dyn std::error::Error>> {
    let mut left = Vec::<i32>::new();
    let mut right = Vec::<i32>::new();

    for line in input.lines() {
        let mut parts = line.split_whitespace();

        left.push(parts.next().unwrap().parse::<i32>()?);

        right.push(parts.next().unwrap().parse::<i32>()?);
    }

    left.sort();
    right.sort();

    if left.len() != right.len() {
        return Err(Box::new(std::fmt::Error));
    }

    let mut sum = 0;
    for i in 0..left.len() {
        let count = right.iter().filter(|&x| *x == left[i]).count();
        sum += (count as i32) * left[i];
    }

    return Ok(sum.to_string());
}