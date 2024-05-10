fn main(){
	let a = 13.;
	let b = 2.3;
	let c = 120.0;

    let average = (a + b + c)/3.;
    //let mut average = (a + b + c)/3.;

 //   average = (average * 10.).round()/10.;


assert_eq!(average, 45.1);
println!("Test passed!");
}
