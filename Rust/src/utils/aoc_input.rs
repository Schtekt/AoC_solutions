use std::io::{Read, Write};
use std::path::Path;
use std::fs::File;

use super::fetch::fetch_input;

pub fn get_input(year: u32, day: u8) -> Result<String, Box<dyn std::error::Error>> {
    let file_path = format!("Resources/{year}/day{day}.txt");
    let path = Path::new(&file_path);

    if path.exists() {
        let mut file = File::open(path)?;
        let mut buf = String::new();
        let _ = file.read_to_string(&mut buf);
        return Ok(buf);
    }
    else {
        let mut cookie_file = File::open("Resources/config.txt")?;
        let mut cookie_buf = String::new();
        let _ = cookie_file.read_to_string(&mut cookie_buf);

        let data = fetch_input(year, day, &cookie_buf)?;
        let mut data_file = File::create(file_path)?;
        
        data_file.write_all(data.as_bytes())?;

        return Ok(data);
    }
}