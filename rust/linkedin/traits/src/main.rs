use std::fmt;

struct Satellite {
	name: String, 
	velocity: f64 //miles per second
}

trait Description {
    fn describe(&self) -> String;
}
   
impl Description for Satellite {
    fn describe(&self) -> String {
        format!("the {} flying at {} miles per second!", self.name, self.velocity)
    }
}

fn main() {
	let hubble = Satellite {
		name: String::from("Hubble Telescope"), 
		velocity: 4.72
	};
	println!("hubble is {}", hubble.describe());
}
