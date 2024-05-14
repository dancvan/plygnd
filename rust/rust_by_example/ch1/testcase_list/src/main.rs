use std::fmt;

struct List(Vec<i32>);

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let vec = &self.0;

        write!(f, "[")?;

        for (count, v) in vec.iter().enumerate() {
            if count != 0 { write!(f, ", ")?; }
            write!(f, "{}", v)?;
         }
        write!(f, "]")
    }
}

fn main() {
    let v = List(vec![1,2,3]);
    println!("{}", v);
}

//ACTIVITY
// Change the program so the index of each element is also printed.
// [0: 1, 1: 2, 2: 3]
