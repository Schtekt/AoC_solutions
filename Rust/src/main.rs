mod utils;
mod solutions;

fn main() -> Result<(), Box<dyn std::error::Error>>{

    let input = utils::aoc_input::get_input(2024, 1)?;

    println!("Part1:\n{}", solutions::_2024::day1::part1(&input)?);

    println!("Part2:\n{}", solutions::_2024::day1::part2(&input)?);

    return Ok(());
}