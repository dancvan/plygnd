struct Satellite {
    name: String, 
    velocity f64 // miles per second
}

impl fmt::Display for Satellite {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Reult {
            write!(f, "{} flying at {} miles per hour", self.name, self.velicity)
    }
}

fn main() {
    let hubble = Satellite {
        name: String::from("Hubble Telescope"), 
        velocity: 4.72
    };
    println!("hubble is {}", hubble);
}
