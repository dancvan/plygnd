use std::io;
use rand::Rng;

fn main() {
	let answer = rand::thread_rng().gen_range(1..101);
	// println!("number is {}", number);
    let mut guess = 0;
    let mut buffer = String::new();
    
	while guess != answer {
        buffer = String::new();
		println!("Enter a number between 1 and 100:");
		io::stdin().read_line(&mut buffer);
		guess = buffer.trim().parse::<i32>().unwrap();
		/* or let number: i32 = buffer.trim().parse().unwrap(); */
        if guess < answer {
            println!("Too low\n");
        }
        if guess > answer {
            println!("Too high\n");
		println!("Try again\n");
        }
        if guess == answer{
            break
        }
	}
    println!("Congratulations you won! (Answer: {})", answer) 
}


