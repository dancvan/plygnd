struct Rectangle(f64, f64);

impl Rectangle{
    fn new(length:f64, width:f64) -> Rectangle {
        Rectangle(length, width)
    }

    fn get_area(&self) -> f64 {
        &self.0*&self.1
    }

    fn scale(&mut self, scale:f64) {
        self.0*=scale; 
        self.1*=scale;
    }
}

fn main() {
    let mut rect = Rectangle::new(1.2, 3.4);
    assert_eq!(rect.get_area(), 4.08);
    println!("{}", rect.get_area());
    rect.scale(0.5);
    println!("{}", rect.get_area());
    assert_eq!(rect.get_area(), 1.02); 
    println!("Tests passed!");
}
