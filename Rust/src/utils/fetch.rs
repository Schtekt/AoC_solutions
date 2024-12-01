use reqwest::blocking::Client;
use reqwest::header::{HeaderMap, HeaderValue};

pub fn fetch_input(year: u32, day: u8, cookie: &str) -> Result<String, Box<dyn std::error::Error>>{
    let client = Client::new();

    let url = format!("https://adventofcode.com/{year}/day/{day}/input");

    let mut headers = HeaderMap::new();
    
    let cookie_session: String = format!("session={cookie}");

    headers.insert("Cookie", HeaderValue::from_str(&cookie_session)?);

    let response = client.get(url).headers(headers).send()?.text()?;

    return Ok(response);
}