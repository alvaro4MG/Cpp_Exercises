use std::sync::{Arc, Mutex};
use std::thread;

const THREADS : i32 = 5;
const MAX_COUNTS : i32 = 50000;

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..THREADS {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            for _ in 0..MAX_COUNTS{
                let mut num = counter.lock().unwrap();

                *num += 1;
            }
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}